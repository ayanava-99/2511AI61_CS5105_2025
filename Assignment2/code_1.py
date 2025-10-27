from __future__ import annotations
import os
import pandas as pd
from datetime import datetime
import logging
from typing import Tuple

BASE_DIR = os.getcwd()
OUTPUT_DIR = os.path.join(BASE_DIR, "outputs")
os.makedirs(OUTPUT_DIR, exist_ok=True)
LOG_FILE = os.path.join(OUTPUT_DIR, "allocation.log")

logging.basicConfig(
    filename=LOG_FILE,
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
)
logger = logging.getLogger(__name__)


def compute_faculty_pref_counts_from_df(
    df: pd.DataFrame,
    cgpa_col_name: str = "CGPA",
    output_csv: str | None = None,
    add_total: bool = False,
    add_percent: bool = False,
    percent_decimals: int = 2,
) -> pd.DataFrame:
    if cgpa_col_name not in list(df.columns):
        raise ValueError(f"CGPA column '{cgpa_col_name}' not found.")
    cols = list(df.columns)
    cgpa_idx = cols.index(cgpa_col_name)
    faculty_cols = cols[cgpa_idx + 1 :]
    if len(faculty_cols) == 0:
        logger.info("No faculty names found")
        raise ValueError("No faculty columns found after CGPA column.")
    pref_numeric = df[faculty_cols].apply(pd.to_numeric, errors="coerce")
    num_students = len(df)
    max_pref_val = int(pref_numeric.max().max())
    count_cols = [f"Count Pref {i}" for i in range(1, max_pref_val + 1)]
    result = pd.DataFrame(0, index=faculty_cols, columns=count_cols, dtype=int)
    result.index.name = "Fac"
    for fac in faculty_cols:
        vc = pref_numeric[fac].value_counts(dropna=True).to_dict()
        for rank, cnt in vc.items():
            if pd.isna(rank):
                continue
            rank_int = int(rank)
            if 1 <= rank_int <= max_pref_val:
                result.at[fac, f"Count Pref {rank_int}"] = int(cnt)
    if add_total:
        result["Total"] = result[count_cols].sum(axis=1)
    if add_percent:
        for col in count_cols:
            pct_col = col.replace("Count", "Pct")
            result[pct_col] = (result[col] / float(num_students) * 100).round(percent_decimals)
    if output_csv:
        result.to_csv(output_csv, index=True)
    return result


def detect_faculties(df: pd.DataFrame):
    cols = list(df.columns)
    if "CGPA" not in cols:
        raise KeyError("Input file must contain a 'CGPA' column.")
    cgpa_idx = cols.index("CGPA")
    fac_cols = cols[cgpa_idx + 1 :]
    if not fac_cols:
        raise ValueError("No faculty columns found after CGPA.")
    return fac_cols


def make_bands(df_sorted: pd.DataFrame, n_fac: int):
    total = len(df_sorted)
    base = total // n_fac
    rem = total % n_fac
    bands, start = [], 0
    for i in range(n_fac):
        size = base + (1 if i < rem else 0)
        bands.append(list(range(start, start + size)))
        start += size
    return bands


def init_quotas(fac_cols, total_students):
    n = len(fac_cols)
    base = total_students // n
    rem = total_students % n
    return {fac: base + (1 if i < rem else 0) for i, fac in enumerate(fac_cols)}


def allocate_by_band_with_cycle(input_path: str) -> Tuple[str, str]:
    try:
        df = pd.read_csv(input_path)
        logger.info("Loaded input: %s shape=%s", input_path, df.shape)
        fac_cols = detect_faculties(df)
        n_fac = len(fac_cols)
        total_students = len(df)
        df_sorted = df.copy().sort_values(by="CGPA", ascending=False).reset_index(drop=True)
        bands = make_bands(df_sorted, n_fac)
        quotas = init_quotas(fac_cols, total_students)
        logger.info("Faculties: %s", fac_cols)
        logger.info("Initial quotas: %s", quotas)
        logger.info("Bands sizes: %s", [len(b) for b in bands])
        df_sorted["Allocated"] = pd.NA
        df_sorted["PrefRankAllocated"] = pd.NA
        df_sorted["AssignedCycle"] = pd.NA
        remaining = set(df_sorted.index)

        def rank_to_fac(row: pd.Series):
            m = {}
            for fac in fac_cols:
                try:
                    val = int(row[fac])
                    if 1 <= val <= n_fac:
                        m[val] = fac
                except Exception:
                    continue
            return m

        cycle = 0
        while remaining:
            cycle += 1
            fac_curr_cycle = set()
            assign_curr_cycle = 0
            logger.info("Starting cycle %d; remaining students=%d", cycle, len(remaining))
            for band_idx, band in enumerate(bands):
                student_idx = None
                for idx in band:
                    if idx in remaining:
                        student_idx = idx
                        break
                if student_idx is None:
                    continue
                row = df_sorted.loc[student_idx]
                mapping = rank_to_fac(row)
                allocated = False
                for rank in range(1, n_fac + 1):
                    fac = mapping.get(rank)
                    if not fac:
                        continue
                    if fac in fac_curr_cycle:
                        continue
                    if quotas.get(fac, 0) <= 0:
                        continue
                    df_sorted.at[student_idx, "Allocated"] = fac
                    df_sorted.at[student_idx, "PrefRankAllocated"] = rank
                    df_sorted.at[student_idx, "AssignedCycle"] = cycle
                    quotas[fac] -= 1
                    fac_curr_cycle.add(fac)
                    remaining.remove(student_idx)
                    allocated = True
                    assign_curr_cycle += 1
                    logger.info("Cycle %d: Assigned Roll=%s to %s (pref=%d). Quota left=%d",
                                cycle, row.get("Roll", ""), fac, rank, quotas.get(fac, 0))
                    break
                if not allocated:
                    fallback_fac = None
                    for fac in fac_cols:
                        if fac in fac_curr_cycle:
                            continue
                        if quotas.get(fac, 0) > 0:
                            fallback_fac = fac
                            break
                    if fallback_fac:
                        df_sorted.at[student_idx, "Allocated"] = fallback_fac
                        df_sorted.at[student_idx, "PrefRankAllocated"] = pd.NA
                        df_sorted.at[student_idx, "AssignedCycle"] = cycle
                        quotas[fallback_fac] -= 1
                        fac_curr_cycle.add(fallback_fac)
                        remaining.remove(student_idx)
                        assign_curr_cycle += 1
                        logger.info("Cycle %d: Fallback assigned Roll=%s to %s. Quota left=%d",
                                    cycle, row.get("Roll", ""), fallback_fac, quotas.get(fallback_fac, 0))
                    else:
                        logger.debug(
                            "Cycle %d band %d candidate idx %s could not be assigned this cycle (no available fac/quota).",
                            cycle, band_idx, student_idx)
            logger.info("Cycle %d complete. Assigned this cycle: %d", cycle, assign_curr_cycle)
            if assign_curr_cycle == 0 and remaining:
                logger.warning("No assignments in cycle %d; relaxing per-cycle constraint to finish allocation.", cycle)
                rem_list = sorted(list(remaining))
                for idx in rem_list:
                    assign_flag = False
                    for fac in fac_cols:
                        if quotas.get(fac, 0) > 0:
                            df_sorted.at[idx, "Allocated"] = fac
                            df_sorted.at[idx, "PrefRankAllocated"] = pd.NA
                            df_sorted.at[idx, "AssignedCycle"] = cycle
                            quotas[fac] -= 1
                            remaining.remove(idx)
                            assign_flag = True
                            logger.info("Relaxed assign Cycle %d: Roll=%s -> %s", cycle, df_sorted.at[idx, "Roll"], fac)
                            break
                    if not assign_flag:
                        logger.error("Relaxed mode: no quota left to assign idx %d", idx)

        final_cols = list(df.columns[0:4]) + ["Allocated"]  #+ ["PrefRankAllocated", "AssignedCycle"] #for checking
        df_final = df_sorted[final_cols]
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")

        alloc_file = f"output_btp_mtp_allocation_{timestamp}.csv"
        fac_file = f"fac_preference_count_{timestamp}.csv"

        alloc_path = os.path.join(OUTPUT_DIR, alloc_file)
        fac_path = os.path.join(OUTPUT_DIR, fac_file)

        df_final.to_csv(alloc_path, index=False)
        fac_pref_df = compute_faculty_pref_counts_from_df(df, output_csv=fac_path, add_total=False, add_percent=False) # set add_total, add_percent to verify

        logger.info("Allocation CSV written: %s", alloc_path)
        logger.info("Faculty pref CSV written: %s", fac_path)
        logger.info("Total cycles executed: %d", cycle)
        return alloc_path, fac_path
    except Exception as exc:
        logger.exception("Allocation failed: %s", exc)
        raise


if __name__ == "__main__":
    input_file = os.path.join(BASE_DIR, "input_btp_mtp_allocation.csv")
    if not os.path.exists(input_file):
        raise FileNotFoundError(f"Input CSV not found at {input_file}")
    alloc_csv, fac_csv = allocate_by_band_with_cycle(input_file)
    print("Allocation saved to:", alloc_csv)
    print("Faculty stats saved to:", fac_csv)
    print("Log file:", LOG_FILE)

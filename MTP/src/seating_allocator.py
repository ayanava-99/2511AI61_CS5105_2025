"""
seating_allocator.py — Core logic for exam seating arrangement generation (refactored, no comments).
"""

import os
import math
from collections import defaultdict

import pandas as pd

from .io_utils import read_excel_file
from .attendance_pdf import build_attendance_pdf


class SeatingAllocator:
    def __init__(self, input_file, buffer=0, density="Dense", outdir="output", logger=None):
        self.input_file = input_file
        self.buffer = int(buffer)
        self.density = density
        self.outdir = outdir
        self.logger = logger

        self.sheets = {}
        self.timetable = None
        self.course_roll_map = None
        self.roll_name_map = {}
        self.subject_rolls = defaultdict(list)
        self.room_capacity = []
        self.allocations = defaultdict(list)

        os.makedirs(self.outdir, exist_ok=True)

    def load_inputs(self):
        try:
            self.logger.info("Reading Excel file: %s", self.input_file)
            self.sheets = read_excel_file(self.input_file, logger=self.logger)

            self._load_timetable()
            self._load_roll_name_mapping()
            self._load_course_roll_mapping()
            self._load_room_capacity()

            self.logger.info("Finished loading all input sheets successfully.")
        except Exception as exc:
            self.logger.exception("Error while loading inputs: %s", exc)
            raise

    def _load_timetable(self):
        if "in_timetable" not in self.sheets:
            raise ValueError("Missing required sheet: in_timetable")

        tt_df = self.sheets["in_timetable"]
        needed = ["Date", "Day", "Morning", "Evening"]

        for col in needed:
            if col not in tt_df.columns:
                raise ValueError(f"in_timetable missing required column: {col}")

        def _parse_slot_cell(cell_val):
            if pd.isna(cell_val):
                return ["NO EXAM"]
            text = str(cell_val).strip()
            if not text or text.upper() == "NO EXAM":
                return ["NO EXAM"]
            return [p.strip() for p in text.split(";") if p.strip()]

        timetable_entries = []
        for _, row in tt_df.iterrows():
            date_str = str(row["Date"]).strip()
            day_str = str(row["Day"]).strip()

            morning_list = _parse_slot_cell(row["Morning"])
            evening_list = _parse_slot_cell(row["Evening"])

            timetable_entries.append(
                {
                    "Date": date_str,
                    "Day": day_str,
                    "Morning": morning_list,
                    "Evening": evening_list,
                }
            )

        self.timetable = timetable_entries
        self.logger.info("Timetable loaded with %d days.", len(self.timetable))

    def _load_roll_name_mapping(self):
        if "in_roll_name_mapping" not in self.sheets:
            self.logger.warning(
                "Sheet 'in_roll_name_mapping' not found; names will default to 'Unknown Name'."
            )
            return

        df_names = self.sheets["in_roll_name_mapping"]

        if "Roll" in df_names.columns and "Name" in df_names.columns:
            roll_col = "Roll"
            name_col = "Name"
        else:
            lowered = {c.lower(): c for c in df_names.columns}
            if "roll" in lowered and "name" in lowered:
                roll_col = lowered["roll"]
                name_col = lowered["name"]
            else:
                self.logger.warning(
                    "in_roll_name_mapping does not contain expected columns; "
                    "student names will be marked as 'Unknown Name'."
                )
                return

        count = 0
        for _, row in df_names.iterrows():
            roll = str(row[roll_col]).strip()
            name = str(row[name_col]).strip() or "Unknown Name"
            if roll:
                self.roll_name_map[roll] = name
                count += 1

        self.logger.info("Loaded %d roll-name mappings.", count)

    def _load_course_roll_mapping(self):
        if "in_course_roll_mapping" not in self.sheets:
            raise ValueError("Missing required sheet: in_course_roll_mapping")

        df_map = self.sheets["in_course_roll_mapping"]
        self.course_roll_map = df_map

        lower_map = {c.lower(): c for c in df_map.columns}

        if not {"rollno", "course_code"}.issubset(set(lower_map.keys())):
            raise ValueError("in_course_roll_mapping must contain columns: rollno, course_code")

        roll_col = lower_map["rollno"]
        course_col = lower_map["course_code"]

        n_pairs = 0
        for _, row in df_map.iterrows():
            roll_str = str(row[roll_col]).strip()
            code_str = str(row[course_col]).strip()
            if roll_str and code_str:
                self.subject_rolls[code_str].append(roll_str)
                n_pairs += 1

        self.logger.info(
            "Loaded course-roll mapping: %d mappings, %d distinct subjects.",
            n_pairs,
            len(self.subject_rolls),
        )

    def _load_room_capacity(self):
        if "in_room_capacity" not in self.sheets:
            raise ValueError("Missing required sheet: in_room_capacity")

        room_df = self.sheets["in_room_capacity"]
        col_lut = {c.strip().lower(): c for c in room_df.columns}

        required = ["room no.", "exam capacity", "block"]
        for key in required:
            if key not in col_lut:
                raise ValueError(
                    "in_room_capacity must contain columns: 'Room No.', 'Exam Capacity', 'Block' (case-insensitive)"
                )

        room_col = col_lut["room no."]
        cap_col = col_lut["exam capacity"]
        block_col = col_lut["block"]

        room_list = []
        for _, row in room_df.iterrows():
            room_code = str(row[room_col]).strip()
            try:
                cap = int(row[cap_col])
            except Exception:
                cap = int(float(row[cap_col]))

            block = str(row[block_col]).strip()
            eff_cap = self.effective_capacity(cap)

            room_list.append(
                {
                    "building": block,
                    "room_code": room_code,
                    "capacity": cap,
                    "capacity_effective": eff_cap,
                }
            )

        self.room_capacity = room_list
        self.logger.info("Loaded %d room entries from in_room_capacity.", len(self.room_capacity))

    def effective_capacity(self, capacity):
        try:
            base = max(0, int(capacity) - int(self.buffer))
        except Exception:
            base = max(0, int(float(capacity)) - int(self.buffer))

        if str(self.density).strip().lower() == "sparse":
            return base // 2
        return base

    def check_clashes(self):
        try:
            if self.course_roll_map is None:
                raise ValueError("course_roll_map not loaded; cannot perform clash check.")

            df_map = self.course_roll_map
            lower_cols = {c.lower(): c for c in df_map.columns}
            roll_col = lower_cols.get("rollno")
            course_col = lower_cols.get("course_code")

            if not roll_col or not course_col:
                raise ValueError("in_course_roll_mapping must contain rollno and course_code columns")

            conflict_found = False

            for day_entry in self.timetable:
                date_str = day_entry["Date"]

                for slot_label, subj_list in [("Morning", day_entry["Morning"]), ("Evening", day_entry["Evening"])]:
                    if subj_list == ["NO EXAM"]:
                        continue

                    subj_to_rolls = {}
                    for subj in subj_list:
                        subj_code = str(subj).strip()
                        rolls_set = set(
                            str(x).strip()
                            for x in df_map.loc[
                                df_map[course_col].astype(str).str.strip() == subj_code, roll_col
                            ].dropna()
                        )
                        subj_to_rolls[subj_code] = rolls_set

                    subj_codes = list(subj_to_rolls.keys())
                    for i in range(len(subj_codes)):
                        for j in range(i + 1, len(subj_codes)):
                            s1, s2 = subj_codes[i], subj_codes[j]
                            collided = subj_to_rolls[s1] & subj_to_rolls[s2]
                            if collided:
                                conflict_found = True
                                for roll in collided:
                                    self.logger.error(
                                        "Clash on %s %s: %s & %s -> %s", date_str, slot_label, s1, s2, roll
                                    )

            if conflict_found:
                print("⚠️ Clash detected — check log for details.")
            else:
                self.logger.info("No clashes found in timetable.")
        except Exception as exc:
            self.logger.exception("Error during clash checking: %s", exc)
            raise

    def allocate_subject(self, subject, rolls, room_pool):
        try:
            pending = list(rolls)
            allocations = []

            sorted_rooms = sorted(
                room_pool,
                key=lambda r: r.get("capacity_effective", 0),
                reverse=True,
            )

            for room in sorted_rooms:
                if not pending:
                    break

                remaining_cap = int(room.get("capacity_effective", 0))
                if remaining_cap <= 0:
                    continue

                take_count = min(len(pending), remaining_cap)
                current_batch = pending[:take_count]
                pending = pending[take_count:]

                allocations.append(
                    {
                        "building": room.get("building"),
                        "room": room.get("room_code"),
                        "rolls": current_batch,
                    }
                )

            return allocations, pending
        except Exception as exc:
            self.logger.exception("Error in allocate_subject for %s: %s", subject, exc)
            raise

    def allocate_all_days(self):
        try:
            self.check_clashes()

            for day_entry in self.timetable:
                date_str = day_entry["Date"]
                day_name = day_entry["Day"]

                date_only = str(date_str).split()[0]
                folder_date = date_only.replace("-", "_").replace("/", "_")

                root_folder = os.path.join(self.outdir, folder_date)
                morning_dir = os.path.join(root_folder, "Morning")
                evening_dir = os.path.join(root_folder, "Evening")
                os.makedirs(morning_dir, exist_ok=True)
                os.makedirs(evening_dir, exist_ok=True)

                for slot_label, subj_list in [("Morning", day_entry["Morning"]), ("Evening", day_entry["Evening"])]:
                    slot_dir = morning_dir if slot_label == "Morning" else evening_dir

                    if subj_list == ["NO EXAM"]:
                        try:
                            with open(
                                os.path.join(slot_dir, "NO_EXAM.txt"),
                                "w",
                                encoding="utf-8",
                            ) as fh:
                                fh.write("NO EXAM")
                        except Exception:
                            self.logger.exception("Unable to write NO_EXAM.txt in %s", slot_dir)
                        continue

                    room_pool = [dict(r) for r in self.room_capacity]

                    subj_with_sizes = [
                        (s, len(self.subject_rolls.get(s, []))) for s in subj_list
                    ]
                    subj_with_sizes.sort(key=lambda x: x[1], reverse=True)

                    for subj_code, _ in subj_with_sizes:
                        subj_code = str(subj_code).strip()
                        roll_list = self.subject_rolls.get(subj_code, [])

                        if not roll_list:
                            self.logger.warning(
                                "Subject %s on %s %s has no roll numbers.",
                                subj_code,
                                date_str,
                                slot_label,
                            )
                            try:
                                df_empty = pd.DataFrame(
                                    columns=["Room", "Rolls (semicolon separated)", "Count"]
                                )
                                empty_path = os.path.join(slot_dir, f"{subj_code}.xlsx")
                                df_empty.to_excel(empty_path, index=False)
                            except Exception:
                                self.logger.exception(
                                    "Unable to write empty subject file for %s", subj_code
                                )
                            continue

                        assignments, leftover = self.allocate_subject(
                            subj_code, roll_list, room_pool
                        )

                        if leftover:
                            error_msg = (
                                f"Cannot allocate {len(leftover)} students for "
                                f"{subj_code} on {date_str} {slot_label}"
                            )
                            self.logger.error(error_msg)
                            raise RuntimeError(
                                "Cannot allocate due to excess number of students across rooms."
                            )

                        for alloc in assignments:
                            for rp in room_pool:
                                if (
                                    rp["room_code"] == alloc["room"]
                                    and rp["building"] == alloc["building"]
                                ):
                                    rp["capacity_effective"] = max(
                                        0,
                                        rp.get("capacity_effective", 0)
                                        - len(alloc["rolls"]),
                                    )
                                    break

                            slot_key = f"{date_str}_{slot_label}"
                            self.allocations[slot_key].append(
                                {
                                    "date": date_str,
                                    "day": day_name,
                                    "slot": slot_label,
                                    "subject": subj_code,
                                    "building": alloc["building"],
                                    "room": alloc["room"],
                                    "rolls": alloc["rolls"],
                                }
                            )

                        try:
                            rows_out = [
                                {
                                    "Room": alloc["room"],
                                    "Rolls (semicolon separated)": ";".join(
                                        alloc["rolls"]
                                    ),
                                    "Count": len(alloc["rolls"]),
                                }
                                for alloc in assignments
                            ]
                            df_sub = pd.DataFrame(rows_out)
                            subject_out = os.path.join(slot_dir, f"{subj_code}.xlsx")
                            df_sub.to_excel(subject_out, index=False)
                        except Exception:
                            self.logger.exception(
                                "Failed to write subject file for %s in %s",
                                subj_code,
                                slot_dir,
                            )

                    self.logger.info(
                        "Allocated slot %s for date %s (subjects: %s)",
                        slot_label,
                        date_str,
                        ",".join(subj_list),
                    )

        except Exception as exc:
            self.logger.exception("Error in allocate_all_days: %s", exc)
            raise

    def write_outputs(self):
        try:
            master_rows = []
            for slot_key, alloc_list in self.allocations.items():
                for alloc in alloc_list:
                    master_rows.append(
                        {
                            "Date": alloc["date"],
                            "Day": alloc.get("day", ""),
                            "course_code": alloc["subject"],
                            "Room": alloc["room"],
                            "Allocated_students_count": len(alloc["rolls"]),
                            "Roll_list (semicolon separated)": ";".join(
                                alloc["rolls"]
                            ),
                        }
                    )

            df_master = pd.DataFrame(master_rows)
            op_overall = os.path.join(
                self.outdir, "op_overall_seating_arrangement.xlsx"
            )
            df_master.to_excel(op_overall, index=False)

            grouped = defaultdict(list)
            for _, alloc_list in self.allocations.items():
                for alloc in alloc_list:
                    key = (str(alloc["date"]), str(alloc["slot"]))
                    grouped[key].append(alloc)

            op_seats = os.path.join(self.outdir, "op_seats_left.xlsx")

            with pd.ExcelWriter(op_seats, engine="xlsxwriter") as writer:
                for (date_str, slot_label), alloc_list in grouped.items():
                    room_allotted = {r["room_code"]: 0 for r in self.room_capacity}
                    for alloc in alloc_list:
                        room_code = alloc["room"]
                        room_allotted[room_code] = room_allotted.get(room_code, 0) + len(
                            alloc["rolls"]
                        )

                    seat_rows = []
                    for room in self.room_capacity:
                        room_code = room["room_code"]
                        capacity = room["capacity"]
                        allotted = room_allotted.get(room_code, 0)
                        vacant = max(0, capacity - allotted)
                        seat_rows.append(
                            {
                                "Room No.": room_code,
                                "Exam Capacity": capacity,
                                "Block": room["building"],
                                "Alloted": allotted,
                                "Vacant (B-C)": vacant,
                            }
                        )

                    df_seats = pd.DataFrame(seat_rows)

                    date_only = str(date_str).split()[0].replace("-", "_").replace("/", "_")
                    sheet_name = f"{date_only}_{slot_label}"
                    for ch in '[]:*?/\\':
                        sheet_name = sheet_name.replace(ch, "_")
                    if len(sheet_name) > 31:
                        sheet_name = sheet_name[:31]

                    df_seats.to_excel(writer, sheet_name=sheet_name, index=False)

            self.logger.info(
                "Output files written: %s and %s", op_overall, op_seats
            )
        except Exception as exc:
            self.logger.exception("Error writing outputs: %s", exc)
            raise

    def generate_attendance_pdfs(self, photos_dir, no_image_icon, pdf_outdir=None):
        if pdf_outdir is None:
            pdf_outdir = os.path.join(self.outdir, "attendance")

        os.makedirs(pdf_outdir, exist_ok=True)

        self.logger.info("Generating attendance PDFs in %s", pdf_outdir)

        grouped = {}
        for _, alloc_list in self.allocations.items():
            for alloc in alloc_list:
                key = (
                    str(alloc["date"]),
                    str(alloc["slot"]),
                    str(alloc["room"]),
                    str(alloc["subject"]),
                )
                grouped.setdefault(key, []).extend(alloc["rolls"])

        def _sanitize_name(name: str) -> str:
            forbidden = '<>:"/\\|?*'
            for ch in forbidden:
                name = name.replace(ch, "_")
            return name.replace(" ", "_")

        for (date_str, slot_label, room_no, subj_code), roll_list in grouped.items():
            unique_rolls = list(dict.fromkeys(roll_list))

            date_only = str(date_str).split()[0]
            date_clean = (
                date_only.replace("-", "_")
                .replace("/", "_")
                .replace(" ", "_")
            )

            fname = f"{date_clean}_{slot_label}_{room_no}_{subj_code}.pdf"
            fname = _sanitize_name(fname)
            out_path = os.path.join(pdf_outdir, fname)

            subject_name = subj_code

            try:
                build_attendance_pdf(
                    out_path=out_path,
                    date_str=date_only,
                    shift=slot_label,
                    room_no=room_no,
                    subject_code=subj_code,
                    subject_name=subject_name,
                    roll_list=unique_rolls,
                    roll_to_name=self.roll_name_map,
                    photos_dir=photos_dir,
                    no_image_icon=no_image_icon,
                    logger=self.logger,
                )
                self.logger.info("Created attendance PDF: %s", out_path)
            except Exception:
                self.logger.error(
                    "Error while generating attendance for %s %s %s %s",
                    date_str,
                    slot_label,
                    room_no,
                    subj_code,
                )
                continue

        self.logger.info("Finished generating all attendance PDFs.")

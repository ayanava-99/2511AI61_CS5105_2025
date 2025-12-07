# streamlit_ui.py
import os
import streamlit as st
import pandas as pd
from io import BytesIO
from datetime import datetime
import logging
from allocation_core import allocate_by_band_with_cycle, compute_faculty_pref_counts_from_df

BASE_DIR = os.getcwd()
OUTPUT_DIR = os.path.join(BASE_DIR, "outputs")
os.makedirs(OUTPUT_DIR, exist_ok=True)
LOG_FILE = os.path.join(OUTPUT_DIR, "allocation.log")

logging.basicConfig(
    filename=LOG_FILE,
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
)
logger = logging.getLogger("streamlit_ui")


def df_to_csv_bytes(df: pd.DataFrame) -> bytes:
    buf = BytesIO()
    df.to_csv(buf, index=False)
    buf.seek(0)
    return buf.getvalue()



st.set_page_config(page_title="Student Allocation System", layout="wide")
st.title("Student Allocation System -- IIT Patna")
st.markdown("Upload your input CSV (Roll, Name, Email, CGPA, then faculty columns with integer ranks).")


for key in ("uploaded_df", "alloc_df", "fac_pref_df", "alloc_ts", "alloc_path", "fac_path"):
    if key not in st.session_state:
        st.session_state[key] = None


uploaded_file = st.file_uploader("Upload CSV", type=["csv"])
if uploaded_file is not None:
    try:
        st.session_state["uploaded_df"] = pd.read_csv(uploaded_file)
        st.toast(f"Loaded input file: {st.session_state['uploaded_df'].shape[0]} rows × {st.session_state['uploaded_df'].shape[1]} cols")
    except Exception as e:
        st.error(f"Error reading uploaded CSV: {e}")
        logger.exception("Error reading uploaded CSV: %s", e)
        st.session_state["uploaded_df"] = None


if st.session_state["uploaded_df"] is not None:
    if st.checkbox("View top 20 records", value=False):
        st.dataframe(st.session_state["uploaded_df"].head(20))


st.subheader("Run Allocation")

col1, col2, col3 = st.columns([1, 1, 1])
with col1:
    run_btn = st.button("Process allocation")
with col2:
    st.empty()
with col3:
    st.empty()

if run_btn and st.session_state["uploaded_df"] is not None:
    try:
        with st.spinner("Allocating..."):
            alloc_df, fac_pref_df, alloc_path, fac_path = allocate_by_band_with_cycle(
                st.session_state["uploaded_df"].copy(), output_dir=OUTPUT_DIR
            )
            ts = datetime.now().strftime("%Y%m%d_%H%M%S")
            st.session_state["alloc_df"] = alloc_df
            st.session_state["fac_pref_df"] = fac_pref_df
            st.session_state["alloc_ts"] = ts
            st.session_state["alloc_path"] = alloc_path
            st.session_state["fac_path"] = fac_path
            st.success("✅ Files generated successfully")
    except Exception as e:
        st.error(f"Allocation failed: {e}")
        logger.exception("Allocation failed: %s", e)


if st.session_state.get("alloc_df") is not None and st.session_state.get("fac_pref_df") is not None:
    alloc_df = st.session_state["alloc_df"]
    fac_pref_df = st.session_state["fac_pref_df"]
    ts = st.session_state.get("alloc_ts") or datetime.now().strftime("%Y%m%d_%H%M%S")
    fac_counts = fac_pref_df.copy()

    
    st.subheader("Allocation (first 10 rows)")
    st.dataframe(alloc_df.head(10))
    st.subheader("Faculty Preference Counts")
    st.dataframe(fac_counts)

   
    col_dl1, col_dl2 = st.columns(2)
    with col_dl1:
        st.download_button(
            "Download allocation CSV",
            data=df_to_csv_bytes(alloc_df),
            file_name=f"output_btp_mtp_allocation_{ts}.csv",
            mime="text/csv",
        )
    with col_dl2:
        st.download_button(
            "Download faculty preference CSV",
            data=df_to_csv_bytes(fac_counts.reset_index()),
            file_name=f"fac_preference_count_{ts}.csv",
            mime="text/csv",
        )

    


st.markdown("---")
st.caption(f"Logs are automatically saved to: `{LOG_FILE}`")


if st.button("Clear outputs"):
    for k in ("alloc_df", "fac_pref_df", "alloc_ts", "alloc_path", "fac_path"):
        st.session_state[k] = None
    st.success("Cleared generated outputs")

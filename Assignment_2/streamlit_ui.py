# streamlit_ui.py
import os
import streamlit as st
import pandas as pd
from io import BytesIO
from datetime import datetime
import logging
from allocation_core import allocate_by_band_with_cycle, compute_faculty_pref_counts_from_df

import tempfile

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
OUTPUT_DIR = os.path.join(tempfile.gettempdir(), "assignment2_outputs")
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



st.set_page_config(page_title="Student Allocation System", layout="wide", page_icon="🎓")

# Sidebar for instructions and sample download
with st.sidebar:
    st.header("ℹ️ Instructions")
    st.markdown("""
    1. **Upload Input**: CSV file with columns: `Roll`, `Name`, `Email`, `CGPA`, followed by Faculty columns (integer ranks).
    2. **Process**: Click 'Process Allocation' to run the algorithm.
    3. **Download**: Get the allocation results and statistics.
    """)
    
    st.markdown("---")
    st.subheader("📂 Sample Data")
    sample_csv_path = os.path.join(BASE_DIR, "input_btp_mtp_allocation.csv")
    if os.path.exists(sample_csv_path):
        with open(sample_csv_path, "rb") as f:
            st.download_button(
                label="📥 Download Sample CSV",
                data=f,
                file_name="sample_input_allocation.csv",
                mime="text/csv",
                help="Use this file structure for your input."
            )

st.title("🎓 Student Allocation System")
st.markdown("### IIT Patna - BTP/MTP Allocation")

# Main Input Section
with st.container():
    st.markdown("#### 1. Upload Data")
    uploaded_file = st.file_uploader("Upload your input CSV file", type=["csv"])

    if uploaded_file is not None:
        try:
            st.session_state["uploaded_df"] = pd.read_csv(uploaded_file)
            st.success(f"✅ Loaded: {st.session_state['uploaded_df'].shape[0]} students")
            
            with st.expander("👀 Preview Input Data"):
                st.dataframe(st.session_state["uploaded_df"].head(10))
                
        except Exception as e:
            st.error(f"❌ Error reading CSV: {e}")
            logger.exception("Error reading uploaded CSV: %s", e)
            st.session_state["uploaded_df"] = None

# Allocation Section
if st.session_state.get("uploaded_df") is not None:
    st.markdown("---")
    st.markdown("#### 2. Run Allocation")
    
    if st.button("🚀 Process Allocation", type="primary"):
        try:
            with st.spinner("🔄 Running allocation algorithm..."):
                alloc_df, fac_pref_df, alloc_path, fac_path = allocate_by_band_with_cycle(
                    st.session_state["uploaded_df"].copy(), output_dir=OUTPUT_DIR
                )
                ts = datetime.now().strftime("%Y%m%d_%H%M%S")
                st.session_state["alloc_df"] = alloc_df
                st.session_state["fac_pref_df"] = fac_pref_df
                st.session_state["alloc_ts"] = ts
                st.session_state["alloc_path"] = alloc_path
                st.session_state["fac_path"] = fac_path
                st.toast("✅ Allocation Completed!", icon="🎉")
        except Exception as e:
            st.error(f"❌ Allocation failed: {e}")
            logger.exception("Allocation failed: %s", e)

# Results Display
if st.session_state.get("alloc_df") is not None:
    st.markdown("---")
    st.markdown("#### 3. Results & Downloads")
    
    alloc_df = st.session_state["alloc_df"]
    fac_pref_df = st.session_state["fac_pref_df"]
    ts = st.session_state.get("alloc_ts") or datetime.now().strftime("%Y%m%d_%H%M%S")
    fac_counts = fac_pref_df.copy()

    tab1, tab2 = st.tabs(["📋 Student Allocation", "📊 Faculty Stats"])
    
    with tab1:
        st.dataframe(alloc_df.head(20), use_container_width=True)
        st.caption("Showing first 20 rows.")
        st.download_button(
            "📥 Download Full Allocation CSV",
            data=df_to_csv_bytes(alloc_df),
            file_name=f"allocation_results_{ts}.csv",
            mime="text/csv",
            type="primary"
        )
        
    with tab2:
        st.dataframe(fac_counts, use_container_width=True)
        st.download_button(
            "📥 Download Faculty Stats CSV",
            data=df_to_csv_bytes(fac_counts.reset_index()),
            file_name=f"faculty_stats_{ts}.csv",
            mime="text/csv",
        )

    if st.button("🔄 Clear Results"):
        for k in ("alloc_df", "fac_pref_df", "alloc_ts", "alloc_path", "fac_path"):
            st.session_state[k] = None
        st.rerun()

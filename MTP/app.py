import streamlit as st
import tempfile
import os
from pathlib import Path
import datetime
import shutil
import base64
import textwrap
import pandas as pd

from src.seating_allocator import SeatingAllocator
from src.logger_setup import setup_logging

# Get the directory where this script is located
SCRIPT_DIR = Path(__file__).parent.resolve()

def load_image_base64(path: str):
    if not os.path.exists(path):
        return None
    with open(path, "rb") as f:
        return base64.b64encode(f.read()).decode()

# Use absolute paths relative to the script location
crest_b64 = load_image_base64(str(SCRIPT_DIR / "assets" / "images" / "iitp_crest.png"))
full_logo_b64 = load_image_base64(str(SCRIPT_DIR / "assets" / "images" / "iitp_full_logo.png"))

def run_allocation(uploaded_file, buffer, density):
    with tempfile.TemporaryDirectory() as tmpdir:
        excel_path = os.path.join(tmpdir, uploaded_file.name)
        with open(excel_path, "wb") as f:
            f.write(uploaded_file.getbuffer())

        outdir = os.path.join(tmpdir, "output")
        os.makedirs(outdir, exist_ok=True)

        logger = setup_logging(
            logfile=os.path.join(outdir, "seating.log"),
            errorfile=os.path.join(outdir, "errors.txt"),
        )

        alloc = SeatingAllocator(
            input_file=excel_path,
            buffer=buffer,
            density=density,
            outdir=outdir,
            logger=logger,
        )
        alloc.load_inputs()
        alloc.allocate_all_days()
        alloc.write_outputs()

        photos_dir = str(SCRIPT_DIR / "assets" / "photos")
        no_image_icon = os.path.join(photos_dir, "no_image_available.jpg")
        alloc.generate_attendance_pdfs(photos_dir, no_image_icon)

        zip_base = os.path.join(tmpdir, "attendance_output")
        shutil.make_archive(zip_base, "zip", outdir)
        zip_path = zip_base + ".zip"

        with open(zip_path, "rb") as f:
            zip_bytes = f.read()

        close_logger(logger)
        return zip_bytes


st.set_page_config(
    page_title="IIT Patna Exam Seating & Attendance Generator",
    page_icon="🎓",
    layout="centered",
)

def close_logger(logger):
    if logger is None:
        return
    for h in list(logger.handlers):
        try:
            h.flush()
        except Exception:
            pass
        try:
            h.close()
        except Exception:
            pass
        logger.removeHandler(h)





st.markdown(
    """
    <style>
    .stApp {
        background: linear-gradient(135deg, #003366 0%, #ffffff 40%, #FFD700 100%);
        background-attachment: fixed;
    }
    .block-container {
        background-color: #ffffff;
        border-radius: 32px;
        padding: 2rem 2.2rem;
        margin-top: 1.5rem;
        box-shadow: 0 10px 25px rgba(0, 0, 0, 0.25);
        border: 2px solid #FFD700;
    }
    .iitp-header {
        background-color: #003366;
        padding: 1.2rem 1.5rem;
        border-radius: 0 0 18px 18px;
        box-shadow: 0 4px 18px rgba(0,0,0,0.4);
        text-align: center;
    }
    .iitp-header-title {
        color: #ffffff !important;
        font-size: 1.5rem;
        font-weight: 700;
        margin-bottom: 0.25rem;
    }
    .iitp-header-subtitle {
        color: #FFD700 !important;
        font-size: 0.90rem;
        font-weight: 600;
        margin-top: 0;
    }
    .iitp-footer {
        margin-top: 2.5rem;
        padding-top: 0.8rem;
        border-top: 1px solid #CCCCCC;
        text-align: center;
        font-size: 0.8rem;
        color: #003366 !important;
    }
    body, .stApp, .block-container,
    div[data-testid="stMarkdownContainer"] h1,
    div[data-testid="stMarkdownContainer"] h2,
    div[data-testid="stMarkdownContainer"] h3,
    div[data-testid="stMarkdownContainer"] p,
    label, span, p {
        color: #003366 !important;
        opacity: 1 !important;
    }
    div[data-testid="stFileUploader"] {
        background-color: #f4f6fb !important;
        border-radius: 12px;
        padding: 1rem;
        border: 1px solid #d0d4e4;
    }
    div[data-testid="stFileUploader"] section {
        background-color: #ffffff !important;
        border-radius: 10px;
        border: 2px dashed #003366 !important;
        color: #003366 !important;
    }
    div[data-testid="stFileUploader"] section * {
        color: #003366 !important;
        opacity: 1 !important;
    }
    .stSelectbox div[data-baseweb="select"] > div {
        background-color: #ffffff !important;
        color: #003366 !important;
        border-radius: 8px !important;
    }
    .stSlider label {
        color: #003366 !important;
        font-weight: 600 !important;
    }
    .stButton>button {
        background-color: #003366 !important;
        color: #ffffff !important;
        border-radius: 16px;
        padding: 0.9rem 1.2rem;
        font-size: 1rem;
        font-weight: 600;
        border: 2px solid #FFD700;
    }
    .stButton>button * {
        color: #ffffff !important;
    }
    .stButton>button:hover {
        background-color: #FFD700 !important;
        color: #003366 !important;
    }
    </style>
    """,
    unsafe_allow_html=True,
)

header_html = textwrap.dedent(f"""
<div class="iitp-header">
    {f'<img src="data:image/png;base64,{crest_b64}" alt="IIT Patna Crest" style="height:70px; margin-bottom:6px;" />' if crest_b64 else ''}
    <div class="iitp-header-title">Indian Institute of Technology Patna</div>
    <div class="iitp-header-subtitle">Exam Seating & Attendance Generator</div>
</div>
""")
st.markdown(header_html, unsafe_allow_html=True)
st.write("")

tab_generate, tab_attendance, tab_video = st.tabs(
    ["🧮 Generate Seating & Attendance", "📂 Download Attendance Sheets", "📺 Project Video"]
)


with tab_generate:
    st.subheader("📄 Upload Input Excel File")
    st.markdown(
        "Upload the **exam input Excel (.xlsx)** file in the required format to generate "
        "seating arrangements and attendance sheets."
    )

    sample_file_path = SCRIPT_DIR / "sample_inputs" / "input_data_tt.xlsx"
    if sample_file_path.exists():
        with open(sample_file_path, "rb") as f:
            st.download_button(
                label="📥 Download Sample Input File",
                data=f,
                file_name="sample_input.xlsx",
                mime="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
                help="Download a sample Excel file to see the expected format."
            )
    else:
        st.warning("Sample input file not found.")

    uploaded = st.file_uploader("Choose an Excel file", type=["xlsx"], key="input_excel")

    col1, col2 = st.columns(2)
    with col1:
        buffer = st.slider(
            "Buffer seats per room",
            min_value=0,
            max_value=50,
            value=5,
            step=1,
            help="Empty buffer seats to leave per room.",
        )

    with col2:
        density = st.selectbox(
            "Seating density",
            ["Dense", "Sparse"],
            help="Choose 'Dense' for maximum utilization and 'Sparse' for spaced seating.",
        )

    st.markdown("---")

    generate = st.button("🚀 Generate Seating Arrangement", use_container_width=True)

    if generate:
        if not uploaded:
            st.warning("⚠️ Please upload an Excel file before generating.")
        else:
            with st.spinner("⏳ Running allocation pipeline..."):
                try:
                    zip_bytes = run_allocation(uploaded, buffer, density)
                    st.success("✅ Seating and attendance files generated successfully!")
                    st.download_button(
                        "📥 Download Output ZIP",
                        data=zip_bytes,
                        file_name="attendance_output.zip",
                        mime="application/zip",
                        use_container_width=True,
                    )
                    st.balloons()
                except Exception as e:
                    st.error(f"❌ An error occurred while generating output: **{e}**")


with tab_attendance:
    st.subheader("📂 Find Attendance PDF")

    st.markdown(
        "- Upload the generated **`op_overall_seating_arrangement.xlsx`** file.\n"
        "- Provide the path to the **attendance PDFs folder**.\n"
        "- Enter **room number** and **exam date**.\n"
        "- The app will show **Morning** and **Evening** shifts separately for that room & date,\n"
        "  with separate download buttons for each subject code where a PDF exists."
    )

    overall_file = st.file_uploader(
        "Upload `op_overall_seating_arrangement.xlsx`",
        type=["xlsx"],
        key="overall_excel",
    )

    attendance_dir = st.text_input(
        "Path to attendance folder (containing PDFs like `2016_04_30_Morning_10502_CB204.pdf`)",
        value=r"C:\Users\ayana\OneDrive\Desktop\attendance_output\attendance",
        help="This should be the directory where all attendance PDFs are stored on the server/machine running this app.",
    )

    room_no = st.text_input("Room number", value=10502)

    # --Dynamic date range
    min_date = datetime.date(2000, 1, 1)
    max_date = datetime.date.today()
    default_date = datetime.date.today()

    if overall_file is not None:
        try:
            df_dates = pd.read_excel(overall_file, usecols=["Date"])
            date_series = pd.to_datetime(df_dates["Date"], errors="coerce").dt.date
            date_series = date_series.dropna()

            if not date_series.empty:
                min_date = date_series.min()
                max_date = date_series.max()
                default_date = min_date
        except Exception:
            
            pass

    exam_date = st.date_input(
        "Exam date(dynamic to input `.xlsx` file)",
        value=default_date,
        min_value=min_date,
        max_value=max_date,
    )

    search = st.button("🔍 Search Attendance Sheets", use_container_width=True)

    if search:
        if overall_file is None:
            st.warning("⚠️ Please upload `op_overall_seating_arrangement.xlsx`.")
        elif not attendance_dir or not os.path.isdir(attendance_dir):
            st.warning("⚠️ Please provide a valid path to the attendance PDFs folder.")
        elif not room_no.strip():
            st.warning("⚠️ Please enter a room number.")
        else:
            try:
                df_overall = pd.read_excel(overall_file)

                df_overall["Date_only"] = pd.to_datetime(
                    df_overall["Date"], errors="coerce"
                ).dt.date

                mask = (
                    (df_overall["Date_only"] == exam_date)
                    & (df_overall["Room"].astype(str).str.strip() == str(room_no).strip())
                )
                df_filtered = df_overall.loc[mask]

                if df_filtered.empty:
                    st.error(
                        "No exams found for the given room and date in the uploaded Excel file."
                    )
                else:
                    subject_codes = sorted(
                        df_filtered["course_code"].astype(str).str.strip().unique()
                    )

                    st.success(
                        f"Found {len(subject_codes)} subject(s) scheduled in room {room_no} on {exam_date}."
                    )
                    st.write("**Subject codes (both shifts combined):** ", ", ".join(subject_codes))

                    date_str_for_filename = exam_date.strftime("%Y_%m_%d")
                    shifts = ["Morning", "Evening"]

                    overall_any_pdf = False

                    for shift_label in shifts:
                        st.markdown(f"### 🕒 {shift_label} shift")

                        found_in_this_shift = False

                        for subj in subject_codes:
                            expected_name = f"{date_str_for_filename}_{shift_label}_{room_no}_{subj}.pdf"
                            full_path = os.path.join(attendance_dir, expected_name)

                            if os.path.exists(full_path):
                                found_in_this_shift = True
                                overall_any_pdf = True
                                with open(full_path, "rb") as f:
                                    pdf_bytes = f.read()
                                st.download_button(
                                    label=f"📥 Download {subj} ({shift_label}, Room {room_no})",
                                    data=pdf_bytes,
                                    file_name=expected_name,
                                    mime="application/pdf",
                                    use_container_width=True,
                                )

                        if not found_in_this_shift:
                            st.info(
                                f"No attendance PDFs found in folder `{attendance_dir}` "
                                f"for **{shift_label}** shift in room **{room_no}** on **{exam_date}**."
                            )

                    if not overall_any_pdf:
                        st.warning(
                            "No matching attendance PDFs were found in the given folder "
                            "for this room and date in either shift."
                        )

            except Exception as e:
                st.error(f"❌ Error while searching attendance PDFs: **{e}**")

footer_html = textwrap.dedent(f"""
<div class="iitp-footer">
    {f'<img src="data:image/png;base64,{full_logo_b64}" alt="IIT Patna Logo" style="height:50px; margin-bottom:4px;" />' if full_logo_b64 else ''}
    <span>Developed for IIT Patna · © 2025</span>
</div>
""")
st.markdown(footer_html, unsafe_allow_html=True)


with tab_video:
    st.subheader('?? Project Explanation')
    st.markdown('Watch this video to understand how the Exam Seating & Attendance Generator works:')
    st.video('https://youtu.be/apRsykyDjLM')


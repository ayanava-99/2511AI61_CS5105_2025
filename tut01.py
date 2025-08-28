import streamlit as st
import pandas as pd
import os
import time
import glob
from Assignment1 import save_branchwise
from Assignment1 import shullfe_records
from Assignment1 import generate_summary

st.set_page_config("Shuffle App| assignment 1")


if "page" not in st.session_state:
    st.session_state["page"] = "Home"



def home_page():
    
    st.markdown("<h1 style='text-align: center; color:#f44336;'>🎲 Shuffle App 🎲</h1>", unsafe_allow_html=True)
    st.markdown("<h3 style='text-align: center; color:gray;'>Create randomized student groups</h3>", unsafe_allow_html=True)

    st.markdown(""" <br>
                    <br>
                """, unsafe_allow_html=True)
    
    st.markdown("""    
        <h4> How To Execute:</h4>
        <ol>
            <li>Upload Excel File</li>
            <li>Choose the type of grouping</li>
            <li>Execute and save the groups to CSV files</li>
            <li>Generate Summary of Mix</li>
        </ol>
    """, unsafe_allow_html=True)

    st.markdown(""" <br>
                    <br>
                """, unsafe_allow_html=True)

    if st.button("Proceed to Upload File", use_container_width=True):
        st.session_state["page"] = "upload"



def file_upload_util():
    st.markdown("<h1 style='text-align: center; color:#f44336;'>Upload Excel File</h1>", unsafe_allow_html=True)

    uploaded_file = st.file_uploader(
        "Upload Excel files ", 
        type=["xlsx"], 
        accept_multiple_files=False
    )
    col1, col2, col3, col4, col5 = st.columns([2, 1, 1, 1, 2])
    with col1:
        if st.button("Home"):
            st.session_state["page"] = "Home"

    if uploaded_file:     
        st.success("File Uploaded!")
        try:
            read_dataframe=pd.read_excel(uploaded_file)
            st.session_state["df"] = read_dataframe
            

            with col5:
                if st.button(f"Proceed with Mix"):
                    st.session_state["page"] = "grouping"


        except Exception as e:
            st.exception(e)






def grouping_ui():
    st.title("Welcome to student Group Generator")

    if "df" not in st.session_state:
        st.warning("Please re-upload files first.")
        if st.button("Back to Upload"):
            st.session_state["page"] = "upload"
        return

    df = st.session_state["df"]

    output_path=st.text_input("Output Files will be saved at:-", os.getcwd())
    st.session_state["out_loc"]=output_path

    col1, col2, col3= st.columns([2, 1, 2])
    with col2:
        if st.button("Branchwise Full-List"):
            try:
                with st.spinner('Grouping Branchwise....',width='stretch'):
                    time.sleep(2)
                    save_branchwise(df,output_path)
                    st.toast("Task Completed")
                    time.sleep(1)
                    
                st.success("Files Saved")
                
            except Exception as e:
                st.exception(e)
            

    st.header("Enter number of students per group")
    group_size = st.number_input(f"Drag the slider to choose a number between 1 to {len(df)})",min_value=1,max_value=len(df),value=14)
    
    col21, col22, col23, col24= st.columns([2, 1, 1, 2])
    with col21:
        if st.button("Branch wise Mix"):
            try:
                with st.spinner("Sit tight, creating Branch-wise mix...."):
                    time.sleep(2)
                    shullfe_records(df,'branch_wise',group_size,output_path)
                    st.toast("Task Completed")
                    time.sleep(2)
                st.success("Files Saved")
            except Exception as e:
                st.exception(e)
    
    with col24:
        if st.button("Uniform mix"):
            try:
                with st.spinner('Sit tight, creating uniform mix...'):
                    time.sleep(3)
                    shullfe_records(df,'uniform',group_size,output_path)
                    st.toast("Task Completed")
                    time.sleep(2)
                st.success("Files Saved")
            except Exception as e:
                st.exception(e)

    if st.button("Back to Upload"):
        st.session_state["page"] = "upload"

    
    col31, col32, col33, col34= st.columns([2, 1, 1, 2])
    with col31:
        if st.button("Re-Upload files"):
            st.session_state["page"] = "upload"
    with col34:
        if st.button("Generate Summary"):
            st.session_state["page"] = "Summary"


def generate_summary_files():

    st.title("Generate Summary Files!")
    root=st.session_state["out_loc"]
    group_folders=['branch_wise','uniform']

    if "out_loc" not in st.session_state or not all(os.path.exists(os.path.join(root, folder)) for folder in group_folders):
        st.warning("Please generate group wise files first.")
        if st.button("Back to Grouping"):
            st.session_state["page"] = "grouping"
        return
    
    time.sleep(2)
    col1, col2, col3 = st.columns([2, 1, 2])
    with col1:
        if st.button("Generate Summary"):
            try:
                with st.spinner("creating consolidated files..."):
                    time.sleep(3)
                    generate_summary(root,group_folders)
                    time.sleep(1)
                st.success("Summary has been generted")

            except Exception as e:
                st.exception(e)
    with col3:
        summary_path=os.path.join(root,'Summary')
        if os.path.exists(summary_path):
            st.session_state["summary_file"] = summary_path
            if st.button("View Summary file"):
                st.session_state["page"] = "view_summary"
    if st.button("Back"):
        st.session_state["page"] = "grouping"

def view_summary():
    st.title("Summary Viewer")
    summary_path=st.session_state["summary_file"]
    try:
        get_summary_csv = glob.glob(f"{summary_path}/*.csv")
        #st.write(get_summary_csv)
        st.dataframe(pd.read_csv(get_summary_csv[0]))

    except Exception as e:
        st.exception(e)
    if st.button("Home"):
        st.session_state["page"] = "Home"
    if st.button("Back"):
        st.session_state["page"] = "Summary"


if st.session_state["page"] == "Home":
    home_page()
elif st.session_state["page"] == "upload":
    file_upload_util()
elif st.session_state["page"] == "grouping":
    grouping_ui()
elif st.session_state['page']=="Summary":
    generate_summary_files()
elif st.session_state['page']=="view_summary":
    view_summary()






# 🎓IIT Patna Exam Seating & Attendance Generator [LINK](https://seating-attendance-iitp.streamlit.app/)

**An intelligent, end-to-end exam management system that automates seating arrangements, clash detection, and attendance PDF generation.**

**[📺 Watch Project Explanation Video](https://youtu.be/apRsykyDjLM)**

---

## 🎯 Overview

This is a **comprehensive exam management solution** designed for educational institutions (especially IIT Patna) to efficiently manage large-scale examinations. The system automates:

✅ **Seating Allocation** - Intelligent room assignment based on room capacities and exam timetable  
✅ **Clash Detection** - Ensures no student appears in multiple exams simultaneously  
✅ **Attendance Generation** - Professional PDF sheets with student photos and signature fields  
✅ **Smart Avatar Fetching** - Automatically fetches student avatars from DiceBear API if photos are completely missing  
✅ **Report Generation** - Excel sheets with seating summaries and vacancy tracking  
✅ **Web Interface** - User-friendly Streamlit UI for non-technical users  
✅ **Docker Support** - One-click deployment on any system  

---

## 🚀 Key Features

### 1. **Single Excel Input File**
All exam data in one place:
- Exam timetable (dates, time slots, courses)
- Student roll-to-name mapping
- Course-to-roll mapping
- Room capacity and block information

### 2. **Intelligent Clash Detection**
- Validates that no student is scheduled for two exams in the same time slot
- Provides detailed error logs identifying conflicts
- Prevents invalid allocations before processing

### 3. **Smart Seating Allocation Algorithm**
```
Priority-based allocation using:
├── Sort subjects by student count (descending)
├── Allocate rooms based on effective capacity
├── Apply buffer seats (social distancing)
├── Density modes: Dense (100% capacity) or Sparse (50% capacity)
└── Optimize room utilization
```

### 4. **Attendance PDF Generation with Smart Avatars**
Each room-wise attendance sheet includes:
- Student name and roll number
- Student photograph (from `assets/photos/` folder)
- **Auto-Fetch Feature**: If a student's photo is missing, the system automatically fetches a deterministic avatar from the DiceBear API based on their roll number.
- Signature field for each student
- Exam metadata (date, subject, room, shift)
- Institution header with IITP branding

### 5. **Output Files**
- **Date-wise folders**: Organized by exam dates
- **Shift-wise subdirectories**: Morning and Evening exams
- **Subject Excel files**: Student allocation per subject
- **Attendance PDFs**: Room-wise attendance sheets
- **Summary reports**: Overall seating arrangement and vacancy analysis
- **Log files**: Detailed execution logs for debugging

### 6. **Streamlit Web Interface**
- Intuitive upload interface
- Real-time parameter adjustment
- One-click processing
- Automatic ZIP file generation for download
- Search and view attendance reports by room and date
- **Project Video Tab**: Integrated video explanation of the project

### 7. **Docker Containerization**
- Deploy without environment setup
- Consistent across all platforms
- Production-ready configuration

---


## 📁 Project Structure

```
MTP/
├── app.py                        # Streamlit web interface
├── main.py                       # CLI entry point
├── Dockerfile                    # Docker configuration
├── .dockerignore                 # Docker ignore rules
├── requirements.txt              # Python dependencies
├── README.md                     # Project documentation
│
├── src/                          # Source code modules
│   ├── seating_allocator.py      # Core seating logic
│   ├── attendance_pdf.py         # PDF generation logic
│   ├── avatar_fetcher.py         # [NEW] API integration for avatars
│   ├── io_utils.py               # File I/O utilities
│   ├── logger_setup.py           # Logging setup
│   └── config.py                 # Configuration
│
├── assets/                       # Static assets
│   ├── images/
│   │   ├── iitp_crest.png        # Institution crest
│   │   └── iitp_full_logo.png    # Institution logo
│   └── photos/                   # Student photographs
│       ├── <roll_number>.jpg     # e.g., B210001.jpg
│       └── no_image_available.jpg # Fallback image
│
├── sample_input/                 # Example input Excel file
│   └── sample_timetable.xlsx     # Template with required sheets
│
└── output/                       # Generated outputs (created at runtime)
    ├── <date>/                   # Date-wise organization
    │   ├── Morning/
    │   │   ├── <course_code>.xlsx
    │   │   └── ...
    │   ├── Evening/
    │   │   ├── <course_code>.xlsx
    │   │   └── ...
    │   └── ...
    ├── attendance/               # Generated PDFs
    │   ├── <date>_Morning_<room>_<course>.pdf
    │   └── ...
    ├── op_overall_seating_arrangement.xlsx
    ├── op_seats_left.xlsx
    ├── seating.log               # Execution logs
    └── errors.txt                # Error details
```

---

## 📥 Input Format

### Required Excel Sheets

Your input Excel file must contain the following sheets:

#### 1. **in_timetable**
Exam schedule for all days and time slots.

| Date | Day | Morning | Evening |
|------|-----|---------|---------|
| 2025-01-10 | Friday | CS101;CS102 | NO EXAM |
| 2025-01-11 | Saturday | CS201 | CS301;CS302 |

- **Date**: Exam date (YYYY-MM-DD format)
- **Day**: Day of week
- **Morning/Evening**: Semicolon-separated course codes (or "NO EXAM")

#### 2. **in_course_roll_mapping**
Links which students take which courses.

| RollNo | Course_Code |
|--------|-------------|
| B210001 | CS101 |
| B210002 | CS101 |
| B210001 | CS102 |

- **RollNo**: Student roll number
- **Course_Code**: Subject code

#### 3. **in_roll_name_mapping** (Optional)
Student roll number to name mapping.

| Roll | Name |
|------|------|
| B210001 | Aayan Verma |
| B210002 | Priya Singh |

- **Roll**: Student roll number
- **Name**: Student name (appears on attendance PDFs)

#### 4. **in_room_capacity**
Available exam halls and their capacities.

| Room No. | Exam Capacity | Block |
|----------|---------------|-------|
| 6101 | 50 | B1 |
| 10502 | 60 | B2 |
| AUD1 | 200 | Auditorium |

- **Room No.**: Room identifier
- **Exam Capacity**: Seating capacity
- **Block**: Building/block name

---

## ⚡ Quick Start

### 1. **Prepare Your Input File**
Create an Excel file with the 4 sheets described above. Use `sample_input/sample_timetable.xlsx` as a template.

### 2. **Prepare Student Photos** (Optional)
Place student photos in the `assets/photos/` folder:
```
assets/photos/
├── B210001.jpg
├── B210002.jpg
└── no_image_available.jpg  # Fallback image
```
*Note: If a photo is missing, the system will try to fetch a random avatar from the web.*

### 3. **Run the Web App**
```bash
streamlit run app.py
```

### 4. **Upload & Process**
- Upload your Excel file in the UI
- Adjust buffer seats (social distancing requirement)
- Select density mode (Dense/Sparse)
- Click "Process" and download the ZIP

### 5. **Extract Outputs**
- Attendance PDFs ready for printing
- Excel reports for administrators
- Logs for troubleshooting

---

## 💾 Installation

### Prerequisites
- Python 3.8 or higher
- pip (Python package manager)

### Step 1: Clone Repository
```bash
git clone <repository_url>
cd MTP
```

### Step 2: Install Dependencies
```bash
pip install -r requirements.txt
```

**Required Packages:**
```
streamlit          # Web UI framework
pandas             # Data processing
reportlab          # PDF generation
openpyxl           # Excel file handling
xlsxwriter         # Excel writing
Pillow             # Image processing
requests           # API calls for avatars
```

---

## 🎮 Execution Guide

### **Method 1: Web Interface **

```bash
streamlit run app.py
```

**Steps:**
1. Open `http://localhost:8501` in browser
2. Upload your Excel input file
3. Set parameters:
    - **Buffer Seats**: Seats to reserve per room (e.g., 0, 2, 5)
    - **Density Mode**: Dense (full capacity) or Sparse (50% capacity)
4. Click "Generate Seating & Attendance"
5. Download ZIP file with all outputs


### **Method 2: Docker**

```bash
# Build image
docker build -t seating-app .

# Run container
docker run -p 8501:8501 seating-app
```

Access at `http://localhost:8501`

---

## 📝 License

This project is part of an MTech thesis at **Indian Institute of Technology Patna**.

---

## 👤 Author

**Ayanava Dutta**  
M.Tech, Computer Science & Engineering  
Indian Institute of Technology Patna  
CS5105 - Computing Lab (2025)

---

**Last Updated**: February 2026  
**Version**: 1.1 (Reorganized structure & Avatar API Integration)

# 🎓IIT Patna Exam Seating & Attendance Generator

**An intelligent, end-to-end exam management system that automates seating arrangements, clash detection, and attendance PDF generation.**

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Input Format](#input-format)
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Usage Guide](#usage-guide)
- [Configuration](#configuration)
- [Output Files](#output-files)
- [Technical Details](#technical-details)
- [Troubleshooting](#troubleshooting)
- [Author & License](#author--license)

---

## 🎯 Overview

This is a **comprehensive exam management solution** designed for educational institutions (especially IIT Patna) to efficiently manage large-scale examinations. The system automates:

✅ **Seating Allocation** - Intelligent room assignment based on room capacities and exam timetable  
✅ **Clash Detection** - Ensures no student appears in multiple exams simultaneously  
✅ **Attendance Generation** - Professional PDF sheets with student photos and signature fields  
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

### 4. **Attendance PDF Generation**
Each room-wise attendance sheet includes:
- Student name and roll number
- Student photograph (from `photos/` folder)
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
- Search and view attendance reports by room and date **(additional feature)**

### 7. **Docker Containerization**
- Deploy without environment setup
- Consistent across all platforms
- Production-ready configuration

---


## 📁 Project Structure

```
MTP/
├── app.py                        # Streamlit web interface
├── seating_allocator.py          # Core seating logic
├── attendance_pdf.py             # PDF generation module
├── main.py                       # CLI entry point
├── config.py                     # Configuration (rooms, adjacency)
├── logger_setup.py               # Logging configuration
├── io_utils.py                   # File I/O utilities
├── requirements.txt              # Python dependencies
├── Dockerfile                    # Docker configuration
├── .dockerignore                 # Docker ignore rules
│
├── iitp_crest.jpg                # Institution logo (small)
├── iitp_full_logo.jpg            # Institution logo (full)
│
├── photos/                       # Student photographs
│   ├── <roll_number>.jpg         # e.g., B210001.jpg
│   ├── <roll_number>.jpg
│   └── no_image_available.jpg    # Fallback image
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
Place student photos in the `photos/` folder:
```
photos/
├── B210001.jpg
├── B210002.jpg
└── no_image_available.jpg  # Fallback image
```

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
```

### Step 3: Prepare Resources
- Add student photos to `photos/` folder (naming: `<rollno>.jpg`)
- Place institution logos as `iitp_crest.jpg` and `iitp_full_logo.jpg`

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

**Update these if using different rooms.**

### Buffer Seats
- **What**: Seats reserved between students for social distancing
- **Usage**: `--buffer 2` reserves 2 seats per room
- **Effect**: Reduces effective capacity

### Density Modes
- **Dense**: Uses full room capacity (100%)
- **Sparse**: Uses 50% of room capacity
- **Use case**: Sparse for large-scale exams or social distancing requirements

---

## 📊 Output Files

### Generated Outputs

#### 1. **Attendance PDFs**
```
attendance/
├── 2025_01_10_Morning_6101_CS101.pdf
├── 2025_01_10_Morning_6102_CS102.pdf
├── 2025_01_10_Evening_10502_CS201.pdf
└── ...
```
**Contains:** Student photos, names, roll numbers, signature fields

#### 2. **Seating Arrangement Excel**
**File**: `op_overall_seating_arrangement.xlsx`

| Date | Day | Course_Code | Room | Allocated_Students_Count | Roll_List |
|------|-----|-------------|------|--------------------------|-----------|
| 2025-01-10 | Friday | CS101 | 6101 | 25 | B210001;B210002;... |

#### 3. **Vacancy Report**
**File**: `op_seats_left.xlsx`

Multiple sheets (one per date-slot combination):

| Room No. | Exam Capacity | Block | Alloted | Vacant |
|----------|---------------|-------|--------|--------|
| 6101 | 50 | B1 | 25 | 25 |
| 10502 | 60 | B2 | 45 | 15 |

#### 4. **Subject-wise Allocation** (per date/slot)
```
output/2025_01_10/Morning/
├── CS101.xlsx    # Students allocated to CS101
├── CS102.xlsx    # Students allocated to CS102
└── ...
```

#### 5. **Log Files**
- **seating.log**: Detailed execution logs
- **errors.txt**: All errors and warnings

---



### Check Logs

```bash
cat output/app.log
cat output/app_errors.txt
```


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

**Last Updated**: December 2025  
**Version**: 1.0  

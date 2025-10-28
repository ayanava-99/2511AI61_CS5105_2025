# 🧮 Student Allocation App  **[{LIVE🌐}](https://studentallocationapp.streamlit.app/)**

A dynamic **BTP/MTP Student–Faculty Allocation System** built using **Python** and **Streamlit**, supporting both local and Docker-based execution.  
It performs **banded, mod-n allocation** based on CGPA and faculty preferences, generating two CSV outputs:
- **Allocation file** (`output_btp_mtp_allocation_*.csv`)
- **Faculty preference count file** (`fac_preference_count_*.csv`)

---


## 📁 Folder Structure

```
project-root/
├── allocation_core.py        # Core allocation and faculty preference logic
├── streamlit_ui.py           # Streamlit web interface (imports from core)
├── requirements.txt          # Dependencies
├── Dockerfile                # Container setup for Streamlit
├── docker-compose.yml        # For quick deployment
├── outputs/                  # Auto-created for logs and generated CSVs
└── README.md                 # This file
```

---

## ⚙️ Installation & Setup

### 🧩 Prerequisites
- Python **3.9+**
- (Optional) Docker & Docker Compose

---

### 💻 Run Locally

```bash
# 1. Clone the repository
git clone https://github.com/<your-username>/student-allocation-app.git
cd student-allocation-app

# 2. Install dependencies
pip install -r requirements.txt

# 3. Start the Streamlit app
streamlit run streamlit_ui.py
```

Then open your browser and visit:  
👉 [http://localhost:8501](http://localhost:8501)

---

### 🐳 Run with Docker

```bash
# Build and start the container
docker-compose up --build
```

Then visit:  
👉 [http://localhost:8501](http://localhost:8501)

---

## 🧠 How It Works

### 🧾 1. Input Format
Upload a CSV file in this format:

| Roll | Name | Email | CGPA | FAC1 | FAC2 | FAC3 | ... |
|------|------|--------|------|------|------|------|-----|
| 1001 | Alice | alice@xyz.edu | 9.2 | 1 | 3 | 2 | ... |
| 1002 | Bob   | bob@xyz.edu   | 8.7 | 2 | 1 | 3 | ... |

> Each faculty column (FAC1, FAC2, etc.) should contain numeric preferences (1 = first choice, 2 = second choice, ...).

---

### ⚙️ 2. Processing Logic

1. Sort students by **CGPA** (descending).  
2. Divide students into **bands = number of faculties**.  
3. Allocate one student per faculty per cycle (using mod-n round robin).  
4. Continue until all students are allocated.  
5. If students > faculties × bands, remaining students are distributed evenly.

---

### 📊 3. Outputs

Two files are generated automatically inside `/outputs`:

| File | Description |
|------|--------------|
| **output_btp_mtp_allocation_YYYYMMDD_HHMMSS.csv** | Student–Faculty allocation |
| **fac_preference_count_YYYYMMDD_HHMMSS.csv** | Faculty preference count statistics |

Both files can be downloaded directly from the Streamlit UI.

---

## 🧾 Logs

All logs are automatically saved to:
```
outputs/allocation.log
```

Each log entry includes timestamps, cycle counts, assignments, and errors (if any).

---


## 🧑‍💻 Development Notes

- Modular design — `allocation_core.py` can be imported independently.  
- Streamlit UI handles uploads, processing, and file downloads.  
- Dockerized for consistent deployment.  
- Logs are persistent across restarts.

---

## 🧹 Example Output Folder

After a successful run, your folder will look like:

```
outputs/
├── allocation.log
├── output_btp_mtp_allocation_20251027_142210.csv
└── fac_preference_count_20251027_142210.csv
```


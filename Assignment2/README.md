# Student Allocation App

### Folder Structure
```
project-root/
├─ allocation_core.py        # main allocation logic (your current code)
├─ streamlit_ui.py          # Streamlit UI (imports functions from core)
├─ requirements.txt
├─ Dockerfile
├─ docker-compose.yml
└─ outputs/                 # created automatically for logs and CSV outputs
```

### Run Locally
```bash
pip install -r requirements.txt
streamlit run streamlit_ui.py
```
Visit: http://localhost:8501

### Run with Docker
```bash
docker-compose up --build
```
Visit: http://localhost:8501

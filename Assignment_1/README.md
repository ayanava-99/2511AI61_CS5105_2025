# 🎲 Shuffle App  

A Streamlit-based application to **randomize student groups** from branch-wise Excel files.  
It supports multiple grouping strategies (branch-wise, uniform mix) and generates summaries of the groups.  

---

## 📂 Project Structure  

```
ShuffleApp/
│── tut01.py              # Streamlit UI (main app entry point)
│── Assignment1.py        # Core functions (grouping, shuffling, summary)
│── requirements.txt      # Dependencies
│── README.md             # Documentation
│── input/                # Place input Excel files here
│── output/               # Generated output files
    │── branch_wise/      # Branch-wise grouped output
    │── uniform/          # Uniformly mixed groups
    │── Summary/          # Consolidated summary CSVs
```

---

## ⚙️ Installation & Setup  

### 1. Clone the Repository  
```bash
git clone https://github.com/ayanava-99/2511AI61_CS5105_2025.git
cd 2511AI61_CS5105_2025
```


### 2. Create a Virtual Environment  
Using **venv**:  
```bash
python -m venv venv
```

Activate it:  
- Windows:
  ```bash
  venv\Scripts\activate
  ```
- Linux/Mac:
  ```bash
  source venv/bin/activate
  ```

### 3. Install Dependencies  
```bash
pip install -r requirements.txt
```

---

## ▶️ Running the Application  

Run the Streamlit app with:  
```bash
streamlit run tut01.py
```

Then open the link in your browser (default: `http://localhost:8501`).

---

## 📘 How to Use  

1. **Upload Input File**  
   - Place your Excel file (with student details) inside the `input/` folder.  
   - Upload it from the app interface.  

2. **Choose Grouping Method**  
   - Branch-wise full list  
   - Branch-wise mix  
   - Uniform mix  

3. **Save & View Outputs**  
   - Generated group files are saved in the `output/` directory.  
   - Use "Generate Summary" to consolidate results.  

4. **View Summary**  
   - Open the summary CSV from the app.  

---

## 📦 Requirements  

Your `requirements.txt` should include:  

```
streamlit
pandas
openpyxl
```

---



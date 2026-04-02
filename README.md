# 🏥 Biomedical Patient Health Monitoring System
---

## 📌 Project Overview

A C++ based **Patient Vital Signs Monitoring System** that simulates real-time health monitoring in a clinical environment. The system records, analyzes, and classifies patient vitals to assist in early risk detection.

This project bridges **biomedical domain knowledge** with **software engineering** using core C++ concepts.

---

## 🩺 Features

- **Vital Signs Monitoring**
  - Heart Rate (bpm) — Detects Bradycardia / Tachycardia
  - Blood Pressure (systolic/diastolic) — WHO classification stages
  - SpO2 / Oxygen Saturation — Hypoxemia detection
  - Body Temperature — Fever & Hypothermia detection
  - Blood Glucose — Hypo/Hyperglycemia detection

- **Automated Risk Score (0–100)**
  - Calculates a composite risk score from all vitals
  - Classifies patients as: Stable / Moderate / High Risk / Critical

- **Session Statistics**
  - Average vitals across all patients
  - Count of critical-risk patients

- **File Export**
  - Saves all patient reports to `patient_reports.txt`

- **Demo Mode**
  - Preloaded sample patients for quick demonstration

---

## 🛠️ Technologies Used

| Technology | Usage |
|---|---|
| C++ (Standard: C++11) | Core language |
| STL (vector, string) | Data structures |
| File I/O (fstream) | Report saving |
| ctime | Timestamp generation |
| iomanip | Formatted output |

---

## 🚀 How to Run

### Compile
```bash
g++ -std=c++11 -o health_monitor main.cpp
```

### Run
```bash
./health_monitor        # Linux/Mac
health_monitor.exe      # Windows
```

---

## 📊 Sample Output

```
╔══════════════════════════════════════════════════════╗
║         PATIENT HEALTH MONITORING REPORT             ║
╚══════════════════════════════════════════════════════╝
  Patient ID   : 2
  Name         : Priya Sharma
  Age / Gender : 62 / F
  Timestamp    : 2024-03-15 10:32:11
──────────────────────────────────────────────────────
  VITAL SIGNS
──────────────────────────────────────────────────────
  Heart Rate   :  105.0 bpm     → TACHYCARDIA (High)
  Blood Press  : 165.0/100.0 mmHg  → HYPERTENSION Stage 2
  SpO2         :   91.0 %       → MILD HYPOXEMIA
  Temperature  :   38.8 °C      → MILD FEVER
  Blood Glucose:  220.0 mg/dL   → HYPERGLYCEMIA (High)
──────────────────────────────────────────────────────
  RISK SCORE   : 65 / 100
  RISK LEVEL   : ** HIGH RISK **
══════════════════════════════════════════════════════
```

---

## 🎓 Biomedical Concepts Applied

| Parameter | Normal Range | Clinical Significance |
|---|---|---|
| Heart Rate | 60–100 bpm | Arrhythmia detection |
| Systolic BP | 90–120 mmHg | Hypertension staging (WHO) |
| SpO2 | ≥ 95% | Respiratory health |
| Temperature | 36.1–37.5 °C | Infection / Hypothermia |
| Blood Glucose | 70–140 mg/dL | Diabetes monitoring |

---

## 💡 Future Scope
- GUI using Qt or wxWidgets
- Real-time sensor integration (Arduino / Raspberry Pi)
- Database connectivity (SQLite) for persistent records
- ECG signal processing module

---

## 👤 Author
Vijayan.P 
B.E. Biomedical Engineering  
V.S.B Engineering College. 


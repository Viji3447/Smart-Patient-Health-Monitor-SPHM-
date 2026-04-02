#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

// ─────────────────────────────────────────────
//  PATIENT STRUCT
// ─────────────────────────────────────────────
struct Patient {
    int id;
    string name;
    int age;
    string gender;

    // Vital signs
    float heartRate;       // bpm
    float systolicBP;      // mmHg
    float diastolicBP;     // mmHg
    float spo2;            // %
    float temperature;     // Celsius
    float bloodGlucose;    // mg/dL

    string timestamp;
};

// ─────────────────────────────────────────────
//  UTILITY: Get current timestamp
// ─────────────────────────────────────────────
string getCurrentTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

// ─────────────────────────────────────────────
//  ANALYSIS: Classify vital signs
// ─────────────────────────────────────────────
string classifyHeartRate(float hr) {
    if (hr < 60)  return "BRADYCARDIA (Low)";
    if (hr > 100) return "TACHYCARDIA (High)";
    return "NORMAL";
}

string classifyBP(float sys, float dia) {
    if (sys < 90 || dia < 60)   return "HYPOTENSION (Low)";
    if (sys >= 180 || dia >= 120) return "HYPERTENSIVE CRISIS";
    if (sys >= 140 || dia >= 90) return "HYPERTENSION Stage 2";
    if (sys >= 130 || dia >= 80) return "HYPERTENSION Stage 1";
    if (sys >= 120)              return "ELEVATED";
    return "NORMAL";
}

string classifySpO2(float spo2) {
    if (spo2 >= 95) return "NORMAL";
    if (spo2 >= 90) return "MILD HYPOXEMIA";
    if (spo2 >= 85) return "MODERATE HYPOXEMIA";
    return "SEVERE HYPOXEMIA - CRITICAL";
}

string classifyTemperature(float temp) {
    if (temp < 35.0) return "HYPOTHERMIA";
    if (temp > 38.5) return "HIGH FEVER";
    if (temp > 37.5) return "MILD FEVER";
    return "NORMAL";
}

string classifyGlucose(float glucose) {
    if (glucose < 70)  return "HYPOGLYCEMIA (Low)";
    if (glucose > 200) return "HYPERGLYCEMIA (High)";
    if (glucose > 140) return "PRE-DIABETIC RANGE";
    return "NORMAL";
}

// ─────────────────────────────────────────────
//  RISK SCORE CALCULATOR (0-100)
// ─────────────────────────────────────────────
int calculateRiskScore(const Patient& p) {
    int score = 0;

    // Heart rate
    if (p.heartRate < 50 || p.heartRate > 130) score += 30;
    else if (p.heartRate < 60 || p.heartRate > 100) score += 10;

    // Blood pressure
    if (p.systolicBP >= 180 || p.diastolicBP >= 120) score += 30;
    else if (p.systolicBP >= 140 || p.diastolicBP >= 90) score += 15;
    else if (p.systolicBP < 90) score += 20;

    // SpO2
    if (p.spo2 < 85) score += 30;
    else if (p.spo2 < 90) score += 20;
    else if (p.spo2 < 95) score += 10;

    // Temperature
    if (p.temperature > 39.5 || p.temperature < 34) score += 20;
    else if (p.temperature > 38.5 || p.temperature < 35) score += 10;

    // Glucose
    if (p.bloodGlucose < 50 || p.bloodGlucose > 300) score += 20;
    else if (p.bloodGlucose < 70 || p.bloodGlucose > 200) score += 10;

    return min(score, 100);
}

string riskLevel(int score) {
    if (score >= 70) return "*** CRITICAL ***";
    if (score >= 40) return "** HIGH RISK **";
    if (score >= 20) return "* MODERATE *";
    return "LOW / STABLE";
}

// ─────────────────────────────────────────────
//  DISPLAY PATIENT REPORT
// ─────────────────────────────────────────────
void displayReport(const Patient& p) {
    int risk = calculateRiskScore(p);

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║         PATIENT HEALTH MONITORING REPORT             ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";
    cout << "  Patient ID   : " << p.id << "\n";
    cout << "  Name         : " << p.name << "\n";
    cout << "  Age / Gender : " << p.age << " / " << p.gender << "\n";
    cout << "  Timestamp    : " << p.timestamp << "\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << "  VITAL SIGNS\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << fixed << setprecision(1);
    cout << "  Heart Rate   : " << setw(6) << p.heartRate   << " bpm     → " << classifyHeartRate(p.heartRate) << "\n";
    cout << "  Blood Press  : " << p.systolicBP << "/" << p.diastolicBP << " mmHg  → " << classifyBP(p.systolicBP, p.diastolicBP) << "\n";
    cout << "  SpO2         : " << setw(6) << p.spo2        << " %       → " << classifySpO2(p.spo2) << "\n";
    cout << "  Temperature  : " << setw(6) << p.temperature << " °C      → " << classifyTemperature(p.temperature) << "\n";
    cout << "  Blood Glucose: " << setw(6) << p.bloodGlucose<< " mg/dL   → " << classifyGlucose(p.bloodGlucose) << "\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << "  RISK SCORE   : " << risk << " / 100\n";
    cout << "  RISK LEVEL   : " << riskLevel(risk) << "\n";
    cout << "══════════════════════════════════════════════════════\n\n";
}

// ─────────────────────────────────────────────
//  SAVE REPORT TO FILE
// ─────────────────────────────────────────────
void saveReport(const Patient& p) {
    ofstream file("patient_reports.txt", ios::app);
    if (!file) {
        cout << "  [ERROR] Could not save report.\n";
        return;
    }
    int risk = calculateRiskScore(p);
    file << "---\n";
    file << "ID:" << p.id << " | Name:" << p.name << " | Age:" << p.age << " | Gender:" << p.gender << "\n";
    file << "Time:" << p.timestamp << "\n";
    file << "HR:" << p.heartRate << " | BP:" << p.systolicBP << "/" << p.diastolicBP
         << " | SpO2:" << p.spo2 << " | Temp:" << p.temperature << " | Glucose:" << p.bloodGlucose << "\n";
    file << "Risk Score:" << risk << " | Level:" << riskLevel(risk) << "\n";
    file.close();
    cout << "  [✓] Report saved to patient_reports.txt\n";
}

// ─────────────────────────────────────────────
//  INPUT PATIENT DATA
// ─────────────────────────────────────────────
Patient inputPatient(int id) {
    Patient p;
    p.id = id;
    p.timestamp = getCurrentTime();

    cout << "\n  Enter Patient Name      : ";
    cin.ignore();
    getline(cin, p.name);

    cout << "  Enter Age               : ";
    cin >> p.age;

    cout << "  Enter Gender (M/F)      : ";
    cin >> p.gender;

    cout << "\n  --- Vital Signs ---\n";
    cout << "  Heart Rate (bpm)        : ";
    cin >> p.heartRate;

    cout << "  Systolic BP (mmHg)      : ";
    cin >> p.systolicBP;

    cout << "  Diastolic BP (mmHg)     : ";
    cin >> p.diastolicBP;

    cout << "  SpO2 (%)                : ";
    cin >> p.spo2;

    cout << "  Temperature (°C)        : ";
    cin >> p.temperature;

    cout << "  Blood Glucose (mg/dL)   : ";
    cin >> p.bloodGlucose;

    return p;
}

// ─────────────────────────────────────────────
//  STATISTICS ACROSS ALL PATIENTS
// ─────────────────────────────────────────────
void showStatistics(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "  No patient data available.\n";
        return;
    }

    float totalHR = 0, totalSpO2 = 0, totalTemp = 0;
    int criticalCount = 0;

    for (const auto& p : patients) {
        totalHR   += p.heartRate;
        totalSpO2 += p.spo2;
        totalTemp += p.temperature;
        if (calculateRiskScore(p) >= 70) criticalCount++;
    }

    int n = patients.size();
    cout << "\n  ── SESSION STATISTICS ──────────────────────────\n";
    cout << "  Total Patients Monitored : " << n << "\n";
    cout << fixed << setprecision(2);
    cout << "  Avg Heart Rate           : " << totalHR / n << " bpm\n";
    cout << "  Avg SpO2                 : " << totalSpO2 / n << " %\n";
    cout << "  Avg Temperature          : " << totalTemp / n << " °C\n";
    cout << "  Critical Risk Patients   : " << criticalCount << "\n";
    cout << "  ────────────────────────────────────────────────\n";
}

// ─────────────────────────────────────────────
//  DEMO MODE: Preloaded sample patients
// ─────────────────────────────────────────────
vector<Patient> loadDemoPatients() {
    vector<Patient> demo;

    Patient p1 = {1, "Arun Kumar", 45, "M", 88.0, 138.0, 88.0, 96.5, 37.2, 105.0, getCurrentTime()};
    Patient p2 = {2, "Priya Sharma", 62, "F", 105.0, 165.0, 100.0, 91.0, 38.8, 220.0, getCurrentTime()};
    Patient p3 = {3, "Ravi Menon", 30, "M", 72.0, 118.0, 76.0, 98.0, 36.8, 90.0, getCurrentTime()};

    demo.push_back(p1);
    demo.push_back(p2);
    demo.push_back(p3);

    return demo;
}

// ─────────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────────
int main() {
    vector<Patient> patients;
    int choice;
    int nextId = 1;

    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║   BIOMEDICAL PATIENT HEALTH MONITORING SYSTEM   ║\n";
    cout << "  ║         Developed in C++ | College Project      ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";

    while (true) {
        cout << "\n  ── MAIN MENU ──────────────────────────────────\n";
        cout << "  1. Add New Patient & Monitor Vitals\n";
        cout << "  2. Load Demo Patients (Sample Data)\n";
        cout << "  3. View All Patient Reports\n";
        cout << "  4. Show Session Statistics\n";
        cout << "  5. Save Reports to File\n";
        cout << "  6. Exit\n";
        cout << "  ───────────────────────────────────────────────\n";
        cout << "  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient p = inputPatient(nextId++);
                patients.push_back(p);
                displayReport(p);
                break;
            }
            case 2: {
                auto demo = loadDemoPatients();
                for (auto& p : demo) {
                    p.id = nextId++;
                    patients.push_back(p);
                }
                cout << "  [✓] 3 demo patients loaded.\n";
                for (const auto& p : demo) displayReport(p);
                break;
            }
            case 3: {
                if (patients.empty()) {
                    cout << "  No patients added yet.\n";
                } else {
                    for (const auto& p : patients) displayReport(p);
                }
                break;
            }
            case 4:
                showStatistics(patients);
                break;
            case 5:
                for (const auto& p : patients) saveReport(p);
                break;
            case 6:
                cout << "\n  Exiting system. Stay healthy!\n\n";
                return 0;
            default:
                cout << "  Invalid choice. Try again.\n";
        }
    }
}

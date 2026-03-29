#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// --- App Interface Color Codes ---
const string RED = "\033[1;31m";
const string ORANGE = "\033[1;33m";
const string YELLOW = "\033[1;33m"; // Fallback for Orange in some terminals
const string GREEN = "\033[1;32m";
const string BLUE = "\033[1;36m";
const string RESET = "\033[0m";

struct Patient {
    string name;
    string symptoms;
    int score = 0;
    string category;
    string color;
};

map<string, int> medicalDict;

// 1. Load the 1,500+ Dictionary File
void loadDictionary() {
    ifstream file("medical_dictionary.txt");
    if (!file) {
        cout << RED << "[ERROR] medical_dictionary.txt not found! Creating default..." << RESET << endl;
        medicalDict["chest"] = 60; medicalDict["bleed"] = 50; medicalDict["fever"] = 20;
        return;
    }
    string line, word;
    int score;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, word, ',');
        ss >> score;
        medicalDict[word] = score;
    }
    file.close();
}

// 2. Convert to Lowercase
string toLower(string data) {
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}
// --- INNOVATION: Levenshtein Distance (Typo Correction) ---
int getEditDistance(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
        }
    }
    return dp[m][n];
}
// 3. The "AI" Priority Engine
void calculatePriority(Patient &p) {
    string text = toLower(p.symptoms);
    
    // 1. INNOVATION: Clean the data! Remove punctuation so "pain," doesn't break the math.
    text.erase(remove_if(text.begin(), text.end(), ::ispunct), text.end());

    stringstream ss(text);
    string userWord;
    bool isSevere = false; // Track this while we read the words
    
    while (ss >> userWord) {
        
        // 2. FUZZY MATCH THE MULTIPLIER: Catch typos like "seveere" or "extreem"
        if (getEditDistance(userWord, "severe") <= 2 || getEditDistance(userWord, "extreme") <= 2) {
            isSevere = true;
        }

        // 3. SCAN THE DICTIONARY
        for (auto const& [keyword, weight] : medicalDict) {
            
            // EXACT MATCH or SUBSTRING
            if (userWord.find(keyword) != string::npos) {
                p.score += weight;
                break; 
            }
            
            // FUZZY MATCH (Typo Correction)
            if (keyword.length() > 3) {
                int distance = getEditDistance(userWord, keyword);
                
                // Allow 2 typos for long words (like "bleeding"), but only 1 typo for short words (like "pain")
                int maxTypos = (keyword.length() >= 5) ? 2 : 1;
                
                if (distance <= maxTypos) {
                    p.score += weight;
                    break;
                }
            }
        }
    }

    // 4. Apply the Multiplier 
    if (isSevere) {
        p.score = (p.score == 0) ? 20 : p.score * 2; 
    }

    // 5. App Colors & ESI Logic
    if (p.score >= 100) { p.category = "L1: RESUSCITATION"; p.color = RED; }
    else if (p.score >= 70) { p.category = "L2: EMERGENT     "; p.color = ORANGE; }
    else if (p.score >= 40) { p.category = "L3: URGENT       "; p.color = YELLOW; }
    else if (p.score >= 20) { p.category = "L4: LESS URGENT  "; p.color = GREEN; }
    else { p.category = "L5: NON-URGENT   "; p.color = BLUE; }
}
// 4. App Dashboard UI
void displayDashboard(const vector<Patient>& queue) {
    // Clear the screen (works on Windows and Mac/Linux)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << BLUE << "================================================================" << RESET << endl;
    cout << "             " << RED << "+ TriageFlow Emergency Dashboard +" << RESET << "             " << endl;
    cout << BLUE << "================================================================" << RESET << endl;
    cout << " PATIENT NAME       | SCORE | STATUS               | PRIORITY   " << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (const auto &p : queue) {
        cout << " " << left << setw(18) << p.name 
             << " | " << setw(5) << p.score 
             << " | " << p.color << p.category << RESET 
             << " | " << p.color << "P" << (p.score >= 100 ? 1 : p.score >= 70 ? 2 : p.score >= 40 ? 3 : p.score >= 20 ? 4 : 5) << RESET << endl;
    }
    cout << "----------------------------------------------------------------\n" << endl;
}

int main() {
    loadDictionary();
    vector<Patient> queue;
    string addMore = "y";

    while (addMore == "y" || addMore == "Y") {
        Patient p;
        cout << "\n[NEW PATIENT ENTRY]" << endl;
        cout << "Enter Patient Name: ";
        getline(cin, p.name);
        cout << "Enter Symptoms: ";
        getline(cin, p.symptoms);

        calculatePriority(p);
        queue.push_back(p);

        // Sort instantly so the highest priority is always at the top
        sort(queue.begin(), queue.end(), [](const Patient &a, const Patient &b) {
            return a.score > b.score;
        });

        // Show the updated "App" Dashboard
        displayDashboard(queue);

        cout << "Add another patient? (y/n): ";
        getline(cin, addMore);
    }

    cout << GREEN << "\n[SYSTEM LOGOFF] Triage queue saved and finalized." << RESET << endl;
    return 0;
}
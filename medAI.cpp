#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//colours
const string RED = "\033[1;31m";
const string ORANGE = "\033[1;33m";
const string YELLOW = "\033[1;33m"; 
const string GREEN = "\033[1;32m";
const string BLUE = "\033[1;36m";
const string RESET = "\033[0m";

struct Patient {
    string name;
    int age;//babies and old people have more priority
    string symptoms;
    int score = 0;
    string category;
    string color;
    string waitTime;
};
// parallel dictionary
string dictWords[100];
int dictScores[100];
int totalDictionaryWords = 0; 

void setupDictionary() {
    // Instant CRITICAL (100 points = 0 MINS wait guaranteed)
    dictWords[0] = "heart";      dictScores[0] = 100;
    dictWords[1] = "stroke";     dictScores[1] = 100;
    dictWords[2] = "choke";      dictScores[2] = 100;
    dictWords[3] = "poison";     dictScores[3] = 100;
    dictWords[4] = "gunshot";    dictScores[4] = 100;
    dictWords[5] = "seizure";    dictScores[5] = 100;
    dictWords[6] = "crash";      dictScores[6] = 100;
    dictWords[7] = "arrest";     dictScores[7] = 100; 
    dictWords[8] = "shortness";  dictScores[8] = 100; 
    dictWords[9] = "accident";   dictScores[9] = 100; 

    // HIGH TIER (70-90 points = 5-10 MINS WAIT)
    dictWords[10] = "chest";     dictScores[10] = 80; 
    dictWords[11] = "breath";    dictScores[11] = 80;
    dictWords[12] = "trauma";    dictScores[12] = 80;
    dictWords[13] = "bleed";     dictScores[13] = 80; 
    dictWords[14] = "blood";     dictScores[14] = 80; 
    
    // MID TIER (40-60 points = 15-30 MINS WAIT)
    dictWords[15] = "faint";     dictScores[15] = 60;
    dictWords[16] = "asthma";    dictScores[16] = 60;
    dictWords[17] = "neck";      dictScores[17] = 50; 
    dictWords[18] = "allergy";   dictScores[18] = 50;
    dictWords[19] = "burn";      dictScores[19] = 45;
    dictWords[20] = "broken";    dictScores[20] = 45;
    dictWords[21] = "fracture";  dictScores[21] = 45;
    dictWords[22] = "numb";      dictScores[22] = 40;
    dictWords[23] = "vision";    dictScores[23] = 40;
    dictWords[24] = "blurry";    dictScores[24] = 40; 

    // LOWER MID TIER (25-35 points = 30-60 MINS WAIT)
    dictWords[25] = "head";      dictScores[25] = 35; 
    dictWords[26] = "headache";  dictScores[26] = 35; 
    dictWords[27] = "migraine";  dictScores[27] = 35; 
    dictWords[28] = "stomach";   dictScores[28] = 35;
    dictWords[29] = "diarrhea";  dictScores[29] = 35; 
    dictWords[30] = "injury";    dictScores[30] = 30;
    dictWords[31] = "wound";     dictScores[31] = 30;
    dictWords[32] = "bone";      dictScores[32] = 30;
    dictWords[33] = "dizzy";     dictScores[33] = 30;
    dictWords[34] = "cut";       dictScores[34] = 30;
    dictWords[35] = "fall";      dictScores[35] = 30;
    dictWords[36] = "bite";      dictScores[36] = 30;
    dictWords[37] = "attack";    dictScores[37] = 30; 
    dictWords[38] = "swollen";   dictScores[38] = 30; 
    dictWords[39] = "vomit";     dictScores[39] = 25;
    dictWords[40] = "throwing";  dictScores[40] = 25; 
    dictWords[41] = "nausea";    dictScores[41] = 25; 
    dictWords[42] = "pee";       dictScores[42] = 25; 

    // LOW TIER (5-20 points = 1-2 HOURS WAIT)
    dictWords[43] = "pain";      dictScores[43] = 20;
    dictWords[44] = "back";      dictScores[44] = 20;
    dictWords[45] = "backache";  dictScores[45] = 20; 
    dictWords[46] = "throat";    dictScores[46] = 20; 
    dictWords[47] = "joint";     dictScores[47] = 20; 
    dictWords[48] = "knee";      dictScores[48] = 15;
    dictWords[49] = "leg";       dictScores[49] = 15;
    dictWords[50] = "arm";       dictScores[50] = 15;
    dictWords[51] = "fever";     dictScores[51] = 15;
    dictWords[52] = "ankle";     dictScores[52] = 15;
    dictWords[53] = "sore";      dictScores[53] = 15; 
    dictWords[54] = "gland";     dictScores[54] = 15; 
    dictWords[55] = "stiff";     dictScores[55] = 15; 
    dictWords[56] = "cough";     dictScores[56] = 10;
    dictWords[57] = "coughing";  dictScores[57] = 10; 
    dictWords[58] = "toe";       dictScores[58] = 10;
    dictWords[59] = "rash";      dictScores[59] = 5;

    // confusing slang words 
    dictWords[60] = "ticker";    dictScores[60] = 100; // Heart
    dictWords[61] = "breathing"; dictScores[61] = 80;  // Breath
    dictWords[62] = "peepers";   dictScores[62] = 40;  // Vision
    dictWords[63] = "tingly";    dictScores[63] = 40;  // Numb
    dictWords[64] = "noggin";    dictScores[64] = 35;  // Head
    dictWords[65] = "fog";       dictScores[65] = 35;  // Brain fog
    dictWords[66] = "tummy";     dictScores[66] = 35;  // Stomach
    dictWords[67] = "gut";       dictScores[67] = 35;  // Stomach
    dictWords[68] = "runs";      dictScores[68] = 35;  // Diarrhea
    dictWords[69] = "woozy";     dictScores[69] = 30;  // Dizzy
    dictWords[70] = "spinning";  dictScores[70] = 30;  // Dizzy
    dictWords[71] = "stars";     dictScores[71] = 30;  // Dizzy/Vision
    dictWords[72] = "puking";    dictScores[72] = 25;  // Vomiting
    dictWords[73] = "guts";      dictScores[73] = 25;  // Puking guts out
    dictWords[74] = "wiped";     dictScores[74] = 15;  // Fatigue / Faint
    
    totalDictionaryWords = 75;//will print this 
    cout << GREEN << "Loaded internal dictionary with " << totalDictionaryWords << " target symptoms." << RESET << endl;
}

string makeLowercase(string sentence) {
    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
            sentence[i] = sentence[i] + 32; 
        }
    }
    return sentence;
}

//this is used for the Levenshtein Distance function to find the smallest of 3 numbers
int findSmallestNumber(int a, int b, int c) {
    int smallest = a;
    if (b < smallest) smallest = b;
    if (c < smallest) smallest = c;
    return smallest;// 
}

//typo checker (Levenshtein Distance)
// this is the way to measure how different two words are
int getTypoDistance(string word1, string word2) {
    int length1 = word1.length();
    int length2 = word2.length();
    
    int typoGrid[50][50]; //this creates a matrix where rows represent the first word and columns represent the second word. the code fill this table cell-by-cell. Each cell stores the cost of matching the words upto that point.
    
    for (int row = 0; row <= length1; row++) {
        for (int col = 0; col <= length2; col++) {
            if (row == 0) {
                typoGrid[row][col] = col;//if one word is empty, the cost is simply the length of the other word
            }
            else if (col == 0) {
                typoGrid[row][col] = row;//same logic
            }
            else if (word1[row - 1] == word2[col - 1]) {
                typoGrid[row][col] = typoGrid[row - 1][col - 1];//If the letters match perfectly, the cost doesn't go up
            }
            else {
                typoGrid[row][col] = 1 + findSmallestNumber(//If the letters don't match, we have to perform an "edit." We look at the neighbors (Left, Top, and Diagonal) and pick the cheapest path, then add +1 for the edit we just made.
                    typoGrid[row][col - 1],      
                    typoGrid[row - 1][col],      
                    typoGrid[row - 1][col - 1]   
                );
            }
        }
    }
    return typoGrid[length1][length2]; // after the loop, the last cell in the bottom right corner contains the final cost
}
// logic
void calculatePriority(Patient &p) {
    string text = makeLowercase(p.symptoms);
    
    // remove punctuation
    string cleanText = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] != ',' && text[i] != '.' && text[i] != '!') {
            cleanText += text[i];
        }
    }
    //if these stuff turn true, it will increase or decrease the points
    bool isSevere = false;
    bool isMild = false; 
    bool highRiskArea = false;
    bool lowRiskArea = false;

    // checking for specific high risk areas(reduce wait)
    if (text.find("internal") != string::npos || text.find("chest") != string::npos || 
        text.find("heart") != string::npos || text.find("brain") != string::npos || 
        text.find("breath") != string::npos) {
        highRiskArea = true;
    }

    // Check for Low Risk Areas(will reduce points if the issue is with these ones)
    if (text.find("finger") != string::npos || text.find("toe") != string::npos || 
        text.find("nail") != string::npos || text.find("skin") != string::npos) {
        lowRiskArea = true;
    }

    string userWord = "";
    for (int j = 0; j <= cleanText.length(); j++) {
        if (j == cleanText.length() || cleanText[j] == ' ') {
            if (userWord.length() > 0) {
                
                // Check for Severe stuff
                if (getTypoDistance(userWord, "severe") <= 2 || getTypoDistance(userWord, "extreme") <= 2 || 
                    getTypoDistance(userWord, "killing") <= 1 || getTypoDistance(userWord, "agony") <= 1) {
                    isSevere = true;
                }
                
                // Check for Mild
                if (getTypoDistance(userWord, "mild") <= 1 || getTypoDistance(userWord, "minor") <= 1) {
                    isMild = true;
                }

                // Match against Dictionary
                for (int i = 0; i < totalDictionaryWords; i++) {
                    if (userWord.find(dictWords[i]) != string::npos) { 
                        p.score += dictScores[i];
                        break; 
                    }
                }
                userWord = ""; 
            }
        } else {
            userWord += cleanText[j]; 
        }
    }
    // after a bunch wrong outputs...
    // high-risk area ==> double the score regardless of "mild" or any other words
    if (highRiskArea) {
        p.score = p.score * 2; 
    }

    // low-risk area ==> divide the score by 2
    if (lowRiskArea) {
        p.score = p.score / 2;
    }

    //standard "Severe" multiplier
    if (isSevere) p.score = p.score * 2;

    //"Mild" downgrader only if it's NOT a high-risk area
    if (isMild && !highRiskArea) {
        p.score = p.score / 2;
    }
    // check if age is < 5 or > 65
    if (p.age < 5 || p.age > 65) p.score += 15;

    // wait time and critical status
    if (p.score >= 100) { p.category = "L1: CRITICAL     "; p.color = RED; p.waitTime = "0 MINS"; }
    else if (p.score >= 70) { p.category = "L2: EMERGENT     "; p.color = ORANGE; p.waitTime = "2 - 10 MINS"; }
    else if (p.score >= 40) { p.category = "L3: URGENT       "; p.color = YELLOW; p.waitTime = "20 - 30 MINS"; }
    else if (p.score >= 20) { p.category = "L4: LESS URGENT  "; p.color = GREEN; p.waitTime = "30 - 45 MINS"; }
    else { p.category = "L5: NON-URGENT   "; p.color = BLUE; p.waitTime = "45 MIN -  1.5 HOURS"; }
}
// UI (queue)
void displayDashboard(Patient queue[], int patientCount) {
    #ifdef _WIN32 //asks the compiler if its mac or windows
        system("cls");//windows
    #else
        system("clear");//mac
    #endif // only to clear the console so that it doesnt get messy
    cout << "-------------------------------------------------------------------------" << endl;
    cout << " PATIENT NAME       | AGE | STATUS            | PRIORITY | EST. WAIT  " << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < patientCount; i++) {
        Patient p = queue[i];
        
        int pLevel = 5;
        if (p.score >= 100) pLevel = 1;
        else if (p.score >= 70) pLevel = 2;
        else if (p.score >= 40) pLevel = 3;
        else if (p.score >= 20) pLevel = 4;

        cout << " " << left << setw(18) << p.name 
             << " | " << setw(3) << p.age
             << " | " << p.color << p.category << RESET 
             << " | " << p.color << "P" << pLevel << RESET 
             << "       | " << p.waitTime << endl;
    }
    cout << "-------------------------------------------------------------------------\n" << endl;
}

int main() {
    setupDictionary(); 
    cout << "\nPress ENTER to launch the Dashboard...";
    string dummy;
    getline(cin, dummy);//enter whatever and it will continue

    Patient ER_Queue[100];
    int patientCount = 0; 

    string addMore = "y"; // if anything else, it will quit

    while ((addMore == "y" || addMore == "Y") && patientCount < 100) {
        Patient newPatient;
        
        cout << "\n[NEW PATIENT ENTRY]" << endl;
        cout << "Enter Patient Name: ";
        getline(cin, newPatient.name);
        
        cout << "Enter Patient Age: ";
        cin >> newPatient.age;
        cin.ignore(); 
        
        cout << "Enter Symptoms: ";
        getline(cin, newPatient.symptoms);

        calculatePriority(newPatient);
        
        ER_Queue[patientCount] = newPatient;
        patientCount++;

        // Bubble Sort
        for (int i = 0; i < patientCount; i++) {
            for (int j = 0; j < patientCount - 1; j++) {
                if (ER_Queue[j].score < ER_Queue[j+1].score) {
                    Patient temporaryHolder = ER_Queue[j];
                    ER_Queue[j] = ER_Queue[j+1];
                    ER_Queue[j+1] = temporaryHolder;
                }
            }
        }

        displayDashboard(ER_Queue, patientCount);

        if (patientCount < 100) {
            cout << "Add another patient? (y/n): ";
            getline(cin, addMore);
        } else {
            cout << RED << "Max Capacity Reached!" << RESET << endl;
            break;
        }
    }

    cout << GREEN << "\n[SYSTEM LOGOFF] Triage queue finalized." << RESET << endl;
    return 0;
}
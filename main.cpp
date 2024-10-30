// Lab 26: Data Structures Olympics 
// COMSC-210 - Ibrahim Alatig 

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm> // For std::sort
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const int NUM_OF_ELEMENTS = 20000; 
const int NUM_OF_SIMULATIONS = 15;
const int NUM_OF_OPERATIONS = 4;

void readData(const string& filename, vector<string>& vec, list<string>& lst, set<string>& st);
void sortData(vector<string>& vec, list<string>& lst);
void insertData(vector<string>& vec, list<string>& lst, set<string>& st, const string& value);
void deleteData(vector<string>& vec, list<string>& lst, set<string>& st);

// main method
int main() {
    vector<string> dataVector;
    list<string> dataList;
    set<string> dataSet;

    long long timings[NUM_OF_SIMULATIONS][NUM_OF_OPERATIONS][2] = {{{0}}};

    for (int sim = 0; sim < NUM_OF_SIMULATIONS; ++sim) {
        dataVector.clear();
        dataList.clear();
        dataSet.clear();

        // measure read time
        auto start = high_resolution_clock::now();
        readData("codes.txt", dataVector, dataList, dataSet);
        auto end = high_resolution_clock::now();
        timings[sim][0][0] = duration_cast<milliseconds>(end - start).count(); 

        // Measure Sort Time
        start = high_resolution_clock::now();
        sortData(dataVector, dataList);
        end = high_resolution_clock::now();
        timings[sim][1][0] = duration_cast<milliseconds>(end - start).count();

        // Measure Insert Time
        start = high_resolution_clock::now();
        insertData(dataVector, dataList, dataSet, "TESTCODE");
        end = high_resolution_clock::now();
         timings[sim][2][0] = duration_cast<milliseconds>(end - start).count();

        // Measure Delete Time
        start = high_resolution_clock::now();
        deleteData(dataVector, dataList, dataSet);
        end = high_resolution_clock::now();
        timings[sim][3][0] = duration_cast<milliseconds>(end - start).count();

        timings[sim][2][1] = (dataSet.count("TESTCODE") > 0) ? 1 : 0;
        timings[sim][3][1] = (dataSet.count("TESTCODE") == 0) ? 1 : 0;
    }

    cout << "Number of simulations: " << NUM_OF_SIMULATIONS << endl;
    cout << left << setw(10) << "Operation" << setw(12) << "Vector" << setw(12) << "List" << setw(12) << "Set" << endl;

    const char* operationNames[] = { "Read", "Sort", "Insert", "Delete" };
    
    for (int op = 0; op < NUM_OF_OPERATIONS; ++op) {
        long long sumVector = 0, sumList = 0, sumSet = 0;

        for (int sim = 0; sim < NUM_OF_SIMULATIONS; ++sim) {
            sumVector += timings[sim][op][0]; 
            sumList += timings[sim][op][0];

            if (op == 2) { // Insert operation
                sumSet += timings[sim][op][1]; 
            } 
            else if (op == 3) { 
                sumSet += timings[sim][op][1]; 
            }
        }

        cout << setw(10) << operationNames[op] 
             << setw(12) << (sumVector / NUM_OF_SIMULATIONS) 
             << setw(12) << (sumList / NUM_OF_SIMULATIONS) 
             << setw(12) << (sumSet / NUM_OF_SIMULATIONS) << endl;
    }

    return 0;
}

void readData(const string& filename, vector<string>& vec, list<string>& lst, set<string>& st) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (vec.size() < NUM_OF_ELEMENTS) {
            vec.push_back(line);
            lst.push_back(line);
            st.insert(line);
        } else {
            break;
        }
    }
}

void sortData(vector<string>& vec, list<string>& lst) {
    std::sort(vec.begin(), vec.end());
    lst.sort(); 
}

void insertData(vector<string>& vec, list<string>& lst, set<string>& st, const string& value) {
    // Insert into vector (middle)
    vec.insert(vec.begin() + vec.size() / 2, value);
    
    // Insert into list (middle)
    auto it = lst.begin();
    advance(it, lst.size() / 2);
    lst.insert(it, value);
    
    // Insert into set
    st.insert(value);
}

void deleteData(vector<string>& vec, list<string>& lst, set<string>& st) {
    // Delete middle element from vector
    if (!vec.empty()) {
        vec.erase(vec.begin() + vec.size() / 2);
    }
    
    // Delete middle element from list
    if (!lst.empty()) {
        auto it = lst.begin();
        advance(it, lst.size() / 2);
        lst.erase(it);
    }
    
    st.erase("TESTCODE");
}
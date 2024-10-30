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

int main() {
    vector<string> dataVector;
    list<string> dataList;
    set<string> dataSet;

    long long timings[NUM_OF_SIMULATIONS][NUM_OF_OPERATIONS] = {0};

    for (int sim = 0; sim < NUM_OF_SIMULATIONS; ++sim) {
        dataVector.clear();
        dataList.clear();
        dataSet.clear();

        // measure read time
        auto start = high_resolution_clock::now();
        readData("codes.txt", dataVector, dataList, dataSet);
        auto end = high_resolution_clock::now();
        timings[sim][0] = duration_cast<milliseconds>(end - start).count();

        

    // output format setup
    cout << left << setw(10) << "Operation" << setw(12) << "Vector" << setw(12) << "List" << setw(12) << "Set" << endl;
    cout << setw(10) << "Read" << setw(12) << duration.count() << setw(12) << duration.count() << setw(12) << duration.count() << endl;

    // sort
    start = high_resolution_clock::now();
    sortData(dataVector, dataList);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << setw(10) << "Sort" << setw(12) << duration.count() << setw(12) << duration.count() << setw(12) << "-1" << endl;

    // value into all three data structures
    start = high_resolution_clock::now();
    insertData(dataVector, dataList, dataSet, "TESTCODE");
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << setw(10) << "Insert" << setw(12) << duration.count() << setw(12) << duration.count() << setw(12) << dataSet.count("TESTCODE") << endl;

    // Delete a value from all three data structures
    start = high_resolution_clock::now();
    deleteData(dataVector, dataList, dataSet);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << setw(10) << "Delete" << setw(12) << duration.count() << setw(12) << duration.count() << setw(12) << 0 << endl; 
    
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
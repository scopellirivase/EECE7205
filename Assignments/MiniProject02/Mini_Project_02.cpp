#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


class Airport {
    public:
        string iata;
        Airport* left;
        Airport* right;

        int id;
        string name;
        string city;
        string country;
        string icao;
        float lat;
        float lon;
        int altitude;
        float time_zone;
        string dst;
        string database;
        string type;
        string source;

        Airport(vector<string> records)
            {
                id          = stoi(records[0]);
                name        = records[1];
                city        = records[2];
                country     = records[3];
                iata        = records[4];
                icao        = records[5];
                lat         = stof(records[6]);
                lon         = stof(records[7]);
                altitude    = stoi(records[8]);
                time_zone   = stof(records[9]);
                dst         = records[10];
                database    = records[11];
                type        = records[12];
                source      = records[13];
                
                left = nullptr;
                right = nullptr;
            }
};

class AirportBST {
    private:
        vector<vector<string>> airportRecords;
    public:
        vector<string> parseCSVLine(const string& line) {
            vector<string> cells;
            string currentCell = "";
            bool insideQuotes = false;

            for (size_t i = 0; i < line.length(); ++i) {
                char ch = line[i];

                if (ch == '"') {
                    if (insideQuotes && i + 1 < line.length() && line[i + 1] == '"') {
                        currentCell += '"';
                        i++;
                    } else {
                        insideQuotes = !insideQuotes;
                    }
                } 
                else if (ch == ',' && !insideQuotes) {
                    cells.push_back(currentCell);
                    currentCell = "";
                } 
                else {
                    currentCell += ch;
                }
            }
            
            cells.push_back(currentCell);
            return cells;
        }
        void loadData(string fileName) {
            ifstream file(fileName);
            if (!file.is_open()) {
                cerr << "Error: Could not open the file." << endl;
                return;
            }

            string line;

            while (getline(file, line)) {
                vector<string> rowCells = parseCSVLine(line);
                airportRecords.push_back(rowCells);
            }
        }
        void printAirports() {
            for (const auto& item : airportRecords) {
                cout << item[1] << " ";
            }
            cout << endl;
        }
        Airport* buildTree() {
            int n = airportRecords.size();
            int c = 0;
            Airport* root = new Airport(airportRecords[0]);

            for (int i = 1; i < n; i++) {
                string key = airportRecords[i][4];
                if (key != "") {
                    Airport* parent = nullptr;
                    Airport* cur = root;

                    while (cur != nullptr && cur->iata != key) {
                        parent = cur;
                        if (cur->iata > key) cur = cur->left;
                        else cur = cur->right;
                    }

                    if (cur->iata != key) {
                        if (parent->left == cur) parent->left = new Airport(airportRecords[i]);
                        else parent->right = new Airport(airportRecords[i]);
                    }
                    c++;
                }
            }
            cout << "Number of insertions: " << c << endl;

            return root;
        }
};


void freeTree(Airport* node) {
    if (node == nullptr) return;
    
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main() {
    AirportBST builder;
    builder.loadData("/home/scopellie/EECE7205/Assignments/MiniProject02/airports.csv");
    builder.printAirports();
}

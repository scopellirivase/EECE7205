#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
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

                left = nullptr;
                right = nullptr;
            }
        void copyData(const Airport& other) {
            iata    = other.iata;
            id      = other.id;
            name    = other.name;
            city    = other.city;
            country = other.country;
            icao    = other.icao;
            lat     = other.lat;
            lon     = other.lon;
        }
        string describe() const {
            return iata + " " + name + ", " + city + ", " + country;
        }
};

class AirportBST {
    private:
        Airport* root;
        int nodeCount;
        int skippedLines;
        vector<Airport> airportRecords;
        unordered_map<string, Airport> database;

        void freeTree(Airport* node) {
            if (node == nullptr) return;
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
        int heightTree(Airport* node) {
            if (node == nullptr) {
                return -1;
            }
            int leftDepth = heightTree(node->left);
            int rightDepth = heightTree(node->right);

            if (leftDepth > rightDepth) {
                return 1 + leftDepth;
            } else {
                return 1 + rightDepth;
            }
        }
        long long sumDepths(Airport* node, int depth) {
            if (node == nullptr) return 0;
            return depth + sumDepths(node->left, depth + 1) + sumDepths(node->right, depth + 1);
        }
        void inorderHelper(Airport* node, vector<Airport*>& out) {
            if (node == nullptr) return;
            inorderHelper(node->left, out);
            out.push_back(node);
            inorderHelper(node->right, out);
        }
        void preorderHelper(Airport* node, vector<string>& out) {
            if (node == nullptr) return;
            out.push_back(node->iata);
            preorderHelper(node->left, out);
            preorderHelper(node->right, out);
        }
        bool isBST(Airport* node, const string* lo, const string* hi) {
            if (node == nullptr) return true;
            if (lo != nullptr && node->iata <= *lo) return false;
            if (hi != nullptr && node->iata >= *hi) return false;
            return isBST(node->left, lo, &node->iata) && isBST(node->right, &node->iata, hi);
        }
        void rangeHelper(Airport* node, const string& from, const string& to, vector<Airport*>& out, int& visited) {
            if (node == nullptr) return;
            visited++;
            if (from < node->iata) rangeHelper(node->left, from, to, out, visited);
            if (from <= node->iata && node->iata <= to) out.push_back(node);
            if (node->iata < to) rangeHelper(node->right, from, to, out, visited);
        }
        Airport* buildBalanced(const vector<Airport>& a, int lo, int hi) {
            if (lo > hi) return nullptr;
            int mid = (lo + hi) / 2;
            Airport* node = new Airport(a[mid]);
            node->left = buildBalanced(a, lo, mid - 1);
            node->right = buildBalanced(a, mid + 1, hi);
            return node;
        }

    public:
        AirportBST() {
            root = nullptr;
            nodeCount = 0;
            skippedLines = 0;
        }
        ~AirportBST() { clear(); }
        AirportBST(const AirportBST&) = delete;
        AirportBST& operator=(const AirportBST&) = delete;
        void clear() {
            freeTree(root);
            root = nullptr;
            nodeCount = 0;
        }
        int size() { 
            return nodeCount; 
        }
        const vector<Airport>& records() { 
            return airportRecords; 
        }
        bool inDatabase(string code) { 
            return database.count(code) > 0; 
        }

        // ---------- 1: loading and building ----------
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
                else if (ch != '\r') {
                    currentCell += ch;
                }
            }

            cells.push_back(currentCell);
            return cells;
        }
        bool loadData(string fileName) {
            ifstream file(fileName);
            if (!file.is_open()) {
                cerr << "Error: Could not open the file." << endl;
                return false;
            }

            airportRecords.clear();
            database.clear();
            skippedLines = 0;

            string line;
            while (getline(file, line)) {
                if (line.empty()) continue;
                vector<string> rowCells = parseCSVLine(line);

                // keep only lines with a 3-letter IATA code (missing is \N)
                if (rowCells.size() < 8 || rowCells[4].length() != 3) {
                    skippedLines++;
                    continue;
                }
                try {
                    Airport a(rowCells);
                    airportRecords.push_back(a);
                    database.insert({a.iata, a});
                } catch (...) {
                    skippedLines++;
                }
            }
            return true;
        }
        void printAirports() {
            cout << "Loaded " << airportRecords.size() << " airports ("
                 << skippedLines << " lines skipped: no IATA code)" << endl;
        }
        bool insert(const Airport& a) {
            Airport* parent = nullptr;
            Airport* cur = root;

            while (cur != nullptr) {
                if (cur->iata == a.iata) return false;
                parent = cur;
                if (a.iata < cur->iata) cur = cur->left;
                else cur = cur->right;
            }

            Airport* node = new Airport(a);
            node->left = nullptr;
            node->right = nullptr;

            if (parent == nullptr) root = node;
            else if (a.iata < parent->iata) parent->left = node;
            else parent->right = node;

            nodeCount++;
            return true;
        }
        void buildTree() {
            clear();
            int n = airportRecords.size();
            int duplicates = 0;

            for (int i = 0; i < n; i++) {
                if (!insert(airportRecords[i])) {
                    duplicates++;
                    cout << "Duplicate code ignored: " << airportRecords[i].iata << endl;
                }
            }
            cout << "Number of insertions: " << nodeCount << ", duplicates: " << duplicates << endl;
        }
        int height() { 
            return heightTree(root); 
        }
        double averageDepth() {
            if (nodeCount == 0) return 0;
            return (double)sumDepths(root, 0) / nodeCount;
        }
        void printShape() {
            cout << "Height: " << height() << "  Average depth: "
                 << fixed << setprecision(1) << averageDepth() << endl;
        }

        // ---------- 2: airport search ----------
        Airport* find(string key, vector<string>* path = nullptr) {
            Airport* cur = root;
            while (cur != nullptr && cur->iata != key) {
                if (path != nullptr) path->push_back(cur->iata);
                if (key < cur->iata) cur = cur->left;
                else cur = cur->right;
            }
            if (cur != nullptr && path != nullptr) path->push_back(cur->iata);
            return cur;
        }
        Airport* minNode() {
            Airport* cur = root;
            while (cur != nullptr && cur->left != nullptr) cur = cur->left;
            return cur;
        }
        Airport* maxNode() {
            Airport* cur = root;
            while (cur != nullptr && cur->right != nullptr) cur = cur->right;
            return cur;
        }
        string rootCode() {
            if (root == nullptr) return "";
            return root->iata;
        }

        // ---------- 3: delete an airport ----------
        bool remove(string key, string& info) {
            Airport* parent = nullptr;
            Airport* cur = root;

            while (cur != nullptr && cur->iata != key) {
                parent = cur;
                if (key < cur->iata) cur = cur->left;
                else cur = cur->right;
            }
            if (cur == nullptr) {
                info = "not found";
                return false;
            }

            if (cur->left == nullptr && cur->right == nullptr) {
                info = "case D1: leaf";
            }
            else if (cur->right == nullptr) {
                info = "case D2: only a left child, " + cur->left->iata;
            }
            else if (cur->left == nullptr) {
                info = "case D2: only a right child, " + cur->right->iata;
            }
            else {
                Airport* succParent = cur;
                Airport* succ = cur->right;
                while (succ->left != nullptr) {
                    succParent = succ;
                    succ = succ->left;
                }
                info = "case D3: two children, successor " + succ->iata;
                cur->copyData(*succ);
                parent = succParent;
                cur = succ;
            }
            Airport* child = (cur->left != nullptr) ? cur->left : cur->right;
            if (parent == nullptr) root = child;
            else if (parent->left == cur) parent->left = child;
            else parent->right = child;

            delete cur;
            nodeCount--;
            return true;
        }
        string findExample(int kind) {
            vector<Airport*> q;
            if (root != nullptr) {
                if (root->left != nullptr) q.push_back(root->left);
                if (root->right != nullptr) q.push_back(root->right);
            }
            for (int i = 0; i < (int)q.size(); i++) {
                Airport* n = q[i];
                bool l = (n->left != nullptr);
                bool r = (n->right != nullptr);
                if (kind == 0 && !l && !r) return n->iata;
                if (kind == 1 && l && !r) return n->iata;
                if (kind == 2 && !l && r) return n->iata;
                if (kind == 3 && l && r) return n->iata;
                if (l) q.push_back(n->left);
                if (r) q.push_back(n->right);
            }
            return "";
        }

        // ---------- 4: traversals and validation ----------
        vector<Airport*> inorderList() {
            vector<Airport*> out;
            inorderHelper(root, out);
            return out;
        }
        vector<string> preorderList() {
            vector<string> out;
            preorderHelper(root, out);
            return out;
        }
        vector<string> levelOrder() {
            vector<string> out;
            vector<Airport*> q;
            if (root != nullptr) q.push_back(root);
            for (int i = 0; i < (int)q.size(); i++) {
                out.push_back(q[i]->iata);
                if (q[i]->left != nullptr) q.push_back(q[i]->left);
                if (q[i]->right != nullptr) q.push_back(q[i]->right);
            }
            return out;
        }
        void printTopLevels(int levels) {
            vector<Airport*> cur;
            vector<Airport*> next;
            cur.push_back(root);

            for (int lv = 0; lv < levels; lv++) {
                cout << "    L" << lv << ":";
                next.clear();
                for (int i = 0; i < (int)cur.size(); i++) {
                    if (cur[i] != nullptr) {
                        cout << " " << cur[i]->iata;
                        next.push_back(cur[i]->left);
                        next.push_back(cur[i]->right);
                    } else {
                        cout << " -";
                        next.push_back(nullptr);
                        next.push_back(nullptr);
                    }
                }
                cout << endl;
                cur = next;
            }
        }
        bool validate() { 
            return isBST(root, nullptr, nullptr); 
        }
        bool saveTree(string fileName) {
            ofstream out(fileName);
            if (!out.is_open()) return false;
            out << "#preorder" << endl;
            vector<string> codes = preorderList();
            for (int i = 0; i < (int)codes.size(); i++) out << codes[i] << endl;
            return true;
        }
        bool restoreTree(string fileName) {
            ifstream in(fileName);
            if (!in.is_open()) return false;
            clear();
            string line;
            while (getline(in, line)) {
                while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
                if (line.empty() || line[0] == '#') continue;
                auto it = database.find(line);
                if (it == database.end()) {
                    cout << "Code not in the airport data: " << line << endl;
                    continue;
                }
                insert(it->second);
            }
            return true;
        }

        // ---------- 5: range query ----------
        int range(string from, string to, vector<Airport*>& out) {
            int visited = 0;
            out.clear();
            rangeHelper(root, from, to, out, visited);
            return visited;
        }

        // ---------- 6: balanced tree ----------
        void buildFromSorted(const vector<Airport>& sorted) {
            clear();
            root = buildBalanced(sorted, 0, (int)sorted.size() - 1);
            nodeCount = sorted.size();
        }
        void rebalance() {
            vector<Airport*> nodes = inorderList();
            vector<Airport> sorted;
            for (int i = 0; i < (int)nodes.size(); i++) sorted.push_back(*nodes[i]);
            buildFromSorted(sorted);
        }
};

// ---------------------------------------------------------------------------
// 6: the shape experiment
// ---------------------------------------------------------------------------
void timeRow(string label, AirportBST& tree, const vector<string>& queries) {
    int found = 0;
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < (int)queries.size(); i++) {
        if (tree.find(queries[i]) != nullptr) found++;
    }
    auto stop = chrono::steady_clock::now();
    double ms = chrono::duration<double, milli>(stop - start).count();

    cout << left << setw(24) << label << right << setw(8) << tree.height()
         << setw(12) << fixed << setprecision(1) << tree.averageDepth()
         << setw(12) << setprecision(2) << ms << " ms";
    if (found != (int)queries.size()) cout << "  (some searches failed)";
    cout << endl;
}
void runExperiment(AirportBST& source) {
    vector<Airport> fileOrder = source.records();
    if (fileOrder.empty()) {
        cout << "Load the airport data first." << endl;
        return;
    }

    vector<Airport> sorted = fileOrder;
    sort(sorted.begin(), sorted.end(),
         [](const Airport& a, const Airport& b) { return a.iata < b.iata; });
    sorted.erase(unique(sorted.begin(), sorted.end(),
                        [](const Airport& a, const Airport& b) { return a.iata == b.iata; }),
                 sorted.end());

    vector<Airport> shuffled = fileOrder;
    mt19937 rng(2026);
    shuffle(shuffled.begin(), shuffled.end(), rng);

    vector<string> queries;
    for (int i = 0; i < 10000; i++) queries.push_back(sorted[rng() % sorted.size()].iata);

    AirportBST t1, t2, t3, t4;
    for (int i = 0; i < (int)fileOrder.size(); i++) t1.insert(fileOrder[i]);
    for (int i = 0; i < (int)sorted.size(); i++) t2.insert(sorted[i]);
    t3.buildFromSorted(sorted);
    for (int i = 0; i < (int)shuffled.size(); i++) t4.insert(shuffled[i]);

    cout << left << setw(24) << "Build order" << right << setw(8) << "Height"
         << setw(12) << "Avg depth" << setw(20) << "10,000 searches" << endl;
    timeRow("File order", t1, queries);
    timeRow("Sorted order", t2, queries);
    timeRow("Balanced (middle rule)", t3, queries);
    timeRow("Random shuffle (bonus)", t4, queries);
}


// ---------------------------------------------------------------------------
// test command (2 - 5)
// ---------------------------------------------------------------------------
int failures = 0;

void check(bool ok, string what) {
    cout << "    [" << (ok ? "PASS" : "FAIL") << "] " << what << endl;
    if (!ok) failures++;
}

void printFind(AirportBST& tree, string code) {
    vector<string> path;
    Airport* a = tree.find(code, &path);

    cout << "  Path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    if (a != nullptr) cout << "  (comparisons: " << path.size() << ")" << endl;
    else cout << " -> (NULL) not found  (comparisons: " << path.size() << ")" << endl;
}

void deleteTest(AirportBST& tree, string label, string code) {
    if (code == "") {
        cout << "  no example of " << label << " in this tree" << endl;
        return;
    }
    cout << "  Delete " << code << "  (" << label << ")" << endl << "  Before:" << endl;
    tree.printTopLevels(3);

    string info;
    bool ok = tree.remove(code, info);

    cout << "  Result: " << info << endl << "  After:" << endl;
    tree.printTopLevels(3);
    check(ok && tree.find(code) == nullptr && tree.validate(), "removed " + code + ", tree is still a valid BST");
}

void runTests(AirportBST& tree) {
    if (tree.records().empty()) {
        cout << "Load the airport data first." << endl;
        return;
    }
    failures = 0;
    tree.buildTree();
    check(tree.validate(), "validate after building the tree");

    // ----- Task 2 -----
    cout << endl << "== Task 2: every search case ==" << endl;
    vector<string> levels = tree.levelOrder();
    string names[6] = {"root", "a leaf", "deepest node", "missing code", "smaller than every key", "larger than every key"};
    string codes[6] = {tree.rootCode(), tree.findExample(0), levels.back(), "XYZ", "000", "~~~"};

    for (int i = 0; i < 6; i++) {
        cout << "  " << names[i] << ": " << codes[i] << endl;
        printFind(tree, codes[i]);
        check((tree.find(codes[i]) != nullptr) == tree.inDatabase(codes[i]), "found only if it is in the data");
    }
    cout << "  Minimum: " << tree.minNode()->describe() << endl;
    cout << "  Maximum: " << tree.maxNode()->describe() << endl;

    // ----- Task 3 -----
    cout << endl << "== Task 3: every delete case ==" << endl;
    deleteTest(tree, "leaf, D1", tree.findExample(0));
    deleteTest(tree, "only a left child, D2", tree.findExample(1));
    deleteTest(tree, "only a right child, D2", tree.findExample(2));
    deleteTest(tree, "two children, D3", tree.findExample(3));
    deleteTest(tree, "the root", tree.rootCode());

    cout << endl << "== Task 3(c): add QQQ, find it, remove it ==" << endl;
    vector<string> fields = {"0", "Quokka Island Test Airfield", "Quokkaville", "Nowhere", "QQQ", "ZQQQ", "0", "0"};
    Airport q(fields);
    check(tree.insert(q) && tree.validate(), "insert QQQ, tree is still a valid BST");
    printFind(tree, "QQQ");
    check(tree.find("QQQ") != nullptr, "QQQ can be found");
    string info;
    bool removed = tree.remove("QQQ", info);
    check(removed && tree.validate() && tree.find("QQQ") == nullptr, "removed QQQ (" + info + ")");

    // ----- Task 4 -----
    cout << endl << "== Task 4: traversals, save / load ==" << endl;
    vector<Airport*> list = tree.inorderList();
    bool sorted = true;
    for (int i = 0; i + 1 < (int)list.size(); i++) {
        if (!(list[i]->iata < list[i + 1]->iata)) sorted = false;
    }
    check(sorted && (int)list.size() == tree.size(), "inorder list is sorted and has every node");

    int h = tree.height();
    vector<string> before = tree.levelOrder();
    check(tree.saveTree("preorder_test.txt"), "saved preorder_test.txt");
    check(tree.restoreTree("preorder_test.txt"), "loaded preorder_test.txt");
    check(tree.height() == h && tree.levelOrder() == before, "reloaded tree has the same height (" + to_string(h) + ") and level order");
    check(tree.validate(), "validate after reload");

    // ----- Task 5 -----
    cout << endl << "== Task 5: range query ==" << endl;
    tree.buildTree();                       // full tree again
    vector<Airport*> found;
    int visited = tree.range("BOS", "BWI", found);

    int expected = 0;
    list = tree.inorderList();
    for (int i = 0; i < (int)list.size(); i++) {
        if (list[i]->iata >= "BOS" && list[i]->iata <= "BWI") expected++;
    }
    cout << "  range BOS BWI: " << found.size() << " airports, " << visited
         << " nodes visited (the posted file should give 113)" << endl;
    check((int)found.size() == expected, "range result equals a full inorder scan");

    cout << endl << (failures == 0 ? "All checks passed." : to_string(failures) + " check(s) FAILED.") << endl;
}

string upper(string s) {
    for (int i = 0; i < (int)s.size(); i++) s[i] = toupper((unsigned char)s[i]);
    return s;
}

void loadFile(AirportBST& tree, string fileName) {
    ifstream probe(fileName);
    if (!probe.is_open()) {
        cout << "Error: could not open " << fileName << endl;
        return;
    }
    int first = probe.peek();
    probe.close();

    if (first == '#') {
        if (tree.records().empty()) {
            cout << "Load the airport data first." << endl;
            return;
        }
        tree.restoreTree(fileName);
        cout << "Rebuilt tree from preorder file: " << tree.size() << " airports" << endl;
    } else {                                // airports.dat
        if (!tree.loadData(fileName)) return;
        tree.printAirports();
        tree.buildTree();
        cout << "validate: " << (tree.validate() ? "OK" : "FAILED") << endl;
    }
    tree.printShape();
}

int main(int argc, char* argv[]) {
    AirportBST tree;
    if (argc > 1) loadFile(tree, argv[1]);

    string line;
    while (true) {
        cout << "> " << flush;
        if (!getline(cin, line)) break;

        istringstream in(line);
        string cmd, a1, a2;
        if (!(in >> cmd)) continue;
        cmd = upper(cmd);

        if (cmd == "QUIT") break;
        else if (cmd == "HELP") {
            cout << "load FILE | find CODE | minmax | remove CODE | add CODE name|city|country\n"
                 << "list [N] | save FILE | validate | range FROM TO | stats | rebalance\n"
                 << "experiment | test | quit" << endl;
        }
        else if (cmd == "LOAD") {
            in >> a1;
            loadFile(tree, a1);
        }
        else if (cmd == "FIND") {
            in >> a1;
            a1 = upper(a1);
            vector<string> path;
            Airport* a = tree.find(a1, &path);
            cout << "Path: ";
            for (int i = 0; i < (int)path.size(); i++) {
                if (i > 0) cout << " -> ";
                cout << path[i];
            }
            if (a != nullptr) {
                cout << " (comparisons: " << path.size() << ")" << endl;
                cout << a->describe() << "  [" << a->icao << ", lat " << a->lat << ", lon " << a->lon << "]" << endl;
            } else {
                cout << " -> (NULL) not found (comparisons: " << path.size() << ")" << endl;
            }
        }
        else if (cmd == "MINMAX") {
            if (tree.size() == 0) cout << "Tree is empty" << endl;
            else {
                cout << "Minimum: " << tree.minNode()->describe() << endl;
                cout << "Maximum: " << tree.maxNode()->describe() << endl;
            }
        }
        else if (cmd == "REMOVE") {
            in >> a1;
            a1 = upper(a1);
            string info;
            if (tree.remove(a1, info))
                cout << "Deleted " << a1 << " (" << info << ") validate: " << (tree.validate() ? "OK" : "FAILED") << endl;
            else
                cout << a1 << " not found" << endl;
        }
        else if (cmd == "ADD") {
            in >> a1;
            a1 = upper(a1);
            string rest, part;
            getline(in, rest);
            vector<string> p;
            istringstream ss(rest);
            while (getline(ss, part, '|')) {
                size_t s = part.find_first_not_of(" ");
                size_t e = part.find_last_not_of(" ");
                p.push_back(s == string::npos ? "" : part.substr(s, e - s + 1));
            }
            while (p.size() < 3) p.push_back("Unknown");

            vector<string> fields = {"0", p[0], p[1], p[2], a1, "", "0", "0"};
            Airport a(fields);
            if (tree.insert(a)) cout << "Added " << a.describe() << " validate: " << (tree.validate() ? "OK" : "FAILED") << endl;
            else cout << a1 << " already exists" << endl;
        }
        else if (cmd == "LIST") {
            int limit = 1000000000;
            if (in >> a1) limit = atoi(a1.c_str());
            vector<Airport*> list = tree.inorderList();
            bool sorted = true;
            for (int i = 0; i + 1 < (int)list.size(); i++) {
                if (!(list[i]->iata < list[i + 1]->iata)) sorted = false;
            }
            for (int i = 0; i < (int)list.size() && i < limit; i++) cout << list[i]->describe() << endl;
            cout << list.size() << " airports, sorted check: " << (sorted ? "OK" : "FAILED") << endl;
        }
        else if (cmd == "SAVE") {
            in >> a1;
            cout << (tree.saveTree(a1) ? "Saved " + a1 : "Could not write " + a1) << endl;
        }
        else if (cmd == "VALIDATE") cout << "validate: " << (tree.validate() ? "OK" : "FAILED") << endl;
        else if (cmd == "RANGE") {
            in >> a1 >> a2;
            vector<Airport*> out;
            int visited = tree.range(upper(a1), upper(a2), out);
            for (int i = 0; i < (int)out.size() && i < 20; i++) cout << "  " << out[i]->describe() << endl;
            if (out.size() > 20) cout << "  ... (" << out.size() - 20 << " more)" << endl;
            cout << out.size() << " airports, " << visited << " nodes visited" << endl;
        }
        else if (cmd == "STATS") tree.printShape();
        else if (cmd == "REBALANCE") {
            tree.rebalance();
            tree.printShape();
        }
        else if (cmd == "EXPERIMENT") runExperiment(tree);
        else if (cmd == "TEST") runTests(tree);
        else cout << "Unknown command. Type help." << endl;
    }
    return 0;
}
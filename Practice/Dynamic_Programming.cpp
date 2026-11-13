#include <iostream>
#include <algorithm>
using namespace std;

int chargers(int n, int arrival[], int departure[]) {
    int i = 0; int j = 0; int counter = 0; int best = 0;

    while (i < n) {
        if (arrival[i] < departure[j]) {
            counter++;
            if (counter > best) best = counter;
            i++;
        } else {
            counter--;
            j++;
        }
    }

    return best;
}

void runTests() {
    // Example 1
    int n1 = 6;
    int arrivals1[n1] = {800, 815, 830, 845, 900, 1000};
    int departures1[n1] = {900, 845, 1000, 930, 1015, 1030};

    sort(arrivals1, arrivals1 + n1);
    sort(departures1, departures1 + n1);

    cout << "Case 1 - Chargers needed: " << chargers(n1, arrivals1, departures1) << endl;

    // Example 2
    int n2 = 4;
    int arrivals2[n2] = {900, 900, 900, 900};
    int departures2[n2] = {1000, 1000, 1000, 1000};

    sort(arrivals2, arrivals2 + n2);
    sort(departures2, departures2 + n2);

    cout << "Case 2 - Chargers needed: " << chargers(n2, arrivals2, departures2) << endl;

    // Example 3
    int n3 = 3;
    int arrivals3[n3] = {900, 1000, 1100};
    int departures3[n3] = {1000, 1100, 1200};

    sort(arrivals3, arrivals3 + n3);
    sort(departures3, departures3 + n3);

    cout << "Case 3 - Chargers needed: " << chargers(n3, arrivals3, departures3) << endl;
}

void customTest() {
    int n = 0;

    cout << "Number of vehicles: ";
    cin >> n;

    int arrivals[n] = {};
    int departures[n] = {};

    for (int i = 0; i < n; i++) {
        int t = 0;
        cout << "Arrival " << i + 1 << ": ";
        cin >> t;
        arrivals[i] = t;
    }
    for (int i = 0; i < n; i++) {
        int t = 0;
        cout << "Departure " << i + 1 << ": ";
        cin >> t;
        departures[i] = t;
    }

    sort(arrivals, arrivals + n);
    sort(departures, departures + n);

    cout << "Custom case - Chargers needed: " << chargers(n, arrivals, departures) << endl;
}

int main() {
    int c = 0;

    cout << "Run tests (0) or create custom test (1)? ";
    cin >> c;

    switch(c) {
        case 0:
            runTests();
            break;
        case 1:
            customTest();
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }
}
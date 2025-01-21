#include <iostream>
#include <chrono>
#include <mutex>
#include <queue>
#include <string>
#include "config_reader.h"
#include "A1.h"
#include "A2.h"
#include "B1.h"
#include "B2.h"

using namespace std;

int main() {
    auto config = read_config("config.txt");
    int X = config["X"];
    int y = config["y"];
    mutex mtx;
    queue<string> results;

    int choice;
    cout << "[1] A1 - immediate printing, search range" << endl;
	cout << "[2] A2 - deferred printing, search range" << endl;
	cout << "[3] B1 - immediate printing, linear search" << endl;
	cout << "[4] B2 - deferred printing, linear search" << endl;
    cout << "Select choice: ";
    cin >> choice;

    auto start = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char start_time_str[26];
    ctime_s(start_time_str, sizeof(start_time_str), &start);
    cout << "Start Time: " << start_time_str << endl;

    switch (choice) {
    case 1:
        cout << "Running Task A1..." << endl;
        taskA1(X, y, mtx);
        break;
    case 2:
        cout << "Running Task A2..." << endl;
        taskA2(X, y, mtx, results);
        break;
    case 3:
        cout << "Running Task B1..." << endl;
        taskB1(X, y, mtx);
        break;
    case 4:
        cout << "Running Task B2..." << endl;
        taskB2(X, y, mtx, results);
        break;
    default:
        cout << "Invalid choice." << endl;
        break;
    }

    auto end = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char end_time_str[26];
    ctime_s(end_time_str, sizeof(end_time_str), &end);
    cout << "End Time: " << end_time_str << endl;

    return 0;
}
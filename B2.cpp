#include "B2.h"
#include <vector>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>

using namespace std;

void taskB2(int X, int y, mutex& mtx, queue<string>& results) {
    vector<thread> threads;
    queue<int> numbers;
    vector<int> primes;

    // Initialize the queue with numbers from 1 to y
    for (int num = 1; num <= y; ++num) {
        numbers.push(num);
    }

    auto worker = [&numbers, &mtx, &primes]() {
        while (true) {
            int num;
            {
                lock_guard<mutex> lock(mtx);
                if (numbers.empty()) {
                    return;
                }
                num = numbers.front();
                numbers.pop();
            }

            vector<future<bool>> futures;
            int limit = num / 2 + 1;

            for (int i = 2; i < limit; ++i) {
                futures.push_back(async(launch::async, [i, num]() {
                    return num % i == 0;
                    }));
            }

            bool is_prime = true;
            for (auto& f : futures) {
                if (f.get()) {
                    is_prime = false;
                    break;
                }
            }

            if (is_prime && num > 1) {
                lock_guard<mutex> lock(mtx);
                primes.push_back(num);
            }
        }
        };

    // Print the initial statement
    cout << "Prime Numbers between 1 and " << y << ": ";

    // Create and start threads
    for (int i = 0; i < X; ++i) {
        threads.emplace_back(worker);
    }

    // Join threads
    for (auto& th : threads) {
        th.join();
    }

    lock_guard<mutex> lock(mtx);
    string result;
    for (const auto& prime : primes) {
        result += to_string(prime) + " ";
    }
    results.push(result);

    while (!results.empty()) {
        cout << results.front();
        results.pop();
    }
    cout << endl;
}


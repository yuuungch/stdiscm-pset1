#include "B1.h"
#include <vector>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <chrono>

using namespace std;

/*
* This function searches for prime numbers using divisibility testing and prints them immediately.
* @param X the number of threads to be created
* @param y the range of numbers to be searched
* @param mtx the mutex to be used for synchronization
*/
void taskB1(int X, int y, mutex& mtx) {
    vector<thread> threads;
    queue<int> numbers;

    // Initialize the queue with numbers from 1 to y
    for (int num = 1; num <= y; ++num) {
        numbers.push(num);
    }

    auto worker = [&numbers, &mtx](int thread_id) {
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

            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            char time_str[26];
            ctime_s(time_str, sizeof(time_str), &now);

            lock_guard<mutex> lock(mtx);
            if (is_prime && num > 1) {
                cout << "Thread " << thread_id << ": " << num << " at " << time_str;
            }
        }
        };

    // Create and start threads
    for (int i = 0; i < X; ++i) {
        threads.emplace_back(worker, i + 1);
    }

    // Join threads
    for (auto& th : threads) {
        th.join();
    }
}



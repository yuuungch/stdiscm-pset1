#include "B2.h"
#include "prime_operations.h"

void taskB2(int X, int y, mutex& mtx, queue<string>& results) {
    vector<thread> threads;

    for (int num = 1; num <= y; ++num) {
        threads.emplace_back(test_divisibility_deferred, num, num % X, ref(mtx), ref(results));
        if (threads.size() == X) {
            for (auto& th : threads) {
                th.join();
            }
            threads.clear();
        }
    }

    for (auto& th : threads) {
        th.join();
    }

    while (!results.empty()) {
        cout << results.front();
        results.pop();
    }
}
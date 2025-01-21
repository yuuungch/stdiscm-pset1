#include "B1.h"
#include "prime_operations.h"

void taskB1(int X, int y, mutex& mtx) {
    vector<thread> threads;

    for (int num = 1; num <= y; ++num) {
        threads.emplace_back(test_divisibility, num, num % X, ref(mtx));
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
}
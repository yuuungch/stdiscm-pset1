#include "A1.h"
#include "prime_operations.h"

void taskA1(int X, int y, mutex& mtx) {
    vector<thread> threads;
    int step = y / X;

    for (int i = 0; i < X; ++i) {
        int start = i * step + 1;
        int end = (i == X - 1) ? y : (i + 1) * step;
        threads.emplace_back(search_primes, start, end, i + 1, ref(mtx));
    }

    for (auto& th : threads) {
        th.join();
    }
}
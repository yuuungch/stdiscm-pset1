#include "A2.h"
#include "prime_operations.h"

/*
* This function looks for the prime numbers within a specific range and prints them as soon as they are finished.
* @param X the number of threads to be created
* @param y the range of numbers to be searched
* @param mtx the mutex to be used for synchronization
*/
void taskA2(int X, int y, mutex& mtx, queue<string>& results) {
    vector<thread> threads;
    int step = y / X;

    for (int i = 0; i < X; ++i) {
        int start = i * step + 1;
        int end = (i == X - 1) ? y : (i + 1) * step;
        threads.emplace_back(search_primes_deferred, start, end, i + 1, ref(mtx), ref(results));
    }

    for (auto& th : threads) {
        th.join();
    }

    while (!results.empty()) {
        cout << results.front();
        results.pop();
    }
}
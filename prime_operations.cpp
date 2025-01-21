#include "prime_operations.h"

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void search_primes(int start, int end, int thread_id, mutex& mtx) {
    for (int num = start; num <= end; ++num) {
        if (is_prime(num)) {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            char time_str[26];
            ctime_s(time_str, sizeof(time_str), &now);
            lock_guard<mutex> lock(mtx);
            cout << "Thread " << thread_id << ": " << num << " at " << time_str;
        }
    }
}

void search_primes_deferred(int start, int end, int thread_id, mutex& mtx, queue<string>& results) {
    for (int num = start; num <= end; ++num) {
        if (is_prime(num)) {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            char time_str[26];
            ctime_s(time_str, sizeof(time_str), &now);
            string result = "Thread " + to_string(thread_id) + ": " + to_string(num) + " at " + time_str;
            lock_guard<mutex> lock(mtx);
            results.push(result);
        }
    }
}

void test_divisibility(int num, int thread_id, mutex& mtx) {
    if (is_prime(num)) {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        char time_str[26];
        ctime_s(time_str, sizeof(time_str), &now);
        lock_guard<mutex> lock(mtx);
        cout << "Thread " << thread_id << ": " << num << " at " << time_str;
    }
}

void test_divisibility_deferred(int num, int thread_id, mutex& mtx, queue<string>& results) {
    if (is_prime(num)) {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        char time_str[26];
        ctime_s(time_str, sizeof(time_str), &now);
        string result = "Thread " + to_string(thread_id) + ": " + to_string(num) + " at " + time_str;
        lock_guard<mutex> lock(mtx);
        results.push(result);
    }
}
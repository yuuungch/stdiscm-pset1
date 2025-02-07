#include "prime_operations.h"
#include <vector>
#include <future>

/*
* This function checks if a number is a prime number
* @param n the number to be checked
*/
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

/*
* This function searches for prime numbers within a given range and prints them immediately
* @param start the start of the range
* @param end the end of the range
* @param thread_id the id of the thread
* @param mtx the mutex to be used for synchronization
*/
void search_primes(int start, int end, int thread_id, mutex& mtx) {
    for (int num = start; num <= end; ++num) {
        if (is_prime(num)) {
            auto now = chrono::system_clock::now();
            auto now_time_t = chrono::system_clock::to_time_t(now);
            auto now_ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
            auto now_ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()) % 1000000;

            char time_str[26];
            ctime_s(time_str, sizeof(time_str), &now_time_t);
            time_str[strlen(time_str) - 1] = '\0'; // Remove newline character

            lock_guard<mutex> lock(mtx);
            cout << time_str << " | " << setfill('0') << setw(3) << now_ms.count() << " ms " << setfill('0') << setw(6) << now_ns.count() << " ns | Thread " << thread_id << ": " << num << endl;
        }
    }
}

/*
* This function searches for prime numbers within a given range and prints them collectively
* @param start the start of the range
* @param end the end of the range
* @param thread_id the id of the thread
* @param mtx the mutex to be used for synchronization
* @param results the queue to store the results
*/
void search_primes_deferred(int start, int end, int thread_id, mutex& mtx, queue<string>& results) {
    for (int num = start; num <= end; ++num) {
        if (is_prime(num)) {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            char time_str[26];
            ctime_s(time_str, sizeof(time_str), &now);
            string result = to_string(num) + " ";
            lock_guard<mutex> lock(mtx);
            results.push(result);
        }
    }
}

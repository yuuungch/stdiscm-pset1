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
	// Worker function
    auto worker = [&numbers, &mtx, &primes]() {
        while (true) {
            int num;
            {
                lock_guard<mutex> lock(mtx);
                // If the queue is empty, return
                if (numbers.empty()) {
                    return;
                }

                // Get the number from the queue and remove it from the queue
                num = numbers.front();
                numbers.pop();
            }

            // Check if the number is prime
            vector<future<bool>> futures;

            // ALGORITHM UPDATE:
            // Check divisibility of num based on its square root
            // Explanation: a number that can divide num and is greater than num's square root also has a corresponding factor that is less than the square root.
            // Result: Less numbers to check per number for divisibility testing, faster runtime.
            for (int i = 2; i * i <= num; ++i) {
                // Check if num is divisible by i
                futures.push_back(async(launch::async, [i, num]() {
                    return num % i == 0;
                    }));
            }

            bool is_prime = true;
            // Check if any of the futures return true
            for (auto& f : futures) {
                if (f.get()) {
                    is_prime = false;
                    break;
                }
            }

            // If num is prime and greater than 1, add it to the list of primes
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
    // Store prime numbers in a string
    string result;
    for (const auto& prime : primes) {
        result += to_string(prime) + " ";
    }
    results.push(result);

    // Prints the prime numbers collectively
    while (!results.empty()) {
        cout << results.front();
        results.pop();
    }
    cout << endl;
}


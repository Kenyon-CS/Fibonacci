#include <iostream>
#include <iomanip>     // For std::setw and std::setprecision
#include <chrono>      // For timing
#include <limits>      // For input validation
#include <unordered_map>

// Iterative Fibonacci function
long long fib_iterative(long long n) {
    if (n <= 1) return n;

    long long prev = 0;
    long long curr = 1;

    for (long long i = 2; i <= n; ++i) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

// Global counter for memoized recursive calls
long long fib_memo_counter = 0;

// Memoized recursive Fibonacci function
long long fib_memoization(long long n, std::unordered_map<long long, long long>& fibmap) {
    fib_memo_counter++; // Increment counter every time function is called

    if (n <= 1) {
        return n;
    }

    // Check if result is already computed
    if (fibmap.find(n) != fibmap.end()) {
        return fibmap[n];
    }

    // Compute and store the result in the map
    long long result = fib_memoization(n - 1, fibmap) + fib_memoization(n - 2, fibmap);
    fibmap[n] = result;
    return result;
}

int main() {
    int n;

    // Prompt the user for input between 1 and 60
    do {
        std::cout << "Enter the number of terms of series (1 to 60): ";
        std::cin >> n;

        // Input validation
        if (std::cin.fail() || n < 1 || n > 60) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input! Please enter a number between 1 and 60.\n";
        } else {
            break; // Valid input
        }
    } while (true);

    // Table header
    std::cout << "\n#\tFib(i)\tIterative Time(ms)\tMemoized Time(ms)\tRecursive Calls\n";

    // For formatting output
    const int width_num = 5;
    const int width_fib = 15;
    const int width_time = 20;
    const int width_calls = 20;

    // Loop from 0 to n
    for (int i = 0; i <= n; ++i) {
        // Variables to store results and times
        long long fib_i, fib_memo;
        double time_i, time_memo;
        long long calls_memo;

        // Measure time for iterative function
        auto start_i = std::chrono::high_resolution_clock::now();
        fib_i = fib_iterative(i);
        auto end_i = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_i = end_i - start_i;
        time_i = elapsed_i.count();

        // Reset counter and map for memoized recursive function
        fib_memo_counter = 0;
        std::unordered_map<long long, long long> fibmap;

        // Measure time for memoized recursive function
        auto start_memo = std::chrono::high_resolution_clock::now();
        fib_memo = fib_memoization(i, fibmap);
        auto end_memo = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_memo = end_memo - start_memo;
        time_memo = elapsed_memo.count();

        // Get the number of recursive calls
        calls_memo = fib_memo_counter;

        // Output the results in a formatted way
        std::cout << std::setw(width_num) << i
                  << std::setw(width_fib) << fib_i
                  << std::setw(width_time) << std::fixed << std::setprecision(3) << time_i
                  << std::setw(width_time) << std::fixed << std::setprecision(3) << time_memo
                  << std::setw(width_calls) << calls_memo
                  << '\n';
    }

    return 0;
}

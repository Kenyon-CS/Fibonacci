#include <iostream>
#include <iomanip>    // For std::setw and std::setprecision
#include <chrono>     // For timing
#include <limits>     // For std::numeric_limits

// Global counter for fib_recursive calls
long long fib_recursive_counter = 0;

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

// Recursive Fibonacci function with counter
long long fib_recursive(long long n) {
    fib_recursive_counter++; // Increment counter every time function is called

    if (n <= 1) {
        return n;
    } else {
        return fib_recursive(n - 1) + fib_recursive(n - 2);
    }
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
    std::cout << "\n#\tFibi\tTime(ms)\tFibr\tTime(ms)\tRecursive Calls\n";

    // For formatting output
    const int width_num = 5;
    const int width_fib = 15;
    const int width_time = 15;
    const int width_calls = 15;

    // Loop from 0 to n
    for (int i = 0; i <= n; ++i) {
        // Variables to store results and times
        long long fib_i, fib_r;
        double time_i, time_r;
        long long calls_r;

        // Measure time for iterative function
        auto start_i = std::chrono::high_resolution_clock::now();
        fib_i = fib_iterative(i);
        auto end_i = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_i = end_i - start_i;
        time_i = elapsed_i.count();

        // Reset counter for recursive function
        fib_recursive_counter = 0;

        // Measure time for recursive function
        auto start_r = std::chrono::high_resolution_clock::now();
        fib_r = fib_recursive(i);
        auto end_r = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_r = end_r - start_r;
        time_r = elapsed_r.count();

        // Get the number of recursive calls
        calls_r = fib_recursive_counter;

        // Output the results in a formatted way
        std::cout << std::setw(width_num) << i
                  << std::setw(width_fib) << fib_i
                  << std::setw(width_time) << std::fixed << std::setprecision(3) << time_i
                  << std::setw(width_fib) << fib_r
                  << std::setw(width_time) << std::fixed << std::setprecision(3) << time_r
                  << std::setw(width_calls) << calls_r
                  << '\n';

        // Optional: Stop recursive computation if it takes too long
        if (time_r > 10000) { // If recursive time exceeds 10 seconds
            std::cout << "\nRecursive computation is taking too long beyond this point.\n";
            break;
        }
    }

    return 0;
}

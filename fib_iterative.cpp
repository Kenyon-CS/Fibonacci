#include <iostream>

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

int main() {
    long long n;

    std::cout << "Enter a non-negative integer to compute its Fibonacci number: ";
    std::cin >> n;

    if (n < 0) {
        std::cerr << "Invalid input! Please enter a non-negative integer." << std::endl;
        return 1;
    }

    long long result = fib_iterative(n);
    std::cout << "Fibonacci number " << n << " is " << result << std::endl;

    return 0;
}

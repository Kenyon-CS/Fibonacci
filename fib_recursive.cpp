#include <iostream>

long long fib_recursive(long long n) {
  if ((n == 1) || (n == 0)) {
    return (n);
  } else {
    return (fibr(n - 1) + fibr(n - 2));
  }
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

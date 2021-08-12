// C++ program demonstrates the use of
// constexpr
#include <iostream>
using namespace std;
  
// Constexpr function if replaced with
// consteval, program works fine
constexpr int fib(int n)
{
    // Base Case
    if (n <= 1)
        return n;
  
    // Find the Fibonacci Number
    return fib(n - 1) + fib(n - 2);
}
  
// Driver Code
int main()
{
    // Constant expression evaluated
    // at compile time
    constexpr int val = fib(20);
  
    cout << "The fibonacci number "
         << "is: " << val << "\n";
  
    return 0;
}

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
============================== RECURSION IN C++ ==============================

Recursion is a technique where a function solves a problem by calling itself
on a smaller version of the same problem.

Every recursive solution should have:
1) Base Case  : The smallest/terminating condition where recursion stops.
2) Recursive Case: The rule that reduces the problem toward the base case.

Why recursion works:
- Each call is pushed onto the call stack.
- When a base case is reached, calls return one by one (stack unwinding).

Template:
    returnType solve(problem) {
        if (base_condition) return base_answer;
        // reduce problem
        return combine(current_state, solve(smaller_problem));
    }

Common mistakes:
- Missing base case -> infinite recursion.
- Not reducing the input -> stack overflow.
- Inefficient repeated work (e.g., plain Fibonacci) -> exponential time.

When to prefer recursion:
- Tree/graph traversal (DFS).
- Divide-and-conquer (merge sort, quick sort).
- Backtracking (maze, N-Queens, subsets).

When iteration may be better:
- Very deep recursion (risk of stack overflow).
- Problems naturally solved with loops and constant memory.

==============================================================================
PROBLEMS IMPLEMENTED (All recursive):
1) Print numbers from 1 to n
2) Sum from 1 to n
3) Factorial
4) Sum of digits
5) Count digits
6) n-th Fibonacci term
7) a^b (fast exponentiation)
8) Print array elements
9) Largest element in array
10) Largest and smallest element in array
11) Palindrome check
12) Remove spaces + convert uppercase to lowercase
13) Traverse path in 2D matrix from source to destination and outline path
==============================================================================
*/

void print1ToN(int n) {
    if (n <= 0) {
        return;
    }
    print1ToN(n - 1);
    cout << n << " ";
}

long long sum1ToN(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum1ToN(n - 1);
}

long long factorial(int n) {
    if (n < 0) {
        throw invalid_argument("Factorial is undefined for negative numbers.");
    }
    if (n <= 1) {
        return 1;
    }
    return 1LL * n * factorial(n - 1);
}

int sumOfDigits(long long n) {
    n = llabs(n);
    if (n < 10) {
        return static_cast<int>(n);
    }
    return static_cast<int>(n % 10) + sumOfDigits(n / 10);
}

int countDigits(long long n) {
    n = llabs(n);
    if (n < 10) {
        return 1;
    }
    return 1 + countDigits(n / 10);
}

long long fibonacci(int n) {
    if (n < 0) {
        throw invalid_argument("Fibonacci index cannot be negative.");
    }
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

long long power(long long a, long long b) {
    if (b < 0) {
        throw invalid_argument("This integer power function expects non-negative exponent.");
    }
    if (b == 0) {
        return 1;
    }

    long long half = power(a, b / 2);
    long long square = half * half;

    if (b % 2 == 0) {
        return square;
    }
    return a * square;
}

void printArray(const vector<int> &arr, size_t index = 0) {
    if (index >= arr.size()) {
        return;
    }
    cout << arr[index] << " ";
    printArray(arr, index + 1);
}

int largestElement(const vector<int> &arr, size_t index = 0) {
    if (arr.empty()) {
        throw invalid_argument("Array is empty.");
    }
    if (index == arr.size() - 1) {
        return arr[index];
    }
    return max(arr[index], largestElement(arr, index + 1));
}

pair<int, int> minMaxElement(const vector<int> &arr, size_t index = 0) {
    if (arr.empty()) {
        throw invalid_argument("Array is empty.");
    }
    if (index == arr.size() - 1) {
        return {arr[index], arr[index]};
    }

    pair<int, int> rest = minMaxElement(arr, index + 1);
    int currentMax = max(arr[index], rest.first);
    int currentMin = min(arr[index], rest.second);

    return {currentMax, currentMin};
}

bool isPalindrome(const string &text, int left, int right) {
    if (left >= right) {
        return true;
    }
    if (text[left] != text[right]) {
        return false;
    }
    return isPalindrome(text, left + 1, right - 1);
}

string removeSpacesAndToLower(const string &text, size_t index = 0) {
    if (index >= text.size()) {
        return "";
    }

    char current = text[index];
    string rest = removeSpacesAndToLower(text, index + 1);

    if (isspace(static_cast<unsigned char>(current))) {
        return rest;
    }

    char lowered = static_cast<char>(tolower(static_cast<unsigned char>(current)));
    return string(1, lowered) + rest;
}

bool validCell(const vector<vector<int>> &grid, int row, int col) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    return row >= 0 && row < rows && col >= 0 && col < cols;
}

bool findPathDFS(const vector<vector<int>> &grid,
                 int row,
                 int col,
                 int destRow,
                 int destCol,
                 vector<vector<int>> &visited,
                 vector<vector<int>> &path) {
    if (!validCell(grid, row, col) || grid[row][col] == 0 || visited[row][col] == 1) {
        return false;
    }

    visited[row][col] = 1;
    path[row][col] = 1;

    if (row == destRow && col == destCol) {
        return true;
    }

    static const int dRow[4] = {-1, 1, 0, 0};
    static const int dCol[4] = {0, 0, -1, 1};

    for (int dir = 0; dir < 4; dir++) {
        int nextRow = row + dRow[dir];
        int nextCol = col + dCol[dir];

        if (findPathDFS(grid, nextRow, nextCol, destRow, destCol, visited, path)) {
            return true;
        }
    }

    path[row][col] = 0; // backtrack if this route fails
    return false;
}

vector<vector<int>> outlinePath(const vector<vector<int>> &grid,
                                pair<int, int> source,
                                pair<int, int> destination) {
    if (grid.empty() || grid[0].empty()) {
        return {};
    }

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    if (source.first < 0 || source.first >= rows || source.second < 0 || source.second >= cols ||
        destination.first < 0 || destination.first >= rows || destination.second < 0 || destination.second >= cols) {
        throw invalid_argument("Source or destination is outside matrix bounds.");
    }

    vector<vector<int>> visited(rows, vector<int>(cols, 0));
    vector<vector<int>> path(rows, vector<int>(cols, 0));

    bool found = findPathDFS(grid,
                             source.first,
                             source.second,
                             destination.first,
                             destination.second,
                             visited,
                             path);

    if (!found) {
        return {};
    }
    return path;
}

void printMatrix(const vector<vector<int>> &matrix) {
    for (const auto &row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << "\n";
    }
}

int main() {
    try {
        int n = 5;
        cout << "1) Print 1 to n (n = " << n << "): ";
        print1ToN(n);
        cout << "\n\n";

        cout << "2) Sum 1 to n: " << sum1ToN(n) << "\n\n";

        cout << "3) Factorial of " << n << ": " << factorial(n) << "\n\n";

        long long number = 12345;
        cout << "4) Sum of digits of " << number << ": " << sumOfDigits(number) << "\n\n";

        cout << "5) Count digits of " << number << ": " << countDigits(number) << "\n\n";

        int fibIndex = 8;
        cout << "6) Fibonacci term at n = " << fibIndex << ": " << fibonacci(fibIndex) << "\n\n";

        long long a = 2, b = 10;
        cout << "7) " << a << "^" << b << " = " << power(a, b) << "\n\n";

        vector<int> arr = {7, 2, 15, 4, 9, 1};

        cout << "8) Array elements: ";
        printArray(arr);
        cout << "\n\n";

        cout << "9) Largest element: " << largestElement(arr) << "\n\n";

        pair<int, int> maxMin = minMaxElement(arr);
        cout << "10) Largest: " << maxMin.first << ", Smallest: " << maxMin.second << "\n\n";

        string palindromeText = "madam";
        cout << "11) Is \"" << palindromeText << "\" palindrome? "
             << (isPalindrome(palindromeText, 0, static_cast<int>(palindromeText.size()) - 1) ? "Yes" : "No")
             << "\n\n";

        string mixedText = "HeLLo WoRLD  Cpp";
        cout << "12) Remove spaces + lowercase:\n";
        cout << "Original : " << mixedText << "\n";
        cout << "Converted: " << removeSpacesAndToLower(mixedText) << "\n\n";

        vector<vector<int>> grid = {
            {1, 1, 0, 1, 1},
            {0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 1, 1},
            {1, 1, 1, 0, 1}
        };

        pair<int, int> source, destination;
        cout << "13) Matrix path traversal (cells with 1 are walkable, 0 blocked).\n";
        cout << "Enter source row and col: ";
        cin >> source.first >> source.second;
        cout << "Enter destination row and col: ";
        cin >> destination.first >> destination.second;

        vector<vector<int>> path = outlinePath(grid, source, destination);

        if (path.empty()) {
            cout << "No path exists between source and destination.\n";
        } else {
            cout << "Path outlined matrix (1 means selected path):\n";
            printMatrix(path);
        }
    } catch (const exception &error) {
        cout << "Error: " << error.what() << "\n";
    }

    return 0;
}
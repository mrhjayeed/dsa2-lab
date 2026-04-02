// ============================================================
//   C++ TEMPLATES — COMPLETE DETAILED GUIDE
//   Topics Covered:
//     1.  Why Templates? (The Problem They Solve)
//     2.  Function Templates
//     3.  Function Template with Multiple Type Parameters
//     4.  Template with Non-Type Parameters
//     5.  Function Template Specialization (Full)
//     6.  Class Templates
//     7.  Class Template with Multiple Type Parameters
//     8.  Class Template Member Functions (Defined Outside)
//     9.  Class Template Specialization (Full)
//     10. Class Template Partial Specialization
//     11. Default Template Parameters
//     12. Template with STL / Standard Types
//     13. Variadic Templates (C++11)
//     14. Template and Inheritance
//     15. Quick Reference Summary
// ============================================================

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


// ============================================================
// SECTION 1: WHY TEMPLATES?
// ============================================================
// Without templates you'd need to write the same logic for
// every data type:
//
//   int    addInt(int a, int b)       { return a + b; }
//   double addDouble(double a, double b) { return a + b; }
//   float  addFloat(float a, float b)    { return a + b; }
//
// Templates let the COMPILER generate those versions for you
// from a single generic definition. This is called:
//   "Generic Programming"
//
// Templates are resolved entirely at COMPILE TIME — zero
// runtime overhead compared to virtual dispatch.
// ============================================================


// ============================================================
// SECTION 2: FUNCTION TEMPLATE — BASIC
// ============================================================
// Syntax:
//   template <typename T>        // or: template <class T>
//   ReturnType functionName(T param) { ... }
//
// 'T' is a placeholder for any data type.
// When you call the function the compiler deduces T from the
// argument type, OR you can specify it explicitly:
//   add<int>(3, 5)
// ============================================================

template <typename T>
T add(T a, T b) {
    return a + b;
}

// Works with any type that supports '<'
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

// Works with any type that supports '<<' (printable types)
template <typename T>
void printValue(const T& val) {
    cout << "  Value: " << val << "\n";
}

// Swap two values of any type
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


// ============================================================
// SECTION 3: FUNCTION TEMPLATE — MULTIPLE TYPE PARAMETERS
// ============================================================
// You can have more than one type placeholder.
// Each can be independently deduced or explicitly specified.
// ============================================================

template <typename T1, typename T2>
void displayPair(const T1& first, const T2& second) {
    cout << "  Pair -> First: " << first
         << " | Second: " << second << "\n";
}

// Return type can also differ — use 'auto' (C++14) or explicit
template <typename T1, typename T2>
double multiply(T1 a, T2 b) {
    return static_cast<double>(a) * static_cast<double>(b);
}


// ============================================================
// SECTION 4: NON-TYPE TEMPLATE PARAMETERS
// ============================================================
// Template parameters don't have to be types!
// They can be compile-time constant integers, pointers, etc.
// The value is fixed at compile time — no runtime cost.
// ============================================================

// A fixed-size array wrapper using a non-type parameter
template <typename T, int SIZE>
void fillAndPrint(T fillValue) {
    T arr[SIZE];                      // SIZE is a compile-time constant
    for (int i = 0; i < SIZE; i++)
        arr[i] = fillValue;

    cout << "  Array[" << SIZE << "] filled with '" << fillValue << "': ";
    for (int i = 0; i < SIZE; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

// Raise a number to a COMPILE-TIME power using recursion
template <int POWER>
double power(double base) {
    return base * power<POWER - 1>(base);
}

// Base case specialization — POWER = 0 → always returns 1
template <>
double power<0>(double base) {
    (void)base;   // suppress unused-parameter warning
    return 1.0;
}


// ============================================================
// SECTION 5: FUNCTION TEMPLATE SPECIALIZATION (FULL)
// ============================================================
// Sometimes the generic template doesn't work correctly for
// a specific type. You can write a SPECIALIZED version that
// overrides the generic one for that exact type.
//
// Syntax:
//   template <>          // empty angle brackets
//   ReturnType funcName<SpecificType>(SpecificType param) { ... }
// ============================================================

// Generic: compare two values
template <typename T>
bool areEqual(T a, T b) {
    return a == b;
}

// Specialization for 'const char*' — pointer comparison won't
// correctly compare C-strings, so we write a custom version.
template <>
bool areEqual<const char*>(const char* a, const char* b) {
    // Compare character-by-character
    while (*a && *b) {
        if (*a != *b) return false;
        ++a; ++b;
    }
    return (*a == '\0' && *b == '\0');
}

// Specialization for 'double' — handle floating-point epsilon
template <>
bool areEqual<double>(double a, double b) {
    const double EPSILON = 1e-9;
    double diff = a - b;
    return (diff < 0 ? -diff : diff) < EPSILON;
}


// ============================================================
// SECTION 6: CLASS TEMPLATE — BASIC
// ============================================================
// Just like function templates, but for entire classes.
// Every member function inside the class body has access to T.
//
// Syntax:
//   template <typename T>
//   class MyClass { ... };
//
// To create an object you MUST specify the type explicitly:
//   MyClass<int> obj;
//   MyClass<string> obj2;
// (Unlike function templates, the type can't be auto-deduced
//  from a constructor in older standards.)
// ============================================================

template <typename T>
class Box {
private:
    T value;
    string label;

public:
    // Constructor
    Box(const T& val, const string& lbl = "box")
        : value(val), label(lbl) {
        cout << "[Box Constructor] Created box '" << label
             << "' holding: " << value << "\n";
    }

    // Destructor
    ~Box() {
        cout << "[Box Destructor]  Destroyed box '" << label << "'\n";
    }

    // Getters
    T       getValue() const { return value; }
    string  getLabel() const { return label; }

    // Setter
    void setValue(const T& val) { value = val; }

    // Display
    void display() const {
        cout << "  Box['" << label << "'] = " << value << "\n";
    }

    // Compare two Box objects of the same type
    bool isGreaterThan(const Box<T>& other) const {
        return value > other.value;
    }
};


// ============================================================
// SECTION 7: CLASS TEMPLATE — MULTIPLE TYPE PARAMETERS
// ============================================================
// A Pair class that can hold two values of (possibly) different
// types — similar to std::pair in the STL.
// ============================================================

template <typename K, typename V>
class Pair {
private:
    K key;
    V value;

public:
    Pair(const K& k, const V& v) : key(k), value(v) {}

    K getKey()   const { return key;   }
    V getValue() const { return value; }

    void display() const {
        cout << "  Pair { key: " << key << ", value: " << value << " }\n";
    }

    void setKey(const K& k)   { key   = k; }
    void setValue(const V& v) { value = v; }
};


// ============================================================
// SECTION 8: CLASS TEMPLATE — MEMBER FUNCTIONS DEFINED OUTSIDE
// ============================================================
// When you define member functions OUTSIDE the class body,
// each function must carry its own template declaration.
//
// Syntax:
//   template <typename T>
//   ReturnType ClassName<T>::methodName(params) { ... }
// ============================================================

template <typename T>
class Stack {
private:
    T*  data;       // dynamic array
    int top;        // index of top element
    int capacity;   // max elements

public:
    Stack(int cap = 10);   // declaration only
    ~Stack();

    void push(const T& item);
    T    pop();
    T    peek() const;
    bool isEmpty() const;
    bool isFull()  const;
    int  size()    const;
    void display() const;
};

// --- Constructor (defined outside) ---
template <typename T>
Stack<T>::Stack(int cap)
    : top(-1), capacity(cap)
{
    data = new T[capacity];
    cout << "[Stack] Created stack with capacity " << capacity << "\n";
}

// --- Destructor ---
template <typename T>
Stack<T>::~Stack() {
    delete[] data;
    cout << "[Stack] Stack destroyed, memory freed.\n";
}

// --- push ---
template <typename T>
void Stack<T>::push(const T& item) {
    if (isFull())
        throw overflow_error("Stack overflow! Cannot push.");
    data[++top] = item;
}

// --- pop ---
template <typename T>
T Stack<T>::pop() {
    if (isEmpty())
        throw underflow_error("Stack underflow! Cannot pop.");
    return data[top--];
}

// --- peek ---
template <typename T>
T Stack<T>::peek() const {
    if (isEmpty())
        throw underflow_error("Stack is empty! Cannot peek.");
    return data[top];
}

// --- isEmpty ---
template <typename T>
bool Stack<T>::isEmpty() const { return top == -1; }

// --- isFull ---
template <typename T>
bool Stack<T>::isFull()  const { return top == capacity - 1; }

// --- size ---
template <typename T>
int Stack<T>::size() const { return top + 1; }

// --- display ---
template <typename T>
void Stack<T>::display() const {
    if (isEmpty()) {
        cout << "  Stack is empty.\n";
        return;
    }
    cout << "  Stack (top -> bottom): ";
    for (int i = top; i >= 0; i--)
        cout << data[i] << " ";
    cout << "\n";
}


// ============================================================
// SECTION 9: CLASS TEMPLATE FULL SPECIALIZATION
// ============================================================
// Like function specialization, but for an entire class.
// You write a COMPLETELY separate class for that one type.
// The compiler picks the specialized version when the type matches.
//
// Syntax:
//   template <>       // empty angle brackets
//   class ClassName<SpecificType> { ... };
// ============================================================

// Generic Box<T> already defined above (Section 6).
// Now let's fully specialize Box for 'bool' —
// booleans deserve a special display (true/false instead of 1/0).

template <>
class Box<bool> {
private:
    bool  value;
    string label;

public:
    Box(bool val, const string& lbl = "bool-box")
        : value(val), label(lbl) {
        cout << "[Box<bool> Specialization] Created '" << label << "'\n";
    }

    ~Box() {
        cout << "[Box<bool> Specialization] Destroyed '" << label << "'\n";
    }

    bool   getValue() const { return value; }
    string getLabel() const { return label; }

    void display() const {
        cout << "  Box<bool>['" << label << "'] = "
             << (value ? "TRUE" : "FALSE") << "\n";
    }

    void toggle() { value = !value; }   // unique method for bool only
};


// ============================================================
// SECTION 10: CLASS TEMPLATE PARTIAL SPECIALIZATION
// ============================================================
// You can specialize a class for a PATTERN of types rather
// than one exact type.
// For example: specialize for ANY pointer type, or for
// Pair<T, T> (same type for both).
//
// Only CLASS templates support partial specialization.
// Function templates use overloading instead.
// ============================================================

// Generic Pair<K,V> already defined in Section 7.
// Partial specialization for Pair<T, T> (same type both sides):

template <typename T>
class Pair<T, T> {            // <-- T,T pattern
private:
    T first;
    T second;

public:
    Pair(const T& a, const T& b) : first(a), second(b) {}

    T getFirst()  const { return first;  }
    T getSecond() const { return second; }

    // Extra method available only when both types are the same
    T sum() const { return first + second; }

    bool areSame() const { return first == second; }

    void display() const {
        cout << "  Pair<T,T> { " << first << ", " << second << " }"
             << " | sum=" << sum()
             << " | same=" << (areSame() ? "yes" : "no") << "\n";
    }
};


// ============================================================
// SECTION 11: DEFAULT TEMPLATE PARAMETERS
// ============================================================
// Like default function arguments, template parameters can
// have default types or values.
// ============================================================

template <typename T = int, int SIZE = 5>
class FixedArray {
private:
    T arr[SIZE];
    int count;

public:
    FixedArray() : count(0) {
        for (int i = 0; i < SIZE; i++) arr[i] = T{};  // zero-initialize
    }

    bool add(const T& val) {
        if (count >= SIZE) return false;
        arr[count++] = val;
        return true;
    }

    void display() const {
        cout << "  FixedArray<" << SIZE << ">: [ ";
        for (int i = 0; i < count; i++) cout << arr[i] << " ";
        cout << "]\n";
    }

    int  size()  const { return count;  }
    int  maxSize() const { return SIZE; }
    T    get(int i) const { return arr[i]; }
};


// ============================================================
// SECTION 12: TEMPLATES WITH STL / STANDARD TYPES
// ============================================================
// Templates work seamlessly with standard types like string,
// as long as the operations used (==, +, >, <<) are defined.
// ============================================================

template <typename T>
T clamp(T val, T lo, T hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

template <typename T>
void reverseArray(T arr[], int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--)
        swapValues(arr[i], arr[j]);
}

template <typename T>
int linearSearch(T arr[], int size, const T& target) {
    for (int i = 0; i < size; i++)
        if (arr[i] == target) return i;
    return -1;   // not found
}

template <typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j+1])
                swapValues(arr[j], arr[j+1]);
}


// ============================================================
// SECTION 13: VARIADIC TEMPLATES (C++11)
// ============================================================
// A variadic template accepts ZERO OR MORE template arguments
// of any types. The ellipsis (...) is the key syntax.
//
// 'Args...'   — template parameter pack
// 'args...'   — function parameter pack
// sizeof...(args) — number of arguments in the pack
//
// Expansion uses RECURSION:
//   base case (0 or 1 args) + recursive case (peel one arg off).
// ============================================================

// Base case: nothing to print
void printAll() {
    cout << "\n";
}

// Recursive case: print first arg, then recurse on the rest
template <typename First, typename... Rest>
void printAll(const First& first, const Rest&... rest) {
    cout << first;
    if (sizeof...(rest) > 0) cout << ", ";
    printAll(rest...);   // peel one arg, recurse
}

// Variadic sum — all args must support '+'
template <typename T>
T sumAll(T only) {
    return only;   // base case: single value
}

template <typename T, typename... Args>
T sumAll(T first, Args... args) {
    return first + sumAll(args...);
}

// Count arguments at compile time
template <typename... Args>
constexpr int countArgs(Args...) {
    return sizeof...(Args);
}


// ============================================================
// SECTION 14: TEMPLATES AND INHERITANCE
// ============================================================
// A template class can serve as a base class.
// Derived class can be templated or concrete.
// ============================================================

// Generic base: a printable item
template <typename T>
class Printable {
protected:
    T data;

public:
    Printable(const T& d) : data(d) {}
    virtual void print() const {
        cout << "  [Printable] data = " << data << "\n";
    }
    virtual ~Printable() {}
};

// Derived template class — extends Printable<T>
template <typename T>
class TaggedItem : public Printable<T> {
private:
    string tag;

public:
    TaggedItem(const T& d, const string& t)
        : Printable<T>(d), tag(t) {}

    void print() const override {
        cout << "  [TaggedItem] tag='" << tag
             << "', data=" << this->data << "\n";
    }

    string getTag() const { return tag; }
};


// ============================================================
//  MAIN — Demonstrating Every Section
// ============================================================
int main() {

    cout << "=======================================================\n";
    cout << "  C++ TEMPLATES — COMPLETE DEMONSTRATION\n";
    cout << "=======================================================\n\n";


    // ----------------------------------------------------------
    // Section 2: Function Templates
    // ----------------------------------------------------------
    cout << "--- Section 2: Function Templates ---\n";

    // Type deduced automatically from arguments
    cout << "  add(3, 7)          = " << add(3, 7)          << "\n";
    cout << "  add(1.5, 2.5)      = " << add(1.5, 2.5)      << "\n";
    cout << "  add<string>(\"Hi \",\"C++\") = " << add<string>("Hi ", "C++") << "\n";

    cout << "  findMax(10, 25)    = " << findMax(10, 25)    << "\n";
    cout << "  findMax('z', 'a')  = " << findMax('z', 'a')  << "\n";

    printValue(42);
    printValue(3.14);
    printValue(string("Templates!"));

    int x = 10, y = 20;
    cout << "  Before swap: x=" << x << " y=" << y << "\n";
    swapValues(x, y);
    cout << "  After  swap: x=" << x << " y=" << y << "\n";


    // ----------------------------------------------------------
    // Section 3: Multiple Type Parameters
    // ----------------------------------------------------------
    cout << "\n--- Section 3: Multiple Type Parameters ---\n";
    displayPair(1, "one");
    displayPair(3.14, true);
    displayPair(string("Score"), 99);
    cout << "  multiply(3, 2.5) = " << multiply(3, 2.5) << "\n";


    // ----------------------------------------------------------
    // Section 4: Non-Type Template Parameters
    // ----------------------------------------------------------
    cout << "\n--- Section 4: Non-Type Template Parameters ---\n";
    fillAndPrint<int, 5>(7);
    fillAndPrint<char, 4>('*');
    cout << "  power<3>(2.0)  = " << power<3>(2.0)  << "\n";   // 8
    cout << "  power<4>(3.0)  = " << power<4>(3.0)  << "\n";   // 81
    cout << "  power<0>(99.0) = " << power<0>(99.0) << "\n";   // 1


    // ----------------------------------------------------------
    // Section 5: Function Template Specialization
    // ----------------------------------------------------------
    cout << "\n--- Section 5: Function Template Specialization ---\n";
    cout << "  areEqual(5, 5)             = " << areEqual(5, 5)                    << "\n";
    cout << "  areEqual(5, 6)             = " << areEqual(5, 6)                    << "\n";
    cout << "  areEqual<double>(0.1+0.2, 0.3) = " << areEqual<double>(0.1+0.2, 0.3) << "\n";
    cout << "  areEqual<const char*>(\"abc\",\"abc\") = "
         << areEqual<const char*>("abc", "abc") << "\n";
    cout << "  areEqual<const char*>(\"abc\",\"xyz\") = "
         << areEqual<const char*>("abc", "xyz") << "\n";


    // ----------------------------------------------------------
    // Section 6: Class Template — Box
    // ----------------------------------------------------------
    cout << "\n--- Section 6: Class Template (Box) ---\n";
    {
        Box<int>    intBox(42, "IntBox");
        Box<double> dblBox(3.14, "DblBox");
        Box<string> strBox(string("Hello"), "StrBox");

        intBox.display();
        dblBox.display();
        strBox.display();

        cout << "  intBox > dblBox? (comparing int vs double via int box): ";
        Box<int> another(10, "Another");
        cout << (intBox.isGreaterThan(another) ? "yes" : "no") << "\n";
    }   // <-- destructors fire here


    // ----------------------------------------------------------
    // Section 7: Multiple Type Parameters — Pair
    // ----------------------------------------------------------
    cout << "\n--- Section 7: Class Template Multiple Types (Pair<K,V>) ---\n";
    Pair<string, int>    studentGrade("Alice", 95);
    Pair<int, double>    idScore(101, 88.5);
    Pair<string, string> dict("apple", "a fruit");

    studentGrade.display();
    idScore.display();
    dict.display();


    // ----------------------------------------------------------
    // Section 8: Stack (members defined outside)
    // ----------------------------------------------------------
    cout << "\n--- Section 8: Stack<T> (members outside class) ---\n";
    {
        Stack<int> intStack(5);
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        intStack.display();
        cout << "  Peek: " << intStack.peek() << "\n";
        cout << "  Pop:  " << intStack.pop()  << "\n";
        intStack.display();

        Stack<string> strStack(3);
        strStack.push("alpha");
        strStack.push("beta");
        strStack.push("gamma");
        strStack.display();
    }


    // ----------------------------------------------------------
    // Section 9: Full Class Specialization — Box<bool>
    // ----------------------------------------------------------
    cout << "\n--- Section 9: Full Class Specialization (Box<bool>) ---\n";
    {
        Box<bool> flagBox(true, "FlagBox");
        flagBox.display();
        flagBox.toggle();
        flagBox.display();
    }


    // ----------------------------------------------------------
    // Section 10: Partial Specialization — Pair<T,T>
    // ----------------------------------------------------------
    cout << "\n--- Section 10: Partial Specialization (Pair<T,T>) ---\n";
    Pair<int, int>    intPair(10, 20);
    Pair<double, double> dblPair(1.5, 2.5);

    intPair.display();    // uses Pair<T,T> specialization
    dblPair.display();

    // Different types still use the generic Pair<K,V>
    Pair<int, string> mixed(1, "one");
    mixed.display();


    // ----------------------------------------------------------
    // Section 11: Default Template Parameters — FixedArray
    // ----------------------------------------------------------
    cout << "\n--- Section 11: Default Template Parameters (FixedArray) ---\n";

    FixedArray<> defaultArr;          // T=int, SIZE=5
    defaultArr.add(1); defaultArr.add(2); defaultArr.add(3);
    defaultArr.display();

    FixedArray<double, 3> dblArr;
    dblArr.add(1.1); dblArr.add(2.2); dblArr.add(3.3);
    dblArr.display();

    FixedArray<string, 4> strArr;
    strArr.add("C++"); strArr.add("Templates"); strArr.add("Rock");
    strArr.display();


    // ----------------------------------------------------------
    // Section 12: Templates with STL / standard types
    // ----------------------------------------------------------
    cout << "\n--- Section 12: Templates with STL / Standard Types ---\n";

    cout << "  clamp(15, 0, 10)     = " << clamp(15, 0, 10)       << "\n";
    cout << "  clamp(-5, 0, 10)     = " << clamp(-5, 0, 10)       << "\n";
    cout << "  clamp(5, 0, 10)      = " << clamp(5, 0, 10)        << "\n";
    cout << "  clamp(3.7, 0.0, 3.5) = " << clamp(3.7, 0.0, 3.5)  << "\n";

    int nums[] = {5, 3, 8, 1, 9, 2};
    int sz = 6;
    cout << "  Before sort: ";
    for (int i = 0; i < sz; i++) cout << nums[i] << " ";
    cout << "\n";
    bubbleSort(nums, sz);
    cout << "  After  sort: ";
    for (int i = 0; i < sz; i++) cout << nums[i] << " ";
    cout << "\n";

    reverseArray(nums, sz);
    cout << "  After reverse: ";
    for (int i = 0; i < sz; i++) cout << nums[i] << " ";
    cout << "\n";

    int idx = linearSearch(nums, sz, 8);
    cout << "  Search for 8: index = " << idx << "\n";

    string words[] = {"mango", "apple", "banana"};
    bubbleSort(words, 3);
    cout << "  Sorted words: ";
    for (auto& w : words) cout << w << " ";
    cout << "\n";


    // ----------------------------------------------------------
    // Section 13: Variadic Templates
    // ----------------------------------------------------------
    cout << "\n--- Section 13: Variadic Templates ---\n";

    cout << "  printAll(1, 2.5, \"hello\", 'X'): ";
    printAll(1, 2.5, "hello", 'X');

    cout << "  sumAll(1, 2, 3, 4, 5)    = " << sumAll(1, 2, 3, 4, 5)    << "\n";
    cout << "  sumAll(1.1, 2.2, 3.3)    = " << sumAll(1.1, 2.2, 3.3)    << "\n";
    cout << "  sumAll(10)               = " << sumAll(10)                << "\n";

    cout << "  countArgs(1,2,3)         = " << countArgs(1, 2, 3)        << "\n";
    cout << "  countArgs('a','b')       = " << countArgs('a', 'b')       << "\n";
    cout << "  countArgs()              = " << countArgs()               << "\n";


    // ----------------------------------------------------------
    // Section 14: Templates and Inheritance
    // ----------------------------------------------------------
    cout << "\n--- Section 14: Templates and Inheritance ---\n";

    Printable<int>     base(100);
    TaggedItem<int>    tagInt(200, "score");
    TaggedItem<string> tagStr(string("World"), "greeting");

    base.print();
    tagInt.print();
    tagStr.print();

    // Polymorphism with template base
    Printable<int>* ptr = &tagInt;
    cout << "  Via base pointer (virtual dispatch):\n  ";
    ptr->print();


    cout << "\n=======================================================\n";
    cout << "  End of main(). All local objects now destroyed.\n";
    cout << "=======================================================\n";

    return 0;
}


// ============================================================
//  QUICK REFERENCE SUMMARY
// ============================================================
//
//  Concept                        Syntax
//  ──────────────────────────────────────────────────────────
//  Function template              template <typename T>
//                                 T func(T a, T b) { ... }
//
//  Explicit instantiation         func<int>(3, 5)
//
//  Multiple type params           template <typename T1, typename T2>
//
//  Non-type parameter             template <typename T, int N>
//
//  Function specialization        template <>
//                                 RetType func<Type>(Type a) { ... }
//
//  Class template                 template <typename T>
//                                 class MyClass { ... };
//
//  Class member outside           template <typename T>
//                                 RetType MyClass<T>::method() { }
//
//  Full class specialization      template <>
//                                 class MyClass<SpecificType> { ... };
//
//  Partial specialization         template <typename T>
//                                 class MyClass<T, T> { ... };
//
//  Default type parameter         template <typename T = int, int N = 10>
//
//  Variadic template              template <typename... Args>
//                                 void f(Args... args) { }
//
//  sizeof... operator             sizeof...(args)  // count of pack
//
//  Template + inheritance         class Derived : public Base<T> { }
//
//  typename vs class              Both are identical for type params.
//                                 Prefer 'typename' for clarity.
//
//  When is type deduced?
//    - Function templates: auto-deduced from call arguments.
//    - Class templates:    must specify explicitly (pre-C++17).
//    - C++17 CTAD:         MyClass obj(args) — compiler deduces.
//
//  Compile-time vs runtime
//    - Templates are resolved at COMPILE TIME.
//    - No virtual dispatch overhead (unlike runtime polymorphism).
//    - Each instantiation (Box<int>, Box<double>) is a separate
//      compiled class/function — binary may be larger (code bloat).
// ============================================================
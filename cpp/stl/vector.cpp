// ============================================================
//   C++ std::vector — COMPLETE GUIDE
//   Topics Covered:
//     1.  What is a Vector? (vs Raw Array)
//     2.  Declaration & Initialization (All Ways)
//     3.  Accessing Elements ([], at, front, back, data)
//     4.  Modifying Elements
//     5.  Adding Elements (push_back, emplace_back, insert)
//     6.  Removing Elements (pop_back, erase, clear)
//     7.  Size & Capacity (size, capacity, resize, reserve)
//     8.  Iterators (begin, end, rbegin, rend, cbegin)
//     9.  Range-Based For Loop
//     10. Passing Vector to Functions (by value, ref, ptr)
//     11. Returning Vector from Function
//     12. Sorting & Searching with <algorithm>
//     13. Common Algorithms on Vectors
//     14. 2D Vector (Vector of Vectors)
//     15. Vector of Objects (User-Defined Class)
//     16. Vector vs Array — When to Use Which
//     17. Quick Reference Summary
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   // sort, find, count, reverse, etc.
#include <numeric>     // accumulate, iota
#include <iterator>    // ostream_iterator
using namespace std;


// ============================================================
//  HELPER — print any vector of printable type
// ============================================================
template <typename T>
void printVector(const vector<T>& v, const string& label = "") {
    if (!label.empty()) cout << "  " << label << ": ";
    else cout << "  ";
    cout << "[ ";
    for (const T& elem : v) cout << elem << " ";
    cout << "] (size=" << v.size()
         << ", capacity=" << v.capacity() << ")\n";
}


// ============================================================
// SECTION 1: WHAT IS A VECTOR?
// ============================================================
// std::vector is a DYNAMIC ARRAY from the C++ Standard Library.
//
//   Raw Array  : fixed size set at compile time, no bounds check
//   std::vector: grows/shrinks at runtime, bounds-checked (at()),
//                manages its own memory, copyable, movable.
//
// Internally:
//   - Stores elements in a CONTIGUOUS block of heap memory.
//   - Tracks: pointer to data, current size, allocated capacity.
//   - When capacity is exceeded, it allocates a LARGER block
//     (typically 2x), copies/moves all elements, frees old block.
//     This is called REALLOCATION.
//
// Header required:  #include <vector>
// Namespace:        std::vector<T>
// ============================================================


// ============================================================
// SECTION 15 PREP: User-Defined Class for Vector of Objects
// ============================================================
class Student {
private:
    string name;
    int    age;
    float  gpa;

public:
    // Default constructor (needed for vector resize)
    Student() : name("Unknown"), age(0), gpa(0.0f) {}

    // Parameterized constructor
    Student(const string& n, int a, float g)
        : name(n), age(a), gpa(g) {}

    // Getters
    string getName() const { return name; }
    int    getAge()  const { return age;  }
    float  getGpa()  const { return gpa;  }

    // Setters
    void setGpa(float g) { gpa = g; }

    void display() const {
        cout << "  Student{ name: " << name
             << ", age: " << age
             << ", gpa: " << gpa << " }\n";
    }

    // Operator overload for sort / comparison
    bool operator<(const Student& other) const {
        return gpa < other.gpa;   // sort by GPA ascending
    }

    bool operator==(const Student& other) const {
        return name == other.name && age == other.age;
    }
};

// ostream operator for easy printing
ostream& operator<<(ostream& os, const Student& s) {
    os << s.getName() << "(" << s.getGpa() << ")";
    return os;
}


// ============================================================
// SECTION 10: PASSING VECTOR TO FUNCTIONS
// ============================================================

// --- By Value: receives a FULL COPY, original unchanged ---
void doubleElementsByValue(vector<int> v) {
    for (int& x : v) x *= 2;
    cout << "  [By Value  ] Inside function: ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}   // copy destroyed here

// --- By Reference: works on the ORIGINAL vector ---
void doubleElementsByRef(vector<int>& v) {
    for (int& x : v) x *= 2;
}

// --- By Const Reference: read-only, no copy overhead ---
void printSumByConstRef(const vector<int>& v) {
    int sum = 0;
    for (int x : v) sum += x;
    cout << "  [Const Ref ] Sum = " << sum << "\n";
}

// --- By Pointer: explicit address passing ---
void appendByPointer(vector<int>* vPtr, int val) {
    vPtr->push_back(val);
}


// ============================================================
// SECTION 11: RETURNING VECTOR FROM FUNCTION
// ============================================================

// Return by value — compiler applies RVO (Return Value Optimization)
// so no expensive copy actually happens in practice.
vector<int> generateRange(int start, int end, int step = 1) {
    vector<int> result;
    for (int i = start; i <= end; i += step)
        result.push_back(i);
    return result;   // RVO: no copy, direct construction
}

vector<int> filterEven(const vector<int>& v) {
    vector<int> evens;
    for (int x : v)
        if (x % 2 == 0) evens.push_back(x);
    return evens;
}

vector<string> splitWords(const string& sentence) {
    vector<string> words;
    string word;
    for (char c : sentence) {
        if (c == ' ') {
            if (!word.empty()) { words.push_back(word); word.clear(); }
        } else {
            word += c;
        }
    }
    if (!word.empty()) words.push_back(word);
    return words;
}


// ============================================================
//  MAIN — All Sections Demonstrated
// ============================================================
int main() {

    cout << "=======================================================\n";
    cout << "  C++ std::vector — COMPLETE DEMONSTRATION\n";
    cout << "=======================================================\n\n";


    // ----------------------------------------------------------
    // SECTION 2: DECLARATION & INITIALIZATION — ALL WAYS
    // ----------------------------------------------------------
    cout << "--- Section 2: Declaration & Initialization ---\n\n";

    // 2a. Empty vector (size=0, capacity=0)
    vector<int> v1;
    printVector(v1, "Empty vector<int>");

    // 2b. Vector with N elements, all zero-initialized
    vector<int> v2(5);
    printVector(v2, "vector<int>(5) — zero init");

    // 2c. Vector with N elements, all set to a specific value
    vector<int> v3(5, 99);
    printVector(v3, "vector<int>(5, 99)");

    // 2d. Initializer list (brace initialization)
    vector<int> v4 = {10, 20, 30, 40, 50};
    printVector(v4, "Init list {10,20,30,40,50}");

    // 2e. Copy constructor — deep copy of another vector
    vector<int> v5(v4);
    printVector(v5, "Copy of v4");

    // 2f. Range constructor — copy from iterators (subrange)
    vector<int> v6(v4.begin() + 1, v4.end() - 1);
    printVector(v6, "Range [begin+1, end-1] of v4");

    // 2g. Using assign()
    vector<int> v7;
    v7.assign(4, 7);                 // 4 copies of 7
    printVector(v7, "assign(4, 7)");

    vector<int> v8;
    v8.assign(v4.begin(), v4.end()); // assign from range
    printVector(v8, "assign from v4's range");

    // 2h. String vector
    vector<string> names = {"Alice", "Bob", "Charlie", "Diana"};
    printVector(names, "vector<string>");

    // 2i. Double vector
    vector<double> scores = {88.5, 92.0, 75.3, 96.8};
    printVector(scores, "vector<double>");

    // 2j. Move constructor (C++11) — transfers ownership, v4 left empty
    vector<int> v9(move(v4));
    printVector(v9, "Move from v4 into v9");
    printVector(v4, "v4 after move (now empty)");


    // ----------------------------------------------------------
    // SECTION 3: ACCESSING ELEMENTS
    // ----------------------------------------------------------
    cout << "\n--- Section 3: Accessing Elements ---\n\n";

    vector<int> arr = {11, 22, 33, 44, 55};
    printVector(arr, "arr");

    // 3a. Subscript operator [] — NO bounds checking, fast
    cout << "  arr[0]         = " << arr[0]         << "  (first)\n";
    cout << "  arr[4]         = " << arr[4]         << "  (last)\n";
    cout << "  arr[arr.size()-1] = " << arr[arr.size()-1] << "  (last safe)\n";

    // 3b. at() — WITH bounds checking, throws std::out_of_range
    cout << "  arr.at(2)      = " << arr.at(2) << "\n";
    try {
        cout << "  arr.at(10)     = ";
        cout << arr.at(10) << "\n";   // will throw
    } catch (const out_of_range& e) {
        cout << "EXCEPTION caught: " << e.what() << "\n";
    }

    // 3c. front() and back()
    cout << "  arr.front()    = " << arr.front() << "  (first element)\n";
    cout << "  arr.back()     = " << arr.back()  << "  (last element)\n";

    // 3d. data() — pointer to underlying C-array
    int* raw = arr.data();
    cout << "  arr.data()[1]  = " << raw[1] << "  (via raw pointer)\n";

    // 3e. Modifying via reference from []
    arr[2] = 300;
    cout << "  After arr[2]=300: ";
    printVector(arr);


    // ----------------------------------------------------------
    // SECTION 4: MODIFYING ELEMENTS
    // ----------------------------------------------------------
    cout << "\n--- Section 4: Modifying Elements ---\n\n";

    vector<int> m = {1, 2, 3, 4, 5};
    printVector(m, "Original");

    // Direct assignment
    m[0] = 10;
    m.at(4) = 50;
    printVector(m, "After m[0]=10, m.at(4)=50");

    // Using a loop to double each element
    for (int& x : m) x *= 2;
    printVector(m, "After doubling all");

    // fill a subrange with a value via fill()
    fill(m.begin() + 1, m.begin() + 3, 0);
    printVector(m, "After fill [1,3) with 0");

    // Replace all occurrences of a value using replace()
    replace(m.begin(), m.end(), 0, 99);
    printVector(m, "After replace(0 -> 99)");


    // ----------------------------------------------------------
    // SECTION 5: ADDING ELEMENTS
    // ----------------------------------------------------------
    cout << "\n--- Section 5: Adding Elements ---\n\n";

    vector<int> a;

    // 5a. push_back — add to END, copy/move the value
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    printVector(a, "After 3x push_back");

    // 5b. emplace_back (C++11) — constructs IN PLACE at end
    //     Slightly more efficient than push_back for objects
    //     because it avoids creating a temporary.
    a.emplace_back(40);
    a.emplace_back(50);
    printVector(a, "After 2x emplace_back");

    // 5c. insert at a SPECIFIC POSITION
    //     insert(iterator pos, value) — inserts BEFORE pos
    a.insert(a.begin(), 0);           // insert 0 at front
    printVector(a, "insert(begin, 0) — prepend");

    a.insert(a.begin() + 3, 999);     // insert at index 3
    printVector(a, "insert(begin+3, 999)");

    // 5d. insert multiple copies
    a.insert(a.end(), 3, 77);         // append three 77s
    printVector(a, "insert(end, 3, 77)");

    // 5e. insert range from another vector
    vector<int> extra = {100, 200};
    a.insert(a.begin() + 2, extra.begin(), extra.end());
    printVector(a, "insert range {100,200} at index 2");

    // 5f. emplace (C++11) — in-place insert at position
    a.emplace(a.begin() + 1, 555);
    printVector(a, "emplace(begin+1, 555)");


    // ----------------------------------------------------------
    // SECTION 6: REMOVING ELEMENTS
    // ----------------------------------------------------------
    cout << "\n--- Section 6: Removing Elements ---\n\n";

    vector<int> r = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printVector(r, "Original");

    // 6a. pop_back — remove LAST element (O(1))
    r.pop_back();
    r.pop_back();
    printVector(r, "After 2x pop_back");

    // 6b. erase at specific position
    r.erase(r.begin());               // remove first element
    printVector(r, "erase(begin) — remove front");

    r.erase(r.begin() + 2);          // remove element at index 2
    printVector(r, "erase(begin+2)");

    // 6c. erase a RANGE [first, last)   — last is NOT erased
    r.erase(r.begin() + 1, r.begin() + 3);
    printVector(r, "erase range [1, 3)");

    // 6d. Erase-Remove Idiom — remove ALL occurrences of a value
    //     remove() shifts non-target elements forward and returns
    //     an iterator to the new logical end. erase() then trims.
    vector<int> dup = {1, 3, 2, 3, 4, 3, 5};
    printVector(dup, "Before erase-remove 3s");
    dup.erase(remove(dup.begin(), dup.end(), 3), dup.end());
    printVector(dup, "After  erase-remove 3s");

    // 6e. Remove elements matching a CONDITION (remove_if)
    vector<int> cond = {1, 2, 3, 4, 5, 6, 7, 8};
    cond.erase(remove_if(cond.begin(), cond.end(),
                         [](int x){ return x % 2 == 0; }),
               cond.end());
    printVector(cond, "Remove even numbers");

    // 6f. clear — remove ALL elements (size=0, capacity kept)
    vector<int> toClear = {1, 2, 3};
    toClear.clear();
    printVector(toClear, "After clear()");


    // ----------------------------------------------------------
    // SECTION 7: SIZE & CAPACITY
    // ----------------------------------------------------------
    cout << "\n--- Section 7: Size & Capacity ---\n\n";

    vector<int> sc;
    cout << "  empty() = " << sc.empty() << "  (1=true)\n";
    cout << "  size()  = " << sc.size()    << "\n";
    cout << "  capacity() = " << sc.capacity() << "\n";

    // Watch capacity grow as we push elements
    cout << "\n  Pushing elements — observe capacity jumps:\n";
    for (int i = 1; i <= 10; i++) {
        sc.push_back(i);
        cout << "  push " << i
             << "  -> size=" << sc.size()
             << ", capacity=" << sc.capacity() << "\n";
    }

    // reserve — pre-allocate capacity WITHOUT changing size
    vector<int> reserveDemo;
    reserveDemo.reserve(100);
    cout << "\n  After reserve(100): size=" << reserveDemo.size()
         << ", capacity=" << reserveDemo.capacity() << "\n";
    // Now push_back won't cause reallocation until >100 elements

    // resize — CHANGE size (add default elements or truncate)
    vector<int> rv = {1, 2, 3};
    rv.resize(6);               // adds 3 zero-initialized elements
    printVector(rv, "After resize(6)   — grew");

    rv.resize(2);               // truncate to 2 elements
    printVector(rv, "After resize(2)   — shrank");

    rv.resize(5, 42);           // grow and fill new spots with 42
    printVector(rv, "After resize(5,42) — fill");

    // shrink_to_fit — release unused capacity (hint to compiler)
    vector<int> shrink = {1,2,3,4,5};
    shrink.reserve(100);
    cout << "\n  Before shrink_to_fit: capacity=" << shrink.capacity() << "\n";
    shrink.shrink_to_fit();
    cout << "  After  shrink_to_fit: capacity=" << shrink.capacity() << "\n";

    // max_size — theoretical maximum number of elements
    cout << "  max_size() = " << sc.max_size() << "\n";


    // ----------------------------------------------------------
    // SECTION 8: ITERATORS
    // ----------------------------------------------------------
    cout << "\n--- Section 8: Iterators ---\n\n";

    vector<int> iv = {10, 20, 30, 40, 50};

    // 8a. begin() / end() — forward traversal
    cout << "  Forward  (begin->end):  ";
    for (auto it = iv.begin(); it != iv.end(); ++it)
        cout << *it << " ";
    cout << "\n";

    // 8b. rbegin() / rend() — reverse traversal
    cout << "  Reverse  (rbegin->rend): ";
    for (auto it = iv.rbegin(); it != iv.rend(); ++it)
        cout << *it << " ";
    cout << "\n";

    // 8c. cbegin() / cend() — const forward (read-only)
    cout << "  Const    (cbegin->cend): ";
    for (auto it = iv.cbegin(); it != iv.cend(); ++it)
        cout << *it << " ";
    cout << "\n";

    // 8d. crbegin() / crend() — const reverse
    cout << "  ConstRev (crbegin):      ";
    for (auto it = iv.crbegin(); it != iv.crend(); ++it)
        cout << *it << " ";
    cout << "\n";

    // 8e. Iterator arithmetic
    auto it = iv.begin();
    cout << "\n  it = begin(),  *it        = " << *it       << "\n";
    cout <<   "  *(it + 2)                 = " << *(it + 2) << "\n";
    advance(it, 3);
    cout <<   "  After advance(it,3), *it  = " << *it       << "\n";
    cout <<   "  distance(begin, it)       = "
         << distance(iv.begin(), it) << "\n";

    // 8f. Modifying via iterator
    for (auto itr = iv.begin(); itr != iv.end(); ++itr)
        *itr += 1;
    printVector(iv, "After +1 via iterator");


    // ----------------------------------------------------------
    // SECTION 9: RANGE-BASED FOR LOOP
    // ----------------------------------------------------------
    cout << "\n--- Section 9: Range-Based For Loop ---\n\n";

    vector<int> rf = {1, 2, 3, 4, 5};

    // Read-only
    cout << "  Read-only  : ";
    for (const int& x : rf) cout << x << " ";
    cout << "\n";

    // Modify in-place (use reference)
    for (int& x : rf) x *= 3;
    printVector(rf, "After *=3 (by ref)");

    // auto copy (no & — makes a copy each iteration)
    for (auto x : rf) x = 0;          // doesn't change rf
    printVector(rf, "auto copy loop — rf unchanged");


    // ----------------------------------------------------------
    // SECTION 10: PASSING VECTOR TO FUNCTIONS
    // ----------------------------------------------------------
    cout << "\n--- Section 10: Passing Vector to Functions ---\n\n";

    vector<int> fv = {5, 10, 15, 20, 25};
    printVector(fv, "fv before calls");

    doubleElementsByValue(fv);         // copy — fv unchanged
    printVector(fv, "fv after byValue call (unchanged)");

    doubleElementsByRef(fv);           // reference — fv CHANGED
    printVector(fv, "fv after byRef  call (CHANGED)");

    printSumByConstRef(fv);            // const ref — read only

    appendByPointer(&fv, 999);         // pointer — fv CHANGED
    printVector(fv, "fv after byPointer append(999)");


    // ----------------------------------------------------------
    // SECTION 11: RETURNING VECTOR FROM FUNCTION
    // ----------------------------------------------------------
    cout << "\n--- Section 11: Returning Vector from Function ---\n\n";

    vector<int> range = generateRange(1, 10);
    printVector(range, "generateRange(1,10)");

    vector<int> stepped = generateRange(0, 20, 5);
    printVector(stepped, "generateRange(0,20, step=5)");

    vector<int> evens = filterEven(range);
    printVector(evens, "filterEven(range)");

    vector<string> wordVec = splitWords("the quick brown fox jumps");
    printVector(wordVec, "splitWords(...)");


    // ----------------------------------------------------------
    // SECTION 12: SORTING & SEARCHING
    // ----------------------------------------------------------
    cout << "\n--- Section 12: Sorting & Searching ---\n\n";

    vector<int> sv = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    printVector(sv, "Unsorted");

    // Sort ascending (default)
    sort(sv.begin(), sv.end());
    printVector(sv, "Ascending sort");

    // Sort descending (custom comparator)
    sort(sv.begin(), sv.end(), greater<int>());
    printVector(sv, "Descending sort");

    // Sort with lambda
    sort(sv.begin(), sv.end(), [](int a, int b){
        return a % 3 < b % 3;   // sort by remainder mod 3
    });
    printVector(sv, "Sort by (x%3) ascending");

    // stable_sort — preserves relative order of equal elements
    vector<int> stbl = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    stable_sort(stbl.begin(), stbl.end());
    printVector(stbl, "stable_sort result");

    // Binary search (vector MUST be sorted first)
    sort(stbl.begin(), stbl.end());
    bool found = binary_search(stbl.begin(), stbl.end(), 5);
    cout << "  binary_search(5) in sorted = " << (found ? "found" : "not found") << "\n";

    // lower_bound / upper_bound — iterators into sorted range
    auto lb = lower_bound(stbl.begin(), stbl.end(), 5);
    auto ub = upper_bound(stbl.begin(), stbl.end(), 5);
    cout << "  lower_bound(5) at index = " << distance(stbl.begin(), lb) << "\n";
    cout << "  upper_bound(5) at index = " << distance(stbl.begin(), ub) << "\n";

    // find — linear search (works on unsorted too)
    vector<int> fnd = {10, 30, 20, 50, 40};
    auto pos = find(fnd.begin(), fnd.end(), 20);
    if (pos != fnd.end())
        cout << "  find(20): found at index " << distance(fnd.begin(), pos) << "\n";

    // find_if — find first element matching condition
    auto it2 = find_if(fnd.begin(), fnd.end(), [](int x){ return x > 25; });
    if (it2 != fnd.end())
        cout << "  find_if(>25): first match = " << *it2 << "\n";


    // ----------------------------------------------------------
    // SECTION 13: COMMON ALGORITHMS
    // ----------------------------------------------------------
    cout << "\n--- Section 13: Common Algorithms ---\n\n";

    vector<int> alg = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    printVector(alg, "alg");

    // count — how many times a value appears
    cout << "  count(1)  = " << count(alg.begin(), alg.end(), 1) << "\n";
    cout << "  count(5)  = " << count(alg.begin(), alg.end(), 5) << "\n";

    // count_if — count elements matching condition
    cout << "  count_if(>4) = "
         << count_if(alg.begin(), alg.end(), [](int x){ return x > 4; }) << "\n";

    // accumulate — sum (or other fold operations)
    int total = accumulate(alg.begin(), alg.end(), 0);
    cout << "  accumulate (sum) = " << total << "\n";

    int product = accumulate(alg.begin(), alg.end(), 1,
                             [](int a, int b){ return a * b; });
    cout << "  accumulate (product) = " << product << "\n";

    // min_element / max_element — returns iterator
    auto minIt = min_element(alg.begin(), alg.end());
    auto maxIt = max_element(alg.begin(), alg.end());
    cout << "  min = " << *minIt << " at index " << distance(alg.begin(), minIt) << "\n";
    cout << "  max = " << *maxIt << " at index " << distance(alg.begin(), maxIt) << "\n";

    // reverse
    vector<int> rev = {1, 2, 3, 4, 5};
    reverse(rev.begin(), rev.end());
    printVector(rev, "reverse");

    // rotate — shift elements left by N positions
    vector<int> rot = {1, 2, 3, 4, 5};
    rotate(rot.begin(), rot.begin() + 2, rot.end()); // left-rotate by 2
    printVector(rot, "rotate left by 2");

    // unique — removes CONSECUTIVE duplicates (sort first!)
    vector<int> uniq = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    auto newEnd = unique(uniq.begin(), uniq.end());
    uniq.erase(newEnd, uniq.end());
    printVector(uniq, "unique (consec. dups removed)");

    // transform — apply function to each element → write to dest
    vector<int> src = {1, 2, 3, 4, 5};
    vector<int> dest(src.size());
    transform(src.begin(), src.end(), dest.begin(),
              [](int x){ return x * x; });
    printVector(dest, "transform (square each)");

    // for_each — apply function to each element (side-effects)
    cout << "  for_each (print *2): ";
    for_each(src.begin(), src.end(), [](int x){ cout << x * 2 << " "; });
    cout << "\n";

    // iota — fill with incrementing values (from <numeric>)
    vector<int> seq(8);
    iota(seq.begin(), seq.end(), 1);   // 1, 2, 3, ..., 8
    printVector(seq, "iota(1..8)");

    // copy — copy range to another vector
    vector<int> copied(seq.size());
    copy(seq.begin(), seq.end(), copied.begin());
    printVector(copied, "copy of seq");

    // any_of / all_of / none_of
    cout << "  any_of  (>5) in seq = "
         << any_of (seq.begin(), seq.end(), [](int x){ return x > 5; }) << "\n";
    cout << "  all_of  (>0) in seq = "
         << all_of (seq.begin(), seq.end(), [](int x){ return x > 0; }) << "\n";
    cout << "  none_of (<0) in seq = "
         << none_of(seq.begin(), seq.end(), [](int x){ return x < 0; }) << "\n";


    // ----------------------------------------------------------
    // SECTION 14: 2D VECTOR (VECTOR OF VECTORS)
    // ----------------------------------------------------------
    cout << "\n--- Section 14: 2D Vector (vector of vectors) ---\n\n";

    // 14a. Declare a 3x4 matrix, all zeros
    int rows = 3, cols = 4;
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    // Fill with values
    int val = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = val++;

    // Print matrix
    cout << "  3x4 Matrix:\n";
    for (int i = 0; i < rows; i++) {
        cout << "    [ ";
        for (int j = 0; j < cols; j++)
            cout << matrix[i][j] << "\t";
        cout << "]\n";
    }

    // 14b. Jagged (ragged) 2D vector — rows have different sizes
    vector<vector<int>> jagged;
    jagged.push_back({1});
    jagged.push_back({2, 3});
    jagged.push_back({4, 5, 6});
    jagged.push_back({7, 8, 9, 10});

    cout << "\n  Jagged 2D Vector:\n";
    for (int i = 0; i < (int)jagged.size(); i++) {
        cout << "    Row " << i << " [" << jagged[i].size() << "]: ";
        for (int x : jagged[i]) cout << x << " ";
        cout << "\n";
    }

    // 14c. Adding a new row dynamically
    jagged.push_back({11, 12, 13, 14, 15});
    cout << "\n  After push_back new row, rows = " << jagged.size() << "\n";

    // 14d. Transpose of the 3x4 matrix (creates 4x3)
    vector<vector<int>> transposed(cols, vector<int>(rows));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            transposed[j][i] = matrix[i][j];

    cout << "\n  Transposed 4x3 Matrix:\n";
    for (auto& row : transposed) {
        cout << "    [ ";
        for (int x : row) cout << x << "\t";
        cout << "]\n";
    }


    // ----------------------------------------------------------
    // SECTION 15: VECTOR OF OBJECTS
    // ----------------------------------------------------------
    cout << "\n--- Section 15: Vector of Objects ---\n\n";

    // 15a. Creating vector of Student objects
    vector<Student> students;

    // push_back with object
    students.push_back(Student("Alice",   20, 3.8f));
    students.push_back(Student("Bob",     22, 3.2f));
    students.push_back(Student("Charlie", 21, 3.9f));
    students.push_back(Student("Diana",   19, 3.5f));

    // emplace_back — constructs in place (no temp object)
    students.emplace_back("Edward", 23, 2.9f);
    students.emplace_back("Fatima", 20, 3.7f);

    cout << "  All students:\n";
    for (const Student& s : students) s.display();

    // 15b. Access and modify via index
    students[1].setGpa(3.6f);
    cout << "\n  After updating Bob's GPA:\n";
    students[1].display();

    // 15c. Sort by GPA (uses overloaded operator<)
    sort(students.begin(), students.end());
    cout << "\n  Sorted by GPA ascending:\n";
    for (const Student& s : students) s.display();

    // 15d. Sort descending with lambda
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b){
             return a.getGpa() > b.getGpa();
         });
    cout << "\n  Sorted by GPA descending:\n";
    for (const Student& s : students) s.display();

    // 15e. find_if — find first student with GPA > 3.8
    auto topIt = find_if(students.begin(), students.end(),
                         [](const Student& s){ return s.getGpa() > 3.8f; });
    if (topIt != students.end()) {
        cout << "\n  First student with GPA > 3.8:\n";
        topIt->display();
    }

    // 15f. count_if — how many have GPA >= 3.5
    int highGpa = count_if(students.begin(), students.end(),
                           [](const Student& s){ return s.getGpa() >= 3.5f; });
    cout << "\n  Students with GPA >= 3.5: " << highGpa << "\n";

    // 15g. erase a student by value condition
    students.erase(
        remove_if(students.begin(), students.end(),
                  [](const Student& s){ return s.getGpa() < 3.0f; }),
        students.end()
    );
    cout << "\n  After removing GPA < 3.0:\n";
    for (const Student& s : students) s.display();

    // 15h. Vector of pointers to objects (heap objects)
    cout << "\n  Vector of pointers (heap students):\n";
    vector<Student*> ptrVec;
    ptrVec.push_back(new Student("Grace",  21, 3.85f));
    ptrVec.push_back(new Student("Haris",  22, 3.40f));

    for (Student* sp : ptrVec) sp->display();

    // Must manually free heap objects
    for (Student* sp : ptrVec) delete sp;
    ptrVec.clear();
    cout << "  Heap students deleted.\n";


    cout << "\n=======================================================\n";
    cout << "  End of main(). All vectors destroyed automatically.\n";
    cout << "=======================================================\n";

    return 0;
}


// ============================================================
//  SECTION 16: VECTOR vs RAW ARRAY — WHEN TO USE WHICH
// ============================================================
//
//  Feature              Raw Array          std::vector
//  ────────────────     ─────────────────  ──────────────────────
//  Size                 Fixed at compile   Dynamic, grows at runtime
//  Memory               Stack (usually)    Heap (managed by vector)
//  Bounds checking      None               .at() throws out_of_range
//  Copyable             No (decays to ptr) Yes, deep copy with =
//  Passed to function   Pointer + size     Pass by reference cleanly
//  STL algorithms       Need ptr + size    Works directly with iterators
//  Overhead             None               Small (3 pointers: data,size,cap)
//  Reallocation         N/A                Automatic, ~2x growth
//
//  Use RAW ARRAY when:
//    - Size is truly fixed and known at compile time
//    - Performance is ultra-critical (embedded systems)
//    - Interfacing with C APIs
//    - Use std::array<T,N> instead for safety with fixed size
//
//  Use std::vector when:
//    - Size is unknown or changes at runtime
//    - You need to insert/remove elements
//    - You want STL algorithm support
//    - Default choice for most C++ code
//
// ============================================================
//  QUICK REFERENCE SUMMARY
// ============================================================
//
//  Declaration / Init
//    vector<T> v;                   empty
//    vector<T> v(n);                n default-initialized elements
//    vector<T> v(n, val);           n copies of val
//    vector<T> v = {a, b, c};       initializer list
//    vector<T> v2(v1);              copy constructor
//    vector<T> v2(v1.begin(), v1.end());  range constructor
//    vector<T> v2(move(v1));        move constructor (v1 empty after)
//
//  Access
//    v[i]       — unchecked, fast
//    v.at(i)    — bounds-checked, throws out_of_range
//    v.front()  — first element
//    v.back()   — last element
//    v.data()   — raw pointer to underlying array
//
//  Size / Capacity
//    v.size()          — current number of elements
//    v.capacity()      — allocated storage
//    v.empty()         — true if size == 0
//    v.reserve(n)      — pre-allocate capacity (no size change)
//    v.resize(n)       — change size (fill with 0 or truncate)
//    v.resize(n, val)  — fill new elements with val
//    v.shrink_to_fit() — release unused capacity
//    v.max_size()      — theoretical maximum
//
//  Add / Remove
//    v.push_back(val)          — append copy/move
//    v.emplace_back(args...)   — construct in place at end
//    v.pop_back()              — remove last (O(1))
//    v.insert(pos, val)        — insert before pos
//    v.insert(pos, n, val)     — insert n copies
//    v.insert(pos, first, last)— insert range
//    v.emplace(pos, args...)   — construct in place at pos
//    v.erase(pos)              — remove at pos
//    v.erase(first, last)      — remove range [first, last)
//    v.clear()                 — remove all (capacity kept)
//    Erase-Remove idiom:
//      v.erase(remove(v.begin(), v.end(), val), v.end())
//      v.erase(remove_if(v.begin(), v.end(), pred), v.end())
//
//  Iterators
//    v.begin() / v.end()       — forward
//    v.rbegin() / v.rend()     — reverse
//    v.cbegin() / v.cend()     — const forward
//    v.crbegin() / v.crend()   — const reverse
//
//  Algorithms (need #include <algorithm>)
//    sort(b, e)                — ascending sort
//    sort(b, e, comp)          — custom comparator / lambda
//    stable_sort(b, e)         — stable ascending sort
//    binary_search(b, e, val)  — requires sorted
//    lower_bound(b, e, val)    — first >= val (sorted)
//    upper_bound(b, e, val)    — first >  val (sorted)
//    find(b, e, val)           — linear search
//    find_if(b, e, pred)       — linear search with condition
//    count(b, e, val)          — occurrences of val
//    count_if(b, e, pred)      — count matching condition
//    reverse(b, e)             — reverse in-place
//    rotate(b, mid, e)         — left-rotate
//    unique(b, e)              — remove consecutive dups
//    transform(b, e, out, f)   — apply f to each element
//    for_each(b, e, f)         — side-effect loop
//    any_of / all_of / none_of — predicate checks
//    min_element / max_element — iterators to min/max
//    accumulate(b, e, init)    — sum / fold (from <numeric>)
//    iota(b, e, start)         — fill incrementing (from <numeric>)
//    copy(b, e, out)           — copy range
//    fill(b, e, val)           — fill range with val
//    replace(b, e, old, new)   — replace value
//    remove(b, e, val)         — shift out val (use with erase)
//    remove_if(b, e, pred)     — shift out matching (use with erase)
// ============================================================
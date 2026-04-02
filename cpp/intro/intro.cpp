// ============================================================
//   C++ INTRODUCTION
//   Topics Covered:
//     1. Classes & Objects
//     2. Constructors (Default, Parameterized, Copy)
//     3. Destructor
//     4. Passing Object to Function — by Value
//     5. Passing Object to Function — by Pointer
//     6. Passing Object to Function — by Reference
//     7. Passing Array of Objects to Function
// ============================================================

#include <iostream>
#include <string>
using namespace std;


// ============================================================
// SECTION 1: CLASS DEFINITION
// ============================================================
// A class is a blueprint/template for creating objects.
// It bundles DATA (attributes) and BEHAVIOR (methods) together.
// Access specifiers:
//   private  -> accessible only within the class
//   public   -> accessible from outside the class
//   protected-> accessible within class and derived classes
// ============================================================

class Student {

private:
    // --- Data Members (Attributes) ---
    string name;   // Student's name
    int    age;    // Student's age
    float  gpa;    // Grade Point Average
    int    id;     // Unique student ID

public:

    // ==========================================================
    // SECTION 2A: DEFAULT CONSTRUCTOR
    // ==========================================================
    // Called automatically when an object is created WITHOUT
    // any arguments. Initializes members to safe default values.
    // Syntax: ClassName() { ... }
    // ==========================================================
    Student() {
        name = "Unknown";
        age  = 0;
        gpa  = 0.0f;
        id   = -1;
        cout << "[Constructor] Default constructor called. "
             << "A blank Student object created.\n";
    }

    // ==========================================================
    // SECTION 2B: PARAMETERIZED CONSTRUCTOR
    // ==========================================================
    // Called when an object is created WITH arguments.
    // Uses an INITIALIZER LIST (after the colon) for efficiency —
    // members are initialized directly instead of being assigned.
    // ==========================================================
    Student(string n, int a, float g, int i)
        : name(n), age(a), gpa(g), id(i)
    {
        cout << "[Constructor] Parameterized constructor called. "
             << "Student '" << name << "' (ID: " << id << ") created.\n";
    }

    // ==========================================================
    // SECTION 2C: COPY CONSTRUCTOR
    // ==========================================================
    // Called when one object is INITIALIZED from another.
    //   Student s2 = s1;   <-- triggers copy constructor
    //   Student s2(s1);    <-- same thing
    // Also triggered when passing an object BY VALUE to a function.
    // Parameter must be a CONST REFERENCE to avoid infinite recursion.
    // ==========================================================
    Student(const Student& other)
        : name(other.name), age(other.age), gpa(other.gpa), id(other.id)
    {
        cout << "[Copy Constructor] Copy constructor called. "
             << "Copied student '" << name << "' (ID: " << id << ").\n";
    }

    // ==========================================================
    // SECTION 3: DESTRUCTOR
    // ==========================================================
    // Called AUTOMATICALLY when an object goes out of scope,
    // is deleted (if on heap), or the program ends.
    // Purpose: release resources (memory, files, connections, etc.)
    // Syntax: ~ClassName() { ... }
    // Rules:
    //   - No return type, no parameters
    //   - A class can have ONLY ONE destructor
    //   - Cannot be overloaded
    // ==========================================================
    ~Student() {
        cout << "[Destructor]  Destructor called for student '"
             << name << "' (ID: " << id << "). Object destroyed.\n";
    }

    // ---- Setter Methods (Mutators) ----
    void setName(const string& n) { name = n; }
    void setAge(int a)            { age  = a; }
    void setGpa(float g)          { gpa  = g; }
    void setId(int i)             { id   = i; }

    // ---- Getter Methods (Accessors) ----
    string getName() const { return name; }
    int    getAge()  const { return age;  }
    float  getGpa()  const { return gpa;  }
    int    getId()   const { return id;   }

    // ---- Utility Method ----
    void display() const {
        cout << "  +---------------------------+\n";
        cout << "  | ID   : " << id   << "\n";
        cout << "  | Name : " << name << "\n";
        cout << "  | Age  : " << age  << "\n";
        cout << "  | GPA  : " << gpa  << "\n";
        cout << "  +---------------------------+\n";
    }

    // ---- Increase GPA by a delta ----
    void increaseGpa(float delta) {
        gpa += delta;
        if (gpa > 4.0f) gpa = 4.0f;  // cap at 4.0
    }
};


// ============================================================
// SECTION 4: PASSING OBJECT TO FUNCTION — BY VALUE
// ============================================================
// A COPY of the object is passed to the function.
// The copy constructor is invoked automatically.
// Changes made inside the function do NOT affect the original.
// Overhead: involves copying — avoid for large objects.
// ============================================================
void printStudentByValue(Student s) {      // <-- receives a COPY
    cout << "\n[By Value] Inside function — working on a copy:\n";
    s.display();

    // Modifying the copy — original is UNAFFECTED
    s.setGpa(1.0f);
    cout << "  [By Value] GPA changed to 1.0 inside function.\n";
    cout << "  [By Value] This does NOT affect the original object.\n";
}   // <-- destructor called here for the local copy 's'


// ============================================================
// SECTION 5: PASSING OBJECT TO FUNCTION — BY POINTER
// ============================================================
// The ADDRESS of the object is passed.
// No copy is made — efficient for large objects.
// Changes via the pointer DIRECTLY affect the original.
// Use -> operator to access members through a pointer.
// ============================================================
void upgradeStudentByPointer(Student* sPtr) {  // <-- receives address
    cout << "\n[By Pointer] Inside function — working on original via pointer:\n";
    cout << "  Before upgrade:\n";
    sPtr->display();

    sPtr->increaseGpa(0.5f);   // modifies the ORIGINAL object
    cout << "  [By Pointer] GPA increased by 0.5 on the original.\n";

    cout << "  After upgrade:\n";
    sPtr->display();
}   // <-- no destructor called here (no object ownership)


// ============================================================
// SECTION 5B: PASSING OBJECT TO FUNCTION — BY REFERENCE
// ============================================================
// An ALIAS (another name) for the original object is passed.
// No copy is made — efficient, and syntax is cleaner than pointer.
// Changes DIRECTLY affect the original.
// Use . operator (same as normal object access).
// ============================================================
void renameStudentByRef(Student& s, const string& newName) {
    cout << "\n[By Reference] Renaming student inside function...\n";
    s.setName(newName);   // modifies the ORIGINAL object
    cout << "  [By Reference] Name changed to '" << newName << "' on the original.\n";
}


// ============================================================
// SECTION 6: PASSING ARRAY OF OBJECTS TO FUNCTION
// ============================================================
// An array name in C++ is a pointer to its first element.
// So passing an array always passes a pointer — no copy overhead.
// We also pass 'size' because arrays don't carry their length.
// Inside the function, use arr[i] to access each object.
// ============================================================
void displayAllStudents(Student arr[], int size) {
    cout << "\n[Array of Objects] Displaying all " << size << " students:\n";
    for (int i = 0; i < size; i++) {
        cout << "  --- Student [" << i << "] ---\n";
        arr[i].display();
    }
}

// Bonus: compute class average GPA from array
float computeAverageGpa(Student arr[], int size) {
    float total = 0.0f;
    for (int i = 0; i < size; i++) {
        total += arr[i].getGpa();
    }
    return (size > 0) ? (total / size) : 0.0f;
}

// Bonus: find top student (highest GPA) from array
Student& findTopStudent(Student arr[], int size) {
    int topIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i].getGpa() > arr[topIndex].getGpa()) {
            topIndex = i;
        }
    }
    return arr[topIndex];   // return reference to the top student
}


// ============================================================
//  MAIN — Putting It All Together
// ============================================================
int main() {

    cout << "===============================================\n";
    cout << "  C++ INTRO — Classes, Objects & Functions\n";
    cout << "===============================================\n\n";

    // ----------------------------------------------------------
    // Creating Objects (instances of Student class)
    // ----------------------------------------------------------
    cout << "--- Creating Objects ---\n";

    // Calls the DEFAULT constructor
    Student s1;

    // Calls the PARAMETERIZED constructor
    Student s2("Alice", 20, 3.8f, 101);
    Student s3("Bob",   22, 3.5f, 102);

    // Calls the COPY constructor (s4 is a copy of s2)
    Student s4 = s2;

    cout << "\n--- Initial State of s2 ---\n";
    s2.display();

    cout << "\n--- s4 is a copy of s2 ---\n";
    s4.display();

    // ----------------------------------------------------------
    // Heap Allocation with new / delete
    // ----------------------------------------------------------
    cout << "\n--- Heap Object (new/delete) ---\n";
    Student* heapStudent = new Student("Charlie", 21, 3.2f, 103);
    cout << "  Heap student created:\n";
    heapStudent->display();

    // When done, we MUST manually call delete to free memory.
    // This triggers the destructor explicitly.
    delete heapStudent;
    cout << "  Heap student deleted (destructor called above).\n";

    // ----------------------------------------------------------
    // Passing by Value
    // ----------------------------------------------------------
    cout << "\n========================================\n";
    cout << "  PASSING OBJECT BY VALUE\n";
    cout << "========================================\n";

    printStudentByValue(s2);   // s2 is COPIED into 's' inside function

    cout << "\n  [Main] s2 after byValue call (unchanged):\n";
    s2.display();

    // ----------------------------------------------------------
    // Passing by Pointer
    // ----------------------------------------------------------
    cout << "\n========================================\n";
    cout << "  PASSING OBJECT BY POINTER\n";
    cout << "========================================\n";

    upgradeStudentByPointer(&s2);   // pass address of s2

    cout << "\n  [Main] s2 after byPointer call (GPA changed):\n";
    s2.display();

    // ----------------------------------------------------------
    // Passing by Reference
    // ----------------------------------------------------------
    cout << "\n========================================\n";
    cout << "  PASSING OBJECT BY REFERENCE\n";
    cout << "========================================\n";

    renameStudentByRef(s3, "Robert");   // s3's name changes

    cout << "\n  [Main] s3 after byRef call (name changed):\n";
    s3.display();

    // ----------------------------------------------------------
    // Array of Objects
    // ----------------------------------------------------------
    cout << "\n========================================\n";
    cout << "  ARRAY OF OBJECTS\n";
    cout << "========================================\n";

    cout << "\n--- Creating array of 4 Students ---\n";

    // Stack array of Student objects — each uses parameterized constructor
    Student classRoom[4] = {
        Student("Diana",   19, 3.9f, 201),
        Student("Edward",  21, 3.4f, 202),
        Student("Fatima",  20, 3.7f, 203),
        Student("George",  23, 3.1f, 204)
    };

    // Pass the entire array + size to a function
    displayAllStudents(classRoom, 4);

    // Compute and display class average GPA
    float avg = computeAverageGpa(classRoom, 4);
    cout << "\n  [Array] Class Average GPA: " << avg << "\n";

    // Find and display the top student
    Student& top = findTopStudent(classRoom, 4);
    cout << "\n  [Array] Top Student:\n";
    top.display();

    // ----------------------------------------------------------
    // Dynamic Array of Objects on Heap
    // ----------------------------------------------------------
    cout << "\n--- Dynamic Array of Objects (Heap) ---\n";
    int n = 3;
    Student* dynArr = new Student[n];   // calls default constructor n times

    // Assign values using setters
    dynArr[0].setName("Hana");   dynArr[0].setAge(20); dynArr[0].setGpa(3.6f); dynArr[0].setId(301);
    dynArr[1].setName("Ivan");   dynArr[1].setAge(22); dynArr[1].setGpa(3.3f); dynArr[1].setId(302);
    dynArr[2].setName("Julia");  dynArr[2].setAge(21); dynArr[2].setGpa(3.8f); dynArr[2].setId(303);

    displayAllStudents(dynArr, n);

    // Free the heap array — calls destructor for each element
    delete[] dynArr;
    cout << "  Dynamic array deleted (destructors called above).\n";

    // ----------------------------------------------------------
    // End of main — stack objects destroyed in reverse order
    // ----------------------------------------------------------
    cout << "\n========================================================\n";
    cout << "  End of main(). Stack objects now being destroyed...\n";
    cout << "  (Note: destructors fire in REVERSE order of creation)\n";
    cout << "========================================================\n";

    return 0;
}


// ============================================================
//  QUICK REFERENCE SUMMARY
// ============================================================
//
//  Concept               Syntax / Notes
//  ─────────────────────────────────────────────────────────
//  Class definition      class MyClass { private: ... public: ... };
//  Default constructor   MyClass() { }
//  Param constructor     MyClass(int x) : member(x) { }
//  Copy constructor      MyClass(const MyClass& other) { }
//  Destructor            ~MyClass() { }
//
//  Object on stack       MyClass obj;          // auto-destroyed
//  Object on heap        MyClass* p = new MyClass();  delete p;
//
//  Pass by value         void f(MyClass obj)   // copy made
//  Pass by pointer       void f(MyClass* ptr)  // use ->
//  Pass by reference     void f(MyClass& ref)  // use .
//
//  Array of objects      MyClass arr[5];
//  Pass array            void f(MyClass arr[], int size)
//  Dynamic array         MyClass* arr = new MyClass[n];  delete[] arr;
//
//  When does copy ctor fire?
//    - Object initialized from another:  MyClass b = a;
//    - Passed BY VALUE to a function
//    - Returned BY VALUE from a function
//
//  When does destructor fire?
//    - Stack object goes out of scope
//    - delete is called on a heap object
//    - delete[] is called on a heap array
// ============================================================
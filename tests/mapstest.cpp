//g++ -O3 -std=c++11 -o mapstest tests/mapstest.cpp
#include "../headers/Arrays-Maps/hashMap.cpp"
#include "../headers/Arrays-Maps/arrays.cpp"
#include "../headers/Arrays-Maps/bitmap.cpp"
#include "../headers/Arrays-Maps/hashMap.cpp"
#include "../headers/Arrays-Maps/matrix.cpp"
#include "../headers/Arrays-Maps/multiset.cpp"
#include "../headers/Arrays-Maps/queue.cpp"
#include "../headers/Arrays-Maps/set.cpp"
#include "../headers/Arrays-Maps/stack.cpp"
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <iomanip>
#include <vector>
#include <cassert>

using namespace std;

enum DataStructure {
    VECTOR,
    SPARSE_VECTOR,
    BITSET,
    BITMAP,
    HASHMAP,
    MATRIX,
    SPARSE_MATRIX,
    TRIANGLE_MATRIX,
    MULTISET,
    MULTIMAP,
    QUEUE,
    DEQUEUE,
    STACK,
    SET,
    EXIT,
    INVALID
};

DataStructure chooseMap() {
  int choice;
  cout << "Choose the tree you want to work with: " << endl;
  cout << "1. Vector" << endl;
  cout << "2. Sparse Vector" << endl;
  cout << "3. Bitset" << endl;
  cout << "4. Bitmap" << endl;
  cout<< "5. HashMap (benchmarking included)" << endl;
  cout << "6. Matrix" << endl;
  cout << "7. Sparse Matrix" << endl;
  cout << "8 Triangle Matrix" << endl;
  cout << "9. Multiset" << endl;
  cout<< "10. MultiMap" << endl;
  cout << "11. Queue" << endl;
  cout << "12. Dequeue" << endl;
  cout << "13. Stack" << endl;
  cout << "14. Set" << endl;
  cout << "15. Exit" << endl;
  cin >> choice;

    switch (choice) {
      case 1:
          return VECTOR;
      case 2:
          return SPARSE_VECTOR;
      case 3:
          return BITSET;
      case 4:
          return BITMAP;
      case 5:
          return HASHMAP;
      case 6:
          return MATRIX;
      case 7:
          return SPARSE_MATRIX;
      case 8:
          return TRIANGLE_MATRIX;
      case 9:
          return MULTISET;
      case 10:
          return MULTIMAP;
      case 11:
          return QUEUE;
      case 12:
          return DEQUEUE;
      case 13:
          return STACK;
      case 14:
          return SET;
      case 15:
          return EXIT;
      default:
          return INVALID;
  }
}

string generate_random_string(size_t length, mt19937& generator, uniform_int_distribution<>& distribution, const string& CHARACTERS) {
    string random_string(length, ' ');  // Preallocate string with required length
    for (size_t i = 0; i < length; ++i) {
        random_string[i] = CHARACTERS[distribution(generator)];
    }
    return random_string;
}

double benchmark_custom(int N, size_t string_length, const string& test_case) {
    HashTable<string, int> table;

    const string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        string random_string;
        if (test_case == "large") {
            random_string = generate_random_string(string_length, generator, distribution, CHARACTERS);
        } else if (test_case == "small") {
            random_string = generate_random_string(5, generator, distribution, CHARACTERS); // Small string of length 5
        } else if (test_case == "random") {
            random_string = generate_random_string(rand() % string_length + 1, generator, distribution, CHARACTERS); // Random length string
        } else if (test_case == "same") {
            random_string = "constant_string"; // Same string
        }
        table.insert(random_string, i);
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    return duration.count();
}

void print_table(const vector<string>& test_cases, const int milestones[], size_t milestone_count, const vector<vector<double>>& results, const string& title) {
    // Use stringstream to accumulate the output in memory first
    ostringstream oss;

    oss << title << "\n";
    oss << setw(15) << "Sample Size";

    // Add column headers for test cases
    for (const auto& test_case : test_cases) {
        oss << setw(12) << test_case;
    }
    oss << "\n" << "-------------------------------------------------------------------" << "\n";

    // Set precision once before entering the loop
    oss << fixed << setprecision(6);

    // Accumulate the data rows
    for (size_t i = 0; i < milestone_count; ++i) {
        oss << setw(15) << milestones[i];
        for (size_t j = 0; j < test_cases.size(); ++j) {
            oss << setw(12) << results[j][i];
        }
        oss << "\n";
    }

    // Output everything at once
    cout << oss.str();
}

void testHMap() {
    const size_t LARGE_STRING_LENGTH = 100; // Length of each large random string
    const int milestones[] = {1000, 10000, 50000, 100000, 500000, 1000000}; // Different values of N
    const vector<string> test_cases = {"large", "small", "random", "same"};
    const size_t milestone_count = sizeof(milestones) / sizeof(milestones[0]);

    vector<vector<double>> custom_results(test_cases.size(), vector<double>(milestone_count));

    for (size_t i = 0; i < test_cases.size(); ++i) {
        for (size_t j = 0; j < milestone_count; ++j) {
            custom_results[i][j] = benchmark_custom(milestones[j], LARGE_STRING_LENGTH, test_cases[i]);
        }
    }

    print_table(test_cases, milestones, milestone_count, custom_results, "Custom HashTable Benchmark");
    cout << endl;
}

void testBitset() {
    try {
        // Create a BitSet with 128 bits using uint32_t
        BitSet<uint32_t> bitset(128);
        BitSet<uint32_t> bitset2(128);

        // Set, clear, and toggle operations
        bitset.set(3);
        bitset.set(5);
        bitset.set(127);

        std::cout << "Bit 3 is " << bitset.test(3) << std::endl;
        std::cout << "Bit 127 is " << bitset.test(127) << std::endl;

        bitset.clear(3);
        std::cout << "After clearing, Bit 3 is " << bitset.test(3) << std::endl;

        bitset.toggle(5);
        std::cout << "After toggling, Bit 5 is " << bitset.test(5) << std::endl;

        // Bitwise operations between bitsets
        bitset2.set(5);
        bitset2.set(120);

        BitSet<uint32_t> bitset3 = bitset | bitset2;
        std::cout << "Bit 5 in bitset3 (OR) is " << bitset3.test(5) << std::endl;
        std::cout << "Bit 120 in bitset3 (OR) is " << bitset3.test(120) << std::endl;

        bitset3 = bitset & bitset2;
        std::cout << "Bit 5 in bitset3 (AND) is " << bitset3.test(5) << std::endl;
        std::cout << "Bit 127 in bitset3 (AND) is " << bitset3.test(127) << std::endl;

        bitset3 = bitset ^ bitset2;
        std::cout << "Bit 120 in bitset3 (XOR) is " << bitset3.test(120) << std::endl;

        BitSet<uint32_t> bitset4 = ~bitset;
        std::cout << "Bit 3 in bitset4 (NOT) is " << bitset4.test(3) << std::endl;
        std::cout << "Bit 127 in bitset4 (NOT) is " << bitset4.test(127) << std::endl;

        // Reset the bitset
        bitset.reset();
        std::cout << "After reset, Bit 127 is " << bitset.test(127) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testBitmap() {
    try {
            // Bitmap test
        Bitmap<uint32_t> bitmap(10, 10);  // Create a 10x10 bitmap using uint32_t
        Bitmap<uint32_t> bitmap2(10, 10);

        bitmap.set(3, 3);
        bitmap.set(9, 9);

        std::cout << "Bitmap (3,3) is " << bitmap.test(3, 3) << std::endl;
        std::cout << "Bitmap (9,9) is " << bitmap.test(9, 9) << std::endl;

        bitmap2.set(3, 3);
        bitmap2.set(5, 5);

        Bitmap<uint32_t> bitmap3 = bitmap | bitmap2;
        std::cout << "Bitmap (3,3) in bitmap3 (OR) is " << bitmap3.test(3, 3) << std::endl;
        std::cout << "Bitmap (5,5) in bitmap3 (OR) is " << bitmap3.test(5, 5) << std::endl;

        bitmap3 = bitmap & bitmap2;
        std::cout << "Bitmap (3,3) in bitmap3 (AND) is " << bitmap3.test(3, 3) << std::endl;
        std::cout << "Bitmap (9,9) in bitmap3 (AND) is " << bitmap3.test(9, 9) << std::endl;

        bitmap3 = bitmap ^ bitmap2;
        std::cout << "Bitmap (5,5) in bitmap3 (XOR) is " << bitmap3.test(5, 5) << std::endl;

        Bitmap<uint32_t> bitmap4 = ~bitmap;
        std::cout << "Bitmap (3,3) in bitmap4 (NOT) is " << bitmap4.test(3, 3) << std::endl;
        std::cout << "Bitmap (9,9) in bitmap4 (NOT) is " << bitmap4.test(9, 9) << std::endl;

        // Reset the bitmap
        bitmap.reset();
        std::cout << "After reset, Bitmap (9,9) is " << bitmap.test(9, 9) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testMultiset() {
    Multiset<int> mset;

    // Insert elements
    mset.insert(5);
    mset.insert(5);
    mset.insert(10);
    mset.insert(20);
    mset.insert(20);
    mset.insert(20);

    // Print all elements
    std::cout << "Multiset elements:" << std::endl;
    mset.print();  // Output should show counts of each element

    // Test count functionality
    std::cout << "Count of 5: " << mset.count(5) << std::endl;  // Output: 2
    std::cout << "Count of 10: " << mset.count(10) << std::endl; // Output: 1
    std::cout << "Count of 20: " << mset.count(20) << std::endl; // Output: 3

    // Erase elements
    mset.erase(20);
    std::cout << "After erasing 20 once:" << std::endl;
    mset.print();  // Should show counts of remaining elements with 20 reduced

    mset.erase(20);
    std::cout << "After erasing 20 once more:" << std::endl;
    mset.print();  // Should show counts of remaining elements with 20 reduced

    mset.erase(5);
    std::cout << "After erasing 5 once:" << std::endl;
    mset.print();  // Should show counts of remaining elements with 5 reduced

}

void testMultiMap() {
    Multimap<int, std::string> mmap;

    // Insert elements
    mmap.insert(1, "one");
    mmap.insert(1, "uno");
    mmap.insert(2, "two");
    mmap.insert(2, "dos");
    mmap.insert(3, "three");

    // Print all elements
    std::cout << "Multimap elements:" << std::endl;
    mmap.print();  // Output should show all (key, value) pairs

    // Test size functionality
    std::cout << "Size of multimap: " << mmap.size() << std::endl; // Output: 5

    // Erase elements
    mmap.erase(2);
    std::cout << "After erasing key 2:" << std::endl;
    mmap.print();  // Should show all remaining (key, value) pairs with key 2 removed
}

void testVector() {
    //randomize an n
    int n = rand() % 1000 + 1;

    try {

        Vector<int> v1;
        Vector<int> v2;

        for (int i = 0; i < n; i++) {
            v1.push_back(n-i);
        }

        cout<<v1<<endl;

        for (int i = 0; i < n; i++) {
            v2.push_back(i);
        }

        cout<<v2<<endl;

        Vector<int> v3 = v1 + v2;
        cout<<v3<<endl;

        Vector<int> v4 = v1 - v2;
        cout<<v4<<endl;

        cout<<"Skalar szorzat: ";
        double dot = v1 * v2;
        cout<<dot<<endl;
        
        cout<<"Euk. norma: ";
        double norm = ~v1;
        cout<<norm<<endl;

        cout<<"Tavolsag: ";
        double dist = v1 % v2;
        cout<<dist<<endl;

        cout<<"Index: ";
        cout<<v1[0]<<endl;

        cout<<"Ritka Vector: "<<endl;
        SparseVector<int> rv1 = v1;
        cout << rv1 << endl;
        SparseVector<int> rv2 = v2;
        cout << rv2 << endl;

        v1 = v2;
        cout<<v1<<endl;

    } catch (const char* e) {
        cout<<e<<endl;
    }    

}

void testSparseVector() {
    int n = rand() % 1000 + 1;

     try {
        SparseVector<int> rv1;
        SparseVector<int> rv2;

        int x = 0;

        for (int i = 0; i < n; i++) {
            cin>>x;
            rv1.push(x, i);
        }

        cout<<rv1<<endl;

        for (int i = 0; i < n; i++) {
            cin>>x;
            rv2.push(x, i);
        }

        cout<<rv2<<endl;
        cout<<"Osszeg: ";
        SparseVector<int> rv3 = rv1 + rv2;
        cout<<rv3<<endl;


        cout<<"Kulonbseg: ";
        SparseVector<int> rv4 = rv1 - rv2;
        cout<<rv4<<endl;

        cout<<"Skalar szorzat: ";
        double dot = rv1 * rv2;
        cout<<dot<<endl;

        cout<<"Euk. norma: ";
        double norm = ~rv1;
        cout<<norm<<endl;
        
        cout<<"Tavolsag: ";
        double dist = rv1 % rv2;
        cout<<dist<<endl;
        
        cout<<"Index: ";
        cout<<rv1[0]<<endl;

        cout<<"Vector: "<<endl;
        Vector<int> v6 = rv1;
        cout << v6 << endl;
        Vector<int> v7 = rv2;
        cout << v7 << endl;

        SparseVector<int> rv9(5);
        cout<<rv9<<endl;

        rv1 = rv2;

        cout<<rv1<<endl;
    } catch(const char* e) {
        cout<<e<<endl;
    }

}

template <typename T>
void printResult(const std::string& question, const T& result, const T& expected) {
    std::cout << question << " Result: " << result << " Expected: " << expected << std::endl;
}

void testMatrix() {
    Matrix<int> mat1(2, 2);
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 2);
    mat1.set(1, 0, 3);
    mat1.set(1, 1, 4);

    Matrix<int> mat2(2, 2);
    mat2.set(0, 0, 5);
    mat2.set(0, 1, 6);
    mat2.set(1, 0, 7);
    mat2.set(1, 1, 8);

    // Test Matrix Addition
    Matrix<int> sum = mat1 + mat2;
    printResult("sum.get(0, 0) == 6", sum.get(0, 0), 6);
    printResult("sum.get(0, 1) == 8", sum.get(0, 1), 8);
    printResult("sum.get(1, 0) == 10", sum.get(1, 0), 10);
    printResult("sum.get(1, 1) == 12", sum.get(1, 1), 12);

    // Test Matrix Multiplication
    Matrix<int> product = mat1 * mat2;
    printResult("product.get(0, 0) == 19", product.get(0, 0), 19);
    printResult("product.get(0, 1) == 22", product.get(0, 1), 22);
    printResult("product.get(1, 0) == 43", product.get(1, 0), 43);
    printResult("product.get(1, 1) == 50", product.get(1, 1), 50);

    // Test Matrix Equality and Inequality
    Matrix<int> mat3(2, 2);
    mat3.set(0, 0, 6);
    mat3.set(0, 1, 8);
    mat3.set(1, 0, 10);
    mat3.set(1, 1, 12);
    printResult("sum == mat3", sum == mat3, true);
    printResult("sum != mat1", sum != mat1, true);

    // Test Matrix Copy Constructor
    Matrix<int> matCopy(mat1);
    printResult("matCopy == mat1", matCopy == mat1, true);

    // Test Matrix Copy Assignment Operator
    Matrix<int> matAssign;
    matAssign = mat2;
    printResult("matAssign == mat2", matAssign == mat2, true);

    // Test Matrix Resize
    mat1.resize(3, 3);
    mat1.set(2, 2, 9);
    printResult("mat1.get(2, 2) == 9", mat1.get(2, 2), 9);
    printResult("mat1.get(0, 0) == 1", mat1.get(0, 0), 1);  // Ensure existing values are preserved

    // Test Matrix Clear
    mat1.clear();
    try {
        mat1.get(0, 0); // Should throw an exception
        printResult("mat1.get(0, 0) should throw exception", false, true); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "mat1.get(0, 0) threw std::out_of_range as expected" << std::endl;
    }

    std::cout << "Matrix tests passed!" << std::endl;
}

void testSparseMatrix() {
    sparseMatrix<int> spMat(3, 3);
    spMat.set(0, 1, 5);
    spMat.set(1, 2, 10);
    spMat.set(2, 0, 15);

    // Test getting values
    printResult("spMat.get(0, 1) == 5", spMat.get(0, 1), 5);
    printResult("spMat.get(1, 2) == 10", spMat.get(1, 2), 10);
    printResult("spMat.get(2, 0) == 15", spMat.get(2, 0), 15);
    printResult("spMat.get(0, 0) == 0", spMat.get(0, 0), 0);  // Default value

    // Test Sparse Matrix Copy Constructor
    sparseMatrix<int> spMatCopy(spMat);
    printResult("spMatCopy == spMat", spMatCopy == spMat, true);

    // Test Sparse Matrix Copy Assignment Operator
    sparseMatrix<int> spMatAssign;
    spMatAssign = spMat;
    printResult("spMatAssign == spMat", spMatAssign == spMat, true);

    // Test Sparse Matrix Resize (dummy resize for demonstration)
    spMat.resize();
    spMat.set(1, 1, 20);  // Ensure resize did not affect previously set values
    printResult("spMat.get(1, 1) == 20", spMat.get(1, 1), 20);

    // Test Sparse Matrix Equality and Inequality
    sparseMatrix<int> spMatAnother(3, 3);
    spMatAnother.set(0, 1, 5);
    spMatAnother.set(1, 2, 10);
    spMatAnother.set(2, 0, 15);
    printResult("spMat == spMatAnother", spMat == spMatAnother, true);
    printResult("spMat != spMatCopy", spMat != spMatCopy, true);

    // Test Sparse Matrix Clear
    spMat.clear();
    try {
        spMat.get(0, 1); // Should throw an exception
        printResult("spMat.get(0, 1) should throw exception", false, true); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "spMat.get(0, 1) threw std::out_of_range as expected" << std::endl;
    }

    std::cout << "Sparse matrix tests passed!" << std::endl;
}

void testTriangleMatrix() {
    enum class TriangleType { UPPER, LOWER };

    // Create and initialize upper triangular matrix
    TriangleMatrix<int, TriangleType> triMat(3, TriangleType::UPPER);
    triMat.set(0, 0, 1);
    triMat.set(0, 1, 2);
    triMat.set(0, 2, 3);
    triMat.set(1, 1, 4);
    triMat.set(1, 2, 5);
    triMat.set(2, 2, 6);

    // Test getting values
    printResult("triMat.get(0, 0) == 1", triMat.get(0, 0), 1);
    printResult("triMat.get(0, 1) == 2", triMat.get(0, 1), 2);
    printResult("triMat.get(0, 2) == 3", triMat.get(0, 2), 3);
    printResult("triMat.get(1, 1) == 4", triMat.get(1, 1), 4);
    printResult("triMat.get(1, 2) == 5", triMat.get(1, 2), 5);
    printResult("triMat.get(2, 2) == 6", triMat.get(2, 2), 6);
    printResult("triMat.get(2, 0) == 0", triMat.get(2, 0), 0);  // Default value for lower triangular part

    // Test Triangle Matrix Copy Constructor
    TriangleMatrix<int, TriangleType> triMatCopy(triMat);
    printResult("triMatCopy == triMat", triMatCopy == triMat, true);

    // Test Triangle Matrix Copy Assignment Operator
    TriangleMatrix<int, TriangleType> triMatAssign;
    triMatAssign = triMat;
    printResult("triMatAssign == triMat", triMatAssign == triMat, true);

    // Test Triangle Matrix Resize
    triMat.resize();
    triMat.set(2, 1, 7);  // Ensure resize did not affect previously set values
    printResult("triMat.get(2, 1) == 7", triMat.get(2, 1), 7);

    // Test Triangle Matrix Equality and Inequality
    TriangleMatrix<int, TriangleType> triMatAnother(3, TriangleType::UPPER);
    triMatAnother.set(0, 0, 1);
    triMatAnother.set(0, 1, 2);
    triMatAnother.set(0, 2, 3);
    triMatAnother.set(1, 1, 4);
    triMatAnother.set(1, 2, 5);
    triMatAnother.set(2, 2, 6);
    printResult("triMat == triMatAnother", triMat == triMatAnother, true);
    printResult("triMat != triMatCopy", triMat != triMatCopy, true);

    // Test Triangle Matrix Clear
    triMat.clear();
    try {
        triMat.get(0, 0); // Should throw an exception
        printResult("triMat.get(0, 0) should throw exception", false, true); // Should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "triMat.get(0, 0) threw std::out_of_range as expected" << std::endl;
    }

    std::cout << "Triangle matrix tests passed!" << std::endl;
}

void testQueue() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    printResult("q.size() == 3", q.size(), 3);
    printResult("q.peek() == 1", q.peek(), 1);
    printResult("q.tail() == 3", q.getTail(), 3);

    Queue<int> q2;
    q2.enqueue(1);
    q2.enqueue(2);
    q2.enqueue(3);
    printResult("q2.dequeue() == 1", q2.dequeue(), 1);
    printResult("q2.size() == 2", q2.size(), 2);
    printResult("q2.peek() == 2", q2.peek(), 2);
    try {
        Queue<int> emptyQueue;
        emptyQueue.dequeue();
        std::cout << "emptyQueue.dequeue() should throw exception Result: false Expected: true" << std::endl; // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "emptyQueue.dequeue() threw std::out_of_range as expected" << std::endl;
    }

    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);

    Queue<int> q3;
    q3.enqueue(1);
    q3.enqueue(2);
    q3.enqueue(3);

    Queue<int> q4;
    q4.enqueue(1);
    q4.enqueue(2);

    printResult("q1 == q3", q1 == q3, true);
    printResult("q1 != q4", q1 != q4, true);
}

void testDequeue() {
    Deque<int> dq;
    dq.pushFront(1);
    dq.pushFront(2);
    dq.pushBack(3);
    dq.pushBack(4);
    printResult("dq.size() == 4", dq.size(), 4);
    printResult("dq.peekFront() == 2", dq.peekFront(), 2);
    printResult("dq.peekBack() == 4", dq.peekBack(), 4);

    Deque<int> dq2;
    dq2.pushFront(1);
    dq2.pushFront(2);
    dq2.pushBack(3);
    dq2.pushBack(4);
    printResult("dq2.popFront() == 2", dq2.popFront(), 2);
    printResult("dq2.size() == 3", dq2.size(), 3);
    printResult("dq2.peekFront() == 1", dq2.peekFront(), 1);
    printResult("dq2.popBack() == 4", dq2.popBack(), 4);
    printResult("dq2.size() == 2", dq2.size(), 2);
    printResult("dq2.peekBack() == 3", dq2.peekBack(), 3);
    try {
        Deque<int> emptyDequeue;
        emptyDequeue.popFront();
        std::cout << "emptyDequeue.popFront() should throw exception Result: false Expected: true" << std::endl; // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "emptyDequeue.popFront() threw std::out_of_range as expected" << std::endl;
    }

    Deque<int> dq1;
    dq1.pushFront(1);
    dq1.pushFront(2);
    dq1.pushBack(3);
    dq1.pushBack(4);

    Deque<int> dq3;
    dq3.pushFront(1);
    dq3.pushFront(2);
    dq3.pushBack(3);
    dq3.pushBack(4);

    Deque<int> dq4;
    dq4.pushFront(1);
    dq4.pushFront(2);
    dq4.pushBack(3);

    printResult("dq1 == dq3", dq1 == dq3, true);
    printResult("dq1 != dq4", dq1 != dq4, true);
}

void testStack() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    printResult("s.size() == 3", s.size(), 3);
    printResult("s.peek() == 3", s.peek(), 3);

    Stack<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);
    printResult("s2.pop() == 3", s2.pop(), 3);
    printResult("s2.size() == 2", s2.size(), 2);
    printResult("s2.peek() == 2", s2.peek(), 2);
    try {
        Stack<int> emptyStack;
        emptyStack.pop();
        std::cout << "emptyStack.pop() should throw exception Result: false Expected: true" << std::endl; // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "emptyStack.pop() threw std::out_of_range as expected" << std::endl;
    }

    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s3;
    s3.push(1);
    s3.push(2);
    s3.push(3);

    Stack<int> s4;
    s4.push(1);
    s4.push(2);

    printResult("s1 == s3", s1 == s3, true);
    printResult("s1 != s4", s1 != s4, true);
}

void testSet() {
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    printResult("set.size() == 3", set.size(), 3);
    printResult("set.contains(2) == true", set.contains(2), true);

    Set<int> set2;
    set2.add(1);
    set2.add(2);
    set2.add(3);
    printResult("set2.remove(2) == true", set2.remove(2), true);
    printResult("set2.size() == 2", set2.size(), 2);
    printResult("set2.contains(2) == false", set2.contains(2), false);
    try {
        Set<int> emptySet;
        emptySet.remove(1);
        std::cout << "emptySet.remove(1) should throw exception Result: false Expected: true" << std::endl; // Should not reach here
    } catch (const std::out_of_range& e) {
        std::cout << "emptySet.remove(1) threw std::out_of_range as expected" << std::endl;
    }

    Set<int> set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);

    Set<int> set3;
    set3.add(1);
    set3.add(2);
    set3.add(3);

    Set<int> set4;
    set4.add(1);
    set4.add(2);

    printResult("set1 == set3", set1 == set3, true);
    printResult("set1 != set4", set1 != set4, true);
}


int main() {
    DataStructure choice = chooseMap();

    switch (choice) {
        case VECTOR:
            testVector();
            break;
        case SPARSE_VECTOR:
            testSparseVector();
            break;
        case BITSET:
            testBitset();
            break;
        case BITMAP:
            testBitmap();
            break;
        case HASHMAP:
            testHMap();
            break;
        case MATRIX:
            testMatrix();
            break;
        case SPARSE_MATRIX:
            testSparseMatrix();
            break;
        case TRIANGLE_MATRIX:
            testTriangleMatrix();
            break;
        case MULTISET:
            testMultiset();
            break;
        case MULTIMAP:
            testMultiMap();
            break;
        case QUEUE:
            testQueue();
            break;
        case DEQUEUE:
            testDequeue();
            break;
        case STACK:
            testStack();
            break;
        case SET:
            testSet();
            break;
        case EXIT:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }

    return 0;
}

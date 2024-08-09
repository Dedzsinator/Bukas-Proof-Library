//g++ -O3 -std=c++11 -o mapstest tests/mapstest.cpp
#include "../headers/Arrays-Maps/hashMap.cpp"
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <iomanip>
#include <vector>
#include <unordered_map>

using namespace std;

string chooseMap() {
  int choice;
  cout << "Choose the tree you want to work with: " << endl;
  cout << "1. Vector" << endl;
  cout << "2. Sparse Vector" << endl;
  cout << "3. Bitset" << endl;
  cout << "4. Bitmap" << endl;
  cout << "5. Bitarray" << endl; // Add BTree option
  cout<< "6. HashMap (benchmarking included)" << endl;
  cout << "7. Matrix" << endl;
  cout << "8. Sparse Matrix" << endl;
  cout << "9 Triangle Matrix" << endl;
  cout << "10. Multiset" << endl;
  cout<< "11. MultiMap" << endl;
  cout << "12. Queue" << endl;
  cout << "13. Dequeue" << endl;
  cout << "14. Stack" << endl;
  cout << "15. Set" << endl;
  cout << "16. Exit" << endl;
  cin >> choice;

  switch (choice) {
    case 1:
      return "Vector";
    case 2:
      return "Sparse Vector";
    case 3:
      return "Bitset";
    case 4:
      return "Bitmap";
    case 5:
      return "Bitarray";
    case 6:
      return "HashMap";
    case 7:
      return "Matrix";
    case 8:
      return "Sparse Matrix";
    case 9:
      return "Triangle Matrix";
    case 10:
      return "Multiset";
    case 11:
      return "MultiMap";
    case 12:
      return "Queue";
    case 13:
      return "Dequeue";
    case 14:
      return "Stack";
    case 15:
      return "Set";
    case 16:
      return "Exit";
    default:
      return "Invalid choice";
  }
}

string generate_random_string(size_t length) {
    const string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += CHARACTERS[distribution(generator)];
    }
    return random_string;
}

double benchmark_custom(int N, size_t string_length, const string& test_case) {
    HashTable<string, int> table;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        string random_string;
        if (test_case == "large") {
            random_string = generate_random_string(string_length);
        } else if (test_case == "small") {
            random_string = generate_random_string(5); // Small string of length 5
        } else if (test_case == "random") {
            random_string = generate_random_string(rand() % string_length + 1); // Random length string
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
    cout << title << endl;
    cout << setw(15) << "Sample Size";
    for (const auto& test_case : test_cases) {
        cout << setw(12) << test_case;
    }
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (size_t i = 0; i < milestone_count; ++i) {
        cout << setw(15) << milestones[i];
        for (size_t j = 0; j < test_cases.size(); ++j) {
            cout << setw(12) << fixed << setprecision(6) << results[j][i];
        }
        cout << endl;
    }
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

int main() {

    string choice = chooseMap();

    if (choice == "HashMap") {
        testHMap();
    }

    return 0;
}
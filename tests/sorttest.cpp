#include <algorithm> 
#include <chrono>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include "../headers/Misc-Algorithms/Sorting/sorts.cpp"
using namespace std;
#define BIG_SIZE 50000
#define SMALL_SIZE BIG_SIZE / 100

class Timer {

  public:
  chrono::time_point<chrono::high_resolution_clock> start, end;
  long double duration;

    Timer() {
        start = chrono::high_resolution_clock::now();
    }

    ~Timer() {
    }

    long double getDuration() {
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<long double>(end - start).count();
    }
};

vector<string> types = {"constant", "asc", "desc", "smallrange", "random"};
vector<string> names= {"copy", "bubble", "merge", "quick", "inertion", "ska", "shell", "bucket", "radix", "magyar", "heap", "tim", "tree", "count", "std", "skacopy", "grail", "sqrt", "flag", "spagetti", "shelf", "stable"};

vector<int> geninputs(const string& type) {
  srand(time(0));
  vector<int> input; 

  if(type == "constant") {
    int val = rand();
    for(int i = 0; i < BIG_SIZE; i++) {
      input.push_back(val);
    }

  } else if(type == "asc") {
    for(int i = 0; i < BIG_SIZE; i++) {
      input.push_back(i);
    }

  } else if(type == "desc") {
    for(int i = 0; i < BIG_SIZE; i++) {
      input.push_back(BIG_SIZE - i - 1);
    }
  } else if(type == "smallrange") {
    int val = rand() / 2;
    for(int i = 0; i < BIG_SIZE; i++) {
      input.push_back(val + rand() % 100);
    }

  } else if(type == "random") {
    for(int i = 0; i < BIG_SIZE; i++) {
      input.push_back(rand());
    }
  }

  return input;
}

int main() {
    map<string, vector<long double>> results; 
    map<string, double> maxDurations;

    Sorts<vector<int>::iterator> sorts;
    
    vector<bool> executedFlags(names.size(), false);

    for (const auto& type : types) {
        vector<int> input = geninputs(type);
        vector<long double> durations(names.size(), 0);

        for (size_t i = 0; i < names.size(); ++i) {
            auto inputCopy = input;
            Timer t;
            if(names[i] == "copy") {
                std::copy(inputCopy.begin(), inputCopy.end(), inputCopy.begin());
                durations[i] = t.getDuration(); 
                executedFlags[i] = true; 
            } else if (names[i] == "bubble") {
                //sorts.bubbleSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true; 
            } else if (names[i] == "merge") {
                sorts.mergeSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true; 
            } else if (names[i] == "quick") {
                sorts.quickSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if (names[i] == "insert") {
                //sorts.insertionSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true; 
            } else if (names[i] == "shell") {
                sorts.shellSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if (names[i] == "bucket") {
                sorts.bucketSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if (names[i] == "radix") {
                sorts.radixSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if (names[i] == "heap") {
                sorts.heapSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if(names[i] == "tree") {
                sorts.treeSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if(names[i] == "count") {
                sorts.countSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if(names[i] == "tim") {
                sorts.timSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if(names[i] == "magyar") {
                //sorts.magyarSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true;
            } else if(names[i] == "ska") {
                //sorts.skaSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true; 
            } else if(names[i] == "skacopy") {
                //sorts.skaCopySort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true;
            } else if(names[i] == "std") {
                sort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if(names[i] == "grail") {
                //grailSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true;
            } else if(names[i] == "sqrt") {
                //sqrtSort(n, inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true;
            } else if(names[i] == "flag") {
                //americanFlagSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true;
            } else if(names[i] == "spagetti") {
                //spagettiSort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            } else if(names[i] == "shelf") {
                //shelfSort(inputCopy.begin(), inputCopy.end());
                //executedFlags[i] = true;
            } else if(names[i] == "stable") {
                stable_sort(inputCopy.begin(), inputCopy.end());
                executedFlags[i] = true;
            }
            durations[i] = t.getDuration();
        }
        results[type] = durations;
    }

    ofstream file("res.csv");

    for (const auto& type : types) {
        const auto& durations = results[type];
        for (size_t i = 0; i < names.size(); ++i) {
            if (executedFlags[i]) {
                
                if (maxDurations.find(names[i]) == maxDurations.end() || maxDurations[names[i]] < durations[i]) {
                    maxDurations[names[i]] = durations[i];
                }
            }
        }
    }

    for (const auto& type : types) {
        file << right << setw(10) << type << "   ";
        for (size_t i = 0; i < names.size(); ++i) {
            if (executedFlags[i]) {
                file << fixed << setprecision(3) << results[type][i] << "s    "; 
            }
        }
        file << endl; 
    }

    file<<endl;
    

    size_t maxNameLength = 0;
    for (size_t i = 0; i < names.size(); ++i) {
        if (executedFlags[i]) {
            maxNameLength = max(maxNameLength, names[i].length());
        }
    }

    maxNameLength += 3;

    file << right << setw(10) << "worst" << "   ";

    for (size_t i = 0; i < names.size(); ++i) {
        if (executedFlags[i]) {
            
            file << fixed << setprecision(3) << maxDurations[names[i]] << "s    "; 
        }
    }
    file<<endl<<"\t  ";

    // Write the names aligned based on the maximum name length
    for (size_t i = 0; i < names.size(); ++i) {
        if (executedFlags[i]) {
            file << right << setw(maxNameLength) << names[i] << " ";
        }
    }

    file.close();

    return 0;
}
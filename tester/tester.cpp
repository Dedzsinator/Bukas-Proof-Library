#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <xmmintrin.h> // For _mm_prefetch
#include <numeric>

using namespace std;

class Timer {
public:
    using clock = chrono::high_resolution_clock;
    using time_point = clock::time_point;

    static time_point Now() {
        return clock::now();
    }

    template <typename Duration>
    static double Elapsed(time_point start, time_point end) {
        return chrono::duration_cast<Duration>(end - start).count();
    }
};

class Benchmark {
public:
    template <typename Func, typename... Args>
    static void Run(Func func, size_t maxSampleSize, const vector<size_t>& steps, Args&&... args) {
        Timer::time_point totalStart = Timer::Now();

        vector<pair<size_t, double>> results = RunBenchmark(func, maxSampleSize, steps, forward<Args>(args)...);

        Timer::time_point totalEnd = Timer::Now();
        double totalTime = Timer::Elapsed<chrono::nanoseconds>(totalStart, totalEnd) / 1e9;  // Total time in seconds

        ExportResultsToCSV(results, totalTime);
    }

private:
    template <typename T>
    static void PrefetchArgs(const T& arg) {
        _mm_prefetch(reinterpret_cast<const char*>(&arg), _MM_HINT_T0);
    }

    template <typename Func, typename... Args>
    static vector<pair<size_t, double>> RunBenchmark(Func func, size_t maxSampleSize, const vector<size_t>& steps, Args&&... args) {
        vector<pair<size_t, double>> results;

        for (const auto& sampleSize : steps) {
            if (sampleSize > maxSampleSize) break;

            // Prefetch each argument in the pack
            (PrefetchArgs(args), ...);

            auto start = Timer::Now();

            // Execute the function only once
            func(forward<Args>(args)...);

            auto end = Timer::Now();
            double duration = Timer::Elapsed<chrono::nanoseconds>(start, end) / 1e9; // Convert to seconds

            results.push_back({sampleSize, duration});
            cout << "SampleSize: " << sampleSize << ", Time: " << duration << " s" << endl;
        }

        return results;
    }

    static void ExportResultsToCSV(const vector<pair<size_t, double>>& results, double totalTime) {
        ofstream file("benchmark_results.csv");
        file << "SampleSize,Time(s)\n";
        for (const auto& result : results) {
            file << result.first << "," << result.second << "\n";
        }
        file << "TotalTime(s)," << totalTime / 60.0 << "\n";
        file.close();
    }
};
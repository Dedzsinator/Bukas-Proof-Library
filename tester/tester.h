#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <string>

class TestCase {
public:
    // Constructor for functions with no return value
    TestCase(const std::string& name, std::function<void()> testFunc)
        : name(name), testFunc(testFunc), hasReturnValue(false) {}

    // Constructor for functions with return values
    TestCase(const std::string& name, std::function<void()> testFunc, bool returnValue)
        : name(name), testFunc(testFunc), hasReturnValue(true) {}

    void Run() const {
        try {
            testFunc();
            std::cout << "\033[1;32m[PASSED]\033[0m " << name << std::endl; // Green color for passed
        } catch (const std::exception& e) {
            std::cout << "\033[1;31m[FAILED]\033[0m " << name << ": " << e.what() << std::endl; // Red color for failed
        }
    }

    template <typename T>
    void AssertEqual(const T& expected, const T& actual) const {
        if (expected != actual) {
            throw std::runtime_error("Assertion failed: expected " + std::to_string(expected) + ", got " + std::to_string(actual));
        }
    }

    void AssertEqual(const std::string& expected, const std::string& actual) const {
        if (expected != actual) {
            throw std::runtime_error("Assertion failed: expected \"" + expected + "\", got \"" + actual + "\"");
        }
    }

private:
    std::string name;
    std::function<void()> testFunc;
    bool hasReturnValue;
};

class TestSuite {
public:
    // Add a test case with no return value
    static void AddTest(const std::string& name, std::function<void()> testFunc) {
        tests.emplace_back(name, testFunc);
    }

    // Add a test case with a return value
    template <typename T>
    static void AddTest(const std::string& name, std::function<T()> testFunc, const T& expected) {
        tests.emplace_back(name, [testFunc, expected]() {
            T result = testFunc();
            TestSuite::AssertEqual(expected, result);
        });
    }

    static void RunAllTests() {
        for (const auto& test : tests) {
            test.Run();
        }
    }

private:
    static void AssertEqual(const std::string& expected, const std::string& actual) {
        if (expected != actual) {
            throw std::runtime_error("Assertion failed: expected \"" + expected + "\", got \"" + actual + "\"");
        }
    }

    static std::vector<TestCase> tests;
};

// Initialize the static member
std::vector<TestCase> TestSuite::tests;

#define TEST_CASE(name) \
void name(); \
__attribute__((constructor)) void register_##name() { \
    TestSuite::AddTest(#name, name); \
} \
void name()

#endif // TEST_FRAMEWORK_H
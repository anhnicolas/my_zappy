/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Test
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <optional>
#include <chrono>
#include <memory>

class TestResult {
    public:
        TestResult() = default;
        ~TestResult() = default;
        void setOutput(std::string output);
        void setError(std::string error);
        void setReturn(uint8_t ret);
        void setRunnedTime(std::chrono::milliseconds runned_time);
        std::string getOutput();
        std::string getError();
        uint8_t getReturn();
        std::chrono::milliseconds getRunnedTime();
        void setFailed(bool failed);
        bool getFailed();

    private:
        std::string _output = "";
        std::string _error = "";
        uint8_t _return = 0;
        std::chrono::milliseconds _runnedTime = std::chrono::milliseconds(0);
        bool _failed = false;
};

class Test {
    public:
        Test(std::string title, std::vector<std::string> params, std::string expectedOutput, std::string expectedError, int expectedReturn, std::optional<std::chrono::seconds> timeout);
        ~Test() = default;
        TestResult run(std::string binaryPath);
        std::string _title;
        std::vector<std::string> _params;
        std::string _expectedOutput;
        std::string _expectedError;
        int _expectedReturn;
    private:
        std::optional<std::chrono::seconds> _timeout;
};

class Tester {
    public:
        Tester(const std::string& binaryPath);
        ~Tester() = default;
        void test();
        void addTest(std::string title, std::vector<std::string> params, std::string expectedOutput, std::string expectedError, int expectedReturn, std::optional<std::chrono::seconds> timeout);
        void addTest(Test test);
    private:
        std::string _binaryPath;
        std::map<std::string, std::shared_ptr<Test>> _tests;
        std::optional<std::chrono::seconds> _timeout;
};


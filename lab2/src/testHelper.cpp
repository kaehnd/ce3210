/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-03-23 16:58:56
 * @ Description:
 */
#include "testHelper.h"
#include "matrix.h"
#include <iostream>
#include <sstream>

using namespace std;

static const string red = "\x1b[31m";
static const string green = "\x1b[32m";
static const string clrRst = "\x1b[0m";
static int failedAssertions = 0;
static int passedAssertions = 0;
static string currentTestName;
/*
 * Initialize test session and print start message
 */
void startTests(string testName)
{
    currentTestName = testName;
    cout << "\n*********************************************"
            "\nStarting Tests for " << testName<< "...\n"
            "*********************************************\n";
}

/*
 * End a test session and print results
 */
void finishTests()
{
    cout << "\n*********************************************"
            "\nEnd Tests for "
         << currentTestName << "...\n"
         << green << passedAssertions << " assertions passed" << clrRst << "\n"
         << (failedAssertions ? red : green) << failedAssertions
         << " assertions failed " << clrRst
         << "\n"
            "*********************************************\n\n";
}

/*
 * Asserts that the provided condition is true
 */
void _withMeta_assertTrue(const string file, const string function, int lineNum,
                          int condition)
{
    if (condition)
    {
        _withMeta_assertTestPass();
    }
    else
    {
        _withMeta_assertTestFail(file, function, lineNum, "True", "False");
    }
}

/*
 * Asserts that the provided condition is false
 */
void _withMeta_assertFalse(const string file, const string function,
                           int lineNum, int condition)
{
    if (condition)
    {
        _withMeta_assertTestFail(file, function, lineNum, "False", "True");
    }
    else
    {
        _withMeta_assertTestPass();
    }
}

/*
 * Asserts that the provided integers are equal
 */
void _withMeta_assertEqual(const string file, const string function,
                           int lineNum, int expected, int actual)
{
    if (expected == actual)
    {
        _withMeta_assertTestPass();
    }
    else
    {
        _withMeta_assertTestFail(file, function, lineNum, to_string(expected),
                                 to_string(actual));
    }
}

/*
 * Asserts that the provided doubles are equal
 */
void _withMeta_assertEqual(const string file, const string function,
                           int lineNum, double expected, double actual)
{
    if (expected == actual)
    {
        _withMeta_assertTestPass();
    }
    else
    {
        _withMeta_assertTestFail(file, function, lineNum, to_string(expected),
                                 to_string(actual));
    }
}

/*
 * Asserts that the provided matrices are equal
 */
void _withMeta_assertEqual(const string file, const string function,
                           int lineNum, const matrix &expected,
                           const matrix &actual)
{
    if (expected == actual)
    {
        _withMeta_assertTestPass();
    }
    else
    {
        stringstream ex;
        stringstream act;
        ex << expected;
        act << actual;
        _withMeta_assertTestFail(file, function, lineNum, ex.str(), act.str());
    }
}

/*
 * Prints a failure message based on an expected condition that was not met
 * Counts the failure internally
 */
void _withMeta_assertTestFail(const string file, const string function,
                              int lineNum, string expected, string actual)
{
    cout << red
         << "TEST FAIL\n\n..in file "<< file
         << "\n\n..in function "<< function
         << "\n\n..at line "<< lineNum
         << "\n\nExpected: "<< expected 
         << "\tActual: " << actual << clrRst << "\n\n\n";
    failedAssertions++;
}

/*
 * Counts a test pass internally
 */
void _withMeta_assertTestPass() { passedAssertions++; }

/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-03-23 15:00:48
 * @ Description: Collection of methods to handle console output for running
 * tests
 */
#ifndef TESTHELPER
#define TESTHELPER
#include "matrix.h"
#include <string>

using namespace std;

// quality of life macros to avoid calling functions with calling metadata each
// time
#define assertTrue(condition)                                                  \
    _withMeta_assertTrue(__FILE__, __FUNCTION__, __LINE__, condition)
#define assertFalse(condition)                                                 \
    _withMeta_assertFalse(__FILE__, __FUNCTION__, __LINE__, condition)
#define assertEqual(expected, actual)                                          \
    _withMeta_assertEqual(__FILE__, __FUNCTION__, __LINE__, expected, actual)
#define assertTestFail(expected, actual)                                       \
    _withMeta_assertTestFail(__FILE__, __FUNCTION__, __LINE__, expected, actual)
#define assertTestPass() _withMeta_assertTestPass()

/*
 * Initialize test session and print start message
 */
void startTests(string testName);

/*
 * End a test session and print results
 */
void finishTests();

/*
 * Asserts that the provided condition is true
 */
void _withMeta_assertTrue(const string file, const string function, int lineNum,
                          int condition);

/*
 * Asserts that the provided condition is false
 */
void _withMeta_assertFalse(const string file, const string function,
                           int lineNum, int condition);

/*
 * Asserts that the provided integers are equal
 */
void _withMeta_assertEqual(const string file, const string function,
                           int lineNum, int a, int b);

void _withMeta_assertEqual(const string file, const string function,
                           int lineNum, double expected, double actual);

/*
 * Asserts that the provided matrices are equal
 */
void _withMeta_assertEqual(const string file, const string function,
                           int lineNum, const matrix &expected,
                           const matrix &actual);

/*
 * Prints a failure message based on an expected condition that was not met
 * Counts the failure internally
 */
void _withMeta_assertTestFail(const string file, const string function,
                              int lineNum, string expected, string actual);

/*
 * Counts a test pass internally
 */
void _withMeta_assertTestPass();

#endif
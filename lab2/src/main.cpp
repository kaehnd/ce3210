/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-03-23 15:00:55
 * @ Description: Test driver for the matrix class
 */

#include "matrix.h"
#include "testHelper.h"
#include <iostream>

using namespace std;

// Create a matrix of the specified size with defined values, useful for testing
static matrix createMatrix(unsigned int numRows, unsigned int numCols,
                           double values[])
{
    matrix toReturn(numRows, numCols);

    for (unsigned int i = 0; i < numRows; i++)
    {
        for (unsigned int j = 0; j < numCols; j++)
        {
            double toAssign = values[i * numCols + j];
            toReturn[i][j] = toAssign;
        }
    }
    return toReturn;
}

static void testCopyConstructor()
{
    double vals[] = {1, 2, 3, 4, 5, 6};
    matrix test = createMatrix(3, 2, vals);
    matrix copy(test);
    assertEqual(test, copy);
}

static void testIdentityConstructor()
{
    matrix test(4, 4);
    matrix identity = matrix::identity(4);
    assertEqual(test, identity);

    try
    {
        matrix err = matrix::identity(0);
        assertTestFail("matrixException when instantiating 0x0 matrix",
                       "no error");
    }
    catch (matrixException &me)
    {
        assertTestPass();
    }
}

static void testMatrixAdd()
{
    double op1Vals[] = {1, 2, 3, 4, 5, 6};

    double op2Vals[] = {6, 5, 4, 3, 2, 1};

    double expectedVals[] = {7, 7, 7, 7, 7, 7};

    matrix op1 = createMatrix(2, 3, op1Vals);
    matrix op2 = createMatrix(2, 3, op2Vals);
    matrix expected = createMatrix(2, 3, expectedVals);

    matrix result = op1 + op2;
    assertEqual(expected, result);

    matrix oddSize(5, 6);
    try
    {
        cout << op1 + oddSize;
        assertTestFail(
            "matrixException when addming matrices of different sizes",
            "no error");
    }
    catch (matrixException &me)
    {
        assertTestPass();
    }
}

static void testMatrixMultiply()
{
    double op1Vals[] = {1, 2, 3, 4, 5, 6};

    double op2Vals[] = {0, 2, 1, 3, 2, 4};

    double expectedVals[] = {8, 20, 17, 47};

    matrix op1 = createMatrix(2, 3, op1Vals);
    matrix op2 = createMatrix(3, 2, op2Vals);
    matrix expected = createMatrix(2, 2, expectedVals);

    matrix result = op1 * op2;
    assertEqual(expected, result);

    try
    {
        cout << op1 * result;
        assertTestFail("matrixException when multiplying matrices of differing "
                       "inner dimensions",
                       "no error");
    }
    catch (matrixException &me)
    {
        assertTestPass();
    }
}

static void testMatrixScalarMultiply()
{
    double testVals[] = {1, 2, 3, 4, 5, 6};

    double expectedVals[] = {2, 4, 6, 8, 10, 12};

    matrix test = createMatrix(2, 1, testVals);
    matrix expected = createMatrix(2, 1, expectedVals);

    matrix result = 2 * test;

    matrix otherResult = test * 2;

    assertEqual(expected, result);
    assertEqual(expected, otherResult);
}

static void testMatrixTranspose()
{
    double testVals[] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};

    double expectedVals[] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};

    matrix m1 = createMatrix(3, 4, testVals);
    matrix expected = createMatrix(4, 3, expectedVals);

    matrix result = ~m1;

    assertEqual(expected, result);
}

static void testIndexing()
{
    double vals[] = {1, 2, 3, 4, 5, 6};
    matrix test = createMatrix(3, 2, vals);

    assertEqual(test[0][0], 1.0);
    assertEqual(test[1][1], 4.0);
    assertEqual(test[2][0], 5.0);

    try
    {
        cout << test[3][0];
        assertTestFail("matrixException when accessing illegal row",
                       "no error");
    }
    catch (const matrixException &e)
    {
        assertTestPass();
    }
    try
    {
        cout << test[0][2];
        assertTestFail("matrixException when accessing illegal column",
                       "no error");
    }
    catch (const matrixException &e)
    {
        assertTestPass();
    }
}

int main(void)
{

    startTests("Matrix Class");

    testCopyConstructor();
    testIdentityConstructor();
    testMatrixAdd();
    testMatrixMultiply();
    testMatrixScalarMultiply();
    testMatrixTranspose();
    testIndexing();

    finishTests();

    return 0;
}

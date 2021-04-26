/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-25 21:20:08
 * @ Description: matrix class implementation
 */
#include "matrix.h"
#include <cmath>
#include <cstdarg>
#include <cstring>
#include <functional>
#include <sstream>
#include <string>

//****matrixVector implementation************
// Constructs a matrixVector pointing to the given memory
matrix::matrixVector::matrixVector(double *values, int length, int stepSize)
    : values(NULL), length(0)
{
    if (this->values != NULL)
    {
        delete[] this->values;
    }
    this->length = length;
    this->values = new double *[length];
    // point internal double pointers to the given heap
    for (unsigned int i = 0; i < this->length; i++)
    {
        this->values[i] = &values[i * stepSize];
    }
}

// Destruct the vector. DOES NOT FREE PASSED EXTERNAL MEMORY (values )
matrix::matrixVector::~matrixVector()
{
    delete[] values;
}

// Takes sum of vector values
double matrix::matrixVector::sum() const
{
    double sum = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        sum += (*this)[i];
    }
    return sum;
}

// Inserts the vector as characters to the provided string
std::ostream &matrix::matrixVector::out(std::ostream &os) const
{
    os << "[";
    for (unsigned int i = 0; i < length - 1; i++)
    {
        os << (*this)[i] << ", ";
    }
    return os << (*this)[length - 1] << "]";
}

// Assigns double values from anothermatrixVector OF EQUAL LENGTH
matrix::matrixVector &matrix::matrixVector::operator=(const matrixVector &other)
{
    if (&other != this)
    {
        if (length != other.length)
        {
            throw matrixException(
                "matrixVector does not support assignment of matrix of "
                "different length");
        }
        for (unsigned int i = 0; i < length; i++)
        {
            double &ref = (*this)[i];
            ref = other[i];
        }
    }
    return (*this);
}

// Adds constant value to all values of matrixVector
matrix::matrixVector &matrix::matrixVector::operator+=(const double offset)
{
    for (unsigned int i = 0; i < length; i++)
    {
        (*this)[i] += offset;
    }
    return (*this);
}

// Adds values of other to this elementwise
matrix::matrixVector &
matrix::matrixVector::operator+=(const matrixVector &other)
{
    if (length != other.length)
    {
        throw matrixException("Can't multiply vectors of unequal length");
    }
    for (unsigned int i = 0; i < length; i++)
    {
        (*this)[i] += other[i];
    }
    return (*this);
}

// Multiplies all values of this by passed scale
matrix::matrixVector &matrix::matrixVector::operator*=(const double scale)
{
    for (unsigned int i = 0; i < length; i++)
    {
        (*this)[i] *= scale;
    }
    return (*this);
}

// Multiplies this vector elementwise byother
matrix::matrixVector &
matrix::matrixVector::operator*=(const matrixVector &other)
{
    if (length != other.length)
    {
        throw matrixException("Can't multiply vectors of unequal length");
    }
    for (unsigned int i = 0; i < length; i++)
    {
        (*this)[i] *= other[i];
    }
    return (*this);
}

// Performs a dot product of the two vectors
double matrix::matrixVector::operator*(const matrixVector &other) const
{
    if (length != other.length)
    {
        throw matrixException(
            "Can't do dot product of vectors of unequal length");
    }
    double toReturn = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        toReturn += (*this)[i] * other[i];
    }
    return toReturn;
}

// Gets reference to value pointed by index
double &matrix::matrixVector::operator[](unsigned int index)
{
    if (index >= length)
    {
        throw matrixException(
            "Tried to access outside bounds of matrix columns");
    }
    return *values[index];
}

// Gets value pointed by index
double matrix::matrixVector::operator[](unsigned int index) const
{
    if (index >= length)
    {
        throw matrixException(
            "Tried to access outside bounds of matrix columns");
    }
    return *values[index];
}

//****matrix implementation****
// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols)
    : matrixHeap(NULL), rows(NULL), cols(NULL), numRows(rows), numCols(cols)
{
    if (rows < 1 || cols < 1)
    {
        throw matrixException("Row and column counts of a matrix must be > 0");
    }
    initMatrixMemory();
    clear();
}

matrix::matrix(unsigned int rows, unsigned int cols,
               std::initializer_list<double> values)
    : matrixHeap(NULL), rows(NULL), cols(NULL), numRows(rows), numCols(cols)
{
    if (rows < 1 || cols < 1)
    {
        throw matrixException("Row and column counts of a matrix must be > 0");
    }
    initMatrixMemory();

    if (values.size() == numRows * numCols)
    {
        memcpy(matrixHeap, values.begin(), numRows * numCols * sizeof(double));
    }
    else
    {
        throw matrixException(
            "Initializer list size did not match size of matrix");
    }
}


// Copy constructor
matrix::matrix(const matrix &from)
    : matrixHeap(NULL), rows(NULL), cols(NULL), numRows(from.numRows),
      numCols(from.numCols)
{
    initMatrixMemory();
    memcpy(matrixHeap, from.matrixHeap, numRows * numCols * sizeof(double));
}



// Destructor
matrix::~matrix()
{
    freeMatrixMemory();
}

// Assignment operator
matrix &matrix::operator=(const matrix &rhs)
{
    if (&rhs != this)
    {
        if (numCols != rhs.numCols || numRows != rhs.numRows)
        {
            freeMatrixMemory();
            numRows = rhs.numRows;
            numCols = rhs.numCols;
            initMatrixMemory();
        }
        memcpy(matrixHeap, rhs.matrixHeap, numRows * numCols * sizeof(double));
    }
    return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
    return matrix(size, size);
}

// Binary operations
matrix matrix::operator+(const matrix &rhs) const
{
    if (numCols != rhs.numCols || numRows != rhs.numRows)
    {
        throw matrixException("Size must be equal for matrix addition");
    }
    matrix retVal(*this);

    for (unsigned int i = 0; i < numRows; i++)
    {
        *retVal.rows[i] += *rhs.rows[i];
    }
    return retVal;
}

// Performs matrix multiplication
matrix matrix::operator*(const matrix &rhs) const
{
    if (numCols != rhs.numRows)
    {
        throw matrixException("LHS column number must match "
                              "RHS row number for matrix multiply");
    }
    matrix retVal(numRows, rhs.numCols);

    for (unsigned int i = 0; i < numRows; i++)
    {
        for (unsigned int j = 0; j < rhs.numCols; j++)
        {
            // Set each value on result via dot product of lhs row and rhs
            // column
            retVal[i][j] = (*rows[i]) * (*rhs.cols[j]);
        }
    }
    return retVal;
}

// Performs scalar multiplication to matrix
matrix matrix::operator*(const double scale) const
{
    matrix retVal(*this);

    for (unsigned int i = 0; i < numRows; i++)
    {
        *retVal.rows[i] *= scale;
    }
    return retVal;
}

// Performs transpose of matrix (swap rows & cols)
matrix matrix::operator~() const
{
    matrix retVal(numCols, numRows);

    for (unsigned int i = 0; i < numCols; i++)
    {
        // swapping by assignment utilizing the matrixVector class
        *retVal.rows[i] = *cols[i];
    }
    return retVal;
}

// Sets all values to zero
void matrix::clear()
{
    memset(matrixHeap, 0, numRows * numCols * sizeof(double));
}

// Get row
matrix::matrixVector &matrix::operator[](unsigned int row)
{
    if (row >= numRows)
    {
        throw matrixException("Tried to access outside bounds of matrix rows");
    }
    return *rows[row];
}

// Get row (const)
const matrix::matrixVector &matrix::operator[](unsigned int row) const
{
    if (row >= numRows)
    {
        throw matrixException("Tried to access outside bounds of matrix rows");
    }
    return *rows[row];
}

// Inserts matrix into passed stream
std::ostream &matrix::out(std::ostream &os) const
{
    os << "[";
    (*rows[0]).out(os) << std::endl << " ";

    for (unsigned int i = 1; i < numRows - 1; i++)
    {
        (*rows[i]).out(os) << std::endl << " ";
    }
    return (*rows[numRows - 1]).out(os) << "]";
}

// Deep compares matrix objects by each double value
bool matrix::operator==(const matrix &rhs) const
{
    if (numRows != rhs.numRows || numCols != rhs.numCols)
    {
        return false; // not equal if size differs
    }
    for (unsigned int i = 0; i < numRows; i++)
    {
        for (unsigned int j = 0; j < numCols; j++)
        {
            if ((*this)[i][j] != rhs[i][j])
            {
                return false; // not equal if any value differs
            }
        }
    }
    return true;
}

// Free all memory
void matrix::freeMatrixMemory()
{
    if (matrixHeap != NULL)
    {
        delete[] matrixHeap;
    }
    if (cols != NULL)
    {
        for (unsigned int i = 0; i < numCols; i++)
        {
            delete cols[i];
        }
        delete[] cols;
    }
    if (rows != NULL)
    {
        for (unsigned int i = 0; i < numRows; i++)
        {
            delete rows[i];
        }
        delete[] rows;
    }
}

// Allocate all memory; assumes numRows and numCols are set
void matrix::initMatrixMemory()
{
    rows = new matrixVector *[numRows];
    cols = new matrixVector *[numCols];

    // Raw memory block to store doubles that rows & cols will point to
    matrixHeap = new double[numRows * numCols];

    // Instantiate rows and cols of matrixVectors pointing to matrixHeap
    for (unsigned int i = 0; i < numRows; i++)
    {
        rows[i] = new matrixVector(&matrixHeap[i * numCols], numCols, 1);
    }
    for (unsigned int i = 0; i < numCols; i++)
    {
        cols[i] = new matrixVector(&matrixHeap[i], numRows, numCols);
    }
}

// Global insertion and operator
std::ostream &operator<<(std::ostream &os, const matrix &rhs)
{
    return rhs.out(os);
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix &rhs)
{
    return rhs * scale;
}

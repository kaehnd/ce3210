#include "matrix.h"
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include <cstdarg>
#include <functional>


// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols)
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}

	this->rows = new matrixVector[rows];
	this->cols = new matrixVector[cols];
	matrixHeap = new double[rows*cols];


	for (int i = 0; i < rows; i++)
	{
		(this->rows)[i].setSpace(matrixHeap, cols, 1);
	}

	for (int i = 0; i < cols; i++)
	{
		this->cols[i].setSpace(matrixHeap, rows, cols);
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	// the_matrix = new double[rows*cols];
	// memcpy(the_matrix, from.the_matrix, rows*cols);
}

// Destructor
matrix::~matrix()
{
	// delete [] the_matrix;
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	if (&rhs != this)
	{
		delete [] matrixHeap;
		delete [] cols;
		delete [] rows;

		numRows = rhs.numRows;
		numCols = rhs.numCols;

		rows = new matrixVector[numRows];
		cols = new matrixVector[numCols];
		matrixHeap = new double[numRows*numCols];

		memcpy(matrixHeap, rhs.matrixHeap, numRows*numCols);
		for (int i = 0; i < numRows; i++)
		{
			(this->rows)[i].setSpace(matrixHeap, numCols, 1);
		}

		for (int i = 0; i < numCols; i++)
		{
			this->cols[i].setSpace(matrixHeap, numRows, numCols);
		}


	}
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	// use p-constructor
	return matrix(size,size);
}




// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	if (numCols != rhs.numCols || numRows != rhs.numRows)
	{
		throw new matrixException("Can't do that");
	}

	matrix retVal(rhs);

	for (int i = 0; i < numRows; i++)
	{
		retVal.rows[i] += this->rows[i];
	}

	return retVal;
}



matrix matrix::operator*(const matrix& rhs) const
{

	if (numCols!= rhs.numRows)
	{
		
	}
	// stub
	matrix retVal(rhs);
	return retVal;
}

matrix matrix::operator*(const double scale) const
{
	// stub
	matrix retVal(*this);
	return retVal;
}


// Unary operations
matrix matrix::operator~() const
{
	// stub
	matrix retVal(*this);
	return retVal;
}
	

void matrix::clear()
{
	// stub
	return;
}

double* matrix::operator[](unsigned int row)
{
	// stub
	return NULL;
}

double* matrix::operator[](unsigned int row) const
{
	// stub
	return NULL;
}


std::ostream& matrix::out(std::ostream& os) const
{
	// stub
	return os;	
}



// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	// stub
	os << "todo";
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	// stub
	matrix retval(rhs);
	return retval;
}



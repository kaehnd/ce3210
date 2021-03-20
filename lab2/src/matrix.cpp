#include "matrix.h"
#include <string>
#include <cmath>
#include <cstring>
#include <sstream>
#include <cstdarg>
#include <functional>


matrix::matrixVector::matrixVector():values(NULL),length(0){}

matrix::matrixVector::matrixVector(double * values, int length, int stepSize):values(NULL),length(0)
{
	setSpace(values, length, stepSize);
}
//matrixVector(matrixVector& other);
matrix::matrixVector::~matrixVector()
{
	delete [] values;
}


double matrix::matrixVector::sum() const
{
	double sum = 0;
	for (unsigned int i = 0; i < length; i++)
	{
		sum+= (*this)[i];
	}
	return sum;
}

void matrix::matrixVector::setSpace(double * values, int length, int stepSize)
{
	if (this->values != NULL)
	{
		delete [] this->values;
	}
	this->length = length;

	this->values = new double*[length];

	for (unsigned int i = 0; i < this->length; i++)
	{
		this->values[i] = &values[i*stepSize];
	}
}


std::ostream & matrix::matrixVector::out(std::ostream& os) const
{
	os<<"[";
	for (unsigned int i = 0; i < length; i++)
	{
		os<<(*this)[i]<<", ";
	}
	return os<<"]";
}

matrix::matrixVector& matrix::matrixVector::operator = (const matrixVector & other)
{
	if (values != NULL || length != other.length)
	{
		delete [] values;
		values = new double*[length];
	}
	for (unsigned int i = 0; i < length; i++)
	{
		(*this)[i]=other[i];
	}	
	return (*this);
}


matrix::matrixVector& matrix::matrixVector::operator += (const double scale)
{
	for (unsigned int i = 0; i < length; i++)
	{
		(*this)[i] += scale;
	}
	return (*this);

}
matrix::matrixVector& matrix::matrixVector::operator += (const matrixVector & other)
{
	for (unsigned int i = 0; i < length; i++)
	{
		(*this)[i] += other[i];
	}
	return (*this);
}
matrix::matrixVector& matrix::matrixVector::operator*=(const double scale)
{
	for (unsigned int i = 0; i < length; i++)
	{
		(*this)[i] *= scale;
	}
	return (*this);
}

double& matrix::matrixVector::operator[](unsigned int index)
{
	if (index > length)
	{
		throw new matrixException("Tried to access outside bounds of matrix columns");
	}
	return *values[index];
}
double matrix::matrixVector::operator[](unsigned int index) const
{
	if (index > length)
	{
		throw new matrixException("Tried to access outside bounds of matrix columns");
	}
	return *values[index];
}

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols) : matrixHeap(NULL),rows(NULL),cols(NULL), numRows(rows), numCols(cols)
{  
	if (rows < 1 || cols < 1)
	{
		throw matrixException("p-constructor bad arguments");
	}

	this->rows = new matrixVector[rows];
	this->cols = new matrixVector[cols];
	matrixHeap = new double[rows*cols];

	for (unsigned int i = 0; i < rows; i++)
	{
		(this->rows)[i].setSpace(&matrixHeap[i*numCols], numCols, 1);
	}

	for (unsigned int i = 0; i < cols; i++)
	{
		this->cols[i].setSpace(&matrixHeap[i], numRows, numCols);
	}

	clear();
}

// Copy constructor
matrix::matrix(const matrix& from):matrixHeap(NULL),rows(NULL),cols(NULL),numRows(from.numRows),numCols(from.numCols)
{
	(*this)=from;
}

// Destructor
matrix::~matrix()
{
	delete [] rows;
	delete [] cols;
	delete [] matrixHeap;
	
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	if (&rhs != this)
	{
		if (matrixHeap != NULL)
		{
			delete [] matrixHeap;
		}

		if (cols != NULL)
		{
			delete [] cols;
		}

		if (rows != NULL)
		{
			delete [] rows;
		}

		numRows = rhs.numRows;
		numCols = rhs.numCols;

		rows = new matrixVector[numRows];
		cols = new matrixVector[numCols];
		matrixHeap = new double[numRows*numCols];

		memcpy(matrixHeap, rhs.matrixHeap, numRows*numCols*sizeof(double));
		for (unsigned int i = 0; i < numRows; i++)
		{
			this->rows[i].setSpace(&matrixHeap[i*numCols], numCols, 1);
		}

		for (unsigned int i = 0; i < numCols; i++)
		{
			this->cols[i].setSpace(&matrixHeap[i], numRows, numCols);
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

	for (unsigned int i = 0; i < numRows; i++)
	{
		retVal.rows[i] += this->rows[i];
	}

	return retVal;
}



matrix matrix::operator*(const matrix& rhs) const
{
	if (numCols!= rhs.numRows)
	{
		throw new matrixException("Can't do that");
	}
	matrix retVal(numRows, rhs.numCols);

	for (unsigned int i = 0; i < numCols; i++)
	{
		retVal.cols[i] = cols[i];
		retVal.cols[i] *= rhs.rows[i].sum();
	}

	return retVal;
}

matrix matrix::operator*(const double scale) const
{
	matrix retVal(*this);

	for (unsigned int i = 0; i < numRows; i++)
	{
		retVal.rows[i] *= scale;
	}

	return retVal;
}


// Unary operations
matrix matrix::operator~() const
{
	matrix retVal(numCols, numRows);

	for (unsigned int i = 0; i < numCols; i++)
	{
		retVal.rows[i] = cols[i];
	}
	return retVal;
}
	

void matrix::clear()
{
	memset(matrixHeap, 0, numRows*numCols*sizeof(double));
}

matrix::matrixVector& matrix::operator[](unsigned int row)
{
	if (row > numRows)
	{
		throw new matrixException("Tried to access outside bounds of matrix rows");
	}
	return rows[row];
}

const matrix::matrixVector& matrix::operator[](unsigned int row) const
{
	if (row > numRows)
	{
		throw new matrixException("Tried to access outside bounds of matrix rows");
	}
	return rows[row];
}


std::ostream& matrix::out(std::ostream& os) const
{
	os<<"[";
	if (numRows > 0)
	{
		rows[1].out(os)<<std::endl;
	}

	for (unsigned int i = 1; i < numRows; i++)
	{
		os<<" ";
		rows[i].out(os)<<std::endl;
	}

	os<<"]";

	return os;
}

// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	return rhs.out(os);
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	return rhs * scale;
}

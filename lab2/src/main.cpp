#include "matrix.h"
#include <iostream>
 
using namespace std;

int main(void)
{
	// test our matrix
	
	matrix m1(3,3);
	
	cout << "m1 - should be all zeros" << endl;
	cout << m1 << endl;
	
	matrix m2 = matrix::identity(3);

	cout << "m2 - should be 3 x 3 identity matrix" << endl;
	cout << m2 << endl;

	matrix m3 = m1 + m2;

	cout << "m3 - should be 3 x 3 identity matrix" << endl;
	cout << m3 << endl;
	
	try
	{
		matrix m4(0,0);	// should throw
		cout << "m4 - exception not thrown (but should have)" << endl;
	}
	catch (matrixException me)
	{
		cout << "m4 - exception expected and thrown" << endl;
	}
	
	return 0;
}		

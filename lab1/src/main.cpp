// code9.cpp
// STL vector
//
#include <iostream>
#include <string>
#include <vector>

using namespace std; // for iostream, string and vector

int main()
{
	// make a vectors
	vector<string> vs;
	
	vs.push_back("one");
	string s = "two";
	string s2 = s;
	s[1]='X';
	vs.push_back(s);
	vs.push_back(s2);
	s = "three";
	vs.push_back(s);
	vs.push_back(s2);
	s[1]='Y';
	vs.push_back(s);

	// iterate	
	for (int i = 0; i < (int) vs.size(); i++)
	{
		cout << vs[i] << ", ";
	}
	cout << endl;

	// get rid of an element
	vs.pop_back();
	
	// better yet - use iterators
	for (vector<string>::iterator it = vs.begin(); it != vs.end(); ++it)
	{
		cout << *it << ", ";
	}
	cout << endl;		
		 
	return 0;
}
	 

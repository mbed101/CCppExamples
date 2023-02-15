//#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main()
{
	// Little endian or big indian?
	unsigned int i = 1;
	char* c = (char*)&i;
	if (*c)
		cout << "Little endian";
	else
		cout << "Big endian";

	return 0;
}

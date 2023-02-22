#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include<functional>

int main(int argc, char** argv)
{
	std::list<std::function<int(int)>> lamblist = {
		[](int x){return x+1;},
		[](int x){return x*2;},
		[](int x){return x-3;}
	};

	int result = 5;
	for(const auto& lambda:lamblist)
	{
		result = lambda(result);
	}

	std::cout << "Result: " << result << std::endl;

	return 0;
}

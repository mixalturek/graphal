#include <iostream>
using namespace std;

#define NUM 10000000
#define DISP 100000

int main(int argc, char* argv[])
{
	int i;
	int tmp;

	for(i = 0; i < NUM; i++)
	{
		tmp = i * 2;

		if(i % DISP == 0)
			cout << "debug: " << i << endl;
	}

	return 0;
}

#include <iostream>
using namespace std;

#define NUM 10000000
#define DISP 100000
#define SIZE 5

int fce(int val)
{
	return val * 2;
}

int main(int argc, char* argv[])
{
	int i;
	int tmp;

	for(i = 0; i < NUM; i++)
	{
		tmp = fce(i);

		if(i % DISP == 0)
			cout << "debug: " << i << endl;
	}

	return 0;
}

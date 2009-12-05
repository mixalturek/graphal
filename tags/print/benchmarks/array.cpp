#include <iostream>
using namespace std;

#define NUM 10000000
#define DISP 100000
#define SIZE 5

int main(int argc, char* argv[])
{
	int i;
	int a[SIZE];

	for(i = 0; i < NUM; i++)
	{
		a[i % SIZE] = i * 2;
		a[i % SIZE]++;

//		if(i % DISP == 0)
//			cout << "debug: " << i << endl;
	}

	return 0;
}


#include "Header.h"


int main()
{
	My_container <int> test;
	for (int i = 0; i < 5; i++)
	{
		test.add(i + 1);
	}
	cout << test.size() << endl;


	My_container<int>::iterator it = test.begin();

	
	for (it = test.begin(); it != test.end(); ++it)
	{
		cout << *it << endl;
	}
	getch();
}

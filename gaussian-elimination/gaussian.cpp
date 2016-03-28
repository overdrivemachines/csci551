#include <iostream>

using namespace std;

int main(void)
{
	int am[5][6] = {
		3, 0, 0, -1, 2, 2,
		1, -2, 1, 0, 4, 10
		8, 0, -8, 1, 0, 16,
		4, 0, 0, 5, -2, -3,
		-3, 5, -8, 6, -5, 1
	};

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
			cout << am[i][j] << " ";
		cout << "\n";
	}
	return 0;
}
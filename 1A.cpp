#include <bits/stdc++.h>

int
main()
{
	int old = INT_MAX;
	int n;
	int c = 0;

	while (std::cin >> n)
	{
		if (n > old)
		{
			c++;
		}

		old = n;
	}

	std::cout << c << std::endl;
}
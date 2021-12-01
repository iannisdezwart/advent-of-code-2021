#include <bits/stdc++.h>

int
main()
{
	std::vector<int> v;
	int n;

	while (std::cin >> n)
	{
		v.push_back(n);
	}

	int c = 0;
	int old = INT_MAX;

	for (size_t i = 2; i < v.size(); i++)
	{
		int s = v[i - 2] + v[i - 1] + v[i];

		if (s > old)
		{
			c++;
		}

		old = s;
	}

	std::cout << c << std::endl;
}
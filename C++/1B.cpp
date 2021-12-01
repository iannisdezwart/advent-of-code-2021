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

	for (size_t i = 3; i < v.size(); i++)
	{
		if (v[i] > v[i - 3])
		{
			c++;
		}
	}

	std::cout << c << std::endl;
}
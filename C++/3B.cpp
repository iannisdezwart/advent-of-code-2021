#include <bits/stdc++.h>

const constexpr int bit_count = 12;
const constexpr int n = 1000;

enum Type
{
	GAMMA,
	EPSILON
};

int
solve(std::vector<std::bitset<bit_count>> v, Type type)
{
	for (int j = bit_count - 1; j >= 0; --j)
	{
		int count = 0;

		for (int i = 0; i < v.size(); i++)
		{
			if (v[i][j])
			{
				count++;
			}
		}

		bool keep;
		std::vector<std::bitset<bit_count>> new_v;

		if (type == GAMMA)
		{
			keep = 2 * count >= v.size();
		}
		else
		{
			keep = 2 * count < v.size();
		}

		for (int i = 0; i < v.size(); i++)
		{
			if (v[i][j] == keep)
			{
				new_v.push_back(v[i]);
			}
		}

		if (new_v.size() == 1)
		{
			return new_v[0].to_ulong();
		}

		v = new_v;
	}

	std::cout << "Error: No solution found" << std::endl;
	exit(1);
}

int
main()
{
	std::vector<std::bitset<bit_count>> v(n);

	for (int i = 0; i < n; i++)
	{
		std::cin >> v[i];
	}

	std::cout << solve(v, GAMMA) * solve(v, EPSILON) << std::endl;
}
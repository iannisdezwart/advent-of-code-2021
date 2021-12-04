#include <bits/stdc++.h>

const constexpr int bit_count = 12;

int
main()
{
	std::bitset<bit_count> b;
	int count[bit_count] = { 0 };
	int n = 0;

	while (std::cin >> b)
	{
		++n;

		for (int i = 0; i < bit_count; ++i)
		{
			count[i] += b[i];
		}
	}

	std::bitset<bit_count> common;

	for (int i = 0; i < bit_count; ++i)
	{
		common[i] = count[i] >= n / 2;
	}

	uint64_t gamma = common.to_ullong();
	uint64_t epsilon = common.flip().to_ullong();

	std::cout << gamma * epsilon << std::endl;
}
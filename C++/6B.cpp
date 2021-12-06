#include <bits/stdc++.h>

#define N_DAYS 256

struct Population
{
	long long arr[9];

	Population()
	{
		memset(arr, 0, sizeof(arr));
	}

	void
	add(int n)
	{
		arr[n]++;
	}

	void
	tick()
	{
		long long new_fish = arr[0];

		for (int i = 0; i < 8; i++)
		{
			arr[i] = arr[i + 1];
		}

		arr[6] += new_fish;
		arr[8] = new_fish;
	}

	size_t
	size()
	{
		size_t s = 0;

		for (int i = 0; i < 9; i++)
		{
			s += arr[i];
		}

		return s;
	}
};

void
solve(Population &pop)
{
	for (int i = 0; i < N_DAYS; i++)
	{
		pop.tick();
	}

	std::cout << pop.size() << std::endl;
}

int
main()
{
	Population pop;
	int c = '\0';

	while (c != EOF)
	{
		c = fgetc(stdin);
		pop.add(c - '0');
		c = fgetc(stdin);
	}

	solve(pop);
}
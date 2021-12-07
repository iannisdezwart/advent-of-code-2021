#include <bits/stdc++.h>

#define N 1000

int
gauss_sum(int i)
{
	return i * (i + 1) / 2;
}

int
main()
{
	std::vector<int> v(N);
	int sum = 0;

	for (int i = 0; i < N; i++)
	{
		std::cin >> v[i];
		getc(stdin);
		sum += v[i];
	}

	int avg = (float) sum / N;
	int align_sum = 0;

	for (int i = 0; i < N; i++)
	{
		align_sum += gauss_sum(std::abs(v[i] - avg));
	}

	std::cout << align_sum << std::endl;
}
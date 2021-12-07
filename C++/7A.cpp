#include <bits/stdc++.h>

#define N 1000

int
main()
{
	std::vector<int> v(N);

	for (int i = 0; i < N; i++)
	{
		std::cin >> v[i];
		getc(stdin);
	}

	std::nth_element(v.begin(), v.begin() + N / 2, v.end());
	int median = v[N / 2];
	int align_sum = 0;

	for (int i = 0; i < N; i++)
	{
		align_sum += std::abs(v[i] - median);
	}

	std::cout << align_sum << std::endl;
}
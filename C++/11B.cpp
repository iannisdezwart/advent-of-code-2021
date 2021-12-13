#include <bits/stdc++.h>

#define WIDTH 10
#define HEIGHT 10

using coord = std::pair<int, int>;
using coord_set = std::unordered_set<coord>;

template <>
struct std::hash<coord>
{
	size_t
	operator()(const coord &c)
	const
	{
		return c.first | (uint64_t) c.second << 32;
	}
};

void
flash(int map[HEIGHT][WIDTH], int x, int y, coord_set &flashes)
{
	if (flashes.count({ x, y }))
	{
		return;
	}

	flashes.insert({ x, y });

	// Top row

	if (y > 0)
	{
		for (int i = std::max(0, x - 1);
			i <= std::min(WIDTH - 1, x + 1); i++)
		{
			map[y - 1][i]++;

			if (map[y - 1][i] > 9)
			{
				flash(map, i, y - 1, flashes);
			}
		}
	}

	// Bottom row

	if (y < HEIGHT - 1)
	{
		for (int i = std::max(0, x - 1);
			i <= std::min(WIDTH - 1, x + 1); i++)
		{
			map[y + 1][i]++;

			if (map[y + 1][i] > 9)
			{
				flash(map, i, y + 1, flashes);
			}
		}
	}

	// Left

	if (x > 0)
	{
		map[y][x - 1]++;

		if (map[y][x - 1] > 9)
		{
			flash(map, x - 1, y, flashes);
		}
	}

	// Right

	if (x < WIDTH - 1)
	{
		map[y][x + 1]++;

		if (map[y][x + 1] > 9)
		{
			flash(map, x + 1, y, flashes);
		}
	}
}

int
tick(int map[HEIGHT][WIDTH])
{
	coord_set flashes;

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			map[y][x]++;
		}
	}

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (map[y][x] > 9)
			{
				flash(map, x, y, flashes);
			}
		}
	}

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (map[y][x] > 9)
			{
				map[y][x] = 0;
			}
		}
	}

	return flashes.size();
}

int
main()
{
	std::string s;

	int map[HEIGHT][WIDTH];

	for (int y = 0; y < HEIGHT; ++y)
	{
		std::getline(std::cin, s);

		for (int x = 0; x < WIDTH; ++x)
		{
			map[y][x] = s[x] - '0';
		}
	}

	int c = 1;

	while (tick(map) != WIDTH * HEIGHT)
	{
		c++;
	}

	std::cout << c << std::endl;
}
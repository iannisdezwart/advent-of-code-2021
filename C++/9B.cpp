#include <bits/stdc++.h>

#define HEIGHT 100
#define WIDTH 100

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

int
search(uint8_t map[HEIGHT][WIDTH], int x, int y, coord_set &vis)
{
	if (vis.count({ x, y }))
	{
		return 0;
	}

	if (map[y][x] == 9)
	{
		return 0;
	}

	int size = 1;

	vis.insert({ x, y });

	if (y + 1 < HEIGHT && map[y + 1][x] > map[y][x])
	{
		size += search(map, x, y + 1, vis);
	}

	if (y - 1 >= 0 && map[y - 1][x] > map[y][x])
	{
		size += search(map, x, y - 1, vis);
	}

	if (x + 1 < WIDTH && map[y][x + 1] > map[y][x])
	{
		size += search(map, x + 1, y, vis);
	}

	if (x - 1 >= 0 && map[y][x - 1] > map[y][x])
	{
		size += search(map, x - 1, y, vis);
	}

	return size;
}

int
main()
{
	uint8_t map[HEIGHT][WIDTH];
	std::string s;
	std::vector<int> basins;

	for (int y = 0; y < HEIGHT; y++)
	{
		std::getline(std::cin, s);

		for (int x = 0; x < WIDTH; x++)
		{
			map[y][x] = s[x] - '0';
		}
	}

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (y + 1 < HEIGHT && map[y + 1][x] <= map[y][x])
			{
				continue;
			}

			if (y - 1 >= 0 && map[y - 1][x] <= map[y][x])
			{
				continue;
			}

			if (x + 1 < WIDTH && map[y][x + 1] <= map[y][x])
			{
				continue;
			}

			if (x - 1 >= 0 && map[y][x - 1] <= map[y][x])
			{
				continue;
			}

			coord_set vis;
			basins.push_back(search(map, x, y, vis));
		}
	}

	std::sort(basins.rbegin(), basins.rend());
	std::cout << basins[0] * basins[1] * basins[2] << std::endl;
}
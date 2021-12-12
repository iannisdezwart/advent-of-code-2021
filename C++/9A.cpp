#include <bits/stdc++.h>

#define HEIGHT 100
#define WIDTH 100

int
main()
{
	uint8_t map[HEIGHT][WIDTH];
	std::string s;
	int c = 0;

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

			c += 1 + map[y][x];
		}
	}

	std::cout << c << std::endl;
}
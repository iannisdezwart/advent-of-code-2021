#include <bits/stdc++.h>

#define N_LINES 500
#define MAX_X 1000
#define MAX_Y 1000

struct Point
{
	int x;
	int y;
};

struct Line
{
	Point p1;
	Point p2;
};

void
solve(std::vector<Line> &lines)
{
	int grid[MAX_Y][MAX_X] = { 0 };

	for (auto [ p1, p2 ] : lines)
	{
		if (p1.x != p2.x && p1.y != p2.y)
		{
			continue;
		}

		if (p1.x == p2.x)
		{
			int y_start = std::min(p1.y, p2.y);
			int y_end = std::max(p1.y, p2.y);

			for (int y = y_start; y <= y_end; y++)
			{
				grid[y][p1.x]++;
			}
		}
		else
		{
			int x_start = std::min(p1.x, p2.x);
			int x_end = std::max(p1.x, p2.x);

			for (int x = x_start; x <= x_end; x++)
			{
				grid[p1.y][x]++;
			}
		}
	}

	int count = 0;

	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (grid[y][x] > 1)
			{
				count++;
			}
		}
	}

	std::cout << count << std::endl;
}

int
main()
{
	std::vector<Line> lines(N_LINES);

	for (int i = 0; i < N_LINES; i++)
	{
		scanf("%d,%d -> %d,%d\n", &lines[i].p1.x, &lines[i].p1.y, &lines[i].p2.x, &lines[i].p2.y);
	}

	solve(lines);
}
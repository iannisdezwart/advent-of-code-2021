#include <bits/stdc++.h>

#define WIDTH 100
#define HEIGHT 100
#define FACTOR 5
#define FULL_WIDTH (WIDTH * FACTOR)
#define FULL_HEIGHT (HEIGHT * FACTOR)
#define INF 0x3f3f3f3f

struct coord
{
	int x;
	int y;

	bool
	operator==(const coord &other)
	const
	{
		return x == other.x && y == other.y;
	}
};

using coord_set = std::unordered_set<coord>;

template <>
struct std::hash<coord>
{
	size_t
	operator()(const coord &c)
	const
	{
		return c.x | (uint64_t) c.y << 32;
	}
};

struct coord_pr
{
	int pr;
	coord c;
};

template <>
struct std::greater<coord_pr>
{
	bool
	operator()(const coord_pr &lhs, const coord_pr &rhs)
	const
	{
		return lhs.pr > rhs.pr;
	}
};

int
dijkstra(int grid[FULL_HEIGHT][FULL_WIDTH])
{
	std::priority_queue<coord_pr, std::vector<coord_pr>,
		std::greater<coord_pr>> q;

	int dists[FULL_HEIGHT][FULL_WIDTH];

	for (int y = 0; y < FULL_HEIGHT; y++)
	{
		for (int x = 0; x < FULL_WIDTH; x++)
		{
			dists[y][x] = INF;
		}
	}

	std::vector<coord> neighbours = {
		{ -1,  0 },
		{  1,  0 },
		{  0, -1 },
		{  0,  1 }
	};

	q.push({ 0, { 0, 0 } });
	dists[0][0] = 0;

	while (!q.empty())
	{
		auto c = q.top().c;
		q.pop();

		if (c == coord { FULL_HEIGHT - 1, FULL_WIDTH - 1 })
		{
			return dists[c.y][c.x];
		}

		for (auto neighbour : neighbours)
		{
			if (c.x + neighbour.x < 0
				|| c.x + neighbour.x >= FULL_HEIGHT
				|| c.y + neighbour.y < 0
				|| c.y + neighbour.y >= FULL_WIDTH)
			{
				continue;
			}

			int from = dists[c.y][c.x];
			int &to = dists[c.y + neighbour.y][c.x + neighbour.x];
			int cost = grid[c.y + neighbour.y][c.x + neighbour.x];

			if (to > from + cost)
			{
				to = from + cost;

				q.push({ to, {
					c.x + neighbour.x,
					c.y + neighbour.y }
				});
			}
		}
	}

	return dists[FULL_HEIGHT - 1][FULL_WIDTH - 1];
}

void
fill_chunk(int grid[FULL_HEIGHT][FULL_WIDTH], int y, int x)
{
	int delta = y + x;
	int start_x = x * WIDTH;
	int start_y = y * HEIGHT;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			int orig = grid[i][j];
			int new_val = orig + delta;

			if (new_val > 9)
			{
				new_val -= 9;
			}

			grid[start_y + i][start_x + j] = new_val;
		}
	}
}

int
main()
{
	std::string s;
	int grid[FULL_HEIGHT][FULL_WIDTH];

	for (int y = 0; y < HEIGHT; y++)
	{
		std::getline(std::cin, s);

		for (int x = 0; x < WIDTH; x++)
		{
			grid[y][x] = s[x] - '0';
		}
	}

	for (int y = 0; y < FACTOR; y++)
	{
		for (int x = 0; x < FACTOR; x++)
		{
			if (y == 0 && x == 0)
			{
				continue;
			}

			fill_chunk(grid, y, x);
		}
	}

	std::cout << dijkstra(grid) << std::endl;
}
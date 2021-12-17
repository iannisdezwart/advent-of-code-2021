#include <bits/stdc++.h>

struct Target
{
	int min_x;
	int max_x;
	int min_y;
	int max_y;

	Target(int x1, int x2, int y1, int y2)
	{
		this->min_x = std::min(x1, x2);
		this->max_x = std::max(x1, x2);
		this->min_y = std::min(y1, y2);
		this->max_y = std::max(y1, y2);
	}

	bool
	inside(int x, int y)
	const
	{
		return x >= min_x && x <= max_x && y >= min_y && y <= max_y;
	}
};

int
fire(const Target &target, int dx, int dy)
{
	int x = 0;
	int y = 0;
	int max = INT_MIN;

	while (x <= target.max_x && y >= target.max_y)
	{
		x += dx;
		y += dy;

		if (dx)
		{
			dx--;
		}

		dy--;

		max = std::max(max, y);

		if (target.inside(x, y))
		{
			return max;
		}
	}

	return INT_MIN;
}

int
solve(const Target &target)
{
	int max = INT_MIN;

	for (int y = target.max_y; y <= -target.min_y; y++)
	{
		for (int x = 0; x <= target.max_x; x++)
		{
			max = std::max(fire(target, x, y), max);
		}
	}

	return max;
}

int
main()
{
	std::string s;
	std::getline(std::cin, s);

	int x1, x2, y1, y2;

	size_t x1_index = s.find("x=") + 2;
	size_t x1_end_index = s.find("..", x1_index);

	x1 = std::stoi(s.substr(x1_index, x1_end_index - x1_index));

	size_t x2_index = x1_end_index + 2;
	size_t x2_end_index = s.find(",", x1_index);

	x2 = std::stoi(s.substr(x2_index, x2_end_index - x2_index));

	size_t y1_index = s.find("y=") + 2;
	size_t y1_end_index = s.find("..", y1_index);

	y1 = std::stoi(s.substr(y1_index, y1_end_index - y1_index));

	size_t y2_index = y1_end_index + 2;
	size_t y2_end_index = s.find(",", y1_index);

	y2 = std::stoi(s.substr(y2_index, y2_end_index - y2_index));

	std::cout << solve({ x1, x2, y1, y2 }) << std::endl;
}
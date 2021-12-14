#include <bits/stdc++.h>

using coord = std::pair<int, int>;
using coord_v = std::vector<coord>;
using coord_set = std::unordered_set<coord>;
using fold = std::pair<char, int>;
using fold_v = std::vector<fold>;

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
print(coord_v &v)
{
	int max_x = INT_MIN;
	int max_y = INT_MIN;

	for (auto &c : v) {
		max_x = std::max(max_x, c.first);
		max_y = std::max(max_y, c.second);
	}

	for (int y = 0; y <= max_y; ++y)
	{
		for (int x = 0; x <= max_x; ++x)
		{
			if (std::find(v.begin(), v.end(), coord(x, y)) != v.end())
			{
				std::cout << '#';
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
}

void
do_fold(coord_v &c, fold &f)
{
	if (f.first == 'x')
	{
		for (auto it = c.begin(); it != c.end(); ++it)
		{
			auto &i = *it;

			if (i.first == f.second)
			{
				c.erase(it);
			}
			else if (i.first > f.second)
			{
				i.first = f.second - (i.first - f.second);
			}
		}
	}

	else
	{
		for (auto it = c.begin(); it != c.end(); ++it)
		{
			auto &i = *it;

			if (i.second == f.second)
			{
				c.erase(it);
			}
			else if (i.second > f.second)
			{
				i.second = f.second - (i.second - f.second);
			}
		}
	}
}

int
main()
{
	std::string s;
	coord_v c;
	fold_v f;

	// Coords

	while (std::getline(std::cin, s), s != "")
	{
		int index = s.find(",");
		int x = std::stoi(s.substr(0, index));
		int y = std::stoi(s.substr(index + 1));
		c.push_back({ x, y });
	}

	// Folds

	while (std::getline(std::cin, s))
	{
		int index = s.find("=");
		char axis = s[index - 1];
		int value = std::stoi(s.substr(index + 1));
		f.push_back({ axis, value });
	}

	for (auto &i : f)
	{
		do_fold(c, i);
	}

	coord_set set;

	for (auto &i : c)
	{
		set.insert(i);
	}

	print(c);
}
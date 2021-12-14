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

	do_fold(c, f[0]);

	coord_set set;

	for (auto &i : c)
	{
		set.insert(i);
	}

	std::cout << set.size() << std::endl;
}
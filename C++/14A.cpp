#include <bits/stdc++.h>

using cc_p = std::pair<char, char>;
using cc_m = std::unordered_map<cc_p, char>;

template <>
struct std::hash<cc_p>
{
	size_t
	operator()(const cc_p &p) const
	{
		return p.first | ((uint16_t) p.second << 8);
	}
};

void
insert(std::vector<char> &v, const cc_m &map)
{
	std::vector<char> new_v;

	for (int i = 0; i < v.size() - 1; ++i) {
		char a = v[i];
		char b = v[i + 1];

		auto it = map.find(std::make_pair(a, b));

		if (it == map.end())
		{
			new_v.push_back(a);
		}
		else
		{
			new_v.push_back(a);
			new_v.push_back(it->second);
		}
	}

	new_v.push_back(v.back());

	v = std::move(new_v);
}

int
solve(std::vector<char> &v)
{
	std::unordered_map<char, int> map;

	for (char c : v)
	{
		map[c]++;
	}

	int max = INT_MIN;
	int min = INT_MAX;

	for (auto &p : map)
	{
		if (p.second > max)
		{
			max = p.second;
		}

		if (p.second < min)
		{
			min = p.second;
		}
	}

	return max - min;
}

int
main()
{
	std::vector<char> v;
	std::string s;
	std::getline(std::cin, s);
	cc_m map;

	for (char c : s)
	{
		v.push_back(c);
	}

	std::getline(std::cin, s);

	while (std::getline(std::cin, s))
	{
		char a = s[0];
		char b = s[1];
		char c = s[6];

		map[{ a, b }] = c;
	}

	for (int i = 0; i < 10; i++)
	{
		insert(v, map);
	}

	std::cout << solve(v) << std::endl;
}
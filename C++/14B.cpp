#include <bits/stdc++.h>

using cc_p = std::pair<char, char>;
using cc_m = std::unordered_map<cc_p, char>;
using cnt_m = std::unordered_map<cc_p, long long>;

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
insert(cnt_m &cnt, const cc_m &map)
{
	cnt_m new_cnt;

	for (auto &p : cnt)
	{
		char a = p.first.first;
		char b = p.first.second;

		auto it = map.find({ a, b });

		if (it == map.end())
		{
			new_cnt[p.first] = p.second;
		}
		else
		{
			new_cnt[{ a, it->second }] += p.second;
			new_cnt[{ it->second, b }] += p.second;
		}
	}

	cnt = std::move(new_cnt);
}

long long
solve(cnt_m &cnt)
{
	std::unordered_map<char, long long> map;

	for (auto &i : cnt)
	{
		map[i.first.first] += i.second;
		map[i.first.second] += i.second;
	}

	long long max = LONG_LONG_MIN;
	long long min = LONG_LONG_MAX;

	for (auto &p : map)
	{
		if (p.first == ' ')
		{
			continue;
		}

		long long cnt = p.second / 2;

		if (cnt > max)
		{
			max = cnt;
		}

		if (cnt < min)
		{
			min = cnt;
		}
	}

	return max - min;
}

int
main()
{
	cnt_m cnt;
	std::string s;
	std::getline(std::cin, s);
	cc_m map;

	// Header and trailer

	cnt[{ ' ', s[0] }] = 1;
	cnt[{ s.back(), ' ' }] = 1;

	for (int i = 0; i < s.size() - 1; ++i) {
		char a = s[i];
		char b = s[i + 1];
		cnt[{ a, b }]++;
	}

	std::getline(std::cin, s);

	while (std::getline(std::cin, s))
	{
		char a = s[0];
		char b = s[1];
		char c = s[6];

		map[{ a, b }] = c;
	}

	for (int i = 0; i < 40; i++)
	{
		insert(cnt, map);
	}

	std::cout << solve(cnt) << std::endl;
}
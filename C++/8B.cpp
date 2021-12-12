#include <bits/stdc++.h>

std::string
complement(const std::string &str)
{
	bool map[7] = { 0 };

	for (char c : str)
	{
		map[c - 'a'] = true;
	}

	std::string res;

	for (int i = 0; i < 7; ++i)
	{
		if (!map[i])
		{
			res += (i + 'a');
		}
	}

	return res;
}

int
main()
{
	std::string s;
	int sum = 0;

	while (std::getline(std::cin, s))
	{
		size_t index = s.find('|');
		std::stringstream left_stream(s.substr(0, index));
		std::stringstream right_stream(s.substr(index + 1));
		std::vector<std::string> left;
		std::vector<std::string> right;

		while (left_stream >> s)
		{
			left.push_back(s);
		}

		while (right_stream >> s)
		{
			right.push_back(s);
		}

		constexpr const int top_left     = 1 << 0;
		constexpr const int bottom_left  = 1 << 1;
		constexpr const int top_right    = 1 << 2;
		constexpr const int bottom_right = 1 << 3;
		constexpr const int top          = 1 << 4;
		constexpr const int middle       = 1 << 5;
		constexpr const int bottom       = 1 << 6;

		constexpr const int one = top_right | bottom_right;
		constexpr const int four = top_left | middle | top_right
			| bottom_right;
		constexpr const int seven = top | top_right | bottom_right;

		constexpr const int size_6 = top_left | top | bottom | bottom_right;
		constexpr const int size_5 = top | middle | bottom;

		uint8_t map[7]; memset(map, 0x7F, sizeof(map));

		for (size_t i = 0; i < left.size(); i++)
		{
			switch (left[i].size())
			{
			case 2:
				// Has to be a one.

				for (char c : left[i])
				{
					map[c - 'a'] &= one;
				}

				for (char c : complement(left[i]))
				{
					map[c - 'a'] &= ~one;
				}

				break;

			case 3:
				// Has to be a seven.

				for (char c : left[i])
				{
					map[c - 'a'] &= seven;
				}

				for (char c : complement(left[i]))
				{
					map[c - 'a'] &= ~seven;
				}

				break;

			case 4:
				// Has to be a four.

				for (char c : left[i])
				{
					map[c - 'a'] &= four;
				}

				for (char c : complement(left[i]))
				{
					map[c - 'a'] &= ~four;
				}

				break;

			case 5:
				for (char c : complement(left[i]))
				{
					map[c - 'a'] &= ~size_5;
				}

				break;

			case 6:
				// Zero, six or nine.

				for (char c : complement(left[i]))
				{
					map[c - 'a'] &= ~size_6;
				}

				break;

			default:;
			}
		}

		int mult = 1000;
		int running_sum = 0;

		#define OUT(n) running_sum += (n) * mult; mult /= 10

		for (const std::string &str : right)
		{
			switch (str.size())
			{
				case 2:
					OUT(1);
					goto next;

				case 3:
					OUT(7);
					goto next;

				case 4:
					OUT(4);
					goto next;

				case 5:
				{
					std::string comp = complement(str);

					if (comp.size() != 2)
					{
						printf("ambiguous\n");
						goto next;
					}

					uint8_t d1 = map[comp[0] - 'a'];
					uint8_t d2 = map[comp[1] - 'a'];

					switch (d1 | d2)
					{
					case top_left | bottom_left:
						OUT(3);
						break;

					case top_left | bottom_right:
						OUT(2);
						break;

					case top_right | bottom_left:
						OUT(5);
						break;

					default:
						if (d1 & bottom_right ||
							d2 & bottom_right)
						{
							OUT(2);
							break;
						}

						if (d1 & top_right ||
							d2 & top_right)
						{
							OUT(5);
							break;
						}

						printf("what?\n");

						break;
					}

					goto next;
				}

				case 6:
				{
					std::string comp = complement(str);

					if (comp.size() != 1)
					{
						printf("ambiguous\n");
						goto next;
					}

					uint8_t d = map[comp[0] - 'a'];

					switch (d)
					{
					case top_right:
						OUT(6);
						break;

					case bottom_left:
						OUT(9);
						break;

					case middle:
						OUT(0);
						break;

					default:
						printf("what?\n");
						break;
					}

					goto next;
				}

				case 7:
					OUT(8);
					goto next;

				default:;
			}

			next:;
		}

		sum += running_sum;
	}

	std::cout << sum << std::endl;
}
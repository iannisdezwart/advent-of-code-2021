#include <bits/stdc++.h>

int
main()
{
	std::string s;
	int n;

	int dep = 0;
	int hor = 0;
	int aim = 0;

	while (std::cin >> s >> n)
	{
		switch (s[0])
		{
			case 'f':
				hor += n;
				dep += aim * n;
				break;

			case 'u':
				aim -= n;
				break;

			case 'd':
				aim += n;
				break;
		}
	}

	std::cout << dep * hor << std::endl;
}
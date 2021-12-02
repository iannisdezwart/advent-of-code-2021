#include <bits/stdc++.h>

int
main()
{
	std::string s;
	int n;

	int dep = 0;
	int hor = 0;

	while (std::cin >> s >> n)
	{
		switch (s[0])
		{
			case 'f':
				hor += n;
				break;

			case 'u':
				dep -= n;
				break;

			case 'd':
				dep += n;
				break;
		}
	}

	std::cout << dep * hor << std::endl;
}
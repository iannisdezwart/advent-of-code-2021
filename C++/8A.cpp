#include <bits/stdc++.h>

int
main()
{
	std::string s;
	int c = 0;

	while (std::getline(std::cin, s))
	{
		size_t index = s.find('|');
		s = s.substr(index + 1);

		std::stringstream ss(s);

		while (ss >> s)
		{
			switch (s.size())
			{
				case 2:
				case 3:
				case 4:
				case 7:
					c++;
					break;

				default:;
			}
		}
	}

	std::cout << c << std::endl;
}
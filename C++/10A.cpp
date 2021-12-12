#include <bits/stdc++.h>

int
check(const std::string &str)
{
	std::stack<char> st;
	char top;

	for (char c : str)
	{
		switch (c)
		{
		case '(':
		case '[':
		case '{':
		case '<':
			st.push(c);
			break;

		case ')':
			top = st.top(); st.pop();

			if (top != '(')
			{
				return 3;
			}

			break;

		case ']':
			top = st.top(); st.pop();

			if (top != '[')
			{
				return 57;
			}

			break;

		case '}':
			top = st.top(); st.pop();

			if (top != '{')
			{
				return 1197;
			}

			break;

		case '>':
			top = st.top(); st.pop();

			if (top != '<')
			{
				return 25137;
			}

			break;
		}
	}

	return 0;
}

int
main()
{
	std::string s;
	int c = 0;

	while (std::getline(std::cin, s))
	{
		c += check(s);
	}

	std::cout << c << std::endl;
}
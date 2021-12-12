#include <bits/stdc++.h>

long long
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
				return 0;
			}

			break;

		case ']':
			top = st.top(); st.pop();

			if (top != '[')
			{
				return 0;
			}

			break;

		case '}':
			top = st.top(); st.pop();

			if (top != '{')
			{
				return 0;
			}

			break;

		case '>':
			top = st.top(); st.pop();

			if (top != '<')
			{
				return 0;
			}

			break;
		}
	}

	long long c = 0;

	while (st.size())
	{
		top = st.top(); st.pop();
		c *= 5;

		switch (top)
		{
		case '(':
			c += 1;
			break;

		case '[':
			c += 2;
			break;

		case '{':
			c += 3;
			break;

		case '<':
			c += 4;
			break;
		}
	}

	return c;
}

int
main()
{
	std::string s;
	std::vector<long long> v;

	while (std::getline(std::cin, s))
	{
		long long n = check(s);

		if (n != 0)
		{
			v.push_back(n);
		}
	}

	std::sort(v.begin(), v.end());
	std::cout << v[v.size() / 2] << std::endl;
}
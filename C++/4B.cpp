#include <bits/stdc++.h>

#define MARKED -1

struct BingoCard
{
	bool won_flag = false;
	int card[5][5];

	const int *
	operator[](size_t i)
	const
	{
		return card[i];
	}

	int *
	operator[](size_t i)
	{
		return card[i];
	}

	int
	count_unmarked()
	const
	{
		int count = 0;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (card[i][j] != MARKED)
				{
					count += card[i][j];
				}
			}
		}

		return count;
	}

	bool
	won()
	{
		if (won_flag)
		{
			return true;
		}

		// Columns

		for (int x = 0; x < 5; ++x)
		{
			// Assume the whole column is marked.

			for (int y = 0; y < 5; ++y)
			{
				if (card[x][y] != MARKED)
				{
					goto next_column;
				}
			}

			// If we get here, the whole column is marked.

			return won_flag = true;

			next_column:;
		}

		// Rows

		for (int y = 0; y < 5; ++y)
		{
			// Assume the whole row is marked.

			for (int x = 0; x < 5; ++x)
			{
				if (card[x][y] != MARKED)
				{
					goto next_row;
				}
			}

			// If we get here, the whole row is marked.

			return won_flag = true;

			next_row:;
		}

		return false;
	}
};

void
mark(std::vector<BingoCard> &cards, int value)
{
	for (auto &card : cards)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (card[i][j] == value)
				{
					card[i][j] = MARKED;
				}
			}
		}
	}
}

void
solve(std::vector<int> &draws, std::vector<BingoCard> &cards)
{
	for (int value : draws)
	{
		mark(cards, value);

		for (int i = 0; i < cards.size();)
		{
			if (cards[i].won())
			{
				if (cards.size() == 1)
				{
					std::cout
						<< value *
						cards[i].count_unmarked()
						<< std::endl;
					return;
				}

				std::swap(cards[i], cards.back());
				cards.pop_back();
			}
			else
			{
				++i;
			}
		}
	}
}

int
main()
{
	std::vector<int> draws;
	std::string line;

	std::getline(std::cin, line);

	std::istringstream iss(line);

	while (true)
	{
		int n;
		iss >> n;
		draws.push_back(n);

		char c;
		iss >> c;

		if (iss.eof())
		{
			break;
		}
	}

	std::vector<BingoCard> cards;

	while (true)
	{
		BingoCard card;
		int n;

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				std::cin >> n;
				card[i][j] = n;
			}
		}

		cards.push_back(card);

		if (std::cin.eof())
		{
			break;
		}
	}

	solve(draws, cards);
}
#include <bits/stdc++.h>

#define MARKED -1

struct BingoCard
{
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

int
winner(const std::vector<BingoCard> &cards)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		// Columns

		for (int x = 0; x < 5; ++x)
		{
			// Assume the whole column is marked.

			for (int y = 0; y < 5; ++y)
			{
				if (cards[i][x][y] != MARKED)
				{
					goto next_column;
				}
			}

			// If we get here, the whole column is marked.

			return cards[i].count_unmarked();

			next_column:;
		}

		// Rows

		for (int y = 0; y < 5; ++y)
		{
			// Assume the whole row is marked.

			for (int x = 0; x < 5; ++x)
			{
				if (cards[i][x][y] != MARKED)
				{
					goto next_row;
				}
			}

			// If we get here, the whole row is marked.

			return cards[i].count_unmarked();

			next_row:;
		}
	}

	return -1;
}

void
solve(std::vector<int> &draws, std::vector<BingoCard> &cards)
{
	for (int value : draws)
	{
		mark(cards, value);

		int winner_value = winner(cards);

		if (winner_value != -1)
		{
			std::cout << value * winner_value << std::endl;
			return;
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
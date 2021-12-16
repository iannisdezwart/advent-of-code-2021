#include <bits/stdc++.h>

uint8_t
hex_to_i(char hex)
{
	if (hex >= '0' && hex <= '9')
	{
		return hex - '0';
	}

	return hex - 'A' + 10;
}

struct Bits
{
	std::vector<uint8_t> data;

	Bits(std::string s)
	{
		for (size_t i = 0; i < s.size(); i += 2)
		{
			uint8_t c = hex_to_i(s[i]) << 4 | hex_to_i(s[i + 1]);
			data.push_back(c);
		}
	}

	bool
	operator[](size_t index)
	{
		size_t pos = index / 8;
		size_t rem = 7 - index % 8;

		return (data[pos] & (1 << rem)) >> rem;
	}

	size_t
	size()
	const
	{
		return data.size() * 8;
	}

	std::vector<uint8_t>
	slice(size_t start, size_t size)
	{
		std::vector<uint8_t> ret;

		for (size_t i = 0; i < size; i++)
		{
			ret.push_back((*this)[start + i]);
		}

		return ret;
	}
};

struct Block
{
	uint8_t version;
	std::vector<Block *> children;
	std::vector<uint8_t> data;

	enum Type {
		LIT = 4,
		UNKNOWN
	} type;

	Block(uint8_t version, Type type)
		: version(version), type(type) {}

	void
	dfs(std::function<void (Block &, size_t)> cb, size_t depth = 0)
	{
		cb(*this, depth);

		for (auto &child : children)
		{
			child->dfs(cb, depth + 1);
		}
	}

	void
	print(size_t depth)
	const
	{
		std::string out;
		std::string pad(depth, '\t');

		out += pad + "Block:\n";
		out += pad + "- num_children: " + std::to_string(children.size()) + "\n";
		out += pad + "- version: " + std::to_string(version) + "\n";
		out += pad + "- type: " + std::to_string(type) + "\n";
		out += pad + "- data: ";

		for (auto &c : data)
		{
			out += std::to_string(c) + " ";
		}

		std::cout << out << std::endl;
	}
};

struct Parser
{
	size_t i = 0;
	Bits &b;
	std::vector<Block *> blocks;

	Parser(Bits &b) : b(b)
	{
		while (i < b.size())
		{
			blocks.push_back(parse_block());
			align();
		}
	}

	void
	align()
	{
		if (i % 4 != 0)
		{
			i += 4 - (i % 4);
		}
	}

	uint64_t
	read(size_t size)
	{
		uint64_t ret = 0;

		for (size_t j = 0; j < size; j++)
		{
			ret |= b[i + j] << (size - j - 1);
		}

		i += size;

		return ret;
	}

	Block *
	parse_block()
	{
		uint8_t version = read(3);
		Block::Type type = (Block::Type) read(3);

		Block *block = new Block(version, type);

		if (type == Block::LIT)
		{
			parse_literal(*block);
		}
		else
		{
			parse_operator(*block);
		}

		return block;
	}

	void
	parse_literal(Block &block)
	{
		while (parse_literal_chunk(block));
		std::reverse(block.data.begin(), block.data.end());
	}

	bool
	parse_literal_chunk(Block &block)
	{
		bool keep_reading = read(1);
		block.data.push_back(read(4));
		return keep_reading;
	}

	void
	parse_operator(Block &block)
	{
		uint8_t type = read(1);

		if (type == 0)
		{
			uint16_t len = read(15);
			size_t old_i = i;

			while (i < old_i + len)
			{
				block.children.push_back(parse_block());
			}
		}
		else
		{
			uint16_t len = read(11);

			for (size_t i = 0; i < len; i++)
			{
				block.children.push_back(parse_block());
			}
		}
	}
};

int
main()
{
	std::string s;
	std::getline(std::cin, s);
	Bits b(s);
	Parser p(b);

	int c = 0;

	for (Block *block : p.blocks)
	{
		block->dfs([&c](Block &block, size_t depth)
		{
			c += block.version;
		});
	}

	std::cout << c << std::endl;

	// Let the OS clean up the dynamically allocated memory.
}
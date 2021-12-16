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

struct Val
{
	std::vector<uint8_t> data;

	Val(const std::vector<uint8_t>& data)
		: data(data)
	{
		normalise();
	}

	Val(std::vector<uint8_t>&& data)
		: data(std::move(data))
	{
		normalise();
	}

	Val(uint64_t ull)
	{
		for (size_t i = 0; i < 8; i++)
		{
			data.push_back((ull >> (i * 8)) & 0xFF);
		}

		normalise();
	}

	static Val
	unpack(std::vector<uint8_t> data)
	{
		if (data.size() % 2)
		{
			data.push_back(0);
		}

		for (size_t i = 0; i < data.size() / 2; i++)
		{
			data[i] = data[2 * i] | data[2 * i + 1] << 4;
		}

		data.resize(data.size() / 2);

		return Val(std::move(data));
	}

	void
	normalise()
	{
		while (data.size() > 1 && data.back() == 0)
		{
			data.pop_back();
		}
	}

	uint64_t
	to_ull()
	{
		uint64_t ret = 0;

		for (size_t i = 0; i < data.size(); i++)
		{
			ret |= (uint64_t) data[i] << (uint64_t) (i * 8);
		}

		return ret;
	}

	void
	print()
	{
		for (int i = 0; i < data.size(); i++)
		{
			printf("%02X", data[i]);

			if (i != data.size() - 1)
			{
				printf(" ");
			}
		}
	}

	static Val
	max()
	{
		return Val(std::vector<uint8_t>(32, 0xFF));
	}

	static Val
	min(const Val &a, const Val &b)
	{
		if (a.data.size() < b.data.size())
		{
			return Val(a.data);
		}

		if (a.data.size() > b.data.size())
		{
			return Val(b.data);
		}

		for (ssize_t i = a.data.size() - 1; i >= 0; i--)
		{
			if (a.data[i] < b.data[i])
			{
				return Val(a.data);
			}

			return Val(b.data);
		}

		return Val(a.data);
	}

	static Val
	max(const Val &a, const Val &b)
	{
		if (a.data.size() > b.data.size())
		{
			return Val(a.data);
		}

		if (a.data.size() < b.data.size())
		{
			return Val(b.data);
		}

		for (ssize_t i = a.data.size() - 1; i >= 0; i--)
		{
			if (a.data[i] > b.data[i])
			{
				return Val(a.data);
			}

			return Val(b.data);
		}

		return Val(a.data);
	}
};

Val
operator+(const Val &a, const Val &b)
{
	std::vector<uint8_t> data;
	uint8_t carry = 0;

	for (size_t i = 0; i < a.data.size() || i < b.data.size(); i++)
	{
		uint8_t a_val = i < a.data.size() ? a.data[i] : 0;
		uint8_t b_val = i < b.data.size() ? b.data[i] : 0;
		uint16_t sum = a_val + b_val + carry;

		carry = sum >> 8;
		data.push_back(sum & 0xFF);
	}

	if (carry)
	{
		data.push_back(carry);
	}

	return Val(data);
}

Val
operator*(const Val &a, const Val &b)
{
	std::vector<uint8_t> data(a.data.size() + b.data.size(), 0);

	for (size_t i = 0; i < a.data.size(); i++)
	{
		uint8_t carry = 0;

		for (size_t j = 0; j < b.data.size() || carry; j++)
		{
			uint16_t a_val = a.data[i];
			uint16_t b_val = j < b.data.size() ? b.data[j] : 0;
			uint16_t sum = a_val * b_val + carry + data[i + j];

			data[i + j] = sum & 0xFF;
			carry = sum >> 8;
		}
	}

	return Val(data);
}

Val
operator==(const Val &a, const Val &b)
{
	if (a.data.size() != b.data.size())
	{
		return Val({ 0 });
	}

	for (size_t i = 0; i < a.data.size(); i++)
	{
		if (a.data[i] != b.data[i])
		{
			return Val({ 0 });
		}
	}

	return Val({ 1 });
}

Val
operator!=(const Val &a, const Val &b)
{
	Val inv = a == b;

	if (inv.data[0] == 1)
	{
		return Val({ 0 });
	}

	return Val({ 1 });
}

Val
operator<(const Val &a, const Val &b)
{
	if (a.data.size() > b.data.size())
	{
		return Val({ 0 });
	}

	if (a.data.size() < b.data.size())
	{
		return Val({ 1 });
	}

	for (ssize_t i = a.data.size() - 1; i >= 0; i--)
	{
		if (a.data[i] > b.data[i])
		{
			return Val({ 0 });
		}

		if (a.data[i] < b.data[i])
		{
			return Val({ 1 });
		}
	}

	return Val({ 0 });
}

Val
operator>(const Val &a, const Val &b)
{
	if (a.data.size() < b.data.size())
	{
		return Val({ 0 });
	}

	if (a.data.size() > b.data.size())
	{
		return Val({ 1 });
	}

	for (ssize_t i = a.data.size() - 1; i >= 0; i--)
	{
		if (a.data[i] < b.data[i])
		{
			return Val({ 0 });
		}

		if (a.data[i] > b.data[i])
		{
			return Val({ 1 });
		}
	}

	return Val({ 0 });
}

struct Block
{
	uint8_t version;
	std::vector<Block *> children;
	std::vector<uint8_t> data;

	enum Type {
		SUM,
		PRODUCT,
		MIN,
		MAX,
		LIT,
		GREATER,
		LESS,
		EQUAL
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

	Val
	calc()
	const
	{
		switch (type)
		{
			case SUM:
			{
				Val val({ 0 });

				for (auto &child : children)
				{
					Val child_val = child->calc();
					val = val + child_val;
				}

				return val;
			}

			case PRODUCT:
			{
				Val val({ 1 });

				for (auto &child : children)
				{
					Val child_val = child->calc();
					val = val * child_val;
				}

				return val;
			}

			case MIN:
			{
				Val val = Val::max();

				for (auto &child : children)
				{
					Val child_val = child->calc();
					val = Val::min(val, child_val);
				}

				return val;
			}

			case MAX:
			{
				Val val({ 0 });

				for (auto &child : children)
				{
					Val child_val = child->calc();
					val = Val::max(val, child_val);
				}

				return val;
			}

			case LIT:
			{
				Val val = Val::unpack(data);
				return val;
			}

			case GREATER:
			{
				Val a = children[0]->calc();
				Val b = children[1]->calc();
				Val val = a > b;

				return val;
			}

			case LESS:
			{
				Val a = children[0]->calc();
				Val b = children[1]->calc();
				Val val = a < b;

				return val;
			}

			case EQUAL:
			{
				Val a = children[0]->calc();
				Val b = children[1]->calc();
				Val val = a == b;

				return val;
			}

			default:
			{
				std::cerr << "Unknown type: "
					<< type << std::endl;
				exit(1);
			}
		}
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

	void
	calc()
	{
		std::cout << blocks[0]->calc().to_ull() << std::endl;
	}
};

int
main()
{
	std::string s;
	std::getline(std::cin, s);
	Bits b(s);
	Parser p(b);

	p.calc();

	// Let the OS clean up the dynamically allocated memory.
}
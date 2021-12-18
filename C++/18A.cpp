#include <bits/stdc++.h>

std::string
repeat(const std::string &str, size_t count)
{
	std::string out;

	for (size_t i = 0; i < count; ++i)
	{
		out += str;
	}

	return out;
}

struct Node
{
	int val;

	Node *parent;
	Node *left;
	Node *right;

	Node(Node *parent, int val)
		: val(val), parent(parent), left(nullptr), right(nullptr) {}

	bool
	is_leaf()
	const
	{
		return left == nullptr && right == nullptr;
	}

	int
	magnitude()
	{
		if (is_leaf())
		{
			return val;
		}

		return 3 * left->magnitude() + 2 * right->magnitude();
	}

	void
	dfs_before(std::function<void (Node *, size_t)> cb, size_t depth = 0)
	{
		cb(this, depth);

		if (left)
		{
			left->dfs_before(cb, depth + 1);
		}

		if (right)
		{
			right->dfs_before(cb, depth + 1);
		}
	}

	void
	dfs_after(std::function<void (Node *, size_t)> cb, size_t depth = 0)
	{
		if (left)
		{
			left->dfs_after(cb, depth + 1);
		}

		if (right)
		{
			right->dfs_after(cb, depth + 1);
		}

		cb(this, depth);
	}

	void
	reduce()
	{
		Node *four_nested = nullptr;
		Node *ten_or_greater = nullptr;

		dfs_before([&four_nested, &ten_or_greater](
			Node *node, size_t depth)
		{
			if (four_nested == nullptr && depth >= 4
				&& node->left != nullptr
				&& node->left->is_leaf()
				&& node->right != nullptr
				&& node->right->is_leaf())
			{
				four_nested = node;
			}

			if (ten_or_greater == nullptr && node->is_leaf()
				&& node->val >= 10)
			{
				ten_or_greater = node;
			}
		});

		if (four_nested != nullptr)
		{
			four_nested->explode();
		}
		else if (ten_or_greater != nullptr)
		{
			ten_or_greater->split();
		}
		else
		{
			return;
		}

		reduce();
	}

	void
	split()
	{
		int left_val = val / 2;
		int right_val = val - left_val;

		left = new Node(this, left_val);
		right = new Node(this, right_val);
	}

	void
	explode()
	{
		Node *directly_left = find_directly_left();
		Node *directly_right = find_directly_right();

		if (directly_left != nullptr)
		{
			directly_left->val += left->val;
		}

		if (directly_right != nullptr)
		{
			directly_right->val += right->val;
		}

		left = nullptr;
		right = nullptr;
		val = 0;
	}

	static Node *
	add(Node *lhs, Node *rhs)
	{
		Node *root = new Node(nullptr, 0);

		root->left = lhs;
		root->left->parent = root;
		root->right = rhs;
		root->right->parent = root;

		root->reduce();

		return root;
	}

	Node *
	find_left_most_leaf()
	{
		Node *left_most_leaf = nullptr;

		dfs_before([&left_most_leaf](Node *node, size_t depth)
		{
			if (left_most_leaf == nullptr && node->is_leaf())
			{
				left_most_leaf = node;
			}
		});

		return left_most_leaf;
	}

	Node *
	find_right_most_leaf()
	{
		Node *right_most_leaf = nullptr;

		dfs_after([&right_most_leaf](Node *node, size_t depth)
		{
			if (node->is_leaf())
			{
				right_most_leaf = node;
			}
		});

		return right_most_leaf;
	}

	Node *
	find_directly_left()
	{
		Node *node = this;

		while (node->parent != nullptr)
		{
			if (node->parent->left != nullptr
				&& node->parent->left != node)
			{
				return node->parent->left->find_right_most_leaf();
			}

			node = node->parent;
		}

		return nullptr;
	}

	Node *
	find_directly_right()
	{
		Node *node = this;

		while (node->parent != nullptr)
		{
			if (node->parent->right != nullptr
				&& node->parent->right != node)
			{
				return node->parent->right->find_left_most_leaf();
			}

			node = node->parent;
		}

		return nullptr;
	}

	friend std::ostream &
	operator<<(std::ostream &os, const Node &node)
	{
		if (node.is_leaf())
		{
			os << node.val;
		}
		else
		{
			os << "[";
			os << *node.left << "," << *node.right;
			os << "]";
		}

		return os;
	}
};

struct Parser
{
	const std::string &str;
	size_t i;

	Parser(const std::string &str)
		: str(str), i(0) {}

	char
	read()
	{
		return str[i++];
	}

	[[ noreturn ]] void
	syntax_err()
	{
		exit(1);
	}

	void
	expect(char c)
	{
		if (read() != c)
		{
			fprintf(stderr, "Expected '%c' at %zu\n", c, i);
			syntax_err();
		}
	}

	Node *
	parse(Node *parent = nullptr)
	{
		char c = read();

		if (c == '[')
		{
			Node *node = new Node(parent, 0);
			node->left = parse(node);
			expect(',');
			node->right = parse(node);
			expect(']');

			return node;
		}

		if (isdigit(c))
		{
			return new Node(parent, c - '0');
		}

		fprintf(stderr,
			"Unexpected '%c' at %zu\n", c, i);
		syntax_err();
	}
};

int
main()
{
	std::string s;
	Node *node = nullptr;

	while (std::getline(std::cin, s))
	{
		Parser parser(s);
		Node *second_node = parser.parse();

		if (node != nullptr)
		{
			node = Node::add(node, second_node);
		}
		else
		{
			node = second_node;
		}
	}

	std::cout << node->magnitude() << std::endl;
}
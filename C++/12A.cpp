#include <bits/stdc++.h>

using adjacency_list = std::unordered_map<std::string, std::vector<std::string>>;
using vis_list = std::unordered_set<std::string>;

void
dfs(std::string node, adjacency_list &adj, vis_list &vis, int &paths)
{
	if (vis.count(node))
	{
		return;
	}

	if (node != "end" && node[0] >= 'a' && node[0] <= 'z')
	{
		vis.insert(node);
	}

	if (node == "end")
	{
		paths++;
		return;
	}

	for (auto &neighbour : adj[node])
	{
		dfs(neighbour, adj, vis, paths);
	}

	vis.erase(node);
}

int
main()
{
	std::string from;
	std::string to;
	adjacency_list adj;
	vis_list vis;

	while (std::getline(std::cin, from))
	{
		int index = from.find("-") + 1;

		to = from.substr(index);
		from = from.substr(0, index - 1);

		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	int c = 0;

	dfs("start", adj, vis, c);

	std::cout << c << std::endl;
}
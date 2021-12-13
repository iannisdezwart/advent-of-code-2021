#include <bits/stdc++.h>

using adjacency_list = std::unordered_map<std::string, std::vector<std::string>>;
using vis_list = std::unordered_map<std::string, int>;

void
dfs(std::string node, adjacency_list &adj, vis_list &vis, int max_vis, int &paths)
{
	if (vis[node] > 1)
	{
		return;
	}

	if (node == "start" && vis[node] == 1)
	{
		return;
	}

	if (node != "end" && node[0] >= 'a' && node[0] <= 'z')
	{
		if (vis[node] == 2)
		{
			return;
		}

		if (vis[node] == 1 && max_vis == 2)
		{
			return;
		}

		vis[node]++;
		max_vis = std::max(max_vis, vis[node]);
	}

	if (node == "end")
	{
		paths++;
		return;
	}

	for (auto &neighbour : adj[node])
	{
		dfs(neighbour, adj, vis, max_vis, paths);
	}

	if (vis[node]-- == 2)
	{
		max_vis = 1;
	}
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

	dfs("start", adj, vis, 0, c);

	std::cout << c << std::endl;
}
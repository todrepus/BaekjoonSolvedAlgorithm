// CppForStudy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>

struct Edge
{
	int start;
	int end;
	int dist;

	Edge() { start = end = dist = 0; }
	Edge(int _start, int _end, int _dist) { start = _start; end = _end; dist = _dist; }
};

std::vector<Edge> edges[101];
int distMap[101][101] = { {0}, };

int solve()
{
	int N = 0, M = 0;
	std::cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int start = 0, end = 0, dist = 0;
		std::cin >> start >> end >> dist;
		edges[start].emplace_back(start, end, dist);
	}


	for (int i = 1; i <= N; i++)
	{
		bool visited[101] = { 0, };
		visited[i] = true;

		std::queue<int> qCity;
		qCity.push(i);


		while (qCity.empty() == false)
		{
			int nStart = qCity.front();
			std::vector<int> vecAdd;
			for (const Edge& edge : edges[nStart])
			{
				if (visited[edge.end] == true)
				{
					int distNext = distMap[i][edge.end];
					int distNew = distMap[i][nStart] + edge.dist;
					if (distNext <= distNew)
						continue;
					distMap[i][edge.end] = distNew;
				}
				else
				{
					distMap[i][edge.end] = distMap[i][nStart] + edge.dist;
				}

				visited[edge.end] = true;
				vecAdd.push_back(edge.end);
			}

			qCity.pop();

			for (int add : vecAdd)
				qCity.push(add);
		}

		for (int j = 1; j < N; j++)
		{
			std::cout << distMap[i][j] << " ";
		}

		std::cout << distMap[i][N] << "\n";
	}
	return 0;
}

int main()
{
	solve();
	return 0;
}


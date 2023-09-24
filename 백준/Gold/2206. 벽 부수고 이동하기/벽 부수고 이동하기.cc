// CppForStudy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>

inline bool IsInRect(int x, int y, int w, int h)
{
	return (x >= 0 && x < w) && (y >= 0 && y < h);
}

inline int min(int x, int y) 
{ 
	return x < y ? x : y; 
}

struct Point
{
	int x;
	int y;
	Point(int _x, int _y) { x = _x; y = _y; }
};

class Robot
{
public:
	Point pos;
	int nSearchCnt;
	int nDestroyWall;

	Robot() : pos(0, 0)
	{
		nDestroyWall = 0;
		nSearchCnt = 1;
	}
};

enum Piece
{
	EMPTY = 0,
	WALL
};


int map[1000][1000] = { 0, };
int dist_map[1000][1000] = { 0, };
int pass_map[1000][1000] = { 0, };

int solve()
{
	const int int_max = (1 << 31) -1;
	int nRet = int_max;

	int N = 0, M = 0;
	std::cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		int j = 0;
		std::string s;
		std::cin >> s;
		for (char ch : s)
			map[i][j++] = ch - '0';
	}

	std::queue<Robot> qRobot;
	qRobot.emplace();

	while (qRobot.empty() == false)
	{
		Robot robot = qRobot.front();
		Point& pos = robot.pos;
		qRobot.pop();

		// 도착점에 도달했다면, 최단거리인지 파악후 저장한다.
		if (pos.x == (M - 1) && pos.y == (N - 1))
		{
			nRet = min(nRet, robot.nSearchCnt);
			continue;
		}

		int dist = dist_map[pos.y][pos.x];
		

		/*
		선별기준
		1) 벽을 뚫고 도착한 녀석이 있는경우
		-> 초기화되지 않은 경우 통과
		-> 벽을 안뚫었으면 무조건 통과
		-> 벽을 뚫었으면 최단거리일때만 통과
		2) 벽을 안뚫고 이미 도착한 경우
		-> 벽을 안뚫고 최단거리일때만 통과
		*/
		if (pass_map[pos.y][pos.x] == 0)
		{
			if (dist == 0)
			{

			}
			else if (robot.nDestroyWall == 1 && dist <= robot.nSearchCnt)
				continue;
		}
		else if (!(robot.nDestroyWall == 0 && dist > robot.nSearchCnt))
		{
			continue;
		}
		
		// 현재 탐색횟수로 거리를 초기화한다.
		dist_map[pos.y][pos.x] = robot.nSearchCnt;
		// 벽을 안뚫고 왔다면 표기한다.
		pass_map[pos.y][pos.x] = robot.nDestroyWall == 0 ? 1 : 0;

		int dxs[] = { 1, 0, -1, 0 };
		int dys[] = { 0, 1, 0, -1 };
		for (int i = 0; i < 4; i++)
		{
			// 새로운 좌표
			int dx = dxs[i], dy = dys[i];
			int newX = pos.x + dx, newY = pos.y + dy;
			// 경계를 넘는다면, 건너뛴다.
			if (IsInRect(newX, newY, M, N) == false)
			{
				continue;
			}

			// 다음 좌표가 벽인데, 이미 벽을 뚫었다면 건너뛴다.
			if (map[newY][newX] == WALL && robot.nDestroyWall == 1)
			{
				continue;
			}

			// 다음좌표에 새로운 기물을 생성하고, 탐색횟수를 늘린다.
			Robot newRobot = robot;
			newRobot.nSearchCnt += 1;
			newRobot.pos = Point(newX, newY);

			// 다음 좌표가 벽이라면, 벽을 뚫는다.
			if (map[newY][newX] == WALL)
			{
				newRobot.nDestroyWall = 1;
			}
			
			// 새로운 기물을 queue에 삽입한다.
			qRobot.push(newRobot);
		}
	}

	return nRet == int_max ? -1 : nRet;
}

int main()
{
	int nRet = solve();
	std::cout << nRet << "\n";
	return 0;
}


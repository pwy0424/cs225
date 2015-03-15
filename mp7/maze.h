#include <vector>
#include "png.h"

#ifndef _MAZE_H
#define _MAZE_H
using namespace std;
class SquareMaze
{
	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector <int> solveMaze();
		PNG* drawMaze() const;
		PNG* drawMazeWithSolution();
	private:
		int _width;
		int _height;
		vector<bool> downWall;
		vector<bool> rightWall;
		int exit;
};

#endif //maze.h

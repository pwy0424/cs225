#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include "dsets.h"

using namespace std;

SquareMaze::SquareMaze()
{
	_width = 0;
	_height = 0;
	downWall.clear();
	rightWall.clear();
	exit = -1;
}

void SquareMaze::makeMaze(int width, int height)
{
	_width = width;
	_height = height;
	int size = width * height;
	downWall.clear();
	rightWall.clear();
	downWall = vector<bool>(size,true);
	rightWall = vector<bool>(size,true);
	DisjointSets tempDsets;
	tempDsets.addelements(size);
	int n = 0;
	while(n < size-1)
	{
		for(int i = 0; i <size; i++)
		{
			if ((random()*10 % 100) / (float) 100.0 > 0.9) continue;

			bool randombool = (rand()%10 > 4);
			if ((randombool && (i % _width + 1) == _width) || (!randombool && (i / _width + 1) == _height)
		    || (randombool && (tempDsets.find(i) == tempDsets.find(i + 1))) 
		    || (!randombool && (tempDsets.find(i) == tempDsets.find(i + _width))))
			{
				continue;
			}

			if (randombool) 
			{
				tempDsets.setunion(i, i + 1);
				n++;
				rightWall[i] = false;
			} 
			else
			{
				tempDsets.setunion(i, i + _width);
				n++;
				downWall[i] = false;
			}	
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	int index = y * _width + x;
	if((x < 0)||(y < 0)||(x >= _width)||(y >= _height)) return false;
	if((dir == 0 && x == _width - 1) || (dir == 1 && y == _height - 1) || (dir == 2 && x == 0) || (dir == 3 && y == 0)) return false;
	if(dir == 0) return (!rightWall[index]);
	if(dir == 1) return (!downWall[index]);
	if(dir == 2) return (!rightWall[index-1]);
    if(dir == 3) return (!downWall[index - _width]);
	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
 {
	int index = y * _width + x;
	if(dir == 0) rightWall[index] = exists;
	if(dir == 1) downWall[index] = exists;
}

vector<int> SquareMaze::solveMaze()
{
	int size = _width * _height;
	vector<int> result;
	vector<int> length(size,-1);
	vector<int> path(size,-1);
	vector<int> parent(size,-1);
	queue<int> myQueue;
	myQueue.push(0);
	vector<int> output;
	while(!myQueue.empty())
	{
		int index = myQueue.front();
		int x = index % _width;
		int y = index / _width;
		
		if (canTravel(x, y, 0)) 
		{
			if (length[index + 1] < 0)
			{
				length[index + 1] = length[index] + 1;
				path[index + 1] = 0;
				parent[index + 1] = index;
				myQueue.push(index + 1);
			}
		}
		if (canTravel(x, y, 1)) 
		{
			if (length[index + _width] < 0) 
			{
				length[index + _width] = length[index] + 1;
				path[index + _width] = 1;
				parent[index + _width] = index;
				myQueue.push(index + _width);
			}
		}
		if (canTravel(x, y, 2))
		{
			if (length[index - 1] < 0) 
			{
				length[index - 1] = length[index] + 1;
				path[index - 1] = 2;
				parent[index - 1] = index;
				myQueue.push(index - 1);
			}
		}
		if (canTravel(x, y, 3)) 
		{
			if (length[index - _width] < 0) 
			{
				length[index - _width] = length[index] + 1;
				path[index - _width] = 3;
				parent[index - _width] = index;
				myQueue.push(index - _width);
			}
		}

		myQueue.pop();
	}
	
	int currdist = -1;
	for (int i = _width * (_height - 1); i < size; i++)
	{
		int tempdist = length[i];
		if (tempdist > currdist) 
		{
			currdist = tempdist;
			exit = i;
		}
	}

	int temp = exit;
	while (temp > 0) 
	{
		output.push_back(path[temp]);
		temp = parent[temp];
	}

	result.clear();
	
	while (!output.empty()) 
	{
		result.push_back(output.back());
		output.pop_back();
	}

	return result;
}

PNG *SquareMaze::drawMaze() const
{
	PNG * result = new PNG(_width * 10 + 1, _height * 10 + 1);
	int size = _width * _height;
	for(int x = 10; x < _width*10 + 1; x++)
	{
		(*result)(x,0)->red = 0;
		(*result)(x,0)->green = 0;
		(*result)(x,0)->blue = 0;
	}
	for(int y = 0; y < _height*10 +1; y++)
	{
		(*result)(0,y)->red = 0;
		(*result)(0,y)->green = 0;
		(*result)(0,y)->blue = 0;
	}
	for(int i = 0; i < size; i++)
	{
		int x = i % _width;
		int y = i / _width;
		if(rightWall[i])
		{
			for(int k = 0; k <= 10; k++)
			{
				(*result)((x+1)*10,y*10+k)->red = 0;
				(*result)((x+1)*10,y*10+k)->green = 0;
				(*result)((x+1)*10,y*10+k)->blue = 0;
			}
		} 
		if(downWall[i])
		{
			for(int k = 0; k <= 10; k++)
			{
				(*result)(x*10+k,(y+1)*10)->red = 0;
				(*result)(x*10+k,(y+1)*10)->green = 0;
				(*result)(x*10+k,(y+1)*10)->blue = 0;
			}
		} 
	}
	return result;
}

PNG *SquareMaze::drawMazeWithSolution()
{
	PNG * result = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5;
	int y = 5;
	for(int i = 0; i < solution.size(); i++)
	{
		if (solution[i] == 0)
		{
			for(int k = 0; k <= 10; k++) 
			{
				(*result)(x+k,y)->red = 255;
				(*result)(x+k,y)->green = 0;
				(*result)(x+k,y)->blue = 0;
			}
			x += 10;
		}
		if (solution[i] == 1)
		{
			for(int k = 0; k <= 10; k++)
			{
				(*result)(x,y+k)->red = 255;
				(*result)(x,y+k)->green = 0;
				(*result)(x,y+k)->blue = 0;
			}
			y += 10;
		}
		if (solution[i] == 2)
		{
			for(int k = 0; k <= 10; k++)
			{
				(*result)(x-k,y)->red = 255;
				(*result)(x-k,y)->green = 0;
				(*result)(x-k,y)->blue = 0;
			}
			x -= 10;
		}
		if (solution[i] == 3)
		{
			for(int k = 0; k <= 10; k++)
			{
				(*result)(x,y-k)->red = 255;
				(*result)(x,y-k)->green = 0;
				(*result)(x,y-k)->blue = 0;
			}
			y -= 10;
		}
	}
	int exitX = exit % _width;
	int exitY = exit / _width;
	for(int k = 1; k <= 9; k++)
	{
		(*result)(exitX*10+k, (exitY+1)*10)->red = 255;
		(*result)(exitX*10+k, (exitY+1)*10)->green = 255;
		(*result)(exitX*10+k, (exitY+1)*10)->blue = 255;
	}
	//if (result->width()>1000) result->writeToFile("shit.png");
	//else result->writeToFile("result.png");
	return result;
}


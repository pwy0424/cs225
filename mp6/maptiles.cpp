/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	int rows = theSource.getRows();
	int columns = theSource.getColumns();
	MosaicCanvas * result = new MosaicCanvas(rows, columns);
	vector< Point< 3 > > newPoints;
	map<Point<3>, TileImage> mymap;
	for (int i = 0; i < theTiles.size(); i++)
	{
		RGBAPixel temp = theTiles[i].getAverageColor();
		Point<3> thePoint;
		thePoint[0] = (double) temp.red;
		thePoint[1] = (double) temp.green;
		thePoint[2] = (double) temp.blue;
		newPoints.push_back(thePoint);
		mymap.insert( pair<Point<3>, TileImage>(thePoint, theTiles[i]) );
	}
	KDTree<3> myKDTree = KDTree<3>(newPoints);
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			RGBAPixel targetColor = theSource.getRegionColor(x, y);
			Point<3> targetPoint;
			targetPoint[0] = (double)targetColor.red;
			targetPoint[1] = (double)targetColor.green;
			targetPoint[2] = (double)targetColor.blue;
			Point<3> resultPoint = myKDTree.findNearestNeighbor(targetPoint);
			result->setTile(x, y, mymap.find(resultPoint)->second);			
		}
	}
	return result;
}

/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	if (first[curDim] == second[curDim]) return(first < second);
	else return (first[curDim] < second[curDim]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
	double curdist = 0;
	double potdist = 0;
	for (int i = 0; i < Dim; i++)
	{
		curdist += ((currentBest[i]-target[i])*(currentBest[i]-target[i]));
		potdist += ((potential[i]-target[i])*(potential[i]-target[i]));
	}
	if (potdist == curdist) return(potential < currentBest);
    else return (potdist < curdist);
}

template<int Dim>
void KDTree<Dim>::sort(vector< Point<Dim> > & Points, int curDim, int a, int b)
{
	for (int i = a; i <= b; i++)
	{
		for (int j = i+1; j <= b; j++)
		{
			if (smallerDimVal(Points[j], Points[i], curDim))
			{
				Point<Dim> temp = Points[i];
				Points[i] = Points[j];
				Points[j] = temp;
			}
		}
	}
}

template<int Dim>
void KDTree<Dim>::build(vector<Point<Dim> > & Points, int curDim, int a, int b)
{
	if (a >= b) return;
	else 
	{
		sort(Points, curDim, a, b);
		int mid = (a+b)/2;
		build(Points, (curDim+1)%Dim, a, mid-1);
		build(Points, (curDim+1)%Dim, mid+1, b);
	}	
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
	int size = newPoints.size();
	for (int i = 0; i < size; i++) points.push_back(newPoints[i]);
	build(points, 0, 0, size-1);
}


template<int Dim>
Point<Dim> KDTree<Dim>::find(const Point<Dim> & query, int cur, int curDim, int a, int b) const
{
	if(a == b) return points[a];
	else
	{
		Point<Dim> temp;
		double childdist = 0;
		double parentdist2 = ((points[cur])[curDim] - query[curDim])*((points[cur])[curDim] - query[curDim]);
		double parentdist = 0;
		if(smallerDimVal(query, points[cur], curDim))
		{
			if (cur-1 < a) return points[cur];
			else 
			{
				temp = find(query, (a+cur-1)/2, (curDim+1)%Dim, a, cur-1);
				
				for (int i = 0; i < Dim; i++)
				{
					childdist += ((temp[i]-query[i])*(temp[i]-query[i]));
					parentdist += (((points[cur])[i]-query[i])*((points[cur])[i]-query[i]));
				}
				if (parentdist2 <= childdist)
				{
					Point<Dim> temp2;
					if (cur+1 > b) temp2 = points[cur];
					else temp2 = find(query, (cur+1+b)/2, (curDim+1)%Dim, cur+1, b);
					if ((parentdist < childdist)||((parentdist == childdist)&&(points[cur] < temp))) temp = points[cur];
					if (shouldReplace(query, temp, temp2)) return temp2;
					else return temp;
				}
				else return temp;
			}
		}
		else
		{
			if (cur+1 > b) return points[cur];
			else 
			{
				temp = find(query, (cur+1+b)/2, (curDim+1)%Dim, cur+1, b);
				for (int i = 0; i < Dim; i++)
				{
					childdist += ((temp[i]-query[i])*(temp[i]-query[i]));
					parentdist += (((points[cur])[i]-query[i])*((points[cur])[i]-query[i]));
				}
				if (parentdist2 <= childdist)
				{
					Point<Dim> temp2;
					if (cur-1 < a) temp2 = points[cur];
					else temp2 = find(query, (a+cur-1)/2, (curDim+1)%Dim, a, cur-1);
					if ((parentdist < childdist)||((parentdist == childdist)&&(points[cur] < temp))) temp = points[cur];
					if (shouldReplace(query, temp, temp2)) return temp2;
					else return temp;
				}
				else return temp;

			}
		}
	}
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
	
	return find(query, (points.size()-1)/2, 0, 0, points.size()-1);
}

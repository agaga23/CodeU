#include<iostream>
#include<vector>
#include<algorithm>	
#include <assert.h>
using namespace std;
class VisitedMap{
	int rowSize = 0;
	vector<vector<bool> > visited; // To find one island I will start on unvisited land and go as far as possible to mark all neighbouring lands as visited.
	
	void dfs( int y, int x ){
		visited[y][x] = true;
		
		int changeY[] = {-1,0,1,0}, changeX[] = {0,1,0,-1};
		for ( int i = 0; i < 4; i ++ ){
			int newY = y + changeY[i], newX = x + changeX[i];
			
			if ( newY >= 0 && newY < visited.size() && newX >= 0 && newX < rowSize )
				if( !visited[newY][newX] ) dfs( newY, newX );
		}
	}
	void prepareVisited(){
		for ( int y = 0; y < array.size(); y ++ ) rowSize = max ( rowSize, (int)array[y].size() );
		
		visited.resize ( array.size(), vector<bool>(rowSize, false) );
		for ( int y = 0; y < array.size(); y ++ ){
			for ( int x = 0; x < array[y].size(); x ++ ){
				visited[y][x] = !array[y][x]; //water can be marked as visited cell - I don't want to stand on it looking for land.
			}
		}
	}
public:
	vector<vector<bool> > array;
	
	int countIslands(){
		prepareVisited();
		int nrIslands = 0;

		for ( int y = 0; y < visited.size(); y ++ ){
			for ( int x = 0; x < rowSize; x ++ ){
				if ( !visited[y][x] ){
					nrIslands ++;
					dfs( y, x );
				}
			}
		}
		return nrIslands;
	}	
	VisitedMap( const vector<vector<bool> >& grid ){
		array = grid;
	}
};
int countIslands( const vector<vector<bool> >& array ){
	
	VisitedMap map( array );
	return map.countIslands();
}		

int countIslandsFromString ( const vector<string> &array, int expectedValue ){
	vector<vector<bool> > v;
	v.resize ( array.size() );
	int rowSize = 0;
	if ( array.size()) rowSize = array[0].size();
	
	for ( int y = 0; y < array.size(); y ++ ){
		string row = array[y];
		assert(row.size() == rowSize);
		
		for ( int x = 0; x < rowSize; x ++ ){
			bool cell = (row[x] == 't');
			v[y].push_back(cell);
		}
	}
	int islands = countIslands(v);

	if ( islands != expectedValue ) {
		for ( int y = 0; y < array.size(); y ++ ){
			string row = array[y];
			for ( int x = 0; x < row.size(); x ++ ) cout << row[x] << " ";
			cout << "\n";
		}
		cerr << "Your value is " << islands << " and expected value is " << expectedValue << "\n";
	}
	return islands;
}
int main(){
	vector<string> s = { "ftft", "ttff", "fftf", "fftf" };
	cout << countIslandsFromString( s, 3 ) << "\n";

	vector<string > s2 = { "ftf", "ftt", "tff", "fft", "ftt", "tft" };
	cout << countIslandsFromString( s2, 4 ) << "\n";
}

#include<iostream>
#include<vector>
using namespace std;
class visitedMap{
	vector<vector<bool> > visited; // To find one island I will start on unvisited land and go as far as possible to mark all neighbouring lands as visited.
	
	void dfs( int x, int y ){
		visited[x][y] = true;
		
		int change[] = {-1,0,1,0,-1}; //together changeX: [0-3] and changeY: [1-4]
		for ( int i = 0; i < 4; i ++ ){
			int newX = x + change[i], newY = y + change[i + 1];
			if( newX < 0 or newY < 0 or newX == visited.size() or newY == visited[0].size() ) continue;
			if( !visited[newX][newY] ) dfs( newX, newY );
		}
	}
public:
	int countIslands(){
		int nrIslands = 0;

		for ( int i = 0; i < visited.size(); i ++ ){
			for ( int j = 0; j < visited[i].size(); j ++ ){
				if ( !visited[i][j] ){
					nrIslands ++;
					dfs( i, j );
				}
			}
		}
		return nrIslands;
	}	
	visitedMap( const vector<vector<bool> >& array ){
		visited.resize ( array.size(), vector<bool>(array[0].size(), false) );
		for ( int i = 0; i < array.size(); i ++ ){
			for ( int j = 0; j < array[i].size(); j ++ ){
				if ( !array[i][j] ) visited[i][j] = true; //water can be marked as visited cell - I don't want to stand on it looking for land.
			}
		}
	}
};
int countIslands( const vector<vector<bool> >& array ){
	
	visitedMap map( array );
	return map.countIslands();
}
int main(){
	bool f = false, t = true;
	vector<vector<bool> > array = { { f, t, f, t }, { t, t, f, f }, { f, f, t, f }, { f, f, t, f } };
	cout << "f.f.\n..ff\nff.f\nff.f\nf-water .-land\n";
	cout << countIslands( array ) << "\n";

	vector<vector<bool> > array2 = { { f, t, f }, { f, t, t }, { t, f, f }, { f, f, t }, { f, t, t }, { t, f, t } };
	cout << "f.f\nf..\n.ff\nff.\nf..\n.f.\nf-water .-land\n";
	cout << countIslands( array2 ) << "\n";
}
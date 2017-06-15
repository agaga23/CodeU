#include "dictionary.h"
#include<iostream>
#include<unordered_set>
using namespace std;

class Board{
public:
	const int rows, columns;	
	const vector<vector<char> > array;
	
	Dictionary *dict;
	
	set<string> allWords;
	unordered_set< int > visitedCells;
	
	Board(int r, int c, vector<vector<char> >* ar, Dictionary* d)
	: rows{ r }, columns { c }, array { *ar }, dict { d }
	{}
};
void prefixWords (Board* boardGame, int x, int y, string prefix ){
	if ( x < 0 || y < 0 || x == boardGame->rows || y == boardGame->columns ) return; //x means 1st dimension, y - 2nd

	int nrCell = x * (boardGame->rows) + y;
	prefix += boardGame -> array[x][y];
	
	if ( boardGame -> visitedCells.find(nrCell) != boardGame -> visitedCells.end() ) return;
	if ( !(boardGame -> dict -> isPrefix(prefix)) ) return;

	boardGame->visitedCells.insert(nrCell);
	
	if ( boardGame -> dict -> isWord(prefix) ) boardGame -> allWords.insert(prefix);

	int changeX[] = {-1,0,1,1,1,0,-1,-1}, changeY[] = {1,1,1,0,-1,-1,-1,0}; //functions to change coordinates into one of 8 directions
	
	for ( int i = 0; i < 8; i ++ ){
		int newX = x + changeX[i], newY = y + changeY[i];
		
		prefixWords ( boardGame, newX, newY, prefix);
	}
	boardGame -> visitedCells.erase(nrCell);
}
set<string> findAllWords (const int rows, const int columns, vector<vector<char> >* array, Dictionary* dict){

	Board boardGame(rows,columns,array,dict);
	
	for ( int startX = 0; startX < rows; startX ++ ){
		for ( int startY = 0; startY < columns; startY ++ ){ //start from the cell array[startX][startY] and find all posibble words beginning there 
			//and add them to allWords
 			prefixWords( &boardGame, startX, startY, "");
		}
	}
	return boardGame.allWords;
}
int main(){
	Dictionary dict({"cat","card","cart", "car"});
	
	vector<vector<char> > array = {{'a','a','r'},{'t','c','d'}};
		
	set<string> allWords = findAllWords(2, 3, &array, &dict);
	
	for ( auto &word: allWords ) cout << word << " ";
	cout << "\n";
	
	Dictionary plDict({"rak","kora","kret","krety","kareta","karetka","teka","teczka","mapa","krem","korek","prom","tapeta","tora","tak","krew","marker"});
	vector<vector<char> > array2 = {{'m','r','e'},{'a','k','o'},{'r','e','t'},{'m','p','a'}};

	set<string> polishWords = findAllWords(4, 3, &array2, &plDict);
	
	for ( auto &word: polishWords ) cout << word << " ";
	cout << "\n";
	
	return 0;
}
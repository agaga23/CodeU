#include "dictionary.h"
#include<iostream>
#include<unordered_set>
using namespace std;
class Board{
	const vector<vector<char> > array;
	Dictionary *dict;
	set<string> allWords;
	bool* visitedCells;
	
	void prefixWords (int row, int column, string prefix ){
		if ( row < 0 || column < 0 || row == array.size() || column == array[0].size() ) return;

		int cell = row * array.size() + column;
		prefix += array[row][column];
	
		if ( visitedCells[cell] == true ) return;
		if ( !dict -> isPrefix(prefix) ) return;

		visitedCells[cell] = true;
		if ( dict -> isWord(prefix) ) allWords.insert(prefix);

		int changeX[] = {-1,0,1,1,1,0,-1,-1}, changeY[] = {1,1,1,0,-1,-1,-1,0}; //functions to change coordinates into one of 8 directions
		for ( int i = 0; i < 8; i ++ )
			prefixWords ( row + changeX[i], column + changeY[i], prefix);
	
		visitedCells[cell] = false;
	}
public:
	set<string> findAllWords (){
		
		for ( int startX = 0; startX < array.size(); startX ++ ){
			for ( int startY = 0; startY < array[0].size(); startY ++ ){ //start from the cell array[startX][startY] and find all posibble words beginning there 
				prefixWords( startX, startY, "");				 //and add them to allWords
			}
		}
		return allWords;
	}
	Board(vector<vector<char> >* ar, Dictionary* d)
	: array { *ar }, dict { d }, visitedCells { new bool[(*ar).size()] }
	{}
};
int main(){
	Dictionary dict({"cat","card","cart", "car"});	
	vector<vector<char> > array = {{'a','a','r'},{'t','c','d'}};
	
	Board boardGame(&array, &dict);	
	for ( auto &word: boardGame.findAllWords() ) cout << word << " ";
	cout << "\n";
	
	Dictionary plDict({"rak","kora","kret","krety","kareta","karetka","teka","teczka","mapa","krem","korek","prom","tapeta","tora","tak","krew","marker"});
	vector<vector<char> > array2 = {{'m','r','e'},{'a','k','o'},{'r','e','t'},{'m','p','a'}};

	Board boardGame2(&array2, &plDict);	
	for ( auto &word: boardGame2.findAllWords() ) cout << word << " ";
	cout << "\n";
	
	return 0;
}

#include "dictionary.h"
#include<iostream>
using namespace std;
void prefixWords (const int rows, const int columns, const char* array, Dictionary* dict, 
						   int x, int y, string prefix, set<string>* allWords, set<pair<int,int> > visitedCells = set<pair<int,int> >() ){
	//the last parameter is the set of visited cells during creating given prefix (cells where we can't go again)
	
	if ( x < 0 || y < 0 || x == rows || y == columns ) return; //x means 1st dimension, y - 2nd
	
	if ( visitedCells.find({x,y}) != visitedCells.end() ) return;
	visitedCells.insert({x,y});
	
	prefix += *(array + x * columns + y);
	
	if ( dict -> isPrefix(prefix) == false ) return;
	if ( dict -> isWord(prefix) == true ) allWords -> insert(prefix);

	int changeX[] = {-1,0,1,1,1,0,-1,-1}, changeY[] = {1,1,1,0,-1,-1,-1,0}; //functions to change coordinates into one of 8 directions
	
	for ( int i = 0; i < 8; i ++ ){
		int newX = x + changeX[i], newY = y + changeY[i];
		
		prefixWords (rows, columns, array, dict, newX, newY, prefix, allWords, visitedCells);
	}
}
set<string> findAllWords (const int rows, const int columns, const char* array, Dictionary* dict){

	set<string> allWords;
	for ( int startX = 0; startX < rows; startX ++ ){
		for ( int startY = 0; startY < columns; startY ++ ){ //start from the cell array[startX][startY] and find all posibble words beginning there 
			//and add them to allWords
 			prefixWords(rows, columns, array, dict, startX, startY, "", &allWords);
		}
	}
	return allWords;
}
int main(){
	Dictionary dict({"cat","card","cart", "car"});
	
	char array[2][3] = {{'a','a','r'},{'t','c','d'}};
	
	set<string> allWords = findAllWords(2, 3, (char*)array, &dict);
	
	for ( auto &word: allWords ) cout << word << " ";
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
class Alphabet{
	map < char, int > allLetters;
	vector < char > numberedLetters;
	
	vector < vector < int > > orderGraph;
	vector < int > connectedWith;
	
	int firstDifferentPosition ( string& a, string &b ){
		int minLength = min ( a.length(), b.length() );
		
		for ( int i = 0; i < minLength; i ++ )
			if ( a[i] != b[i] ) return i;
		
		return minLength;
	}
	int findAllLetters ( vector<string>& dictionary ){
		int counter = 0;
		for ( int i = 0; i < dictionary.size(); i ++ ){
	
			string word = dictionary[i];
			for ( int j = 0; j < word.length(); j ++ ) {
				char letter = word[j];
				if ( allLetters.find ( letter ) == allLetters.end() ){
					allLetters[letter] = ++ counter;
					numberedLetters.push_back ( letter );
				}
			}
		}
		return counter;
	}
	vector < char > topSorting (){
		vector < char > sortedLetters;

		queue < char > lettersToTake;
		for ( pair < char, int > letter : allLetters ){
			char cLetter = letter.first; //as charLetter
			int nLetter = letter.second; //as numberOfLetter
			if ( connectedWith[nLetter] == 0 ) 
				lettersToTake.push ( cLetter );
		}
		while ( lettersToTake.size() ){
			char cLetter = lettersToTake.front(); //as charLetter
			int nLetter = allLetters[cLetter]; //as numberOfLetter
			
			lettersToTake.pop();
			sortedLetters.push_back ( cLetter );
			
			for ( int i = 0; i < orderGraph[nLetter].size(); i ++ ){
				int nextLetter = orderGraph[nLetter][i];
				
				connectedWith[nextLetter] --;
				if ( connectedWith[nextLetter] == 0 )
					lettersToTake.push ( numberedLetters[nextLetter - 1] );
			}
		}
		return sortedLetters;
	}
public:
	vector<char> findTheAlphabet ( vector<string>& dictionary ){
		
		int sizeOfAlphabet = findAllLetters ( dictionary );
		
		orderGraph.resize ( sizeOfAlphabet + 1 );
		connectedWith.resize ( sizeOfAlphabet + 1, 0 );
		
		for ( int i = 0; i < dictionary.size(); i ++ ){
			for ( int j = i + 1; j < dictionary.size(); j ++ ){
				int differentPos = firstDifferentPosition ( dictionary[i], dictionary[j] );
				
				if ( differentPos < dictionary[i].size() && differentPos < dictionary[j].size() ){
					
					char letter1 = dictionary[i][differentPos], letter2 = dictionary[j][differentPos];
					
					int nrOfLetter1 = allLetters[letter1], nrOfLetter2 = allLetters[letter2];
					cerr << letter1 << " < " << letter2 << "\n";
					orderGraph[nrOfLetter1].push_back ( nrOfLetter2 );
					
					connectedWith [ nrOfLetter2 ] ++;
				}
			}
		}
		return topSorting();
	}
};
void printAlphabet ( vector<char> alphabet ){
	cout << "[ ";
	for ( int i = 0; i < alphabet.size(); i ++ ) {
		cout << alphabet[i];
		if ( i + 1 < alphabet.size() ) cout << ", ";
	}
	cout << "]\n";
}
vector<char> findTheAlphabet ( vector<string>& dictionary ){
	Alphabet alpha;
	return alpha.findTheAlphabet ( dictionary );
}
int main (){
	vector < string > dict = { "art", "rat", "cat", "car" };
	printAlphabet ( findTheAlphabet ( dict ) );
	dict = { "a", "abc", "abd", "bb", "bd" };
	printAlphabet ( findTheAlphabet ( dict ) );
	dict = { "z", "yx", "yz", "a" };
	printAlphabet ( findTheAlphabet ( dict ) );
	return 0;
}
#include<bits/stdc++.h>
using namespace std;

class Alphabet{
	
	set < char > allLetters;
	
	vector < vector < char > > orderGraph;
	vector < int > connectedWith;
	
	int firstDifferentPosition ( const string& a, const string &b ){
		
		const int minLength = min ( a.length(), b.length() );
		
		for ( int i = 0; i < minLength; i ++ )
			if ( a[i] != b[i] ) return i;
		
		return -1;
	}
	int findAllLetters ( const vector<string>& dictionary ){
		
		for (const string &word : dictionary)
			for (const char letter : word)
				allLetters.insert(letter);

		return allLetters.size();
	}
	vector < char > topSorting (){
		
		vector < char > sortedLetters;
		queue < char > lettersToTake;
		
		for ( const char letter : allLetters ){
			
			if ( connectedWith[letter] == 0 ) //find letters which don't have any connections back - they could be the first letter in the alphabet
				lettersToTake.push ( letter ); 
		}
		while ( lettersToTake.size() ){
			
			const char letter = lettersToTake.front(); //if you take the letter it means that all letters which should be before this one are processed
			lettersToTake.pop();
			
			sortedLetters.push_back ( letter );
			
			for ( const char nextLetter: orderGraph[letter] ){
				
				connectedWith[nextLetter] --; //as you process the next connection, check if all letters which should be before this one are processed (or in queue)
				if ( connectedWith[nextLetter] == 0 )
					lettersToTake.push ( nextLetter ); //if so, you can process this letter
			}
		}
		return sortedLetters;
	}
public:
	vector<char> findTheAlphabet ( const vector<string>& dictionary ){
		
		findAllLetters ( dictionary );
		
		orderGraph.resize ( 200 );
		connectedWith.resize ( 200, 0 );
		
		for ( int i = 0; i < dictionary.size() - 1; i ++ ){
			
			const int differentPos = firstDifferentPosition ( dictionary[i], dictionary[i + 1] );
			if ( differentPos != -1 ){
				
				const char letter1 = dictionary[i][differentPos], letter2 = dictionary[i + 1][differentPos];
				
				orderGraph[letter1].push_back ( letter2 ); //connection: letter1 should be in the alphabet before letter2
				
				connectedWith [ letter2 ] ++; //letter2 has one more letters which should be before it in the alphabet
			}
		}
		return topSorting();
	}
};

void printAlphabet ( const vector<char> alphabet ){
	
	cout << "[ ";
	
	for ( int i = 0; i < alphabet.size(); i ++ ) {
		cout << alphabet[i];
		if ( i + 1 < alphabet.size() ) cout << ", ";
	}
	
	cout << "]\n";
}

vector<char> findTheAlphabet ( const vector<string>& dictionary ){
	
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
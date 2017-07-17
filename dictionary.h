#include<string>
#include<set>
#include<vector>
using namespace std;
class Dictionary{
	set<string> allWords,allPrefixes;
	
public:
	bool isWord(string s){
		return allWords.find(s) != allWords.end();
	}
	bool isPrefix(string s){
		return allPrefixes.find(s) != allPrefixes.end();
	}
	Dictionary(vector<string> words){ //vector of words which should be in dict
		for ( string word: words ){
			
			string prefix = "";
			for ( char c: word ) {
				prefix += c;
				allPrefixes.insert(prefix);
			}
			allWords.insert( word );
		}
	}
};
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
		for ( int i = 0; i < words.size(); i ++ ){

			string prefix = "";
			for ( int j = 0; j < words[i].length(); j ++ ){
				prefix += words[i][j];
				allPrefixes.insert(prefix);
			}
			allWords.insert(words[i]);
		}
	}
};
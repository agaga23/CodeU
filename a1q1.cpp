#include<iostream>
#include<algorithm>
using namespace std;
bool diff_strings (string a, string b){
  if ( a.size() != b.size() ) return false;
  
  transform (a.begin(), a.end(), a.begin(), ::tolower);
  transform (b.begin(), b.end(), b.begin(), ::tolower);
  
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

 return a == b;
}
int main(){
	
  string a, b;
  cin >> a >> b;
  cout << diff_strings (a, b) << "\n";
}

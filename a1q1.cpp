#include<iostream>
#include<algorithm>
using namespace std;
bool diff_strings (string a, string b){
  if ( a.size() != b.size() ) return 0;
  
  transform (a.begin(), a.end(), a.begin(), ::tolower);
  transform (b.begin(), b.end(), b.begin(), ::tolower);
  
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  
  for ( int i = 0; i < a.size(); i ++ )
	if ( a[i] != b[i] ) return 0;
	
  return 1;
}
int main(){
	
  string a, b;
  cin >> a >> b;
  cout << diff_strings (a, b) << "\n";
}
#include<iostream>
#include <cstdlib>
using namespace std;
bool randtable[] = {1,0,0,0,1,0,1,1,0,1};
struct Node{
	int value = 0;
	Node* Left = nullptr;
	Node* Right = nullptr;
	Node(int v){
		value = v;
		cout << v << "\n";
	}
	void addNode(Node* A){
		
		int v = A-> value;
		
		Node* x = this;
		int index = v % 10;
		bool r = randtable[(index++)%10];
		while ( true ){
			cout << x -> value <<" ";
			if ( r == true ) {
				if ( x -> Left == nullptr ) break;
				x = x -> Left;
			}
			else{
				if ( x -> Right == nullptr ) break;
				x = x -> Right;
			}
			r = randtable[(index++)%10];
		}
		if ( r == true ) x -> Left = A;
		else x -> Right = A;
	}
	bool printAncestors(int v){
		if ( value == v ) return 1;
		
		if ( (Left != nullptr && Left->printAncestors(v) == true) or (Right != nullptr && Right->printAncestors(v) == true) ){
			cout << value << " ";
			return true;
		}
		return false;
	}
};
int main(){
	Node* x[11];
	for ( int i = 0; i <= 10; i ++ ){
		int v = (i * i + (i + 2 ) * 4) + 1;
		x[i] = new Node ( v );
	}
	cout << "\nStructure of tree: \n";
	Node t = *x[0];
	cout << x[0] -> value << "\n";
	for ( int i = 1; i <= 10; i ++ ){
		t.addNode(x[i]);
		cout << x[i]->value << "\n";
	}
	cout << "-------------------\n";
	
	for ( int i = 1; i <= 10; i += 3 ){		
		cout << "printAncestors of " << x[i]->value <<": ";
		t.printAncestors(x[i]->value);
		cout << "\n";
	}
	cout << "printAncestors of " << 1234 <<": ";
	t.printAncestors(1234);
	cout << "\n";
}
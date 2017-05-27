#include<iostream>
#include <cstdlib>
using namespace std;
bool randtable[] = {1,0,0,0,1,0,1,1,0,1};
struct Node{
	int value = 0, in, out; //in-time and out-time
	Node* Left = nullptr;
	Node* Right = nullptr;
	Node(int v){
		value = v;
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
	int dfs(int time){
		in = time ++;
		if ( Left != nullptr ) time = Left -> dfs(time);
		if ( Right != nullptr ) time = Right -> dfs(time);
		out = time ++;
		return time;
	}
	Node* lca ( Node* a, Node* b ){
		if ( a-> in > b-> in ) swap ( a, b );
		if ( b-> in <= a-> out ) return a; //a-> in -> b -> a-> out
		
		int mini_in  = min ( a -> in, b -> in );
		int maxi_out = max ( a -> out, b -> out );
		
		Node *x = this;
		while ( true ){
			if ( x->Left != nullptr && x->Left -> in <= mini_in && x->Left -> out >= maxi_out ) x = x->Left;
			else {
				if ( x->Right != nullptr && x->Right -> in <= mini_in && x->Right -> out >= maxi_out ) x = x->Right;
				else return x;
			}
		}
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
	t.dfs(1);
//  pair<int,int> testtable[] = { {69, 9}, {54,41}, {105,105}, {54,149} {30,69} };
	pair<int,int> testtable[] = { {6,0}, {5,4}, {8,8}, {10,5},{3,6} };
	for ( int i = 0; i < 5; i ++ ){
		Node* a = x[testtable[i].first];
		Node* b = x[testtable[i].second];
		cout << "lca of " << a->value << " " << b->value << " = " << t.lca(a,b)->value << "\n";
	}
}
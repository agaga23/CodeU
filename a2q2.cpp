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
	Node* lca ( Node* node1, Node* node2 ){
		int mini_in  = min ( node1 -> in, node2 -> in );
		int maxi_out = max ( node1 -> out, node2 -> out );
		
		Node *x = this;
		//Start from the root (x), go down (left/right every time) as long as both nodes are in the subtree of x.
		//The node a is in a subtree of another (name it c) if c.in <= a.in, a.out <= c.out
		
		while ( true ){
			if ( x->Left != nullptr && x->Left -> out >= maxi_out ) x = x->Left;
			else {
				if ( x->Right != nullptr && x->Right -> in <= mini_in ) x = x->Right;
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
	Node* t = x[0];
	cout << t -> value << "\n";
	for ( int i = 1; i <= 10; i ++ ){
		t->addNode(x[i]);
		cout << x[i]->value << "\n";
	}
	cout << "-------------------\n";
	t->dfs(1);
//  pair<int,int> testtable[] = { {69, 9}, {54,41}, {105,105}, {54,149} {30,69} };
	pair<int,int> testtable[] = { {6,0}, {5,4}, {8,8}, {10,5},{3,6} };
	for ( int i = 0; i < 5; i ++ ){
		Node* a = x[testtable[i].first];
		Node* b = x[testtable[i].second];
		cout << "lca of " << a->value << " " << b->value << " = " << t->lca(a,b)->value << "\n";
	}
}
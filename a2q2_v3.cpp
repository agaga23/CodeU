#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
struct Node{
	int value;
	Node* Left = nullptr;
	Node* Right = nullptr;
	Node* Up = nullptr;
	bool tmp = false;
	
	Node (int v, Node* up){
		value = v;
		Up = up;
	}
	Node(int v){
		value = v;
	}
	void addNode(int val, int pos){
		int initial_pos = pos;
		int pos_level = 1;
		while ( pos_level * 2 <= pos ) pos_level *= 2;
		
		// Go through the tree from root to target place. Check if you should go left / right by checking on which half of the floor in tree is that position. Then go down in the tree and count the positions in the subtree from the beginning.
		Node *x = this;		
		while ( pos > 3 ){
			int half = pos_level / 2;
			if ( pos < pos_level + half ) { //left half
				if ( x -> Left == nullptr ) break;
				x = x -> Left;
				pos -= half;
			}
			else{
				if ( x -> Right == nullptr ) break;
				x = x -> Right;
				pos -= pos_level;
			}
			pos_level /= 2;
		}
		if ( pos > 3 ) cerr << "you can't add node with value "<< val << " (at position " << initial_pos << ") to the tree - it doesn't have all his ancestors\n";
		else {
			if ( pos == 2 ) x -> Left = new Node(val, x);
			else x -> Right = new Node(val, x);
		}
	}
	Node* findNode(int nodeVal){ 
		if ( value == nodeVal ) return this;

		if ( Left != nullptr ){
			Node* anc = Left -> findNode(nodeVal);
			if ( anc != nullptr ) return move(anc);
		}
		if ( Right != nullptr ){
			Node* anc = Right -> findNode(nodeVal);
			if ( anc != nullptr ) return move(anc);
		}
		return nullptr;
	}
	int lowestCommonAncestor (int val1, int val2){
		
		//find pointers to both nodes in tree
		Node* node1 = findNode(val1);
		Node* node2 = findNode(val2);

		//mark all ancestors of node1
		Node *goUp = node1;
		while ( goUp != nullptr ){
			goUp -> tmp = true;
			goUp = goUp -> Up;
		}  
		
		//and go up with node2 finding the first marked node (first ancestor of both nodes)
		int ans = -1;
		goUp = node2;
		while ( goUp != nullptr ){
			if ( goUp -> tmp == true ) {
				ans = goUp -> value;
				break;
			}
			goUp = goUp -> Up;
		}
		
		//unmark everything to be prepared for next querries
		goUp = node1;
		while ( goUp != nullptr ){
			goUp -> tmp = false;
			goUp = goUp -> Up;
		}
		
		if ( ans == -1 ) {
			if ( node1 == nullptr ) cerr << "The node with value " << val1 << " doesn't exist in tree\n";
			if ( node2 == nullptr ) cerr << "The node with value " << val2 << " doesn't exist in tree\n";
			return -1;
		}
		return ans;
	}
};
int main(){
	cout << "\nStructure of tree: \n";
	Node t(9);
	cout << "9\n";
	int enter_pos = 4;
	for ( int i = 1; i <= 11; i ++ ){
		int v = (i * i + ( i + 2 ) * 4) + 1;
		t.addNode(v, i + 1);
		if ( i + 1 == enter_pos ) { cout << "\n"; enter_pos *= 2; }
		cout << v << " ";
	}
	cout << "\n-------------------\n";

	pair<int,int> testtable[] = { {69, 9}, {54,41}, {105,105}, {54,149}, {86,41} };
	for ( int i = 0; i < 5; i ++ )
		cout << "lca of " << testtable[i].first << "," << testtable[i].second << " is " << t.lowestCommonAncestor(testtable[i].first, testtable[i].second) << "\n";
	
}

#include<iostream>
#include <cstdlib>
using namespace std;
struct Node{
	int value;
	Node* Left = nullptr;
	Node* Right = nullptr;
	Node(int v){
		value = v;
	}
	void addNode(int val, int pos){
		int initial_pos = pos;
		//pos - position in binary tree where we want to add node counting down from root (from left to right) (level-traversal)
		//counting starts from 1, then its left node = 2, right node = 3 etc.
		int pos_level = 1;
		while ( pos_level * 2 <= pos ) pos_level *= 2; 
		//pos_level - the level in tree, where our pos is, e.g positions 8,9,10,11,..,15 are on the pos_level = 8
		
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
			pos_level /= 2; //every time after going down we look at the subtree of the changed x node and in this subtree our pos changed as well as pos_level
		}
		//if our pos is 2/3 we will add new node to our son
		//if not => pos > 3 we need to go further, but finishing while above means - we can't, so error
		if ( pos > 3 ) cerr << "you can't add node with value "<< val << " (at position " << initial_pos << ") to the tree - it doesn't have all his ancestors\n";
		else {
			if ( pos == 2 ) x -> Left = new Node(val);
			else x -> Right = new Node(val);
		}
	}
	bool printAncestors(int nodeVal){ 
		if ( value == nodeVal ) return true;

		if ( (Left != nullptr && Left->printAncestors(nodeVal) ) || (Right != nullptr && Right->printAncestors(nodeVal) ) ){
			cout << value << " ";
			return true;
		}
		return false;
	}
};
int main(){
	cout << "\nStructure of tree: \n";
	Node t(9);
	cout << "9\n";
	int enter_pos = 4;
	for ( int i = 1; i <= 10; i ++ ){
		int v = (i * i + ( i + 2 ) * 4) + 1;
		t.addNode(v, i + 1);
		if ( i + 1 == enter_pos ) { cout << "\n"; enter_pos *= 2; }
		cout << v << " ";
	}
	t.addNode(1, 30);
	cout << "\n-------------------\n";
	
	for ( int i = 1; i <= 10; i += 3 ){		
		int v = (i * i + ( i + 2 ) * 4) + 1;
		cout << "printAncestors of " << v <<": ";
		t.printAncestors(v);
		cout << "\n";
}
	cout << "printAncestors of " << 1234 <<": ";
	t.printAncestors(1234);
	cout << "\n";
}

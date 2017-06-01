#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
struct Node{
	int value;
	Node* Left = nullptr;
	Node* Right = nullptr;
	Node(int v){
		value = v;
	}
	void addNode(int val, int pos){
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
		if ( pos > 3 ) cout << "you can't add node to the tree on that position - it doesn't have all his ancestors\n";
		else {
			if ( pos == 2 ) x -> Left = new Node(val);
			else x -> Right = new Node(val);
		}
	}
	vector<int> ancestors(int nodeVal){ //the function similar to printAncestors from task1, but instead of printing, storage ancestors in vector
		vector<int> anc;
		if ( value == nodeVal ) {
			anc.push_back(value);
			return move(anc);
		}
		if ( Left != nullptr ){
			anc = Left -> ancestors(nodeVal);
			if ( anc.size() ) {
				anc.push_back(value);
				return move(anc);
			}
		}
		if ( Right != nullptr ){
			anc = Right-> ancestors(nodeVal);
			if ( anc.size() ) {
				anc.push_back(value);
				return move(anc);
			}
		}
		return move(anc);
	}
	int lca (int val1, int val2){
		//find ancestors of both nodes and choose the last common from the list
		
		vector<int> anc1 = ancestors(val1);
		vector<int> anc2 = ancestors(val2);
		reverse ( anc1.begin(), anc1.end() );
		reverse ( anc2.begin(), anc2.end() );
		
		int min_size = min ( anc1.size(), anc2.size() );
		
		if ( min_size == 0 ) return 0; // val1 or/and val2 doesn't exist in tree
		
		for ( int i = 1; i < min_size; i ++ ){
			if ( anc1[i] != anc2[i] ) return anc1[i - 1]; //on this position they differ, so the last common is the previous one
		}
		return anc1[min_size - 1]; //when ancestors of one have finished, this one node is lca
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

	pair<int,int> testtable[] = { {69, 9}, {54,41}, {105,105}, {54,149}, {30,69} };
	//  pair<int,int> testtable[] = { {6,0}, {5,4}, {8,8}, {10,5},{3,6} };
	for ( int i = 0; i < 5; i ++ )
		cout << "lca of " << testtable[i].first << "," << testtable[i].second << " is " << t.lca(testtable[i].first, testtable[i].second) << "\n";
	
}

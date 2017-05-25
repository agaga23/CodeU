#include<iostream>
using namespace std;
struct Node{
  int value;
  Node *next = nullptr;

  Node(int v) :value{v}{
  }
};
struct LList{
  Node *head = nullptr, *last = nullptr;
  int size = 0;
  void add(int v){
	size ++;
	if ( head == nullptr ) {
	  head = new Node(v);
	  last = head;
	  return;
	}
	last -> next = new Node(v);
	last = last -> next;
  }
  Node* findk(int k){
	if ( k < 0 || k >= size ) return nullptr;
	Node *kth = head;
	for ( int nr = 1; nr < (size - k); nr ++ ) kth = kth -> next;
	return kth;
  }
};
int main(){
  LList x;
  x.add(5);
  x.add(1);
  x.add(29);
  x.add(8);
  
  for ( int i = -1; i < 5; i ++ ){
	  Node *kth = x.findk(i);
	  if ( kth != NULL ) cout << (*kth).value << "\n";
	  else cout << "You gave wrong input.\n"; 
	}
}

#include<iostream>
using namespace std;
struct Node{
  int value;
  Node *next = NULL;

  Node(int v) :value{v}{
  }
};
struct LList{
  Node *head = NULL;
  void add(int v){
	if ( head == NULL ) {
	  head = new Node(v);
	  return;
	}
	Node *end = head;
	while ( end -> next != NULL ) end = end -> next;
	end -> next = new Node(v);
  }
  Node findk(int k){
	int siz = 0;
	Node *end = head;
	while ( end != NULL ){
	  siz ++;
	  end = end -> next;
	}
	int nr = 1;
	Node *kth = head;
	while ( nr != ( siz - k ) ){
	  kth = kth -> next;
	  nr ++;
	}
	return *kth;
  }
};
int main(){
  LList x;
  x.add(5);
  x.add(1);
  x.add(29);
  x.add(8);
  cout << x.findk(1).value << "\n";
}
	
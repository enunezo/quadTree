#include <iostream>
#include "quadTree.h"

using namespace std;

int main(){

	vector <node> information;
	information.push_back(node(0,0));
	information.push_back(node(0,10));
	information.push_back(node(0,-10));
	information.push_back(node(10,0));
	information.push_back(node(-10,0));
	/*for (int i = 0,j = 20; i < 10 && j>=0; ++i, j-=2){
		ne newnode;
		if( i%2 == 0 ){
			get<0>(newnode.data)= i;
			get<1>(newnode.data)= j;
		}
		else{
			get<1>(newnode.data)= i;
			get<0>(newnode.data)= j;
		}
		information.push_back(newnode);
	}
	quadTree a(information);
	a.insert(information);
	*///a.print();
	quadTree a(information);
	// a.insert(information);
	a.print();
	node b(2,9);
	node t(b);
	t.print();
	return 0;
}

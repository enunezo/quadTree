#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class node{
public:
	tuple<int, int> data;
	node * sons[4];
	/*
	sons[0] -> northWest	
	sons[1] -> northEast
	sons[2] -> southEast
	sons[3] -> southWest
			N
		NW 	l	NE
	W ------l-------O			
		SW 	l 	SE
			S
	*/

	node(){
		for (int i = 0; i < 4; ++i){
			sons[i]=NULL;
		}
	}

	node( int x, int y){
		get<0>(data)=x;
		get<1>(data)=y;
		for (int i = 0; i < 4; ++i){
			sons[i]=NULL;
		}
	}

	node( const node & a){
		get<0>(data) = get<0>(a.data);
		get<1>(data) = get<1>(a.data);
		for (int i = 0; i < 4; ++i){
			sons[i] = a.sons[i];
		}	
	}

	node & operator = (node a){
		get<0>(data) = get<0>(a.data);
		get<1>(data) = get<1>(a.data);
		return *this;
	}

	void print(){
		cout<<get<0>(this->data)<<","<<get<1>(this->data);
	}
	~node(){}
};
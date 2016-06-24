#include <iostream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "node.h"

using namespace std;

class quadTree{
public:
	node * head;
	vector< node > information;
	quadTree(vector< node > information_){
		information = information_;
		head = NULL;
	}

	bool isNorthWestPoint(int x, int y, node * current){
		return (x < get<0>(current->data) && y >= get<1>(current->data));
	}

	bool isNorthEastPoint(int x, int y, node * current){
		return (x >= get<0>(current->data) && y > get<1>(current->data));
	}

	bool isSouthEastPoint(int x, int y, node * current){
		return (x > get<0>(current->data) && y <= get<1>(current->data));
	}

	bool isSouthWestPoint(int x, int y, node * current){
		return (x >= get<0>(current->data) && y < get<1>(current->data));
	}

	node getNorthernPoint(vector< node > inf){
		node tmp;
		tmp = inf.at(0);
		for (int i = 1; i < inf.size(); ++i){
			if ( get<1>(tmp.data) < get<1>((inf.at(i)).data) ){
				tmp = inf.at(i);
			}
		}
		return tmp;
	}

	node getSouthernPoint(vector< node > inf){
		node tmp;
		tmp = inf.at(0);
		for (int i = 1; i < inf.size(); ++i){
			if ( get<1>(tmp.data) > get<1>((inf.at(i)).data) ){
				tmp = inf.at(i);
			}
		}
		return tmp;
	}

	node getEasternPoint(vector< node > inf){
		node tmp;
		tmp = inf.at(0);
		for (int i = 1; i < inf.size(); ++i){
			if ( get<0>(tmp.data) < get<0>((inf.at(i)).data) ){
				tmp = inf.at(i);
			}
		}
		return tmp;
	}

	node getWesternPoint(vector< node > inf){
		node tmp;
		tmp = inf.at(0);
		for (int i = 1; i < inf.size(); ++i){
			if ( get<0>(tmp.data) > get<0>((inf.at(i)).data) ){	
				tmp = inf.at(i);
			}
		}
		return tmp;
	}

	node getCenter(vector< node > inf){
		int y = get<1>(getNorthernPoint(inf).data)- ( (get<1>(getNorthernPoint(inf).data)-get<1>(getSouthernPoint(inf).data))/2 );
		int x = get<0>(getEasternPoint(inf).data)- ( (get<0>(getEasternPoint(inf).data)-get<0>(getWesternPoint(inf).data))/2 );
		node newNode(x,y);
		return newNode;
	}

	vector< vector<node> > splitSpace (vector< node > inf){
		node center = getCenter(inf);
		int x = get<0>(center.data);
		int y = get<1>(center.data);
		vector<node> northWest,northEast,southEast,southWest;
		for (int i = 0; i < inf.size(); ++i){
			if( get<0>((inf.at(i)).data)< x && get<1>((inf.at(i)).data)>=y )
				northWest.push_back(inf.at(i));
			if( get<0>((inf.at(i)).data)>=x && get<1>((inf.at(i)).data)> y )
				northEast.push_back(inf.at(i));
			if( get<0>((inf.at(i)).data)> x && get<1>((inf.at(i)).data)<=y )
				southEast.push_back(inf.at(i));
			if( get<0>((inf.at(i)).data)>=x && get<1>((inf.at(i)).data)< y )
				southWest.push_back(inf.at(i));
		}
		vector< vector<node> > result;
		result.push_back(northWest);
		result.push_back(northEast);
		result.push_back(southEast);
		result.push_back(southWest);
		return result;
	}

	bool insert(vector< node > inf) {
        return insert(inf, &head);
    }

	bool insert(vector< node > inf, node ** current){
		if  ( !(*current) )	{
			node tmp  = getCenter(inf);
			node * newNode = &tmp;
			current = &newNode;
			//(*current)->print();
			// cout<<endl;
			vector< vector< node > > newSpace = splitSpace(inf);
			return insert(newSpace.at(0), current) &&
			  	   insert(newSpace.at(1), current) &&
			   	   insert(newSpace.at(2), current) &&
			   	   insert(newSpace.at(3), current);
		}
		if (inf.size() <= 1 ){
			if (inf.size() == 1) {
				if ( isNorthWestPoint( get<0>( (inf.at(0)).data ),get<1>( (inf.at(0)).data ), *current ) ){
					(*current)->sons[0] = &inf.at(0);
					// (*current)->sons[0]->print();
					return true;
				}
			
				else if ( isNorthEastPoint( get<0>( (inf.at(0)).data ),get<1>( (inf.at(0)).data ), *current ) ){
					(*current)->sons[1] = &inf.at(0);
					// (*current)->sons[1]->print();
					return true;
				}

				else if ( isSouthEastPoint( get<0>( (inf.at(0)).data ),get<1>( (inf.at(0)).data ), *current ) ){
					(*current)->sons[2] = &inf.at(0);
					// (*current)->sons[2]->print();
					return true;
				}

				else if ( isSouthWestPoint( get<0>( (inf.at(0)).data ),get<1>( (inf.at(0)).data ), *current ) ){
					(*current)->sons[3] = &inf.at(0);
					// (*current)->sons[3]->print();
					return true;
				}
				else
					return false;
			}
			return false;
		}

		else{			
			node tmp  = getCenter(inf);
			node * newNode = &tmp;
			vector< vector< node > > newSpace = splitSpace(inf);
			for (int i = 0; i < newSpace.size(); ++i){
				node tmp = getCenter( newSpace.at(i) );
				newNode->sons[i] = &tmp;
			}
			return insert(newSpace.at(0), &newNode) &&
			  	   insert(newSpace.at(1), &newNode) &&
			   	   insert(newSpace.at(2), &newNode) &&
			   	   insert(newSpace.at(3), &newNode);
		}
		
		return true; 
	}
//TAREA: RTREE, CONSTRUCCION DEL ARBOL, SPLIT CASOS, MERGE, COMO FUNCIONA EL BOUNDING BOX, MBR,MINIMO RECTANGULO
	void print () {
		cout << head;
		// head->print();
		//print(&head, 0);
	}

    void print (node ** current, int indent) {
		if (*current) {
			//(*current)->print();
			/*
			print(&(*current)->sons[0], indent+1);
			print(&(*current)->sons[1], indent+1);
			for (int i=0; i<indent; i++) cout << "    ";
			(*current)->print();
			cout<<endl;
			print(&(*current)->sons[2], indent+1);
			print(&(*current)->sons[3], indent+1);
			*/
		}
	}


	~quadTree(){}

	/* data */
};
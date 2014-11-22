// Assignment #7
// Name: Jacob Pruitt
// ASU Email Address: jrpruit1@asu.edu
// Description: This header file describes the Vertex class, used in the graph 
//        and Queue to represent the element vertex with a name, distance, and
//				next pointer.

#include <string>

using namespace std;

class Vertex {
	private: 
		string name;
		int distance;
		Vertex * next;

	public:
		// Two constructor functions
		Vertex() {
			distance = 0;
			name = "";
			next = NULL;
		}

		Vertex(string name1, int distance1) {
			distance = distance1;
			name = name1;
			next = NULL;
		}

		string getName() {
			return name;
		}

		int getDistance() {
			return distance;
		}

		Vertex * getNext() {
			return next;
		}

		void setNext(Vertex * other) {
			next = other;
		}
};

void insertInOrder(Vertex * head, Vertex * v) {
	Vertex * temp = head;
	if (temp->getNext() == NULL) {
		head->setNext(v);
	} else {
		bool inserted = false;
		while(inserted == false) {
			if (temp->getNext() == NULL) {
				temp->setNext(v);
				inserted = true;
			} else if (temp->getNext()->getName().compare(v->getName()) > 0) {
				v->setNext(temp->getNext());
				temp->setNext(v);
				inserted = true;
			} else {
				temp = temp->getNext();
			}
		}
	}
};

void deleteList(Vertex * head) {
	while(head != NULL) {
		Vertex * nextVertex = head->getNext();
		delete head;
		head = nextVertex;
	}
};
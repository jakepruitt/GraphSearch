// Assignment #7
// Name: Jacob Pruitt
// ASU Email Address: jrpruit1@asu.edu
// Description: This program describes the Queue class for pushing and pulling
//        various Vertex elements to keep track of what needs to be iterated 
//        through.

#include <iostream>
#include <string>

using namespace std;

class Queue {
	private:
		Vertex * head, * tail;

	public:
		// The constructor function
		Queue() {
			head = NULL;
			tail = NULL;
		}

		void enqueue(Vertex * v) {
			Vertex * cloneV = new Vertex(v->getName(), v->getDistance());

			if (head == NULL) {
				head = cloneV;
			}
			if (tail != NULL) {
				tail->setNext(cloneV);
			}
			tail = cloneV;
		}

		string dequeue() {
			if (head->getNext() == NULL) {
				tail = NULL;
			}

			Vertex * v = head;
			head = head->getNext();

			string name = v->getName();
			delete v;

			return name;
		}

		Vertex * getHead() {
			return head;
		}

		void printQueue() {
			Vertex * temp = head;

			cout << "{ ";
			while (temp != NULL) {
				cout << temp->getName() << " ";
				temp = temp->getNext();
			}
			cout << "}\n";
		}
};
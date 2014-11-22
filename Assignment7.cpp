// Assignment #7
// Name: Jacob Pruitt
// ASU Email Address: jrpruit1@asu.edu
// Description: This program parses the input from the command line, creates
//        a graph data structure, and performs Breadth First Search on the
//        graph, outputting the Queue contents, the array pi content, and the
//				array d content.

#include <iostream> // to use cin and cout
#include <string>		// to use strings
#include <sstream>

#include "Vertex.h"
#include "Queue.h"

using namespace std;

int total;

int listIndex(Vertex * array[], string name) {
	for (int i = 0; i < total; ++i) {
		if (array[i]->getName().compare(name) == 0) {
			return i;
		}
	}
	return -1;
};

void sortNodes(Vertex * arr[]) {
	for (int j = 1; j < total; ++j)

	{
		Vertex * temp = arr[j];

		int i = j-1;

		while(i > -1 && (arr[i]->getName().compare(temp->getName()) > 0)) {
			arr[i+1] = arr[i];
			i = i-1;
		}
		arr[i+1] = temp;
	}
};

int main() {

	string line;
	Vertex * vertex;
	Vertex * adjList[40];
	string color[40];
	Vertex * pi[40];
	int d[40];
	Queue * q = new Queue();

	getline(cin, line);
	istringstream(line) >> total;

	getline(cin, line);

	// Inputting the data into an adjacency list
	for (int i = 0; i < total; ++i) {
		// Parse one whole line
		getline(cin, line);

		istringstream iss(line);
		string elem;

		// Parse the first word, and create an element in the array
		getline(iss, elem, ' ');
		adjList[i] = new Vertex(elem, 0);

		// Loop through the rest of the words, parsing them and turning them
		// into elements that are appended to the list at adjList[i] in alphabetic order
		while( getline(iss, elem, ' ') ) {
			if (elem != "") {
				string elemName = elem.substr(0, elem.find('/'));
				string lengthStr = elem.substr(elem.find('/') + 1, elem.length());
				int length;
				istringstream(lengthStr) >> length;

				// cout << "\tAppending element: " << elemName << " with length: " << length << endl;
				Vertex * v = new Vertex(elemName, length);

				// Insert element v into list in alphabetical order:
				insertInOrder(adjList[i], v);
			}
		}
	}

	sortNodes(adjList);

	// Begin the algorithm for Breadth Search Traversal
	for (int i = 0; i < total; ++i)
	{
		color[i] = "white";
		pi[i] = NULL;
		d[i] = 9999999999;
	}

	int startIndex = listIndex(adjList, "Aluminum");
	// cout << "The starting index for Aluminum is: " << startIndex << endl;

	d[startIndex] = 0;
	color[startIndex] = "gray";
	pi[startIndex] = NULL;

	cout << "The Queue content:\n\n";
	q->enqueue(adjList[startIndex]);

	for (int i = 0; i < total; ++i) {
		q->printQueue();
		string uName = q->dequeue();
		int uIndex = listIndex(adjList, uName);
		Vertex * u = adjList[uIndex];

		Vertex * v = u->getNext();
		if (v == NULL) {
			for (int j = 0; j < total; ++j)
			{
				if (color[j].compare("white") == 0) {
					d[j] = 0;
					q->enqueue(adjList[j]);
				}
			}
		}
		while(v != NULL) {
			int vIndex = listIndex(adjList,v->getName());
			if (color[vIndex].compare("white") == 0) {
				color[vIndex] = "gray";
				d[vIndex] = d[uIndex] + 1;
				pi[vIndex] = u;
				q->enqueue(v);
			}
			v = v->getNext();
		}

		color[uIndex] = "black";
	}

	cout << "\n\nThe array pi content:\n\n";
	for (int i = 0; i < total; ++i) {
		string piName;
		if (pi[i] == NULL) {
			piName = "none";
		} else {
			piName = pi[i]->getName();
		}
		cout << "pi[" << adjList[i]->getName() << "] = " << piName << endl;
	}
	cout << "\n\nThe array d content:\n\n";
	for (int i = 0; i < total; ++i) {
		cout << "d[" << adjList[i]->getName() << "] = " << d[i] << endl;
	}
	for (int i = 0; i < total; ++i) {
		deleteList(adjList[i]);
	}
	return 0;
}
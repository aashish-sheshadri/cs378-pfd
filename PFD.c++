// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "PFD.h"

vector<node> _graph;

bool PFD_read (int numVerts, int numRules, std::istream& in) {
	PFD_construct(numVerts);
	for (int i = 0; i < numRules; ++i) {
		int nodeid;
		cin >> nodeid;
		int numDeps;
		cin >> numDeps;
		vector<int> dep;
		for(int j = 0; j < numDeps; ++j) {
			int temp;
			cin >> temp;
			dep.push_back(temp);
		}
		PFD_construct(nodeid, dep);
	}

}

void PFD_construct(int numVerts) {
	for (int i = 0; i < numVerts; ++i) {
		vector<int> temp_incoming;
		vector<int> temp_outgoing;
		node temp = {i, temp_outgoing, temp_incoming};
		_graph.push_back(temp);
	}
}

int PFD_construct (int nodeId, vector<int> dependencies){
	node Node = _graph[nodeId];
	for (vector_iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		int num = *it;
		Node.incoming.push_back(num);
		node temp = _graph[num];
		temp.outgoing.push_back(nodeId);
	}
}

int PFD_eval () {

	PFD_print();
}

void PFD_print (std::ostream&);

void PFD_solve (std::istream& in, std::ostream& out) {
	int numVerts;
	cin >> numVerts;
	do {
		int numRules;
		cin >> numRules;
		PFD_read(numVerts, numRules, in);
		PFD_construct();
		PFD_eval();
		cin>>numVerts;
	} while (numVerts);
}

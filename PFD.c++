// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "PFD.h"


bool PFD_read (int numVerts, int numRules, std::istream& in) {
	assert(numVerts>0);
    assert(numRules>0);

    vector<node> graph;
    PFD_construct(numVerts, graph);
    assert(!graph.empty());
    int graphSize = graph.size();
	for (int i = 0; i < numRules; ++i) {
		int nodeId;
		cin >> nodeId;
        assert(nodeId>0);
        --nodeId; //nodeId ranges from [1,N]
        assert(nodeId>0);
		int numDeps;
		cin >> numDeps;
        assert(numDeps>0);
		vector<int> dep;
		for(int j = 0; j < numDeps; ++j) {
			int temp;
			cin >> temp;
            assert(temp>0);
            --temp; //nodeId ranges from [1,N]
            assert(temp>0);
			dep.push_back(temp);
		}
        assert(dep.size()>0);
		PFD_construct(nodeid, dep, graph);
        assert(graph.size() == graphSize);
	}
    return (!graph.empty())};

void PFD_construct(int numVerts, vector<node>& graph) {
	assert(numVerts > 0);
    assert(graph.empty());

    for (int i = 0; i < numVerts; ++i) {
		vector<int> temp_incoming;
		vector<int> temp_outgoing;
		node temp (i, temp_outgoing, temp_incoming);
        
        assert(temp.id == i);
        assert(temp.outgoing.empty());
        assert(temp.incoming.empty());

		graph.push_back(temp);
	}
    assert(!graph.empty());}

void PFD_construct (int nodeId, vector<int> dependencies, vector<node>& graph){
	assert(nodeId < (graph.size() - 1));
    assert(!dependencies.empty());
    assert(!graph.empty());

    node& Node = graph[nodeId];
	for (vector_iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		int num = *it;
		Node.incoming.push_back(num);
		node& tempNode = graph[num];
		tempNode.outgoing.push_back(nodeId);
	}}

void PFD_eval () {
}

void PFD_print () {
}

void PFD_solve (std::istream& in, std::ostream& out) {
	int numVerts;
	cin >> numVerts;
	do {
        assert(numVerts>0);
		int numRules;
		cin >> numRules;
        assert(numRules>0);
		PFD_read(numVerts, numRules, in);
		PFD_construct();
		//PFD_eval();
		cin>>numVerts;
	} while (numVerts);}
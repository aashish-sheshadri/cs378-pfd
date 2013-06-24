// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>

#include "PFD.h"


std::vector<node> PFD_read (int numVerts, int numRules, std::istream& in) {
	assert(numVerts>0);
    assert(numRules>=0);

    std::vector<node> graph;
    PFD_construct(numVerts, graph);
    assert(!graph.empty());
    int graphSize = graph.size();
	for (int i = 0; i < numRules; ++i) {
		int nodeId;
        in >> nodeId;
        assert(nodeId>0);
        --nodeId; //nodeId ranges from [1,N]
        assert(nodeId>=0);
		int numDeps;
		in >> numDeps;
        assert(numDeps>0);
		std::vector<int> dep;
		for(int j = 0; j < numDeps; ++j) {
			int temp;
			in >> temp;
            assert(temp>0);
            --temp; //nodeId ranges from [1,N]
            assert(temp>=0);
			dep.push_back(temp);
		}
        assert(dep.size()>0);
		PFD_construct(nodeId, dep, graph);
        assert(graph.size() == static_cast<unsigned int>(graphSize));}
    return (graph);}

void PFD_construct(int numVerts, std::vector<node>& graph) {
	assert(numVerts > 0);
    assert(graph.empty());

    for (int i = 0; i < numVerts; ++i) {
		std::vector<int> temp_incoming;
		std::vector<int> temp_outgoing;
		node temp (i, temp_outgoing, temp_incoming);
        
        assert(temp.id == i);
        assert(temp.outgoing.empty());
        assert(temp.incoming.empty());

		graph.push_back(temp);
	}
    assert(!graph.empty());}

void PFD_construct (int nodeId, std::vector<int> dependencies, std::vector<node>& graph){
	assert(static_cast<unsigned int>(nodeId) <= (graph.size() - 1));
    assert(!dependencies.empty());
    assert(!graph.empty());

    node& Node = graph[nodeId];
	for (std::vector<int>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		int num = *it;
		Node.incoming.push_back(num);
		node& tempNode = graph[num];
		tempNode.outgoing.push_back(nodeId);
	}}

int _delNodeId;
bool checkNode (const node& Node){
    if(Node.id == _delNodeId)
        return true;
    return false;
}

std::vector<int> PFD_eval (std::vector<node>& graph) {
	assert (!graph.empty());

	std::vector<int> result;

	while(!graph.empty()) {  
        std::vector<int> nodeIdx;

        // Push nodes without incoming edges into a vector
		for(std::vector<node>::iterator it = graph.begin(); it != graph.end(); ++it) {
			if((*it).incoming.empty()){
				nodeIdx.push_back((*it).id);
			}
		}

		// Sort vector to get lowest nodeID value among nodes without incoming edges
		std::sort(nodeIdx.begin(),nodeIdx.end());
		int delNodeId = nodeIdx[0];
        _delNodeId = delNodeId;
        
        // Find node that matches delNodeID
		node& delNode = *(std::find_if(graph.begin(),graph.end(),checkNode));
        
        // Remove delNode from incoming edges of other nodes in graph
        for(std::vector<int>::iterator it = delNode.outgoing.begin();it!=delNode.outgoing.end();++it){
            _delNodeId = *it;
            node& restNodes = *(std::find_if(graph.begin(),graph.end(),checkNode));   
            restNodes.incoming.erase(std::remove(restNodes.incoming.begin(), restNodes.incoming.end(),delNodeId), restNodes.incoming.end());} 
		
		// Add delNodeId to result vector	
		result.push_back(delNodeId + 1); 
     
     	// Remove delNode from graph
        _delNodeId = delNodeId;
        graph.erase(std::remove_if(graph.begin(),graph.end(),checkNode),graph.end());   
	}
	return result;
}

void PFD_print (std::vector<int> result, std::ostream& out) {
	bool first = true;
	for(std::vector<int>::iterator it = result.begin();it!=result.end();++it){
		if(!first)
			out<<" ";
		out<<*it;
		first = false;
	}
	out << "\n";
}

void PFD_solve (std::istream& in, std::ostream& out) {
	// Check for presence of information in input stream
	assert (in);
	int numVerts;
	in >> numVerts;
	do {
        assert(numVerts>0);
		int numRules;
		in >> numRules;
        assert(numRules>=0);
		std::vector<node> graph = PFD_read(numVerts, numRules, in);
		std::vector<int> result = PFD_eval(graph);
		PFD_print(result,out);
		in >> numVerts;
	} while (in);}
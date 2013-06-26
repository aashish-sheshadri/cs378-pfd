#ifndef PFD_h
#define PFD_h

#include <iostream>
#include <vector>
#include <algorithm>

struct node {
	int id;
    std::vector<int> outgoing;
    std::vector<int> incoming;
    node(int nId, std::vector<int> out, std::vector<int> in):id(nId),outgoing(out),incoming(in){}
};


// ------------
// PFD_read
// ------------

/**
 * reads two ints into i and j
 * @param numVerts an int indicating number of vertices in the dependency graph
 * @param numRules an int indicating number of rules detailing dependencies
 * @param in a std::istream with dependency rules 
 * @return true if read succeeds, false otherwise
 */
std::vector<node> PFD_read (int numVerts, int numRules, std::istream& in);

// ------------
// PFD_construct
// ------------

/**
 * @param numVerts an int indicating number of vertices in the dependency graph
 * @param graph a vector<node> by reference holding the dependency graph
 */
void PFD_construct(int numVerts, std::vector<node>& graph);

// ------------
// PFD_construct
// ------------

/**
 * @param nodeId an int indicate node number to be updated
 * @param dependencies a vector<int> holding node dependencies 
 * @param graph a vector<node> by reference holding the dependency graph
 */
void PFD_construct (int nodeId, std::vector<int> dependencies, std::vector<node>& graph);

// ------------
// PFD_eval
// ------------

/**
 * @param graph is a vector by reference -- hold the dependency graph
 * @return is a vector of intergers with final results
 */
std::vector<int> PFD_eval (std::vector<node>& graph);


// -------------
// PFD_print
// -------------

/**
 * prints
 * @param result is the vector of results
 * @param out is the output stream to which to print 
 */
void PFD_print (std::vector<int> result, std::ostream& out);

// -------------
// PFD_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void PFD_solve (std::istream& r, std::ostream& w);


#endif // PFD_h
// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>

std::vector<node> PFD_read (int numVerts, int numRules, std::istream& in) {
	assert(numVerts>0);
    assert(numRules>0);

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
	std::vector<int> result;
	while(!graph.empty()) {  
        std::vector<int> nodeIdx;
		for(std::vector<node>::iterator it = graph.begin(); it != graph.end(); ++it) {
			if((*it).incoming.empty()){
				nodeIdx.push_back((*it).id);
			}
		}
        
		std::sort(nodeIdx.begin(),nodeIdx.end());
		int delNodeId = nodeIdx[0];
        _delNodeId = delNodeId;
        
		node& delNode = *(std::find_if(graph.begin(),graph.end(),checkNode));
        
        for(std::vector<int>::iterator it = delNode.outgoing.begin();it!=delNode.outgoing.end();++it){
            _delNodeId = *it;
            node& restNodes = *(std::find_if(graph.begin(),graph.end(),checkNode));   
            restNodes.incoming.erase(std::remove(restNodes.incoming.begin(), restNodes.incoming.end(),delNodeId), restNodes.incoming.end());} 
			
		result.push_back(delNodeId + 1); 
     
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
}

void PFD_solve (std::istream& in, std::ostream& out) {
	do {
		int numVerts;
		in >> numVerts;
        assert(numVerts>0);
		int numRules;
		in >> numRules;
        assert(numRules>0);
		std::vector<node> graph = PFD_read(numVerts, numRules, in);
		std::vector<int> result = PFD_eval(graph);
		PFD_print(result,out);
	} while (!in);}

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout

// ----
// main
// ----

int main () {
    using namespace std;
    PFD_solve(cin, cout);
    return 0;}

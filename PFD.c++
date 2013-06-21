// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>

#include "PFD.h"


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
        std::cout<<std::endl<<"*******************Processing Node: "<<graph[0].id<<std::endl;
        std::cout<<std::endl<<"*******************Graph Size: "<<graph.size()<<std::endl;
        std::vector<int> nodeIdx;
        bool assertTest_1 = false;
		for(std::vector<node>::iterator it = graph.begin(); it != graph.end(); ++it) {
			if((*it).incoming.empty()){
				nodeIdx.push_back((*it).id);
                assertTest_1 = true;
			}
		}
        
        std::cout<<"Here at 1"<<std::endl;
        
        assert(assertTest_1);
		std::sort(nodeIdx.begin(),nodeIdx.end());
		int delNodeId = nodeIdx[0];
        
        std::cout<<"Here at 2"<<std::endl;

		for(std::vector<int>::iterator it = graph[delNodeId].outgoing.begin(); it != graph[delNodeId].outgoing.end(); ++it) {
			//std::vector<int>::iterator iit = graph[*it].incoming.begin();
            unsigned int bDelSize = graph[*it].incoming.size();
            //unsigned int delCounter = 0;
            graph[*it].incoming.erase(std::remove(graph[*it].incoming.begin(), graph[*it].incoming.end(),delNodeId), graph[*it].incoming.end()); 
            //while(iit != graph[*it].incoming.end()){ 
			//	if(*iit == delNodeId){
			//		iit = graph[*it].incoming.erase(iit);
            //        ++delCounter;
            //    } else {
            //    ++iit;}
			//}
            unsigned int aDelSize = graph[*it].incoming.size();
            //assert(delCounter == 1);
            assert(bDelSize == (aDelSize + 1));
		}
		result.push_back(delNodeId + 1);
		
        std::cout<<"Here at 3"<<std::endl;
        //std::vector<node>::iterator it = graph.begin();
        unsigned int bDelSize = graph.size();
        //unsigned int delCounter = 0;
        _delNodeId = delNodeId;
        graph.erase(std::remove_if(graph.begin(),graph.end(),checkNode),graph.end()); 
        //while(it != graph.end()){
		//	if((*it).id == delNodeId){
		//		it = graph.erase(it);
        //        ++delCounter;
        //    } else {
        //    ++it;}
		//}
        unsigned int aDelSize = graph.size();
        //assert(delCounter == 1);
        assert(bDelSize == (aDelSize + 1));
        std::cout<<"Here at 4"<<std::endl<<std::endl;
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

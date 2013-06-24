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
// check_node
// ------------

/**
 * Helper method for PFD_construct(int, std::vector<int>, std::vector<node>&).
 * Checks a node against deletion ID to see if it is the node
 * that needs to be deleted.
 * @param Node Node to check against deletion ID
 * @return True if Node's id matches deletion ID
 */
bool checkNode (const node& Node);

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

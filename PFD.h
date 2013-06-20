#ifndef PFD_h
#define PFD_h

#include <iostream>
#include <vector>

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
bool PFD_read (int numVerts, int numRules, std::istream& in);

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
 * @param 
 * @param
 * @return
 */
void PFD_eval ();


// -------------
// PFD_print
// -------------

/**
 * prints
 * @param
 * @param 
 * @param 
 * @param 
 */
void PFD_print ();

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

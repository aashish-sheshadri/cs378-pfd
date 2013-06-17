#ifndef PFD_h
#define PFD_h

#include <iostream>
#include <vector>

// ------------
// PFD_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool PFD_read (std::istream&);

// ------------
// PFD_solve
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int PFD_construct ();

// ------------
// PFD_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int PFD_eval ();


// -------------
// PFD_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void PFD_print (std::ostream&);

// -------------
// PFD_construct
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void PFD_solve (std::istream&, std::ostream&);

struct node {
	int id;
	vector<int> outgoing;
	vector<int> incoming;
};

#endif // PFD_h

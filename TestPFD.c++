// --------
// includes
// --------

#include <iostream> // cout, endl, ios_base
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "PFD.h"

// -----------
// TestPFD
// -----------

struct TestPFD : CppUnit::TestFixture {
    // ----
    // read
    // ----
    void test_read_1 () {
        //sample input
        int numVerts = 5;
        int numRules = 4;
        std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        const bool b = PFD_read(numVerts,numRules,in);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numVerts == 5);
        CPPUNIT_ASSERT(numRules == 4);}

     void test_read_2 () {
        //sample input
        int numVerts = 100;
        int numRules = 4;
        std::istringstream in("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        const bool b = PFD_read(numVerts,numRules,in);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numVerts == 100);
        CPPUNIT_ASSERT(numRules == 4);}

    void test_read_3 () {
        //sample input
        int numVerts = 5;
        int numRules = 4;
        std::istringstream in("3 1 1\n2 2 5 3\n4 1 3\n5 1 1\n");
        const bool b = PFD_read(numVerts,numRules,in);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(numVerts == 100);
        CPPUNIT_ASSERT(numRules == 4);}
    
    // -----
    // Create graph
    // -----
    void test_PFD_make_graph () {
        vector<node> graph;
        int numVerts = 10;
        PDF_construct(numVerts,graph);
        CPPUNIT_ASSERT(numVerts == 10);
        CPPUNIT_ASSERT(!graph.empty());
        CPPUNIT_ASSERT(graph.size() == 10);
        CPPUNIT_ASSERT(graph[0].id == 0);
        CPPUNIT_ASSERT(graph[0].incoming.empty());
        CPPUNIT_ASSERT(graph[0].outgoing.empty());
        CPPUNIT_ASSERT(graph[9].id == 9);
        CPPUNIT_ASSERT(graph[9].incoming.empty());
        CPPUNIT_ASSERT(graph[9].outgoing.empty());}
    
    // -----
    // Update graph
    // -----
    void test_PFD_construct_1 () {
        vector<int> dependencies; 
        dependencies.push_back(1);
        dependencies.push_back(5);
        
        vector<node> graph;
        int numVerts = 5;
        for (int i = 0; i < numVerts; ++i) {
		    vector<int> temp_incoming;
		    vector<int> temp_outgoing;
		    node temp (i, temp_outgoing, temp_incoming);
		    graph.push_back(temp);}
        
        PFD_construct(2,dependencies,graph);
        CPPUNIT_ASSERT(dependencies.size() == 2);
        CPPUNIT_ASSERT(graph.size() == 5);
        CPPUNIT_ASSERT(graph[2].incoming.size() == 2);
        CPPUNIT_ASSERT(graph[0].outgoing.size() == 1);
        CPPUNIT_ASSERT(graph[4].outgoing.size() == 1); 
        CPPUNIT_ASSERT(graph[2].incoming[0] == 0);
        CPPUNIT_ASSERT(graph[2].incoming[1] == 4);
        CPPUNIT_ASSERT(graph[0].outgoing[0] == 2);
        CPPUNIT_ASSERT(graph[4].outgoing[0] == 2);
        }
    
    // -----
    // eval
    // -----
    void test_eval () {
        PFD_eval();
        CPPUNIT_ASSERT(false);}

    // -----
    // print
    // -----
    void test_print() {
        PFD_print();
        CPPUNIT_ASSERT(false);}

    // -----
    // solve
    // -----
    void test_solve_1 () {
        std::istringstream in("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream out;
        PFD_solve(in,out);
        CPPUNIT_TEST(true);}
    
    void test_solve_2 () {
        std::istringstream in("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n\n5 4\n3 1 1\n2 2 5 3\n4 1 3\n5 1 1\n");
        std::ostringstream out;
        PFD_solve(in,out);
        CPPUNIT_TEST(true);}

    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_PFD_make_graph);
    CPPUNIT_TEST(test_PFD_construct_1);
    CPPUNIT_TEST(test_eval);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestPFD.c++" << endl;
    
    CppUnit::TextTestRunner tr;
    tr.addTest(TestPFD::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;}
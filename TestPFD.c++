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
    
    }
    
    // -----
    // Update graph
    // -----
    void test_PFD_construct () {
        
    }
    
    // -----
    // eval
    // -----
    void test_eval () {
    }

    // -----
    // print
    // -----
    void test_print() {
    }

    // -----
    // solve
    // -----
    void test_solve () {
    }

    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestPFD);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
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

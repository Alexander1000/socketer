#include <cpp-unit-test.h>

CppUnitTest::TestCase* testRequest_PostRequest_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("001-simple-post-request");
    t->printTitle();

    t->finish();
    return t;
}


int main(int argc, char** argv)
{
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(testRequest_PostRequest_Positive());

    testSuite.printTotal();

    return 0;
}

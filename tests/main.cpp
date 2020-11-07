#include <cpp-unit-test.h>
#include <socketer.h>

CppUnitTest::TestCase* testRequest_PostRequest_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("001-simple-post-request");
    t->printTitle();

    char* raw_request = "POST /v1/save HTTP/1.1\n"
                        "Host: 127.0.0.1:50101\n"
                        "User-Agent: curl/7.64.1\n"
                        "Accept: */*\n"
                        "Content-Length: 6\n"
                        "Content-Type: application/x-www-form-urlencoded\n"
                        "\n"
                        "test=1";

    Socketer::Request r(raw_request);

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

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
                        "Content-Type: application/x-www-form-urlencoded"
                        "\n\r\n\r"
                        "test=1\0";

    Socketer::Request r(raw_request);

    // assert main header
    CppUnitTest::assertEquals(t, "POST", r.method);
    CppUnitTest::assertEquals(t, "/v1/save", r.uri);
    CppUnitTest::assertEquals(t, "HTTP/1.1", r.protocol);

    // assert headers
    CppUnitTest::assertEquals(t, "127.0.0.1:50101", r.headers.at("Host"));
    CppUnitTest::assertEquals(t, "curl/7.64.1", r.headers.at("User-Agent"));
    CppUnitTest::assertEquals(t, "*/*", r.headers.at("Accept"));
    CppUnitTest::assertEquals(t, "6", r.headers.at("Content-Length"));
    CppUnitTest::assertEquals(t, "application/x-www-form-urlencoded", r.headers.at("Content-Type"));

    // assert body
    CppUnitTest::assertEquals(t, "test=1", r.raw_body);

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

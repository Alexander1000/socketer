#include <cpp-unit-test.h>
#include <socketer.h>
#include <thread>
#include <curl/curl.h>

CppUnitTest::TestCase* testRequest_PostRequest_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("001-simple-post-request");
    t->printTitle();

    char* raw_request = "POST /v1/save HTTP/1.1\r\n"
                        "Host: 127.0.0.1:50101\r\n"
                        "User-Agent: curl/7.64.1\r\n"
                        "Accept: */*\r\n"
                        "Content-Length: 6\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "\r\n"
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

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CppUnitTest::TestCase* testDefaultServe_SimpleRequest_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("002-default-serve-simple-request");
    t->printTitle();

    CURL* c;
    c = curl_easy_init();

    std::string readBuffer;
    std::string headerBuffer;

    curl_easy_setopt(c, CURLOPT_URL, "127.0.0.1:49900" );
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(c, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(c, CURLOPT_HEADERFUNCTION, WriteCallback);
    curl_easy_setopt(c, CURLOPT_HEADERDATA, &headerBuffer);
    curl_easy_perform(c);
    curl_easy_cleanup(c);

    CppUnitTest::assertEquals(
        t,
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 15\r\n"
        "Server: socketer/1.0.0\r\n\r\n",
        headerBuffer
    );

    CppUnitTest::assertEquals(
        t,
        "default handler",
        readBuffer
    );

    t->finish();
    return t;
}

void run_server() {
    std::cout << "Run Server" << std::endl;
    Socketer::Socketer s;
    s.listen("127.0.0.1", 49900);
    s.dispatch();
}

int main(int argc, char** argv)
{
    std::thread t(run_server);
    t.detach();

    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(testRequest_PostRequest_Positive());

    testSuite.addTestCase(testDefaultServe_SimpleRequest_Positive());

    testSuite.printTotal();

    return 0;
}

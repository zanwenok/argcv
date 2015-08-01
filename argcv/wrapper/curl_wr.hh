#ifndef ARGCV_WRAPPER_CURL_WR_HH
#define ARGCV_WRAPPER_CURL_WR_HH

#include <stdio.h>

#include <openssl/ssl.h>
#include <curl/curl.h>

// http://curl.haxx.se/libcurl/c/curl_easy_setopt.html

#include <string>
#include <vector>

namespace argcv {
namespace wrapper {
namespace curl {

enum class CURL_VERSION : unsigned char { HTTP_VERSION_1_0, HTTP_VERSION_1_1, HTTP_VERSION_2_0 };

class curl_wr_resp {
public:
    std::vector<std::string> headers;
    std::string body;
};


class curl_wr {
public:
    curl_wr(const std::string& url) : url(url), handler(curl_easy_init()) {
        curl_global_init(CURL_GLOBAL_ALL);  // In windows, this will init the winsock stuff
        // handler = curl_easy_init();
        if (handler) {
            curl_easy_setopt(handler, CURLOPT_URL, url.c_str());
            headers = NULL;
            _e = false;
        } else {
            _e = true;
        }
    }

    ~curl_wr() {
        if (!_e) {
            curl_easy_cleanup(handler);
        }
        if (!headers) {
            curl_slist_free_all(headers);
        }
        curl_global_cleanup();
    }

    bool _err() { return _e; }

    void referer(const std::string& rurl);
    void header(const std::string& hstr);
    void useragent(const std::string& useragent);
    void verbose(bool flag = true);

    void conn_timeout(long sec);
    void conn_timeout_ms(long ms);
    void timeout(long sec);
    void timeout_ms(long ms);

    void version(CURL_VERSION v = CURL_VERSION::HTTP_VERSION_1_1);

    curl_wr_resp& get();

    curl_wr_resp& resp() { return _resp; }

private:
    const std::string url;
    CURL* handler;
    struct curl_slist* headers;
    bool _e;
    curl_wr_resp _resp;
    void pre_request();
};
}
}
}  // namespace argcv::wrapper::curl

#endif  // ARGCV_WRAPPER_CURL_WR_HH

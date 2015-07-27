#include "argcv/wrapper/curl_wr.hh"

#include <cstdio>

#include <string>

namespace argcv {
namespace wrapper {
namespace curl {

static size_t __curl_header_callback(char *buffer, size_t size, size_t nmemb, void *_resp) {
    printf("__curl_header_callback: [%s] %zu %zu %x\n", buffer, size, nmemb, _resp);
    curl_wr_resp *_r = (curl_wr_resp *)_resp;
    //_r->headers.push_back(std::string(buffer,size * nmemb));
    return nmemb * size;
}
size_t __curl_write_callback(char *ptr, size_t size, size_t nmemb, void *_resp) {
    printf("__curl_write_callback: [%s] %zu %zu", ptr, size, nmemb);
    curl_wr_resp *_r = (curl_wr_resp *)_resp;
    // for (size_t i = 0; i < size; i++) _r->body += std::string(ptr, nmemb);
    return nmemb * size;
}
void curl_wr::pre_request() {
    curl_easy_setopt(handler, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(handler, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(handler, CURLOPT_HTTPHEADER, headers);
    // curl_easy_setopt(handler, CURLOPT_READDATA, &i);

    curl_easy_setopt(handler, CURLOPT_HEADERFUNCTION, __curl_header_callback);
    curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, __curl_write_callback);
    int i = 1;
    curl_easy_setopt(handler, CURLOPT_WRITEDATA, (void *)&i);
    // curl_easy_setopt(handler, CURLOPT_WRITEDATA, &_resp);
}

curl_wr_resp &curl_wr::get() {
    if (!_e) {
        pre_request();
        _e = CURLE_OK != curl_easy_perform(handler);
        return _resp;
    } else {
        return _resp;
    }
}
}
}
}  // namespace argcv::wrapper::curl

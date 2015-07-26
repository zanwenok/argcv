#include "argcv/string/string.hh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <string>

#include "porter2_stemmer.hh"

namespace argcv {
namespace string {

/**
 * stemm a string
 */
std::vector<std::string> stemm_s(const std::string &str) {
    std::vector<std::string> rt;
    std::string buff;
    size_t sz = str.length();
    uint8_t m = 0;
    for (size_t i = 0; i < sz; i++) {
        char ch = str[i];
        uint8_t cm = 0;
        if (isupper(ch) || islower(ch)) {
            cm = 1;
            ch = tolower(ch);
        } else {
            switch (ch) {
                case '\r':
                case '\n':
                case '\t':
                case '\b':
                case ' ':
                    cm = 0;
                    break;
                case '\'':
                case '\"':
                case '/':
                case '[':
                case ']':
                case '%':
                case '&':
                case '_':
                case '(':
                case ')':
                    cm = 2;
                    break;
                default:
                    cm = 3;
            }
        }

        if (m != cm) {
            Porter2Stemmer::stem(buff);
            if (buff.length() > 0) {
                rt.push_back(buff);
                buff.clear();
            }
            m = cm;
        }
        if (cm != 0) {
            buff += ch;
        }
    }
    Porter2Stemmer::stem(buff);
    if (buff.length() > 0) {
        rt.push_back(buff);
        buff.clear();
    }
    return rt;
}

/**
 * stemm a string, it will remove all Non ASCII words
 */
std::vector<std::string> stemm_s_cl(const std::string &str) {
    std::vector<std::string> rt;
    std::string buff;
    size_t sz = str.length();
    for (size_t i = 0; i < sz; i++) {
        char ch = str[i];
        if (isupper(ch) || islower(ch)) {
            buff += tolower(ch);  // forces lower case
        } else {
            Porter2Stemmer::stem(buff);
            if (buff.length() > 0) {
                rt.push_back(buff);
                buff.clear();
            }
        }
    }
    Porter2Stemmer::stem(buff);
    if (buff.length() > 0) {
        rt.push_back(buff);
        buff.clear();
    }
    return rt;
}

/**
 * stemm a word
 */
std::string stemm_w(const std::string &word) {
    std::string buff = word;
    Porter2Stemmer::stem(buff);
    return buff;
}
}
}  // argcv::string

#ifndef ARGCV_IR_INDEX_FIELD_HH
#define ARGCV_IR_INDEX_FIELD_HH

#include <string>

#include "argcv/string/string.hh"

namespace argcv {
namespace ir {
namespace index {

using argcv::string::as_str;

enum class FIELD_TYPE : unsigned char {
    UNKNOWN = 0x00,
    TEXT = 0x01,
    STRING = 0x02,
    LONG = 0x03,
    DOUBLE = 0x04,
    VECTOR = 0x05
};

enum class DATA_STORE : unsigned char { NO = 0x00, YES = 0x08 };

template <typename T>
class field {
public:
    field(FIELD_TYPE t, T d, DATA_STORE s = DATA_STORE::YES) : t(t), d(d), s(s) {}

    field(FIELD_TYPE t, T d, bool s = true) : t(t), d(d), s(s ? DATA_STORE::YES : DATA_STORE::NO) {}

    std::string to_str() {
        std::string str(as_str<unsigned char>((unsigned char)t | (unsigned char)s));
        str += as_str<T>(d);
        return str;
    }

    bool orig() { return s == DATA_STORE::YES; }

    static FIELD_TYPE type_test(const std::string& v) {
        return (FIELD_TYPE)(v.length() > 0 ? v[0] & 0x07 : 0x00);
    }

    static DATA_STORE store_test(const std::string& v) {
        return (DATA_STORE)(v.length() > 0 ? v[0] & 0x08 : 0x00);
    }

protected:
    FIELD_TYPE t;
    T d;
    DATA_STORE s;
};

class long_field : public field<int64_t> {
public:
    long_field(int64_t d, DATA_STORE s = DATA_STORE::YES) : field<int64_t>(FIELD_TYPE::LONG, d, s) {}
};

class double_field : public field<double> {
public:
    double_field(double d, DATA_STORE s = DATA_STORE::YES) : field<double>(FIELD_TYPE::DOUBLE, d, s) {}
};

class string_field : public field<std::string> {
public:
    string_field(const std::string& d, DATA_STORE s = DATA_STORE::YES)
        : field<std::string>(FIELD_TYPE::STRING, d, s) {}

    std::string to_str() {
        std::string str(as_str<unsigned char>((unsigned char)t | (unsigned char)s));
        str += d;
        return str;
    }

protected:
    string_field(FIELD_TYPE t, const std::string& d, DATA_STORE s = DATA_STORE::YES)
        : field<std::string>(t, d, s) {}
};

class text_field : public string_field {
public:
    text_field(const std::string& d, DATA_STORE s = DATA_STORE::YES) : string_field(FIELD_TYPE::TEXT, d, s) {}
};
}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_FIELD_HH
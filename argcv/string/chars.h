#ifndef ARGCV_STRING_CHARS_H
#define ARGCV_STRING_CHARS_H

#ifdef __cplusplus
extern "C" {
#endif

inline int is_western_space(char ch) {
    switch (ch) {
        case 0x09:
        case 0x0A:
        case 0x0D:
        case 0x20:
            return 1;
        default:
            return 0;
    }
}

inline int is_western_punct(char ch) {
    // see if it is either a space, control character, or alphanumeric and negate that
    return ch > 0
           && !(((ch >= 0x30 /*'0'*/) && (ch <= 0x39 /*'9'*/))
                || ((ch >= 0x41 /*'A'*/) && (ch <= 0x5A /*'Z'*/))
                || ((ch >= 0x61 /*'a'*/) && (ch <= 0x7A /*'z'*/)) || ((ch >= 0x00) && (ch <= 0x20)));
}

inline int is_western_hyphen(char ch) { return ch == 0x2D; }

inline int is_western_character(char ch) {
    return (((ch >= 0x30 /*'0'*/) && (ch <= 0x39 /*'9'*/)) || ((ch >= 0x41 /*'A'*/) && (ch <= 0x5A /*'Z'*/))
            || ((ch >= 0x61 /*'a'*/) && (ch <= 0x7A /*'z'*/)));
}

#ifdef __cplusplus
}
#endif

#endif  // ARGCV_STRING_CHARS_H

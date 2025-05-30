#ifndef ERRORS_H
#define ERRORS_H

enum{
    SUCCESS,
    E_NO_NEWLINE,
    E_WORD_EXPECTED_REDIRECT,
    E_CLOSE_EXPECTED,
    E_WORD_OR_OPEN_EXPECTED,
    ENUM_ERRORS_END
};

const char *error_message(int);

#endif

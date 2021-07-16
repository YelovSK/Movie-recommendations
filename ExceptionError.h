#ifndef HODNOTENIEFILMOV_EXCEPTIONERROR_H
#define HODNOTENIEFILMOV_EXCEPTIONERROR_H
#include <exception>

using namespace std;

class ExceptionError : exception {
    string text;
public:
    explicit ExceptionError(const char *chyba) {text = chyba;};
    string getMessage() {return text;};
};

#endif //HODNOTENIEFILMOV_EXCEPTIONERROR_H

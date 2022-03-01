
#include "string_.h"

size_t strLen_(const char *begin){
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;

}

char* find(char *begin, char *end, int ch){
    while (begin != end && *begin != ch)
        begin ++;
    return begin;
}

char* findNonSpace(char *begin){
    while (*begin != '\0') {
        if (!isspace(*begin))
            return begin;
        begin++;
    }
    return begin;
}

char* findSpace(char *begin){
    while (*begin != '\0') {
        if (isspace(*begin))
            return begin;
        begin++;
    }
    return begin;
}

char* findNonSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend) {
        if (!isspace(*rbegin))
            return rbegin;
        rbegin--;
    }
    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend) {
        if (isspace(*rbegin))
            return rbegin;
        rbegin--;
    }
    return rbegin;
}

int strcmp ( const char *lhs , const char *rhs){
    while (*lhs && (*lhs == *rhs)) {
        lhs++, rhs++;
    }
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination){
    memcpy(&beginSource, beginDestination, *endSource);
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource))
            *beginDestination = *beginSource;
        beginSource++;
        beginDestination++;
    }
     return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)){
    while (rendSource != rbeginSource){
        if(f(*rbeginSource))
            *beginDestination = *rbeginSource;
        rbeginSource--;
        beginDestination++;
    }
    return beginDestination;
}

// 1 задача

char getEndOfString(char *begin){
    while(*begin != '\0')
        begin++;
    return begin;
}

void removeNonLetters ( char *s) {
    char * endSource = getEndOfString (s);
    char * destination = copyIf (s, endSource , s, isgraph );
    * destination = '\0';
}




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
}

char* findSpace(char *begin){
    while (*begin != '\0') {
        if (isspace(*begin))
            return begin;
        begin++;
    }
}

char* findNonSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend) {
        if (!isspace(*rbegin))
            return rbegin;
        rbegin--;
    }
}

char* findSpaceReverse(char *rbegin, const char *rend){
    while(rbegin != rend) {
        if (isspace(*rbegin))
            return rbegin;
        rbegin--;
    }
}

int strcmp ( const char *lhs , const char *rhs){
    while (*lhs && (*lhs == *rhs)) {
        lhs++, rhs++;
    }
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination){
    memcpy(&beginDestination, beginSource, endSource - beginSource);

    return beginDestination + (endSource - beginSource);
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
     return beginDestination;
}


char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)){
    while (rendSource != rbeginSource){
        if(f(*rbeginSource)) {
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }
    return beginDestination;
}

// 1 задача

char getEndOfString(char *begin){
    while(*begin != '\0')
        begin++;
    return *begin;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

// 2 задача

void removeExtraSpaces(char *s) {
    char *begin = s + 1;
    s++;
    while (*s != '\0') {
        if (isspace(*begin) && isspace(*s - 1))
            begin++;
        else{
                *s = *begin;
                s++;
                begin++;
            }
    }

    *s = '\0';
}


// 3 задача

char _stringBuffer[MAX_STRING_SIZE + 1];

typedef struct WordDescriptor {
    char *begin ;   // позиция начала слова
    char *end ;     // позиция первого символа, после последнего символа слова
} WordDescriptor;

int getWord (char *beginSearch, WordDescriptor *word){
    word->begin = findNonSpace (beginSearch);
    if (*word -> begin == '\0')
        return 0;

    word->end = findSpace(word->begin);

    return 1;
}



void digitToStart (WordDescriptor word){
    char *endStringBuff = copy(word.begin, word.end, _stringBuffer);

    char *recPosition = copyIf(endStringBuff, _stringBuffer, word.end, isalpha);

    copyIf(_stringBuffer, endStringBuff, recPosition, isdigit);
}

int getWordReverse (char *rbeginSearch, const char *rend, WordDescriptor *word){
    word->begin = findNonSpaceReverse(rbeginSearch, rend);
    if (*word->begin != *rend)
        return 0;

    word->end = findNonSpaceReverse(word->begin, rend);

    return 1;
}

// 4 задача
void replaceNumberWithSpaces(char *s){
    char *getEndS = getEndOfString(s);
    char *startStringBuffer = _stringBuffer;
    char *stringBuffer = copy(s, getEndS, _stringBuffer);
    *stringBuffer = '\0';

    while (*startStringBuffer != '\0'){
        if (isdigit(*startStringBuffer)){
            int temp = *startStringBuffer - 48;
            while (temp--) {
                *s = ' ';
                s++;
            }
        } else {
            *s = *startStringBuffer;
            s++;
            startStringBuffer++;
        }
    }

    *s = '\0';
}

// 6 задача //
bool isSortedByLexicographicDictionary (char *s) {
    WordDescriptor w1;
    if (!getWord(s, &w1))
        return true;

    WordDescriptor w2 = w1;
    char *begin = (w2).end;
    while (getWord(begin, &w1)) {
        if (strcmp((w1).begin, (w2).begin) > 0)
            return false;

        w2 = w1;
        begin = w2.end;
    }
    return true;
}
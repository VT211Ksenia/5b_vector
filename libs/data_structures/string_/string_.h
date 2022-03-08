#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include <memory.h>
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

#ifndef UNTITLED10_STRING__H
#define UNTITLED10_STRING__H

typedef struct WordDescriptor {
    char *begin ; // позиция начала слова
    char *end ; // позиция первого символа, после последнего символа слова
} WordDescriptor;

char* reverseString (char *s);


typedef struct BagOfWords{
    WordDescriptor words[1000];
    size_t size;
} BagOfWords;

size_t strLen_(const char *begin);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char* findNonSpaceReverse(char *rbegin, const char *rend);

char* findSpaceReverse(char *rbegin, const char *rend);

int strcmp ( const char *lhs , const char *rhs);

char* copy(const char *beginSource, const char *endSource, char *beginDestination);

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

bool isSortedByLexicographicDictionary (char *s);

void removeExtraSpaces(char *s);

void removeNonLetters(char *s);

#endif //UNTITLED10_STRING__H

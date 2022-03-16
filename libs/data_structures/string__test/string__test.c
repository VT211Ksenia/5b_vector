#include "string__test.h"
#include "C:/Users/User/CLionProjects/untitled10/libs/data_structures/string_/string_.h"

void test_strlen_stringEmpty() {
    char *s = "";

    assert(strLen_(s) == 0);
}

void test_strlen_stringWithoutSpace() {
    char *s = "unnicorn";

    assert(strLen_(s) == 8);
}

void test_strlen_stringWithSpace() {
    char *s = "Hello world!";

    assert(strLen_(s) == 12);

}

void test_strlen() {
    test_strlen_stringEmpty();
    test_strlen_stringWithoutSpace();
    test_strlen_stringWithSpace();
}


void test_find_stringNoElement() {
    char *s = "unnicorn";

    assert(*(find(s, &s[strLen_(s)], 'w')) == '\0');
}

void test_find_stringIsElement() {
    char *s = "unnicorn";

    assert(*(find(s, "\0", 'p')) == 'p');
}

void test_find() {
    test_find_stringNoElement();
    test_find_stringIsElement();
}

void test_findNonSpace_stringEmpty() {
    char *s = "";

    assert(*(findNonSpace(s)) == '\0');
}

void test_findNonSpace_stringSpace() {
    char *s = " ";

    assert(*(findNonSpace(s)) == '\0');
}

void test_findNonSpace_stringWithoutSpace() {
    char *s = "unnicorn";

    assert(*(findNonSpace(s)) == 'u');
}

void test_findNonSpace_stringWithSpace() {
    char *s = "\t \n \r \t \r w";

    assert(*(findNonSpace(s)) == 'w');
}

void test_findNonSpace() {
    test_findNonSpace_stringEmpty();
    test_findNonSpace_stringSpace();
    test_findNonSpace_stringWithoutSpace();
    test_findNonSpace_stringWithSpace();
}

void test_findSpace_stringEmpty() {
    char *s = "";

    assert(*(findSpace(s)) == '\0');
}

void test_findSpace_stringWithoutSpace() {
    char *s = "unnicornspace";

    assert(*(findSpace(s)) == '\0');
}

void test_findSpace_stringWithSpace() {
    char *s = "unicorn space";

    assert(*(findSpace(s)) == *(s + 8));
}

void test_findSpace() {
    test_findSpace_stringEmpty();
    test_findSpace_stringWithoutSpace();
    test_findSpace_stringWithSpace();
}

void test_findNonSpaceReverse_stringEmpty() {
    char *s = "";

    assert(*(findNonSpaceReverse(s, s - 1)) == '\0');
}

void test_findNonSpaceReverse_stringWithoutSpace() {
    char *s = "unnicorn";

    assert(*(findNonSpaceReverse(s + 7, s - 1)) == 'i');
}

void test_findNonSpaceReverse_stringWithSpace() {
    char *s = " \t \t k u r a p i k a\t \r \t";

    assert(*(findNonSpaceReverse(s + 34, s - 1)) == 'a');
}

void test_findNonSpaceReverse() {
    test_findNonSpaceReverse_stringEmpty();
    test_findNonSpaceReverse_stringWithoutSpace();
    test_findNonSpaceReverse_stringWithSpace();
}

void test_findSpaceReverse_stringSpace() {
    char *s = "";

    assert(*(findSpaceReverse(s, s - 1)) == '\0');
}

void test_findSpaceReverse_stringWithoutSpace() {
    char *s = "unnicorn";

    assert(*(findSpaceReverse(s + 7, s - 1)) == *(s - 1));
}

void test_findSpaceReverse_stringWithSpace() {
    char *s = " \t \t u n i c o r n \t \r \t";

    assert(*(findSpaceReverse(s + 34, s - 1)) == '\t');
}

void test_findSpaceReverse() {
    test_findSpaceReverse_stringSpace();
    test_findSpaceReverse_stringWithoutSpace();
    test_findSpaceReverse_stringWithSpace();
}

void test_strcmp_stringEqual() {
    char *s1 = "hotake";
    char *s2 = "hotake";

    assert(strcmp(s1, s2) == 0);
}

void test_strcmp_stringNonEqual_firstGreaterSecond() {
    char *s1 = "death";
    char *s2 = "life";

    assert(strcmp(s1, s2) == 'd' - 'l');
}

void test_strcmp_stringNonEqual_secondGreaterFirst() {
    char *s1 = "shikamaru";
    char *s2 = "BEST BOY";

    assert(strcmp(s1, s2) == 's' - 'B');
}

void test_strcmp() {
    test_strcmp_stringEqual();
    test_strcmp_stringNonEqual_firstGreaterSecond();
    test_strcmp_stringNonEqual_secondGreaterFirst();
}

void test_copy_fullString() {
    char s1[MAX_STRING_SIZE] = "kageyama ";
    char s2[MAX_STRING_SIZE] = " ";

    char *dst = copy(s1, s1 + 8, s2);

    char expectation[MAX_STRING_SIZE] = "kurapika";

    assert(strcmp(s2, expectation) == 0 && dst == &s2[strLen_(s2)]);
}

void test_copy_partString() {
    char s1[MAX_STRING_SIZE] = "picachu";
    char s2[MAX_STRING_SIZE] = " pico";

    char *dst = copy(s1 + 4, s1 + 8, s2);

    char
            expectation[MAX_STRING_SIZE] = "pikapico";

    assert(strcmp(s2, expectation) == 0 && dst == &s2[strLen_(s2) - 4]);
}

void test_copy() {
    test_copy_fullString();
    test_copy_partString();
}

void test_copyIf_digit() {
    char s1[MAX_STRING_SIZE] = "k2r8p1k3";
    char s2[MAX_STRING_SIZE] = " pico";

    char *dst = copyIf(s1 + 4, s1 + 8, s2, isdigit);

    char expectation[MAX_STRING_SIZE] = "13pico";

    assert(strcmp(s2, expectation) == 0 && dst == &s2[strLen_(s2) - 4]);
}

void test_copyIf() {
    test_copyIf_digit();
}

void test_copyIfReverse_digit() {
    char s1[MAX_STRING_SIZE] = "k2r8p1k3";
    char s2[MAX_STRING_SIZE] = " pico";

    char *dst = copyIfReverse(s1 + 8, s1, s2, isdigit);

    char expectation[MAX_STRING_SIZE] = "3182pico";

    assert(strcmp(s2, expectation) == 0 && dst == &s2[strLen_(s2) - 4]);
}

void test_copyIfReverse() {
    test_copyIfReverse_digit();
}

void test_functions() {
    test_strlen();
    test_find();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
    test_copy();
    test_copyIf();
    test_copyIfReverse();
}

void test_removeNonLetters_emptyString() {
    char s[MAX_STRING_SIZE] = "";

    removeNonLetters(s);

    char expectation[MAX_STRING_SIZE] = "";

    assert(strcmp(s, expectation) == 0);
}

void test_removeNonLetters_withoutSpace() {
    char s[MAX_STRING_SIZE] = "naruto";

    removeNonLetters(s);

    char expectation[MAX_STRING_SIZE] = "naruto";

    assert(strcmp(s, expectation) == 0);
}

void test_removeNonLetters_allSpaceSymbols() {
    char s[MAX_STRING_SIZE] = "\t \n \n \t";

    removeNonLetters(s);

    char expectation[MAX_STRING_SIZE] = "";

    assert(strcmp(s, expectation) == 0);
}

void test_removeNonLetters_withSpace() {
    char s[MAX_STRING_SIZE] = "n a\tr u t o";

    removeNonLetters(s);

    char expectation[MAX_STRING_SIZE] = "naruto";

    assert(strcmp(s, expectation) == 0);
}

void test_removeNonLetters() {
    test_removeNonLetters_emptyString();
    test_removeNonLetters_withoutSpace();
    test_removeNonLetters_allSpaceSymbols();
    test_removeNonLetters_withSpace();
}


void test_removeExtraSpaces_emptyString() {
    char s[MAX_STRING_SIZE] = "";

    removeExtraSpaces(s);

    char expectation[MAX_STRING_SIZE] = "";

    assert(strcmp(s, expectation) == 0);
}

void test_removeExtraSpaces_allSpaces() {
    char s[MAX_STRING_SIZE] = " ";

    removeExtraSpaces(s);

    char expectation[MAX_STRING_SIZE] = " ";

    assert(strcmp(s, expectation) == 0);
}

void test_removeExtraSpaces_stringWithoutSpaces() {
    char s[MAX_STRING_SIZE] = "naruto";

    removeExtraSpaces(s);

    char expectation[MAX_STRING_SIZE] = "naruto";


    assert(strcmp(s, expectation) == 0);
}

void test_removeExtraSpaces_stringWithSpaces() {
    char s[MAX_STRING_SIZE] = "n ar uto ";

    removeExtraSpaces(s);

    char expectation[MAX_STRING_SIZE] = "n ar uto ";

    assert(strcmp(s, expectation) == 0);
}

void test_removeExtraSpaces() {
    test_removeExtraSpaces_emptyString();
    test_removeExtraSpaces_allSpaces();
    test_removeExtraSpaces_stringWithoutSpaces();
    test_removeExtraSpaces_stringWithSpaces();
}

void test_areWordsOfStringLexicographicallyOrdered_emptyString() {
    char s[MAX_STRING_SIZE] = "";

    assert(isSortedByLexicographicDictionary(s) == true);
}

void test_areWordsOfStringLexicographicallyOrdered_twoWordsEquals() {
    char s[MAX_STRING_SIZE] = "naruto naruto";

    assert(isSortedByLexicographicDictionary(s) == true);
}

void test_areWordsOfStringLexicographicallyOrdered_w1LessW2() {
    char s[MAX_STRING_SIZE] = "narut naruto";

    assert(isSortedByLexicographicDictionary(s) == true);
}

void test_areWordsOfStringLexicographicallyOrdered_w1MoreW2() {
    char s[MAX_STRING_SIZE] = "naruto narut";

    assert(isSortedByLexicographicDictionary(s) == false);
}

void test_areWordsOfStringLexicographicallyOrdered() {
    test_areWordsOfStringLexicographicallyOrdered_emptyString();
    test_areWordsOfStringLexicographicallyOrdered_twoWordsEquals();
    test_areWordsOfStringLexicographicallyOrdered_w1LessW2();
    test_areWordsOfStringLexicographicallyOrdered_w1MoreW2();
}

void test_reverseString_emptyString() {
    char s[MAX_STRING_SIZE] = "";

    reverseString(s);

    char expectation[MAX_STRING_SIZE] = "";

    assert(strcmp(s, expectation) == 0);
}

void test_reverseString_oneWord() {
    char s[MAX_STRING_SIZE] = "jaba";

    reverseString(s);

    char expectation[MAX_STRING_SIZE] = "jaba";

    assert(strcmp(s, expectation) == 0);
}

void test_reverseString_twoWord() {
    char s[MAX_STRING_SIZE] = "jaba man";

    reverseString(s);

    char expectation[MAX_STRING_SIZE] = "man jaba";

    assert(strcmp(s, expectation) == 0);
}

void test_reverseString_fewWord() {
    char s[MAX_STRING_SIZE] = "best jaba man";

    reverseString(s);

    char expectation[MAX_STRING_SIZE] = "man jaba best";

    assert(strcmp(s, expectation) == 0);
}

void test_reverseWordsOfString() {
    test_reverseString_emptyString();
    test_reverseString_oneWord();
    test_reverseString_twoWord();
    test_reverseString_fewWord();
}



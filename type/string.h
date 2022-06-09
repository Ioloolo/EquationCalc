#ifndef _EQUATION_CALC_TYPE_STRING_HEADER_
#define _EQUATION_CALC_TYPE_STRING_HEADER_

#include <string.h>
#include <stdlib.h>

// define macro
#define String struct String

// define struct
String {
    // field
    char *string;

    // method
    char (*at)         (String *, int);
    int  (*length)     (String *);
    void (*removeSpace)(String *);
};

// constructor list
String stringFrom(char *);

// method list
char at         (String *, int);    // return character at index of string
int  length     (String *);         // return length of string
void removeSpace(String *);         // remove space in string

// define constructor
String stringFrom(char *str) {
    String string;

    char *s = (char *) malloc(sizeof(char) * strlen(str));
    strcpy(s, str);

    string.string      = s;
    string.at          = at;
    string.length      = length;
    string.removeSpace = removeSpace;

    return string;
}

//define method
char at(String *this, int index) {
    return this->string[index];
}

int length(String *this) {
    return (int) strlen(this->string);
}

void removeSpace(String *this) {
    for (int i = 0; i < this->length(this);)
        if (this->at(this, i) == ' ')
            for (int j = i; j < this->length(this); j++)
                this->string[j] = this->string[j+1];
        else i++;
}

#endif //_EQUATION_CALC_TYPE_STRING_HEADER_

#ifndef _EQUATION_CALC_TYPE_EQUATION_HEADER_
#define _EQUATION_CALC_TYPE_EQUATION_HEADER_

#include <stdio.h>
#include "string.h"


// define macro
#define Equation struct Equation

// define struct
Equation {
    // field
    String  oe;
    String  equation;
    int     degree;
    int    *coefficients;
    double  right;
    
    // method
    void (*refreshEquationString)(Equation *);
};

// constructor list
Equation equationFromCoefficients(int *);
Equation equationFromString      (String eq);

// method list
void refreshEquationString(Equation *);

// static method list
int    *parseEquationFromString  (      String);
int     getDegreeFromCoefficients(const int *);
String  coefficientsToString     (const int *);

// define constructor
Equation equationFromCoefficients(int *coefficients) {
    Equation equation;

    coefficients[5] = 0;

	equation.oe	                   = coefficientsToString(coefficients);
    equation.equation              = coefficientsToString(coefficients);
    equation.coefficients          = coefficients;
    equation.right                 = 0;
    equation.degree                = getDegreeFromCoefficients(coefficients);
    equation.refreshEquationString = refreshEquationString;

    return equation;
}

Equation equationFromString(String eq) {
    return equationFromCoefficients(parseEquationFromString(eq));
}

// define method
void refreshEquationString(Equation *this) {
	this->equation = coefficientsToString(this->coefficients);
}

// define static method
int *parseEquationFromString(String eq) {
    int *coefficients = (int *) malloc(sizeof(int) * 5);

	for (int i = 0; i < 5; i++)
		coefficients[i] = 0;

    int isMinus     = -1;
    int coefficient = -1;
    int tmp         = 0;
    
    for (int i = 0; i < eq.length(&eq); i++) {
        char c = eq.at(&eq, i);

        if ('0' <= c && c <= '9') {
            tmp *= 10;
            tmp += c - '0';
        } else if (c == 'x') {
            if (eq.at(&eq, i + 1) == '^') {
                coefficient = eq.at(&eq, i + 2) - '0';
                i += 2;
            } else {
                coefficient = 1;
            }
        } else if (c == '+' || c == '-') {
            if (i != 0) {
                coefficients[coefficient] = (tmp == 0 ? 1 : tmp) * (isMinus == 1 ? -1 : 1);
                coefficient = -1;
                tmp = 0;
            }

            isMinus = c == '-';
        } else if (c == '=') {
            coefficients[coefficient == -1 ? 0 : coefficient] = (tmp == 0 ? 1 : tmp) * (isMinus == 1 ? -1 : 1);
            break;
        }
    }

    return coefficients;
}

int getDegreeFromCoefficients(const int *coefficients) {
    int degree = 0;

    for (int i = 4; i >= 0; i--)
        if (coefficients[i] != 0) {
            degree = i;
            break;
        }

    return degree;
}

String coefficientsToString(const int *coefficients) {
    char *result = (char *) malloc(sizeof(char) * 50);
	
	strcpy(result, "");

    int degree = getDegreeFromCoefficients(coefficients);

    for (int i = degree; i >= 0; i--) {
        int coefficient = coefficients[i];
        
        if (coefficient == 0) continue;

        char *tmp1 = (char *) malloc(sizeof(char) * 10);
        
        sprintf(tmp1, "%d", coefficient >= 0 ? coefficient : -coefficient);
        
        strcat(result, i == degree ? "" : (coefficient > 0 ? "+" : "-"));
        strcat(result, coefficient == 1 ? (i == 0 ? tmp1 : "") : tmp1);
        strcat(result, i > 0 ? "x" : "");
        strcat(result, i == 2 ? "©÷" : (i == 3 ? "©ø" : (i == 4 ? "©ù" : "")));

        free(tmp1);
    }

    strcat(result, "=0");

    return stringFrom(result);
}

#endif //_EQUATION_CALC_TYPE_EQUATION_HEADER_

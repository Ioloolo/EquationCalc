#ifndef _EQUATION_CALC_UTIL_INPUT_HEADER_
#define _EQUATION_CALC_UTIL_INPUT_HEADER_

#include <stdio.h>
#include "output.h"

// function list
String inputEquation();

// define function
String inputEquation() {
    String equation;

    char *tmp = malloc(sizeof(char) * 100);
    
    fgets(tmp, 100, stdin);

    equation = stringFrom(tmp);

    equation.removeSpace(&equation);
    equation.string[equation.length(&equation) - 1] = '\0';

    int isFindEqualSymbol = 0;
    for (int i = equation.length(&equation) - 1; i >= 0; i--)
        if (equation.at(&equation, i) == '=') {
            isFindEqualSymbol = 1;
            break;
        }
    if (isFindEqualSymbol == 0)
        printError(stringFrom("잘못된 수식입니다. ('=0' 꼴로 입력해주세요.)"));

    return equation;
}

#endif //_EQUATION_CALC_UTIL_INPUT_HEADER_

#ifndef _EQUATION_CALC_UTIL_OUTPUT_HEADER_
#define _EQUATION_CALC_UTIL_OUTPUT_HEADER_

#include <stdio.h>
#include "../type/solution.h"

// function list
void clearScreen    ();
void printCommonForm(String);
void printError     (String);
void printInputForm ();

// define function
void clearScreen() {
    for (int i = 0; i < 50; i++)
        printf("\n");
}

void printCommonForm(String equation) {
    clearScreen();

    printf("                        ┌─────────────────┐\n");
    printf("                        │  방정식 계산기  │\n");
    printf("   ┌────────────────────┴─────────────────┴────────────────────┐\n");
    printf("   │ 수식 : %-50s │\n", equation.string);
    printf("   └───────────────────────────────────────────────────────────┘\n");
}

void printError(String string) {
    clearScreen();

    printf("                      ┌─────────────────────────┐\n");
    printf("                      │   오류가 발생했습니다   │\n");
    printf("   =──────────────────┴─────────────────────────┴──────────────────=\n");
    printf("      %s", string.string);

    exit(0);
}

void printInputForm() {
    printCommonForm(stringFrom(""));

    printf("\n");
    printf("    $ 1차 방정식부터 4차 방정식까지 계산 가능합니다.\n");
    printf("    $ 다항식의 연산은 불가능하므로, 연산 후 입력해주세요.\n");
    printf("    $ 마지막은 '=0'을 입력해주세요.\n");
    printf("\n");

    printf("> 수식을 입력해주세요.  : ");
}

void printSolution(Solution solution) {
    printCommonForm(solution.equation.oe);
    printf("\n");
    printf("                        ┌───────────────────┐\n");
    printf("                        │  %d차 방정식 풀이  │\n", solution.equation.degree);
    printf("  =─────────────────────┴───────────────────┴─────────────────────=\n");

    for (int i = 1; i <= solution.step; i++) {
    	char *ptr = strtok(solution.solution[i].string, "$");
    	
    	printf("      #%02d. %s\n", i, ptr);
    
    	while ((ptr = strtok(NULL, "$")) != NULL) {
			printf("           %s\n", ptr);
    		ptr = strtok(NULL, "$");
		}
		
		printf("\n");
	}

    printf("\n");

    for (int i = 0; i < solution.nor; i++)
        printf("    ∴x(%d) = %s  ", i+1, solution.answer[i].string);

    printf("\n");
    printf("  =───────────────────────────────────────────────────────────────=\n");
}

#endif //_EQUATION_CALC_UTIL_OUTPUT_HEADER_

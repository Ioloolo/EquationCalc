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

    printf("                        ��������������������������������������\n");
    printf("                        ��  ������ ����  ��\n");
    printf("   ��������������������������������������������������������������������������������������������������������������������������\n");
    printf("   �� ���� : %-50s ��\n", equation.string);
    printf("   ��������������������������������������������������������������������������������������������������������������������������\n");
}

void printError(String string) {
    clearScreen();

    printf("                      ������������������������������������������������������\n");
    printf("                      ��   ������ �߻��߽��ϴ�   ��\n");
    printf("   =������������������������������������������������������������������������������������������������������������������������������=\n");
    printf("      %s", string.string);

    exit(0);
}

void printInputForm() {
    printCommonForm(stringFrom(""));

    printf("\n");
    printf("    $ 1�� �����ĺ��� 4�� �����ı��� ��� �����մϴ�.\n");
    printf("    $ ���׽��� ������ �Ұ����ϹǷ�, ���� �� �Է����ּ���.\n");
    printf("    $ �������� '=0'�� �Է����ּ���.\n");
    printf("\n");

    printf("> ������ �Է����ּ���.  : ");
}

void printSolution(Solution solution) {
    printCommonForm(solution.equation.oe);
    printf("\n");
    printf("                        ������������������������������������������\n");
    printf("                        ��  %d�� ������ Ǯ��  ��\n", solution.equation.degree);
    printf("  =������������������������������������������������������������������������������������������������������������������������������=\n");

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
        printf("    ��x(%d) = %s  ", i+1, solution.answer[i].string);

    printf("\n");
    printf("  =������������������������������������������������������������������������������������������������������������������������������=\n");
}

#endif //_EQUATION_CALC_UTIL_OUTPUT_HEADER_

#ifndef _EQUATION_CALC_UTIL_EQUATION_HEADER_
#define _EQUATION_CALC_UTIL_EQUATION_HEADER_

#include <math.h>
#include "../type/string.h"
#include "../type/equation.h"

// function list
String getDiscriminant     (Equation); 
int    getNumberOfRootsOf2d(Equation);

// define function
String getDiscriminant(Equation equation) {
	int  *coefficients = equation.coefficients;
	char *str          = (char *) malloc(sizeof(char) * 50);
	
	sprintf(str, "%d^2-4*%d*%d", coefficients[1], coefficients[0], coefficients[2]);
	
	return stringFrom(str);
}

int getNumberOfRootsOf2d(Equation equation) {
	int  *coefficients = equation.coefficients;
	
	int discriminant = pow(coefficients[1], 2) - 4*coefficients[0]*coefficients[2];
	
	if      (discriminant >  0) return 2;
	else if (discriminant == 0) return 1;
	else if (discriminant <  0) return 0;
	
	return 0;
}

int *divideRoot(int d) {
	static int result[] = {1, 0};
	int i = 1;
	int k = 2;
	int factorization[100] = {0,};
	int index[100] = {0};
		
	while (d != 1)
		if (d % k == 0) {
			factorization[index[i-1] != k ? index[i++]=k : k]++;
			d /= k;
		} else k++;
		
	for (int i = 1; i < 100; i++) {
		int idx = index[i];
			
		if (idx == 0) break;
			
		if (factorization[idx] > 1)
			result[0] *= idx * factorization[idx] / 2;
		else
			result[1] += idx;
	}
	
	return result;
}

int *dividePolynomial(int *coefficients, int r) {
	int p[4];
	int q[3];
	
	int *result = (int *) malloc(sizeof(int) * 5);
	
	for (int i = 0; i < 5; i++)
		result[i] = 0;
	
	for (int i = 0; i < 4; i++)
		p[i] = coefficients[3-i];

    q[0] = p[0];
    
    for (int i = 0; i < 3; i++)
        q[i] = (q[i-1]*r)+p[i];
    
    for (int i = 0; i < 3; i++)
    	result[i] = q[2-i];
        
    return result;
}

#endif //_EQUATION_CALC_UTIL_EQUATION_HEADER_

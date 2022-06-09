#ifndef _EQUATION_CALC_TYPE_SOLUTION_HEADER_
#define _EQUATION_CALC_TYPE_SOLUTION_HEADER_

#include <math.h>
#include "string.h"
#include "equation.h"
#include "../util/equation.h"

// define macro
#define Solution struct Solution

// define struct
Solution {
    // field
    Equation  equation;
    String   *solution;
    String   *answer;
    int       step;
    int       nor;

    // method
    void (*solve)(Solution *);
};

// constructor list
Solution solutionFrom(Equation);

// method list
void solve  (Solution *); // solve equation
void solve1D(Solution *); // solve equation of 1 degree
void solve2D(Solution *); // solve equation of 2 degree
void solve3D(Solution *); // solve equation of 3 degree
void solve4D(Solution *); // solve equation of 4 degree

// define constructor
Solution solutionFrom(Equation equation) {
    Solution solution;

    String *sol = (String *) malloc(sizeof(String) * 25);
    String *ans = (String *) malloc(sizeof(String) * 4);

	for (int i = 0; i < 4; i++)
		ans[i] = stringFrom("");

    solution.equation = equation;
    solution.solution = sol;
    solution.answer   = ans;
    solution.step     = 0;
    solution.nor      = 0;

    solution.solve    = solve;

    return solution;
}

// define method
void solve(Solution *this) {
    Equation equation = this->equation;

    switch (equation.degree) {
        case 1:
            solve1D(this);
            break;
        case 2:
            solve2D(this);
            break;
        case 3:
            solve3D(this);
            break;
        case 4:
            solve4D(this);
            break;
    }
}

void solve1D(Solution *this) {
    int  *coefficients = this->equation.coefficients;
    char *tmp          = (char *) malloc(sizeof(char) * 100);

    this->nor = 1;

	// ����� ���� 
    sprintf(tmp, "%dx=%d$�����(%d)�� �����ϼ���.",
            coefficients[1],
            -coefficients[0],
            coefficients[0]);
    this->solution[++(this->step)] = stringFrom(tmp);
    this->equation.right = -coefficients[0];
    coefficients[0] = 0;
    
    if ((float) this->equation.right/coefficients[1] == (int) this->equation.right/coefficients[1]) {
    	// �Ҽ����� ���� ���, �׳� ��� 
    	sprintf(tmp, "x=%g$�� ���� ������ ���(%d)�� �����ּ���.",
	    		(float) this->equation.right / coefficients[1],
	            coefficients[1]);
	    this->solution[++(this->step)] = stringFrom(tmp);
	    sprintf(tmp, "%g", (float) this->equation.right/coefficients[1]);
	} else { 
		// �Ҽ����� ���� ���, �м� ���·� ��� 
		sprintf(tmp, "x=%g/%d$�� ���� ������ ���(%d)�� �����ּ���.",
	    		this->equation.right,
				coefficients[1],
	            coefficients[1]);
	    this->solution[++(this->step)] = stringFrom(tmp);
		sprintf(tmp, "%g/%d", this->equation.right, coefficients[1]);
	}
    strcpy(this->answer[0].string, tmp);
}

void solve2D(Solution *this) {
	int  *coefficients = this->equation.coefficients;
    char *tmp          = (char *) malloc(sizeof(char) * 150);
    
    // �Ǻ��� ��� �� ���� ���� Ȯ��. 
    this->nor = getNumberOfRootsOf2d(this->equation);
    sprintf(tmp, "���� ���� = %d (��D=%s %c 0)$�Ǻ����� ����� ���� ������ ����մϴ�.",
			this->nor,
			getDiscriminant(this->equation).string,
			this->nor == 2 ? '>' : (this->nor == 1 ? '=' : '<'));
    this->solution[++(this->step)] = stringFrom(tmp);
    
    // 2���� ����� ������� , ����� 
	if (coefficients[2] < 0) {
		coefficients[2] *= -1; 
    	coefficients[1] *= -1;
    	coefficients[0] *= -1;
    	this->equation.refreshEquationString(&this->equation);
    	sprintf(tmp, "%s$2�� �׿� -1�� �����ּ���.",
			this->equation.equation.string);
		this->solution[++(this->step)] = stringFrom(tmp);
	}
    
    // 2���� ����� 1�� �ƴϰ�, 2���� ����� ���� �� �ִٸ� ����. 
    if (coefficients[2] != 1) {
    	if ((float) coefficients[1] / coefficients[2] - coefficients[1] / coefficients[2] == 0 &&
			(float) coefficients[0] / coefficients[2] - coefficients[0] / coefficients[2] == 0) {
				int o2d = coefficients[2];
    			coefficients[1] /= coefficients[2];
    			coefficients[0] /= coefficients[2];
    			coefficients[2] = 1;
    			this->equation.refreshEquationString(&this->equation);
    			sprintf(tmp, "%s$2������ ���(%d)�� �� �׿� �����ּ���.",
					this->equation.equation.string,
					o2d);
				this->solution[++(this->step)] = stringFrom(tmp);
			}
	}
	
    if (this->nor == 2) {
    	if (coefficients[1] == 0 && coefficients[0] < 0) {
    		// �μ����� : �������� 
    		 if (coefficients[2] == 1) {
    		 	if (sqrt(abs(coefficients[0])) - (int) sqrt(abs(coefficients[0])) == 0) {
    		 		sprintf(tmp, "(x+%d)(x-%d)=0$���� ������ ����Ͽ� �μ������մϴ�.",
							(int) sqrt(abs(coefficients[0])),
							(int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[0].string, "%d", (int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[1].string, "-%d", (int) sqrt(abs(coefficients[0])));
				} else {
					sprintf(tmp, "(x+��%d)(x-��%d)=0$���� ������ ����Ͽ� �μ������մϴ�.",
							abs(coefficients[0]),
							abs(coefficients[0]));
					sprintf(this->answer[0].string, "��%d", abs(coefficients[0]));
					sprintf(this->answer[1].string, "-��%d", abs(coefficients[0]));
				}
			 } else {
			 	if (sqrt(abs(coefficients[0])) - (int) sqrt(abs(coefficients[0])) == 0) {
    		 		sprintf(tmp, "(x+(%d/2))(x-(%d/2))=0$���� ������ ����Ͽ� �μ������մϴ�.",
							(int) sqrt(abs(coefficients[0])),
							(int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[0].string, "%d/2", (int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[1].string, "-(%d/2)", (int) sqrt(abs(coefficients[0])));
				} else {
					sprintf(tmp, "(x+(��%d/2))(x-(��%d/2))=0$���� ������ ����Ͽ� �μ������մϴ�.",
							abs(coefficients[0]),
							abs(coefficients[0]));
					sprintf(this->answer[0].string, "��%d/2", abs(coefficients[0]));
					sprintf(this->answer[1].string, "-(��%d/2)", abs(coefficients[0]));
				}
			 }
			 
			 this->solution[++(this->step)] = stringFrom(tmp);
		} else {
			// �μ� ���� ���� ����..? 
		}
	} else if (this->nor == 1) {
    	int half = coefficients[1] / 2;
    		
    	sprintf(tmp, "%d%s%d$1���� ����� ������ ������ ����װ� ������ Ȯ���մϴ�.",
				half*half,
				half*half == coefficients[0] ? "=" : "��",
				coefficients[0]);
		this->solution[++(this->step)] = stringFrom(tmp);
	
		if (half*half != coefficients[0]) {
			sprintf(tmp, "�߸��� �������Դϴ�.");
			this->solution[++(this->step)] = stringFrom(tmp);
			return;
		}
		
		sprintf(tmp, "(x%c%d)��=0$���� ������ ���·� �μ������մϴ�.",
				coefficients[1]/2 > 0 ? '+' : '-',
				abs(coefficients[1]/2));
		this->solution[++(this->step)] = stringFrom(tmp);
		
		sprintf(this->answer[0].string, "%d", -(coefficients[1]/2));
	} else if (this->nor == 0) {
		// �Ǻ����� ����. (���� ���� ��� ����) 
		int *d = divideRoot(abs(pow(coefficients[1], 2) - 4*coefficients[2]*coefficients[0]));
		
		sprintf(tmp, "���� ������ ����Ͽ� �ظ� ���մϴ�.");
		this->solution[++(this->step)] = stringFrom(tmp);
		
		// �и�(2)�� �����ٸ� ������, ��Ʈ �� ����� 1�̶�� �����Ͽ� ���� 
		if (d[0] > 1) {
			if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[0]/2.0 - d[0]/2 == 0) {
				if (d[0]/2 > 1) {
					sprintf(this->answer[0].string, "%d+%d��%di", -coefficients[1]/2, d[0]/2, d[1]);
					sprintf(this->answer[1].string, "%d-%d��%di", -coefficients[1]/2, d[0]/2, d[1]);
				} else {
					sprintf(this->answer[0].string, "%d+��%di", -coefficients[1]/2, d[1]);
					sprintf(this->answer[1].string, "%d-��%di", -coefficients[1]/2, d[1]);
				}
			} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
				sprintf(this->answer[0].string, "%d+((%d��%di)/2)", -coefficients[1]/2, d[0], d[1]);
				sprintf(this->answer[1].string, "%d-((%d��%di)/2)", -coefficients[1]/2, d[0], d[1]);
			} else if (d[0]/2.0 - d[0]/2 == 0) {
				if (d[0]/2 > 1) {
					sprintf(this->answer[0].string, "(%d/2)+%d��%di", -coefficients[1], d[0]/2, d[1]);
					sprintf(this->answer[1].string, "(%d/2)-%d��%di", -coefficients[1], d[0]/2, d[1]);
				} else {
					sprintf(this->answer[0].string, "(%d/2)+��%di", -coefficients[1], d[1]);
					sprintf(this->answer[1].string, "(%d/2)-��%di", -coefficients[1], d[1]);
				}
			} else {
				sprintf(this->answer[0].string, "(%d+%d��%di)/2", -coefficients[1], d[0], d[1]);
				sprintf(this->answer[1].string, "(%d-%d��%di)/2", -coefficients[1], d[0], d[1]);
			}
		} else {
			if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[1]/4.0 - d[1]/4 == 0) {
				sprintf(this->answer[0].string, "%d+��%di", -coefficients[1]/2, d[1]/4);
				sprintf(this->answer[1].string, "%d-��%di", -coefficients[1]/2, d[1]/4);
			} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
				sprintf(this->answer[0].string, "%d+((��%di)/2)", -coefficients[1]/2, d[1]);
				sprintf(this->answer[1].string, "%d-((��%di)/2)", -coefficients[1]/2, d[1]);
			} else if (d[0]/2.0 - d[0]/2 == 0) {
				sprintf(this->answer[0].string, "(%d/2)+��%di", -coefficients[1], d[1]/4);
				sprintf(this->answer[1].string, "(%d/2)-��%di", -coefficients[1], d[1]/4);
			} else {
				sprintf(this->answer[0].string, "(%d+��%di)/2", -coefficients[1], d[1]);
				sprintf(this->answer[1].string, "(%d-��%di)/2", -coefficients[1], d[1]);
			}
		}
		
		this->nor = 2;
	}
}

void solve3D(Solution *this) {
}

void solve4D(Solution *this) {
}

#endif //_EQUATION_CALC_TYPE_SOLUTION_HEADER_

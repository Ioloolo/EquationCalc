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
    }
}

void solve1D(Solution *this) {
    int  *coefficients = this->equation.coefficients;
    char *tmp          = (char *) malloc(sizeof(char) * 100);

    this->nor = 1;

	// 상수항 이항 
    sprintf(tmp, "%dx=%d$상수항(%d)을 이항하세요.",
            coefficients[1],
            -coefficients[0],
            coefficients[0]);
    this->solution[++(this->step)] = stringFrom(tmp);
    this->equation.right = -coefficients[0];
    coefficients[0] = 0;
    
    if ((float) this->equation.right/coefficients[1] == (int) this->equation.right/coefficients[1]) {
    	// 소숫점이 없을 경우, 그냥 출력 
    	sprintf(tmp, "x=%g$각 항을 일차항 계수(%d)로 나눠주세요.",
	    		(float) this->equation.right / coefficients[1],
	            coefficients[1]);
	    this->solution[++(this->step)] = stringFrom(tmp);
	    sprintf(tmp, "%g", (float) this->equation.right/coefficients[1]);
	} else { 
		// 소숫점이 있을 경우, 분수 형태로 출력 
		sprintf(tmp, "x=%g/%d$각 항을 일차항 계수(%d)로 나눠주세요.",
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
    
    // 판별식 사용 후 근의 개수 확인. 
    this->nor = getNumberOfRootsOf2d(this->equation);
    sprintf(tmp, "근의 개수 = %d (∵D=%s %c 0)$판별식을 사용해 해의 개수를 계산합니다.",
			this->nor,
			getDiscriminant(this->equation).string,
			this->nor == 2 ? '>' : (this->nor == 1 ? '=' : '<'));
    this->solution[++(this->step)] = stringFrom(tmp);
    
    // 2차항 계수가 음수라면 , 양수로 
	if (coefficients[2] < 0) {
		coefficients[2] *= -1; 
    	coefficients[1] *= -1;
    	coefficients[0] *= -1;
    	this->equation.refreshEquationString(&this->equation);
    	sprintf(tmp, "%s$각 항에 -1을 곱해주세요.",
			this->equation.equation.string);
		this->solution[++(this->step)] = stringFrom(tmp);
	}
    
    // 2차항 계수가 1이 아니고, 2차항 계수로 나눌 수 있다면 나눔. 
    if (coefficients[2] != 1) {
    	if ((float) coefficients[1] / coefficients[2] - coefficients[1] / coefficients[2] == 0 &&
			(float) coefficients[0] / coefficients[2] - coefficients[0] / coefficients[2] == 0) {
				int o2d = coefficients[2];
    			coefficients[1] /= coefficients[2];
    			coefficients[0] /= coefficients[2];
    			coefficients[2] = 1;
    			this->equation.refreshEquationString(&this->equation);
    			sprintf(tmp, "%s$2차항의 계수(%d)를 각 항에 나눠주세요.",
					this->equation.equation.string,
					o2d);
				this->solution[++(this->step)] = stringFrom(tmp);
			}
	}
	
    if (this->nor == 2) {
    	if (coefficients[1] == 0 && coefficients[0] < 0) {
    		// 인수분해 : 합차공식 
    		 if (coefficients[2] == 1) {
    		 	if (sqrt(abs(coefficients[0])) - (int) sqrt(abs(coefficients[0])) == 0) {
    		 		sprintf(tmp, "(x+%d)(x-%d)=0$합차 공식을 사용하여 인수분해합니다.",
							(int) sqrt(abs(coefficients[0])),
							(int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[0].string, "%d", (int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[1].string, "-%d", (int) sqrt(abs(coefficients[0])));
				} else {
					sprintf(tmp, "(x+√%d)(x-√%d)=0$합차 공식을 사용하여 인수분해합니다.",
							abs(coefficients[0]),
							abs(coefficients[0]));
					sprintf(this->answer[0].string, "√%d", abs(coefficients[0]));
					sprintf(this->answer[1].string, "-√%d", abs(coefficients[0]));
				}
			 } else {
			 	if (sqrt(abs(coefficients[0])) - (int) sqrt(abs(coefficients[0])) == 0) {
    		 		sprintf(tmp, "(x+(%d/2))(x-(%d/2))=0$합차 공식을 사용하여 인수분해합니다.",
							(int) sqrt(abs(coefficients[0])),
							(int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[0].string, "%d/2", (int) sqrt(abs(coefficients[0])));
					sprintf(this->answer[1].string, "-(%d/2)", (int) sqrt(abs(coefficients[0])));
				} else {
					sprintf(tmp, "(x+(√%d/2))(x-(√%d/2))=0$합차 공식을 사용하여 인수분해합니다.",
							abs(coefficients[0]),
							abs(coefficients[0]));
					sprintf(this->answer[0].string, "√%d/2", abs(coefficients[0]));
					sprintf(this->answer[1].string, "-(√%d/2)", abs(coefficients[0]));
				}
			 }
			 
			 this->solution[++(this->step)] = stringFrom(tmp);
		} else {
			double alpha = (-coefficients[1] + sqrt(pow(coefficients[1], 2) - 4*coefficients[2]*coefficients[0])) / (2 * coefficients[2]);
			double beta = (-coefficients[1] - sqrt(pow(coefficients[1], 2) - 4*coefficients[2]*coefficients[0])) / (2 * coefficients[2]);
			
			if (alpha - (int) alpha == 0 && beta - (int) beta == 0) {
				sprintf(tmp, "(x%c%d)(x%c%d)=0$인수분해를 합니다.",
						alpha > 0 ? '-' : '+', abs(alpha),
						beta > 0 ? '-' : '+', abs(beta));
				this->solution[++(this->step)] = stringFrom(tmp);
				
				sprintf(this->answer[0].string, "%d", (int) alpha);
				sprintf(this->answer[1].string, "%d", (int) beta);
			} else {
				int *d = divideRoot(abs(pow(coefficients[1], 2) - 4*coefficients[2]*coefficients[0]));
		
				sprintf(tmp, "근의 공식을 사용하여 해를 구합니다.");
				this->solution[++(this->step)] = stringFrom(tmp);
				
				// 분모(2)로 나뉜다면 나누고, 루트 앞 계수가 1이라면 생략하여 저장 
				if (d[0] > 1) {
					if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[0]/2.0 - d[0]/2 == 0) {
						if (d[0]/2 > 1) {
							sprintf(this->answer[0].string, "%d+%d√%d", -coefficients[1]/2, d[0]/2, d[1]);
							sprintf(this->answer[1].string, "%d-%d√%d", -coefficients[1]/2, d[0]/2, d[1]);
						} else {
							sprintf(this->answer[0].string, "%d+√%d", -coefficients[1]/2, d[1]);
							sprintf(this->answer[1].string, "%d-√%d", -coefficients[1]/2, d[1]);
						}
					} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
						sprintf(this->answer[0].string, "%d+((%d√%d)/2)", -coefficients[1]/2, d[0], d[1]);
						sprintf(this->answer[1].string, "%d-((%d√%d)/2)", -coefficients[1]/2, d[0], d[1]);
					} else if (d[0]/2.0 - d[0]/2 == 0) {
						if (d[0]/2 > 1) {
							sprintf(this->answer[0].string, "(%d/2)+%d√%d", -coefficients[1], d[0]/2, d[1]);
							sprintf(this->answer[1].string, "(%d/2)-%d√%d", -coefficients[1], d[0]/2, d[1]);
						} else {
							sprintf(this->answer[0].string, "(%d/2)+√%d", -coefficients[1], d[1]);
							sprintf(this->answer[1].string, "(%d/2)-√%d", -coefficients[1], d[1]);
						}
					} else {
						sprintf(this->answer[0].string, "(%d+%d√%d)/2", -coefficients[1], d[0], d[1]);
						sprintf(this->answer[1].string, "(%d-%d√%d)/2", -coefficients[1], d[0], d[1]);
					}
				} else {
					if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[1]/4.0 - d[1]/4 == 0) {
						sprintf(this->answer[0].string, "%d+√%d", -coefficients[1]/2, d[1]/4);
						sprintf(this->answer[1].string, "%d-√%d", -coefficients[1]/2, d[1]/4);
					} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
						sprintf(this->answer[0].string, "%d+((√%d)/2)", -coefficients[1]/2, d[1]);
						sprintf(this->answer[1].string, "%d-((√%d)/2)", -coefficients[1]/2, d[1]);
					} else if (d[0]/2.0 - d[0]/2 == 0) {
						sprintf(this->answer[0].string, "(%d/2)+√%d", -coefficients[1], d[1]/4);
						sprintf(this->answer[1].string, "(%d/2)-√%d", -coefficients[1], d[1]/4);
					} else {
						sprintf(this->answer[0].string, "(%d+√%d)/2", -coefficients[1], d[1]);
						sprintf(this->answer[1].string, "(%d-√%d)/2", -coefficients[1], d[1]);
					}
				}
			}
		}
	} else if (this->nor == 1) {
    	int half = coefficients[1] / 2;
    		
    	sprintf(tmp, "%d%s%d$1차항 계수의 절반의 제곱이 상수항과 같은지 확인합니다.",
				half*half,
				half*half == coefficients[0] ? "=" : "≠",
				coefficients[0]);
		this->solution[++(this->step)] = stringFrom(tmp);
	
		if (half*half != coefficients[0]) {
			sprintf(tmp, "잘못된 방정식입니다.");
			this->solution[++(this->step)] = stringFrom(tmp);
			return;
		}
		
		sprintf(tmp, "(x%c%d)²=0$완전 제곱식 형태로 인수분해합니다.",
				coefficients[1]/2 > 0 ? '+' : '-',
				abs(coefficients[1]/2));
		this->solution[++(this->step)] = stringFrom(tmp);
		
		sprintf(this->answer[0].string, "%d", -(coefficients[1]/2));
	} else if (this->nor == 0) {
		// 판별식을 구함. (근의 공식 사용 목적) 
		int *d = divideRoot(abs(pow(coefficients[1], 2) - 4*coefficients[2]*coefficients[0]));
		
		sprintf(tmp, "근의 공식을 사용하여 해를 구합니다.");
		this->solution[++(this->step)] = stringFrom(tmp);
		
		// 분모(2)로 나뉜다면 나누고, 루트 앞 계수가 1이라면 생략하여 저장
		if (d[1] == 0) {
			if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[0]/2.0 - d[0]/2 == 0) {
				sprintf(this->answer[0].string, "%d+%di", -coefficients[1]/2, d[0]/2);
				sprintf(this->answer[1].string, "%d-%di", -coefficients[1]/2, d[0]/2);
			} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
				sprintf(this->answer[0].string, "%d+((%di)/2)", -coefficients[1]/2, d[0]);
				sprintf(this->answer[1].string, "%d-((%di)/2)", -coefficients[1]/2, d[0]);
			} else if (d[0]/2.0 - d[0]/2 == 0) {
				sprintf(this->answer[0].string, "(%d/2)+%di", -coefficients[1], d[0]/2);
				sprintf(this->answer[1].string, "(%d/2)-%di", -coefficients[1], d[0]/2);
			} else {
				sprintf(this->answer[0].string, "(%d+%di)/2", -coefficients[1], d[0]);
				sprintf(this->answer[1].string, "(%d-%di)/2", -coefficients[1], d[0]);
			}
		} else {
			if (d[0] > 1) {
				if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[0]/2.0 - d[0]/2 == 0) {
					if (d[0]/2 > 1) {
						sprintf(this->answer[0].string, "%d+%d√%di", -coefficients[1]/2, d[0]/2, d[1]);
						sprintf(this->answer[1].string, "%d-%d√%di", -coefficients[1]/2, d[0]/2, d[1]);
					} else {
						sprintf(this->answer[0].string, "%d+√%di", -coefficients[1]/2, d[1]);
						sprintf(this->answer[1].string, "%d-√%di", -coefficients[1]/2, d[1]);
					}
				} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
					sprintf(this->answer[0].string, "%d+((%d√%di)/2)", -coefficients[1]/2, d[0], d[1]);
					sprintf(this->answer[1].string, "%d-((%d√%di)/2)", -coefficients[1]/2, d[0], d[1]);
				} else if (d[0]/2.0 - d[0]/2 == 0) {
					if (d[0]/2 > 1) {
						sprintf(this->answer[0].string, "(%d/2)+%d√%di", -coefficients[1], d[0]/2, d[1]);
						sprintf(this->answer[1].string, "(%d/2)-%d√%di", -coefficients[1], d[0]/2, d[1]);
					} else {
						sprintf(this->answer[0].string, "(%d/2)+√%di", -coefficients[1], d[1]);
						sprintf(this->answer[1].string, "(%d/2)-√%di", -coefficients[1], d[1]);
					}
				} else {
					sprintf(this->answer[0].string, "(%d+%d√%di)/2", -coefficients[1], d[0], d[1]);
					sprintf(this->answer[1].string, "(%d-%d√%di)/2", -coefficients[1], d[0], d[1]);
				}
			} else {
				if (coefficients[1]/2.0 - coefficients[1]/2 == 0 && d[1]/4.0 - d[1]/4 == 0) {
					sprintf(this->answer[0].string, "%d+√%di", -coefficients[1]/2, d[1]/4);
					sprintf(this->answer[1].string, "%d-√%di", -coefficients[1]/2, d[1]/4);
				} else if (coefficients[1]/2.0 - coefficients[1]/2 == 0) {
					sprintf(this->answer[0].string, "%d+((√%di)/2)", -coefficients[1]/2, d[1]);
					sprintf(this->answer[1].string, "%d-((√%di)/2)", -coefficients[1]/2, d[1]);
				} else if (d[0]/2.0 - d[0]/2 == 0) {
					sprintf(this->answer[0].string, "(%d/2)+√%di", -coefficients[1], d[1]/4);
					sprintf(this->answer[1].string, "(%d/2)-√%di", -coefficients[1], d[1]/4);
				} else {
					sprintf(this->answer[0].string, "(%d+√%di)/2", -coefficients[1], d[1]);
					sprintf(this->answer[1].string, "(%d-√%di)/2", -coefficients[1], d[1]);
				}
			}
		}
		
		this->nor = 2;
	}
}

void solve3D(Solution *this) {
	int  *coefficients = this->equation.coefficients;
    char *tmp          = (char *) malloc(sizeof(char) * 150);
    
	int alpha = 99;
	int a[4]  = {coefficients[3],};
	
	// 3차항 계수가 음수라면 , 양수로 
	if (coefficients[3] < 0) {
		coefficients[3] *= -1; 
    	coefficients[2] *= -1;
    	coefficients[1] *= -1;
    	coefficients[0] *= -1;
    	this->equation.refreshEquationString(&this->equation);
    	sprintf(tmp, "%s$각 항에 -1을 곱해주세요.",
			this->equation.equation.string);
		this->solution[++(this->step)] = stringFrom(tmp);
	}
    
    // 3차항 계수가 1이 아니고, 3차항 계수로 나눌 수 있다면 나눔. 
    if (coefficients[3] != 1) {
    	if ((float) coefficients[2] / coefficients[3] - coefficients[2] / coefficients[3] == 0 &&
			(float) coefficients[1] / coefficients[3] - coefficients[1] / coefficients[3] == 0 &&
			(float) coefficients[0] / coefficients[3] - coefficients[0] / coefficients[3] == 0) {
				int o3d = coefficients[3];
				coefficients[2] /= coefficients[3];
    			coefficients[1] /= coefficients[3];
    			coefficients[0] /= coefficients[3];
    			coefficients[3] = 1;
    			this->equation.refreshEquationString(&this->equation);
    			sprintf(tmp, "%s$3차항의 계수(%d)를 각 항에 나눠주세요.",
					this->equation.equation.string,
					o3d);
				this->solution[++(this->step)] = stringFrom(tmp);
		}
	}
	
	// 인수 찾기 
	for (int i = -15; i <= 15; i++) {
		if (i == 0) continue;
		
		printf("%d ", i);
		
		if (coefficients[3]*pow(i, 3) + coefficients[2]*pow(i, 2) + coefficients[1]*i + coefficients[0] == 0) {
			alpha = i;
			break;
		}
	}
	
	if (alpha != 99) {
		// 0이 되는 값 발견 시 조립제법 사용 
		sprintf(tmp, "%d%c%d%c%d%c%d=0 (x=%d)$식이 0이 되는 값을 찾습니다.",
				(int) coefficients[3]*pow(alpha, 3),
				coefficients[2]*pow(alpha, 2) >= 0 ? '+' : '-', abs(coefficients[2]*pow(alpha, 2)),
				coefficients[1]*alpha >= 0 ? '+' : '-', abs(coefficients[1]*alpha),
				coefficients[0]*alpha >= 0 ? '+' : '-', abs(coefficients[0]*alpha),
				alpha);
		this->solution[++(this->step)] = stringFrom(tmp);
		
		// 인수 분해 
		Equation newEq = equationFromCoefficients(dividePolynomial(coefficients, alpha));
		
		sprintf(tmp, "(x%c%d)(%s)=0",
				alpha > 0 ? '-' : '+', abs(alpha), strtok(newEq.equation.string, "="));
		this->solution[++(this->step)] = stringFrom(tmp);
		
		// 2차 방정식 풀이
		sprintf(tmp, "이차 방정식 %s 의 근을 구합니다.",
				newEq.equation.string);
		this->solution[++(this->step)] = stringFrom(tmp);
		
		Solution solution = solutionFrom(newEq);
	    solution.solve(&solution);
	    
	    for (int i = 1; i <= solution.step; i++)
	    	this->solution[++(this->step)] = stringFrom(solution.solution[i].string);
	    	
		sprintf(this->answer[0].string, "%d", alpha);
		this->answer[1] = solution.answer[0];
		this->answer[2] = solution.answer[1];
		
		this->nor = 3;
	} else {
		sprintf(tmp, "근을 찾을 수 없습니다.");
		this->solution[++(this->step)] = stringFrom(tmp);
		
		this->nor = 0; 
	}
}

#endif //_EQUATION_CALC_TYPE_SOLUTION_HEADER_

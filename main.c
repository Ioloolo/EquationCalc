#include "type/solution.h"
#include "type/string.h"
#include "type/equation.h"
#include "util/input.h"
#include "util/output.h"

int main(int argc, char *argv[]) {
    printInputForm();

    String   str = inputEquation();    
    Equation eq  = equationFromString(str);
    Solution sol = solutionFrom(eq);

    sol.solve(&sol);

    printSolution(sol);

	return 0;
}

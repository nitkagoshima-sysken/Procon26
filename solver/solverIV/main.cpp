#include "solverIV.hpp"
#include "../../procon26_modio.hpp"

int main()
{
    // read Problem
    string filePath;
    cin >> filePath;
    Problem prob = *readProblem(filePath);

    cin >> SolverIV::limitDepth;
    cin >> SolverIV::limitNumber;
    Answers *ans = SolverIV::solve(prob);

    // output Answers
    ans->print(cout);

    return 0;
}

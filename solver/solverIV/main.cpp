#include "solverIV.hpp"
#include "../../procon26_modio.hpp"

int main()
{
    // read Problem
    string filePath;
    cin >> filePath;
    Problem prob = *readProblem(filePath);

    cin >> SolverIV::scoreFunction;

    cin >> SolverIV::limitDepth;
    cin >> SolverIV::limitNumber;
    cin >> SolverIV::planMax;
    SolverIV::solve(prob);

    return 0;
}

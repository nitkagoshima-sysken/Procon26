#include <iostream>
#include "GA.hpp"
#include "../../procon26_modio.hpp"
#include "../../procon26_module.hpp"

int main() {
	int gene = 5, step = 10;
	string pass;
	cin >> pass;
	//cin >> gene;
	//cin >> step;
	Problem* problem = readProblem(pass);
	SubmissionManager sm("answerGA");

        PutStone put = PutStone(problem);
        Answers* answers = new Answers(problem->num);
        GA ga(gene, put);
        for (int i = 0; i < step; i++) {
            // cout << "step " << ga.getMaxPoint() << endl;
            ga.step();
            if(ga.isEnd()) break;
        }
        cout << endl;
        cout <<  (1024 - ga.getMaxPoint()) << " ";
        vector<bool> tmp = ga.getResult();
        put.putStone(&tmp, answers, true);
        cout << sm.submit(answers) << endl;

        return 0;
}                          

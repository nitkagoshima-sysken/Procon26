#include <iostream>
#include "GA.hpp"
#include "../../procon26_modio.hpp"
#include "../../procon26_module.hpp"

int main() {
	int gene, step;
	string pass;
	cin >> pass;
	cin >> gene;
	cin >> step;
	Problem* problem = readProblem(pass);
	PutStone put = PutStone(problem);
        Answers* answers = new Answers(problem->num);
	GA ga(gene, put);
	for (int i = 0; i < step; i++) {
		cout << "step " << ga.getMaxPoint() << endl;
		ga.step();
		if(ga.isEnd()) break;
	}
	cout << endl;
	cout << ga.getMaxPoint() << endl;
	vector<bool> tmp = ga.getResult();
	put.putStone(&tmp, answers, true);
	SubmissionManager sm("answerGA");
	sm.submit(answers);
	return 0;
}

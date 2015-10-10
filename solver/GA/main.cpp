#include <iostream>
#include "GA.hpp"
#include "../../procon26_modio.hpp"

int main() {
	int gene, step;
	string pass;
	cin >> pass;
	cin >> gene;
	cin >> step;
	Problem* problem = readProblem(pass);
	PutStone put = PutStone(problem);
	GA ga(gene, put);
	for (int i = 0; i < step; i++) {
		cout << "step " << ga.getMaxPoint() << endl;
		ga.step();
		if(ga.isEnd()) break;
	}
	cout << endl;
	cout << ga.getMaxPoint() << endl;
	put.putStone(&ga.getResult(), nullptr, true);
	system("pause");
	return 0;
}
#pragma once

#include "../../procon26_modlib.hpp"

typedef vector<bool> Gene;

struct PutStone {
	Problem* problem;
	Board* board;
	int bp;

	PutStone() : problem(new Problem()) {};

	PutStone(Problem* prob);

	int putStone(Gene*, Answers* = nullptr, bool = false);

	PutStone(const PutStone& obj) {
		problem = new Problem();
		problem->board = *cloneBoard(&obj.problem->board);
		problem->num = obj.problem->num;
		problem->stones = new Stone[problem->num];
		for (int i = 0; i < problem->num; i++) {
			problem->stones[i] = *cloneStone(&obj.problem->stones[i]);
		}
		board = cloneBoard(obj.board);
		bp = obj.bp;
	}

	~PutStone() {
		delete[] problem->stones;
		delete problem;
		delete board;
	}
};
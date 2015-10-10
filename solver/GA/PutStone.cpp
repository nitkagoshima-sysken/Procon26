#include "PutStone.hpp"
#include "../../procon26_modio.hpp"

#define NULL_POINT -64

PutStone::PutStone(Problem* prob) : problem(prob) {
	int point;
	vector<Board*> boards;
	getGroupsBoard(&problem->board, false, boards, &point, &point);
	point = 0;

	board = nullptr;
	for (auto b : boards) {
		int temp = countBitOfBoard(b);
		if (point < temp) {
			point = temp;
			if (board != nullptr) {
				delete board;
			}
			board = cloneBoard(b);
		}
	}
	releaseVector(boards);
	for (int i = 0; i < BOARD_LOOP; i++) {
		board->block[i] = ~board->block[i];
	}

	boards.clear();
}

int PutStone::putStone(Gene* gene, Answers* answers, bool flag) {
	int point;
	Board* board_diff = new Board(), *board = cloneBoard(this->board);
	static const auto toAnswer = [](int x, int y, bool flipped, int turn) -> Answer {
		Answer result;
		result.X = x;
		result.Y = y;
		result.flipped = flipped;
		result.turn = turn;
		return result;
	};

	bool placed = true;

	for (int i = 0; i < problem->num; i++) {
		int X, Y;
		point = 0;
		X = Y = NULL_POINT;
		State result;
		result.flipped = false;
		result.turn = 0;
		if (gene->at(i)) {
			vector<State*> stones;
			getStatesOfStone(&problem->stones[i], stones);
			for (auto stone : stones) {
				for (int y = 1 - STONE_SIZE; y < BOARD_SIZE; y++) {
					for (int x = 1 - STONE_SIZE; x < BOARD_SIZE; x++) {
						if (canPlace(board, board_diff, stone, x, y, placed)) {
							int temp = (placed)? 0 : checkPlacingStone(board, board_diff, stone, x, y);
							if (temp > point || placed) {
								point = temp;
								X = x;
								Y = y;
								result = *stone;
								if (placed) {
									goto FIRST;
								}
							}
						}
					}
				}
			}
		FIRST:
			releaseVector(stones);
			stones.clear();
			if (X == NULL_POINT && Y == NULL_POINT) {
				gene->at(i) = false;
			}
			else {
				Board *tmp;
				tmp      = placeStone(board     , &result, X, Y);
				delete board; board = tmp;
				tmp = placeStone(board_diff, &result, X, Y);
				delete board_diff; board_diff = tmp;
			}
		}
		if (answers) {
			if(!(X == NULL_POINT && Y == NULL_POINT))
				answers->answers.push_back(toAnswer(X, Y, result.flipped, result.turn));
		}
		if (placed && gene->at(i)) placed = false;
	}
	point = countBitOfBoard(board);
	if (flag) {
		showBoard(board);
//		cout << endl;
//		showBoard(board_diff);
		if(answers) point = countScore(*answers, *problem);
		else point = countBitOfBoard(board_diff) + bp;
	}
	delete board_diff;
	delete board;
	return point;
}
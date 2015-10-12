#include <iostream>
#include <fstream>
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"
#include "../procon26_module.hpp"

using namespace std;

struct Placement {
    int x; int y; bool flipped; int rotate; int count; int touching; int passes;
    Placement(int x, int y, bool flipped, int rotate, int count, int touching, int passes) {
        this->x = x;
        this->y = y;
        this->flipped = flipped;
        this->rotate = rotate;
        this->count = count;
        this->touching = touching;
        this->passes = passes;
    }
    bool operator<(const Placement& right) const
    {
        if (count < right.count) return true;
        if (count > right.count) return false;
        if (touching > right.touching) return true;
        if (touching < right.touching) return false;
        if (passes < right.passes) return true;
        if (passes > right.passes) return false;
        return true;
    }
};

std::vector<Placement *> *solve(Board *masterBoard, Board *stonesBoard, std::vector<std::vector<State *> > states, int depth, int remain, int passes);

int main() {
    Board *masterBoard;		// 現在のボードの状態を保持
    Board *stonesBoard = cloneBoard(EMPTY_BOARD);	// 今までに置いた石だけを保持
    SubmissionManager sm("rs");

    // 問題読み込み
    string filePath;
    cin >> filePath;
    Problem *prob = readProblem(filePath);
    Answers answer(prob->num);
    masterBoard = cloneBoard(&prob->board);

    std::vector<std::vector<State *> > states;
    convertStonesToVectorOfStates(prob->stones, prob->num, states);

    int depth = 0;

}

std::vector<Placement *> *solve(Board *masterBoard, Board *stonesBoard, std::vector<std::vector<State *> > states, int depth, int remain, int passes) {
    std::vector<Placement *> places;
    for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++) {
        for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++) {
            for (int i = 0; i < states[depth].size(); i ++) {
                if (canPlace(masterBoard, stonesBoard, states[depth][i], x, y, depth == 0)) {
                    Stone *stonetmp = getTouchingStone(masterBoard, states[depth][i], x, y, true);
                    int touching = countBitOfStone(stonetmp); 
                    Board *masterTmp = placeStone(masterBoard, states[depth][i], x, y); 
                    Baord *stonesTmp = placeStone(stonesBoard, states[depth][i], x, y);
                    int countNum, cnt;
                    getGroupsCountBoard(tmp, 0, &countNum, &cnt);
                    places.push_back(new Placement(mastertmp, stonesTmp, x, y, states[depth][i]->flipped, states[depth][i]->rotate, countNum, touching, passes));
                    std::vector<Placement *> *result = solve(mastertmp, stonesTmp, states, depth + 1, remain - 1, passes);
                    delete tmp;
                }
            }
        }
    }
}

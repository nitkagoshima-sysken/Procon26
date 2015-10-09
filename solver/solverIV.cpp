#include "../procon26_module.hpp"
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

#define SOLVER_FOR for(int x = -(STONE_SIZE - 1); x < BOARD_SIZE - 1; x ++) for(int y = -(STONE_SIZE - 1); y < BOARD_SIZE - 1; y ++)

struct Placement{
    int x, y, rotate;
    bool flipped;
};

struct Cache{
    int score;
    std::vector<Placement> *answer;
    BoardBoolean *boardChecker;
    Board *masterBoard;
    Board *stonesBoard;
};

void releaseCaches(std::vector<Cache *> cashes, int length) {
    for (int i = 0; i < length; i ++) {
        releaseCache(cashes[i]);
        delete cashes[i];
    }
}

void releaseCache(Cache *cache) {
        delete cashes[i]->answer;
        delete cashes[i]->boardChecker;
        delete cashes[i]->masterBoard;
        delete cashes[i]->stonesBoard;
}

class SolverIV{

    public:
        static int limitDepth = 3;
        static int limitNumber = 10;

        static Answers *solve(Problem &problem){
            std::vector<std::vector<State *> > states, picked;
            convertStonesToVectorOfStates(problem.stones, problem.num, states);
            std::vector<int> zukus, stoneNumbers;
            // count zuku of stones
            for (int i = 0; i < problem.num; i ++) {
                zukus.push_back(countBitOfStone(&(problem.stones[i])));
            }
            std::vector<Placement> *answer = new std::vector<Placement>();
            StonePicker *stonePicker = new StonePicker(states, zukus, BOARD_SIZE * BOARD_SIZE - countBitOfBoard(&problem.board));
            BoardBoolean *boardChecker = new BoardBoolean();
            while (true) {
                bool end = false;
                std::vector<Placement> *result = NULL;
                stonePicker->getNext(picked, stoneNumbers);
                if (picked.size() == 0) {
                    end = true;
                    result = NULL;
                } else {
                    result = solve(answer, boardChecker, &problem.board, cloneBoard(EMPTY_BOARD), picked);
                    if (result != NULL) {
                        end = true;
                    }
                }
                if (end) {
                    releaseVector(states);
                    releaseVector(picked);
                    delete boardChecker;
                    delete answer;
                    Answers *answers = new Answers(states.size());
                    for (int i = 0; i < result->size(); i ++) {
                        Placement tmp = result->at(i);
                        answers->place(stoneNumbers[i], tmp.x, tmp.y, tmp.flipped, tmp.rotate);
                    }
                    return answers;
                }
            }
        }

    private:
        static int merge(std::vector<Cache *> &dest, std::vector<Cache *> &caches1, int l1, std::vector<Cache *> &caches2, int l2) {
            int i = 0, i1 = 0, i2 = 0;
            while (i < limitNumber; i1 < l1 && i2 < l2) {
                if (caches1[i1] == caches2[i2]) {
                    dest[i ++] = caches1[i1 ++];
                    i2 ++;
                } else if (caches1[i1] > caches2[i2]) {
                    dest[i ++] = caches1[i1 ++];
                } else {
                    dest[i ++] = caches2[i2 ++];
                }
            }
            for (; i1 < l1; i1 ++) {
                releaseCache(caches1[i1]);
            }
            for (; i2 < l2; i2 ++) {
                releaseCache(caches2[i2]);
            }
            return i;
        }

        static std::vector<Placement> *solve(
                std::vector<Placement> *answer,
                BoardBoolean *boardChecker,
                Board *masterBoard,
                Board *stonesBoard,
                std::vector<std::vector<State *> > &states) {
            int depth = 0, num = states.size(), cachesSize = 0, cachesTmpSize = 1;
            bool end = false;
            std::vector<Cache *> caches(limitNumber), cachesTmp(limitNumber)
            cachesTmp[0] = new Cache(0, answer, boardChecker, masterBoard, stonesBoard);
            while (!end) {
                if (cachesTmpSize == 0) {
                    return NULL;
                }
                releaseCaches(caches, cachesSize);
                caches = cachesTmp;
                cachesTmpSize = 0;

                depth += limitDepth;
                number = limitNumber;
                if (! (depth < num)) {
                    end = true;
                    limitNumber -= depth - (num - 1);
                }
                for (int i = 0; i < cachesSize; i ++) {
                    std::vector<Cache *> *result;
                    int resultSize;
                    result = solveInternal(caches[i].answer, caches[i].boardChecker, caches[i].masterBoard, caches[i].stonesBoard, states, depth, &resultSize);
                    std::vector<Cache *> copy = cachesTmp;
                    cachesTmpSize = merge(cachesTmp, copy, cashesTmpSize, *result, resultSize);
                }
            }
            // end
            if (cashesTmpSize == 0) {
                return NULL;
            }
            return cashesTmp[0].answer;
        }

        static std::vector<Cache *> *solveInternal(
                std::vector<Placement> *answer,
                BoardBoolean *boardChecker,
                Board *masterBoard,
                Board *stonesBoard,
                std::vector<std::vector<State *> > &states,
                int depth,
                int *resultSize){
            SOLVER_FOR if((depth == 0) | !boardChecker->check(x, y)) for(int i = 0; i < states[depth].size(); i ++){
                if(canPlace(masterBoard, stonesBoard, states[depth][i], x, y, depth == 0)){
                    //新しくanswerを作る
                    std::vector<Placement> *placedAnswer = new std::vector<Placement>(answer->size() + 1);
                    for(int i = 0; i < answer->size(); i ++){
                        placedAnswer->assign(i, answer->at(i));
                    }
                    Placement tmp = {x, y, states[depth][i]->turn, states[depth][i]->flipped};
                    placedAnswer->assign(answer->size(), tmp);
                    if(depth == states.size() - 1){
                        return placedAnswer;
                    }
                    //再帰
                    BoardBoolean *placedBoardChecker = boardChecker->place(x, y);
                    Board *placedMasterBoard = placeStone(masterBoard, states[depth][i], x, y);
                    Board *placedStonesBoard = placeStone(stonesBoard, states[depth][i], x, y);
                    std::vector<Placement> *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth - 1);
                    std::vector<Placement>().swap(*placedAnswer);
                    delete placedBoardChecker;
                    delete placedMasterBoard;
                    delete placedStonesBoard;
                    if(result != NULL){
                        return result;
                    }
                }
            }
            return NULL;
        }

};

int main()
{
	// read Problem
	string filePath;
	cin >> filePath;
	Problem prob = *readProblem(filePath);
	
    Answers *ans = SolverIV::solve(prob);

    // output Answers
    ans->print(cout);
    
    return 0;
}

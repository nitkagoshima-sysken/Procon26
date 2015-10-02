#include "../procon26_module.hpp"
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

#define SOLVER_FOR for(int x = -(STONE_SIZE - 1); x < BOARD_SIZE - 1; x ++) for(int y = -(STONE_SIZE - 1); y < BOARD_SIZE - 1; y ++)

struct Placement{
    int x, y, rotate;
    bool flipped;
};

class SolverIV{

    public:
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
                    result = solveInternal(answer, boardChecker, &problem.board, cloneBoard(EMPTY_BOARD), picked, 0, true);
                    if (result != NULL) {
                        end = true;
                    }
                }
                if (end) {
                    releaseVector(states);
                    releaseVector(picked);
                    delete boardChecker;
                    delete answer;
                    Answers *answers = new Answers();
                    for (int i = 0; i < result->size(); i ++) {
                        Placement tmp = result->at(i);
                        answers->place(stoneNumbers[i], tmp.x, tmp.y, tmp.flipped, tmp.rotate);
                    }
                    return answers;
                }
            }
        }

    private:
        static std::vector<Placement> *solveInternal(
                std::vector<Placement> *answer,
                BoardBoolean *boardChecker,
                Board *masterBoard,
                Board *stonesBoard,
                std::vector<std::vector<State *> > &states,
                int depth,
                bool first=false){
            SOLVER_FOR if(boardChecker->check(x, y)) for(int i = 0; i < states[depth].size(); i ++){
                if(canPlace(masterBoard, stonesBoard, states[depth][i], x, y, first)){
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
                    std::vector<Placement> *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth + 1);
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

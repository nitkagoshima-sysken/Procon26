#include "../procon26_module.hpp"
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

#define SOLVER_FOR for(int x = -(STONE_SIZE - 1); x < BOARD_SIZE - 1; x ++) for(int y = -(STONE_SIZE - 1); y < BOARD_SIZE - 1; y ++)

class SolverIV{

    public:
        static Answers *solve(Problem &problem){
            std::vector<std::vector<State *> > states, picked;
            convertStonesToVectorOfStates(problem.stones, problem.num, states);
            std::vector<int> zukus;
            // count zuku of stones
            for (int i = 0; i < problem.num; i ++) {
                zukus.push_back(countBitOfStone(&(problem.stones[i])));
            }
            Answers *answer = new Answers();
            StonePicker *stonePicker = new StonePicker(states, zukus, BOARD_SIZE * BOARD_SIZE - countBitOfBoard(problem.board));
            BoardBoolean boardChecker = new BoardBoolean();
            while (true) {
                bool end = false;
                Answers *result = NULL;
                stonePicker->getNext(picked);
                if (picked.size() == 0) {
                    end = true;
                    result = NULL;
                } else {
                    result = solveInternal(answer, boardChecker, problem.board, cloneBoard(EMPTY_BOARD), picked, 0, true);
                    if (result != NULL) {
                        end = true;
                    }
                }
                if (end) {
                    releaseVector(states);
                    releaseVector(picked);
                    delete boardChecker;
                    delete answer;
                    return result;
                }
            }
        }

    private:
        static Answers *solveInternal(
                Answers *answer,
                BoardBoolean *boardChecker,
                Board *masterBoard,
                Board *stonesBoard,
                std::vector<std::vector<State *> > &states,
                int depth,
                bool first=false){
            SOLVER_FOR if(boardChecker->check(x, y)) for(int i = 0; i < states[depth].size(); i ++){
                if(canPlace(masterBoard, stonesBoard, states[depth][i], x, y, first)){
                    Answers *placedAnswer = answer->place(states[depth][i], x, y);
                    if(depth == states.size() - 1){
                        return placedAnswer;
                    }
                    //再帰
                    BoardBoolean *placedBoardChecker = boardChecker->place(x, y);
                    Board *placedMasterBoard = placeStone(masterBoard, states[depth][i], x, y);
                    Board *placedStonesBoard = placeStone(stonesBoard, states[depth][i], x, y);
                    Answers *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth + 1);
                    delete placedAnswer;
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

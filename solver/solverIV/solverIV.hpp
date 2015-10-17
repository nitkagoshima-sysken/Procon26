#include <vector>
#include "../../procon26_module.hpp"
#include "../../procon26_modlib.hpp"
#include "../../procon26_modio.hpp"

#define SOLVER_FOR for(int x = -(STONE_SIZE - 1); x < BOARD_SIZE - 1; x ++) for(int y = -(STONE_SIZE - 1); y < BOARD_SIZE - 1; y ++)

struct Placement{
    Placement(int, int, bool, int);
    int x, y, rotate;
    bool flipped;
};

struct Cache{
    Cache(int _score, std::vector<Placement *> *_answer, BoardBoolean *_boardChecker, Board *_masterBoard, Board *_stonesBoard);
    int score;
    // TODO 
    std::vector<Placement *> *answer;
    BoardBoolean *boardChecker;
    Board *masterBoard;
    Board *stonesBoard;
};

void releaseCaches(std::vector<Cache *> caches, int length);
void releaseCache(Cache *cache);

class SolverIV{

    public:
        static int limitDepth;
        static int limitNumber;
        static int scoreFunction;
        static int num;
        static std::vector<int> *stoneNumbers;
        static SubmissionManager *submissionManager;
        static int max;

        static Answers *solve(Problem &problem);

    private:
        static Answers *makeAnswers(std::vector<Placement *> *answer);
        static float getScore(std::vector<Placement *> *answer, Board *masterBoard, Board *stonesBoard);
        static int merge(std::vector<Cache *> &dest, std::vector<Cache *> &caches1, int l1, std::vector<Cache *> &caches2, int l2);;
        static void solve(
                std::vector<Placement *> *answer,
                BoardBoolean *boardChecker,
                Board *masterBoard,
                Board *stonesBoard,
                std::vector<std::vector<State *> > &states,
                int depth);
        static std::vector<Cache *> *solveInternal(
                std::vector<Placement *> *answer,
                BoardBoolean *boardChecker,
                Board *masterBoard,
                Board *stonesBoard,
                std::vector<std::vector<State *> > &states,
                int depth,
                int number,
                int *resultSize);
};

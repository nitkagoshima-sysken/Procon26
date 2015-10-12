#include "solverIV.hpp"
#include "../../procon26_module.hpp"
#include "../../procon26_modlib.hpp"
#include "../../procon26_modio.hpp"

#define PLAN_MAX 6

int SolverIV::limitDepth;
int SolverIV::limitNumber;
int SolverIV::scoreFunction;
int SolverIV::num;
std::vector<int> *SolverIV::stoneNumbers;
SubmissionManager *SolverIV::submissionManager;
int SolverIV::max;
int SolverIV::planMax;

void releaseCaches(std::vector<Cache *> caches, int length) {
    for (int i = 0; i < length; i ++) {
        releaseCache(caches[i]);
        delete caches[i];
    }
}

void releaseCache(Cache *cache) {
    delete cache->answer;
    delete cache->boardChecker;
    delete cache->masterBoard;
    delete cache->stonesBoard;
}

Placement::Placement(int x, int y, bool flipped, int rotate) {
    this->x = x;
    this->y = y;
    this->flipped = flipped;
    this->rotate = rotate;
}

Cache::Cache(int _score, std::vector<Placement *> *_answer, BoardBoolean *_boardChecker, Board *_masterBoard, Board *_stonesBoard) {
    score = _score;
    answer = _answer;
    boardChecker = _boardChecker;
    masterBoard = _masterBoard;
    stonesBoard = _stonesBoard;
}

Answers *SolverIV::makeAnswers(std::vector<Placement *> *answer) {
    Answers *answers = new Answers(num);
    for (int i = 0; i < answer->size(); i ++) {
        Placement *tmp = answer->at(i);
        if (tmp != NULL) {
            answers->place(i, tmp->x, tmp->y, tmp->flipped, tmp->rotate);
        }
    }
    return answers;
}

void SolverIV::solve(Problem &problem){
    max = BOARD_SIZE * BOARD_SIZE;
    submissionManager = new SubmissionManager("answer");
    std::vector<std::vector<State *> > states;
    convertStonesToVectorOfStates(problem.stones, problem.num, states);
    SolverIV::num = problem.num;
    std::vector<Placement *> *answer = new std::vector<Placement *>();
    BoardBoolean *boardChecker = new BoardBoolean();
    int groupsCount, count;
    getGroupsCountBoard(&problem.board, 0, &groupsCount, &count);
    solve(answer, boardChecker, cloneBoard(&problem.board), cloneBoard(EMPTY_BOARD), states, 0, groupsCount, 0);
    releaseVector(states);
    delete boardChecker;
    delete answer;
}

float SolverIV::getScore(std::vector<Placement *> *answer, Board *masterBoard, Board *stonesBoard) {
    switch (scoreFunction) {
        case 0:
            return evalBoard(masterBoard);
        default: // 粗密度
            int groupsCount, count;
            getGroupsCountBoard(masterBoard, 0, &groupsCount, &count);
            return count / groupsCount;
    }
}

int SolverIV::merge(std::vector<Cache *> &dest, std::vector<Cache *> &caches1, int l1, std::vector<Cache *> &caches2, int l2) {
    int i = 0, i1 = 0, i2 = 0;
    while (i < SolverIV::limitNumber && i1 < l1 && i2 < l2) {
        if (caches1[i1]->score == caches2[i2]->score) {
            dest[i ++] = caches1[i1 ++];
        } else if (caches1[i1]->score > caches2[i2]->score) {
            dest[i ++] = caches1[i1 ++];
        } else {
            dest[i ++] = caches2[i2 ++];
        }
    }
    while (i < SolverIV::limitNumber && i1 < l1) dest[i ++] = caches1[i1 ++];
    while (i < SolverIV::limitNumber && i2 < l2) dest[i ++] = caches2[i2 ++];
    for (; i1 < l1; i1 ++) {
        releaseCache(caches1[i1]);
    }
    for (; i2 < l2; i2 ++) {
        releaseCache(caches2[i2]);
    }
    return i;
}

void SolverIV::solve(
        std::vector<Placement *> *answer,
        BoardBoolean *boardChecker,
        Board *masterBoard,
        Board *stonesBoard,
        std::vector<std::vector<State *> > &states,
        int depth,
        int groups, int plan) {
    if (depth == num - 1) {
        int score = BOARD_SIZE * BOARD_SIZE - countBitOfBoard(masterBoard);
        if (score < max) {
            cout << score << endl;
            submissionManager->submit(makeAnswers(answer));
            max = score;
        }
        showBoard(masterBoard);
    }
    std::vector<Cache *> *caches = new std::vector<Cache *>(SolverIV::limitNumber);
    int number = SolverIV::limitDepth;
    if (!(depth + number < num)) {
        number = num - depth - 1;
    }
    int resultSize;
    int groupsCount, count;
    getGroupsCountBoard(masterBoard, 0, &groupsCount, &count);
    std::vector<Cache *> *result = solveInternal(answer, boardChecker, masterBoard, stonesBoard, states, depth, number, &resultSize, groupsCount, plan);
    if (resultSize == 0) {
        int score = BOARD_SIZE * BOARD_SIZE - countBitOfBoard(masterBoard);
        if (score < max) {
            cout << score << endl;
            submissionManager->submit(makeAnswers(answer));
            max = score;
        }
    }
    for (int i = 0; i < resultSize; i ++) {
        Cache *tmp = result->at(i);
        int groupsCount, count;
        getGroupsCountBoard(tmp->masterBoard, 0, &groupsCount, &count);
        solve(tmp->answer, tmp->boardChecker, tmp->masterBoard, tmp->stonesBoard, states, depth + number, groupsCount, 0);
    }
    if (plan < planMax) {
        solve(answer, boardChecker, masterBoard, stonesBoard, states, depth, groupsCount, plan + 1);
    }
    releaseCaches(*result, resultSize);
}

std::vector<Cache *> *SolverIV::solveInternal(
        std::vector<Placement *> *answer,
        BoardBoolean *boardChecker,
        Board *masterBoard,
        Board *stonesBoard,
        std::vector<std::vector<State *> > &states,
        int depth,
        int limit,
        int *resultSize, int groups, int plan){
    std::vector<Cache *> *caches = new std::vector<Cache *>(SolverIV::limitNumber);
    *resultSize = 0;

    std::vector<Placement *> *placedAnswer = new std::vector<Placement *>(*answer);
    placedAnswer->push_back(NULL);
    BoardBoolean *placedBoardChecker = boardChecker->place(-100, -100);
    Board *placedMasterBoard = cloneBoard(masterBoard);
    Board *placedStonesBoard = cloneBoard(stonesBoard);

    if(limit != 1){ // edge of limit
        int resultSizeTmp;
        std::vector<Cache *> *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth + 1, limit - 1, &resultSizeTmp, groups, plan);
        std::vector<Cache *> *copy = new std::vector<Cache *>(*caches);
        *resultSize = merge(*caches, *copy, *resultSize, *result, resultSizeTmp);
        delete placedAnswer;
        std::vector<Cache *>().swap(*copy);
        delete placedBoardChecker;
        delete placedMasterBoard;
        delete placedStonesBoard;
    } else {
        caches->at(0) = new Cache(getScore(placedAnswer, placedMasterBoard, placedStonesBoard),
                placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard);
    }
    SOLVER_FOR if((depth == 0) | boardChecker->check(x, y)) for(int i = 0; i < states[depth].size(); i ++){
        if(canPlace(masterBoard, stonesBoard, states[depth][i], x, y, depth == 0)){
            Board *placedMasterBoard = placeStone(masterBoard, states[depth][i], x, y);
            int groups2, count;
            getGroupsCountBoard(placedMasterBoard, 0, &groups2, &count);
            if (groups2 - groups > plan) {
                delete placedMasterBoard;
                continue;
            }

            //新しくanswerを作る
            std::vector<Placement *> *placedAnswer = new std::vector<Placement *>(*answer);
            placedAnswer->push_back(new Placement(x, y, states[depth][i]->flipped, states[depth][i]->turn));


            BoardBoolean *placedBoardChecker = boardChecker->place(x, y);
            Board *placedStonesBoard = placeStone(stonesBoard, states[depth][i], x, y);

            //showBoard(placedStonesBoard);

            if(limit == 1){ // edge of limit
                float score;
                caches->at(1) = new Cache(score = getScore(placedAnswer, placedMasterBoard, placedStonesBoard),
                        placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard);
                *resultSize = 2;
                return caches;
            } else {
                //再帰
                int resultSizeTmp;
                std::vector<Cache *> *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth + 1, limit - 1, &resultSizeTmp, groups2, plan);
                std::vector<Cache *> *copy = new std::vector<Cache *>(*caches);
                *resultSize = merge(*caches, *copy, *resultSize, *result, resultSizeTmp);
                delete placedAnswer;
                std::vector<Cache *>().swap(*copy);
                delete placedBoardChecker;
                delete placedMasterBoard;
                delete placedStonesBoard;
            }
        }
    }
    return caches;
}

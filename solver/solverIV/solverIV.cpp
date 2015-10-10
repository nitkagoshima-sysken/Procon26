#include "solverIV.hpp"
#include "../../procon26_module.hpp"
#include "../../procon26_modlib.hpp"

int SolverIV::limitDepth;
int SolverIV::limitNumber;
int SolverIV::scoreFunction;

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

Answers *SolverIV::solve(Problem &problem){
    std::vector<std::vector<State *> > states, picked;
    convertStonesToVectorOfStates(problem.stones, problem.num, states);
    std::vector<int> zukus, stoneNumbers;
    // count zuku of stones
    for (int i = 0; i < problem.num; i ++) {
        zukus.push_back(countBitOfStone(&(problem.stones[i])));
    }
    std::vector<Placement *> *answer = new std::vector<Placement *>();
    StonePicker *stonePicker = new StonePicker(states, zukus, BOARD_SIZE * BOARD_SIZE - countBitOfBoard(&problem.board));
    BoardBoolean *boardChecker = new BoardBoolean();
    while (true) {
        bool end = false;
        std::vector<Placement *> *result = NULL;
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
                Placement *tmp = result->at(i);
                answers->place(stoneNumbers[i], tmp->x, tmp->y, tmp->flipped, tmp->rotate);
            }
            return answers;
        }
    }
}

float SolverIV::getScore(std::vector<Placement *> *answer, Board *masterBoard, Board *stonesBoard) {
    switch (scoreFunction) {
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

std::vector<Placement *> *SolverIV::solve(
        std::vector<Placement *> *answer,
        BoardBoolean *boardChecker,
        Board *masterBoard,
        Board *stonesBoard,
        std::vector<std::vector<State *> > &states) {
    int depth = 0, num = states.size(), cachesSize = 0, cachesTmpSize = 1;
    bool end = false;
    std::vector<Cache *> caches(SolverIV::limitNumber), cachesTmp(SolverIV::limitNumber);
    cachesTmp[0] = new Cache(0, answer, boardChecker, masterBoard, stonesBoard);
    while (!end) {
        if (cachesTmpSize == 0) {
            return NULL;
        }
        if (! (depth < num)) {
            break;
        }
        releaseCaches(caches, cachesSize);
        caches = cachesTmp;
        cachesSize = cachesTmpSize;
        cachesTmpSize = 0;

        int number = SolverIV::limitDepth;
        if (!(depth + number < num)) {
            number = num - number - 1;
        }
        for (int i = 0; i < cachesSize; i ++) {
            std::vector<Cache *> *result;
            int resultSize;
            result = solveInternal(caches[i]->answer, caches[i]->boardChecker, caches[i]->masterBoard, caches[i]->stonesBoard, states, depth, number, &resultSize);
            std::vector<Cache *> copy = cachesTmp;
            cachesTmpSize = merge(cachesTmp, copy, cachesTmpSize, *result, resultSize);
        }
        depth += number;
    }
    // end
    if (cachesTmpSize == 0) {
        return NULL;
    }
    return cachesTmp[0]->answer;
}

std::vector<Cache *> *SolverIV::solveInternal(
        std::vector<Placement *> *answer,
        BoardBoolean *boardChecker,
        Board *masterBoard,
        Board *stonesBoard,
        std::vector<std::vector<State *> > &states,
        int depth,
        int limit,
        int *resultSize){
    std::vector<Cache *> *caches = new std::vector<Cache *>(100);
    *resultSize = 0;
    SOLVER_FOR if((depth == 0) | !boardChecker->check(x, y)) for(int i = 0; i < states[depth].size(); i ++){
        if(canPlace(masterBoard, stonesBoard, states[depth][i], x, y, depth == 0)){
            //新しくanswerを作る
            std::vector<Placement *> *placedAnswer = new std::vector<Placement *>(answer->size() + 1);
            for(int i = 0; i < answer->size(); i ++){
                placedAnswer->assign(i, answer->at(i));
            }
            Placement *tmp = new Placement(x, y, states[depth][i]->turn, states[depth][i]->flipped);
            placedAnswer->assign(answer->size(), tmp);

            BoardBoolean *placedBoardChecker = boardChecker->place(x, y);
            Board *placedMasterBoard = placeStone(masterBoard, states[depth][i], x, y);
            Board *placedStonesBoard = placeStone(stonesBoard, states[depth][i], x, y);

            if(limit == 1){ // edge of limit
                float score;
                caches->at(0) = new Cache(score = getScore(placedAnswer, placedMasterBoard, placedStonesBoard),
                        placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard);
                *resultSize = 1;
                return caches;
            } else {
                //再帰
                int resultSizeTmp;
                std::vector<Cache *> *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth + 1, limit - 1, &resultSizeTmp);
                std::vector<Cache *> *copy = new std::vector<Cache *>(*caches);
                *resultSize = merge(*caches, *copy, *resultSize, *result, resultSizeTmp);
                for (int i = 0; i < placedAnswer->size(); i ++) {
                    delete placedAnswer->at(i);
                }
                std::vector<Placement *>().swap(*placedAnswer);
                std::vector<Cache *>().swap(*copy);
                delete placedBoardChecker;
                delete placedMasterBoard;
                delete placedStonesBoard;
            }
        }
    }
    return caches;
}

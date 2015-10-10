#include "solverIV.hpp"
#include "../../procon26_module.hpp"
#include "../../procon26_modlib.hpp"
#include "../../procon26_modio.hpp"

int SolverIV::limitDepth;
int SolverIV::limitNumber;
int SolverIV::scoreFunction;
int SolverIV::num;
std::vector<int> *SolverIV::stoneNumbers;
SubmissionManager *SolverIV::submissionManager;

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
        answers->place(stoneNumbers->at(i), tmp->x, tmp->y, tmp->flipped, tmp->rotate);
    }
    return answers;
}

Answers *SolverIV::solve(Problem &problem){
    submissionManager = new SubmissionManager("answer4");
    std::vector<std::vector<State *> > states, picked;
    convertStonesToVectorOfStates(problem.stones, problem.num, states);
    SolverIV::num = problem.num;
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
        SolverIV::stoneNumbers = &stoneNumbers;
        if (picked.size() == 0) {
            end = true;
            result = NULL;
        } else {
            std::vector<Cache *> *caches = solve(answer, boardChecker, &problem.board, picked);
            result = caches->at(0)->answer;
            if (result != NULL) {
                end = true;
            }
        }
        if (end) {
            releaseVector(states);
            releaseVector(picked);
            delete boardChecker;
            delete answer;
            Answers *answers = makeAnswers(answer);
            return answers;
        }
    }
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

std::vector<Cache *> *SolverIV::solve(
        std::vector<Placement *> *answer,
        BoardBoolean *boardChecker,
        Board *masterBoard,
        std::vector<std::vector<State *> > &states) {
    int depth = 0, num = states.size(), cachesSize = 0, cachesTmpSize = 1;
    bool end = false;
    std::vector<Cache *> *caches = new std::vector<Cache *>(SolverIV::limitNumber), *cachesTmp = new std::vector<Cache *>(SolverIV::limitNumber), *copy;
    cachesTmp->at(0) = new Cache(0, answer, boardChecker, cloneBoard(masterBoard), cloneBoard(EMPTY_BOARD));
    while (!end) {
        if (cachesTmpSize == 0) {
            // TODO submit answer
            submissionManager->submit(makeAnswers(caches->at(0)->answer));
            showBoard(caches->at(0)->masterBoard);
            return NULL;
        }
        if (! (depth < num)) {
            break;
        }
        releaseCaches(*caches, cachesSize);
        caches = new std::vector<Cache *>(*cachesTmp);
        cachesSize = cachesTmpSize;
        cachesTmpSize = 0;

        int number = SolverIV::limitDepth;
        if (!(depth + number < num)) {
            number = num - number - 1;
        }
        for (int i = 0; i < cachesSize; i ++) {
            std::vector<Cache *> *result;
            int resultSize;
            result = solveInternal(caches->at(i)->answer, caches->at(i)->boardChecker, caches->at(i)->masterBoard, caches->at(i)->stonesBoard, states, depth, number, &resultSize);
            copy = new std::vector<Cache *>(*cachesTmp);
            cachesTmpSize = merge(*cachesTmp, *copy, cachesTmpSize, *result, resultSize);
        }
        depth += number;
    }
    return cachesTmp;
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
    for (int i = 0; i < depth; i ++) cout << " ";
    cout << "depth: " << depth << endl;
    std::vector<Cache *> *caches = new std::vector<Cache *>(SolverIV::limitNumber);
    *resultSize = 0;
    SOLVER_FOR if((depth == 0) | boardChecker->check(x, y)) for(int i = 0; i < states[depth].size(); i ++){
        if(canPlace(masterBoard, stonesBoard, states[depth][i], x, y, depth == 0)){
            //新しくanswerを作る
            std::vector<Placement *> *placedAnswer = new std::vector<Placement *>(*answer);
            placedAnswer->push_back(new Placement(x, y, states[depth][i]->flipped, states[depth][i]->turn));


            BoardBoolean *placedBoardChecker = boardChecker->place(x, y);
            Board *placedMasterBoard = placeStone(masterBoard, states[depth][i], x, y);
            Board *placedStonesBoard = placeStone(stonesBoard, states[depth][i], x, y);

            //showBoard(placedMasterBoard);

            if(limit == 1){ // edge of limit
                float score;
                caches->at(0) = new Cache(score = getScore(placedAnswer, placedMasterBoard, placedStonesBoard),
                        placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard);
                for (int i = 0; i < depth; i ++) cout << " ";
                *resultSize = 1;
                return caches;
            } else {
                //再帰
                int resultSizeTmp;
                std::vector<Cache *> *result = solveInternal(placedAnswer, placedBoardChecker, placedMasterBoard, placedStonesBoard, states, depth + 1, limit - 1, &resultSizeTmp);
                std::vector<Cache *> *copy = new std::vector<Cache *>(*caches);
                *resultSize = merge(*caches, *copy, *resultSize, *result, resultSizeTmp);
                for (int i = 0; i < depth; i ++) cout << " ";
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

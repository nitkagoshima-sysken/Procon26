cd test
TEST_DIR=SubmissionManager_tmp
mkdir $TEST_DIR; cd $TEST_DIR
g++ -o test.out ../SubmissionManager_test.cpp ../../procon26_module.cpp; ./test.out
[ -f "answer0.txt" ] && [ -f "answer1.txt" ] &&
   cmp answer0.txt ../resources/answer0.txt && cmp answer1.txt ../resources/answer1.txt &&
    echo "[SUCCESS] SubmissionManager" ||
    echo "[FAILURE] SubmissionManager"
cd ..; rm -rf $TEST_DIR;
cd ..

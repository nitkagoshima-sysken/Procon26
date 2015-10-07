TEST_DIR=SubmissionManager_tmp
mkdir $TEST_DIR; cd $TEST_DIR
g++ -o test.out ../SubmissionManager.cpp ../../procon26_module.cpp; ./test.out
[ -f "answer0.txt" ] && [ -f "answer1.txt" ] &&
    ! [ cmp -s "answer0.txt" "../resource/answer0.txt" ] && ! [cmp -s "answer0.txt" "../resource/answer1.txt" ] &&
    echo "[SUCCESS] SubmissionManager" ||
    echo "[FAILURE] SubmissionManager"
cd ..; rm -rf TEST_DIR;


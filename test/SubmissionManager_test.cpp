#include "../procon26_module.hpp"

using namespace std;

int main()
{
    Answers answer1(6), answer2(6);
    Answer ans1; ans1.X = 1; ans1.Y = 0; ans1.turn = 2; ans1.flipped = false;
    Answer ans2; ans2.X = 9; ans2.Y = 5; ans2.turn = 0; ans2.flipped = true;
    State _ans2; _ans2.turn = 0; _ans2.flipped = true;

    answer1.place(2, ans1.X, ans1.Y, ans1.flipped, ans1.turn);
    answer1.place(4, &_ans2, ans2.X, ans2.Y);
    answer2.place(2, &_ans2, ans2.X, ans2.Y);
    answer2.place(4, ans1.X, ans1.Y, ans1.flipped, ans1.turn);

    SubmissionManager sm("answer");
    sm.submit(&answer1);
    sm.submit(&answer2);
    return 0;
}

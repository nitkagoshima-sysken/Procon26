#include "procon26_module.hpp"

string Answer::toString()
{
	stringstream sout;
    if (X == NULL_POINT&& Y == NULL_POINT)
    {
        sout << "";
    }
    else
    {
        sout << X << " " << Y << " " << (flipped ? "T" : "H") << " " << turn;
    }
	
	return sout.str();
}

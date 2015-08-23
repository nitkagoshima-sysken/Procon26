#include "procon26_modio.cpp"

using namespace std;
 
bool releaseVector(vector<Stone> &stones)
{
	//for(int i = 0; i < 8; i++) delete stones[i];
	vector<Stone>().swap(stones);
	if(stones.empty() == 0) return false;
	else					   return true;
}

bool releaseVector(vector<Board> &boards)
{
	vector<Board>().swap(boards);
	if(boards.empty() == 0) return false;
	else					return true;
}

bool releaseVector(vector<State> &states)
{
	vector<State>().swap(states);
	if(states.empty() == 0) return false;
	else					return true;
}

bool releaseVector(vector< vector<State> > &stones)
{
	vector< vector<State> >().swap(stones);
	if(stones.empty() == 0) return false;
	else					return true;
}

bool releaseVector(vector< vector<Stone> > &stones)
{
	vector< vector<Stone> >().swap(stones);
	if(stones.empty() == 0) return false;
	else					return true;
}
int main()
{	
	vector<Stone> data_stone;
	vector<Board> data_board;
	vector<State> data_state;
	vector< vector<Stone> > data_vecstone;
	vector< vector<State> > data_vecstate;
	
	Stone stone;
	Board board;
	State state;
	
	for(int i = 0; i <   8; i++) stone.zuku[i]  = 10;
	for(int i = 0; i < 128; i++) board.block[i] = 10;
	state.flipped = 1; state.turn = 180;
	
	//data_stone.push_back(stone);
	data_board.push_back(board);
	data_state.push_back(state);
	data_vecstone.push_back(data_stone);
	data_vecstate.push_back(data_state);
	
	cout << "-hold-"    << endl;
	cout << "stone   :" << data_stone.capacity()    << endl;
	cout << "board   :" << data_board.capacity()    << endl;
	cout << "state   :" << data_state.capacity()    << endl;
	cout << "vecstone:" << data_vecstone.capacity() << endl;
	cout << "vecstate:" << data_vecstate.capacity() << endl;
	
	cout << endl << "state of releasing :";
	cout << releaseVector(data_stone);
	cout << releaseVector(data_board);
	cout << releaseVector(data_state);
	cout << releaseVector(data_vecstone);
	cout << releaseVector(data_vecstate);
	cout << endl;
	
	cout << endl        << "-release-"               << endl;
	cout << "stone   :" << data_stone.capacity()    << endl;
	cout << "board   :" << data_board.capacity()    << endl;
	cout << "state   :" << data_state.capacity()    << endl;
	cout << "vecstone:" << data_vecstone.capacity() << endl;
	cout << "vecstate:" << data_vecstate.capacity() << endl;
	
	return 0;
}

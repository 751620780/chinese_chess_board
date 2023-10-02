#include <vector>
#include <deque>



using namespace std;
void init_env();
vector<string> cal_move_actions(string fen);
string do_move(string fen,string move);


class ChessBoard
{
public:
	ChessBoard(const string &fen);
	~ChessBoard();
	vector<string> all_legal_moves();
	bool do_move(string &action);
	string fen(); 
	void flip();
private:
    void* ppos;
    void* pstates;
};
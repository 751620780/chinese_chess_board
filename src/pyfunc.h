#include <vector>
#include <deque>



using namespace std;
void init_env();
vector<string> all_legal_moves(string fen_cmd);
string do_move(string fen_cmd,string move);


class ChessBoard
{
public:
	ChessBoard(const string &fen_cmd);
	~ChessBoard();
	vector<string> all_legal_moves();
	bool do_move(string &action);
	string fen(); 
	void flip();
	int side_to_move();
private:
    void* ppos;
    void* pstates;
};
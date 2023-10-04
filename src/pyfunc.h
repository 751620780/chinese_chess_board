#include <vector>
#include <deque>



using namespace std;
void init_env();

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
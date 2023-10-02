#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include "pyfunc.h"
#include "bitboard.h"
#include "position.h"
#include "movegen.h"
#include "types.h"

using namespace Stockfish;

const char *StartFEN = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w";

/// square() converts a Square to a string in algebraic notation (g1, a7, etc.)
string square(Square s)
{
	return string{char('a' + file_of(s)), char('0' + rank_of(s))};
}

/// move() converts a Move to a string in coordinate notation (g1f3, a7a8).
string move_convert(Move m)
{

	if (m == MOVE_NONE)
		return "(none)";

	if (m == MOVE_NULL)
		return "0000";

	Square from = from_sq(m);
	Square to = to_sq(m);

	string move = square(from) + square(to);

	return move;
}

/// to_move() converts a string representing a move in coordinate notation
/// (g1f3, a7a8) to the corresponding legal Move, if any.
Move to_move(const Position &pos, string &str)
{
	for (const auto &m : MoveList<LEGAL>(pos))
	{
		if (str == move_convert(m))
			return m;
	}

	return MOVE_NONE;
}

vector<string> get_moves(const Position &pos)
{
	vector<string> ret(0);
	for (const auto &m : MoveList<LEGAL>(pos))
		ret.push_back(move_convert(m));
	return ret;
}

void init_env()
{
	Bitboards::init();
	Position::init();
}

vector<string> cal_move_actions(string fen)
{
	Position pos;
	Move m;
	string token, cmd;
	istringstream is(fen);
	StateListPtr states = StateListPtr(new deque<StateInfo>(1));

	is >> token;

	if (token == "startpos")
	{
		cmd = StartFEN;
		is >> token; // Consume the "moves" token, if any
	}
	else if (token == "fen")
		while (is >> token && token != "moves")
			cmd += token + " ";
	else
		return vector<string>();

	pos.set(cmd, &states->back());

	// Parse the move list, if any
	while (is >> token && (m = to_move(pos, token)) != MOVE_NONE)
	{
		states->emplace_back();
		pos.do_move(m, states->back());
	}
	return get_moves(pos);
}

string do_move(string fen, string move)
{
	Position pos;
	Move m;
	string token, cmd;
	istringstream is(fen);
	StateListPtr states = StateListPtr(new deque<StateInfo>(1));

	is >> token;

	if (token == "startpos")
	{
		cmd = StartFEN;
		is >> token;
	}
	else if (token == "fen")
		while (is >> token && token != "moves")
			cmd += token + " ";
	else
		return "";

	pos.set(cmd, &states->back());

	while (is >> token && (m = to_move(pos, token)) != MOVE_NONE)
	{
		states->emplace_back();
		pos.do_move(m, states->back());
	}
	if ((m = to_move(pos, move)) != MOVE_NONE)
	{
		states->emplace_back();
		pos.do_move(m, states->back());
	}
	
	return pos.fen();
}

ChessBoard::ChessBoard(const string &fen)
{
	Move m;
	string token, fen_str;
	istringstream is(fen);
	ppos = (void*)new Position();
	pstates = (void*)new StateListPtr(new deque<StateInfo>(1));

	is >> token;

	if (token == "fen")
	{
		while (is >> token && token != "moves")
			fen_str += token + " ";
	}
	else
	{
		fen_str = fen;
		is.str("");
	}

	((Position*)ppos)->set(fen_str, &((*(StateListPtr*)pstates)->back()));

	// Parse the move list, if any
	while (is >> token && (m = to_move(*((Position*)ppos), token)) != MOVE_NONE)
	{
		(*(StateListPtr*)pstates)->emplace_back();
		((Position*)ppos)->do_move(m, (*(StateListPtr*)pstates)->back());
	}
}

vector<string> ChessBoard::all_legal_moves()
{
	return get_moves(*((Position*)ppos));
}

bool ChessBoard::do_move(string &action)
{
	Move m;
	delete (StateListPtr*)pstates;
	pstates = (void*) new StateListPtr(new deque<StateInfo>(1));
	if ((m = to_move(*(Position*)ppos, action)) != MOVE_NONE)
	{
		(*(StateListPtr*)pstates)->emplace_back();
		((Position*)ppos)->do_move(m, (*(StateListPtr*)pstates)->back());
		return true;
	}
	return false;
}

string ChessBoard::fen()
{
	return ((Position*)ppos)->fen();
}

void ChessBoard::flip()
{
	((Position*)ppos)->flip();
}

ChessBoard::~ChessBoard()
{
	if (ppos != nullptr)
		delete (Position*)ppos;
	if (pstates != nullptr)
		delete (StateListPtr*)pstates;
}
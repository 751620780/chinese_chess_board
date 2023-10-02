#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pyfunc.h"

namespace py = pybind11;


PYBIND11_MODULE(chess_board, m)
{
    m.doc() = "pybind11 chess_board plugin"; 

	m.def("init_env", &init_env,"Init chinese chess board environment");

	m.def("cal_move_actions", &cal_move_actions,"Given the state of the Chinese "
	"chess board represented using a FEN string, all possible "
	"pieces action in the current state are returned");  

	m.def("do_move", &do_move,"Given the state of the Chinese chess board represented "
	"using the FEN string and the movement path of the pawn to calculate the chessboard "
	"FEN after the pawn moves, the FEN string is returned if the pawn's movement operation "
	"is a legal operation, otherwise an empty string is returned.");  

	py::class_<ChessBoard>(m, "ChessBoard","Chinese Chess Board, you can instantiate an "
	    "object to implement operations on a chess board")
        .def(py::init<const std::string>(),"create a ChessBoard object, requires a FEN string as parameter.")
        .def("all_legal_moves", &ChessBoard::all_legal_moves,"Calculate and return all legal moves that "
		"all the pieces can move in the chess board")
        .def("do_move", &ChessBoard::do_move,"Given the move action, if the move action is legal, "
		"the piece will move on current chess board and return true.")
		.def("fen", &ChessBoard::fen,"return the FEN string about current chess board")
		.def("flip", &ChessBoard::flip,"flip the current chess board");
}
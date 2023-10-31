#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pyfunc.h"

namespace py = pybind11;


PYBIND11_MODULE(chess_board, m)
{
    m.doc() = "chess_board module for chinese chess, with this module, you can do chess board operate.";

	init_env();
	m.def("do_move", &do_move,"give a fen string and a legal move action,then "
	"return the FEN of piece moved chess board if move is legal, "
	"otherwise return a empty string");
	
	py::class_<ChessBoard>(m, "ChessBoard","Chinese Chess Board, you can instantiate an "
	    "object to implement operations on a chess board")
        .def(py::init<const std::string>(),"create a ChessBoard object, requires a FEN string as parameter.")
        .def("all_legal_moves", &ChessBoard::all_legal_moves,"Calculate and return all legal moves that "
		"all the pieces can move in the chess board")
        .def("do_move", &ChessBoard::do_move,"Given the move action, if the move action is legal, "
		"the piece will move on current chess board and return true.")
		.def("fen", &ChessBoard::fen,"return the FEN string about current chess board")
		.def("side_to_move", &ChessBoard::side_to_move,"tell you which side to move piece. "
		"1 means white and -1 means black")
		.def("flip", &ChessBoard::flip,"flip the current chess board");
}
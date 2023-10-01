#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pyfunc.h"

namespace py = pybind11;


PYBIND11_MODULE(chess_board, m)
{
    m.doc() = "pybind11 chess_board plugin"; 

	m.def("init", &init,"Tnit chinese chess board environment");

	m.def("cal_move", &cal_move,"Given the state of the Chinese "
	"chess board represented using a FEN string, all possible "
	"pieces action in the current state are returned");  

}
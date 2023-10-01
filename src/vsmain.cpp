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

int main(int argc, char* argv[]) 
{

	init();
	auto start = std::chrono::high_resolution_clock::now();
	std::string fen[] = { 
		"fen rnbaka2r/9/1c2b3n/p5p1p/9/1C7/P8/B8/9/cN2K4 b - - 0 1",
		"fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1" 
	};
	vector<string> moves;
	for(int i =0;i<150000;i++)
		moves = cal_move(fen[i%2]);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = end - start;
	std::cout << "Run 15w test, elapsed time: " << elapsed.count() << " microseconds." << std::endl;
	system("pause");
	return 0;
}



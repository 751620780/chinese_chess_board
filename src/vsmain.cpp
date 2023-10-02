#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <thread>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

#include "pyfunc.h"



void test() {
	std::string fen_i[] = {
		"1rbakab1r/9/6n2/p1N4cp/2n1P1pC1/PcP6/1C4P1P/6N2/9/R1BAKAB1R w - - 0 1",      
		"4kr3/4a4/9/p7p/4P1b2/3rC2c1/2P1CN2P/4B4/4A4/3AK1B2 b - - 0 1",             
		"4k3r/4a4/b2aN4/5c2p/pr2PCb2/P1B3P2/2n3C1P/5AN1R/2R6/4K1B2 b - - 0 1",      
		"4k4/2r6/b2aNa3/4c1P1p/6b2/P1B3B2/2nRC1R1P/2prCA3/5N3/4K4 w - - 0 1",       
		"r1bakab2/9/1c2c3r/pC2n1p1p/2p6/5n3/P1P1P1P1P/BN4N1B/9/R2AKA1R1 b - - 0 9",

	};

	std::string move[] = {
		"b3b9",
		"f9f3",
		"b5b0",
		"e2e6",
		"f4e2",
	};

	std::string fen_o[] = {
		"1Cbakab1r/9/6n2/p1N4cp/2n1P1pC1/PcP6/6P1P/6N2/9/R1BAKAB1R b - - 0 1",
		"4k4/4a4/9/p7p/4P1b2/3rC2c1/2P1Cr2P/4B4/4A4/3AK1B2 w - - 0 2",
		"4k3r/4a4/b2aN4/5c2p/p3PCb2/P1B3P2/2n3C1P/5AN1R/2R6/1r2K1B2 w - - 1 2",
		"4k4/2r6/b2aNa3/4C1P1p/6b2/P1B3B2/2nRC1R1P/2pr1A3/5N3/4K4 b - - 0 1",
		"r1bakab2/9/1c2c3r/pC2n1p1p/2p6/9/P1P1P1P1P/BN2n1N1B/9/R2AKA1R1 w - - 1 10",
	};
	int len = sizeof(fen_i) / sizeof(fen_i[0]);

	for (int i = 0; i < 15000; i++)
	{
		ChessBoard cb(fen_i[i % len]);
		auto res = cb.do_move(move[i%len]);
		if (cb.fen() != fen_o[i % len] || !res)
		{
			cout << cb.fen() << "   "<<move[i%len]<<"    " << fen_o[i % len] << endl;
			exit(-1);
		}
	}
}

int thread_safty_test() 
{ 
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::thread> threads;
	for (int i = 0; i < 10; ++i) {
		threads.emplace_back(test);
	}
	for (auto& thread : threads) {
		thread.join();
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = end - start;
	std::cout << "elapsed time: " << elapsed.count() << " microseconds." << std::endl;
	return 0;
}

int main(int argc, char* argv[]) 
{

	init_env();
	thread_safty_test();

	std::string fen[] = { 
		"fen 1rbakab1r/9/6n2/p1N4cp/2n1P1pC1/PcP6/1C4P1P/6N2/9/R1BAKAB1R w - - 0 1",
		"fen 1rbakab1r/9/6n2/p1N4cp/1cn1P1pC1/P1P6/1C4P1P/6N2/9/R1BAKAB1R b - - 0 11",
		"fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1",
		"fen rnbaka2r/9/1c2b3n/p5p1p/9/1C7/P8/B8/9/cN2K4 b - - 0 1"
	};
	int len = sizeof(fen) / sizeof(fen[0]);

	auto start = std::chrono::high_resolution_clock::now();
	vector<string> moves;
	for (int i = 0; i < 150000; i++)
	{
		do_move(fen[0], "b3b9");
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = end - start;
	std::cout << "Run 15w test, elapsed time: " << elapsed.count() << " microseconds." << std::endl;


	int count_all = 0;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 150000; i++)
	{
		ChessBoard cb(fen[i%len]);
		int count = 0;
		while(true)
		{
			count++;
			count_all++;
			auto m = cb.all_legal_moves();
			if (m.size() <= 0 || count >100)
				break;
			cb.do_move(m[0]);
			cb.fen();
		}
	}
	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << "Run 15w test with "<<count_all<<" moves, elapsed time : " << elapsed.count() << " microseconds."<< std::endl;
	system("pause");
	return 0;
}



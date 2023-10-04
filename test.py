# -*- coding: utf8 -*-
# coding=utf-8
# python=3.8.18

import time
import random
import os
import sys

sys.path.append(os.getcwd())
from mp import mp_work
import chess_board as cb


# 此python文件的用途：测试编译后的pyd文件在指定版本的python中能否正常使用

def work_func(data):
    # python 多进程测试
    fen_i = [
        "1rbakab1r/9/6n2/p1N4cp/2n1P1pC1/PcP6/1C4P1P/6N2/9/R1BAKAB1R w - - 0 1",      
        "4kr3/4a4/9/p7p/4P1b2/3rC2c1/2P1CN2P/4B4/4A4/3AK1B2 b - - 0 1",             
        "4k3r/4a4/b2aN4/5c2p/pr2PCb2/P1B3P2/2n3C1P/5AN1R/2R6/4K1B2 b - - 0 1",      
        "4k4/2r6/b2aNa3/4c1P1p/6b2/P1B3B2/2nRC1R1P/2prCA3/5N3/4K4 w - - 0 1",       
        "r1bakab2/9/1c2c3r/pC2n1p1p/2p6/5n3/P1P1P1P1P/BN4N1B/9/R2AKA1R1 b - - 0 9",
    ]

    move=[
        "b3b9",
        "f9f3",
        "b5b0",
        "e2e6",
        "f4e2",
    ]

    fen_o = [
        "1Cbakab1r/9/6n2/p1N4cp/2n1P1pC1/PcP6/6P1P/6N2/9/R1BAKAB1R b - - 0 1",
        "4k4/4a4/9/p7p/4P1b2/3rC2c1/2P1Cr2P/4B4/4A4/3AK1B2 w - - 0 2",
        "4k3r/4a4/b2aN4/5c2p/p3PCb2/P1B3P2/2n3C1P/5AN1R/2R6/1r2K1B2 w - - 1 2",
        "4k4/2r6/b2aNa3/4C1P1p/6b2/P1B3B2/2nRC1R1P/2pr1A3/5N3/4K4 b - - 0 1",
        "r1bakab2/9/1c2c3r/pC2n1p1p/2p6/9/P1P1P1P1P/BN2n1N1B/9/R2AKA1R1 w - - 1 10",
    ]
    fen_len = len(fen_i)
    for i in range(150000):
        cbo = cb.ChessBoard(fen_i[i % fen_len])
        moves = cbo.all_legal_moves()
        ret = cbo.do_move(move[i % fen_len])
        if not ret or cbo.fen() != fen_o[i % fen_len]:
            raise Exception("bad test: {} {} {}".format(cbo.fen(), move[i % fen_len], fen_o[i % fen_len]))

    return data


if __name__ == "__main__":
    mpw = mp_work(10, work_func=work_func)
    data_all = []
    print("start")
    for i in range(10):
        data_all.append({
            i: random.random(),
            'time':random.randint(1,100)
        })
    start = time.time()
    mpw.process_data(data=data_all)

    while not mpw.is_done():
        for result in mpw.get_results():
            pass#print(result)
    del mpw
    print(f"done {time.time()-start}")
    
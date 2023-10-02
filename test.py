# -*- coding: utf8 -*-
# coding=utf-8
# python=3.8.18
import time
import chess_board as cb

# 此python文件的用途：测试编译后的pyd文件在指定版本的python中能否正常使用

fen_list = [
    "fen 1rbakab1r/9/6n2/p1N4cp/2n1P1pC1/PcP6/1C4P1P/6N2/9/R1BAKAB1R w - - 0 11"
    "fen 1rbakab1r/9/6n2/p1N4cp/1cn1P1pC1/P1P6/1C4P1P/6N2/9/R1BAKAB1R b - - 0 11",
    "fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1",
    "fen rnbaka2r/9/1c2b3n/p5p1p/9/1C7/P8/B8/9/cN2K4 b - - 0 1"
]

cb.init_env()

s = time.time()
for i in range(150000):
    l = cb.cal_move_actions(fen_list[i%len(fen_list)])
print(time.time()-s)


cbo = cb.ChessBoard()
cbo.do_move("h5f5")
print(cbo.fen())
cbo.flip()
print(cbo.fen())

print(dir(cb))
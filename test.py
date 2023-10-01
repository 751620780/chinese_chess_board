# -*- coding: utf8 -*-
# coding=utf-8
# python=3.8.18
import time
import chess_board as cb

# 此python文件的用途：测试编译后的pyd文件在指定版本的python中能否正常使用
fen_list = [
    "fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1",
    "fen rnbaka2r/9/1c2b3n/p5p1p/9/1C7/P8/B8/9/cN2K4 b - - 0 1"
]

cb.init()
s = time.time()
l=[]
for i in range(162000):
    l = cb.cal_move(fen_list[i%2])
print(time.time()-s)
print(l)
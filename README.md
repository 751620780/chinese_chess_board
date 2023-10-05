# chinese_chess_board
本项目用于计算象棋棋盘下所有的走子可能，使用C++开发，C++代码完全引用自[Pikafish](https://github.com/official-pikafish/Pikafish)开源项目，使用pybind11实现对python语言的绑定

你可以编译后使用python调用生成的pyd文件，即模块
# 拉取代码

1. git clone git@github.com:751620780/chinese_chess_board.git
2. git submodule update --init  --recursive

# 环境搭建和构建程序

1. 安装VS2017/vs2019/VS2022，注意勾选C++开发环境
2. 安装vscode，可以使用使用vscode打开这个目录
3. 安装cmake
4. 安装anaconda并根据需要的python版本搭建一个新的python环境，记住这个python环境路径
5. 修改build.cmd中的python环境的路径
6. 运行build.cmd
7. 在根目录下可看到一个pyd文件，然后可以使用对应版本的python运行test.py文件，测试运行结果

note:如果要运行C++的测试demo，可在命令行运行build_msvc.cmd，将在build_msvc目录下生成.sln的项目文件，使用vs20xx打开即可。当然，此命令将自动编译产生chess_board.exe在此文件夹内。

# 如何使用

1. 将编译后的pyd文件放到你的python代码文件目录下，代码中使用``import chess_board as cb``
2. 使用例子：
```python

# 支持的中国象棋棋盘状态的FEN格式
fen_list = [
    "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w",
    "fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w",
    "fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1"
    "fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1 moves b2b4 h9g7 b0c2",
    "position fen rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1 moves b2b4 h9g7 b0c2",
]
# 对应FEN状态下的移动棋子方式
move_list = ["b2b9","b2b4","b2b9","a6a5","a6a5"]
for fen,move in zip(fen_list,move_list):
    # 提供中国象棋棋盘局面的FEN字符串，创建一个棋盘对象
    cbo = cb.ChessBoard(fen)
    # 计算最后的局面
    print(cbo.fen())
    # 计算当前局面下所有的合法棋子移动方式，如果返回空的列表表示游戏结束
    print(cbo.all_legal_moves())
    # 移动棋子,返回True表示移动棋子成功
    print(cbo.do_move(move))
    # 打印移动棋子后的局面FEN
    print(cbo.fen())
    # 输出当前轮到谁走子，1表示红方，-1表示黑方
    print(cbo.side_to_move())
    # 红黑双方互换棋子
    cbo.flip()
    # 打印互换棋子后的局面FEN
    print(cbo.fen())


```

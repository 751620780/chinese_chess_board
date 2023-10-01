# chinese_chess_board
本项目用于计算象棋棋盘下所有的走子可能，使用C++开发，C++代码完全引用自[Pikafish](https://github.com/official-pikafish/Pikafish)开源项目，使用pybind11实现对python语言的绑定

你可以编译后使用python调用生成的pyd文件，即模块
# 拉取代码

1. git clone 此仓库
2. git submodule update --init  --recursive

# 环境搭建和构建程序

1. 安装VS2017/vs2019/VS2022，注意勾选C++开发环境
2. 安装vscode，可以使用使用vscode打开这个目录
3. 安装cmake
4. 安装anaconda并根据需要的python版本搭建一个新的python环境，记住这个python环境路径
5. 修改build.cmd中的python环境的路径
6. 运行build.cmd
7. 在根目录下可看到一个pyd文件，然后可以使用对应版本的python运行test.py文件，测试运行结果

note:如果要运行C++的demo，可在命令行运行build_msvc.cmd，将在build_msvc目录下生成.sln的项目文件，使用vs20xx打开即可。当然，此命令将自动编译产生chess_board.exe在此文件夹内。
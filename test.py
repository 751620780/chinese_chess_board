# -*- coding: utf8 -*-
# coding=utf-8
# python=3.8.18

import hello_world as hw

# 此python文件的用途：测试编译后的pyd文件在指定版本的python中能否正常使用

print(dir(hw))

print(hw.add(1,2))

s = hw.SomeClass(2.0)

print(s.multiply(5.0))
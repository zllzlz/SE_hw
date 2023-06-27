#pragma once
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<tchar.h>
using namespace std;


/*
* 类型1：sudoku.exe -c 20 [表示生成20个数独终盘]
* 类型2：sudoku.exe -s game.txt [表示从game.txt读取若干个数独游戏,并给出其解答，生成到sudoku.txt中]
* 类型3：sudoku.exe -n 1000 [表示生成1000个数独游戏]
* 类型4：sudoku.exe -n 1000 -m 1 [表示生成1000个简单数游戏，只有m和n一起使用才认为参数无误，否则请报错,m表示生成游戏的难度]
* 类型5：sudoku.exe -n 20 -r 20~55 [表示生成20个挖空数在20到55之间的数独游戏，只有r和n一起使用才认为参数无误，否则请报错]
* 类型6：sudoku.exe -n 20 -u [表示生成20个解唯一的数独游戏,只有u和n一起使用才认为参数无误，否则请报错]
* 类型7：错误输入
*/




//处理输入参数的类
class ArgCheck {
public:
	//初始化函数
	ArgCheck() {};
	ArgCheck(int argc, char* argv[]);

	//分析输入参数
	void analy_Arg();

	//参数输入是否合法
	bool valid_arg();

	//打印参数（调试使用）
	void print_arg();

	//返回参数类型
	int get_ArgType();

	//返回参数值
	int get_c();
	int get_n();
	int get_m();
	int get_r_left();
	int get_r_right();

	string get_filepath();
	

private:
	//参数数量
	int argc;
	//参数字符串
	char** argv;

	//参数类型
	int arg_type;
	//数独终局的个数 1-1000000
	int c;
	//数独游戏的个数 1-10000
	int n;
	//难度 1-3
	int m;
	//挖空的数量 20-55
	int r_left;
	int r_right;

	//求解时读取的文件路径
	string filepath;

};

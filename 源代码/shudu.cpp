#pragma once
#include<iostream>
#include"arg_check.h"
#include"shudu_func.h"
#include"arg_check.cpp"
#include"shudu_func.cpp"
using namespace std;



//生成不重复的数独终局至文件
//生成指令：shudu.exe-c100 
//其他参数：
/*
* sudoku.exe -c 20 [表示生成20个数独终盘]
* sudoku.exe -s game.txt [表示从game.txt读取若干个数独游戏,并给出其解答，生成到sudoku.txt中]
* sudoku.exe -n 1000 [表示生成1000个数独游戏]
* sudoku.exe -n 1000 -m 1 [表示生成1000个简单数游戏，只有m和n一起使用才认为参数无误，否则请报错,m表示生成游戏的难度]
* sudoku.exe -n 20 -r 20~55 [表示生成20个挖空数在20到55之间的数独游戏，只有r和n一起使用才认为参数无误，否则请报错]
* sudoku.exe -n 20 -u [表示生成20个解唯一的数独游戏,只有u和n一起使用才认为参数无误，否则请报错]
*/

int main(int argc, char* argv[]) {
	//参数识别
	ArgCheck arg_check = ArgCheck(argc, argv);
	arg_check.AnalyArg();
	if (!arg_check.ValidArg()) {
		printf("输入有误，请检查输入\n");
		return 0;
	}
	arg_check.PrintArg();

	int type = arg_check.GetArgType();
	ShuDu shudu_op = ShuDu(arg_check);
	//根据识别的参数进行相应的操作
	switch (type) {
		//sudoku.exe -c 20
	case 1:
		shudu_op.GenShuduEnding(arg_check.GetC());
		break;
		//sudoku.exe -s game.txt
	case 2:
		//添加数独游戏的计算
		shudu_op.SolveShuDu(arg_check.GetFilepath());
		break;
		//sudoku.exe -n 1000 
	case 3:
		shudu_op.GenShuduGame(arg_check.GetM());
		break;
		//sudoku.exe -n 1000 -m 1 
	case 4:
		shudu_op.GenShuduGame(arg_check.GetM());
		break;
		//sudoku.exe -n 20 -r 20~55
	case 5:
		shudu_op.GenShuduGame(arg_check.GetRLeft());
		break;
		//sudoku.exe -n 20 -u
	case 6:
		shudu_op.GenShuduGame(arg_check.GetRLeft());
		break;
		//错误输入
	case 7:
		break;
	}

	return 0;
}

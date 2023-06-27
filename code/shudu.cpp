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
	arg_check.analy_Arg();
	if (!arg_check.valid_arg()) {
		printf("输入有误，请检查输入\n");
		return 0;
	}
	arg_check.print_arg();

	int type = arg_check.get_ArgType();
	ShuDu shudu_op = ShuDu(arg_check);
	//根据识别的参数进行相应的操作
	switch (type) {
		//sudoku.exe -c 20
	case 1:
		shudu_op.gen_shudu_ending(arg_check.get_c());
		break;
		//sudoku.exe -s game.txt
	case 2:
		//添加数独游戏的计算
		shudu_op.solve_shudu(arg_check.get_filepath());
		break;
		//sudoku.exe -n 1000 
	case 3:
		shudu_op.gen_shudu_game(arg_check.get_m());
		break;
		//sudoku.exe -n 1000 -m 1 
	case 4:
		shudu_op.gen_shudu_game(arg_check.get_m());
		break;
		//sudoku.exe -n 20 -r 20~55
	case 5:
		shudu_op.gen_shudu_game(arg_check.get_r_left());
		break;
		//sudoku.exe -n 20 -u
	case 6:
		shudu_op.gen_shudu_game(arg_check.get_r_left());
		break;
		//错误输入
	case 7:
		break;
	}

	return 0;
}
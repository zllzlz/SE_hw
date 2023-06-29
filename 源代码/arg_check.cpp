#pragma once
/*
* 类型1：sudoku.exe -c 20 [表示生成20个数独终盘]
* 类型2：sudoku.exe -s game.txt [表示从game.txt读取若干个数独游戏,并给出其解答，生成到sudoku.txt中]
* 类型3：sudoku.exe -n 1000 [表示生成1000个数独游戏]
* 类型4：sudoku.exe -n 1000 -m 1 [表示生成1000个简单数游戏，只有m和n一起使用才认为参数无误，否则请报错,m表示生成游戏的难度]
* 类型5：sudoku.exe -n 20 -r 20~55 [表示生成20个挖空数在20到55之间的数独游戏，只有r和n一起使用才认为参数无误，否则请报错]
* 类型6：sudoku.exe -n 20 -u [表示生成20个解唯一的数独游戏,只有u和n一起使用才认为参数无误，否则请报错]
* 类型7：错误输入
*/
#include "arg_check.h"


ArgCheck::ArgCheck(int argc, char* argv[]) {
	this->argc = argc;
	this->argv = argv;
	this->arg_type = 7;
	this->c = -1;
	this->n = -1;
	this->m = -1;
	this->r_left = -1;
	this->r_right = -1;
	this->filepath = "NONE";
}

//分析参数
void ArgCheck::AnalyArg() {
	if (argc < 3) {
		printf("参数数量过少，请检查输入\n");
		return;
	}
	if (argc == 3) {
		//指令形式：sudoku.exe -c 20
		if (strcmp(argv[1], "-c") == 0) {
			sscanf_s(argv[2], "%d", &c);
			arg_type = 1;
			return;
		}
		//指令形式：sudoku.exe -s game.txt
		if (strcmp(argv[1], "-s") == 0) {
			//printf("-s指令待实现\n");
			filepath = argv[2];
			arg_type = 2;
			return;
		}
		//指令形式：sudoku.exe -n 1000
		if (strcmp(argv[1], "-n") == 0) {
			n = atoi(argv[2]);
			arg_type = 3;
			return;
		}
	}
	//指令形式：sudoku.exe -n 20 -u
	if (argc == 4) {
		n = atoi(argv[2]);
		arg_type = 6;
		return;
	}
	if (argc == 5) {
		//指令形式：sudoku.exe -n 1000 -m 1 
		if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-m") == 0) {
			n = atoi(argv[2]);
			m = atoi(argv[4]);
			arg_type = 4;
			return;
		}
		//指令形式：sudoku.exe -n 20 -r 20~55
		if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-r") == 0) {
			n = atoi(argv[2]);
			char delims[] = "~";
			char* result = NULL;
			char* ptr = NULL;
			result = strtok_s(argv[4], delims, &ptr);
			sscanf_s(result, "%d", &r_left);
			result = strtok_s(NULL, delims, &ptr);
			sscanf_s(result, "%d", &r_right);
			//r_left = atoi(result[0]);
			//r_right = atoi(result[1]);
			arg_type = 5;
			return;
		}
	}
}

//参数输入是否合法
bool ArgCheck::ValidArg() {
	if (arg_type == 7) {
		return 0;
	}
	if (c != -1 && (c < 1 || c>1e6)) {
		printf("不合法的输入c\n");
		return 0;
	}
	if (n != -1 && (n < 1 || n>1e4)) {
		printf("不合法的输入n\n");
		return 0;
	}
	if (m != -1 && (m < 1 || m>3)) {
		printf("不合法的输入m\n");
		return 0;
	}
	if (r_left != -1 && (r_left < 20 || r_left > 55)) {
		printf("不合法的输入rleft\n");
		return 0;
	}
	if (r_right != -1 && (r_right < 20 || r_right > 55)) {
		printf("不合法的输入rright\n");
		return 0;
	}
	if (r_right < r_left) {
		printf("rright应该大于rleft\n");
		return 0;
	}
	return 1;
}

void ArgCheck::PrintArg() {
	printf("参数arg_type:%d\t", arg_type);
	printf("参数c:%d\t", c);
	printf("参数n:%d\t", n);
	printf("参数m:%d\t", m);
	printf("参数r_left:%d\t", r_left);
	printf("参数r_right:%d\t\n", r_right);
	printf("参数filepath:%s\t\n", filepath.c_str());
}

//返回参数类型
int ArgCheck::GetArgType() {
	return this->arg_type;
}

//返回参数值
int ArgCheck::GetC() {
	return this->c;
}

int ArgCheck::GetN() {
	return this->n;
}

int ArgCheck::GetN() {
	return this->m;
}

int ArgCheck::GetRLeft() {
	return this->r_left;
}

int ArgCheck::GetRRight() {
	return this->r_right;
}

string ArgCheck::GetFilepath() {
	return this->filepath;
}

#pragma once
#include<iostream>
#include<vector>
#include <sstream>
#include <fstream>
#include "arg_check.h"


using namespace std;



class ShuDu {
public:
	//初始化函数，直接放入参数分析对象
	ShuDu(ArgCheck arg_check);

	//生成数独终局
	void gen_shudu_ending(int c);

	//生成数独游戏（对生成的数独终局进行挖空）
	void gen_shudu_game(int r);
	void fixed_r_game(int r);

	//生成唯一解的数独游戏
	bool is_only_solution(int row, int col);
	//填入的数字是否符合数独规则
	bool valid_number(int row, int col, int num);
	void gen_onlySolu_game();


	//******求解数独相关函数*******
	// game.txt文件读取
	vector<vector<vector<int>>> read_game_file(string filepath1);
    // 该数字是否合适
    bool isValid(int row, int col, int val, vector<vector<int>>& board);
    //数独求解
    bool backtracking(vector<vector<int>>& board);
	void solve_shudu(string filepath1);


private:
	//参数对象 获取c,n,m等值
	ArgCheck arg_check;
	int c;
	int n;
	//难度：难度1-挖空20个 难度2-挖空35个 难度3-挖空55个. 默认为难度1
	int difficulty;
	//挖空的格子数量 默认为难度1的20个
	int empty_num;
	//挖空格子数量有一定限制
	int r_left;
	int r_right;
	//解是否唯一
	bool only_solution;

	//求解时读取的文件路径
	string filepath;
};


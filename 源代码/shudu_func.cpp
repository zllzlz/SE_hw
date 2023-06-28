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
#include<algorithm>
#include <vector>
#include <string>
#include <random> 
#include <chrono>
#include "shudu_func.h"
#include "arg_check.h"
char matx[2000000] = { 0 };


ShuDu::ShuDu(ArgCheck arg_check) {
	this->arg_check = arg_check;
	this->c = -1;
	this->n = -1;
	this->difficulty = 1;
	this->empty_num = 20;
	this->r_left = -1;
	this->r_right = -1;
	this->only_solution = 0;
	this->filepath = "NONE";

	switch (arg_check.get_ArgType()) {
	case 1:
		this->c = arg_check.get_c();
		break;
	case 2:
		//printf("求解数独待实现。\n");
		this->filepath = arg_check.GetFilepath();
		break;
	case 3:
		this->n = arg_check.get_n();
		this->difficulty = 1;
		this->empty_num = 20;
		break;
	case 4:
		this->n = arg_check.get_n();
		this->difficulty = arg_check.get_m();
		if (this->difficulty == 1) this->empty_num = 20;
		if (this->difficulty == 2) this->empty_num = 35;
		if (this->difficulty == 3) this->empty_num = 55;
		break;
	case 5:
		this->n = arg_check.get_n();
		this->r_left = arg_check.get_r_left();
		this->r_left = arg_check.get_r_right();
		break;
	case 6:
		this->n = arg_check.get_n();
		this->only_solution = 1;
		break;
	default:
		break;
	}
}

//生成数独终局
void ShuDu::gen_shudu_ending(int c = 1) {
	//已经生成的数独终局数目
	if (this->c != -1) {
		c = this->c;
	}
	int create_num = 0;

	//文件写
	for (int i = 0; i < c * 163; i++) {
		matx[i] = '\t';
	}
	FILE* shudu_ending_file;
	errno_t err;
	err = fopen_s(&shudu_ending_file, "shudu.txt", "w");
	if (err) {
		printf("打开文件失败\n");
	}
	//目标生成c个数独终局
	int shift[9] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };

	for (int i = 0; i < 6; i++) {
		if (create_num >= c) {
			matx[create_num * 163] = '\0';
			break;
		}
		if (i) {
			next_permutation(shift + 3, shift + 6);     //交换4~6行的任意两行
			shift[6] = 2, shift[7] = 5, shift[8] = 8;
		}
		for (int j = 0; j < 6; j++) {
			if (create_num >= c) {
				break;
			}
			if (j) {
				next_permutation(shift + 6, shift + 9); //交换7~9行的任意两行
			}

			char row[10] = "712345689";
			for (int k = 0; k < 40320; k++) { //8!排列
				if (create_num >= c) {
					break;
				}
				if (k) {
					next_permutation(row + 1, row + 9); //第一个数字不变
				}
				int m = 0;
				for (int p = 0; p < 9; p++) {
					for (int q = 0; q < 9; q++) {
						matx[m + create_num * 163] = row[(q + shift[p]) % 9];
						m += 2;
					}
					matx[m - 1 + 163 * create_num] = '\n';
				}
				matx[162 + 163 * create_num] = '\n';
				create_num++;
			}
		}
	}
	fputs(matx, shudu_ending_file);
	fclose(shudu_ending_file);
	printf("数独--终局生成完毕，见文件shudu.txt\n");
}


//生成数独游戏-r固定的情况
void ShuDu::fixed_r_game(int r = 20) {
	//先生成数独终局，再挖空
	int c = n;
	gen_shudu_ending(c);
	FILE* fpQues1;
	errno_t err = fopen_s(&fpQues1, "game.txt", "w");
	if (err) {
		printf("打开文件失败\n");
	}
	int temp;
	while (c--) {
		if (arg_check.get_ArgType() == 5)
			temp = r_left + rand() % r_right;
		else
			temp = r;
		while (temp--) {
			int i = rand() % 9;
			int j = rand() % 9;
			if (matx[18 * i + 2 * j + 163 * c] != '0') {
				matx[18 * i + 2 * j + 163 * c] = '0';
			}
			else {
				temp++;
			}
		}
	}
	fputs(matx, fpQues1);
	fclose(fpQues1);
	printf("数独--游戏生成完毕，见文件game.txt\n");
}

//判断数独解是否唯一：回溯法
int board[9][9] = { 0 };
bool ShuDu::valid_number(int row, int col, int num) {
	bool is_valid = 1;
	//列是否有相同数字
	for (int j = 0; j < 9; j++) {
		if (!is_valid) {
			break;
		}
		if (board[row][j] == num) {
			is_valid = 0;
		}
	}
	//行是否有相同数字
	for (int i = 0; i < 9; i++) {
		if (!is_valid) {
			break;
		}
		if (board[i][col] == num) {
			is_valid = 0;
		}
	}
	//三宫格内是否有相同数字
	int start_row = row - row % 3;
	int start_col = col - col % 3;
	for (int i = 0; i < 3; i++) {
		if (!is_valid) {
			break;
		}
		for (int j = 0; j < 3; j++) {
			if (board[start_row + i][start_col + j] == num) {
				is_valid = 0;
			}
		}
	}
	return is_valid;
}

bool ShuDu::is_only_solution(int row, int col) {
	if (col >= 9) {
		col = 0;
		row++;
		if (row >= 9) {
			return 1;
		}
	}
	if (board[row][col] != 0) {
		return is_only_solution(row, col + 1);
	}
	//if(board[row][col] == '0') --> 填入数字，看是否是唯一解
	vector<int> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));
	for (int num = 0; num < 9; num++) {
		int tmp = nums[num];
		if (valid_number(row, col, tmp)) {
			board[row][col] = tmp;
			if (is_only_solution(row, col + 1)) {
				return true;
			}
			board[row][col] = 0;
		}
	}
	return false;
}

void ShuDu::gen_onlySolu_game() {
	for (int i = 0; i < n * 163; i++) {
		matx[i] = '\t';
	}
	//FILE* OnlyFile;
	//errno_t err;
	//err = fopen_s(&OnlyFile, "game_only.txt", "w");
	int k = 0;
	while (k < n) {
		//重新初始化数组
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = 0;
			}
		}
		//生成合适的数独游戏
		if (!is_only_solution(0, 0)) {
			printf("再次尝试\n");
			continue;
		}
		int m = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				string s = to_string(board[i][j]);
				char s1[2] = { 0 };
				strcpy_s(s1, s.c_str());
				matx[m + k * 163] = s1[0];
				//cout << matx[m + k * 163];
				m += 2;
			}
			matx[m - 1 + 163 * k] = '\n';
		}
		matx[162 + 163 * k] = '\n';
		k++;
	}
	matx[163 * k] = '\0';
	fixed_r_game(20);
	//fputs(matx, OnlyFile);
	//fclose(OnlyFile);
	printf("数独--唯一解游戏生成完毕，见文件game.txt\n");
}

//生成数独游戏
void ShuDu::gen_shudu_game(int r = 20) {
	//挖空的数量 默认为20
	if (empty_num != -1) {
		//cout << "empty_num:" << empty_num << endl;
		r = empty_num;
	}
	//判断类型
	//固定的r值----3：sudoku.exe -n 1000或者4：sudoku.exe -n 1000 -m 1 
	if (arg_check.get_ArgType() == 3 || arg_check.get_ArgType() == 4) {
		fixed_r_game(r);
		return;
	}
	//不固定的r值----5：sudoku.exe -n 20 -r 20~55
	if (arg_check.get_ArgType() == 5) {
		//随机生成r : r_left~r_right
		r = r_left + rand() % r_right;
		fixed_r_game(r);
		return;
	}
	//需要有唯一的解----6：sudoku.exe -n 20 -u
	if (arg_check.get_ArgType() == 6) {
		gen_onlySolu_game();
		return;
	}
}


//******求解数独相关函数*******

//读取game.txt文件
vector<vector<vector<int>>> ShuDu::ReadGameFile(string filepath1){
	//string filepath = "game.txt";
	ifstream myfile(filepath1);
	// 判断文件是否存在
	if (myfile.good())
	{
		printf("game.txt文件读取成功...\n");
	}
	else
	{
		printf("游戏文件读取失败，请重试...\n");
	}
	string temp;
	vector<vector<int>> result;
	vector<int> res;

	// 按行读取
	while (getline(myfile, temp))
	{
		stringstream input(temp);
		string out;

		while (getline(input, out, '\t'))
		{
			res.push_back(stoi(out.c_str()));
		}

		result.push_back(res);
		res.clear();
	}

	myfile.close();

	vector<vector<vector<int>>> tmp3;
	vector<vector<int>> tmp2;

	//消除纯换行行
	for (int i = 0; i < result.size(); i++) {
		//cout << result[i].size() << endl;
		if (result[i].size() == 0)
		{
			result.erase(result.begin() + i);
		}
	}

	for (int i = 0; i < result.size(); i++)
	{

		tmp2.push_back(result[i]);
		if ((i + 1) % 9 == 0)
		{
			tmp3.push_back(tmp2);
			tmp2.clear();
		}
	}

	return tmp3;
}

//判断该数字是否合适
bool ShuDu::IsValid(int row, int col, int val, vector<vector<int>>& board) {
	int startRow = (row / 3) * 3;
	int startCol = (col / 3) * 3;
	for (int i = 0; i < board.size(); ++i) {
		if (board[i][col] == val)return false; // 判断行里是否重复
		if (board[row][i] == val)return false; // 判断列里是否重复
		if (board[startRow + i / 3][startCol + i % 3] == val)return false; // 判断9方格里是否重复
	}
	return true;
}

bool ShuDu::BackTracking(vector<vector<int>>& board) {

	//遍历所有网格
	for (int i = 0; i < board.size(); ++i) {        // row
		for (int j = 0; j < board[i].size(); ++j) { // column

			// 索引移动非数字的位置！
			if (board[i][j] != 0) continue;

			//  尝试填入数字1～9。
			for (int ch = 1; ch <= 9; ch++) {
				if (IsValid(i, j, ch, board)) {  //判断是否合法
					board[i][j] = ch;
					if (BackTracking(board)) return true;
				}
			}

			board[i][j] = 0;  // 回溯复原
			return false;
		}
	}

	return true;  //遍历了所有网格，说明所有空都填好了，可以返回了。
}


void ShuDu::SolveShuDu(const string& filepath1){
	//文件读取
	vector<vector<vector<int>>> tmp3 = ReadGameFile(filepath1);

	fstream f;
	//文件写入，会覆盖原来的内容
	f.open("shuduku.txt", ios::out);


	for (int k = 0; k < tmp3.size(); k++)
	{
		//如果找到了符合要求的终局
		if (BackTracking(tmp3[k]))
		{
			// 进行文件的写入
			for (int i = 0; i < tmp3[k].size(); i++) {
				for (int j = 0; j < tmp3[k][i].size(); j++) {
					f << tmp3[k][i][j] << "\t";
				}
				f << endl;
			}
		}
		f << endl;
	}

	f.close();

	printf("数独游戏求解完毕，见文件shuduku.txt\n");
}

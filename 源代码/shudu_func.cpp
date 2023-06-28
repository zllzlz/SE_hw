#pragma once
/*
* ����1��sudoku.exe -c 20 [��ʾ����20����������]
* ����2��sudoku.exe -s game.txt [��ʾ��game.txt��ȡ���ɸ�������Ϸ,�������������ɵ�sudoku.txt��]
* ����3��sudoku.exe -n 1000 [��ʾ����1000��������Ϸ]
* ����4��sudoku.exe -n 1000 -m 1 [��ʾ����1000��������Ϸ��ֻ��m��nһ��ʹ�ò���Ϊ�������󣬷����뱨��,m��ʾ������Ϸ���Ѷ�]
* ����5��sudoku.exe -n 20 -r 20~55 [��ʾ����20���ڿ�����20��55֮���������Ϸ��ֻ��r��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
* ����6��sudoku.exe -n 20 -u [��ʾ����20����Ψһ��������Ϸ,ֻ��u��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
* ����7����������
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
		//printf("���������ʵ�֡�\n");
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

//���������վ�
void ShuDu::gen_shudu_ending(int c = 1) {
	//�Ѿ����ɵ������վ���Ŀ
	if (this->c != -1) {
		c = this->c;
	}
	int create_num = 0;

	//�ļ�д
	for (int i = 0; i < c * 163; i++) {
		matx[i] = '\t';
	}
	FILE* shudu_ending_file;
	errno_t err;
	err = fopen_s(&shudu_ending_file, "shudu.txt", "w");
	if (err) {
		printf("���ļ�ʧ��\n");
	}
	//Ŀ������c�������վ�
	int shift[9] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };

	for (int i = 0; i < 6; i++) {
		if (create_num >= c) {
			matx[create_num * 163] = '\0';
			break;
		}
		if (i) {
			next_permutation(shift + 3, shift + 6);     //����4~6�е���������
			shift[6] = 2, shift[7] = 5, shift[8] = 8;
		}
		for (int j = 0; j < 6; j++) {
			if (create_num >= c) {
				break;
			}
			if (j) {
				next_permutation(shift + 6, shift + 9); //����7~9�е���������
			}

			char row[10] = "712345689";
			for (int k = 0; k < 40320; k++) { //8!����
				if (create_num >= c) {
					break;
				}
				if (k) {
					next_permutation(row + 1, row + 9); //��һ�����ֲ���
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
	printf("����--�վ�������ϣ����ļ�shudu.txt\n");
}


//����������Ϸ-r�̶������
void ShuDu::fixed_r_game(int r = 20) {
	//�����������վ֣����ڿ�
	int c = n;
	gen_shudu_ending(c);
	FILE* fpQues1;
	errno_t err = fopen_s(&fpQues1, "game.txt", "w");
	if (err) {
		printf("���ļ�ʧ��\n");
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
	printf("����--��Ϸ������ϣ����ļ�game.txt\n");
}

//�ж��������Ƿ�Ψһ�����ݷ�
int board[9][9] = { 0 };
bool ShuDu::valid_number(int row, int col, int num) {
	bool is_valid = 1;
	//���Ƿ�����ͬ����
	for (int j = 0; j < 9; j++) {
		if (!is_valid) {
			break;
		}
		if (board[row][j] == num) {
			is_valid = 0;
		}
	}
	//���Ƿ�����ͬ����
	for (int i = 0; i < 9; i++) {
		if (!is_valid) {
			break;
		}
		if (board[i][col] == num) {
			is_valid = 0;
		}
	}
	//���������Ƿ�����ͬ����
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
	//if(board[row][col] == '0') --> �������֣����Ƿ���Ψһ��
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
		//���³�ʼ������
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = 0;
			}
		}
		//���ɺ��ʵ�������Ϸ
		if (!is_only_solution(0, 0)) {
			printf("�ٴγ���\n");
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
	printf("����--Ψһ����Ϸ������ϣ����ļ�game.txt\n");
}

//����������Ϸ
void ShuDu::gen_shudu_game(int r = 20) {
	//�ڿյ����� Ĭ��Ϊ20
	if (empty_num != -1) {
		//cout << "empty_num:" << empty_num << endl;
		r = empty_num;
	}
	//�ж�����
	//�̶���rֵ----3��sudoku.exe -n 1000����4��sudoku.exe -n 1000 -m 1 
	if (arg_check.get_ArgType() == 3 || arg_check.get_ArgType() == 4) {
		fixed_r_game(r);
		return;
	}
	//���̶���rֵ----5��sudoku.exe -n 20 -r 20~55
	if (arg_check.get_ArgType() == 5) {
		//�������r : r_left~r_right
		r = r_left + rand() % r_right;
		fixed_r_game(r);
		return;
	}
	//��Ҫ��Ψһ�Ľ�----6��sudoku.exe -n 20 -u
	if (arg_check.get_ArgType() == 6) {
		gen_onlySolu_game();
		return;
	}
}


//******���������غ���*******

//��ȡgame.txt�ļ�
vector<vector<vector<int>>> ShuDu::ReadGameFile(string filepath1){
	//string filepath = "game.txt";
	ifstream myfile(filepath1);
	// �ж��ļ��Ƿ����
	if (myfile.good())
	{
		printf("game.txt�ļ���ȡ�ɹ�...\n");
	}
	else
	{
		printf("��Ϸ�ļ���ȡʧ�ܣ�������...\n");
	}
	string temp;
	vector<vector<int>> result;
	vector<int> res;

	// ���ж�ȡ
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

	//������������
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

//�жϸ������Ƿ����
bool ShuDu::IsValid(int row, int col, int val, vector<vector<int>>& board) {
	int startRow = (row / 3) * 3;
	int startCol = (col / 3) * 3;
	for (int i = 0; i < board.size(); ++i) {
		if (board[i][col] == val)return false; // �ж������Ƿ��ظ�
		if (board[row][i] == val)return false; // �ж������Ƿ��ظ�
		if (board[startRow + i / 3][startCol + i % 3] == val)return false; // �ж�9�������Ƿ��ظ�
	}
	return true;
}

bool ShuDu::BackTracking(vector<vector<int>>& board) {

	//������������
	for (int i = 0; i < board.size(); ++i) {        // row
		for (int j = 0; j < board[i].size(); ++j) { // column

			// �����ƶ������ֵ�λ�ã�
			if (board[i][j] != 0) continue;

			//  ������������1��9��
			for (int ch = 1; ch <= 9; ch++) {
				if (IsValid(i, j, ch, board)) {  //�ж��Ƿ�Ϸ�
					board[i][j] = ch;
					if (BackTracking(board)) return true;
				}
			}

			board[i][j] = 0;  // ���ݸ�ԭ
			return false;
		}
	}

	return true;  //��������������˵�����пն�����ˣ����Է����ˡ�
}


void ShuDu::SolveShuDu(const string& filepath1){
	//�ļ���ȡ
	vector<vector<vector<int>>> tmp3 = ReadGameFile(filepath1);

	fstream f;
	//�ļ�д�룬�Ḳ��ԭ��������
	f.open("shuduku.txt", ios::out);


	for (int k = 0; k < tmp3.size(); k++)
	{
		//����ҵ��˷���Ҫ����վ�
		if (BackTracking(tmp3[k]))
		{
			// �����ļ���д��
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

	printf("������Ϸ�����ϣ����ļ�shuduku.txt\n");
}

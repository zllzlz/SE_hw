#pragma once
#include<iostream>
#include<vector>
#include <sstream>
#include <fstream>
#include "arg_check.h"


using namespace std;



class ShuDu {
public:
	//��ʼ��������ֱ�ӷ��������������
	ShuDu(ArgCheck arg_check);

	//���������վ�
	void gen_shudu_ending(int c);

	//����������Ϸ�������ɵ������վֽ����ڿգ�
	void gen_shudu_game(int r);
	void fixed_r_game(int r);

	//����Ψһ���������Ϸ
	bool is_only_solution(int row, int col);
	//����������Ƿ������������
	bool valid_number(int row, int col, int num);
	void gen_onlySolu_game();


	//******���������غ���*******
	// game.txt�ļ���ȡ
	vector<vector<vector<int>>> read_game_file(string filepath1);
    // �������Ƿ����
    bool isValid(int row, int col, int val, vector<vector<int>>& board);
    //�������
    bool backtracking(vector<vector<int>>& board);
	void solve_shudu(string filepath1);


private:
	//�������� ��ȡc,n,m��ֵ
	ArgCheck arg_check;
	int c;
	int n;
	//�Ѷȣ��Ѷ�1-�ڿ�20�� �Ѷ�2-�ڿ�35�� �Ѷ�3-�ڿ�55��. Ĭ��Ϊ�Ѷ�1
	int difficulty;
	//�ڿյĸ������� Ĭ��Ϊ�Ѷ�1��20��
	int empty_num;
	//�ڿո���������һ������
	int r_left;
	int r_right;
	//���Ƿ�Ψһ
	bool only_solution;

	//���ʱ��ȡ���ļ�·��
	string filepath;
};


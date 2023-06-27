#pragma once
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<tchar.h>
using namespace std;


/*
* ����1��sudoku.exe -c 20 [��ʾ����20����������]
* ����2��sudoku.exe -s game.txt [��ʾ��game.txt��ȡ���ɸ�������Ϸ,�������������ɵ�sudoku.txt��]
* ����3��sudoku.exe -n 1000 [��ʾ����1000��������Ϸ]
* ����4��sudoku.exe -n 1000 -m 1 [��ʾ����1000��������Ϸ��ֻ��m��nһ��ʹ�ò���Ϊ�������󣬷����뱨��,m��ʾ������Ϸ���Ѷ�]
* ����5��sudoku.exe -n 20 -r 20~55 [��ʾ����20���ڿ�����20��55֮���������Ϸ��ֻ��r��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
* ����6��sudoku.exe -n 20 -u [��ʾ����20����Ψһ��������Ϸ,ֻ��u��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
* ����7����������
*/




//���������������
class ArgCheck {
public:
	//��ʼ������
	ArgCheck() {};
	ArgCheck(int argc, char* argv[]);

	//�����������
	void analy_Arg();

	//���������Ƿ�Ϸ�
	bool valid_arg();

	//��ӡ����������ʹ�ã�
	void print_arg();

	//���ز�������
	int get_ArgType();

	//���ز���ֵ
	int get_c();
	int get_n();
	int get_m();
	int get_r_left();
	int get_r_right();

	string get_filepath();
	

private:
	//��������
	int argc;
	//�����ַ���
	char** argv;

	//��������
	int arg_type;
	//�����վֵĸ��� 1-1000000
	int c;
	//������Ϸ�ĸ��� 1-10000
	int n;
	//�Ѷ� 1-3
	int m;
	//�ڿյ����� 20-55
	int r_left;
	int r_right;

	//���ʱ��ȡ���ļ�·��
	string filepath;

};

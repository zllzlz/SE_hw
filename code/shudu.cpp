#pragma once
#include<iostream>
#include"arg_check.h"
#include"shudu_func.h"
#include"arg_check.cpp"
#include"shudu_func.cpp"
using namespace std;



//���ɲ��ظ��������վ����ļ�
//����ָ�shudu.exe-c100 
//����������
/*
* sudoku.exe -c 20 [��ʾ����20����������]
* sudoku.exe -s game.txt [��ʾ��game.txt��ȡ���ɸ�������Ϸ,�������������ɵ�sudoku.txt��]
* sudoku.exe -n 1000 [��ʾ����1000��������Ϸ]
* sudoku.exe -n 1000 -m 1 [��ʾ����1000��������Ϸ��ֻ��m��nһ��ʹ�ò���Ϊ�������󣬷����뱨��,m��ʾ������Ϸ���Ѷ�]
* sudoku.exe -n 20 -r 20~55 [��ʾ����20���ڿ�����20��55֮���������Ϸ��ֻ��r��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
* sudoku.exe -n 20 -u [��ʾ����20����Ψһ��������Ϸ,ֻ��u��nһ��ʹ�ò���Ϊ�������󣬷����뱨��]
*/

int main(int argc, char* argv[]) {
	//����ʶ��
	ArgCheck arg_check = ArgCheck(argc, argv);
	arg_check.analy_Arg();
	if (!arg_check.valid_arg()) {
		printf("����������������\n");
		return 0;
	}
	arg_check.print_arg();

	int type = arg_check.get_ArgType();
	ShuDu shudu_op = ShuDu(arg_check);
	//����ʶ��Ĳ���������Ӧ�Ĳ���
	switch (type) {
		//sudoku.exe -c 20
	case 1:
		shudu_op.gen_shudu_ending(arg_check.get_c());
		break;
		//sudoku.exe -s game.txt
	case 2:
		//���������Ϸ�ļ���
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
		//��������
	case 7:
		break;
	}

	return 0;
}
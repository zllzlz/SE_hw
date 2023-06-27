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

//��������
void ArgCheck::analy_Arg() {
	if (argc < 3) {
		printf("�����������٣���������\n");
		return;
	}
	if (argc == 3) {
		//ָ����ʽ��sudoku.exe -c 20
		if (strcmp(argv[1], "-c") == 0) {
			sscanf_s(argv[2], "%d", &c);
			arg_type = 1;
			return;
		}
		//ָ����ʽ��sudoku.exe -s game.txt
		if (strcmp(argv[1], "-s") == 0) {
			//printf("-sָ���ʵ��\n");
			filepath = argv[2];
			arg_type = 2;
			return;
		}
		//ָ����ʽ��sudoku.exe -n 1000
		if (strcmp(argv[1], "-n") == 0) {
			n = atoi(argv[2]);
			arg_type = 3;
			return;
		}
	}
	//ָ����ʽ��sudoku.exe -n 20 -u
	if (argc == 4) {
		n = atoi(argv[2]);
		arg_type = 6;
		return;
	}
	if (argc == 5) {
		//ָ����ʽ��sudoku.exe -n 1000 -m 1 
		if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-m") == 0) {
			n = atoi(argv[2]);
			m = atoi(argv[4]);
			arg_type = 4;
			return;
		}
		//ָ����ʽ��sudoku.exe -n 20 -r 20~55
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

//���������Ƿ�Ϸ�
bool ArgCheck::valid_arg() {
	if (arg_type == 7) {
		return 0;
	}
	if (c != -1 && (c < 1 || c>1e6)) {
		printf("���Ϸ�������c\n");
		return 0;
	}
	if (n != -1 && (n < 1 || n>1e4)) {
		printf("���Ϸ�������n\n");
		return 0;
	}
	if (m != -1 && (m < 1 || m>3)) {
		printf("���Ϸ�������m\n");
		return 0;
	}
	if (r_left != -1 && (r_left < 20 || r_left > 55)) {
		printf("���Ϸ�������rleft\n");
		return 0;
	}
	if (r_right != -1 && (r_right < 20 || r_right > 55)) {
		printf("���Ϸ�������rright\n");
		return 0;
	}
	if (r_right < r_left) {
		printf("rrightӦ�ô���rleft\n");
		return 0;
	}
	return 1;
}

void ArgCheck::print_arg() {
	printf("����arg_type:%d\t", arg_type);
	printf("����c:%d\t", c);
	printf("����n:%d\t", n);
	printf("����m:%d\t", m);
	printf("����r_left:%d\t", r_left);
	printf("����r_right:%d\t\n", r_right);
	printf("����filepath:%s\t\n", filepath.c_str());
}

//���ز�������
int ArgCheck::get_ArgType() {
	return this->arg_type;
}

//���ز���ֵ
int ArgCheck::get_c() {
	return this->c;
}

int ArgCheck::get_n() {
	return this->n;
}

int ArgCheck::get_m() {
	return this->m;
}

int ArgCheck::get_r_left() {
	return this->r_left;
}

int ArgCheck::get_r_right() {
	return this->r_right;
}

string ArgCheck::get_filepath() {
	return this->filepath;
}
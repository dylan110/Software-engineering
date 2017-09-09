#pragma once
#include "stdafx.h"
using namespace std;
class sudo
{
public:
	explicit sudo(int id);								//���캯��
	~sudo();									//��������
	void create_sudoku(int id);					//������������
	void print();								//��ӡ
	void init();								//��ʼ��

private:
	ofstream outfile_;							//����ļ�
	int arr_[9][9];								//������������
	int flag_;									//�Ƿ��ÿһ�еĸ�������õı�־
	int first_number_;							//��ĿҪ��ĸ�ѧ���йص���
	bool is_right(int row, int column, int num);//�ж�row��column���Ƿ������num
	vector<int> rand_vector() const;					//�����������
	void fill_number(int num, int row);			//��row��ʼÿһ�п�ʼ���num
	void clean(int i);							//���ʧ�ܣ���i��������������
};


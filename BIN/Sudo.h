#pragma once
#include "stdafx.h"
using namespace std;
class sudo
{
public:
	explicit sudo(int id);								//构造函数
	~sudo();									//析构函数
	void create_sudoku(int id);					//创建数独矩阵
	void print();								//打印
	void init();								//初始化

private:
	ofstream outfile_;							//输出文件
	int arr_[9][9];								//数独矩阵数组
	int flag_;									//是否把每一行的该数都填好的标志
	int first_number_;							//题目要求的跟学号有关的数
	bool is_right(int row, int column, int num);//判断row行column列是否可以填num
	vector<int> rand_vector() const;					//生成随机数组
	void fill_number(int num, int row);			//从row开始每一行开始填充num
	void clean(int i);							//填充失败，把i数清除，重新填过
};


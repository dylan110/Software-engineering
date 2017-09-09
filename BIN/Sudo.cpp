// shudu.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Sudo.h"

sudo::sudo(int id)				//构造函数
{
	outfile_.open("sudoku.txt");//创建/打开文件
	first_number_ = id % 9 + 1;	//按要求得到第一个数
	init();						//初始化
}

sudo::~sudo()		//析构函数
{
	outfile_.close();//关闭文件
}

void sudo::init()				//初始化
{
	memset(arr_, 0, sizeof(arr_));//矩阵清零
	flag_ = false;				//初始化填充成功标志为false
	arr_[0][0] = first_number_;	//把第一个数放进去
}

bool sudo::is_right(int row, int column, int num)
{								//判断所在位置是否可行
	for (auto i = 0; i < 9; i++)
	{							//检查横和列可不可以 
		if (arr_[i][column] == num)
			return false;
	}
	const auto northwest_x = row / 3 * 3;//算小九宫的第一个位置
	const auto northwest_y = column / 3 * 3;
								//检查九宫 
	for (auto i = 0; i < 3; i++)//横向检查
	{							
		for (auto j = 0; j < 3; j++)//竖向检查
		{						
			if (arr_[i + northwest_x][j + northwest_y] == num)
				return false;
		}
	}
	return true;
}

vector<int> sudo::rand_vector() const
//生成随机数组
{
	vector<int> result;
	result.clear();
	for (auto i = 0; i < 9; i++)
		result.push_back(i);

	random_shuffle(result.begin(), result.end());
	return result;
}

void sudo::print()//打印
{
	for (auto i = 0; i < 9; i++)
	{
		outfile_ << arr_[i][0];
		for (auto j = 1; j < 9; j++)
			outfile_ << " " << arr_[i][j];
		outfile_ << endl;
	}
	outfile_ << endl;
}

void sudo::clean(int num)//把矩阵中的num清掉
{
	for (auto i = 0; i < 9; i++)
	{
		for (auto j = 0; j < 9; j++)
		{
			if (arr_[i][j] == num)
			{
				arr_[i][j] = 0;
			}
		}
	}
}
void sudo::create_sudoku(int hhhhhh)//创建数组
{
	fill_number(first_number_, 1);		//先把要求的那个数填进去
	for (auto i = 1; i < 9; i++)		//从1到9开始填充
	{
		if (i == first_number_)		//如果是要求的那个数
			continue;				//则跳过

		fill_number(i, 0);			//逐行填充数i

		if (flag_)					//如果填充好了
			flag_ = false;			//将flag置false，准备下一个数
		else						//如果没填好
		{
			clean(i);				//把上一个数清掉，重填
			i -= 2;					//先-2，待会+1，从上一个数重新开始
		}
	}

	for (auto i = 0; i < 9; i++)		//发现上面填完了之后9是空的
	{
		for (auto j = 0; j < 9; j++)//就写一个循环把9补上
		{
			if (arr_[i][j] == 0)
			{
				arr_[i][j] = 9;
			}
		}
	}
}

void sudo::fill_number(int num, int row)//从row行开始填充num
{
	if (row > 8)						//如果0-8行都填完了
	{
		flag_ = true;					//将填好的标志flag置true
		return;							//返回
	}

	auto temp = rand_vector();		//生成随机数组，
	for (auto i = 0; i < 9; i++)			//从数组第一个数开始测试第row行temp[i]列行不行
	{
		if (arr_[row][temp.at(i)] != 0)//如果这个位置填过了
			continue;					//跳过这列

		if (is_right(row, temp.at(i), num))//如果这个位置可以
		{
			arr_[row][temp.at(i)] = num;	//填上去
			fill_number(num, row + 1);	//填下一个行
			if (flag_)				//如果填好了
				return;				//返回
			arr_[row][temp.at(i)] = 0;//如果这个数这行没不成，把上一行该数置0，换temp下一个数试试
		}
	}
}
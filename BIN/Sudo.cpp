// shudu.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Sudo.h"

sudo::sudo(int id)				//���캯��
{
	outfile_.open("sudoku.txt");//����/���ļ�
	first_number_ = id % 9 + 1;	//��Ҫ��õ���һ����
	init();						//��ʼ��
}

sudo::~sudo()		//��������
{
	outfile_.close();//�ر��ļ�
}

void sudo::init()				//��ʼ��
{
	memset(arr_, 0, sizeof(arr_));//��������
	flag_ = false;				//��ʼ�����ɹ���־Ϊfalse
	arr_[0][0] = first_number_;	//�ѵ�һ�����Ž�ȥ
}

bool sudo::is_right(int row, int column, int num)
{								//�ж�����λ���Ƿ����
	for (auto i = 0; i < 9; i++)
	{							//������пɲ����� 
		if (arr_[i][column] == num)
			return false;
	}
	const auto northwest_x = row / 3 * 3;//��С�Ź��ĵ�һ��λ��
	const auto northwest_y = column / 3 * 3;
								//���Ź� 
	for (auto i = 0; i < 3; i++)//������
	{							
		for (auto j = 0; j < 3; j++)//������
		{						
			if (arr_[i + northwest_x][j + northwest_y] == num)
				return false;
		}
	}
	return true;
}

vector<int> sudo::rand_vector() const
//�����������
{
	vector<int> result;
	result.clear();
	for (auto i = 0; i < 9; i++)
		result.push_back(i);

	random_shuffle(result.begin(), result.end());
	return result;
}

void sudo::print()//��ӡ
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

void sudo::clean(int num)//�Ѿ����е�num���
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
void sudo::create_sudoku(int hhhhhh)//��������
{
	fill_number(first_number_, 1);		//�Ȱ�Ҫ����Ǹ������ȥ
	for (auto i = 1; i < 9; i++)		//��1��9��ʼ���
	{
		if (i == first_number_)		//�����Ҫ����Ǹ���
			continue;				//������

		fill_number(i, 0);			//���������i

		if (flag_)					//���������
			flag_ = false;			//��flag��false��׼����һ����
		else						//���û���
		{
			clean(i);				//����һ�������������
			i -= 2;					//��-2������+1������һ�������¿�ʼ
		}
	}

	for (auto i = 0; i < 9; i++)		//��������������֮��9�ǿյ�
	{
		for (auto j = 0; j < 9; j++)//��дһ��ѭ����9����
		{
			if (arr_[i][j] == 0)
			{
				arr_[i][j] = 9;
			}
		}
	}
}

void sudo::fill_number(int num, int row)//��row�п�ʼ���num
{
	if (row > 8)						//���0-8�ж�������
	{
		flag_ = true;					//����õı�־flag��true
		return;							//����
	}

	auto temp = rand_vector();		//����������飬
	for (auto i = 0; i < 9; i++)			//�������һ������ʼ���Ե�row��temp[i]���в���
	{
		if (arr_[row][temp.at(i)] != 0)//������λ�������
			continue;					//��������

		if (is_right(row, temp.at(i), num))//������λ�ÿ���
		{
			arr_[row][temp.at(i)] = num;	//����ȥ
			fill_number(num, row + 1);	//����һ����
			if (flag_)				//��������
				return;				//����
			arr_[row][temp.at(i)] = 0;//������������û���ɣ�����һ�и�����0����temp��һ��������
		}
	}
}
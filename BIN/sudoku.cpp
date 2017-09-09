// shudu.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "sudo.h"
using namespace std;

bool is_number(string str)
{
	for (auto i = 0; i < str.size(); i++)
	{
		if (str[i]<'0' || str[i]>'9')
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		if (strcmp(argv[1], "-c") == 0)
		{
			if (is_number(argv[2]))
			{
				auto lup = stoi(argv[2]);
				sudo a(3);
				srand(time(nullptr));

				while (lup--)
				{
					a.init();
					a.create_sudoku(3);
					a.print();
				}

				return 0;
			}
		}
	}
	printf("�밴��Լ���ĸ�ʽ���룬����sudoku.exe -c 123");
	return 0;
}
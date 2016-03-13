//练习二，练习一问题扩充  可以控制：是否有乘除，是否有括号，数值范围
//赵承圣 2016.3.11
#include<iostream>
#include<ctime>
#include<string>
using namespace std;

void main()
{
	//数据定义部分
	srand((int)time(NULL));
	int control[2], num_max, num_min, num_num, bracket_num;
	string item[30];
	char symbol[4];                    //随机计算符号数组
	symbol[0] = '+';
	symbol[1] = '-';
	symbol[2] = '*';
	symbol[3] = '/';

	// 输入部分
	cout << "是否有乘除（2 否/4 是）：  ";
	cin >> control[0];
	cout << "是否有括号（1 否/0 是）：  ";
	cin >> control[1];
	cout << "数字最大取值：  ";
	cin >> num_max;
	cout << "数字最小取值：  ";
	cin >> num_min;


	//算式生成部分
	for (int count = 0; count<30; count++)
	{
		num_num = rand() % 10;
		if (num_num == 0 || num_num == 1)
		{
			count--;
			continue;
		}

		//定义并初始化动态数组 num:数字数组  symnum:符号选择数组  sym:符号数组
		int *num = new int[num_num];
		int *symnum = new int[num_num - 1];
		char *sym = new char[num_num - 1];

		int bracket_leftposition, bracket_rightposition;    //定义左、右括号生成的位置
		int *bracket_left_time = new int[num_num];           //定义左、右括号生成次数数组，下标为数字位置
		int *bracket_right_time = new int[num_num];
		string *bracket_left = new string[num_num]();        //定义左右括号字符串型数组
		string *bracket_right = new string[num_num]();
		for (int rcount = 0; rcount<num_num; rcount++)          //左、右括号生成次数初始化
		{
			bracket_left_time[rcount] = 0;
			bracket_right_time[rcount] = 0;
		}

		if (control[1] == 0)
		{
			bracket_num = rand() % 5 + 1;                                    //生成括号次数
			for (int bcount = 0; bcount<bracket_num; bcount++)
			{
				bracket_leftposition = rand() % num_num;                //随机生成左右括号的位置
				bracket_rightposition = rand() % num_num;
				if (bracket_leftposition == bracket_rightposition)     //先剔除部分一次性在一个数左右同时生成左右括号的情况
				{
					break;
				}
				bracket_left_time[bracket_leftposition]++;            //该位置数左括号生成次数+1
				if (bracket_left_time[bracket_leftposition] == 1)
				{
					bracket_left[bracket_leftposition] = "(";
				}
				if (bracket_left_time[bracket_leftposition] == 2)
				{
					bracket_left[bracket_leftposition] = "((";
				}
				if (bracket_left_time[bracket_leftposition] == 3)
				{
					bracket_left[bracket_leftposition] = "(((";
				}
				bracket_rightposition = rand() % num_num;
				bracket_right_time[bracket_rightposition]++;
				if (bracket_right_time[bracket_rightposition] == 1)
				{
					bracket_right[bracket_rightposition] = ")";
				}
				if (bracket_right_time[bracket_rightposition] == 2)
				{
					bracket_right[bracket_rightposition] = "))";
				}
				if (bracket_right_time[bracket_rightposition] == 3)
				{
					bracket_right[bracket_rightposition] = ")))";
				}
				for (int bpcount = 0; bpcount<num_num; bpcount++)            //再次扫描数字左右括号生成次数相等的情况并排除
				{
					if (bracket_left_time[bpcount] == bracket_right_time[bpcount])
					{
						bracket_right[bpcount] = "";
						bracket_left[bpcount] = "";
					}
				}
			}
		}
		//给参与计算的数赋值(指定数值范围)
		for (int cnum = 0; cnum<num_num; cnum++)
		{
			num[cnum] = rand() % (num_max - num_min + 1) + num_min;
		}

		//随机生成式子的各个位置的符号
		for (int snum = 0; snum<num_num - 1; snum++)
		{
			symnum[snum] = rand() % control[0];
			sym[snum] = symbol[symnum[snum]];
		}

		//输出算式
		for (int ph = 0; ph<num_num - 1; ph++)
		{
			cout << bracket_left[ph] << num[ph] << bracket_right[ph] << sym[ph];
		}
		cout << bracket_left[num_num - 1] << num[num_num - 1] << bracket_right[num_num - 1] << endl;

		if (count == 29)
		{
			delete[]num;
			delete[]symnum;
			delete[]sym;
			delete[]bracket_left_time;
			delete[]bracket_right_time;
			delete[]bracket_left;
			delete[]bracket_right;
		}

	}
	system("pause");
}
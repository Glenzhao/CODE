//赵承圣 2016.3.18
#include<iostream>
#include<ctime>
#include<string>
#include<sstream> 
#include "SqStack.h"
using namespace std;

char ops[7] = { '+', '-', '*', '/', '(', ')', '=' };
char cmp[7][7] = { { '>', '>', '<', '<', '<', '>', '>' },
					{ '>', '>', '<', '<', '<', '>', '>' },
					{ '>', '>', '>', '>', '<', '>', '>' },
					{ '>', '>', '>', '>', '<', '>', '>' },
					{ '<', '<', '<', '<', '<', '=', ' ' },
					{ '>', '>', '>', '>', ' ', '>', '>' },
					{ '<', '<', '<', '<', '<', ' ', '=' } };

bool IsOperator(char ch)
{
	for (int i = 0; i < 7; i++)
		if (ch == ops[i])
			return true;
	return false;
}
char Compare(char ch1, char ch2)
{
	int i, m, n;
	char priority;
	for (i = 0; i < 7; i++) { //找到相比较的两个运算符在比较矩阵里的相对位置
		if (ch1 == ops[i])
			m = i;
		if (ch2 == ops[i])
			n = i;
	}
	priority = cmp[m][n];
	return priority;
}

bool Compute(double x, char op, double y, double &z)
{
	switch (op) {
	case '+':	z = x + y;
		break;
	case '-':	z = x - y;
		break;
	case '*':	z = x * y;
		break;
	case '/':	if (fabs(y) > 1e-7) {
		z = x / y;
		break;
	}
				else
					cout << "除数为0，出错！" << endl;
		return false;
	}
	return true;
}

bool ExpEvaluation(char *str, double &result)
{
	double a, b, v;
	char ch, op;
	int temp, i = 0;
	SqStack <char> optr(20);     //创建运算符栈optr
	SqStack <double> opnd(20);   //创建运算数栈opnd
	optr.Push('=');
	ch = str[i++];
	while (ch != '=' || optr.Top() != '=') {
		while (ch == ' ')   //跳过空格
			ch = str[i++];
		if (IsOperator(ch)) {  //是7种运算符之一
			switch (Compare(optr.Top(), ch)) {
			case '<':         //栈顶运算符优先级低
				optr.Push(ch);
				ch = str[i++];
				break;
			case '=':         //脱括号并接收下一字符
				optr.Pop();
				ch = str[i++];
				break;
			case '>':         //栈顶运算符优先级高，退栈并将运算结果入栈
				op = optr.Top();
				optr.Pop();
				b = opnd.Top();
				opnd.Pop();
				a = opnd.Top();
				opnd.Pop();
				if (Compute(a, op, b, v)) { //计算v = a <op> b
					opnd.Push(v);
					break;
				}
				else {
					result = 0;
					return false;
				}
			}
		}
		else {    //是数字
			temp = ch - '0';    //将字符转换为十进制数
			ch = str[i++];
			while (!IsOperator(ch) && ch != ' ') {
				temp = temp * 10 + ch - '0'; //将逐个读入运算数的各位转化为十进制数
				ch = str[i++];
			}
			opnd.Push(temp);    //数值入栈
		}
	}
	result = opnd.Top();
	return true;
}



string IntToString(int & i)
{
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}


void checkcon0(int &num,string chnum)
{
	while(num!=2&&num!=4)
	{
		if(chnum=="否")
		{
			num=2;
		}
		else if(chnum=="是")
		{
			num=4;
		}
		else
		{
			cout<<"输入不合法，请重新输入: ";
			cin>>chnum;
			cout<<endl;
		}
	}
}
void checkcon1(int &num1,string chnum)
{
	while(num1!=1&&num1!=0)
	{
		if(chnum=="否")
		{
			num1=1;
		}
		else if(chnum=="是")
		{
			num1=0;
		}
		else
		{
			cout<<"输入不合法，请重新输入: ";
			cin>>chnum;
			cout<<endl;
		}
	}

}
void check(int &num2,string chnum)
{
	num2 = std::atoi(chnum.c_str() );
	while(num2<=0)
	{
		cout<<"输入不合法，请重新输入: ";
		cin>>chnum;
		cout<<endl;
		num2 = std::atoi(chnum.c_str() );
	}
}

int main()
{
	//数据定义部分
	srand((int)time(NULL));
	int control[2],itemnum, num_max, num_min, num_num, bracket_num;
	string chnum[5];
	string express = "";
	char symbol[4],c[20];;                    //随机计算符号数组
	symbol[0] = '+';
	symbol[1] = '-';
	symbol[2] = '*';
	symbol[3] = '/';

	//输入及判断部分
	cout << "是否有乘除（是/否）：  ";
	cin >> chnum[0];
	checkcon0(control[0],chnum[0]);
	cout << "是否有括号（是/否）：  ";
	cin >> chnum[1];
	checkcon1(control[1],chnum[1]);
	cout << "数字最大取值：  ";
	cin >> chnum[2];
	check(num_max,chnum[2]);
	cout << "数字最小取值：  ";
	cin >> chnum[3];
	check(num_min,chnum[3]);
	cout<<"式子数量： ";
	cin>>chnum[4];
	check(itemnum,chnum[4]);

	string *item=new string[itemnum];
	double *result = new double[itemnum];
	double *uans = new double[itemnum];
	int rightnum = 0;

	//算式生成部分
	for (int count = 0; count<itemnum; count++)
	{
		num_num = rand() % 10;
		string *str = new string[num_num];
		if (num_num == 0 || num_num == 1)
		{
			count--;
			continue;
		}

		//定义并初始化动态数组 num:数字数组  symnum:符号选择数组  sym:符号数组
		int *num = new int[num_num];
		int *symnum = new int[num_num - 1];
		char *sym = new char[num_num - 1];

		int bracket_leftposition, bracket_rightposition;
		int *bracket_left_time = new int[num_num];           //定义左、右括号生成次数数组，下标为数字位置
		int *bracket_right_time = new int[num_num];
		string *bracket_left = new string[num_num]();        //定义左右括号字符串型数组
		string *bracket_right = new string[num_num]();
		for (int rcount = 0; rcount<num_num; rcount++)          //左、右括号生成次数初始化
		{
			bracket_left_time[rcount] = 0;
			bracket_right_time[rcount] = 0;
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


		if (control[1] == 0)
		{
			bracket_num = rand() % 7 + 1;
			//生成括号次数
			for (int bcount = 0; bcount<bracket_num; bcount++)
			{
				bracket_leftposition = rand() % num_num;                //随机生成左右括号的位置
				bracket_rightposition = rand() % num_num;
				if ((bracket_leftposition >= bracket_rightposition)||((bracket_leftposition==0)&&(bracket_rightposition==num_num-1)))     //先剔除部分一次性在一个数左右同时生成左右括号和在整个式子前后生成式子的情况
				{
					continue;
				}
				bracket_left_time[bracket_leftposition]++;            //该位置数左括号生成次数+1
				bracket_right_time[bracket_rightposition]++;
			}
		}
		for (int stnum = 0; stnum < num_num-2; stnum++)
		{
			if ((symbol[symnum[stnum]] == '/') && (symbol[symnum[stnum + 1]] == '/'))
			{
				bracket_left_time[stnum]++;
				bracket_right_time[stnum + 1]++;
			}
		}
		for (int snum = 0; snum < num_num ; snum++)
		{
			
			if (bracket_left_time[snum] == 1)
			{
				bracket_left[snum] = "(";
			}
			if (bracket_left_time[snum] == 2)
			{
				bracket_left[snum] = "((";
			}
			if (bracket_left_time[snum] == 3)
			{
				bracket_left[snum] = "(((";
			}
			if (bracket_right_time[snum] == 1)
			{
				bracket_right[snum] = ")";
			}
			if (bracket_right_time[snum] == 2)
			{
				bracket_right[snum] = "))";
			}
			if (bracket_right_time[snum] == 3)
			{
				bracket_right[snum] = ")))";
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

		//输出算式
		for (int ph = 0; ph<num_num - 1; ph++)
		{
			cout << bracket_left[ph] << num[ph] << bracket_right[ph] << sym[ph];
		}
		cout << bracket_left[num_num - 1] << num[num_num - 1] << bracket_right[num_num - 1] << "= ";

		
		for (int i = 0; i < num_num; i++)
		{
			int &temp = num[i];
			str[i] = IntToString(temp);
		}
		for (int ph = 0; ph<num_num - 1; ph++)
		{
			express =express+bracket_left[ph]+str[ph]+bracket_right[ph]+sym[ph];
		}
		express = express + bracket_left[num_num - 1] +str[num_num - 1]+ bracket_right[num_num - 1];
		item[count] = express+"=";
		
		strcpy(c, item[count].c_str());
		ExpEvaluation(c, result[count]); //求表达式的值
		
		cin >> uans[count];
		if (uans[count] == result[count])
		{
			rightnum++;
			cout << "回答正确" << endl;
		}
		else
		{
			cout << "回答错误" << endl;
			cout << "正确答案是  " << result[count] << endl;
		}
		

		express="";

		if (count == 29)
		{
			delete[]num;
			delete[]symnum;
			delete[]sym;
			delete[]bracket_left_time;
			delete[]bracket_right_time;
			delete[]bracket_left;
			delete[]bracket_right;
			delete[]item;
			delete[]str;
			delete[]result;
		}

	}
	cout << "本次测试共答对 "<< rightnum <<" 道题"<< endl;

	system("pause");
	return 0;
}
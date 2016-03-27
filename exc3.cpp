//�Գ�ʥ 2016.3.18
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
	for (i = 0; i < 7; i++) { //�ҵ���Ƚϵ�����������ڱȽϾ���������λ��
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
					cout << "����Ϊ0������" << endl;
		return false;
	}
	return true;
}

bool ExpEvaluation(char *str, double &result)
{
	double a, b, v;
	char ch, op;
	int temp, i = 0;
	SqStack <char> optr(20);     //���������ջoptr
	SqStack <double> opnd(20);   //����������ջopnd
	optr.Push('=');
	ch = str[i++];
	while (ch != '=' || optr.Top() != '=') {
		while (ch == ' ')   //�����ո�
			ch = str[i++];
		if (IsOperator(ch)) {  //��7�������֮һ
			switch (Compare(optr.Top(), ch)) {
			case '<':         //ջ����������ȼ���
				optr.Push(ch);
				ch = str[i++];
				break;
			case '=':         //�����Ų�������һ�ַ�
				optr.Pop();
				ch = str[i++];
				break;
			case '>':         //ջ����������ȼ��ߣ���ջ������������ջ
				op = optr.Top();
				optr.Pop();
				b = opnd.Top();
				opnd.Pop();
				a = opnd.Top();
				opnd.Pop();
				if (Compute(a, op, b, v)) { //����v = a <op> b
					opnd.Push(v);
					break;
				}
				else {
					result = 0;
					return false;
				}
			}
		}
		else {    //������
			temp = ch - '0';    //���ַ�ת��Ϊʮ������
			ch = str[i++];
			while (!IsOperator(ch) && ch != ' ') {
				temp = temp * 10 + ch - '0'; //����������������ĸ�λת��Ϊʮ������
				ch = str[i++];
			}
			opnd.Push(temp);    //��ֵ��ջ
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
		if(chnum=="��")
		{
			num=2;
		}
		else if(chnum=="��")
		{
			num=4;
		}
		else
		{
			cout<<"���벻�Ϸ�������������: ";
			cin>>chnum;
			cout<<endl;
		}
	}
}
void checkcon1(int &num1,string chnum)
{
	while(num1!=1&&num1!=0)
	{
		if(chnum=="��")
		{
			num1=1;
		}
		else if(chnum=="��")
		{
			num1=0;
		}
		else
		{
			cout<<"���벻�Ϸ�������������: ";
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
		cout<<"���벻�Ϸ�������������: ";
		cin>>chnum;
		cout<<endl;
		num2 = std::atoi(chnum.c_str() );
	}
}

int main()
{
	//���ݶ��岿��
	srand((int)time(NULL));
	int control[2],itemnum, num_max, num_min, num_num, bracket_num;
	string chnum[5];
	string express = "";
	char symbol[4],c[20];;                    //��������������
	symbol[0] = '+';
	symbol[1] = '-';
	symbol[2] = '*';
	symbol[3] = '/';

	//���뼰�жϲ���
	cout << "�Ƿ��г˳�����/�񣩣�  ";
	cin >> chnum[0];
	checkcon0(control[0],chnum[0]);
	cout << "�Ƿ������ţ���/�񣩣�  ";
	cin >> chnum[1];
	checkcon1(control[1],chnum[1]);
	cout << "�������ȡֵ��  ";
	cin >> chnum[2];
	check(num_max,chnum[2]);
	cout << "������Сȡֵ��  ";
	cin >> chnum[3];
	check(num_min,chnum[3]);
	cout<<"ʽ�������� ";
	cin>>chnum[4];
	check(itemnum,chnum[4]);

	string *item=new string[itemnum];
	double *result = new double[itemnum];
	double *uans = new double[itemnum];
	int rightnum = 0;

	//��ʽ���ɲ���
	for (int count = 0; count<itemnum; count++)
	{
		num_num = rand() % 10;
		string *str = new string[num_num];
		if (num_num == 0 || num_num == 1)
		{
			count--;
			continue;
		}

		//���岢��ʼ����̬���� num:��������  symnum:����ѡ������  sym:��������
		int *num = new int[num_num];
		int *symnum = new int[num_num - 1];
		char *sym = new char[num_num - 1];

		int bracket_leftposition, bracket_rightposition;
		int *bracket_left_time = new int[num_num];           //���������������ɴ������飬�±�Ϊ����λ��
		int *bracket_right_time = new int[num_num];
		string *bracket_left = new string[num_num]();        //�������������ַ���������
		string *bracket_right = new string[num_num]();
		for (int rcount = 0; rcount<num_num; rcount++)          //�����������ɴ�����ʼ��
		{
			bracket_left_time[rcount] = 0;
			bracket_right_time[rcount] = 0;
		}

		//��������������ֵ(ָ����ֵ��Χ)
		for (int cnum = 0; cnum<num_num; cnum++)
		{
			num[cnum] = rand() % (num_max - num_min + 1) + num_min;
		}

		//�������ʽ�ӵĸ���λ�õķ���
		for (int snum = 0; snum<num_num - 1; snum++)
		{
			symnum[snum] = rand() % control[0];
			sym[snum] = symbol[symnum[snum]];
		}


		if (control[1] == 0)
		{
			bracket_num = rand() % 7 + 1;
			//�������Ŵ���
			for (int bcount = 0; bcount<bracket_num; bcount++)
			{
				bracket_leftposition = rand() % num_num;                //��������������ŵ�λ��
				bracket_rightposition = rand() % num_num;
				if ((bracket_leftposition >= bracket_rightposition)||((bracket_leftposition==0)&&(bracket_rightposition==num_num-1)))     //���޳�����һ������һ��������ͬʱ�����������ź�������ʽ��ǰ������ʽ�ӵ����
				{
					continue;
				}
				bracket_left_time[bracket_leftposition]++;            //��λ�������������ɴ���+1
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
			for (int bpcount = 0; bpcount<num_num; bpcount++)            //�ٴ�ɨ�����������������ɴ�����ȵ�������ų�
			{
				if (bracket_left_time[bpcount] == bracket_right_time[bpcount])
				{
					bracket_right[bpcount] = "";
					bracket_left[bpcount] = "";
				}
			}
		}

		//�����ʽ
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
		ExpEvaluation(c, result[count]); //����ʽ��ֵ
		
		cin >> uans[count];
		if (uans[count] == result[count])
		{
			rightnum++;
			cout << "�ش���ȷ" << endl;
		}
		else
		{
			cout << "�ش����" << endl;
			cout << "��ȷ����  " << result[count] << endl;
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
	cout << "���β��Թ���� "<< rightnum <<" ����"<< endl;

	system("pause");
	return 0;
}
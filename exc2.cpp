//��ϰ������ϰһ��������  ���Կ��ƣ��Ƿ��г˳����Ƿ������ţ���ֵ��Χ
//�Գ�ʥ 2016.3.11
#include<iostream>
#include<ctime>
#include<string>
using namespace std;

void main()
{
	//���ݶ��岿��
	srand((int)time(NULL));
	int control[2], num_max, num_min, num_num, bracket_num;
	string item[30];
	char symbol[4];                    //��������������
	symbol[0] = '+';
	symbol[1] = '-';
	symbol[2] = '*';
	symbol[3] = '/';

	// ���벿��
	cout << "�Ƿ��г˳���2 ��/4 �ǣ���  ";
	cin >> control[0];
	cout << "�Ƿ������ţ�1 ��/0 �ǣ���  ";
	cin >> control[1];
	cout << "�������ȡֵ��  ";
	cin >> num_max;
	cout << "������Сȡֵ��  ";
	cin >> num_min;


	//��ʽ���ɲ���
	for (int count = 0; count<30; count++)
	{
		num_num = rand() % 10;
		if (num_num == 0 || num_num == 1)
		{
			count--;
			continue;
		}

		//���岢��ʼ����̬���� num:��������  symnum:����ѡ������  sym:��������
		int *num = new int[num_num];
		int *symnum = new int[num_num - 1];
		char *sym = new char[num_num - 1];

		int bracket_leftposition, bracket_rightposition;    //���������������ɵ�λ��
		int *bracket_left_time = new int[num_num];           //���������������ɴ������飬�±�Ϊ����λ��
		int *bracket_right_time = new int[num_num];
		string *bracket_left = new string[num_num]();        //�������������ַ���������
		string *bracket_right = new string[num_num]();
		for (int rcount = 0; rcount<num_num; rcount++)          //�����������ɴ�����ʼ��
		{
			bracket_left_time[rcount] = 0;
			bracket_right_time[rcount] = 0;
		}

		if (control[1] == 0)
		{
			bracket_num = rand() % 5 + 1;                                    //�������Ŵ���
			for (int bcount = 0; bcount<bracket_num; bcount++)
			{
				bracket_leftposition = rand() % num_num;                //��������������ŵ�λ��
				bracket_rightposition = rand() % num_num;
				if (bracket_leftposition == bracket_rightposition)     //���޳�����һ������һ��������ͬʱ�����������ŵ����
				{
					break;
				}
				bracket_left_time[bracket_leftposition]++;            //��λ�������������ɴ���+1
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
				for (int bpcount = 0; bpcount<num_num; bpcount++)            //�ٴ�ɨ�����������������ɴ�����ȵ�������ų�
				{
					if (bracket_left_time[bpcount] == bracket_right_time[bpcount])
					{
						bracket_right[bpcount] = "";
						bracket_left[bpcount] = "";
					}
				}
			}
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

		//�����ʽ
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
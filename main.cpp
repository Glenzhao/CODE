//��ϰһ��Ҫ��ʵ�����Сѧ����������ʽ����֧��һ�����������������
//�Գ�ʥ 2016.3.5
#include<iostream>
#include<ctime>
using namespace std;

void exchange(int &a, int &b)          //����һ����������
{
    int temp = a;
    a = b;
    b = temp;
}

void main()
{
    srand((int)time(NULL));            //ÿ��ִ�����Ӳ�ͬ�����ɲ�ͬ�������
    int num1, num2,num3,snum,snum1;    //�������ͨ���������������������num1,num2,num3���������snum,snum1
    double result;                     //��result���������
    char symbol[4];                    //��������������
    symbol[0] = '+';
    symbol[1] = '-';
    symbol[2] = '*';
    symbol[3] = '/';
    for (int sexp=0; sexp < 20;sexp++) //���Ƽ򵥱��ʽ�ĸ���Ϊ20��
    {
        num1 = rand() % 100;
        num2 = rand() % 100;
        snum = rand() % 4;
        if (num2 == 0 && snum == 3)    //����Ϊ0�Ľ���ų�
            break;
        switch (snum)
        {
        case 0:result = num1 + num2; break;
        case 1:result = num1 - num2; break;
        case 2:result = num1 * num2; break;
        case 3:double dnum1 = (int)num1; double dnum2 = (int)num2; result = dnum1 / dnum2; break;  //�����Ľ����ʾΪdouble��
        }
        cout << num1 << symbol[snum] << num2 << "="<<result<<endl;
    }
    for (int fexp = 0; fexp < 10; fexp++)   //���Ʊ��ʽ�ĸ���Ϊ10��
    {
        num1 = rand() % 100;
        num2 = rand() % 100;
        num3 = rand() % 100;
        snum = rand() % 4;
        snum1 = rand() % 4;
        if ((num2 == 0 && snum == 3)||(num3==0&&snum1==3))      //����Ϊ0�Ľ���ų�
            break;
        if (snum == 3 && num1 > num2)     //��Ϊ�ٷ���������ӷ�ĸ����������exchange����
            exchange(num1,num2);
        if (snum1 == 3 && num2 > num3)
            exchange(num2, num3);
        cout << num1 << symbol[snum] << num2 <<symbol[snum1]<<num3<< "="<< endl;
    }
    system("pause");
}
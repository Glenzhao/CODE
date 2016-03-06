//练习一，要求实现输出小学四则运算表达式，能支持一个真分数的四则运算
//赵承圣 2016.3.5
#include<iostream>
#include<ctime>
using namespace std;

void exchange(int &a, int &b)          //定义一个交换函数
{
    int temp = a;
    a = b;
    b = temp;
}

void main()
{
    srand((int)time(NULL));            //每次执行种子不同，生成不同的随机数
    int num1, num2,num3,snum,snum1;    //定义变量通过随机函数来获得随机数字num1,num2,num3和随机符号snum,snum1
    double result;                     //用result保存计算结果
    char symbol[4];                    //随机计算符号数组
    symbol[0] = '+';
    symbol[1] = '-';
    symbol[2] = '*';
    symbol[3] = '/';
    for (int sexp=0; sexp < 20;sexp++) //控制简单表达式的个数为20个
    {
        num1 = rand() % 100;
        num2 = rand() % 100;
        snum = rand() % 4;
        if (num2 == 0 && snum == 3)    //除数为0的结果排除
            break;
        switch (snum)
        {
        case 0:result = num1 + num2; break;
        case 1:result = num1 - num2; break;
        case 2:result = num1 * num2; break;
        case 3:double dnum1 = (int)num1; double dnum2 = (int)num2; result = dnum1 / dnum2; break;  //将除的结果显示为double型
        }
        cout << num1 << symbol[snum] << num2 << "="<<result<<endl;
    }
    for (int fexp = 0; fexp < 10; fexp++)   //控制表达式的个数为10个
    {
        num1 = rand() % 100;
        num2 = rand() % 100;
        num3 = rand() % 100;
        snum = rand() % 4;
        snum1 = rand() % 4;
        if ((num2 == 0 && snum == 3)||(num3==0&&snum1==3))      //除数为0的结果排除
            break;
        if (snum == 3 && num1 > num2)     //如为假分数，则分子分母交换，调用exchange函数
            exchange(num1,num2);
        if (snum1 == 3 && num2 > num3)
            exchange(num2, num3);
        cout << num1 << symbol[snum] << num2 <<symbol[snum1]<<num3<< "="<< endl;
    }
    system("pause");
}
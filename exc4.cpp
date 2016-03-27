#include<iostream>
using namespace std;

int main()
{
    int i,num;
    cout << "请输入数组元素个数： " ;
    cin >> num;
    int *arr = new int[num];
    cout << "请依次输入数组元素" << endl;
    for (i = 0; i < num; i++)
    {
        cin >> arr[i];
    }
    int MaxSum = 0;
    int CurSum = 0;
    for (i = 0; i<num; i++)
    {
        CurSum += arr[i];
        if (CurSum > MaxSum)
        {
            MaxSum = CurSum;
        }
        if (CurSum < 0)
        {
            CurSum = 0;
        }
    }
    cout <<"该数组中最大子数组的和是： "<< CurSum<<endl;
    system("pause");

    return 0;
}
#include<iostream>
using namespace std;

int main()
{
    int i,num;
    cout << "����������Ԫ�ظ����� " ;
    cin >> num;
    int *arr = new int[num];
    cout << "��������������Ԫ��" << endl;
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
    cout <<"�����������������ĺ��ǣ� "<< CurSum<<endl;
    system("pause");

    return 0;
}
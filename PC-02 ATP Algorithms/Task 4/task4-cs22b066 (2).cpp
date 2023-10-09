#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void twoTrades(vector<double>& A)
{
    int size=A.size();
    double diffArray;
    double maximum=0.0;
    int flag=0;
    double sum=0.0;
    int buy_day=0;
    int sell_day=0;
    for(int index=1; index<size;index++)
    {
        diffArray=A[index]-A[index-1];
        if(sum+diffArray>0&&sum==0.0)
            buy_day=index;
        sum+=diffArray;
        if(sum>0)
        {
            flag=1;
            if(sum>maximum)
            {
                maximum=sum;
                sell_day=index+1;
            }
        }
        else
        sum=0;
    }
    if(flag==0)
    {
    cout<<"No trades result in profit"<<endl;
    return;
    }
    cout<<"Maximum profit = "<<maximum<<endl<<"Buy on day "<<buy_day<<" and sell on day "<<sell_day<<endl;
}

void manyTrades(vector<double>& A)
{
    int size=A.size();
    double diffArray;
    double maximum=0.0;
    int flag=0;
    double sum=0.0;
    vector<int> buy_day;
    vector<int> sell_day;
    double profit=0.0;
    for(int index=1; index<size;index++)
    {
        diffArray=A[index]-A[index-1];
        if(diffArray>=0)
        {
            flag=1;
            if(buy_day.size()==sell_day.size())
            {
                buy_day.push_back(index);
                profit+=diffArray;
            }
            else
            {
                profit+=diffArray;             
            }
        }
        else
        {
            if(buy_day.size()==sell_day.size()+1)
            sell_day.push_back(index);
        }  
    }
    if(buy_day.size()==sell_day.size()+1)
        sell_day.push_back(size);
    if(flag==0)
    {
    cout<<"No trades result in profit"<<endl;
    return;
    }
    cout<<"Maximum profit: "<<profit<<endl;
    for(int index = 0 ; index < buy_day.size(); index++)
    {
        cout<<"Buy on day "<<buy_day[index]<<" and Sell on day "<<sell_day[index]<<endl;
    }
}

double subProfit(double buy, double sell,double x)
{
    return ((sell-buy)-x);
}

void manyTradesFee(vector<double>& A)
{
    double x;
    cin>>x;
    int size=A.size();
    double diffArray;
    double maximum=0.0;
    int flag=0;
    double sum=0.0;
    vector<int> buy_day;
    vector<int> sell_day;
    double profit=0.0;
    for(int index=1; index<size;index++)
    {
        diffArray=A[index]-A[index-1];
        if(diffArray>=0)
        {
            flag=1;
            if(buy_day.size()==sell_day.size())
            {
                buy_day.push_back(index);
                profit+=diffArray;
            }
            else
            {
                profit+=diffArray;             
            }
        }
        else
        {
            if(buy_day.size()==sell_day.size()+1)
            sell_day.push_back(index);
        }  
    }
    if(buy_day.size()==sell_day.size()+1)
        sell_day.push_back(size);
    if(flag==0)
    {
    cout<<"No trades result in profit"<<endl;
    return;
    }
    double buy = A[buy_day[0]-1];
    double sell =A[sell_day[0]-1];
    double subprofit=subProfit(buy,sell,x);
    profit=0.0;
    for(int index = 1 ; index < buy_day.size(); index++)
    {
        if(subProfit(buy,A[sell_day[index]-1],x)>=(subprofit+subProfit(A[buy_day[index]-1],A[sell_day[index]-1],x)))
        {
            subprofit=subProfit(buy,A[sell_day[index]-1],x);
        }
        else
        {
            profit+=subprofit;
            subprofit+=subProfit(A[buy_day[index]-1],A[sell_day[index]-1],x);
            subprofit=0;
            buy=A[buy_day[index]-1];
        }
    }
    profit+=subprofit;
    cout<<"Maximum profit = "<<profit<<endl;
}

int main()
{
    int days;
    cin >> days;
    vector<double> A(days);
    for(int index=0; index<days; index++)
    {
        cin>>A[index];
    }
    // twoTrades(A);
    // manyTrades(A);
    manyTradesFee(A);
    return 0;
}
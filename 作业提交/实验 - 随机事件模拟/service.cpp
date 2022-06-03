#include<iostream>
#include<vector>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<algorithm>
using namespace std;
/****************************************************************************
 * 建立模型表现在时间段 [0,T] 上，有 C 个顾客到某拥有 K 个办事窗口的办事大厅处理事务。
 * 条件:1. 顾客到达时刻 m 在 [0,T] 上服从某种合理的概率分布 X
        2. 顾客处理时长 p 在 (0,L] 内服从某种合理的概率分布 Y
        3. T, C, K, m, p, L 为正整数
        4. X, Y 为概率分布函数
 * 考察目标：对于给定参数 (T, C, K, L, X, Y) 的模型，考察
          1. 顾客平均等待时间
          2. 最大等待人数
          3. 办事大厅关闭时仍未被服务的人数
          4. 其它值得关注的量
          5. 增加顾客忍耐值及固定的顾客忍耐阈值后的情形
          6. 考虑建立合理模型来表达 忍耐值 和 忍耐阈值
****************************************************************************/
unsigned long T,C,K,L;
unsigned long sum_WaitTime=0;
unsigned long max_Waiting;
unsigned long OutTor = 0;
struct customer_type
{
    unsigned long arrive_time=0;
    unsigned long serice_time=1;
    unsigned long max_tolerance=10000;
    bool serviced = false;
    bool operator<(const customer_type& b) const
    {
        return arrive_time < b.arrive_time;
    }
    bool operator>(const customer_type& b) const
    {
        return arrive_time>b.arrive_time;
    }
    bool operator<=(const customer_type& b) const
    {
        return arrive_time <= b.arrive_time;
    }
    bool operator>=(const customer_type& b) const
    {
        return arrive_time >= b.arrive_time;
    }
    friend ostream& operator<<(ostream& out,customer_type b)
    {
        out<<"到达时间为 : "<<b.arrive_time<<" , 需要服务时间为 : "<<b.serice_time;
        return out;
    }
};

struct counter_type
{
    bool free=true;
    unsigned long rest_time=0;
    int serving = 0;

    friend ostream& operator<<(ostream& out, counter_type b)
    {
        if(b.rest_time > 0)
            out<<"正在服务顾客 "<<b.serving<<" , 剩余服务时间为 "<<b.rest_time;
        else
            out<<"空闲状态";
    }
};

bool cmp(customer_type& a, customer_type& b)
{
    return a>b;
}

int main()
{

/*******************************  导入信息  *******************************/
    ifstream input_file;
    input_file.open("input.txt",ios::in);
    input_file>>T>>C>>K>>L;
    vector<customer_type> customer_queue(0);

    // 生成顾客数据
    for(int i=1 ; i<C ; i++)
    {
        customer_type a_customer;
        a_customer.arrive_time = rand()%T;
        a_customer.serice_time = rand()%L+1;
        a_customer.max_tolerance = rand()%(L/3)+(L/2);
        // cout<<a_customer<<endl;
        customer_queue.push_back(a_customer);
    }
    // 生成 K 个服务台
    counter_type counters[K];

    sort(customer_queue.begin(),customer_queue.end(),cmp);
    int customer_index = 0;
    // 顾客信息检查
    // vector<customer_type>::reverse_iterator ritr = customer_queue.rbegin();
    // for(; ritr != customer_queue.rend() ; ritr++)
    //     cout<<*ritr<<endl;
    // cout<<customer_queue.back()<<endl;


/******************************  顾客服务  *********************************/

    for(int ticks=0 ; ticks<=T ; ticks++)
    {
        if(customer_queue.size()==0 or customer_queue.size()>C)
            break;
        printf("===========================第 %d 秒 ==========================\n",ticks);
//////////////////////////////////////////////////////////////////////////////////////////////////////////
        printf("顾客到达情况：");    
        vector<customer_type>::reverse_iterator ritr1=customer_queue.rbegin();
        int arrive_num = 0;
        for(; ritr1!=customer_queue.rend() ; ritr1++)
        {
            customer_type a_customer = *ritr1;
            if(a_customer.arrive_time == ticks)
                arrive_num++;
        }
        cout<<"此时有 "<<arrive_num<<" 名顾客到达店铺"<<endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
        printf("顾客服务情况：\n");
        for(int k=0 ; k<K ; k++)
        {
            if(counters[k].rest_time>0)
            {
                cout<<"Counter "<<k+1<<" : "<<counters[k]<<endl;
                counters[k].rest_time--;
            }
            else
            {
                customer_type current_customer = customer_queue.back();
                if(current_customer.arrive_time > ticks)
                {
                    cout<<"Counter "<<k+1<<" : "<<counters[k]<<endl;
                    continue;
                }
                else
                {
                    if(customer_index>2)
                        printf("Counter %d : 已经完成对顾客 %d 的服务\n",k+1,counters[k].serving);
                    customer_queue.pop_back();
                    counters[k].rest_time = current_customer.serice_time;
                    counters[k].serving = customer_index++;
                    cout<<"Counter "<<k+1<<" : "<<counters[k]<<endl;
                    sum_WaitTime += ticks - current_customer.arrive_time;
                    if(customer_queue.size() == 0) break;
                }
            }
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////
        int waiting = 0;
        vector<customer_type>::reverse_iterator ritr2=customer_queue.rbegin();
        for(; ritr2<customer_queue.rend() ; ritr2++)
        {
            customer_type a_customer = *ritr2;

            if(a_customer.arrive_time < ticks)
            {
                // cout<<a_customer.arrive_time<<"  "<<ticks<<"  "<<customer_queue.size()<<endl;
                waiting++;
                if(a_customer.max_tolerance < ticks - a_customer.arrive_time)
                {
                    customer_queue.erase((++ritr2).base());
                    cout<<"一位顾客由于等待时间过长而离开....."<<endl;
                    OutTor++;
                    waiting--;
                }
            }
            else
                break;
                
        }
        if(max_Waiting < waiting) max_Waiting=waiting;
        // print_status_counters(counters);
        cout<<"今日剩余人数为: "<<customer_queue.size()<<"       ";
        cout<<"当前等待人数为："<<waiting<<endl;
    }

// 查看最后的情况

/******************************  结果统计  *********************************/
    printf("====================================================\n");
    double average_WaitTime = (double)sum_WaitTime/C/60;
    cout<<"平均等待时长为："<<average_WaitTime<<" mins"<<endl;
    cout<<"服务结束后剩余人数为:"<<customer_queue.size()<<endl;
    cout<<"最大等待人数为："<<max_Waiting<<endl;
    cout<<"由于等待时间过长而离开的人数为："<<OutTor<<endl;
    // print_status_counters(counters);

    input_file.close();

    return 0;
}


 
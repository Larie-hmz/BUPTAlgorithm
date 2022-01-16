#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<queue>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;
int n ;
vector<int> x;
vector<int> num;
vector<vector<double>> cost;
void getdata();
int cou = 1;
double lo = 0,up;
class Node{
    
public:
    vector<bool> visit;
    vector<int> que;
    int s;//qi点
    int e;//最后一个点
    int k;//走过的点数
    double sumv;//经过路径的距离
    double lb;//目标函数的值（目标结果）
    bool operator <(const Node &p)const
    {
        return p.lb < lb;//目标函数值小的先出队列
    }
    Node(){
        visit.resize(n+1);
        for(int i = 1;i <= n;i++)
            visit[i] = false;
        s = 1;
        e = 1;
        k = 1;
        sumv = 0;
        que.push_back(0);
        lb = 0;
    };
} ;

priority_queue<Node> q;
//贪心法获取上界
void get_up(){
    vector<bool> visited(n+1);
    vector<double> dis(n+1);
    for(int i = 1; i <= n; i++)
        visited[i] = false;
    visited[x[1]] = true;
    for(int i =1; i <= n;i++)
        dis[i] = cost[x[1]][i];
    
    for(int i = 2; i <= n;i++){
        double min = 99999;
        int tmp = 0;
        for(int j = 2;j <= n;j++){
            if(!visited[j] && dis[j] < min){
                tmp = j;
                min = dis[j];
            }
        }
        visited[tmp] = true;
        up += dis[tmp];
        for(int j = 2;j <= n;j++)
            if(!visited[j] && dis[j] > dis[tmp]+cost[tmp][j])
                dis[j] = dis[tmp]+cost[tmp][j];
    }
}
//获取初始下界
void get_down(){
    for(int i = 1; i <= n;i++){
        vector<double> tmp = cost[i];
        sort(tmp.begin(),tmp.end());
        lo=lo+tmp[0]+tmp[1];
    }
    lo = ceil(lo/2);
}

void getdata(){
    
    cost.resize(n+1);
    for(int i = 1;i <= n;i++)
        cost[i].resize(n+1);
    if(n == 15){
        x = {0,13,2,3,4,5,6,7,8,9,10,11,12,1,14,15};
        num = {0,3,5,7,8,9,10,11,12,13,16,17,19,20,21,22};
        //swap(x[1],x[13]);
        //num = {0,3,5,7,8,9,10,11,12,13,16,17,19,20,21,22};
        
        ifstream inFile("/Users/zoe/Desktop/15.csv", ios::in);
        string line;
        getline(inFile, line);
        getline(inFile, line);
        for(int i = 1;i <= n;i++){
            getline(inFile, line);
            string field;
            istringstream sin(line);
            getline(sin, field, ',');
            getline(sin, field, ',');
            for(int j = 1;j <= n;j++){
                getline(sin, field, ',');
                cost[i][j] = stof(field);
            }
        }
    }
    else if(n == 20){
//        swap(x[1],x[18]);
//        num = {0,1,2,3,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
        x = {0,18,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,1,19,20};
        num = {0,1,2,3,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
        ifstream inFile("/Users/zoe/Desktop/20.csv", ios::in);
        string line;
        getline(inFile, line);
        getline(inFile, line);
        for(int i = 1;i <= n;i++){
            getline(inFile, line);
            string field;
            istringstream sin(line);
            getline(sin, field, ',');
            getline(sin, field, ',');
            for(int j = 1;j <= n;j++){
                getline(sin, field, ',');
                cost[i][j] = stof(field);
            }
        }
    }
    else{
        x = {0,20,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,1,21,22};
        num = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
//        swap(x[1],x[20]);
//        num = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
        ifstream inFile("/Users/zoe/Desktop/22.csv", ios::in);
        string line;
        getline(inFile, line);
        getline(inFile, line);
        for(int i = 1;i <= n;i++){
            getline(inFile, line);
            string field;
            istringstream sin(line);
            getline(sin, field, ',');
            getline(sin, field, ',');
            for(int j = 1;j <= n;j++){
                getline(sin, field, ',');
                cost[i][j] = stof(field);
            }
        }
    }
}
double get_lb(Node N){
    double ret = N.sumv*2;
    double min1 = 99999,min2 = 99999;
    for(int i = 1;i <= n;i++){
        if(N.visit[x[i]] == false && min1 > cost[x[i]][x[N.s]])
            min1 = cost[x[i]][x[N.s]];
    }
    for(int i = 1;i <= n;i++){
        if(N.visit[x[i]] == false && min2 > cost[x[i]][x[N.e]])
            min2 = cost[x[i]][x[N.e]];
    }
    ret = ret+min1+min2;
    for(int i = 1;i <= n;i++){
        if(N.visit[x[i]] == false){
            min1 = 9999;
            min2 = 9999;
            int temp = 0;
            for(int j = 1;j <= n;j++)
                if(min1 > cost[x[i]][j]){
                    min1 = cost[x[i]][j];
                    temp = j;
                }
            for(int j = 1;j <= n;j++){
                if(j == temp)
                    continue;
                if(min2 > cost[x[i]][j])
                    min2 = cost[x[i]][j];}
            ret = ret+min1+min2;
        }
    }
    return ret/2;
}
Node solve(){
    Node ret;
    ret.sumv = 99999;
    get_up();
    get_down();
    Node node;
    node.lb = lo;
    node.visit[x[1]] = true;
    node.que.push_back(x[1]);
    q.push(node);
    while(q.size()>0){
        Node temp = q.top();
        q.pop();
        if(temp.k == n-1){
            
            int p = -1;
            for(int i =1;i <= n;i++){
                if(temp.visit[x[i]] == false){
                    p = i;
                    break;
                }
                    
            }
            cou++;
            temp.que.push_back(x[p]);
            temp.sumv = temp.sumv+cost[x[p]][x[temp.e]]+cost[x[p]][x[temp.s]];
            if(temp.sumv < temp.lb){
                if(ret.sumv < temp.sumv)
                    return ret;
                else
                    return temp;
                }
            else{
                up = min(up,temp.sumv);
                if(ret.sumv > temp.sumv)
                    ret = temp;
                continue;
            }
        }
        else{
            for(int i = 1;i <= n;i++){
                if(!temp.visit[x[i]] && cost[x[i]][x[temp.e]] < 10000){
                    Node child;
                    child.e = i;
                    child.s = temp.s;
                    child.k = temp.k+1;
                    child.sumv = temp.sumv+cost[x[i]][x[temp.e]];
                    child.visit = temp.visit;
                    child.que = temp.que;
                    child.que.push_back(x[i]);
                    child.visit[x[i]] = true;
                    child.lb = get_lb(child);
                    if(child.lb < up){
                        q.push(child);
                        cou++;
                    }
                    }
                    }
                
            }
        }
    return ret;
}
int main(){
    cin>>n;
    getdata();
    time_t begin,end;
    begin=clock();
    Node N = solve();
    end=clock();
    double ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"Runtime:   "<<ret<<endl;
    for(int i = 1;i <= n;i++)
        cout<<num[N.que[i]]<<" ";
    cout<<endl<<"Cost:    "<<N.sumv<<endl;
    cout<<"Node num:    "<<cou<<endl;
    ret = 0;
//    for(int i = 1;i < n;i++){
//        cout<<N.que[i]<<endl;
//        ret+=cost[N.que[i]][N.que[i+1]];}
//    ret+=cost[N.que[n]][N.que[1]];
//    cout<<ret;
//    vector<int> que = {20,17,5,22 ,11, 19 ,8,18 ,6 ,4 ,1 ,10, 21, 14, 12 ,15, 2 ,13, 3, 16, 7 ,9 };
//
//   que = {20 ,9 ,7 ,16, 3 ,13 ,2 ,15 ,12 ,14 ,21 ,10 ,1 ,4, 6, 18 ,8 ,19, 11 ,22 ,5, 17};
//    que = {0,18 ,7 ,5 ,14, 3 ,11 ,2 ,13, 10 ,12 ,19 ,8 ,1, 6, 16, 17 ,9 ,20, 4 ,15};
//    ret = 0;
//    for(int i = 1;i < n;i++){
//        cout<<que[i]<<endl;
//        ret+=cost[que[i]][que[i+1]];}
//    ret+=cost[que[n]][que[1]];
//    cout<<ret;
//    ret = 0;
//    for(int i = 0;i < n-1;i++)
//        ret+=cost[que[i]][que[i+1]];
//    ret+=cost[que[n-1]][0];
//    cout<<ret;
    return 0;
}


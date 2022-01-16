//
//  main.cpp
//  Traveller
//
//  Created by 袁洁 on 2022/1/2.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;
class traveller{
public:
    vector<int> x;
    vector<int> cx;
    vector<int> num;
    vector<vector<double>> arc;
    int n;
    int count = 1;
    double bestc = 99999;
    double cc = 0;
    void backtrack(int i);
    void getdata();
};

int main(int argc, const char * argv[]) {
    traveller T;
    cin>>T.n;
    T.x.resize(T.n+1);
    T.cx.resize(T.n+1);
    for(int i = 1;i <= T.n;i++)
        T.x[i] = i;
    T.getdata();
    time_t begin,end;
    double ret;
    begin=clock();
    T.backtrack(2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"Runtime:   "<<ret<<endl;
    for(int i = 1;i <= T.n;i++)
        cout<<T.num[T.cx[i]]<<" ";
    
    cout<<endl<<"Cost:  "<<T.bestc<<endl;
    cout<<"Node num:    "<<T.count<<endl;
    ret = 0;
    for(int i = 1;i <T.n;i++)
        ret+=T.arc[T.cx[i]][T.cx[i+1]];
    ret+=T.arc[T.cx[T.n]][T.cx[1]];
    cout<<ret;
//    vector<int> que = {20,17,5,22 ,11, 19 ,8,18 ,6 ,4 ,1 ,10, 21, 14, 12 ,15, 2 ,13, 3, 16, 7 ,9 };
//   que = {20 ,9 ,7 ,16, 3 ,13 ,2 ,15 ,12 ,14 ,21 ,10 ,1 ,4, 6, 18 ,8 ,19, 11 ,22 ,5, 17};
//    ret = 0;
//    for(int i = 0;i < T.n-1;i++)
//        ret+=T.arc[que[i]][que[i+1]];
//    ret+=T.arc[que[T.n-1]][0];
//    cout<<ret;
    return 0;
}
void traveller::getdata(){
    arc.resize(n+1);
    for(int i = 1;i <= n;i++)
        arc[i].resize(n+1);
    if(n == 15){
        swap(x[1],x[13]);
        num = {0,3,5,7,8,9,10,11,12,13,16,17,19,20,21,22};
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
                arc[i][j] = stof(field);
            }
        }
        
    }
    else if(n == 20){
        swap(x[1],x[18]);
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
                arc[i][j] = stof(field);
            }
        }
    }
    else{
        swap(x[1],x[20]);
        num = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
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
                arc[i][j] = stof(field);
            }
        }
    }
}
void traveller::backtrack(int i){
    if(i > n){
        if(arc[x[n]][x[1]] != 99999 && (cc+arc[x[n]][x[1]] < bestc || bestc == 99999) ){
            count++;
            for(int j = 1;j <= n;j++)
                cx[j] = x[j];
            bestc = cc+arc[x[n]][x[1]];
        }
    }
    else{
        for(int j = i;j <= n;j++){
            if(arc[x[i-1]][x[j]] != 99999 && cc+arc[x[i-1]][x[j]] < bestc){
                swap(x[i],x[j]);
                cc+=arc[x[i-1]][x[i]];
                count++;
                backtrack(i+1);
                cc-=arc[x[i-1]][x[i]];
                swap(x[i],x[j]);
            }
        }
    }
}

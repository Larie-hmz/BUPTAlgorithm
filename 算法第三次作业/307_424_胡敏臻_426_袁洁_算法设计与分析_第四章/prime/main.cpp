//
//  main.cpp
//  prime
//
//  Created by 袁洁 on 2021/12/7.
//  Copyright © 2021 Nov29. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>
#define DBL_MAX 100000000000
#define SIZE 42
using namespace std;


void getdata(vector<vector<double>> &d,vector<int> &n){
    ifstream inFile("/Users/zoe/Downloads/Desktop/42.csv", ios::in);
    string line;
    string field;
    getline(inFile,line);
    getline(inFile, line);
    istringstream sin(line);
    getline(sin, field, ',');
    getline(sin, field, ',');
    for(int i = 1;i <= SIZE; i++){
        getline(sin, field, ',');
        n[i] = stoi(field.c_str());
    }
    for(int i = 1;i <= SIZE; i++){
        getline(inFile, line);
        istringstream sin(line);
        getline(sin, field, ',');
        getline(sin, field, ',');
        for(int j = 1;j <= SIZE;j++){
            getline(sin, field, ',');
            double u = stof(field.c_str());
            if(abs(u-(-1)) < 1e-6){
                d[i][j] = DBL_MAX;
            }
            else
                d[i][j] = u;
        }
    }
}
double prime( vector<vector<double>> d,map<int,int> &re){
    int index;
    double sum = 0;
    vector<int> visit(SIZE+1,0);
    vector<double> dis(SIZE+1,0);
    vector<int> nei(SIZE+1);
    visit[1] = 1;
    for(int i = 1;i <= SIZE; i++){
        dis[i] = d[1][i];
        nei[i] = 1;
    }
    for(int i = 2;i <= SIZE;i++){
        double mincost = DBL_MAX;
        for(int j = 1;j <= SIZE; j++){
            if(!visit[j] && dis[j] < mincost){
                mincost = dis[j];
                index = j;
            }
        }
        re.insert(make_pair(index,nei[index]));
        visit[index] = true;
        sum+=mincost;
        for(int j = 1;j <= SIZE;j++){
            if(!visit[j] && dis[j] > d[index][j]){
                dis[j] = d[index][j];
                nei[j] = index;
            }
        }
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    vector<vector<double>> d;
    map<int,int> re;
    vector<int> n(SIZE+1);
    d.resize(SIZE+1);
    for(int i = 0; i < d.size(); i++)
        d[i].resize(SIZE+1);
    getdata(d,n);
    double cost = prime(d,re);
    printf("%lf\n",cost);
    for(auto i = re.begin();i != re.end();i++)
        cout<<i->first<<" "<<i->second<<endl;
    return 0;
}

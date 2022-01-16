//
//  main.cpp
//  dijikstra
//
//  Created by 袁洁 on 2021/12/7.
//  Copyright © 2021 Nov29. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
void dijkstra(int l,vector<vector<double>> d,vector<int> n,vector<double> &result,vector<vector<int>> &p){
    int count = 1;
    vector<int> visit(SIZE+1,0);
    while(count < SIZE){
        double u = DBL_MAX-1;
        int um = 0;
        for(int i = 1;i <= SIZE;i++){
            if(result[i]<u && !(visit[i])){
                u = result[i];
                um = i;
            }
        }
        visit[um] = 1;
        count++;
        for(int i = 1;i <= SIZE; i++){
            if(!(visit[i]) && d[i][um] != DBL_MAX&& d[i][um]+u < result[i]){
                result[i] = d[i][um]+u;
                p[i] = p[um];
                p[i].push_back(i);
            }
                
        }
    }
    
}
int main(int argc, const char * argv[]) {
    vector<vector<double>> d;
    vector<vector<int>> p(SIZE+1);
    vector<int> n(SIZE+1);
    vector<double> result(SIZE+1,DBL_MAX);
    d.resize(SIZE+1);
    for(int i = 0; i < d.size(); i++)
        d[i].resize(SIZE+1);
    getdata(d,n);
    int num,l;
    cin>>num;
    for(l = 1;l <= SIZE;l++)
        if(n[l] == num)
            break;
    for(int i = 1;i <= SIZE;i++)
        result[i] = d[l][i];
    for(int i = 1;i <= SIZE;i++){
        p[i].push_back(l);
        p[i].push_back(i);
    }
    dijkstra(l,d,n,result,p);
    for(int i = 0;i < p[3].size();i++)
        cout<<p[3][i]<<" ";
    
    return 0;
}

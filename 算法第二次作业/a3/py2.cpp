//
//  main.cpp
//  polygon
//
//  Created by 袁洁 on 2021/11/21.
//  Copyright © 2021 Nov29. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#define R 6378137
#define DBL_MAX 100000000000
#define Size 19
using namespace std;
double get_distance(double long1,double la1,double long2, double la2){
    if(long1 == long2 && la1 == la2)
        return DBL_MAX;
    double rlo1=long1*M_PI/180;
    double  rlo2=long2*M_PI/180;
    double  rla1=la1*M_PI/180;
    double  rla2=la2*M_PI/180;
    return R*acos(cos(rla1)*cos(rla2)*cos(rlo1-rlo2)+sin(rla1)*sin(rla2));
}
void getdata(vector<vector<double>>& d,vector<vector<double>> &v){
    ifstream inFile("/Users/yuanjie/Downloads/算法设计与分析-编程作业-第3章-2021/附件3-1.21个基站凸多边形数据.csv", ios::in);
    
    double long1,long2,la1,la2;
    string line;
    string field;
    getline(inFile,line);
    getline(inFile, line);
    istringstream sin(line);
    getline(sin, field, ',');
    getline(sin, field, ',');
    long1 = atof(field.c_str());
    getline(sin, field, ',');
    la1 = atof(field.c_str());
    int i = 0;
    d[i][0] = long1;
    d[i][1] = la1;
    while (i <= Size){
        getline(inFile, line);
        string field;
        istringstream sin(line);
        getline(sin, field, ',');
        getline(sin, field, ',');
        long2 = atof(field.c_str());
        getline(sin, field, ',');
        la2 = atof(field.c_str());
        //w.push_back(get_distance(long1, la1, long2, la2));
        la1 = la2;
        long1 = long2;
        i++;
        if(i <= Size){
            d[i][0] = long1;
            d[i][1] = la1;
        }
    }
    for(int i = 0;i <= Size;i++){
        for(int j = 0;j <= Size;j++){
            v[i][j] = get_distance(d[i][0], d[i][1], d[j][0], d[j][1]);
        }
    }
//    for(int i = 0;i <= Size;i++){
//        for(int j = 0;j <= Size;j++){
//            cout<<i<<" "<<j<<" "<<v[i][j]<<endl;
//            //v[i][j] = get_distance(d[i][0], d[i][1], d[j][0], d[j][1]);
//        }
//        cout<<endl;
//    }
}
double wei(int k,int i,int j,int type,vector<vector<double>> v){
    double a = 0;
    a = v[k][j]+v[k][i]+v[i][j];
//    switch (type) {
//        case 1:
//            a = v[i-1][j]+v[i-1][i];
//            break;
//        case 2:
//            a = v[i-1][j];
//            break;
//        case 3:
//            a = v[i-1][j]+v[j-1][j];
//        default:
//            break;
//    }
    return a;
}
void traceback(vector<vector<vector<int>>> s,int flag,int i,int j){
    if(i == j) return ;
    traceback(s, flag,i,s[i][j][flag]);
    traceback(s, flag,s[i][j][flag]+1,j);
    if(flag == 0)
        cout<<"最优剖分：V"<<i-1<<",V"<<j<<":V"<<s[i][j][0]<<endl;
    else
        cout<<"次优剖分：V"<<i-1<<",V"<<j<<":V"<<s[i][j][1]<<endl;
    
}
int main(int argc, const char * argv[]) {
    //vector<double> w;
    vector<vector<vector<double>>> t(Size+1);
    vector<vector<double>> d(Size+1);
    vector<vector<vector<int>>> s(Size+1);
    vector<vector<double>> v(Size+1);
    for(int i = 0;i < t.size();i++){
        t[i].resize(Size+1);
        for(int j = 0;j <= Size;j++)
            t[i][j].resize(2);
        s[i].resize(Size+1);
        for(int j = 0;j <= Size;j++)
            s[i][j].resize(2);
        d[i].resize(2);
        v[i].resize(Size+1);
    }
    
    getdata(d,v);
//    v = {{0,2,2,3,1,4},{2,0,1,5,2,3},{2,1,0,2,1,4},{3,5,2,0,6,2},{1,2,1,6,0,1},{4,3,4,2,1,0}};
    for(int i = 1;i < t.size();i++){
        t[i][i][0] = 0;
        t[i][i][1] = 0;
    }
    for(int r = 2;r <= Size;r++){
        for(int i = 1;i <=Size-r+1;i++){
            int j = i+r-1;
            
            t[i][j][0] = t[i+1][j][0]+wei(i-1,i,j,1,v);//加i-1，i；i-1，j
            if(r != 2)
                t[i][j][0]-=v[i][j];
            s[i][j][0] = i;
            double u = t[i][j-1][0]+wei(i-1,j-1,j,3,v);//加i-1，j；j，j-1
            if(r != 2)
                u-=v[i-1][j-1];
            //cout<<u<<" "<< t[i][j][0]<<endl;
            if(u < t[i][j][0]){
                t[i][j][1] = t[i][j][0];
                s[i][j][1] = s[i][j][0];
                t[i][j][0] = u;
                s[i][j][0] = j-1;
            }
            else{
                t[i][j][1] = u;
                s[i][j][1] = j-1;
            }
            if(r>4){
                int k = ceil((i+j)/2);
                u = t[i][k][0]+t[k+1][j][0]+wei(i-1,k,j,2,v)-v[i-1][k]-v[k][j];//加i-1，j；
                               //cout<<u<<" "<< t[i][j][0]<<endl;
                               if(u < t[i][j][0]){
                                   t[i][j][1] = t[i][j][0];
                                   s[i][j][1] = s[i][j][0];
                                   t[i][j][0] = u;
                                   s[i][j][0] = k;
                               }
                               else if(u < t[i][j][1]){
                                   t[i][j][1] = u;
                                   s[i][j][1] = k;
                               }
            }
            
        }
    }
    printf("%lf %lf\n",t[1][Size][0],t[1][Size][1]);
    traceback(s, 0, 1, Size);
    traceback(s, 1, 1, Size);
    return 0;
}

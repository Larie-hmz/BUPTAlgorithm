//
//  main.cpp
//  bag
//
//  Created by 袁洁 on 2021/11/21.
//  Copyright © 2021 Nov29. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
int main(int argc, const char * argv[]) {
    int n,c;
    cin>>n;//物品数量
    cin>>c;//背包容量
    int *v,*w;
    vector<vector<int>> m(n+1);
    v = new int[n+1];
    w = new int[n+1];
    for(int i = 1;i <= n; i++)
        cin>>v[i];
    for(int i = 1;i <= n; i++)
        cin>>w[i];
    for(int i = 1;i <= n; i++)
        m[i].resize(c+1);
    
//    int jmax = min(w[n]-1,c);
//    for(int j = 0;j <= jmax;j++)
//        m[n][j] = 0;
//    for(int j = w[n];j <= c;j++)
//        m[n][j] = v[n];
//    for(int i = n-1;i > 1;i--){
//        jmax = min(w[i]-1,c);
//        for(int j = 0;j <= jmax;j++)
//            m[i][j] = m[i+1][j];
//        for(int j = w[i];j <= c;j++)
//            m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
//    }
//    m[1][c] = m[2][c];
//    if(c >= w[1]){
//        m[1][c] = max(m[2][c],m[2][c-w[1]]+v[1]);
//    }
//    cout<<m[1][c];
//    vector<int> x(n+1);
//    for(int i = 1;i < n;i++){
//        if(m[i][c] == m[i+1][c])
//            x[i] = 0;
//        else{
//            x[i] = 1;
//            c = c - w[i];
//        }
//    }
//    x[n] = (m[n][c])?1:0;
//    for(int i = 1;i <= n;i++)
//        cout<<x[i]<<' ';
    int jmax = min(w[1]-1,c);
    for(int j = 0;j <= jmax;j++){
        m[1][j] = 0;
    }
    for(int j = w[1];j <= c;j++){
        m[1][j] = v[1];
    }
    for(int i = 2;i <= n-1;i++){
        jmax = min(w[i]-1,c);
        for(int j = 0;j <= jmax;j++)
            m[i][j] = m[i-1][j];
        for(int j = w[i];j <= c;j++)
            m[i][j] = max(m[i-1][j],m[i-1][j-w[i]]+v[i]);
    }
    m[n][c] = m[n-1][c];
    if(c > w[n])
        m[n][c] = max(m[n-1][c],m[n-1][c-w[n]]+v[n]);
    cout<<m[n][c]<<endl;

    vector<int> x(n+1);
    for(int i = n;i > 1;i--){
        if(m[i][c] == m[i-1][c])
            x[i] = 0;
        else{
            x[i] = 1;
            c = c - w[i];
        }
    }
    x[1] = (m[1][c])?1:0;
    for(int i = 1;i <= n;i++)
        cout<<x[i]<<' ';
    return 0;
}

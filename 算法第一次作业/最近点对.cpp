#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;
void getData(vector<vector<double>>& S);
vector<double> cpair2(vector<vector<double>>& S, int l, int r);
int select(vector<vector<double>>& S, int l, int r,int n);
int partition(vector<vector<double>>& S, int l, int r,double x,int flag);
int partition1(vector<vector<double>> S,vector<int>& Z,int p,int r);
void quickSort(vector<vector<double>> S,vector<int>& Z,int p,int r);
int main(int argc, const char * argv[]) {
 vector<vector<double>> S;
 getData(S);
// for(int i=0;i<S.size();i++){
// 	cout<<S[i][0]<<":"<<S[i][1]<<","<<S[i][2]<<"\n";
// }
// int x = select(S, 0, S.size(), ceil(S.size()/2)),y = select(S, 0, S.size(), ceil(S.size()/2)+1);
// double m =
 
 vector<double> result = cpair2(S, 0, S.size()-1);
 
 
 return 0;
}
vector<double> cpair2(vector<vector<double>>& S, int l, int r){
 if(r == l){
 vector<double> result = {0,0,NAN};
 return result;}
 if(r-l == 1){
 vector<double> result = {double(l),double(r),sqrt(pow(S[l][0]-S[r][0],2)+pow(S[l][1]-S[r][1],2))};
 return result;
 
 }
 if(r-l == 2){
 vector<double> result;
 double a = sqrt(pow(S[l][0]-S[r][0],2)+pow(S[l][1]-S[r][1],2));
 double b = sqrt(pow(S[l][0]-S[l+1][0],2)+pow(S[l][1]-S[l+1][1],2));
 double c = sqrt(pow(S[l+1][0]-S[r][0],2)+pow(S[l+1][1]-S[r][1],2));
 if(a < b && a < c )
 result = {double(l),double(r),a};
 else if(b < c)
 result = {double(l),double(l+1),b};
 else
 result = {double(r),double(l+1),c};
 return result;
 }
 int x = select(S,l,r,ceil((r-l)/2)),y = select(S,0,r,ceil((r-l)/2)+1);
 double m = (S[x][1]+S[y][1])/2;
 int i = partition(S,l,r,m,1);
 vector<double> result1,result2,resultm;
 //double d1,d2,dm;
 result1 = cpair2(S, 0, i);
 result2 = cpair2(S, i+1, r);
 if(result1[2] < result2[2])
 resultm = result1;
 else
 resultm = result2;
 vector<int> Z;
 for(int i = l;i < r; i++){
 if(abs(S[i][0]-m)<resultm[2]){
 Z.push_back(i);
 }
 }
 quickSort(S,Z,0,Z.size());
 for(int i = 0; i < Z.size(); i++){
 for(int j = i+1; j < i+6;j++){
 if(S[Z[j]][1]-S[Z[i]][1] < resultm[2]){
 double a = sqrt(pow(S[Z[j]][0]-S[Z[i]][0],2)+pow(S[Z[j]][1]-S[Z[i]][1],2));
 if(a < resultm[2]){
 resultm.clear();
 resultm = {double(Z[j]),double(Z[i]),a};
 }
 }
 }
 }
 return resultm;
}
void quickSort(vector<vector<double>> S,vector<int>& Z,int p,int r){
 if(r>p){
 int q = partition1(S, Z, p, r);
 quickSort(S, Z, p, q);
 quickSort(S, Z, q+1, r);
 }
}
int partition1(vector<vector<double>> S,vector<int>& Z,int p,int r){
 int i = p, j = r-1;
 int x = Z[p];
 while(true){
 while(S[Z[++i]][1] < S[x][1] && i < r);
 while(S[Z[--j]][1] > S[x][1]);
 if(i >= j) break;
 swap(Z[i],Z[j]);
 }
 Z[p] = Z[j];
 Z[j] = x;
 return j;
}
int partition(vector<vector<double>>& S, int p, int r,double x,int flag){
 int i = p, j = r-1,l;
 while(true){
 for(;S[i][0] < x && i < r;i++);
 for(;S[j][0] < x;j++);
 if(i > j)
 break;
 vector<double> temp = S[j];
 S[j] = S[i];
 S[i] = temp;
 }
 if(flag == 0){
 for(l = p; l < r; l++)
 if(S[l][1] == x)
 break;
 vector<double> temp = S[j+1];
 S[j+1] = S[l];
 S[l] = temp;
 }
 
 return j+1;
}
int select(vector<vector<double>>& S, int p, int r,int k){
 if(r == p)
 return p;
 if(r-p < 20){
 //冒泡排序
 for(int i = r-1;i >= p;i--){
 for(int j = p;j <= i-1; j++){
 if(S[j][1] > S[j+1][1]){
 vector<double> temp = S[j];
 S[j] = S[j+1];
 S[j+1] = temp;
 }
 }
 }
 return p+k-1;
 }
 //寻找各组中位数
 // for(int y = p; y < r;y++)
 // cout<<a[y]<<' ';
 // cout<<endl;
 for (int i = 0; i<=(r-p-5)/5; i++ ){
 int s=p + 5*i;
 for(int j = s; j < s+5; j++)
 for(int k = s+4;k > j;k-- )
 if(S[k][1] < S[k-1][1]){
 vector<double> temp = S[k];
 S[k] = S[k-1];
 S[k-1] = temp;
 }
 //cout<<endl;
 vector<double> temp = S[p+i];
 S[p+i] = S[s+2];
 S[s+2] = temp;
 }
 //确定最终中位数
 // for(int y = p; y < r;y++)
 // cout<<a[y]<<' ';
 //cout<<endl;
 
 int x = select(S, p, p+(r-p-5)/5, (r-p+5)/10);
 //x为索引
 int i = partition(S,p,r,S[x][1],0), j = i-p+1;
 if(k == j)
 return i;
 else if(k < j)
 return select(S,p,i,k);
 else
 return select(S, i+1, r, k-j);
 
}
void getData(vector<vector<double>>& S){
ifstream inFile("02-2 tbcell_km1030-v2.csv", ios::in);
 string line;
 string field;
 getline(inFile,line);
 int previous = 0;
 while (getline(inFile, line)){
 string field;
 vector<double> buffer;
 istringstream sin(line);
 getline(sin, field, ',');
 getline(sin, field, ',');
 getline(sin, field, ',');
 int id = atoi(field.c_str());
 if(id != previous){
 buffer.push_back(id);
 //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
 getline(sin, field, ',');
 getline(sin, field, ',');
 getline(sin, field, ',');
 getline(sin, field, ',');
 getline(sin, field, ',');
 getline(sin, field, ',');
 buffer.push_back(atof(field.c_str()));
 getline(sin, field, ',');
 buffer.push_back(atof(field.c_str()));
 S.push_back(buffer);
 }
 previous = id;
 }
 
}

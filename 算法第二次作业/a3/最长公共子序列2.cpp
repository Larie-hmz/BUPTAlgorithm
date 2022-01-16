#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include <algorithm>

using namespace std;

void longest(vector<int>& A,vector<int>& B);
void LCS(int i,int j,vector<int>& A,vector<vector<int>>&b);

void longest(vector<int>& A,vector<int>& B){
	int lena=A.size(),lenb=B.size();
	vector<vector<int>> c(lena+1,vector<int>(lenb+1,0));
	vector<vector<int>> b(lena+1,vector<int>(lenb+1,0));
	
	for(int i=1;i<=lena;i++){
		for(int j=1;j<=lenb;j++){
			if(A[i]==B[j]){
				//cout<<A[i]<<" "<<i<<" "<<j<<"\n";
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=1;
			}
			else if(c[i-1][j]>=c[i][j-1]){
				c[i][j]=c[i-1][j];
				b[i][j]=2;
			}
			else{
				c[i][j]=c[i][j-1];
				b[i][j]=3;
			}
		}
	} 

	LCS(lena,lenb,A,b);
	
	return;
} 

void LCS(int i,int j,vector<int>& A,vector<vector<int>>&b){
	if(i==0||j==0){
		return;
	}
	//if(c[i][j]==c[i-1][j-1]+1){
	if(b[i][j]==1){
		LCS(i-1,j-1,A,b);
		cout<<A[i]<<" ";
	}
	//else if (c[i][j]==c[i-1][j]){
	else if(b[i][j]==2){
		LCS(i-1,j,A,b);
	}
	else{
		LCS(i,j-1,A,b);
	}
}

int main(){
	
	vector<int> a;
	a.push_back(-1);
	vector<int> b;
	b.push_back(-1);
	
	fstream f1;
	f1.open("附件2.最大子段和输入数据-序列1.txt");
	while(!f1.eof()){
		int temp;
		f1>>temp;
		a.push_back(temp);
	}
	f1.close();
	fstream f2;
	f2.open("附件2.最大子段和输入数据-序列2.txt");
	while(!f2.eof()){
		int temp;
		f2>>temp;
		b.push_back(temp);
	}
	f2.close();
	
	vector<int> A=a;
	sort(++a.begin(),a.end(),greater<int>());
//	for(int i=a.size()-1;i>1;i--){
//		if(a[i]==a[i-1]){
//			a.erase(a.begin()+i);
//		}
//	}
	cout<<"序列1的最长递减子序列\n"; 
	longest(A,a) ;

	vector<int> B=b;
	sort(++b.begin(),b.end(),greater<int>());
	cout<<"序列2的最长递减子序列\n"; 
	longest(B,b) ;
	
	return 0;
}

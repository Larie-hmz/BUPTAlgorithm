#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include <algorithm>

using namespace std;

int maxSum(vector<int> &a){
	int maxi=0,maxj=0,tempi=0;
	int maxsum=0,sum=0;
	for(int i=0;i<a.size();i++){
		if(sum>0){
			sum+=a[i];
		}
		else{
			sum=a[i];
			tempi=i;
		}
		if(sum>maxsum){
			maxsum=sum;
			maxi=tempi;
			maxj=i;
		}
	}
	
	cout<<"����ֶκ�"<<maxsum<<"\n" ;
	cout<<"����ֶκ;���λ�ã���a["<<maxi<<"]��a["<<maxj<<"]\n"; 
}

int main(){
	
	vector<int> a;
	vector<int> b;
	
	fstream f1;
	f1.open("����2.����Ӷκ���������-����1.txt");
	while(!f1.eof()){
		int temp;
		f1>>temp;
		a.push_back(temp);
	}
	f1.close();
	fstream f2;
	f2.open("����2.����Ӷκ���������-����2.txt");
	while(!f2.eof()){
		int temp;
		f2>>temp;
		b.push_back(temp);
	}
	f2.close();
	
	cout<<"����1";
	maxSum(a);
	
	cout<<"����2";
	maxSum(b);	 
	
	return 0;
}

#include<cstdio>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<math.h>
#include<ctime> 

using namespace std;
#define size 22
#define color 5

vector<vector<int> > a(size,vector<int>(size,0));
vector<int> x(size,-1);
int sum=0;
long long int count=0;
int flag=0;


bool ok(int k);
void backtrack(int t);
void predata();
void m_coloring(int n,int m,vector<vector<int> >& a,vector<int>& x);

int main(){
	clock_t start_time,end_time;
	predata();
	start_time=clock();
	int i;
//	for(int i=0;i<size;i++){
//		for(int j=0;j<size;j++){
//			cout<<a[i][j]<<" ";
//		}
//		cout<<"\n";
//	}
	for(i=5;i<=size;i++){
		//backtrack(0);	
		m_coloring(size,i,a,x);
		if(flag){
			break;
		}
	}
	cout<<"着色方案为："; 
	for(int i=1;i<size;i++){
		cout<<x[i]<<" ";
	}
	cout<<"\n图的色数为"<<i<<endl;
	end_time=clock();
	//cout<<"总共的方案数："<<sum<<"\n";
	cout<<"搜索过的结点总数"<<count<<"\n"; 
	cout<<"递归所用时间"<<(double)(end_time - start_time) / CLOCKS_PER_SEC <<endl; 
} 

bool ok(int k){
	for(int i=0;i<k;i++){
		if((a[i][k]==1)&&(x[i]==x[k])){
			return false;
		}
	}
	return true;
}

void backtrack(int t){
	if(t>=size){
		sum++;
		for(int i=0;i<size;i++){
			cout<<x[i]<<" ";
		}
		return; 
	}
	else{
		for(int i=0;i<color;i++){
			count++;
			x[t]=i;
			if(ok(t)){
				backtrack(t+1);
			}
		}
	}
}

void predata(){
	float data;
	fstream f;
	f.open("twenty-two.csv",ios::in);
	if(!f){
		cout<<"error!";
		return;
	}
	string line;
	for(int i=0;i<size;i++){
		getline(f, line);
    	istringstream sin(line);
		for(int j=0;j<size;j++){
			string str;
			getline(sin,str,',');
			double data = atof(str.c_str());
			if(data<10000){
				a[i][j]=1;
			}
		} 
	} 
	f.close();
}

void m_coloring(int n,int m,vector<vector<int> >& a,vector<int>& x){
	
	int k=0;
	while(k>=0){
		count++;
		x[k]=x[k]+1;
		while((x[k]<m)&&(!ok(k))){
			x[k]=x[k]+1;
		}
		if(x[k]<m){
			if(k==n-1){
				flag=1;
				break;
			}
			else{
				k++;
			}
		}
		else{
			x[k]=-1;
			k--;
		}
	}
}


#include<iostream>
#include<cstdio>
#include"randoms.h"
#include"quick_sort1.h"
#include"quick_sort2.h"
#include"re_merge.h"
#include"mersort2.h"

//extern int layers=0;
//extern int maxc=0;
#define size 2000

using namespace std;


int main(){
	//int b[size]={1,4,3,5,7};
	vector<int> b;
	b.resize(size);
	randoms(b,size);
	//b={4,3,2,1,5}; 
	for(int k=0;k<1;k++){
//		for(int i=0;i<size;i++){
//			cout<<b[i]<<" ";
//		}
		clock_t start_time,end_time;
		vector<int> c=b;
		start_time=clock();
		layers=0;maxc=0;
		quick_sort1 qs1;
		qs1.QuickSort(c,0,size-1);
		end_time=clock();
		std::cout<<"¿ìÅÅ1µÝ¹é²ãÊý"<<maxc<<"\n";	
		//cout <<(double)end_time <<" "<< start_time<<"\n";
		cout << "¿ìÅÅ1The run time is: "<<(double)(end_time - start_time) / CLOCKS_PER_SEC <<endl;
		
		c=b;
		start_time=clock();
		layers=0;maxc=0;
		quick_sort2 qs2;
		qs2.QuickSort2(c,0,size-1);
		end_time=clock();
		std::cout<<"¿ìÅÅ2µÝ¹é²ãÊý"<<maxc<<"\n";	
		//cout <<(double)end_time <<" "<< start_time<<"\n";
		cout << "¿ìÅÅ2The run time is: " <<(long double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		
		vector<int> d=b;
		start_time=clock();
		layers=0;maxc=0;
		re_merge mer1;
		mer1.sort(d,0,size-1);
		end_time=clock();
		std::cout<<"µÝ¹éºÏ²¢ÅÅÐòµÝ¹é²ãÊý"<<maxc<<"\n";	
		//cout <<(double)end_time <<" "<< start_time<<"\n";
		cout << "µÝ¹éºÏ²¢ÅÅÐòThe run time is: " <<(long double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		
		d=b;
		start_time=clock();
		mersort2 mer2;
		mer2.MergeSort(d,size);
		end_time=clock();
		//std::cout<<"µÝ¹éºÏ²¢ÅÅÐòµÝ¹é²ãÊý"<<maxc<<"\n";	
		//cout <<(double)end_time <<" "<< start_time<<"\n";
		cout << "µÝ¹éÅÅÐòThe run time is: " <<(long double)(end_time - start_time) / CLOCKS_PER_SEC << endl;	
		
//		for(int i=0;i<size;i++){

//			cout<<d[i]<<" ";
//		}	
		
		cout<<"\n";	
//		if(k<4){
//			randoms_shuffle(b,size);		
//		}		
	} 
	return 0;
} 

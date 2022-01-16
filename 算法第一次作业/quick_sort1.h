#include<iostream>
#include<cstdio>
#include"randoms.h"
#include"quick_sort2.h"

//int layers=0;
//int maxc=0;
//#define size 2000

using namespace std;

class quick_sort1{
	
	template<class Type>
	void Swap(Type &a,Type &b ){
		Type c=a;
		a=b;
		b=c;
	}

	template<class Type>
	int Partition(vector<Type>& a,int p,int r){
		int i=p,j=r+1;
		Type x=a[p];
		while(true){
			while(a[++i]<x && i<r);
			while(a[--j]>x);
			if(i>=j) break;
			Swap(a[i],a[j]); 
		}
	//	while(i<j){
	//		while(a[++i]<x && i<r);
	//		while(a[--j]>x);
	//
	//		Swap(a[i],a[j]); 
	//		for(int k=0;k<10;k++){
	//			std::cout<<a[k]<<" ";
	//		}
	//		std::cout<<i<<" "<<j<<" \n";
	//	}
		a[p]=a[j];
		a[j]=x;
		return j;
	}
	
public: 
	template<class Type>
	void QuickSort(vector<Type>& a,int p,int r){
				int i=-1;
		//ÅÐ¶ÏÊÇ·ñÂú×ã·ÇµÝ¼õ 
		for(i=p+1;i<=r;i++){
			if(a[i]<a[i-1]){
				break;
			}
		}
		if(i==r+1){
			return;
		} 
		//ÅÐ¶ÏÊÇ·ñÂú×ã·ÇµÝÔö 
		for(i=p+1;i<=r;i++){
			if(a[i]>a[i-1]){
				break;
			}
		}
		if(i==r+1){
			for(i=p;i<=(r-p-1)/2+p;i++){
				Swap(a[i],a[r-i+p]);
			}
			return;
		}
		if(p<r){
			int q=Partition(a,p,r);
			layers++;
			if(maxc<layers) maxc=layers;
			QuickSort(a,p,q-1);
			QuickSort(a,q+1,r);
			layers--;
		}
	}
};

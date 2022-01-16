#ifndef quick_sort2_h
#define quick_sort2_h
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include"randoms.h" 

class quick_sort2{
	
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
		a[p]=a[j];
		a[j]=x;
		return j;
	}
	
	template<class Type>
	int RandomizedPartition(vector<Type>& a,int p,int r){
		srand(time(NULL));
		int i=rand()%(r-p+1)+p; 
		//std::cout<<i;
		Swap(a[i],a[p]);
		return Partition(a,p,r);
	}
	
public: 
	template<class Type>
	void QuickSort2(vector<Type>& a,int p,int r){
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
			//int q=Partition(a,p,r);
			int q=RandomizedPartition(a,p,r);
			layers++;
			if(maxc<layers) maxc=layers;
			QuickSort2(a,p,q-1);
			QuickSort2(a,q+1,r);
			layers--;
		}
	}
};

#endif

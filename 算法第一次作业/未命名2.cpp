#include<iostream>

int layers=0;
int maxc=0;


void QuickSort(int a[],int p,int r);

int Partition(int a[],int p,int r);

void Swap(int &a,int &b);

int main(){
	int b[10]={100,105,-5,78,32,500,10,350,-88,0};
	QuickSort(b,0,9);
	for(int i=0;i<10;i++){
		std::cout<<b[i]<<" ";
	}
	std::cout<<"\n"<<maxc<<"\n";
	return 0;
} 

int Partition(int a[],int p,int r){
	int i=p,j=r+1;
	int x=a[p];
	while(i<j){
		std::cout<<i<<" "<<j<<"\n";
		while(a[++i]<x && i<r);
		while(a[--j]>x);
		Swap(a[i],a[j]); 
	}
	a[p]=a[j];
	a[j]=x;
	return j;
}


void QuickSort(int a[],int p,int r){
	if(p<r){
		int q=Partition(a,p,r);
		layers++;
		QuickSort(a,p,q-1);
		QuickSort(a,q+1,r);
		
	}
	else if(p==r){
		maxc=layers;
		layers=0;
	}
}

void Swap(int &a,int &b ){
	int c=a;
	a=b;
	b=c;
}

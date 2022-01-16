#ifndef randoms_h
#define randoms_h 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<vector>
#include<algorithm>
using namespace std;

#define N 30000
#define K 3
extern int layers=0;
extern int maxc=0;
double maxadd=0,minadd=0;

template<class Type>
double calculate_add(vector<Type>& a,int size){
	long long int sum=0;
	for(int i=0;i<size-1;i++){
		for(int j=i+1;j<size;j++){
			if(a[j]<a[i]){
				sum++;
			}
		}
	}
	//std::cout<<"DD: "<<sum<<" ADD: "<<(double)sum/size;
	return (double)sum/size;
}

template<class Type>
void randoms_shuffle(vector<Type>& a,int size){
	double add=0;
	do{
		random_shuffle(a.begin(),a.end());
		add=calculate_add(a,size);		
	}
	while(!(add-maxadd>=K||minadd-add>=K));	
	
	if(add-maxadd>=K){
		maxadd=add;
	}
	else if(minadd-add>=K){
		minadd=add;
	}
	
	cout<<"DD: "<<add*size<<" ADD: "<<add<<"\n";
}

template<class Type>
void randoms(vector<Type>& a,int size){
	srand(unsigned(time(NULL)));
	for(int i=0;i<size;i++){
		a[i]=rand()%(1+N);
	}
	maxadd=calculate_add(a,size);	
	minadd=maxadd;
	while(abs(maxadd-500)>=50){
		randoms_shuffle(a,size);
		maxadd=calculate_add(a,size);	
	}
	cout<<"DD: "<<maxadd*size<<" ADD: "<<maxadd<<"\n";
}



#endif

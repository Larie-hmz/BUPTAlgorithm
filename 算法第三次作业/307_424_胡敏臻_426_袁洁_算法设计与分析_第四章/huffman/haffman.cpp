#include<iostream>
#include<fstream>
#include<vector>
#include<map>

using namespace std;
#define Size 37


typedef struct{
	int weight;   //记录权重 
	int parent,lc,rc;  //记录双亲和左右结点 
}HTNode,*HuffmanTree;

void read_files(vector<int>& bianma);
void select(HuffmanTree &HT,int n,int &s1,int &s2);
void create_huff(HuffmanTree &HT,vector<int>& bianma,int n);
void create_hfcode(HuffmanTree &HT,map<int,string> & HFcode, int n);
void print(vector<int>& bianma, map<int,string>& HFcode,int n);
void output(map<int,string>& HFcode,int n);

int main(){
	vector<int> bianma(Size,0);
	read_files(bianma);
	
	//建立哈夫曼树 
	HuffmanTree HT;
	create_huff(HT,bianma,Size);
	
	//哈夫曼编码
	map<int,string> HFcode;
	create_hfcode(HT,HFcode,Size);
	
	print(bianma,HFcode,Size);
	
	output(HFcode,Size);
	return 0;
} 

void read_files(vector<int>& bianma){
	fstream f;
	f.open("input.txt");
	while(!f.eof()){
		char in;
		f >> in;
		if((in-'a'>=0) && (in-'a'<26)){
			bianma[in-'a']++;
		}
		else if((in-'A'>=0) && (in-'A'<26)){
			bianma[in-'A']++;
		}
		else if((in-'0'>=0) && (in-'0'<=9)){
			bianma[in-'0'+26]++;
		}
		else{
			bianma[Size-1]++;
		}
	}
	f.close();
}

void select(HuffmanTree &HT,int n,int &s1,int &s2){
	int minum;
	for(int i=0;i<n;i++){
		if(HT[i].parent==-1){
			minum=i;
			break;
		}
	}
	for(int i=0;i<n;i++){
		if(HT[i].parent==-1){
			if(HT[i].weight<HT[minum].weight){
				minum=i;
			}
		}
	}
	s1=minum;
	for(int i=0;i<n;i++){
		if(HT[i].parent==-1 && i!=s1){
			minum=i;
			break;
		}
	}
	for(int i=0;i<n;i++){
		if(HT[i].parent==-1 && i!=s1){
			if(HT[i].weight<HT[minum].weight){
				minum=i;
			}
		}
	} 
	s2=minum;
}

void create_huff(HuffmanTree &HT,vector<int>& bianma,int n){
	int m,s1,s2;
	m = n * 2 - 1; //总结点
	HT = new HTNode[m];
	for(int i=0;i<n;i++){ //0-n-1存放叶子结点 
		HT[i].weight=bianma[i];
		HT[i].parent=-1;
		HT[i].lc=-1;
		HT[i].rc=-1; 
	} 
	for(int i=n;i<m;i++){ //其余结点 
		HT[i].weight=0;
		HT[i].parent=-1;
		HT[i].lc=-1;
		HT[i].rc=-1;
	}
	for(int i=n;i<m;i++){
		select(HT,i,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lc=s1;
		HT[i].rc=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
		//cout<<"第"<<i-n<<"次："<<HT[i].weight<<"\n";
	}
}

void create_hfcode(HuffmanTree &HT,map<int,string> & HFcode, int n){
	for(int i=0;i<n;i++){
		int par=HT[i].parent;
		int temp=i;
		while(par != -1){
			if(HT[par].lc==temp){
				HFcode[i]='0'+HFcode[i];
			}
			else{
				HFcode[i]='1'+HFcode[i];
			}
			
			temp=par;
			par=HT[par].parent; 
		}
	}
}

void print(vector<int>& bianma, map<int,string>& HFcode,int n){
	int sum=0;
	for(int i=0;i<26;i++){
		cout<< char('a'+i) <<"出现次数" <<bianma[i]<<"\n"; 
		sum+=bianma[i];
	}
	for(int i=26;i<36;i++){
		cout<< char('0'+i-26) <<"出现次数" <<bianma[i]<<"\n"; 
		sum+=bianma[i];
	}
	cout<<"#"<<"出现次数" <<bianma[n-1]<<"\n"; 
	sum+=bianma[n-1];
	cout<<"总共有"<<sum<<"字符\n"; 
	
	for(int i=0;i<26;i++){
		cout<< char('a'+i) <<"哈夫曼编码" <<HFcode[i]<<"\n"; 
	}
	for(int i=26;i<36;i++){
		cout<< char('0'+i-26) <<"哈夫曼编码" <<HFcode[i]<<"\n"; 
	}
	cout<< "#" <<"哈夫曼编码" <<HFcode[n-1]<<"\n"; 
}

void output(map<int,string>& HFcode,int n){
	fstream f1;
	f1.open("input.txt");
	long long int sum=0;
	long long int count=0;
	
	while(!f1.eof()){
		char temp;
		f1 >> temp;
		count++;
		if((temp-'a'>=0) && (temp-'a'<26)){
			sum+= HFcode[temp-'a'].size();
		}
		else if((temp-'A'>=0) && (temp-'A'<26)){
			sum+= HFcode[temp-'A'].size();
		}
		else if((temp-'0'>=0) && (temp-'0'<=9)){
			sum+= HFcode[temp-'0'+26].size();
		}
		else{
			sum+= HFcode[n-1].size();
		}
	}
	
	f1.close();
	
	cout<<"哈夫曼编码存储比特数"<<sum<<"\n"; 
	cout<<"定长编码存储比特数"<<count*6<<"\n"; 
}



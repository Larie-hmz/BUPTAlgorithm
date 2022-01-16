#include"randoms.h" 
class mersort2{
public:
	void MergeSort(vector<int>& a, int n){
		int i=-1;
        //ÅÐ¶ÏÊÇ·ñÂú×ã·ÇµÝ¼õ
        for(i=0;i<=n-1;i++){
            if(a[i]<a[i-1]){
                break;
            }
        }
        if(i==n){
            return;
        }
        //ÅÐ¶ÏÊÇ·ñÂú×ã·ÇµÝÔö
        for(i=1;i<=n-1;i++){
            if(a[i]>a[i-1]){
                break;
            }
        }
        if(i==n){
            for(i=0;i<=(n-2)/2;i++){
                swap(a[i],a[n-1-i]);
            }
            return;
        }
	    vector<int> b;
	    b.resize(n);
	    int s = 1;
	    while(s < n){
	        MergePass(a,b,s,n);
	        s+=s;
	        MergePass(b,a,s,n);
	        s+=s;
	    }
	}
	void MergePass(vector<int>& x, vector<int>& y, int s, int n){
	    int i = 0;
	    while(i <= n - 2 * s){
	        Merge(x, y, i, i+s-1, i+2*s-1);
	        i+=2*s;
	    }
	    if(i < n-s){
	        Merge(x, y, i, i+s-1, n-1);
	    }
	    else{
	        for(int j = i;j <= n-1;j++)
	            y[j] = x[j];
	    }
	}
	void Merge(vector<int>& c,vector<int>& d,int l,int m,int r){
	    int i = l, j = m + 1, k = l;
	    while(i <= m && j <=r )
	        if(c[i] <= c[j])
	            d[k++] = c[i++];
	        else
	            d[k++] = c[j++];
	    if(i > m){
	        for(int q = j;q <= r;q++){
	            d[k++] = c[q];
	            
	        }
	    }
	    else{
	        for(int q = i;q <= m;q++)
	            d[k++] = c[q];
	    }
	}
}; 

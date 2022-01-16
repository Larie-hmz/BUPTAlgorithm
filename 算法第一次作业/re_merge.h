//int layer = 0,maxl = 0;
#include"randoms.h" 
class re_merge{
	vector<int> c;
	void copy(vector<int>& a, vector<int>& c, int left,int right)
	{
	    for (int i = left; i<= right; i++)
	        a[i] = c[i];
	}
	void meg(vector<int>& a, vector<int>& c, int l, int m, int r)
	{
	    int i = l, j = m + 1, k = l;
	    while ((i <= m) && (j <= r))
	    {
	        if (a[i] <a[j])
	            c[k++] = a[i++];
	        else
	            c[k++] = a[j++];
	    }
	 
	    while (i <= m)
	        c[k++] = a[i++];
	    while (j <= r)
	        c[k++] = a[j++];
	    
	}
public:
	int sort(vector<int>& a ,int left , int right)
	{
	    //int* b = new int[right + 1 -left];
	    //vector<int> c;
	    c.clear();
	    c.resize(right + 1 -left);
	    
	    int i=-1;
        //ÅÐ¶ÏÊÇ·ñÂú×ã·ÇµÝ¼õ
        for(i=left+1;i<=right;i++){
            if(a[i]<a[i-1]){
                break;
            }
        }
        if(i==right+1){
            return 0;
        }
        //ÅÐ¶ÏÊÇ·ñÂú×ã·ÇµÝÔö
        for(i=left+1;i<=right;i++){
            if(a[i]>a[i-1]){
                break;
            }
        }
        if(i==right+1){
            for(i=left;i<=(right-left-1)/2+left;i++){
                swap(a[i],a[right-i+left]);
            }
            return 0;
        }
	    
	    if (left < right)
	    {
	        int i = (left + right) / 2;
	        layers++;
	        if(maxc < layers)
	            maxc = layers;
	        sort(a, left, i);
	        sort(a,i + 1, right);
	        layers--;
	        meg(a, c, left, i, right);
	        copy(a, c, left, right);
	    }
	    //free(b);
	    return maxc;
	}
};

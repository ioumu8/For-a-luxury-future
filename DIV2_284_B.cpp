#include<cstdio>
#include<cstring>




char s[2][11];
char keep[10001][11];
int table[11]={153,241,423,165,447,1342,5434,6742,1245,2345,8934};

int hash(){
	int sum=0;
	for(int i=0;s[0][i]!=0;++i){
		sum=(sum+s[0][i]*table[i])%10000;
	}
	return sum;
}

void Insert(bool ok){
	int sum=hash();
	if(ok)
		for(int i=0;s[0][i]!=0;++i)
			keep[sum][i]=s[0][i];
	else
		for(int i=0;s[1][i]!=0;++i)
			keep[sum][i]=s[1][i];
}

int main(){
	int n,m;
	memset(s,0,sizeof(0));
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;++i){
		scanf("%s %s",s[0],s[1]);
		int len1,len2;
		len1=strlen(s[0]);
		len2=strlen(s[1]);
		Insert(len1<=len2?1:0);
	}
	for(int i=0;i<n;++i){
		scanf("%s",s[0]);
		int sum=hash();
		printf("%s ",keep[sum]);
	}
	printf("\n");
	
	return 0;	
}

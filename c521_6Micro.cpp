#include<cstdio>

int main(){
	int N,M,K;
	int light[200001];
	int sum=0;
	int i;
	scanf("%d %d %d",&N,&M,&K);
	for(int i=0;i<N;++i)
		scanf("%d",&light[i]);
	if(N<2*K+1)
		 i = N/2;
	else if(N%(2*K+1)==0) 
		i = K;
	else
		 i = 0;
	for(i;i<N;i+=(2*K+1))
		sum+=light[i];
		
	printf("%d\n",sum);
	
return 0;	
}

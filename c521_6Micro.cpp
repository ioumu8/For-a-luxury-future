#include<cstdio>

int main(){
	int N,M,K;
	int light[200001];
	int sum=0;
	scanf("%d %d %d",&N,&M,&K);
	for(int i=0;i<N;++i)
		scanf("%d",&light[i]);
	if(N<2*K+1){sum=light[N/2];}
	else if(N%(2*K+1)==0)
		for(int i=K;i<N;i+=(2*K+1)){
			sum+=light[i];	
		}
	else{
		sum+=light[0];
		for(int i=2*K+1;i<N;i+=(2*K+1))
			sum+=light[i];
	}
	printf("%d\n",sum);
	
return 0;	
}

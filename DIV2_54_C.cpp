#include<cstdio>
#include<cmath>

int main(){
	int t;
	double d;
	
	scanf("%d",&t);
	for(int i=0;i<t;++i){
		scanf("%lf",&d);
		double h=d/2;
		double l=0;	
		double a;
		double b;
		bool ok=false;
		for(int j=0;j<=100000;++j){
			a=(h+l)/2;
			b=d-a;
			double sum=a+b-a*b;
			if(sum<0)
				sum=-sum;
			if(sum<=0.000001){
				ok=true;
				break;
			}
			else if(a*b<d)
				l=a;	
			else if(a*b>d)
				h=a;
			
		}
		
		if(ok)
			printf("Y %.12lf %.12lf\n",a,b);
		else
			printf("N\n");
		
	}
		
	
	return 0;
}

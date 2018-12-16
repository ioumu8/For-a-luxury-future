#include<cstdio>
#include<cstdlib>
#include<cstring>


char plate[5001][5001];
bool save[5001][5001];
int sum;

typedef struct {
	int x;
	int y;	
}Pollute;

Pollute point1[300000]; //probably 20000 point;
Pollute point2[300000];

int put(int x,int y,int k,int jud){
	if(plate[y][x]!='#'){
		if(!save[y][x]){
			save[y][x]=1;
			if(jud==1){
				point2[k].x=x;
				point2[k].y=y;
				}
			if(jud==2){
				point1[k].x=x;
				point1[k].y=y;
			}
			k++;
			sum++;
		}
	}
	return k;
}
	

int main(){
	int H;
	int W;
	int N;
	int a;
	int b;
	memset(plate,0,sizeof(plate));
	memset(save,0,sizeof(save));
	sum=0;
	point1[0].x=-1;
	point1[0].y=-1;
	point2[0].x=-1;
	point2[0].y=-1;
	
	scanf("%d %d",&H,&W);
	for(int i=0;i<H;++i)
		scanf("%s",plate[i]);
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d %d",&a,&b);
		int k=0;
		a--;
		b--;
		if(i%2==0){
			if(save[a][b]!=1){
				save[a][b]=1;
				sum++;
				point1[k].x=b;
				point1[k].y=a;
				k++;
			}
			for(int j=0;point2[j].x!=-1;++j){
				if(point2[j].x>0) 
					k=put(point2[j].x-1,point2[j].y,k,2);
				if(point2[j].x!=(W-1))
					k=put(point2[j].x+1,point2[j].y,k,2);
				if(point2[j].y>0)
					k=put(point2[j].x,point2[j].y-1,k,2);
				if(point2[j].y!=(H-1))
					k=put(point2[j].x,point2[j].y+1,k,2);	
			}
			point1[k].x=-1;
			point1[k].y=-1;		
		}
		else{
			if(save[a][b]!=1){
				save[a][b]=1;
				sum++;
				point2[k].x=b;
				point2[k].y=a;
				k++;
			}
			for(int j=0;point1[j].x!=-1;++j){
				if(point1[j].x>0) 
					k=put(point1[j].x-1,point1[j].y,k,1);
				if(point1[j].x!=(W-1))
					k=put(point1[j].x+1,point1[j].y,k,1);
				if(point1[j].y>0)
					k=put(point1[j].x,point1[j].y-1,k,1);
				if(point1[j].y!=(H-1))
					k=put(point1[j].x,point1[j].y+1,k,1);	
			}
			point2[k].x=-1;
			point2[k].y=-1;		
		}
		printf("%d\n",sum);
		
		
	}
	
	return 0;	
}

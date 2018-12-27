#include<cstdio>

int main(){
	int n,m;
	int k;
	bool place[1001][1001]={0};
	int a,b;
	bool check=true;
	int keep=0;
	
	scanf("%d %d",&n,&m);
	scanf("%d",&k);
	
	for(int i=0;i<k;++i){
		scanf("%d %d",&a,&b);
		place[a][b]=1;
		int d[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
		for(int j=0;j<4;++j){
			int y=a+d[j][0];
			int x=b+d[j][1];
			if(x<1||x>m||y<1||y>n||place[y][x]==0||check==false)
				continue;
			else{
				if(place[a][x]&&place[y][b]){
					check=false;	
					keep=i+1;
				}
			}
		
		}	
	}
	
	printf("%d\n",keep);

	return 0;	
}

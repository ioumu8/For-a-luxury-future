#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>

using namespace std;

typedef struct{
	int num;		//which place when scanning
	int next;
	int ver;		//the vertex that connected;
	int len;		//the lenth of the edge;
	int nowlen;
}Line;

Line point[600001];
Line shortpath[600001];
int edge[300001][2];  // for list , save the first & the last place
bool visit[300001];  // already or not;
int d[300001];  //distance from 1 to i;

bool cmp(Line a, Line b){
		
	return a.nowlen > b.nowlen;
}

int main(){
	int n,m;
	int k;
	memset(edge,0,sizeof(edge));
	memset(shortpath,0,sizeof(shortpath));
	for(int i = 0 ; i < 300001 ; i++){
		visit[i] = false;
		d[i]=2147483647;	
	}
	scanf("%d %d %d",&n,&m,&k);
	int keep=1;
	for(int i = 0 ; i < m ; ++i){
		int point1,point2;
		int temp;
		scanf("%d %d %d",&point1,&point2,&temp);
		point[keep].ver = point2;
		point[keep].len = temp;
		point[keep].num = i+1;
		if(!edge[point1][0]){
			edge[point1][0] = keep;
			edge[point1][1] = keep;
			point[keep].next = 2147483647;	
		}
		else{
			int t = edge[point1][1];
			point[t].next = keep;
			edge[point1][1] = keep;
			point[keep].next = 2147483647;	
		}
		keep++;
		point[keep].ver = point1;
		point[keep].len = temp;
		point[keep].num = i+1;
		if(!edge[point2][0]){
			edge[point2][0] = keep;
			edge[point2][1] = keep;	
			point[keep].next = 2147483647;
		}
		else{
			int t = edge[point2][1];
			point[t].next = keep;
			edge[point2][1] = keep;	
			point[keep].next = 2147483647;
		}
		keep++;		
	}
	d[1] = 0;
	visit[1] = true;
	int place = 0;
	for(int i = edge[1][0] ; i <= edge[1][1] ; i = point[i].next){
		int a = point[i].ver;
		d[a] = point[i].len;
		point[i].nowlen = d[a];
		shortpath[place] = point[i];
		place++;
		push_heap(shortpath,shortpath+place,cmp);	
	}
	int visited = 1;
	int save[300001] = {0};
	int now = 0;
	for( ; k > 0 && visited != n && place!=0; k-- , visited++){
		pop_heap(shortpath,shortpath+place,cmp);
		place--;
		Line use = shortpath[place];
		int a = use.ver;
		save[now] = use.num;
		now++;
		visit[a] = true;
		for(int i = edge[a][0] ; i <= edge[a][1] ; i = point[i].next){
			int b = point[i].ver;
			if(!visit[b] && d[a]+point[i].len < d[b]){
				d[b] = d[a]+point[i].len;
				point[i].nowlen = d[b];
				shortpath[place] = point[i];
				place++;
				push_heap(shortpath,shortpath+place,cmp);
			}
		}
	}
	printf("%d\n",now);
	for(int i = 0 ; i < now ; ++i)
		printf("%d ",save[i]);
	printf("\n");
	
	return 0;	
}


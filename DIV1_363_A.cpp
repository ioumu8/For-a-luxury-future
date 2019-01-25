#include<cstdio>
#include<cstring>

int mini(int a, int b, int c){
	int min = a;
	if(b < min)
		min = b;
	if(c < min)
		min = c;
	return min;	
}

int main(){
	int n;
	int work[101];
	int day_off[101][4];  // 0 means rest, 1 sport, 2 IT
	memset(day_off, 0, sizeof(day_off));
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &work[i]);
	for(int i = 0; i < n; ++i){
		if(i == 0){
			day_off[0][i] = 1;
			if(work[i] == 0 || work[i] == 1)	
				day_off[1][i] = 999;
			if(work[i] == 0 || work[i] == 2)
				day_off[2][i] = 999;
		}else{
			day_off[0][i] = mini(day_off[0][i-1], day_off[1][i-1], day_off[2][i-1]) + 1;	
			if(work[i] == 0){
				day_off[1][i] = 999;
				day_off[2][i] = 999;
			}else if(work[i] == 1){
				day_off[1][i] = 999;
				day_off[2][i] = mini(day_off[0][i-1], day_off[1][i-1], 999);
			}else if(work[i] == 2){
				day_off[2][i] = 999;
				day_off[1][i] = mini(day_off[0][i-1], day_off[2][i-1], 999);
			}else if(work[i] == 3){
				day_off[1][i] = mini(day_off[0][i-1], day_off[2][i-1], 999);
				day_off[2][i] = mini(day_off[0][i-1], day_off[1][i-1], 999);
			}
		}	
	}
	printf("%d\n",mini(day_off[0][n-1], day_off[1][n-1], day_off[2][n-1]));
	
	return 0;	
}

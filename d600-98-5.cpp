#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>

struct Place{
	double x;
	double y;	
};

bool check_side(Place a, Place b, Place c){
	double sum = a.x * b.y + b.x * c.y + c.x * a.y;
	sum -= (b.x * a.y + c.x * b.y + a.x * c.y);
	if(sum >= 0)
		return true;
	return false;	
}

bool judge(std:: vector<Place> &area_1,
		   std:: vector<Place> &area_2,
		   std:: vector<Place> &save){
	bool check = true;
	for(int i = 0; i < area_2.size(); ++i){
		bool inside = true;
		for(int j = 0; j < area_1.size(); ++j){
			bool ok;
			if(j == area_1.size() - 1)
				ok = check_side(area_1[j], area_1[0], area_2[i]);
			else
				ok = check_side(area_1[j], area_1[j + 1], area_2[i]);	
			
			if(!ok){
				inside = false;
				break;
			}
		}
		if(inside)
			save.push_back(area_2[i]);
		else
			check = false;
	}
	return check;		   	
}

bool cmp(Place a, Place b){
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;	
}

Place find(Place p_1, Place p_2, Place p_3, Place p_4){
	// ax + by = c;
	double fun_1[3] = {(p_1.y - p_2.y), (p_2.x - p_1.x), p_1.y * p_2.x - p_2.y * p_1.x};	
	double fun_2[3] = {(p_3.y - p_4.y), (p_4.x - p_3.x), p_3.y * p_4.x - p_4.y * p_3.x};
	Place ans;
	ans.x = (fun_1[2] * fun_2[1] - fun_1[1] * fun_2[2]) / (fun_1[0] * fun_2[1] - fun_1[1] * fun_2[0]);
	ans.y = (fun_1[0] * fun_2[2] - fun_1[2] * fun_2[0]) / (fun_1[0] * fun_2[1] - fun_1[1] * fun_2[0]);
	return ans;
}

void find_cross(std:: vector<Place> &area_1,
		   std:: vector<Place> &area_2,
		   std:: vector<Place> &save){	
	for(int i = 0; i < area_1.size(); ++i){
		Place p_1 = area_1[i];
		Place p_2 = i == (area_1.size() - 1) ? area_1[0] : area_1[i + 1];
		for(int j = 0; j < area_2.size(); ++j){
			Place p_3 = area_2[j];
			Place p_4 = j == (area_2.size() - 1) ? area_2[0] : area_2[j + 1];
			if(check_side(p_1, p_2, p_3) ^ check_side(p_1, p_2, p_4))
				if(check_side(p_3, p_4, p_1) ^ check_side(p_3, p_4, p_2)){
					Place ans = find(p_1, p_2, p_3, p_4);
					save.push_back(ans);	
				}
		}
	} 	
}

void make_tobo(std:: vector<Place> &save){
	std:: sort(save.begin(), save.end(), cmp);	
	std:: vector<Place> keep;
	if(!save.empty())
		keep.push_back(save[0]);
	int range = save.size() - 1;
	for(int i = 1; i < range; ++i){
		bool ok = check_side(keep.back(), save[i + 1], save[i]);
		if(!ok)
			keep.push_back(save[i]);
	}
	if(save.size() > 1)
		keep.push_back(save.back());
	for(int i = range - 1; i >= 1; --i){
		bool ok = check_side(keep.back(), save[i - 1], save[i]);
		if(!ok)
			keep.push_back(save[i]);
	}
	save = keep;
}

double find_area(std:: vector<Place> &save){
	if(save.size() < 3)
		return 0;
	save.push_back(save.front());
	double positive = 0;
	double negitive = 0;
	int range = save.size() - 1;
	for(int i = 0; i < range; ++i){
		positive += save[i].x * save[i + 1].y;
		negitive += save[i + 1].x * save[i].y;	
	}
	double ans = (positive - negitive) * 0.5;
	return ans < 0 ? -ans : ans;
}

int main(){
	int m;
	scanf("%d", &m);
	std:: vector<Place> area_1(m);
	for(int i = 0; i < m; ++i)
		scanf("%lf %lf", &area_1[i].x, &area_1[i].y);	
	int n;
	scanf("%d", &n);
	std:: vector<Place> area_2(n);
	for(int i = 0; i < n; ++i)
		scanf("%lf %lf", &area_2[i].x, &area_2[i].y);
	std:: vector<Place> save;
	bool check_1 = judge(area_1, area_2, save);  // judge whether the shape is in other shape or not; 
	bool check_2 = judge(area_2, area_1, save);
	if(check_1 || check_2){
		make_tobo(save);	
	}else{
		find_cross(area_1, area_2, save);	
		make_tobo(save);
	}
	double ans = find_area(save);
	printf("%.2lf\n", ans);
	return 0;	
}


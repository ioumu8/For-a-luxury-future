#include<cstdio>
#include<vector>
#include<utility> 

struct Node{
	int num;
	int sum;
	std:: vector<int> point;	
};

int find(int now, std:: vector<std:: vector<int> > &connect,
		 std:: vector<Node> &node, std:: vector<bool> &visit){
	visit[now] = true;
	if(connect[now].size() == 1 && visit[connect[now][0]])
		return 1;	
	for(int i = 0; i < connect[now].size(); ++i){
		if(!visit[connect[now][i]]){
			int part_sum = find(connect[now][i], connect, node, visit);
			node[now].point.push_back(part_sum);
			node[now].sum += part_sum;
		}
	}
	return node[now].sum + 1;
}

void set_point(int n, std:: vector<Node> &node, std:: vector<std:: vector<int> > &connect){
	std:: vector<bool> visit(n, 0);
	visit[0] = true;
	node[0].sum = find(0, connect, node, visit);
	int maxa = n - 1;
	for(int i = 0; i < n; ++i)
		if(node[i].sum < maxa)
			node[i].point.push_back(maxa - node[i].sum);	
}

std:: pair<int, int> find_ans(std:: vector<Node> &node){
	int maxa = -1;
	int num = 0;
	for(int i = 0; i < node.size(); ++i){
		int sum = 0;
		for(int j = 0; j < node[i].point.size(); ++j){
			for(int z = j + 1; z < node[i].point.size(); ++z)
				sum += node[i].point[j] * node[i].point[z];	
		}
		if(sum > maxa){
			maxa = sum;
			num = i;	
		}
	}
	return std:: make_pair(num + 1, maxa);
	
}
int main(){
	int n;
	scanf("%d", &n);
	std:: vector<Node> node(n);
	for(int i = 0; i < n; ++i){
		node[i].num = i;
		node[i].sum = 0;	
	}
	std:: vector<std:: vector<int> > connect(n);
	for(int i = 1; i < n; ++i){
		int u;
		int v;
		scanf("%d %d", &u, &v);
		u--;
		v--;
		connect[u].push_back(v);
		connect[v].push_back(u);
	}
	set_point(n, node, connect);
	std:: pair<int, int> ans = find_ans(node);
	printf("%d %d\n", ans.first, ans.second);
	return 0;	
}

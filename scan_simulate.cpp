#include <bits/stdc++.h>

#define rep(i,n) for(int i = 0;i <(int)n;i++)

using namespace std;

const int length = 80,width = 40, det_dis = 10;
int cur_x = length/2, cur_y = width/2;
int tg_x,tg_y;
vector<vector<int> > field_map(length,vector<int>(width,0));
const int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
bool seen[length][width];
queue<int> que;

void set_map(float r,float theta){
    int x = cur_x + r*sin(theta), y = cur_y + r*cos(theta);
    // cout << x << ' ' << y << endl;
    rep(i,length){
        rep(j,width){
            if(field_map[i][j] == 2)continue;
            if((i-x)*(i-x) + (j-y)*(j-y) < 10) field_map[i][j] = 2;
            else if((cur_x-i)*(cur_x-i) + (cur_y-j)*(cur_y-j) < det_dis*det_dis)field_map[i][j] = max(field_map[i][j],1);
        }
    }
    field_map[cur_x][cur_y] = 100;
}
void bfs(int x,int y){
    que.push(100*cur_x+cur_y);
    while (!que.empty()){
        rep(dir,4){
            int xd = x + dx[dir], yd = y + dy[dir];
            if(xd < 0 || xd >= length || yd < 0 || yd >= width)continue;
            if(field_map[xd][yd] == 2)continue;
            if(seen[xd][yd])continue;
            que.push(100*xd+yd);
            if(field_map[xd][yd] == 0){
                tg_x = xd, tg_y = yd;
            }
        }
    }
    // rep(dir,4){
    //     int xd = x + dx[dir], yd = y + dy[dir];
    //     if(xd < 0 || xd >= length || yd < 0 || yd >= width)continue;
    //     if(field_map[xd][yd] == 2)continue;
    //     if(seen[xd][yd])continue;
    //     if(field_map[xd][yd] == 0){
    //         que.push(100*xd+yd);
    //     }
    //     while(!que.empty()){
    //         int px = que.front()/100, py = que.front()%100;
    //         que.pop();

    //     }
    // }
}

// void scan(){
    
// }

int main(){
    float r = 10.0, theta = 30.0;
    int div = 15;
    rep(i,180/div){
        set_map(r,i*div);
    }
    bfs(cur_x,cur_y);
    cout << tg_x*100+tg_y << endl;
    rep(i,length){
        rep(j,width)cout << field_map[i][j] << ' ';
        cout << endl;
    }
}

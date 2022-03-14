#include "vector"
#include "iostream"
#include "string"
#include "queue"
#include "scan_simulate.h"
//#include "bits/stdc++.h"

#define rep(i,n) for(short int i = 0;i <(short int)n;i++)
#define sint short int

using namespace std;

const sint length = 10,width = 10, det_dis = 5;
char cur_x = length/2, cur_y = width/2;
char tg_x = 0,tg_y = 0;
sint field_map[length][width];
// vector<vector<sint> > field_map(length,vector<sint>(width,1));
const sint dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
bool seen[length][width];
// vector<vector<bool> > seen(length,vector<bool>(width,false));
queue<sint> que;

//map 0:障害物なし,1:未探査,2:障害物あり 

void set_map(float r,float theta){
    sint x = cur_x + r*sin(theta), y = cur_y + r*cos(theta);
    // cout << x << ' ' << y << endl;
    rep(i,length){
        rep(j,width){
            if(field_map[i][j] == 2)continue;
            if((i-x)*(i-x) + (j-y)*(j-y) < 10) field_map[i][j] = 2;
            else if((cur_x-i)*(cur_x-i) + (cur_y-j)*(cur_y-j) < det_dis*det_dis && field_map[i][j] != 2)field_map[i][j] = 0;
        }
    }
    // field_map[cur_x][cur_y] = 100;
}
sint bfs(){
    while (!que.empty()){
        sint xy = que.front();
        // cout << xy << ' ';
        que.pop();
        sint x = xy/100,y = xy%100;
        seen[x][y] = true;
        rep(dir,4){
            sint xd = x + dx[dir], yd = y + dy[dir];
            if(xd < 0 || xd >= length || yd < 0 || yd >= width)continue;
            if(field_map[xd][yd] == 2)continue;
            if(seen[xd][yd])continue;
            que.push(100*xd+yd);
            seen[xd][yd] = true;
            if(field_map[xd][yd] == 1){
                return xd*100+yd;
            }
        }
    }
    return 9999;
}

vector<float> move(sint cur,sint goal){
    vector<float> road(2,0.0);
    if(goal == 9999)return road;
    else{
        float cx = cur/100,cy = cur%100;
        float gx = goal/100,gy = goal%100;
        float r = sqrt((cx-gx)*(cx-gx)+(cy-gy)*(cy-gy));
        float t = (cx-gx)/(cy-gy);
        cout << t << endl;
        float theta = atan(t);
        road[0] = r,road[1] = theta;
        return road;
    }
}

void scan(){
    float r = 10.0, theta = 30.0;
    sint div = 15;
    rep(i,180/div){
        set_map(r,i*div);
    }
    que.push(100*cur_x+cur_y);
    cout << bfs() << endl;
    rep(i,length){
        rep(j,width)cout << seen[i][j] << ' ';
        cout << endl;
    }
    rep(i,length){
        rep(j,width)cout << field_map[i][j] << ' ';
        cout << endl;
    }
    sint cur = cur_x*100+cur_y;
    vector<float> trans = move(cur,bfs());
    // rep(i,2)Serial.println(trans[i]);
}

sint find(){
    rep(i,length-10){
        rep(j,width-10){
            bool b = true;
            rep(k,10){
                if(!b)break;
                rep(l,10){
                    if(field_map[i+k][j+l] != 0){
                        b = false;
                        break;
                    }
                }
            }
            if(b)return (i+5)*100+(j+5);
        }
    }
    return 0;
}

int main(){
    // float r = 10.0, theta = 30.0;
    // int div = 15;
    // rep(i,180/div){
    //     set_map(r,i*div);
    // }
    // que.push(100*cur_x+cur_y);
    // cout << bfs() << endl;
    // rep(i,length){
    //     rep(j,width)cout << seen[i][j] << ' ';
    //     cout << endl;
    // }
    // rep(i,length){
    //     rep(j,width)cout << field_map[i][j] << ' ';
    //     cout << endl;
    // }
    // int cur = cur_x*100+cur_y;
    // vector<float> trans = move(cur,bfs());
    // rep(i,2)cout << trans[i] << ' ';
    scan();
    sint goal = find();
    cout << goal << endl;
}

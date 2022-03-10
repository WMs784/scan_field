#include "vector"
#include "iostream"
#include "string"
#include "queue"
#include "scan_simulate.h"

#define rep(i,n) for(short int i = 0;i <(short int)n;i++)

using namespace std;

const short int length = 20,width = 20, det_dis = 10;
char cur_x = length/2, cur_y = width/2;
char tg_x = 0,tg_y = 0;
vector<vector<char> > field_map(length,vector<char>(width,1));
const short int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
vector<vector<bool> > seen(length,vector<bool>(width,false));
queue<short int> que;

//map 0:障害物なし,1:未探査,2:障害物あり 

void set_map(float r,float theta){
    short int x = cur_x + r*sin(theta), y = cur_y + r*cos(theta);
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
short int bfs(){
    while (!que.empty()){
        short int xy = que.front();
        // cout << xy << ' ';
        que.pop();
        short int x = xy/100,y = xy%100;
        seen[x][y] = true;
        rep(dir,4){
            short int xd = x + dx[dir], yd = y + dy[dir];
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

vector<float> move(short int cur,short int goal){
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
    short int div = 15;
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
    short int cur = cur_x*100+cur_y;
    vector<float> trans = move(cur,bfs());
    rep(i,2)Serial.println(trans[i]);
}

// int main(){
//     float r = 10.0, theta = 30.0;
//     int div = 15;
//     rep(i,180/div){
//         set_map(r,i*div);
//     }
//     que.push(100*cur_x+cur_y);
//     cout << bfs() << endl;
//     rep(i,length){
//         rep(j,width)cout << seen[i][j] << ' ';
//         cout << endl;
//     }
//     rep(i,length){
//         rep(j,width)cout << field_map[i][j] << ' ';
//         cout << endl;
//     }
//     int cur = cur_x*100+cur_y;
//     vector<float> trans = move(cur,bfs());
//     rep(i,2)cout << trans[i] << ' ';
// }

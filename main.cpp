#include "std.h"
#define rep(i,n) for(int i = 0;i < (int)n;i++)

using namespace std;

void setup() {
    Serial.begin(9600);
}
void loop() {
    float r = 10.0, theta = 30.0;
    int div = 15;
    Serial.println("start");
    delay(1000);
    rep(i,180/div){
        set_map(r,div*i);
    }
    int time = millis();
    Serial.println(time);
    delay(1000);
    scan();
    int time2 = millis();
    Serial.println(time);
    delay(1000);
}

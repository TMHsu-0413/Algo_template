/*

向量Template

*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class Point{
public:
    LL x,y;
    Point(LL x,LL y):x(x),y(y){;}
    Point operator-(Point b){ return {x-b.x, y-b.y}; }
    LL operator^(Point b){ return x * b.y - y * b.x;} //外積
    LL operator*(Point b){ return x * b.x + y * b.y;} // 內積
};

bool between(Point a,Point b,Point c){ // c in line AB
    LL cross = (a - c) ^ (b - c); // c點跟a,b點是否平行 是的會為0
    LL dot = (a - c) * (b - c); // c是否再ab線段中

    return cross == 0 && dot <= 0;
}

LL dir(Point a,Point b,Point c){ // 從點c出發，點b在點a的哪個方向，1為左邊，-1為右邊
    LL cross = (a - c) ^ (b - c);
    if (cross == 0) return 0;
    else if(cross > 0) return 1;
    return -1;
}

bool Intersection(Point a,Point b,Point c,Point d){ // ab線與cd現有沒有交集
    if (between(a,b,c) || between(a,b,d)) return true;
    if (between(c,d,a) || between(c,d,b)) return true;

    if ((dir(a,b,c) * dir(a,b,d)) == -1 && (dir(c,d,a) * dir(c,d,b)) == -1)
        return true;

    return false;
}

int main () {
    int n;
    cin>>n;
    while(n--){
        LL a1,b1,a2,b2,a3,b3,a4,b4;
        cin>>a1>>b1>>a2>>b2>>a3>>b3>>a4>>b4;
        Point p1(a1,b1),p2(a2,b2),p3(a3,b3),p4(a4,b4);

        if (Intersection(p1,p2,p3,p4)) cout <<"YES"<<endl;
        else    cout<<"NO"<<endl;

    }
}
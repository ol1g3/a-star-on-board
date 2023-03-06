#include <iostream>
#include <random>

struct point{
public:
    int x, y;

    point(){x = y = 0;}
    point(int x1, int y1){
        x = x1;
        y = y1;
    }
        
    point& operator=(const point& a){
        x = a.x;
        y = a.y;
        return *this;
    }
    point& operator+=(const point& a){
        x += a.x;
        y += a.y;
        return *this;
    }

    bool check(int grid_size){
        return x >= 0 && x < grid_size && y >= 0 && y < grid_size;
    }

    int dist(const point& a){
        return abs(x - a.x) + abs(y - a.y);
        //return std::max(abs(x - a.x) , abs(y - a.y));
    }
    void create_rand(const int& grid_size){
        x = rand() % grid_size;
        y = rand() % grid_size;
    }
};

bool operator==(point t, point a){
    return a.x == t.x && a.y == t.y;
}
bool operator!=(point t, point a){
    return !(a.x == t.x && a.y == t.y);
}
bool operator<(point t, point a){
    return t.x < a.x || (a.x == t.x && t.y < a.y);
}
bool operator>(point t, point a){
    return t.x > a.x || (a.x == t.x && t.y > a.y);
}
bool operator<=(point t, point a){
    return t == a || t < a;
}
bool operator>=(point t, point a){
    return t > a || t == a;
}
point operator+(const point& a, const point& b){
    return point(a.x+b.x, a.y+b.y);
}

std::ostream& operator<<(std::ostream& os, const point& p){
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

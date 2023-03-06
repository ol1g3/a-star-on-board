#include "class.cpp"

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include <set>


using namespace std;


vector<point> moves;
void create_moves(){
    // create an array of possible changes of coordinates

    moves.push_back(point(0, 1));
    moves.push_back(point(0, -1));
    moves.push_back(point(1, 0));
    moves.push_back(point(-1, 0));
}

// randomly create start/end points
void create_points(const int& grid_size, point& a, point& b){
    a.create_rand(grid_size);
    b.create_rand(grid_size);
    // while the points are equal - create a new end point
    while(b == a){
        b.create_rand(grid_size);
    }
}
// creating random obstacles
void create_obstacles(const int& grid_size, vector<vector<char> >& grid,
                      const point& source_, const point& target_, int obstacles){

    while(obstacles--){
        point p;
        p.create_rand(grid_size);
        // while the obstacle = start/end or another obstacle - generate a new one
        while(grid[p.x][p.y] == '*' || p == source_ || p == target_){
            p.create_rand(grid_size);
        }
        grid[p.x][p.y] = '*';
    }
}
// get a path basing on prev array
vector<point> get_path(const vector<vector<point > >& prev, point target_){
    vector<point> ans;
    while(target_ != point(-1, -1)){
        ans.push_back(target_);
        target_ = prev[target_.x][target_.y];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
// Output the matrix
// S - starting edge, T - target edge
// X - optimal path
// '.' - clear cell, '*' - obstacle
void out_the_matrix(const int& grid_size, const vector<vector<char> >& grid, 
                    const vector<vector<point> >& prev, const vector<point> path, 
                    const point& source_, const point& target_,
                    ostream& fout){

    // create a set of points in path - to check, how it should be written
    set<point> s(path.begin(), path.end());
    for(int i = 0;i < grid_size;i++){
        for(int z = 0;z < grid_size;z++){
            point cur = point(i,z);
            // if start - output S, if end - output T
            if(cur == source_) fout << "S";
            else if(cur == target_) fout << "T";
            // if in path - output X 
            else if(s.count(cur)) fout << "X";
            // if not in path - output the basic info - either '*' or '.'
            else fout << grid[i][z];
        }
        fout << endl;
    }
    // if the size of s = 0 -> size of path = 0 -> no path to be found
    if(!s.size()) fout << "No path!\n";
    else{
        // if the path is found - output 
        fout << endl << "Size of the path: " << path.size() << endl;
        for(auto it : path) fout << it << (it == path.back() ? "\n" : " -> ");
    }
}

void A_star(const int& grid_size, const vector<vector<char> >& grid, 
            const point& source_, point target_, ostream& fout){

    create_moves();
    priority_queue<pair<int, point> > nodes;

    // create a distance array, assign INF to every cell except the starting one
    vector<vector<int> > dist(grid_size, vector<int>(grid_size, 1e9));
    vector<vector<point> > prev(grid_size, vector<point>(grid_size, point(-1, -1)));
    
    dist[source_.x][source_.y] = 0;
    nodes.push(make_pair(0, source_));    

    while(nodes.size() && dist[target_.x][target_.y] == 1e9){
        auto it = nodes.top();
        nodes.pop();

        for(auto m: moves){
            // create a next cell to move
            point next = it.second + m;
            // if its not free or doesnt exist in matrix - skip
            if(!next.check(grid_size)) continue;    
            if(grid[next.x][next.y] == '*') continue;

            // count a distance of a pi_edge
            int next_d = 1 - it.second.dist(target_) + next.dist(target_);
            // if dist(cur) + next_d < dist(next) -> change the value and put in queue
            if(-it.first + next_d < dist[next.x][next.y]){
                prev[next.x][next.y] = it.second;
                dist[next.x][next.y] = -it.first + next_d;
                // we push -(val) since the priority queue takes the biggest value
                // the smallest value is the best, so making it negative makes it the largest
                nodes.push(make_pair(-next_d+it.first, next));
            }
            // if the result for target found - break
            if(next == target_){
                break;
            }
        }
    }
    vector<point> path;
    // if there`s a path - find it
    if(prev[target_.x][target_.y] != point(-1,-1)){
        path = get_path(prev, target_);
    }
    out_the_matrix(grid_size, grid, prev, path, source_, target_, fout);
}

int main(){
    srand(time(0));
    // create the in-out streams for read and write in files
    ifstream fin("in.txt");
    ofstream fout;
    fout.open("out.txt");

    int grid_size, obstacles;
    // input the values - size of the grid and number of obstacles
    fin >> grid_size >> obstacles;
    // create the start-end points and a grid, filling it with obstacles
    point source_, target_;
    vector<vector<char> > grid(grid_size, vector<char>(grid_size, '.'));
    create_points(grid_size, source_, target_);
    create_obstacles(grid_size, grid, source_, target_, obstacles);
    
    fout << "Start: "  << source_ << endl;
    fout << "End: "  << target_ << endl;
    
    // find the answer
    A_star(grid_size, grid, source_, target_, fout);
        
    fout.close();
}

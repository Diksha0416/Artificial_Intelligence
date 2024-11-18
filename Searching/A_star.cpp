#include<iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

typedef pair<int,int>pi;

void DFS(vector<vector<int>>&adj, int start){
    int n = adj.size();
    vector<bool> visited(adj.size(), false); 
    
    cout<<"DFS order: ";
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        
        if(!visited[node]){
            cout << node << " ";
            visited[node] = true;
            for(int i=0;i<n;i++){
                if(adj[node][i]!=0 && !visited[i]){
                    stack.push(i);
                }
            }
        }
    }
    cout << endl;
}

void BFS(vector<vector<int>>&adj, int start){
    int n = adj.size();
    vector<bool> visited(adj.size(), false);

    cout<<"BFS order: ";
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        if(!visited[node]){
            cout << node << " ";
            visited[node] = true;
            for(int i=0;i<n;i++){
                if(adj[node][i]!=0 && !visited[i]){
                    q.push(i);
                }
            }
        }
    }
    cout<<endl;
}

void IBS(vector<vector<int>>&adj,int node,int depth, vector<int>&visited ){

    if (depth < 0) return;

    visited[node]=1;
    cout<<node<<" ";

    for(int i=0;i<adj.size();i++){
        if(adj[node][i] && !visited[i]){
            IBS(adj,i,depth-1,visited);
        }
    }
}

void Depth_IBS(vector<vector<int>> &adj, int start){
    int max_depth = 5;
    for(int i=0;i<max_depth;i++){
        vector<int>visited(adj.size(),0);
        cout<<"For depth "<<i<<":";
        IBS(adj,start,i, visited);
        cout<<endl;
    }
}

void beam_search(vector<vector<int>>& adj, int startNode, int Width) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> isVisited(adj.size(), false);
    pq.push({0, startNode});
    isVisited[startNode] = true;

    cout << "Beam Search order: ";
    while (!pq.empty()) {
        vector<pair<int, int>> current_Nodes;

        for (int i = 0; i < Width && !pq.empty(); i++) {
            current_Nodes.push_back(pq.top());
            pq.pop();
        }

        for (auto& nodePair : current_Nodes) {
            int currentNode = nodePair.second;
            cout << currentNode << " ";

            for (int i = 0; i < adj.size(); i++) {
                if (adj[currentNode][i] != 0 && !isVisited[i]) {
                    pq.push({adj[currentNode][i], i});
                    isVisited[i] = true;
                }
            }
        }
    }
    cout << endl;
}


void BestFS(const vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<bool> visited(n, false);
    priority_queue<pi, vector<pi>, greater<pi>> pq;

    pq.push(make_pair(0, start));
    visited[start] = true;
    cout<<"Best First Search order: ";
    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        cout << current << " ";

        for (int i = 0; i < n; i++) {
            if (adj[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                pq.push(make_pair(adj[current][i], i));
            }
        }
    }
    cout << endl;
}

void A_star(vector<vector<int>> &adj, int start, vector<int> &h){
    priority_queue<pi, vector<pi>, greater<pi>>pq;
    int n = adj.size();
    vector<bool> visited(n, false);

    pq.push(make_pair(h[start],start));
    visited[start]=true;

    cout<<"A* Search order: ";
    while(!pq.empty()){
        int current = pq.top().second;
        pq.pop();
        cout<< current <<" ";

        for(int i=0; i<n;i++){
            if(adj[current][i] !=0 && !visited[i]){
                int edge_cost = adj[current][i];
                int current_cost = edge_cost + h[i];
                pq.push(make_pair(current_cost, i));
                visited[i] = true;
            }
        }
    }
    cout<<endl;
}

int main(){
    int num_nodes = 10, start = 0;
    vector<vector<int>>adj = {
        {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
        {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
        {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
        {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
        {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
        {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
        {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
        {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},
        {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
        {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}};
    
    vector<int> heuristic = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};

    cout<<"Depth First Search without considering any cost: \n";
    DFS(adj, start);

    cout<<"\nBreadth First Search without considering any cost:\n";
    BFS(adj, start);

    cout<<"\nIterative Deepening by exploring best node first:\n";
    Depth_IBS(adj,start);

    cout<<"\nBeam Search (Width=2) by giving preference to best node:\n";
    beam_search(adj, start, 2);

    cout<<"\nBest First Search considering only g value:\n";
    BestFS(adj, start);

    cout<<"\nA* algorithm by considering both g and h' :\n";
    A_star(adj, start, heuristic);
}
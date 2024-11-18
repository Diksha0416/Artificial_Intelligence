#include<iostream>
#include<vector>
using namespace std;
void IBSHelper(vector<vector<int>>&adj,int node,int depth, vector<int>visited ){

    cout<<node<<" ";

    visited[node]=1;

    if(depth!=0){
        for(int i=0;i<adj.size();i++){
            if(adj[node][i] && !visited[i]){
                IBSHelper(adj,i,depth-1,visited);
            }
        }
    }
}
void IBS(vector<vector<int>>&adj,int node,int depth ){
    vector<int>visited(adj.size(),0);
    IBSHelper(adj,node,depth,visited);
}
int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));
    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }
    int start,depth;
    cout << "Enter the starting node: ";
    cin >> start;
    cout <<"Enter the depth: ";
    cin>>depth;
    for(int i=0;i<depth;i++){
        cout<<"For depth "<<i<<":";
        IBS(adj,start,i);
        cout<<endl;
    }
    return 0;
}
#include <bits/stdc++.h> 
#include<iostream>
#include<unordered_map>
using namespace std;

bool isCyclicBFS(int src,unordered_map<int,bool> &visited,unordered_map<int,list<int>>&adj){
    unordered_map<int,int> parent;

    parent[src]=-1;
    visited[src]=1;
    queue<int> q;
    q.push(src);

    while(!q.empty()){
        int front=q.front();
        q.pop();

        for(auto neighbour:adj[front]){
            if(visited[neighbour]==true && neighbour!=parent[front]){
                return true;
            }
            else if(!visited[neighbour]){
                q.push(neighbour);
                visited[neighbour]=1;
                parent[neighbour]=front;
            }
        }
    }
    return false;
}

bool isCyclicDFS(int node,int parent,unordered_map<int,bool> &visited,unordered_map<int,list<int>>&adj){
    visited[node]=true;
    for(auto neighbour: adj[node]){
        if(!visited[neighbour]){
            bool cycleDetected=isCyclicDFS(neighbour,node,visited,adj);
            if(cycleDetected){
                return true;
            }
        }
        else if(neighbour!=parent){
            return true;
        }
    }
    return false;
}

string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    // Write your code here.
    unordered_map<int ,list<int>> adj;
    for(int i=0;i<m;i++){
        int u=edges[i][0];
        int v=edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // return "Yes";
    unordered_map<int,bool> visited;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            bool ans=isCyclicDFS(i,-1,visited,adj);
            if(ans==1){
                return "Yes";
            }
        }
    }
    return "No";
}

int main(){
    int vertex=5;
    int edges=5;
    vector<vector<int>> edge={{0,1},{1,2},{2,3},{3,4},{4,0}};

    cout<<cycleDetection(edge,vertex,edges)<<endl;
    return 0;
}
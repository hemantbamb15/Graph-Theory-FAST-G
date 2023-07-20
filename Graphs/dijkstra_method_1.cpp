// The second implementation is time complexity wise better but is really complex as we have implemented our own priority queue. The First implementation is simpler as it uses STL. The issue with third implementation is, it uses set which in turn uses Self-Balancing Binary Search Trees. For Dijkstra’s algorithm, it is always recommended to use heap (or priority queue) as the required operations (extract minimum and decrease key) match with speciality of heap (or priority queue). However, the problem is, priority_queue doesn’t support decrease key. To resolve this problem, do not update a key, but insert one more copy of it. So we allow multiple instances of same vertex in priority queue. This approach doesn’t require decrease key operation and has below important properties.

// Whenever distance of a vertex is reduced, we add one more instance of vertex in priority_queue. Even if there are multiple instances, we only consider the instance with minimum distance and ignore other instances.
// The time complexity remains O(ELogV)) as there will be at most O(E) vertices in priority queue and O(Log E) is same as O(Log V)

#include <bits/stdc++.h> 
#include<iostream>
#include<unordered_map>
using namespace std;

vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {
    // Write your code here.
    unordered_map<int, list<pair<int,int>>> adj;
    for(int i=0;i<edges;i++){
        int u=vec[i][0];
        int v=vec[i][1];
        int w=vec[i][2];

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    vector<int> dist(vertices);

    for(int i=0;i<vertices;i++){
        dist[i]=INT_MAX;
    }

    set<pair<int,int>> st;
    
    dist[source]=0;
    st.insert(make_pair(0,source));

    while(!st.empty()){
        auto top=*(st.begin());

        int nodeDistance=top.first;
        int topNode=top.second;

        st.erase(st.begin());

        for(auto neighbour:adj[topNode]){
            if(nodeDistance + neighbour.second<dist[neighbour.first]){
                auto record=st.find(make_pair(dist[neighbour.first],neighbour.first));

                if(record!=st.end()){
                    st.erase(record);
                }
                dist[neighbour.first]=nodeDistance + neighbour.second;
                st.insert(make_pair(dist[neighbour.first],neighbour.first));
            }
        }
    }
    return dist;
}

int main(){
    int vertex=5;
    int edges=7;
    vector<vector<int>> edge={{0,1,4},{0,2,8},{1,2,8},{1,3,11},{2,3,7},{2,4,2},{3,4,9}};

    vector<int> ans=dijkstra(edge,vertex,edges,0);

    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return 0;
}






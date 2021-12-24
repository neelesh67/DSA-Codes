#include<bits/stdc++.h>
using namespace std;

// BUILDING A GRAPG (DIRECTED) 
void addEdge(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
}
//FUNCTION TO PRINT GRAPH
void printGraph(vector<int>adj[],int v)
{
    for(int i=0;i<v;i++)
    {
        for(auto x:adj[i])
            cout<<x<<" ";
        cout<<"\n";
    }
}

//BFS TRAVERSAL TO PRINT GRAPH(USAING QUEUE DS)
void bfs_connected(vector<int>adj[],int v,int s)
{
    bool visited[v+1];
    for(int i=0;i<v;i++)
    {
        visited[i] = false;
    }
    queue<int>q;
    q.push(s);
    visited[s] = true;
    while(q.empty() == false)
    {
        int u = q.front();
        q.pop();
        cout<<u<<" ";
        for(int x:adj[u])
        {
            if(visited[x] == false)
            {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

//UTILITY FUNCTION FOR DFS TRAVERSAL
void DFSrec(vector<int>adj[],int s,bool visited[])
{
    visited[s] = true;
    cout<<s<<" ";
    for(auto u:adj[s])
    {
        if(visited[u] == false)
        {
            visited[u] = true;
            DFSrec(adj,u,visited);
        }
    }
}

//DFS TRAVERSAL OF GRAPG
int DFS(vector<int>adj[],int v)
{
    bool visited[v+1];
    int count = 0;
    for(int i=0;i<v;i++)
        visited[i] = false;
    for(int i=0;i<v;i++){
        if(visited[i] == false)
        {
            count++;
            DFSrec(adj,v,visited);  
        }
    }
    return count;
}

//FUNCTION TO CALCULATE SHORTEST PATH
void short_path(vector<int>adj[],int v,int s, int dist[])
{
    bool visited[v];
    for(int i=0;i<v;i++)
        visited[i] = false;
    queue<int>q;
    q.push(s);
    visited[s] = true;
   
    while(q.empty() == false)
    {
        int u = q.front();
        q.pop();
        for(auto x:adj[u])
        {
            if(visited[x] == false)
            {
                dist[x] = dist[u]+1;
                visited[x] = true;
                q.push(x);
            }
            
        }
    }
    for(int i=0;i<v;i++)
        cout<<dist[i]<<" ";

}


bool dfsrec(vector<int>adj[],int s,bool visited[],int parent)
{
    visited[s] = true;
    for(auto x:adj[s])
    {
        if(visited[x] == false)
        {
            if(dfsrec(adj,x,visited,s) == true)
                return true;
            else if(x!=parent)
                return false;
        }
        return false;
    }
}

// LOOP DETECTION IN AN UNDIRECTED GRAPH
bool dfs_cycle(vector<int>adj[],int v)
{
    bool visited[v];
    for(int i=0;i<v;i++)
        visited[i] = false;
    for(int i=0;i<v;i++)
    {
        if(visited[i] == false)
        {
            if(dfsrec(adj,i,visited,-1) == true)
                return true;

        }
        return false;
    }
}

// DETECTING LOOP IN A DIRECTED GRAPG

// utility function for DFS_directed_cycle function
bool DFS_REC_CYCLE(vector<int>adj[],int s,bool visited[],bool rec_stack[])
{
    visited[s] = true;
    rec_stack[s] = true;
    for(auto x:adj[s])
    {
        if(visited[x] == false && DFS_REC_CYCLE(adj,x,visited,rec_stack) == true)
            return true;
        else if(rec_stack[x] == true)
            return true;
    }
    rec_stack[s] = false;
    return false;
}
// main function to detect loop in directed graph
bool DFS_directed_cycle(vector<int>adj[],int v)
{
    bool visited[v];
    for(int i=0;i<v;i++)
        visited[i] = false;
    bool RECst[v];
    for(int i=0;i<v;i++)
        visited[i] = false;
    for(int i=0;i<v;i++)
    {
        if(visited[i] == false)
        {
            if(DFS_REC_CYCLE(adj,i,visited,RECst) == true)
                return true;
        }
    }
    return false;
}

//TOPOLOGICAL SORT FUNCTION
void topological_sort(vector<int>adj[],int v)
{
    vector<int>in_degree(v,0);
    for(int u = 0;u<v;u++)
        for(auto x:adj[u])
            in_degree[x]++;
    queue<int>q;
    for(int i=0;i<v;i++)
        if(in_degree[i] == 0)
            q.push(i);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        cout<<u<<" ";
        for(auto x:adj[u])
        {
            in_degree[x]--;
            if(in_degree[x] == 0)
                q.push(x);
        }
    }
}

// CYCLE DETECTION USING TOPOLOGICAL SORT

bool cycle(vector<int>adj[],int v)
{
    int count = 0;
     vector<int>in_degree(v,0);
    for(int u = 0;u<v;u++)
        for(auto x:adj[u])
            in_degree[x]++;
    queue<int>q;
    for(int i=0;i<v;i++)
        if(in_degree[i] == 0)
            q.push(i);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        
        for(auto x:adj[u])
        {
            in_degree[x]--;
            if(in_degree[x] == 0)
                q.push(x);
        }
        count++;
    }
    return (count!=v);
}

// TOPOLOGICAL SORT USING DFS

//UTIL FUNCTION
void tot_dfs(vector<int>adj[],int u,stack<int>&s,bool visited[])
{
   visited[u]=true;
    
    for(int v:adj[u]){
        if(visited[v]==false)
            tot_dfs(adj,v,s,visited);
    }
    s.push(u);
}

//MAIN TOPOLOGICAL SORT FUNCTION

void tpoplogical_dfs(vector<int>adj[],int V) {
   bool visited[V]; 
    for(int i = 0;i<V; i++) 
        visited[i] = false;
    stack<int> st;
    
    for(int u=0;u<V;u++){
        if(visited[u]==false){
            tot_dfs(adj,u,st,visited);
        }
    }
    
    while(st.empty()==false){
        int u=st.top();
        st.pop();
        cout<<u<<" ";
    }
}

// DRIVER CODE
int main() 
{ 
	int V=5;
    int dist[V];
    for(int i=0;i<V;i++)
        dist[i] = INT_MAX;
    dist[0] = 0;
	  

    vector<int> adj[V];
    addEdge(adj,0, 1); 
    addEdge(adj,1, 3); 
    addEdge(adj,2, 3); 
    addEdge(adj,3, 4); 
    addEdge(adj,2, 4);  
  
    
	cout << "Following is Breadth First Traversal: "<< endl; 
	bfs_connected(adj,V,0);
    cout<<"\n";
    cout<<"shortest path : "; 
    short_path(adj,V,0,dist);
    cout<<"\n";
    if(dfs_cycle(adj,V))
        cout<<"there is a cycle !!";
    else
        cout<<"no cycle !";
    cout<<"\n";
    if(cycle(adj,V))
        cout<<"cycle present";
    else
        cout<<"cycle not present";
    cout<<"topological sort :"<<"\n";
    tpoplogical_dfs(adj,V);
	return 0; 
} 
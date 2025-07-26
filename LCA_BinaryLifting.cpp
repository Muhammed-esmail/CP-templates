int n;
vector<vector<int>> adj;
vector<vector<int>> parent; // parent[i][k] = the 2^k th ancestor of i
vector<int> depth;

const int LOG = 22;
// call after taking input n 
//---------------------------------------------------//
void init() {
    adj.clear(); parent.clear(); depth.clear();
    adj.resize(n+1); parent.resize(n+1); depth.resize(n+1);
}
//---------------------------------------------------//
void pre(int r, int p){
    parent[r][0] = p; 
    for(int i = 1; i <= LOG; i++) {
        parent[r][i] = parent[parent[r][i-1]][i-1];
    }
    for(int c : adj[r]){
        if(c == p)
        continue;
        depth[c] = depth[r] + 1;
        pre(c,r);
    }
}
int lift(int a, int k){
    for(int i = 0; i <= LOG; i++){
        if(k&(1<<i)){
            a = parent[a][i];
        }
    }
    return a;
}
int LCA(int a, int b){
    if(depth[a] < depth[b])
        swap(a,b);
    // now depth[a] >= depth[b]

    // Bring up a to b's level
    a = lift(a,depth[a] - depth[b]);
    
    // now a,b on the same depth
    if(a == b)
        return a;
    
    // they are now in different subtrees
    for(int i = LOG; i >= 0; i--){
        if(parent[a][i] != parent[b][i] and parent[a][i] != 0 and parent[b][i] != 0){
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    return parent[a][0];
}

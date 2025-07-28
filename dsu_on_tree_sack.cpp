void solve() {
    int n,q; cin >> n >> q;
    vector<int> adj[n+1];
    int sz[n+1], big[n+1], ans[q+1], col[n+1];
    map<int,int> mp;
    vector<vector<pii>> qur(n+1);
    fr1(i,n) cin >> col[i];
    fr(i,n-1) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<void(int,int)> pre = [&](int v, int p) {
        sz[v] = 1, big[v] = 0;
        for (int &ch : adj[v]) if (ch != p) {
            pre(ch,v);
            sz[v] += sz[ch];
            if (!big[v]) big[v] = ch;
            else if (sz[ch] > sz[big[v]]) big[v] = ch;
        }
    };

    function<void(int,int)> upd = [&](int v, int d) {
        // update node
    };

    function<void(int,int,int)> collect = [&](int v, int p, int d) {
        upd(v,d);
        for (int &ch : adj[v]) if (ch != p) {
            collect(ch,v,d);
        }
    };

    function<void(int,int,bool)> dfs = [&](int v, int p, bool keep) {
        for (int &ch : adj[v]) if (ch != p and ch != big[v]) {
            dfs(ch,v,0);
        }
        if (big[v]) dfs(big[v],v,1);
        upd(v,1);
        for (int &ch : adj[v]) if (ch != p and ch != big[v]) {
            collect(ch,v,1);
        }
        // answer queries
        for (auto [k,idx] : qur[v]) {
            // answer queries for node v
        }
        if (!keep) collect(v,p,-1);
    };

    int idx = 1;
    while (q--) {
        int v,k;
        cin >> v >> k;
        qur[v].push_back({k,idx++});
    }

    pre(1,-1);
    dfs(1,-1,0);
    for (int i = 1; i < idx; i++) cout << ans[i] << endl;
}

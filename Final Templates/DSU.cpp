struct DSU {
    vector<int> parent, sz;
    // can add another vector for merging sets' values (max/min element in a set)
    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void connect(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (sz[a] > sz[b])
            swap(a, b);
        parent[a] = b;
        sz[b] += sz[a];
    }
};

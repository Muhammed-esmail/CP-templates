constexpr int N = 5e5 + 10;
int n;
int t[2 * N];
int Zero = 0;

int merge(int a, int b) {
    return a + b;
}

void build() {  
    for (int i = n - 1; i > 0; --i)
        t[i] = merge(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {
    --p;
    p += n;  t[p] = value;
    for (; p > 1; p >>= 1)
        t[p>>1] = merge(t[p], t[p^1]);
}

int query(int l, int r) {
    l--; r--;
    int res = Zero;
    l += n, r += n;
    while(l <= r) {
        if(l&1) res = merge(res,t[l++]);
        if(!(r&1)) res = merge(res,t[r--]);
        l >>= 1; r >>= 1;
    }
    return res;
}

void solve() {
    int q; cin >> n >> q;
    for(int i= 0; i < n; i++){
        cin >> t[i+n];
    }
    build();
    for(int i = 0; i < q; i++){
        int op; cin >> op;
        int k,u; cin >> k >> u;
        if(op == 1){
            modify(k,u);
        }
        else{
            cout << query(k,u) << '\n';
        }
    }
}

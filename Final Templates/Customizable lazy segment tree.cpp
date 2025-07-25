int st[N * 4]; // segment tree
int lazy[N * 4];
int L(int p) {return (p << 1);};
int R(int p) {return (p << 1 | 1);}
///////////// tamper with these to customize segment tree, no need to touch rest
int off = 0;          // <------ No lazy needed
int zero = 0;         // <------ Operation identity
int op(int a, int b) {
    return a ^ b;
}
void apply(int p, int len, int value) {
    st[p] = value;
    // lazy[p] ^= value;
}
// Leave this
//------------------------------------------------------------------// 
void prop(int p, int l, int r) {
    if(lazy[p] == off)return;
    if(l == r) return;
    int m = l + r >> 1;
    apply(L(p), m - l + 1, lazy[p]);
    apply(R(p), r - m, lazy[p]);
    lazy[p] = off;
}
void update(int p, int l, int r, int lx, int rx, int value) {
    if(l > rx || r < lx) return;
    prop(p, l, r);
    if(l >= lx && r <= rx) {
        apply(p, r - l + 1, value);
        // prop(p, l, r);
        return;
    }
    int m = l + r >> 1;
    update(L(p), l, m, lx , rx, value);
    update(R(p), m + 1, r, lx , rx, value);
    st[p] = op(st[L(p)], st[R(p)]);
}
int query(int p, int l, int r, int lx, int rx) {
    if(l > rx || r < lx) return zero;
    prop(p, l, r);
    if(l >= lx && r <= rx) {return st[p];}
    int a, b;
    int m = l + r >> 1;
    a = query(L(p), l, m, lx, rx);
    b = query(R(p), m + 1, r, lx ,rx);
    return op(a, b);
}
//------------------------------------------------------------------// 

void solve() {
    int n,q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        update(1,1,2*n-1,i,i,x);
    }
    for(int i = 0; i < q; i++) {
        int a,b; cin >> a >> b;
        cout << query(1,1,2*n-1,a,b) << '\n';
    }
}

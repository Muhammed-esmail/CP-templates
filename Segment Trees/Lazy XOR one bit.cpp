// Lazy flag means it needs to push to children before it goes further down
struct lazy_segment_tree {
    vector<int> sum;
    vector<bool> lazy;
    int n;
    int size = 1;
 
    lazy_segment_tree() = default;
 
    void build(const vector<bool>& v, int x, int l, int r) {
        if (l == r) {
            if (l <= n) sum[x] = v[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(v, 2 * x, l, m);
        build(v, 2 * x + 1, m + 1, r);
        sum[x] = sum[2 * x] + sum[2 * x + 1];
    }
 
    lazy_segment_tree(int n_in, const vector<bool>& v) {
        n = n_in;
        while (size < n) size *= 2;
        sum.assign(2 * size, 0);
        lazy.assign(2 * size, false);
        build(v, 1, 1, size);
    }
 
    void push(int x, int l, int r) {
        if (!lazy[x] || l == r) return;
 
        int m = l + (r - l) / 2;
        int len_left = m - l + 1;
        int len_right = r - m;
 
        // Flip left child's lazy tag and update its sum
        lazy[2 * x] = !lazy[2 * x];
        sum[2 * x] = len_left - sum[2 * x];
 
        // Flip right child's lazy tag and update its sum
        lazy[2 * x + 1] = !lazy[2 * x + 1];
        sum[2 * x + 1] = len_right - sum[2 * x + 1];
 
        lazy[x] = false; // Reset parent's lazy tag
    }
 
    void update(int x, int l, int r, int lx, int rx) {
        if (l > rx || r < lx) return;
        if (l >= lx && r <= rx) {
            lazy[x] = !lazy[x];
            sum[x] = (r - l + 1) - sum[x];
            return;
        }
 
        push(x, l, r); // Push down before recursing
 
        int m = l + (r - l) / 2;
        update(2 * x, l, m, lx, rx);
        update(2 * x + 1, m + 1, r, lx, rx);
        sum[x] = sum[2 * x] + sum[2 * x + 1];
    }
    void update(int l, int r) {
        update(1, 1, size, l, r);
    }
 
    int query(int x, int l, int r, int lx, int rx) {
        if (l > rx || r < lx) return 0;
        if (l >= lx && r <= rx) {
            return sum[x];
        }
 
        push(x, l, r);
 
        int m = l + (r - l) / 2;
        return query(2 * x, l, m, lx, rx) + query(2 * x + 1, m + 1, r, lx, rx);
    }
    int query(int l, int r) {
        return query(1, 1, size, l, r);
    }
};
 

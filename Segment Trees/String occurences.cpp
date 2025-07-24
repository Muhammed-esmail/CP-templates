struct segment_tree {
    int size = 1;
    vector<vector<int>> arr;
    int Zero = 0;

    segment_tree(int n) {
        while (size < n)
            size *= 2;
        arr.resize(26,vector<int>(2 * size + 1));
    }

    void build(int x, int l, int r) {
        if (l == r)
            return;
        int m = (l + r) / 2;
        build(L(x), l, m);
        build(R(x), m + 1, r);
        merge(x);
    }

    segment_tree(int n, string& a) { // string 0-based but segment tree is 1-based
        while (size < n)
            size *= 2;
        arr.resize(26,vector<int>(2 * size + 1));
        for (int i = size; i <= size + n - 1; i++) {
            arr[a[i - size]-'a'][i] = 1;
        }
        build(1, 1, size);
    }

    int L(int x) {
        return 2 * x;
    }

    int R(int x) {
        return 2 * x + 1;
    }
    void merge(int x) {
        for(int i = 0; i < 26; i++) {
            arr[i][x] = arr[i][L(x)]+ arr[i][R(x)];
        }
    }
    void merge(int x, int i) {
        arr[i][x] = arr[i][L(x)]+ arr[i][R(x)];
    }
    void update(int i, int v, int x, int l, int r,char c) {
        if (l == r) {
            arr[c-'a'][x] = v;
            return;
        }
        int m = (r + l) / 2;
        if (i <= m)
            update(i, v, L(x), l, m,c);
        else
            update(i, v, R(x), m + 1, r,c);
        merge(x,c-'a');
    }

    void update(int i, int v, char c) {
        update(i, v, 1, 1, size,c);
    }

    int query_left(int x, int l, int r,int k,char c) {
        if(l == r)
            return l;
        int m = (r + l) / 2;
        if(arr[c-'a'][L(x)] >= k) {
            return query_left(L(x),l,m,k,c);
        }
        else {
            return query_left(R(x),m+1,r,k-arr[c-'a'][L(x)],c);
        }
    }


    int query_right(int x, int l, int r,int k,char c) {
        if(l == r)
            return l;
        int m = (r + l) / 2;
        if(arr[c-'a'][R(x)] >= k) {
            return query_right(R(x),m+1,r,k,c);
        }
        else {
            return query_right(L(x),l,m,k-arr[c-'a'][R(x)],c);
        }
    }

    int sum_left(int x, int l, int r, int i,char c) { 
        if (l > i or r < 1) return Zero;
        if (l >= 1 and r <= i) return arr[c-'a'][x];
        int m = (r + l) / 2;
        return sum_left(L(x),l,m,i,c) + sum_left(R(x),m+1,r,i,c);
    }
    int sum_right(int x, int l, int r, int i,char c) { 
        if (r < i) return Zero;
        if (l >= i) return arr[c-'a'][x];
        int m = (r + l) / 2;
        return sum_right(L(x),l,m,i,c) + sum_right(R(x),m+1,r,i,c);
    }

    int query_left(char c, int k) {      //  find kth occurence from left
        return query_left(1, 1, size,k,c);
    }
    int query_right(char c, int k) {    // k th occurence from right
        return query_right(1, 1, size,k,c);
    }
    int sum_left(int l, char c) {       // number of occurences from 1 to i
        return sum_left(1,1,size,l,c);
    }
    int sum_right(int l, char c) {     // number of occurences from i to n
        return sum_right(1,1,size,l,c);
    }
};

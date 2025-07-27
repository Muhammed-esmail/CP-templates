struct FenwickTree {
    vector<int> s;
    FenwickTree(vector<int>& a){
        s.resize(a.size()+1);
        for(int i = 1; i < a.size(); i++){
            update(i,a[i]);
        }
    }
    void update(int pos, int delta){
        for(;pos < s.size(); pos += pos&(-pos)) 
        s[pos] += delta;
    }
    int query(int r){
        int res = 0;
        for(; r > 0 ; r -= r&(-r)) 
            res += s[r];
        return res;
    }
    int query(int l, int r){
        return query(r) - query(l-1);
    }
};

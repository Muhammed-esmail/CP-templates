// For customizing operations
int op(int a, int b) {
    return a + b;
}
int inverse_op(int a,int b) {
    return a-b;
}

void solve() {
    int n,q; cin >> n >> q;
    vector<vector<int>> a(n+1,vector<int>(n+1));
  
    vector<vector<int>> pref(n+1,vector<int>(n+1));
    // Input + build ---------------------------------------//
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
            pref[i][j] = (a[i][j]) + pref[i][j-1] + pref[i-1][j] - pref[i-1][j-1];  
            // pref[i][j] = inverse_op(op(op((a[i][j]),  pref[i][j-1]) , pref[i-1][j]) , pref[i-1][j-1]);        <-- Change operation
        }
    // Queries       ---------------------------------------//
    for(int i = 0; i < q; i++) {
        int x1,x2; cin >> x1 >> x2; // <--- upper left corner
        int y1,y2; cin >> y1 >> y2; // <--- lower right corner
        int ans = pref[y1][y2] - pref[x1-1][y2] - pref[y1][x2-1] + pref[x1-1][x2-1]; 
        // int ans = op(inverse_op(inverse_op(pref[y1][y2], pref[x1-1][y2]), pref[y1][x2-1]), pref[x1-1][x2-1]);    <-- Change operation
        cout << ans << '\n';
    }
}

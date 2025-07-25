// Build table
const int LOG = 21; // good for 1e6
vector<vector<int>> table(n+1,vector<int>(LOG,inf));

for(int i=1;i<=n;i++) // input
    cin>>a[i], table[i][0] = a[i];

for(int b = 1; b < 19; b++) {
    for(int i = 1; i <= n; i++) {
        if(i +  (1<<(b-1)) > n)
            break;
        table[i][b] = merge(table[i][b-1],table[i+(1<<(b-1))][b-1]);
    }
}
// Choose which to use
//--------------------------------------------------------------------------------------------------------//
function<int(int,int)> answer_query1 = [&](int l, int r) { // operation allows overlaps(max,min,gcd) O(1)
    int diff = r - l + 1;
    int j = 63 - __builtin_clzll(diff);
    r = r - (1<<j) + 1;
    return merge(table[l][j],table[r][j]);
};

function<int(int,int)> answer_query2 = [&](int l, int r) { // operation doesnt allow overlaps(sum,xor,prod) O(log(n))
    int diff = r - l + 1;
    int ans = inf; // CHANGE
    for(int i = 0; i < LOG; i++) {
        if(diff&(1<<i)) {
            ans = merge(ans,table[l][i]);
            l += (1<<i);
        }
    }
    return ans;
};
//--------------------------------------------------------------------------------------------------------//
for(int i = 1; i <= q; i++) {
    int l,r; cin>>l>>r;
    int ans = answer_query2(l,r);
    cout<<ans<<"\n";
}

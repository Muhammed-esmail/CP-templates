// A derangement is a permutation with no fixed points (p[i] != i)
int mul(int a, int b) {
    return (a % mod * b % mod) % mod;
}

int fact[N];
void solve() {
    int n; cin >> n;
    int dp[n+1];
    memset(dp, 0, sizeof dp);
    // Dn = !n = (n-1)(!(n-1) + !(n-2))
    // !1 = 0
    // !0 = 1
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
       dp[i] = mul((i-1), dp[i-1]+dp[i-2]);
    }
    cout << dp[n];
}

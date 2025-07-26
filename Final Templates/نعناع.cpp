const int MOD = 1e9 + 7;

typedef long long ll;
struct mint {
    typedef mint M;
    int v;
    mint(ll _v = 0) : v(int((_v % MOD + MOD) % MOD)) {}
    M& operator+=(M o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    M& operator-=(M o) { if((v -= o.v) < 0) v += MOD; return *this; }
    M& operator*=(M o) { v = int((ll)v * o.v % MOD); return *this; }
    M& operator/=(M o) { return *this *= power(o, MOD - 2); }
    friend M operator+(M a, M b) { return a += b; }
    friend M operator-(M a, M b) { return a -= b; }
    friend M operator*(M a, M b) { return a *= b; }
    friend M operator/(M a, M b) { return a /= b; }
    friend M power(M a, ll e) {
        M r = 1;
        for(; e; e >>= 1) {
            if(e & 1) r *= a;
            a *= a;
        }
        return r;
    }
};

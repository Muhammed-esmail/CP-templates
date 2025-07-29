vector<bool> isprime(N, 1);
vector<int> spf(N);

void sieve() {
    iota(all(spf), 0);
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i < N; i++) {
        if (!isprime[i])
            continue;
        spf[i] = i;
        for (int j = i * i; j < N; j += i) {
            spf[j] = min(spf[j], i);
            isprime[j] = 0;
        }
    }
}

// Unique values vector
//-----------------------------------------------
vector<int> vals = a;
sort(all(vals));
vals.erase(unique(all(vals)), vals.end());
//-----------------------------------------------
// Each element now is 0 <= x <= n-1 
for(int i = 1; i <= n; i++) {
    a[i] = (lower_bound(all(vals),a[i]) - vals.begin());
}
// Can now use a vector for frequency for much better performance than maps
// if the original values don't matter much
vector<int> freq(vals.size());

vector<int> eulerTotient(int n) {
    vector<int> phi(n + 1);
    for (int i = 1; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] = (phi[j] * (i - 1)) / i;
            }
        }
    }
    return phi;
}
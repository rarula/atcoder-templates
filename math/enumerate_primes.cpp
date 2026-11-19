#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "eratosthenes_sieve.cpp"

// from https://github.com/rarula/atcoder-templates
vector<ll> enumerate_primes(ll n) {
    vector<bool> is_prime = eratosthenes(n);
    ll len = is_prime.size();
    vector<ll> primes;
    for (int i = 0; i < len; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

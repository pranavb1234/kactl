/**
 * Author: Pranav Bhatia
 * Date: 2026-10-03
 * License: CC0
 * Source: User-provided reference, formatted for KACTL
 * Description: Modular arithmetic, inverses, matrix multiplication, and combinatorics guide.
 * Time: modPow/inverse O(\log MOD); factorial precomputation O(N); nCr/nPr O(1).
 */
#pragma once

using ll = long long;
const ll MOD = 1000000007LL;

// Modular inverse exists iff gcd(a, mod) = 1.
// Division a / b mod MOD means a * inverse(b) mod MOD.
// Fermat's inverse below requires MOD prime and a % MOD != 0.
ll modPow(ll a, ll e) {
	ll ans = 1;
	a %= MOD;
	if (a < 0) a += MOD;
	while (e) {
		if (e & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		e >>= 1;
	}
	return ans;
}
ll modInverse(ll a) { return modPow(a, MOD - 2); }

// For a possibly composite modulus, use Extended Euclid instead.
ll extendedGCD(ll a, ll b, ll& x, ll& y) {
	if (!b) return x = 1, y = 0, a;
	ll x1, y1, g = extendedGCD(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}
ll inverseAnyMod(ll a, ll mod) {
	ll x, y;
	if (extendedGCD(a, mod, x, y) != 1) return -1;
	return (x % mod + mod) % mod;
}

// Normalize subtraction; use __int128 if a*b can overflow long long.
ll addMod(ll a, ll b) { a += b; return a >= MOD ? a - MOD : a; }
ll subMod(ll a, ll b) { a -= b; return a < 0 ? a + MOD : a; }
ll mulMod(ll a, ll b) { return a * b % MOD; }
ll mulBigMod(ll a, ll b, ll mod) { return (__int128)a * b % mod; }

// Matrix multiplication: i-k-j loop reuses A[i][k] and skips zeros.
using Matrix = vector<vector<ll>>;
Matrix multiply(const Matrix& A, const Matrix& B) {
	int n = sz(A), m = sz(B), p = sz(B[0]);
	Matrix C(n, vector<ll>(p));
	for (int i = 0; i < n; i++) for (int k = 0; k < m; k++) {
		ll aik = A[i][k];
		if (!aik) continue;
		for (int j = 0; j < p; j++)
			C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
	}
	return C;
}

// Factorial + inverse factorial for nCr/nPr under prime MOD.
// Set MAXN to the greatest required n, strictly below MOD.
const int MAXN = 1000000;
ll fact[MAXN + 1], invFact[MAXN + 1];
void initCombinatorics() {
	fact[0] = 1; // 0! = 1
	for (int i = 1; i <= MAXN; i++) fact[i] = fact[i - 1] * i % MOD;
	invFact[MAXN] = modInverse(fact[MAXN]);
	for (int i = MAXN; i >= 1; i--) invFact[i - 1] = invFact[i] * i % MOD;
}
ll nCr(int n, int r) {
	if (r < 0 || r > n) return 0;
	return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}
ll nPr(int n, int r) {
	if (r < 0 || r > n) return 0;
	return fact[n] * invFact[n - r] % MOD;
}

// All inverses 1..N in O(N), for prime MOD and N < MOD.
vector<ll> allInverses(int N) {
	vector<ll> inv(N + 1);
	if (N) inv[1] = 1;
	for (int i = 2; i <= N; i++)
		inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
	return inv;
}

// Checklist:
// - Never do (a / b) % MOD. Check b % MOD != 0, then multiply by inverse.
// - Fermat only works for prime MOD. For composite mod, gcd(a, mod) must be 1.
// - For n >= MOD, factorial[n] is 0 mod MOD: use Lucas or another method.
// - Matrix exponentiation: use with a small fixed state and a huge exponent.

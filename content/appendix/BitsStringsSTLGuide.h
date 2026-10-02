/**
 * Author: Pranav Bhatia
 * Date: 2026-10-03
 * License: CC0
 * Source: User-provided reference, formatted for KACTL
 * Description: Bits, strings, STL, and common contest-pattern quick reference.
 * Time: See individual operations.
 */
#pragma once

// BIT TRICKS (use 1LL << k for a 64-bit mask; do not shift by type width).
bool isPowerOfTwo(ll x) { return x > 0 && !(x & (x - 1)); }
// Check/set/clear/toggle bit k: x&(1LL<<k), x|=(1LL<<k), x&=~(1LL<<k), x^=(1LL<<k).
// Remove/get lowest set bit: x &= x-1; x & -x.
// __builtin_popcountll(x), __builtin_ctzll(x), __builtin_clzll(x).
// ctz/clz on zero is undefined. Highest bit of positive x: 63-__builtin_clzll(x).

// Every value appears twice except one: xor all values.
// Two unique values: xor all -> d; split by lowbit d&-d; xor both groups.
pair<ll,ll> twoUniques(const vector<ll>& a) {
	ll d = 0, x = 0, y = 0;
	for (ll v : a) d ^= v;
	ll bit = d & -d;
	for (ll v : a) (v & bit ? x : y) ^= v;
	return {x, y};
}

// Enumerate all subsets / all submasks (including zero).
// for (int mask = 0; mask < (1 << n); mask++) { ... }
// for (int sub = mask;; sub = (sub - 1) & mask) { ... if (!sub) break; }
// Iterate only set bits: while(mask) { int b=__builtin_ctzll(mask); mask&=mask-1; }
// Bitmask DP: dp[mask], with i=popcount(mask), is standard for N <= about 20 (TSP/assignment).

// STRINGS: getline after formatted input may require cin.ignore(..., '\n').
bool isPalindrome(const string& s) {
	for (int l = 0, r = sz(s) - 1; l < r; l++, r--)
		if (s[l] != s[r]) return false;
	return true;
}
bool isAnagram(const string& a, const string& b) {
	if (sz(a) != sz(b)) return false;
	int cnt[26]{};
	for (char c : a) cnt[c - 'a']++;
	for (char c : b) cnt[c - 'a']--;
	for (int x : cnt) if (x) return false;
	return true;
}
// Character conversions: c-'a', c-'A', c-'0', and '0'+digit.
// s.find(t) == string::npos means absent; s.substr(pos,len), erase, insert, replace.
// reverse(all(s)), sort(all(s)), stoi/stoll, to_string, and lexicographic a < b.
// Frequency: int cnt[26]{} for lowercase; int cnt[256]{} for bytes (use unsigned char).

// Longest substring without repeated characters, O(n).
int longestDistinctSubstring(const string& s) {
	vector<int> last(256, -1);
	int left = 0, ans = 0;
	for (int right = 0; right < sz(s); right++) {
		unsigned char c = s[right];
		if (last[c] >= left) left = last[c] + 1;
		last[c] = right;
		ans = max(ans, right - left + 1);
	}
	return ans;
}
// String recognition: frequencies -> array/map; palindrome -> two pointers;
// substring condition -> sliding window; equality -> hashing; exact matching -> KMP/Z.

// Prefix function / KMP, O(n). Pattern occurrences: pi(pattern + "#" + text) == pattern.size().
vector<int> prefixFunction(const string& s) {
	vector<int> pi(sz(s));
	for (int i = 1; i < sz(s); i++) {
		int j = pi[i - 1];
		while (j && s[i] != s[j]) j = pi[j - 1];
		if (s[i] == s[j]) j++;
		pi[i] = j;
	}
	return pi;
}
vector<int> zFunction(const string& s) {
	vector<int> z(sz(s));
	for (int i = 1, l = 0, r = 0; i < sz(s); i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < sz(s) && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
	return z;
}

// STL CONTAINERS:
// vector: dynamic array, O(1) index/back, amortized O(1) push_back.
// set/map: sorted unique keys, O(log n). multiset: duplicates; erase(x) removes ALL copies.
// unordered_set/unordered_map: average O(1), unordered; member lower_bound on set/map is O(log n).
// stack: LIFO; queue: FIFO/BFS; deque: O(1) both ends/0-1 BFS.
// priority_queue<T>: max heap; priority_queue<T,vector<T>,greater<T>>: min heap.
// bitset<N>: fixed-size fast bit operations (count, any, none, set, reset, flip).
// map[key] inserts a missing key: use find/count for read-only lookup.

// ALGORITHMS ON SORTED VECTOR:
// lower_bound(all(v),x): first >= x; upper_bound(all(v),x): first > x.
// count x: upper_bound(all(v),x)-lower_bound(all(v),x).
// count [L,R]: upper_bound(all(v),R)-lower_bound(all(v),L).
// binary_search(all(v),x), equal_range(all(v),x), and nth_element(v.begin(),v.begin()+k,v.end()).
// nth_element gives kth smallest in average O(n); surrounding elements are not sorted.

// Sorting and common STL: sort, stable_sort, reverse, rotate, min_element, max_element,
// accumulate(all(v),0LL), count, find, all_of/any_of/none_of, and iota(all(idx),0).
// Remove duplicates: sort(all(v)); v.erase(unique(all(v)), v.end());
// Sort indices without moving a: iota(all(idx),0); sort(all(idx),[&](int i,int j){return a[i]<a[j];});

// Binary search on monotonic answer: false...false,true...true gives minimum feasible.
template<class F> ll firstTrue(ll lo, ll hi, F check) {
	while (lo < hi) {
		ll mid = lo + (hi - lo) / 2;
		if (check(mid)) hi = mid;
		else lo = mid + 1;
	}
	return lo;
}

// Coordinate compression: sort values, erase duplicates, then lower_bound for each rank.
// Use 1LL*a*b for int products. gcd/lcm are in <numeric>; lcm can still overflow.
// Fast I/O: ios::sync_with_stdio(false); cin.tie(nullptr);

// RECOGNITION: small N + subsets -> bitmask DP; XOR + pairs -> xor cancellation;
// sorted pair target -> sort + two pointers; huge values -> compression; monotonic check -> binary search;
// repeated min/max -> priority_queue; dynamic sorted values -> set/multiset; rank/kth -> PBDS/nth_element.

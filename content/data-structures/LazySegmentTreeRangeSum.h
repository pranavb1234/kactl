/**
 * Author: Pranav Bhatia
 * Date: 2026-10-02
 * License: CC0
 * Source: User-provided
 * Description: Lazy-propagation segment tree for range addition and range-sum queries.
 * The indices are one-based and ranges are inclusive.
 * To adapt it, change pull() (how children combine), app() (how an update changes
 * a node), and how lz is merged. For min/max queries, also change the out-of-range
 * identity in query().
 * Time: O(\log N) per build node, update, or query.
 * Status: not tested
 */
#pragma once

typedef long long ll;

const int RANGE_SUM_N = 2e5 + 5;
ll rangeSumTree[4 * RANGE_SUM_N], rangeSumLazy[4 * RANGE_SUM_N];

void pullRangeSum(int x) {
	rangeSumTree[x] = rangeSumTree[2 * x] + rangeSumTree[2 * x + 1];
}

void applyRangeSum(int x, int l, int r, ll v) {
	rangeSumTree[x] += v * (r - l + 1);
	rangeSumLazy[x] += v;
}

void pushRangeSum(int x, int l, int r) {
	if (rangeSumLazy[x] == 0 || l == r) return;
	int m = (l + r) / 2;
	applyRangeSum(2 * x, l, m, rangeSumLazy[x]);
	applyRangeSum(2 * x + 1, m + 1, r, rangeSumLazy[x]);
	rangeSumLazy[x] = 0;
}

void buildRangeSum(int x, int l, int r, const vector<ll>& a) {
	rangeSumLazy[x] = 0;
	if (l == r) {
		rangeSumTree[x] = a[l];
		return;
	}
	int m = (l + r) / 2;
	buildRangeSum(2 * x, l, m, a);
	buildRangeSum(2 * x + 1, m + 1, r, a);
	pullRangeSum(x);
}

void addRangeSum(int x, int l, int r, int ql, int qr, ll v) {
	if (qr < l || r < ql) return;
	if (ql <= l && r <= qr) {
		applyRangeSum(x, l, r, v);
		return;
	}
	pushRangeSum(x, l, r);
	int m = (l + r) / 2;
	addRangeSum(2 * x, l, m, ql, qr, v);
	addRangeSum(2 * x + 1, m + 1, r, ql, qr, v);
	pullRangeSum(x);
}

ll queryRangeSum(int x, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) return 0;
	if (ql <= l && r <= qr) return rangeSumTree[x];
	pushRangeSum(x, l, r);
	int m = (l + r) / 2;
	return queryRangeSum(2 * x, l, m, ql, qr)
		+ queryRangeSum(2 * x + 1, m + 1, r, ql, qr);
}

// Usage: vector<ll> a(n + 1); buildRangeSum(1, 1, n, a);
// addRangeSum(1, 1, n, l, r, value);
// ll sum = queryRangeSum(1, 1, n, l, r);

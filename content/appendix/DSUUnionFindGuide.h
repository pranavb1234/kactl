/**
 * Author: Pranav Bhatia
 * Date: 2026-10-03
 * License: CC0
 * Source: User-provided DSU handbook, formatted for KACTL
 * Description: Union-Find with path compression, union by size, component count, and rollback.
 * Time: O(\alpha(N)) amortized per find/unite; rollback DSU O(\log N) per operation.
 */
#pragma once

// Standard DSU: use for undirected connectivity when edges are only added.
// unite(a,b) is true iff it actually merges two different components.
struct DSU {
	vector<int> parent, sz;
	int components;
	DSU(int n = 0) : parent(n), sz(n, 1), components(n) {
		iota(all(parent), 0);
	}
	int find(int x) {
		return parent[x] == x ? x : parent[x] = find(parent[x]); // path compression
	}
	bool unite(int a, int b) {
		a = find(a), b = find(b); // Always merge roots, never arbitrary nodes.
		if (a == b) return false;
		if (sz[a] < sz[b]) swap(a, b); // a becomes the larger/new root.
		parent[b] = a;
		sz[a] += sz[b];               // Merge all root metadata into a here.
		components--;
		return true;
	}
	bool same(int a, int b) { return find(a) == find(b); }
	int size(int x) { return sz[find(x)]; }
	int count() const { return components; }
};

// Basic usage (0-indexed): DSU dsu(n); dsu.unite(u,v); dsu.same(u,v); dsu.size(u).
// For 1-indexed input, allocate DSU dsu(n+1) and ignore index 0.
// To track sum/min/max/special-node count, keep an array at roots and combine data[a] with data[b]
// immediately after parent[b]=a. Example: sum[a]+=sum[b], mn[a]=min(mn[a],mn[b]).

// Undirected cycle / redundant edge: if (!dsu.unite(u,v)), u-v closes a cycle.
// Kruskal: sort edges by weight, then take every edge whose unite(u,v) succeeds.
struct Edge { int u, v, w; };
ll kruskal(int n, vector<Edge> edges) {
	sort(all(edges), [](const Edge& a, const Edge& b) { return a.w < b.w; });
	DSU dsu(n); ll cost = 0;
	for (auto e : edges) if (dsu.unite(e.u, e.v)) cost += e.w;
	return cost; // Check dsu.count()==1 if a connected MST is required.
}

// Grid DSU: map cell (r,c) to r*m+c, then unite valid neighboring cells.
int gridId(int r, int c, int m) { return r * m + c; }

// Rollback DSU: use for offline dynamic connectivity / segment-tree-over-time.
// Deliberately NO path compression: it changes too many parents to undo cheaply.
struct RollbackDSU {
	vector<int> parent, sz;
	struct Change { int child, oldSize; };
	vector<Change> history;
	int components;
	RollbackDSU(int n = 0) : parent(n), sz(n, 1), components(n) { iota(all(parent), 0); }
	int find(int x) { while (parent[x] != x) x = parent[x]; return x; }
	bool unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) { history.push_back({-1, -1}); return false; }
		if (sz[a] < sz[b]) swap(a, b);
		history.push_back({b, sz[a]});
		parent[b] = a; sz[a] += sz[b]; components--;
		return true;
	}
	int snapshot() const { return sz(history); }
	void rollback() {
		auto [b, oldSize] = history.back(); history.pop_back();
		if (b == -1) return;
		int a = parent[b];
		parent[b] = b; sz[a] = oldSize; components++;
	}
	void rollback(int snap) { while (sz(history) > snap) rollback(); }
};

// Recognition:
// merge groups / same component / add edges + connectivity / redundant edge / undirected cycle -> DSU.
// MST -> Kruskal + DSU. Grid regions -> DSU on cell ids. Arbitrary deletions -> reverse process or rollback DSU.
// For one fixed connected-component computation, DFS/BFS is often simpler. DSU is not for directed reachability
// or shortest paths (use SCC algorithms / Dijkstra as appropriate).

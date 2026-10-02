/**
 * Author: Pranav Bhatia
 * Date: 2026-10-03
 * License: CC0
 * Source: User-provided STL syntax reference, formatted for KACTL
 * Description: STL syntax families, iterators, containers, algorithms, and common traps.
 * Time: See individual operations.
 */
#pragma once

// SYNTAX FAMILIES
// container<type> object;        e.g. vector<int> v; map<string,int> mp;
// object.method(arguments);      e.g. v.push_back(10);
// algorithm(first, last);        [first,last): first included, last excluded.
// algorithm(first,last,comp);    e.g. sort(all(v), greater<int>());
// auto it = algorithm(...);      dereference a valid iterator with *it.

// VECTOR: v(n), v(n,value), v={...}, v.push_back(x), v.emplace_back(args...), v.pop_back().
// v[i], v.at(i), v.front(), v.back(), v.size(), v.empty(), v.clear(), v.resize(n), v.reserve(n).
// reserve changes capacity, NOT size. Cast size where a signed value is intended: int n=sz(v).
// v.assign(n,x); v.assign(other.begin(),other.end());

// ITERATORS
// begin/end; rbegin/rend; cbegin/cend. end() is one past last: never dereference it.
// *it gives value. ++it/--it move one step. next(it,k)/prev(it,k) return another iterator.
// advance(it,k) modifies it; distance(first,last) is O(1) for vector but may be O(N) for set/list.
// it+k only works on random-access iterators (vector/deque), not set/map iterators.

// SORTING: comparator must be a strict weak ordering: use <, NEVER <=.
// sort(all(v)); sort(all(v), greater<int>());
// sort(all(v), [](const auto& a,const auto& b) { return a.second < b.second; });
// stable_sort preserves equal-element order; partial_sort(begin,begin+k,end) sorts smallest k.
// nth_element(begin,begin+k,end): v[k] is kth smallest; other elements are not sorted, avg O(N).

// RANGE MODIFIERS
// reverse(all(v)); rotate(v.begin(),v.begin()+k,v.end());
// v.erase(unique(all(v)),v.end());               // unique only removes adjacent duplicates logically.
// sort(all(v)); v.erase(unique(all(v)),v.end()); // remove every duplicate.
// v.erase(remove(all(v),x),v.end());             // erase-remove idiom.
// v.erase(remove_if(all(v), [](int x){ return x % 2 == 0; }), v.end());

// SEARCHING (generic lower/upper_bound require range sorted by same comparator).
// find(all(v),x), find_if(...), count(all(v),x), count_if(...).
// binary_search(all(v),x); lower_bound(all(v),x): first >= x; upper_bound: first > x.
// int index=lower_bound(all(v),x)-v.begin();
// int occurrences=upper_bound(all(v),x)-lower_bound(all(v),x);
// auto [lo,hi]=equal_range(all(v),x);
// min_element, max_element, minmax_element, all_of, any_of, none_of.
// accumulate(all(v),0LL), iota(all(v),0), gcd(a,b), lcm(a,b).

// CONTAINERS
// vector: default dynamic array; O(1) index/back, amortized O(1) push_back.
// deque: O(1) indexing and both ends. list: O(1) insert/erase with iterator, no indexing.
// stack: LIFO (push/top/pop); queue: FIFO (push/front/back/pop).
// priority_queue<T>: max heap. priority_queue<T,vector<T>,greater<T>>: min heap.
// pair<int,int> p={x,y}; p.first/p.second. tuple<int,int,int> t={a,b,c}; auto [a,b,c]=t.
// array<int,N>: fixed size; bitset<N>: count/any/none/all/set/reset/flip/test.

// ORDERED ASSOCIATIVE CONTAINERS: O(log N).
// set: sorted unique. multiset: sorted duplicates. map: sorted key/value. multimap: duplicate keys.
// s.lower_bound(x), s.upper_bound(x), s.find(x), s.count(x), s.erase(x).
// Prefer s.lower_bound(x) over lower_bound(s.begin(),s.end(),x): member version is O(log N).
// multiset.erase(x) removes ALL copies; erase one with auto it=ms.find(x); if(it!=ms.end()) ms.erase(it).
// map[key] inserts a missing key. For lookup only, use mp.find(key) or mp.count(key).

// UNORDERED CONTAINERS: unordered_set/map, average O(1), unordered, worst case can degrade.
// For custom key, give a custom hash. Use map/set when sorted order or bounds are needed.

// PBDS (GNU extension): dynamic kth/rank queries in O(log N).
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T> using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,
//     tree_order_statistics_node_update>;
// st.order_of_key(x): number < x. *st.find_by_order(k): zero-indexed kth.
// Duplicates: tree<pair<T,int>,null_type,less<pair<T,int>>,rb_tree_tag,...>.

// STRING: s.size(), s[i], s.substr(pos,len), s.find(t), s.erase(pos,len), s.insert(pos,t),
// s.replace(pos,len,t), s.push_back(c), s.pop_back(), stoi/stoll, to_string.
// getline reads a line; after cin >> x, call cin.ignore(numeric_limits<streamsize>::max(),'\n') if needed.

// 2D / GRAPH SYNTAX
// vector<vector<int>> a(n, vector<int>(m, value));
// vector<vector<int>> adj(n); adj[u].push_back(v); adj[v].push_back(u); // undirected
// vector<vector<pair<int,int>>> wadj(n); wadj[u].push_back({v,w});

// CUSTOM ORDERING
// struct Compare { bool operator()(int a,int b) const { return a > b; } };
// set<int,greater<int>> descending; map<int,int,greater<int>> descendingKeys;
// struct PairHash { size_t operator()(const pair<int,int>& p) const {
//     return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1); } };

// CHOOSING A TOOL
// dynamic array -> vector; sorted unique -> set; sorted duplicates -> multiset;
// fast membership/frequency -> unordered_set/unordered_map; BFS -> queue; DFS -> stack;
// repeated min/max -> priority_queue; fixed bit operations -> bitset; kth/rank -> PBDS/nth_element.
// lower_bound = first >= x; upper_bound = first > x; monotone feasibility = binary search on answer.

// COMMON MISTAKES: dereferencing end(); unsorted lower_bound; forgetting erase after unique/remove;
// multiset.erase(x) deleting all copies; map[] inserting; pq.pop() returning no value (read top first);
// comparator <=; accumulate(...,0) overflowing int (use 0LL); and using bits/stdc++.h outside GNU judges.

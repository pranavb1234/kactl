/**
 * Author: Pranav Bhatia
 * Date: 2026-10-03
 * License: CC0
 * Source: Curated handbook index
 * Description: Match common problem clues to the algorithm or data structure to try first.
 * Time: Reference material.
 */
#pragma once

// START WITH CONSTRAINTS
// N <= 20: subsets / bitmask DP / TSP / assignment. N about 30..45: meet in the middle.
// N up to 2e5: usually O(N log N) or O(N). N up to 5000: O(N^2) may work.
// Huge exponent / n up to 1e18 with fixed linear transition: matrix exponentiation.

// ARRAYS / RANGE QUERIES
// Static range min/max/gcd, many queries, no updates -> sparse table (idempotent operation).
// Point updates plus range query -> segment tree or Fenwick tree.
// Range add/set plus range query -> lazy segment tree.
// Prefix/range sums with no updates -> prefix sums. Difference-array updates -> range add, final values.
// Many offline [L,R] queries with cheap add/remove -> Mo's algorithm.
// Historical array versions / kth smallest in a subarray -> persistent segment tree.
// Subarray sum equals K -> prefix sum + map. Subarray sum divisible by K -> prefix remainder collision.
// Maximum/minimum subarray sum -> Kadane / prefix sums. Fixed length K -> sliding window.

// SEARCHING / SORTING
// Monotone feasible answer (false...true) -> binary search on answer.
// First >= x / first > x in sorted array -> lower_bound / upper_bound.
// Pair target / closest pair after sorting -> two pointers.
// Huge values but relative order matters -> coordinate compression.
// kth element once -> nth_element. Dynamic kth/rank/median -> PBDS or a Fenwick/segment tree on ranks.

// GRAPHS: choose by edge weights and question type.
// Unweighted shortest path / fewest edges -> BFS. 0/1 weighted edges -> 0-1 BFS.
// Non-negative weighted shortest paths -> Dijkstra. Negative edges -> Bellman-Ford.
// All-pairs shortest paths with small N -> Floyd-Warshall. Directed acyclic graph -> topological DP.
// Directed mutual reachability / compress cycles -> SCC (Kosaraju or Tarjan), then condensation DAG DP.
// Undirected bridges, articulation points, biconnected components -> DFS low-link algorithms.
// Euler path/circuit -> EulerWalk. Bipartite matching -> Hopcroft-Karp.
// Max flow/min cut -> Dinic/Push-Relabel; costs on flow -> Min-Cost Max-Flow.
// MST -> Kruskal + DSU or Prim. Directed arborescence -> Directed MST.
// Many tree path queries/updates -> HLD. LCA / ancestor questions -> binary lifting.
// Tree-subtree statistics for every node -> DSU on Tree; subtree interval queries -> Euler tour + DS/Fenwick.

// CONNECTIVITY / DSU
// Edges only added; same component / merge groups / redundant edge / undirected cycle -> DSU.
// MST -> sort edges + DSU. Grid islands/regions -> DSU on id(r,c)=r*m+c.
// Edge deletions offline -> reverse processing, DSU rollback, or segment tree over time.
// Directed reachability and shortest paths are NOT standard DSU tasks.

// STRINGS
// Exact pattern occurrences -> KMP or Z-function. Prefix/suffix border or periodicity -> prefix function/Z.
// Substring equality / repeated substring (probabilistic) -> rolling hash; use double hash for safety.
// All palindromic centers -> Manacher. Simple palindrome -> two pointers.
// Longest substring with a frequency condition -> sliding window.
// Anagram / character counts -> frequency array or sorting. Lexicographic suffix ordering -> suffix array/tree.

// NUMBER THEORY / COMBINATORICS
// gcd/lcm / linear Diophantine equation -> Euclid or extended Euclid.
// Prime test / factorization for 64-bit numbers -> Miller-Rabin + Pollard Rho / factor routines.
// Congruences with compatible moduli -> CRT. Prime sieve / many prime queries -> Eratosthenes.
// a / b modulo prime -> multiply by b^(MOD-2), provided b is non-zero modulo MOD.
// Inverse under arbitrary modulus -> extended Euclid, only if gcd(a,MOD)=1.
// Many nCr/nPr queries under prime MOD with n<MOD -> factorial + inverse factorial.
// n >= MOD in binomial coefficient -> Lucas theorem or advanced combinatorics.
// Fixed-order recurrence / walks of exactly K edges -> matrix exponentiation.

// DYNAMIC PROGRAMMING
// Choice depends only on previous index/state -> standard DP.
// Transition is min/max of a range -> segment tree, Li Chao tree, convex hull trick, or optimized DP.
// Divide into groups with monotone optima -> divide-and-conquer DP optimization.
// Optimal binary-search-tree-like interval DP -> Knuth optimization.
// Subsets with N <= 20 -> bitmask DP. Knapsack -> DP by weight/value, bitset optimization if applicable.
// Independent impartial game components -> Grundy numbers xor. Single game state -> winning/losing DP.

// GEOMETRY
// Convex hull / extreme points -> ConvexHull. Closest pair -> divide and conquer.
// Segment/line intersection or distance -> geometry primitives. Point inside polygon -> winding/ray method.
// Circle intersection/tangents -> circle geometry routines. Minimum enclosing circle -> randomized MEC.

// QUICK CLUE MAP
// "exactly one component per move" + optimal play -> Nim/Grundy.
// "N around 40" + subset/partition -> MITM.
// "more objects than states" / prefix modulo collision -> pigeonhole principle.
// "dynamic sorted values" -> set/multiset; "fast unordered lookup" -> unordered_map/set.
// "repeated best available item" -> priority_queue. "Need predecessor/successor" -> set/map.
// "range updates and range sums" -> lazy segment tree. "No updates, many min queries" -> sparse table.
// "add edges and query connectivity" -> DSU. "cycles in directed graph, then do DP" -> SCC -> DAG.
// "large string matching" -> KMP/Z/hash. "small alphabet counts" -> frequency array.

// FINAL CHECK BEFORE CODING
// 1) Read limits. 2) Decide online vs offline. 3) Check update type. 4) Identify graph direction/weights.
// 5) Look for monotonicity, prefix states, independent components, or a fixed transition.
// 6) Confirm complexity and edge cases before choosing the implementation.

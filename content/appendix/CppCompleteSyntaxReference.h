/**
 * Author: Pranav Bhatia
 * Date: 2026-10-03
 * License: CC0
 * Source: User-provided C++ syntax reference, formatted for KACTL
 * Description: Core C++ syntax and contest-oriented language constructs.
 * Time: Reference material.
 */
#pragma once

// PROGRAM: #include <bits/stdc++.h> is a GNU shortcut; using namespace std; imports std names.
// int main() { ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }
// Comments: // one line, /* multiple lines */. Statement terminator: ;.

// TYPES / VARIABLES / CONSTANTS
// int x=10; long long y=1LL; double d; char c; bool ok; string s;
// const int x=10; constexpr int N=100000; using ll=long long; using pii=pair<int,int>.
// auto x=10; auto it=v.begin(); auto [a,b]=pair<int,int>{1,2};
// int x(10); int y{10}; 1LL*a*b prevents int multiplication overflow.

// INPUT / OUTPUT: cin >> a >> b; cout << a << ' ' << b << '\n';
// getline(cin,s) reads a line. Use '\n', not endl, in contests.

// CONTROL FLOW
// if (condition) { } else if (condition) { } else { }
// condition ? whenTrue : whenFalse;  switch(x) { case 1: break; default: break; }
// for (int i=0;i<n;i++) { }  for (auto& x:v) { }  while (condition) { } do { } while(condition);
// break exits nearest loop/switch; continue skips current loop iteration.

// FUNCTIONS: return_type name(parameters) { return value; }
int add(int a, int b) { return a + b; } // pass by value: copies.
void increment(int& x) { x++; }          // reference: changes original.
ll sumVector(const vector<int>& v) {     // const reference: no copy, read-only.
	return accumulate(all(v), 0LL);
}
// Default argument: void f(int x, int y=10); Function overloading: same name, different parameters.
// Recursive DFS: void dfs(int u,int p) { for(int v:adj[u]) if(v!=p) dfs(v,u); }

// LAMBDAS: [capture](parameters) -> returnType { body; }.
// [] captures none; [x] by value; [&x] by reference; [=] all used values; [&] all by reference.
auto descending = [](int a, int b) { return a > b; };
auto bySecond = [](const auto& a, const auto& b) { return a.second < b.second; };

// ARRAYS AND POINTERS
// int a[N]; int grid[R][C]; array<int,N> fixed; vector<vector<int>> mat(n,vector<int>(m,0));
// int* p=&x; *p accesses x. int& r=x is an alias to x.
// const int* p: cannot modify *p; int* const p: cannot change p; const int* const p: neither.
// sizeof(a)/sizeof(a[0]) works only for a real C array in its original scope.

// STRUCT / CLASS
struct Edge { int to, w; }; // struct members public by default.
struct Person {
	string name; int age;
	Person(string n, int a) : name(n), age(a) {} // member initializer list.
};
class Counter {
	int x = 0; // private by default.
public:
	void add(int v) { x += v; }
	int get() const { return x; } // const member function does not modify object.
};
// this->x means member x of current object. Child : public Parent is inheritance.
// virtual f() enables dynamic dispatch; f() override checks an override; virtual f()=0 is pure virtual.

// ENUM / NAMESPACE / SCOPE
enum class Color { Red, Green, Blue };
// namespace A { int x; }  A::x; std::vector<int>; ClassName::staticMember.
// static local keeps value between calls; static class member belongs to class.

// OPERATORS
// Arithmetic: + - * / %; assignment: = += -= *= /= %= &= |= ^= <<= >>=.
// Compare: == != < > <= >=. Logical: && || !. Bitwise: & | ^ ~ << >>.
// Parenthesize precedence-sensitive expressions: if ((x & (1LL << k)) != 0) { }.
// static_cast<int>(value) is preferred to a C-style cast (int)value.

// STRINGS AND STANDARD UTILITIES
// string s; s.size(); s[i]; s.substr(pos,len); s.find(t); s.erase(pos,len); s.insert(pos,t);
// stoi/stoll/stod; to_string(x); min({a,b,c}); max({a,b,c}); swap(a,b); gcd(a,b); lcm(a,b).
// bitset<32> b; b.set(i); b.reset(i); b.flip(i); b.test(i); b.count(); b.any(); b.none(); b.all().

// RANDOM / SHUFFLE (usually for stress testing).
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<int> dist(L,R); int x=dist(rng); shuffle(all(v),rng);

// FILE I/O (rare in online judges): ifstream fin("input.txt"); ofstream fout("output.txt");
// fin >> x; fout << x; Exceptions: try { } catch (const exception& e) { cerr << e.what(); }.

// IMPORTANT SYNTAX READING RULE: sort(v.begin(),v.end(),greater<int>()) means:
// algorithm name, then [first,last) iterators, then an optional comparator object.
// In it->first, -> dereferences a pointer/iterator then accesses its member.
// In vector<int>, <int> is a template argument; in object.method(args), . accesses a member.

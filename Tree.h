#ifndef TREE_H
#define TREE_H
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pll = pair <ll, ll>;
using vll = vector <ll>;

const ll MAXN = 1e5;
ll t[MAXN << 2];
ll lazy[MAXN << 2];

class Tree {
 private:
    ll n;
    void build(ll v, ll tl, ll tr) {
        if (tl == tr) {
            t[v] = a[tl];
            return;
        }
        ll tm = (tl + tr) >> 1;
        build(v << 1, tl, tm);
        build((v << 1) + 1, tm + 1, tr);
        t[v] = func(t[v << 1], t[(v << 1) + 1]);
    }
    void push(ll v, ll val) {
        lazy[v << 1] += val;
        lazy[(v << 1) + 1] += val;
        return;
    }
 public:
    vll a;
    function <ll (ll, ll)> func;
    Tree(const vll &a, auto func) {
        this -> a = a;
        this -> func = func;
        build(1, 0, a.size() - 1);
    }
    ll get_function(ll v, ll tl, ll tr, ll l, ll r) {
        if (tl > tr || tl > r || tr < l || l > r)
            return 0;
        if (lazy[v] != 0) {
            t[v] += lazy[v];
            if (tl != tr)
                push(v, lazy[v]);
            lazy[v] = 0;
        }
        if (tl >= l && tr <= r)
            return t[v];
        ll tm = (tl + tr) >> 1;
        ll f1 = get_function((v << 1), tl, tm, l, min(tm, r));
        ll f2 = get_function((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r);
        return func(f1, f2);
    }
    void update(ll v, ll tl, ll tr, ll i, ll val) {
        if ((MAXN << 2) <= v || v < 0) return;
        if (tl == tr) {
            t[v] = a[i] = val;
            return;
        }
        ll M = (tl + tr) >> 1;
        i <= M ? update((v << 1), tl, M, i, val) : update((v << 1) + 1, M + 1, tr, i, val);
        t[v] = func(t[(v << 1)], t[(v << 1) + 1]);
    }
    void update(ll v, ll tl, ll tr, ll l, ll r, ll val) {
        if (lazy[v] != 0) {
            t[v] += lazy[v];
            if (tl != tr)
                push(v, lazy[v]);
            lazy[v] = 0;
        }
        if (tl > tr || tl > l || tr < l || l > r) return;
        if (tl >= l && tr <= r) {
            t[v] += val;
            if (tl != tr)
                push(v, val);
            return;
        }
        ll tm = (tl + tr) >> 1;
        update((v << 1), tl, tm, l, min(tm, r), val);
        update((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, val);
        t[v] = func(t[v << 1], t[(v << 1) + 1]);
        return;
    }
    void print_Tree(void) {
        for (ll i = 1, m = 1; i < (a.size() << 2); m <<= 1) {
            for (ll k = 1; i < (a.size() << 2) && k <= m; ++k) {
                cout << t[i] << '\t';
                ++i;
            }
            cout << endl;
        }
        cout << endl;
    }
};

#endif // TREE_H

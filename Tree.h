#ifndef TREE_H
#define TREE_H
#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using namespace std;

class Tree {

private:
    ll n;
    vector <pair <ll, ll>> pair_tree;
    vector <ll> tree;
    void build(ll v, ll tl, ll tr) {
        if (tl == tr) {
            if (choice == "Pair") pair_tree[v] = b[tl];
            else tree[v] = a[tl];
            return;
        }
        ll tm = (tl + tr) >> 1;
        build((v << 1), tl, tm);
        build((v << 1) + 1, tm + 1, tr);
        if (choice == "Pair") {
            pair_tree[v].first = func(pair_tree[v << 1].first, pair_tree[(v << 1) + 1].first);
            pair_tree[v].second = func(pair_tree[v << 1].second, pair_tree[(v << 1) + 1].second);
        } else {
            tree[v] = func(tree[v << 1], tree[(v << 1) + 1]);
        }
    }

public:
    string choice;
    bool element_of_pair = false;
    vector <pair <ll, ll>> b;
    vector <ll> a;
    function <ll (ll, ll)> func;
    Tree(ll n, const vector <ll> &a, const vector <pair <ll, ll>> &b,
        const string &choice, function <ll (ll, ll)> func, bool element_of_pair) {
        this -> n = n;
        this -> a = a;
        this -> b = b;
        this -> choice = choice;
        this -> func = func;
        this -> element_of_pair = element_of_pair;
        tree.resize(n << 2);
        pair_tree.resize(n << 2);
        build(1, 0, n - 1);
    }
    ll get_function(ll v, ll tl, ll tr, ll l, ll r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return choice == "Pair" ? (!element_of_pair ? pair_tree[v].first : pair_tree[v].second) : tree[v];
        ll tm = (tl + tr) >> 1;
        return func(get_function((v << 1), tl, tm, l, min(r, tm)),
             get_function((v << 1) + 1, tm + 1, tr, max(l, tm + 1), r));
    }
    void update(ll v, ll tl, ll tr, ll i) {
        if (tree.size() <= v || v < 0) return;
        if (tl == tr) {
            if (choice != "Pair") tree[v] = a[i];
            else pair_tree[v] = b[i];
            return;
        }
        ll M = (tl + tr) >> 1;
        i <= M ? update((v << 1), tl, M, i) : update((v << 1) + 1, M + 1, tr, i);
        if (choice == "Pair") {
            if (!element_of_pair)
                pair_tree[v].first = func(pair_tree[(v << 1)].first, pair_tree[(v << 1) + 1].first);
            else
                pair_tree[v].second = func(pair_tree[(v << 1)].second, pair_tree[(v << 1) + 1].second);
        } else {
            tree[v] = func(tree[(v << 1)], tree[(v << 1) + 1]);
        }
    }
    void print(void) {
        for (ll i = 1, m = 1; i < tree.size(); m <<= 1) {
            for (ll k = 1; i < tree.size() && k <= m; ++k) {
                if (choice == "Pair")
                    cout << pair_tree[i].first << " " << pair_tree[i].second << '\t';
                else
                    cout << tree[i] << '\t';
                ++i;
            }
            cout << endl;
        }
        cout << endl;
        if (choice == "Pair") {
            for (auto [i, j] : b)
                cout << i << " " << j << endl;
            cout << endl;
        } else {
            for (ll i : a) cout << i << " ";
            cout << endl;
        }
    }
};

#endif // TREE_H

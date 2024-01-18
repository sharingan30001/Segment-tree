#include <bits/stdc++.h>
#include <Tree.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using namespace std;

ll sum(ll a, ll b) {
    return a + b;
}

ll max_el(ll a, ll b) {
    return max(a, b);
}

ll min_el(ll a, ll b) {
    return min(a, b);
}

signed main() {
    ll q, n, l, r, pos, val, val2;
    bool element_of_pair = false;
    vector <pair <ll, ll>> b;
    vector <ll> a;
    string choice, choice_func, request;
    function <ll (ll, ll)> func;
    cout << "Choose array size: ";
    cin >> n;
    cout << "Choose the segment tree mode:\n\"Pair\" : a tree with a pair of values in a leaf\n\"Vector\" : ordinary tree\n";
    cin >> choice;
    cout << "Enter the values of the array:\n";
    if (choice == "Pair") {
        b.resize(n);
        string mode;
        for (ll i = 0; i < n; ++i)
            cin >> b[i].first >> b[i].second;
        cout << "Choose which element will be used in the function\n";
        cout << "\"First\" : first element of pair\n\"Second\" : second element of pair\n";
        cin >> mode;
        if (mode == "Second") element_of_pair = true;
    } else {
        a.resize(n);
        for (ll i = 0; i < n; ++i)
            cin >> a[i];
    }
    cout << "Choose a function for the tree:\n";
    cout << "\"Sum\" : get the amount on the segment\n\"Max\" : get the max element on the segment\n";
    cout << "\"Min\" : get the min element on the segment\n";
    cin >> choice_func;
    if (choice_func == "Sum") func = sum;
    else if (choice_func == "Max") func = max_el;
    else func = min_el;
    Tree tree(n, a, b, choice, func, element_of_pair);
    cout << "Choose the number of requests ";
    cin >> q;
    cout << "There are 2 requests available to you:\n";
    cout << "\"get\" : get function on the segment L and R\n";
    cout << "\"change\" : change an array element at the pos position to the val element\n";
    cout << "\"print\" : print tree\n";
    while (q--) {
        cout << "Choose request: ";
        cin >> request;
        if (request == "get") {
            cout << "Choose L and R: ";
            cin >> l >> r;
            --l, --r;
            cout << tree.get_function(1, 0, n - 1, l, r) << "\n";
        } else if (request == "change") {
            cout << "Choose pos and val (if you use pair choose pair of val): ";
            cin >> pos >> val;
            if (choice == "Pair") cin >> val2;
            if (choice == "Vector")
                tree.a[pos] = val;
            else
                tree.b[pos] = make_pair(val, val2);
            tree.update(1, 0, n - 1, pos);
        } else {
            tree.print();
        }
    }
    return 0;
}

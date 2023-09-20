#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <cassert>
#define ff first

#define ss second
#define pb push_back
// #define int long long
using namespace std;

const int maxn = 5e5 + 5;
const int INF = 1e9;

struct Data {
    int pref, ans, size, suf;
    Data() {
        pref = 0;
        ans = 0;
        size = 0;
        suf = 0;
    }
};

Data combine(Data l, Data r) {
    Data data;
    data.pref = l.pref;
    if (l.pref == l.size)
        data.pref = l.size + r.pref;
    data.suf = r.suf;
    if (r.suf == r.size)
        data.suf = l.suf + r.suf;
    data.size = l.size + r.size;
    data.ans = max(max(l.suf + r.pref, r.ans), l.ans);
    return data;
}

struct ST {
    vector<Data> tree;
    ST() {
        tree.resize(4 * maxn);
    }
    void build(vector<int>& a, int v = 0, int vl = 0, int vr = maxn) {
        if (vr - vl == 1) {
            if (vl < a.size()) {
                if (a[vl] == 0) {
                    tree[v].pref = 1;
                    tree[v].ans = 1;
                    tree[v].suf = 1;
                    tree[v].size = 1;
                }
                else {
                    tree[v].pref = 0;
                    tree[v].ans = 0;
                    tree[v].suf = 0;
                    tree[v].size = 1;
                }
            }
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v + 1, vl, vm);
        build(a, 2 * v + 2, vm, vr);
        tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
    }

    Data query(int lq, int rq, int v = 0, int vl = 0, int vr = maxn) {
        if (vl >= rq || vr <= lq) {
            return Data();
        }
        if (vl >= lq && vr <= rq) {
            return tree[v];
        }
        int vm = (vl + vr) / 2;
        Data lans, rans;
        lans = query(lq, rq, 2 * v + 1, vl, vm);
        rans = query(lq, rq, 2 * v + 2, vm, vr);
        return combine(lans, rans);
    }

    void update(int pos, int val, int v = 0, int vl = 0, int vr = maxn) {
        if (vr - vl == 1) {
            if (val == 0) {
                tree[v].pref = 1;
                tree[v].ans = 1;
                tree[v].suf = 1;
                tree[v].size = 1;
            }
            else {
                tree[v].pref = 0;
                tree[v].ans = 0;
                tree[v].suf = 0;
                tree[v].size = 1;
            }
            return;
        }
        int vm = (vl + vr) / 2;
        if (pos < vm) {
            update(pos, val, 2 * v + 1, vl, vm);
        }
        else {
            update(pos, val, 2 * v + 2, vm, vr);
        }
        tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // freopen("kthzero.in", "r", stdin);
    // freopen("kthzero.out", "w", stdout);
    int t = 1;
    // cin >> t;
    while(t--){
        ten();
    }
    return 0;
}
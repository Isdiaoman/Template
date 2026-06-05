//动态开点, T 为结点存储的信息，_T 为区间端点类型（int/i64）
// 根为 1
template<typename T, typename _T = int>
struct SegTree {

    vector<T>sum, tag;
    vector<int>ls, rs;
    vector<_T>l, r;
    int N, tot;

    SegTree(_T _L, _T _R, int _q) {// 范围[L,R]，预估add _q次
        init(_L, _R, _q);
    }

    void init(_T _L, _T _R, int _q) {
        N = _q * 40;
        sum = tag = vector<T>(N);
        ls = rs = vector<int>(N);
        l = r = vector<_T>(N);
        tot = 1;
        l[1] = _L, r[1] = _R;
    }

    int open(_T _L, _T _R) {//开点，维护[L,R]
        ++tot;
        l[tot] = _L;
        r[tot] = _R;
        return tot;
    }

    void update(T x, int ind) {
        sum[ind] += (r[ind] - l[ind] + 1) * x;
        tag[ind] += x;
    }

    void add(_T L, _T R, T x, int ind = 1) {
        if (l[ind] >= L && r[ind] <= R) {
            update(x, ind);
            return;
        }
        down(ind);
        _T mid = l[ind] + r[ind] >> 1;
        if (mid >= L)add(L, R, x, ls[ind]);
        if (mid + 1 <= R)add(L, R, x, rs[ind]);
        up(ind);
    }

    void down(int ind) {
        _T mid = l[ind] + r[ind] >> 1;
        if (!ls[ind])ls[ind] = open(l[ind], mid);
        if (!rs[ind])rs[ind] = open(mid + 1, r[ind]);
        update(tag[ind], ls[ind]);
        update(tag[ind], rs[ind]);
        tag[ind] = 0;
    }

    void up(int ind) {
        sum[ind] = sum[ls[ind]] + sum[rs[ind]];
    }

    T query(_T L, _T R, int ind = 1) {
        if (l[ind] >= L && r[ind] <= R)return sum[ind];
        down(ind);
        _T mid = l[ind] + r[ind] >> 1;
        T res = 0;
        if (mid >= L)res += query(L, R, ls[ind]);
        if (mid + 1 <= R)res += query(L, R, rs[ind]);
        return res;
    }

};
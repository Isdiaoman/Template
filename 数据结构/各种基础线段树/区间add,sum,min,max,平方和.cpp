// Segment 普通线段树  维护区间加，查询区间和/max/min
// T 为存储结构， _L, _R 为存储范围
template<typename T>
struct SegTree {

    vector<array<int, 2>>range;// [L,R] 表示维护的范围
    vector<T>sm;// 总和
    vector<T>mx;// 最大值
    vector<T>mn;// 最小值
    vector<T>lz;// 懒标记
    vector<T>s2;// 平方和

    SegTree(int _L, int _R) {// 维护索引 [_L,_R]
        init(_L, _R);
    }

    SegTree(int _n) {// 维护索引 [1,_n]
        init(1, _n);
    }

    void init(int _L, int _R) {// 初始化，维护索引 [_L,_R]
        const int N = (_R - _L + 1) << 2;
        range = vector<array<int, 2>>(N);
        sm = vector<T>(N);
        mx = vector<T>(N);
        mn = vector<T>(N);
        lz = vector<T>(N);
        s2 = vector<T>(N);
        build(_L, _R);
    }

    void build(int _L, int _R, int ind = 1) {// 建树
        range[ind] = { _L,_R };
        if (_L == _R)return;
        int mid = _L + (_R - _L) / 2;
        build(_L, mid, ind << 1);
        build(mid + 1, _R, ind << 1 | 1);
    }

    void down(int ind) {// 下发懒标记
        if (lz[ind] == 0)return;
        update(lz[ind], ind << 1);
        update(lz[ind], ind << 1 | 1);
        lz[ind] = 0;
    }

    void up(int ind) {// 整合儿子信息
        sm[ind] = sm[ind << 1] + sm[ind << 1 | 1];
        mx[ind] = max(mx[ind << 1], mx[ind << 1 | 1]);
        mn[ind] = min(mn[ind << 1], mn[ind << 1 | 1]);
        s2[ind] = s2[ind << 1] + s2[ind << 1 | 1];
    }

    void update(T x, int ind) {// 更新单个结点
        auto &[L, R] = range[ind];
        s2[ind] = s2[ind] + x * 2 * sm[ind] + x * x * (R - L + 1);
        sm[ind] = sm[ind] + x * (R - L + 1);
        mx[ind] = mx[ind] + x;
        mn[ind] = mn[ind] + x;
        lz[ind] = lz[ind] + x;
    }

    void add(int l, int r, T x, int ind = 1) {// 给区间 [l,r] + x
        auto &[L, R] = range[ind];
        if (R < l || r < L)return;
        if (l <= L && R <= r) {
            update(x, ind);
            return;
        }
        down(ind);
        add(l, r, x, ind << 1);
        add(l, r, x, ind << 1 | 1);
        up(ind);
    }

    T qrymx(int l, int r, int ind = 1) {// 查询区间最大值
        auto &[L, R] = range[ind];
        if (R < l || r < L)return numeric_limits<T>::lowest();
        if (l <= L && R <= r)return mx[ind];
        down(ind);
        return max(qrymx(l, r, ind << 1), qrymx(l, r, ind << 1 | 1));
    }

    T qrymn(int l, int r, int ind = 1) {// 查询区间最小值
        auto &[L, R] = range[ind];
        if (R < l || r < L)return numeric_limits<T>::max();
        if (l <= L && R <= r)return mn[ind];
        down(ind);
        return min(qrymn(l, r, ind << 1), qrymn(l, r, ind << 1 | 1));
    }

    T qrysm(int l, int r, int ind = 1) {// 查询区间 和
        auto &[L, R] = range[ind];
        if (R < l || r < L)return 0;
        if (l <= L && R <= r)return sm[ind];
        down(ind);
        return qrysm(l, r, ind << 1) + qrysm(l, r, ind << 1 | 1);
    }

    T qrys2(int l, int r, int ind = 1) {// 查询区间 平方和
        auto &[L, R] = range[ind];
        if (R < l || r < L)return 0;
        if (l <= L && R <= r)return s2[ind];
        down(ind);
        return qrys2(l, r, ind << 1) + qrys2(l, r, ind << 1 | 1);
    }
};
#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

// https://infoarena.ro/job_detail/2444004?action=view-source

class fenwickTree
{
private:
#define uint unsigned int
#define lsb(x) (x)&(-x)
#define swp(a,b) (a)^=(b),(b)^=(a),(a)^=(b)
#define BIT_CHECK_CREATED(ret) if (!created) return ret
#define BIT_ERROR 2147483647
    int *tree;
    bool created;
    uint n;
    void updatee(uint poz, int add)
    {
        for (; poz<=n; poz+=lsb(poz))
            tree[poz]+=add;
    }
    int queryy(uint poz)
    {
        int ret=0;
        for (; poz; poz-=lsb(poz))
            ret+=tree[poz];
        return ret;
    }
public:
    fenwickTree():tree(nullptr), created(false) {}
    bool create(uint sz)
    {
        if (created) return false;
        tree = new int[sz + 2];
        if (tree == nullptr) return false;
        n = sz + 2;
        for (uint i=0; i<n; ++i) tree[i] = 0;
        created = true;
        return true;
    }
    bool update(uint poz, int add)
    {
        BIT_CHECK_CREATED(false);
        if (poz >= n) return false;
        updatee(poz, add);
        return true;
    }
    int query(uint poz)
    {
        BIT_CHECK_CREATED(BIT_ERROR);
        if (poz >= n) return BIT_ERROR;
        return queryy(poz);
    }
    int query(uint left, uint right)
    {
        BIT_CHECK_CREATED(BIT_ERROR);
        if (left > right) swp(left, right);
        if (right >= n) return BIT_ERROR;
        return queryy(right) - queryy(left-1);
    }
#undef swp
};

#endif

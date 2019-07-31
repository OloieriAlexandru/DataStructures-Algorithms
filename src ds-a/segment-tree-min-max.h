#ifndef SEG_TREE_MIN_MAX.H
#define SEG_TREE_MIN_MAX.H
#include <vector>
#include <limits>

// https://infoarena.ro/job_detail/2443989?action=view-source

class segmentTreeMinMax
{
private:
#define left node<<1
#define right node<<1|1
#define mi(a,b) (a)<(b)?(a):(b)
#define ma(a,b) (a)>(b)?(a):(b)
#define swp(a,b) (a)^=(b),(b)^=(a),(a)^=(b)
#define uint unsigned int
#define SEG_TREE_ERROR 2147483647
#define SEG_TREE_CHECK_CREATED(ret) if (!created) return ret
    static const int intMin = std::numeric_limits<int>::min();
    static const int intMax = std::numeric_limits<int>::max();
    struct segTreeNode
    {
        int minn, maxx;
        segTreeNode(int value):minn(value), maxx(value) {}
        segTreeNode():minn(intMax), maxx(intMin) {}
    };
    segTreeNode *tree;
    bool created;
    uint n;
    void updateNode(uint node)
    {
        tree[node].minn = mi(tree[left].minn, tree[right].minn);
        tree[node].maxx = ma(tree[left].maxx, tree[right].maxx);
    }
    void build(uint node, uint l, uint r, int arr[])
    {
        if (l == r)
        {
            tree[node] = segTreeNode(arr[l]);
            return;
        }
        uint mid = (l + r) / 2;
        build(left, l, mid, arr);
        build(right, mid+1, r, arr);
        updateNode(node);
    }
    int queryMin(uint node, uint l, uint r, uint st, uint dr)
    {
        if (st<=l&&r<=dr) return tree[node].minn;
        uint mid = (l+r)/2;
        int ret = intMax;
        if (st<=mid)
            ret = queryMin(left,l,mid,st,dr);
        if (dr>mid)
        {
            int val = queryMin(right,mid+1,r,st,dr);
            ret = mi(ret,val);
        }
        return ret;
    }
    int queryMax(uint node, uint l, uint r, uint st, uint dr)
    {
        if (st<=l&&r<=dr) return tree[node].maxx;
        uint mid = (l+r)/2;
        int ret = intMin;
        if (st<=mid)
            ret = queryMax(left,l,mid,st,dr);
        if (dr>mid)
        {
            int val = queryMax(right,mid+1,r,st,dr);
            ret = ma(ret,val);
        }
        return ret;
    }
    void update(uint node, uint l, uint r, uint poz, int x)
    {
        if (l == r)
        {
            tree[node] = x;
            return;
        }
        uint mid = (l+r)/2;
        if (poz<=mid)
            update(left,l,mid,poz,x);
        else
            update(right,mid+1,r,poz,x);
        updateNode(node);
    }
public:
    segmentTreeMinMax():tree(nullptr), created(false) { }
    bool create(uint sz)
    {
        if (created) return false;
        tree = new segTreeNode[sz * 4 + 4];
        if (tree == nullptr) return false;
        created = true;
        n=sz;
        return true;
    }
    bool create(int a[], uint sz)
    {
        if (created) return false;
        tree = new segTreeNode[sz * 4 + 4];
        if (tree == nullptr) return false;
        created = true;
        n=sz;
        build(1, 1, n, a);
        return true;
    }
    bool update(uint poz, int val)
    {
        SEG_TREE_CHECK_CREATED(SEG_TREE_ERROR);
        if (poz > n) return false;
        update(1,1,n,poz,val);
        return true;
    }
    int queryMin(uint l, uint r)
    {
        SEG_TREE_CHECK_CREATED(SEG_TREE_ERROR);
        if (l > r) swp(l,r);
        if (r > n) return SEG_TREE_ERROR;
        return queryMin(1,1,n,l,r);
    }
    int queryMax(uint l, uint r)
    {
        SEG_TREE_CHECK_CREATED(SEG_TREE_ERROR);
        if (l > r) swp(l,r);
        if (r > n) return SEG_TREE_ERROR;
        return queryMax(1,1,n,l,r);
    }
#undef left
#undef right
};

#endif

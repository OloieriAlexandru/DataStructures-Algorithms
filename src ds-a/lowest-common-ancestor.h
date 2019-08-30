#ifndef LOWEST_COMMON_ANCESTOR_H
#define LOWEST_COMMON_ANCESTOR_H
#include <vector>
#include "range-minimum-query.h"

// https://infoarena.ro/job_detail/2452315?action=view-source

class lca
{
private:
#define uint unsigned int
#define LCA_CHECK_CREATED(ret) if (!created) return ret
#define LCA_ERROR 4294967295
#define pb push_back
    rangeMinimumQuery rmq;
    std::vector<uint>*tree;
    uint *euler, *firstAppearence, *height;
    uint n, nw, h;
    bool created;
    void dfs(int k)
    {
        euler[++nw] = k;
        height[nw] = h;
        firstAppearence[k] = nw;
        for (uint i=0; i<tree[k].size(); ++i)
        {
            ++h;
            dfs(tree[k][i]);
            --h;
            euler[++nw] = k;
            height[nw] = h;
        }
    }
public:
    lca(): tree(nullptr), firstAppearence(nullptr), height(nullptr), created(false) {}
    bool create(uint maxNodes)
    {
        if (created) return false;
        n = maxNodes + 1;

        euler = new uint[2 * n];
        if (euler == nullptr)
            return false;
        firstAppearence = new uint[n];
        if (euler == nullptr)
        {
            delete[] euler;
            return false;
        }
        height = new uint[2 * n];
        if (euler == nullptr)
        {
            delete[] euler;
            delete[] firstAppearence;
            return false;
        }
        tree = new std::vector<uint>[n];
        if (tree == nullptr)
        {
            delete[] euler;
            delete[] firstAppearence;
            delete[] height;
            return false;
        }
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y)
    {
        LCA_CHECK_CREATED(false);
        if (x > n || y > n) return false;
        tree[x].pb(y);
        return true;
    }
    bool computeRmq()
    {
        LCA_CHECK_CREATED(false);
        nw = 0, h = 0;
        dfs(1);
        if (!rmq.create(nw, (int*)height))
            return false;
        return true;
    }
    uint query(uint x, uint y)
    {
        LCA_CHECK_CREATED(LCA_ERROR);
        if (x > n || y > n) return false;
        uint l, r;
        l = firstAppearence[x];
        r = firstAppearence[y];
        int pos = rmq.queryPoz(l, r);
        if (pos == RMQ_ERROR)
            return LCA_ERROR;
        return euler[pos];
    }
};

#endif

#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H
#include <cstring>

// https://infoarena.ro/job_detail/2443999?action=view-source

class disjointSetUnion
{
private:
#define uint unsigned int
#define DSU_ERROR 4294967295
#define DSU_CHECK_CREATED(ret) if (!created) return ret
    uint *father, *height;
    bool created;
    uint n;
    void unionnn(uint a, uint b)
    {
        if (height[a] > height[b]) father[b] = a;
        else if (height[b] > height[a]) father[a] = b;
        else father[b] = a, ++height[b];
    }
    uint finddd(uint x)
    {
        uint cx = x, up;
        while (father[x])
            x = father[x];
        if (x != cx)
            while (father[cx])
                up=father[cx], father[cx]=x, cx=up;
        return x;
    }
public:
    disjointSetUnion(): father(nullptr), height(nullptr), created(false) {}
    bool create(uint sz)
    {
        if (created) return false;
        father = new uint[sz + 2];
        if (father == nullptr) return false;
        height = new uint[sz + 2];
        if (height == nullptr)
        {
            delete[] father;
            return false;
        }
        n = sz + 2;
        for (uint i=0; i<n; ++i) father[i]=0,height[i]=0;
        created = true;
        return true;
    }
    bool unionn(uint a, uint b)
    {
        DSU_CHECK_CREATED(false);
        if (a >= n || b >= n) return false;
        unionnn(finddd(a),finddd(b));
        return true;
    }
    uint findd(uint x)
    {
        DSU_CHECK_CREATED(DSU_ERROR);
        if (x >= n) return DSU_ERROR;
        return finddd(x);
    }
    bool sameset(uint a, uint b)
    {
        DSU_CHECK_CREATED(false);
        if (a >= n || b >= n) return false;
        return finddd(a) == finddd(b);
    }
};

#endif

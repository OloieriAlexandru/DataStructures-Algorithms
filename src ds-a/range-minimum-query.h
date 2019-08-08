#ifndef RANGE_MINIMUM_QUERY_H
#define RANGE_MINIMUM_QUERY_H

// https://infoarena.ro/job_detail/2444561?action=view-source

class rangeMinimumQuery
{
private:
#define RMQ_CHECK_CREATED(ret) if (!created) return ret
#define RMQ_ERROR 2147483647
#define swp(a,b) (a)^=(b),(b)^=(a),(a)^=b;
#define uint unsigned int
    uint **rmq ,*v;
    bool created;
    uint n, dist, logg2, add;
    uint log2(uint x)
    {
        if (x <= 1) return 0;
        uint ans = 0, p2 = 1;
        while (true)
        {
            if (p2 > x) return ans - 1;
            ++ans, p2 *= 2;
        }
    }
public:
    rangeMinimumQuery(): created(false), rmq(nullptr), v(nullptr) {}
    bool create(uint sz, int a[])
    {
        if (created) return false;
        v = new uint[sz + 1];
        if (v == nullptr) return false;
        for (uint i=0;i<=sz;++i)
            v[i] = a[i];
        rmq = new uint*[sz + 1];
        if (rmq == nullptr) return false;
        n = sz + 1;
        uint l2 = log2(n);
        for (uint i=0;i<n;++i)
        {
            rmq[i] = nullptr;
            rmq[i] = new uint[l2];
            if (rmq[i] == nullptr)
            {
                for (uint j=0;j<i;++j)
                {
                    delete[] rmq[j];
                }
                delete[] rmq;
                return false;
            }
        }
        for (uint i=1;i<n;++i)
            rmq[i][0] = i;
        uint shf, secshf;
        for (uint j=1;(1u<<j)<n;++j)
        {
            shf = 1u<<j;
            for (uint i=1;i+shf-1<n;++i)
            {
                secshf = 1<<(j-1);
                if (a[rmq[i][j-1]] < a[rmq[i+secshf][j-1]])
                    rmq[i][j] = rmq[i][j-1];
                else
                    rmq[i][j] = rmq[i+secshf][j-1];
            }
        }
        created = true;
        return true;
    }
    int query(uint l, uint r)
    {
        RMQ_CHECK_CREATED(RMQ_ERROR);
        if (l > r) swp(l,r);
        if (r >= n) return RMQ_ERROR;
        dist = r - l + 1;
        logg2 = log2(dist);
        add = dist - (1u<<logg2);
        if (v[rmq[l][logg2]] < v[rmq[l+add][logg2]])
            return v[rmq[l][logg2]];
        return v[rmq[l+add][logg2]];
    }
    #undef swp
};

#endif

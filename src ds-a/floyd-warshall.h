#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H
#include <vector>

// https://infoarena.ro/job_detail/2451907?action=view-source

class floydWarshall
{
#define inf 999999999
#define uint unsigned int
    std::vector<std::vector<uint>>dist;
    uint n;
    bool computeDists(std::vector<std::vector<uint>> &ret, uint n)
    {
        if (n == 0) return false;
        for (uint i=1; i<=n; ++i)
            for (uint j=1; j<=n; ++j)
                if (i != j && !ret[i][j])
                    ret[i][j] = inf;
        for (uint k=1; k<=n; ++k)
            for (uint i=1; i<=n; ++i)
                for (uint j=1; j<=n; ++j)
                    if (ret[i][k] + ret[k][j] < ret[i][j])
                        ret[i][j] = ret[i][k] + ret[k][j];
        for (uint i=1; i<=n; ++i)
            for (uint j=1; j<=n; ++j)
                if (ret[i][j] == inf)
                    ret[i][j] = 0;
        return true;
    }
public:
    bool setNumberOfNodes(uint n)
    {
        if (n == 0) return false;
        dist.resize(n+1);
        for (uint i=1; i<=n; ++i)
            dist[i].resize(n+1, 0);
        this->n = n;
        return true;
    }
    bool addEdge(uint x, uint y, uint d)
    {
        if (x > n || y > n) return false;
        dist[x][y] = d;
        return true;
    }
    std::vector<std::vector<uint>> getDistMatrix()
    {
        std::vector<std::vector<uint>> ret = dist;
        computeDists(ret, n);
        return ret;
    }
    bool computeDistMatrix(std::vector<std::vector<uint>> &ans)
    {
        uint n = ans.size() - 1;
        return computeDists(ans, n);
    }
};

#endif

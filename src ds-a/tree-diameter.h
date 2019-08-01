#ifndef TREE_DIAMETER_H
#define TREE_DIAMETER_H
#include <vector>

// https://infoarena.ro/job_detail/2444965?action=view-source

class treeDiameter
{
private:
#define TREE_CHECK_CREATED(ret) if (!created) return ret
#define TREE_ERROR 4294967295
#define uint unsigned int
#define pb push_back
    std::vector<uint>*edges;
    bool created, *visited;
    uint n, edgeCount;
    bool df(uint k, uint lst)
    {
        visited[k] = true;
        for (uint i=0;i<edges[k].size();++i)
        {
            if (visited[edges[k][i]] && lst != edges[k][i]) return false;
            if (visited[edges[k][i]]) continue;
            return df(edges[k][i], k);
        }
        return true;
    }
    bool isTree()
    {
        if (edgeCount + 2 != n) return false;
        for (uint i=0;i<n;++i)
            visited[i] = false;
        return df(1, TREE_ERROR);
    }
    void dfs(uint k, uint lst, uint &maxx, uint &maxxN, uint act)
    {
        if (act > maxx)
            maxx = act, maxxN = k;
        for (uint i=0;i<edges[k].size();++i)
        {
            if (edges[k][i] == lst) continue;
            dfs(edges[k][i], k, maxx, maxxN, act + 1);
        }
    }
public:
    treeDiameter(): edges(nullptr), created(false), edgeCount(0) {}
    bool create(uint sz)
    {
        if (created) return false;
        edges = new std::vector<uint>[sz+2];
        if (edges == nullptr) return false;
        visited = new bool[sz + 2];
        if (visited == nullptr)
        {
            delete[] edges;
            return false;
        }
        n = sz + 1;
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y)
    {
        TREE_CHECK_CREATED(false);
        if (x >= n || y >= n || !x || !y) return false;
        edges[x].pb(y);
        edges[y].pb(x);
        ++edgeCount;
        return true;
    }
    uint calcDiameter()
    {
        TREE_CHECK_CREATED(TREE_ERROR);
        if (!isTree()) return TREE_ERROR;
        uint ans = 0, node, altNode;
        dfs(1, TREE_ERROR, ans, node, 0);
        ans = 0;
        dfs(node, TREE_ERROR, ans, altNode, 0);
        return ans + 1;
    }
};

#endif

#ifndef GRAPH_DFS_BFS.h
#define GRAPH_DFS_BFS.h
#include <vector>
#include <queue>
#include <utility>

// https://infoarena.ro/job_detail/2444962?action=view-source
// https://infoarena.ro/job_detail/2444964?action=view-source

class graph
{
private:
#define uint unsigned int
#define GRAPH_CHECK_CREATED(ret) if (!created) return ret
#define GRAPH_ERROR 4294967295
#define puu std::pair<uint,uint>
#define mkp std::make_pair
#define pb push_back
    std::vector<uint>*g;
    uint n;
    bool created, unidirected, *visited;
    void df(uint k, std::vector<uint>*vct = nullptr)
    {
        visited[k] = true;
        if (vct != nullptr)
            vct->push_back(k);
        for (uint i=0; i<g[k].size(); ++i)
        {
            if (visited[g[k][i]]) continue;
            df(g[k][i], vct);
        }
    }
    void bf(uint start, std::vector<int>&minDist)
    {
        minDist.resize(n, -1);
        std::queue<puu> q;
        for (uint i=0; i<n; ++i)
            visited[i]=0;
        q.push(mkp(start,0));
        visited[start] = true;
        puu act;
        while (!q.empty())
        {
            act = q.front();
            q.pop();
            minDist[act.first] = act.second;
            for (uint i=0; i<g[act.first].size(); ++i)
            {
                if (visited[g[act.first][i]]) continue;
                visited[g[act.first][i]] = true;
                q.push(mkp(g[act.first][i],act.second+1));
            }
        }
    }
public:
    graph():created(false), g(nullptr), visited(nullptr) {}
    bool create(uint sz, bool uni = false)
    {
        if (created) return false;
        g = new vector<uint>[sz + 1];
        if (g == nullptr) return false;
        visited = new bool[sz + 1];
        if (visited == nullptr)
        {
            delete[] g;
            return false;
        }
        n = sz + 1;
        unidirected = uni;
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y)
    {
        GRAPH_CHECK_CREATED(false);
        if (x >= n || y >= n || !x || !y) return false;
        g[x].pb(y);
        if (!unidirected) g[y].pb(x);
        return true;
    }
    uint getCCCount()
    {
        GRAPH_CHECK_CREATED(GRAPH_ERROR);
        uint ret = 0;
        for (uint i=1; i<n; ++i)
            visited[i] = false;
        for (uint i=1; i<n; ++i)
            if (!visited[i])
            {
                ++ret;
                df(i);
            }
        return ret;
    }
    bool getNodeCC(uint node, std::vector<uint> &ans)
    {
        GRAPH_CHECK_CREATED(false);
        if (node >= n || !node) return false;
        ans.clear();
        df(node, &ans);
        return true;
    }
    bool getMinDistanceFromNode(uint node, std::vector<int> &ans)
    {
        GRAPH_CHECK_CREATED(false);
        if (node >= n || !node) return false;
        ans.clear();
        bf(node, ans);
        return true;
    }
};

#endif

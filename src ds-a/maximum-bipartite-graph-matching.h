#ifndef MAXIMUM_BIPARTITE_GRAPH_MATCHING_H
#define MAXIMUM_BIPARTITE_GRAPH_MATCHING_H
#include <vector>
#include <utility>

// https://infoarena.ro/job_detail/2444549?action=view-source

class maximumBipartiteMatching
{
private:
#define uint unsigned int
#define pb push_back
#define mkp std::make_pair
#define MAX_BIPARTITE_MATCHING_CHECK_CREATED(ret) if(!created) return ret
    uint *lft, *rgh;
    bool *visited;
    std::vector<uint> *graph;
    uint n, m;
    bool created;
    bool cup(uint node)
    {
        if (visited[node]) return false;
        visited[node] = true;
        for (uint i=0; i<graph[node].size(); ++i)
        {
            if (rgh[graph[node][i]]) continue;
            lft[node] = graph[node][i];
            rgh[graph[node][i]] = node;
            return true;
        }
        for (uint i=0; i<graph[node].size(); ++i)
            if (cup(rgh[graph[node][i]]))
            {
                lft[node] = graph[node][i];
                rgh[graph[node][i]] = node;
                return true;
            }
        return false;
    }
public:
    maximumBipartiteMatching():
        lft(nullptr), rgh(nullptr), graph(nullptr), created(false), visited(nullptr) {}
    bool create(uint szLeft, uint szRight)
    {
        if (created) return false;
        lft = new uint[szLeft + 1];
        if (lft == nullptr) return false;
        rgh = new uint[szRight + 1];
        if (rgh == nullptr)
        {
            delete[] lft;
            return false;
        }
        visited = new bool[szLeft + 1];
        if (visited == nullptr)
        {
            delete[] lft;
            delete[] rgh;
            return false;
        }
        graph = new std::vector<uint>[szLeft + 1];
        n = szLeft + 1;
        m = szRight + 1;
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y)
    {
        MAX_BIPARTITE_MATCHING_CHECK_CREATED(false);
        if (x >= n || y >= m) return false;
        graph[x].pb(y);
        return true;
    }
    bool computeMaxCoupling(std::vector<std::pair<uint,uint>> &ans)
    {
        MAX_BIPARTITE_MATCHING_CHECK_CREATED(false);
        for (uint i=0;i<n;++i)
            lft[i] = 0;
        for (uint i=0;i<m;++i)
            rgh[i] = 0;
        bool ok = true;
        ans.clear();
        while (ok)
        {
            ok = false;
            for (uint i=0;i<n;++i)
                visited[i] = 0;
            for (uint i=1;i<n;++i)
                if (!visited[i] && !lft[i])
                    if (cup(i))
                        ok = true;
        }
        for (uint i=1;i<n;++i)
            if (lft[i])
                ans.pb(mkp(i,lft[i]));
        return true;
    }
};

#endif

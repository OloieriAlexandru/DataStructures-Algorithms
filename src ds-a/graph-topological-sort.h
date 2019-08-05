#ifndef GRAPH_TOPOLOGICAL_SORT_H
#define GRAPH_TOPOLOGICAL_SORT_H
#include <vector>
#include <queue>

// https://infoarena.ro/job_detail/2445906?action=view-source

class graphTopologicalSort
{
private:
#define uint unsigned int
#define pb push_back
#define G_TOPOLOGICAL_SORT_CHECK_CREATED(ret) if (!created) return ret
#define G_TOPOLOGICAL_SORT_CIRCUIT 2
#define G_TOPOLOGICAL_SORT_OK 1
#define G_TOPOLOGICAL_SORT_ERROR 3
    bool created;
    std::vector<uint>*g;
    uint *di, *dc, n;
public:
    graphTopologicalSort(): g(nullptr), di(nullptr), dc(nullptr), created(false){}
    bool create(uint sz)
    {
        if (created) return false;
        g = new std::vector<uint>[sz + 2];
        if (g == nullptr) return false;
        di = new uint[sz + 2];
        if (di == nullptr)
        {
            delete[] g;
            return false;
        }
        dc = new uint[sz + 2];
        if (dc == nullptr)
        {
            delete[] g;
            delete[] di;
            return false;
        }
        n = sz;
        for (uint i=0;i<sz + 2;++i)
            di[i] = dc[i] = 0;
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y)
    {
        G_TOPOLOGICAL_SORT_CHECK_CREATED(false);
        if (x > n || y > n) return false;
        g[x].pb(y);
        ++di[y];
        return true;
    }
    uint topologicalSort(std::vector<uint> &top)
    {
        G_TOPOLOGICAL_SORT_CHECK_CREATED(G_TOPOLOGICAL_SORT_ERROR);
        top.clear();
        std::queue<uint>q;
        for (uint i=1;i<=n;++i)
        {
            dc[i] = di[i];
            if (!dc[i])
                q.push(i);
        }
        uint nodes = 0, act;
        while (!q.empty())
        {
            act = q.front();
            ++nodes;
            top.pb(act);
            q.pop();
            for (uint i=0;i<g[act].size();++i)
            {
                --dc[g[act][i]];
                if (!dc[g[act][i]])
                    q.push(g[act][i]);
            }
        }
        if (nodes < n) return G_TOPOLOGICAL_SORT_CIRCUIT;
        return G_TOPOLOGICAL_SORT_OK;
    }
};

#endif

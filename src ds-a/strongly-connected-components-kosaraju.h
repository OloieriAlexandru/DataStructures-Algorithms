#ifndef STRONGLY_CONNECTED_COMPONENTS_KOSARAJU_H
#define STRONGLY_CONNECTED_COMPONENTS_KOSARAJU_H
#include <vector>

// https://infoarena.ro/job_detail/2444517?action=view-source

class sccKosarajuSharir
{
private:
#define SCC_KOSARAJU_CHECK_CREATED(ret) if (!created) return ret
#define uint unsigned int
#define pb push_back
    std::vector<uint> *graph, *transposedGraph;
    uint *postOrd, n, act;
    bool *nodeUsed;
    bool created;
    void firstDfs(uint x)
    {
        nodeUsed[x] = true;
        for (uint i=0; i<graph[x].size(); ++i)
        {
            if (nodeUsed[graph[x][i]]) continue;
            firstDfs(graph[x][i]);
        }
        postOrd[++act] = x;
    }
    void secondDfs(uint x, std::vector<uint> &cc)
    {
        cc.pb(x);
        nodeUsed[x] = false;
        for (uint i=0; i<transposedGraph[x].size(); ++i)
        {
            if (!nodeUsed[transposedGraph[x][i]]) continue;
            secondDfs(transposedGraph[x][i], cc);
        }
    }
public:
    sccKosarajuSharir():
        created(false), postOrd(nullptr), nodeUsed(nullptr), graph(nullptr), transposedGraph(nullptr) {}
    bool create(uint sz)
    {
        if (created) return false;
        graph = new std::vector<uint>[sz + 1];
        if (graph == nullptr) return false;
        transposedGraph = new std::vector<uint>[sz + 1];
        if (transposedGraph == nullptr)
        {
            delete[] graph;
            return false;
        }
        postOrd = new uint[sz + 1];
        if (postOrd == nullptr)
        {
            delete[] graph;
            delete[] transposedGraph;
            return false;
        }
        nodeUsed = new bool[sz + 1];
        if (nodeUsed == nullptr)
        {
            delete[] graph;
            delete[] transposedGraph;
            delete[] postOrd;
            return false;
        }
        n = sz + 1;
        for (uint i=0; i<n; ++i)
            nodeUsed[i] = 0;
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y)
    {
        SCC_KOSARAJU_CHECK_CREATED(false);
        if (x >= n || y >=n) return false;
        graph[x].pb(y);
        transposedGraph[y].pb(x);
        return true;
    }
    bool computeSCC(std::vector<std::vector<uint>> &ans)
    {
        SCC_KOSARAJU_CHECK_CREATED(false);
        act = 0;
        for (uint i=1; i<n; ++i)
            if (!nodeUsed[i])
                firstDfs(i);
        for (uint i=act; i>0; --i)
            if (nodeUsed[postOrd[i]])
            {
                std::vector<uint> currCc;
                secondDfs(postOrd[i], currCc);
                ans.pb(currCc);
            }
        return true;
    }
};

#endif

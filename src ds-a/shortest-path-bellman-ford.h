#ifndef SHORTEST_PATH_BELLMAN_FORD_H
#define SHORTEST_PATH_BELLMAN_FORD_h
#include <vector>
#include <queue>
#include <utility>

// https://infoarena.ro/job_detail/2445084?action=view-source

class shortestPathBellmanFord
{
private:
#define mkp std::make_pair
#define pb push_back
#define uint unsigned int
#define S_P_BELLMAN_FORD_CHECK_CREATED(ret) if (!created) return ret
#define S_P_BELLMAN_FORD_OK 1
#define S_P_BELLMAN_FORD_NEGATIV_CYCLE 2
#define S_P_BELLMAN_FORD_ERROR 4294967295
#define S_P_BELLMAN_FORD_MAX_VALUE 2147483647
#define pii std::pair<uint,int>
    std::vector<pii>*graph;
    bool created;
    uint n, *visited;
public:
    shortestPathBellmanFord(): graph(nullptr), created(false), visited(nullptr) {}
    bool create(uint sz)
    {
        if (created) return false;
        graph = new std::vector<pii>[sz + 2];
        if (graph == nullptr) return false;
        visited = new uint[sz + 2];
        if (visited == nullptr)
        {
            delete[] graph;
            return false;
        }
        n = sz + 1;
        created = true;
        return true;
    }
    bool addDirectedEdge(uint x, uint y, int c)
    {
        S_P_BELLMAN_FORD_CHECK_CREATED(false);
        if (x >= n || y >= n) return false;
        graph[x].pb(mkp(y,c));
        return true;
    }
    bool addUnidirectedEdge(uint x, uint y, int c)
    {
        S_P_BELLMAN_FORD_CHECK_CREATED(false);
        if (x >= n || y >= n) return false;
        graph[x].pb(mkp(y,c));
        graph[y].pb(mkp(x,c));
        return true;
    }
    uint computeShortestPaths(uint startNode, std::vector<int> &shortestPaths)
    {
        S_P_BELLMAN_FORD_CHECK_CREATED(S_P_BELLMAN_FORD_ERROR);
        if (startNode >= n) return S_P_BELLMAN_FORD_ERROR;
        shortestPaths.resize(n+1, S_P_BELLMAN_FORD_MAX_VALUE);
        shortestPaths[startNode] = 0;
        for (uint i=0;i<n;++i)
            visited[i] = 0;
        std::queue<uint>q;
        q.push(startNode);
        uint act;
        while (!q.empty())
        {
            act = q.front();
            q.pop();
            for (uint i=0;i<graph[act].size();++i)
            {
                if (shortestPaths[act] + graph[act][i].second < shortestPaths[graph[act][i].first])
                {
                    ++visited[graph[act][i].first];
                    if (visited[graph[act][i].first] == n-1) return S_P_BELLMAN_FORD_NEGATIV_CYCLE;
                    shortestPaths[graph[act][i].first] = shortestPaths[act] + graph[act][i].second;
                    q.push(graph[act][i].first);
                }
            }
        }
        return S_P_BELLMAN_FORD_OK;
    }
};

#endif

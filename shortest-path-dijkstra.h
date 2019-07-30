#ifndef SHORTEST_PATH_DIJKSTRA_H
#define SHORTEST_PATH_DIJKSTRA_H
#include <vector>
#include <queue>
#include <functional>

// https://infoarena.ro/job_detail/2444304?action=view-source

class shortestPathDijkstra
{
private:
#define mkp std::make_pair
#define pb push_back
#define uint unsigned int
#define pii std::pair<uint,int>
#define S_P_DIJKSTRA_CHECK_CREATED(ret) if (!created) return ret
#define S_P_DIJKSTRA_MAX_VALUE 2147483647
    std::vector<pii>*graph;
    bool created;
    uint n;
public:
    shortestPathDijkstra(): graph(nullptr), created(false) {}
    bool create(uint sz)
    {
        if (created) return false;
        graph = new std::vector<pii>[sz + 2];
        if (graph == nullptr) return false;
        n = sz + 2;
        created = true;
        return true;
    }
    bool addDirectedEdge(uint x, uint y, int c)
    {
        S_P_DIJKSTRA_CHECK_CREATED(false);
        if (x >= n || y >= n) return false;
        graph[x].pb(mkp(y,c));
        return true;
    }
    bool addUnidirectedEdge(uint x, uint y, int c)
    {
        S_P_DIJKSTRA_CHECK_CREATED(false);
        if (x >= n || y >= n) return false;
        graph[x].pb(mkp(y,c));
        graph[y].pb(mkp(x,c));
        return true;
    }
    bool computeShortestPaths(uint startNode, std::vector<int> &shortestPaths)
    {
        S_P_DIJKSTRA_CHECK_CREATED(false);
        if (startNode >= n) return false;
        shortestPaths.resize(n+1,S_P_DIJKSTRA_MAX_VALUE);
        shortestPaths[startNode] = 0;
        std::priority_queue<std::pair<int, uint>, std::vector<std::pair<int, uint>>, std::greater<std::pair<int,uint>> >pq;
        pq.push(mkp(0,startNode));
        uint chosen = 0;
        std::pair<int,uint> act;
        pii x;
        while (!pq.empty() && chosen < n)
        {
            act = pq.top();
            pq.pop();
            if (act.first > shortestPaths[act.second]) continue;
            ++chosen;
            for (uint i=0; i<graph[act.second].size(); ++i)
            {
                x = graph[act.second][i];
                if (shortestPaths[x.first] > shortestPaths[act.second] + x.second)
                {
                    shortestPaths[x.first] = shortestPaths[act.second] + x.second;
                    pq.push(mkp(shortestPaths[x.first], x.first));
                }
            }
        }
        return true;
    }
};

#endif

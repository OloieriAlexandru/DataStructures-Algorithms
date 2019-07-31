#ifndef MINIMUM_SPANNING_TREE_KRUSKAL
#define MINIMUM_SPANNING_TREE_KRUSKAL
#include <utility>
#include <queue>
#include <vector>

// https://infoarena.ro/job_detail/2444487?action=view-source

class minimumSpanningTreeKruskal
{
private:
#define uint unsigned int
#define edge std::pair<int,std::pair<uint,uint>>
#define mkp std::make_pair
#define MST_KRUSKAL_CHECK_CREATED(ret) if (!created) return ret
#define MST_KRUSKAL_ERROR 2147483647
    std::priority_queue<edge, std::vector<edge>, std::greater<edge> >graph;
    bool created;
    uint *father, *height;
    uint n;
    void prepareUnionFind()
    {
        for (uint i=0;i<n;++i)
            father[i] = height[i] = 0;
    }
    void unionn(uint x, uint y)
    {
        if (height[x] > height[y]) father[y] = x;
        else if (height[x] < height[y]) father[x] = y;
        else father[y] = x, ++height[x];
    }
    uint findd(uint x)
    {
        uint cx = x, up;
        while (father[x]) x = father[x];
        if (x != cx)
            while (father[cx]) up = father[cx], father[cx] = x, cx = up;
        return x;
    }
public:
    minimumSpanningTreeKruskal(): created(false), father(nullptr), height(nullptr) {}
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
        created = true;
        return true;
    }
    bool addEdge(uint x, uint y, int c)
    {
        MST_KRUSKAL_CHECK_CREATED(false);
        if (x >= n || y >= n) return false;
        graph.push(mkp(c,mkp(x,y)));
        return true;
    }
    int computeMinimumSpanningTree(std::vector<std::pair<uint,uint>> &ans)
    {
        int mst = 0;
        uint chosen = 0, c1, c2;
        ans.clear();
        std::priority_queue<edge, std::vector<edge>, std::greater<edge> >graphCopy = graph;
        edge act;
        prepareUnionFind();
        while (!graphCopy.empty() && chosen < n-1)
        {
            act = graphCopy.top();
            graphCopy.pop();
            c1 = findd(act.second.first);
            c2 = findd(act.second.second);
            if (c1 == c2) continue;
            ans.push_back(act.second);
            ++chosen;
            mst += act.first;
            unionn(c1,c2);
        }
        return mst;
    }
};

#endif

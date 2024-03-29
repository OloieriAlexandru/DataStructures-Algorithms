#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include <ostream>
#include <vector>
namespace combinatorics
{
    #define uint unsigned int

    // https://infoarena.ro/job_detail/2479595
    void permutationsGenerator(uint k, uint n, std::vector<int>&perm, std::vector<bool>&used, std::ostream& out)
    {
        if (k == n)
        {
            for (auto x:perm) out<<x<<' ';
            out<<'\n';
            return;
        }
        for (int i=1;i<=n;++i)
        {
            if (used[i]) continue;
            used[i] = true;
            perm[k] = i;
            permutationsGenerator(k+1, n, perm, used, out);
            used[i] = false;
        }
    }
    bool permutations(uint n, std::ostream& out)
    {
        if (!n) return false;
        std::vector<int>perm;
        std::vector<bool>used;
        perm.resize(n);
        used.resize(n);
        permutationsGenerator(0, n, perm, used, out);
        return true;
    }

    void arrangementsGenerator(uint k, uint n, uint m, std::vector<int>&arr, std::vector<bool>&used,std::ostream& out)
    {
        if (k == m)
        {
            for (auto x:arr) out<<x<<' ';
            out<<'\n';
            return;
        }
        for (int i=1;i<=n;++i)
        {
            if (used[i]) continue;
            used[i] = true;
            arr[k] = i;
            arrangementsGenerator(k+1,n,m,arr,used,out);
            used[i] = false;
        }
    }
    bool arrangements(uint n, uint m, std::ostream& out)
    {
        if (!n) return false;
        std::vector<int>arr;
        std::vector<bool>used;
        arr.resize(m);
        used.resize(n);
        arrangementsGenerator(0, n, m, arr, used, out);
        return true;
    }

    // https://infoarena.ro/job_detail/2479598
    void combinationsGenerator(uint k, uint n, uint m, std::vector<int>&comb, std::vector<bool>&used, std::ostream& out)
    {
        if (k == m)
        {
            for (auto x:comb) out<<x<<' ';
            out<<'\n';
            return;
        }
        int i = (k == 0 ? 1 : comb[k-1]+1);
        for (;i<=n-m+k;++i)
        {
            comb[k] = i;
            combinationsGenerator(k+1,n,m,comb,used,out);
        }
    }
    bool combinations(uint n, uint m, std::ostream& out)
    {
        if (!n) return false;
        std::vector<int>comb;
        std::vector<bool>used;
        comb.resize(m);
        used.resize(n);
        combinationsGenerator(0, n, m, comb, used, out);
        return true;
    }

    void cartesianProductGenerator(uint k, uint n, uint m, std::vector<int>&cProd, std::ostream& out)
    {
        if (k == m)
        {
            for (auto x:cProd) out<<x<<' ';
            out<<'\n';
            return;
        }
        for (int i=1;i<=n;++i)
        {
            cProd[k] = i;
            cartesianProductGenerator(k+1,n,m,cProd,out);
        }
    }
    bool cartesianProduct(uint n, uint m, std::ostream& out)
    {
        if (!n) return false;
        std::vector<int>cProd;
        cProd.resize(m);
        cartesianProductGenerator(0,n,m,cProd,out);
        return true;
    }
    // function call example: combinatorics::cartesianProduct(5,5,cout);
}

#endif

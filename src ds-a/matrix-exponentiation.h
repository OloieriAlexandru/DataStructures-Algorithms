#ifndef MATRIX_EXPONENTIATION_H
#define MATRIX_EXPONENTIATION_H
#include <vector>

// https://infoarena.ro/job_detail/2450337?action=view-source

class matrixExponentiation
{
private:
#define uint unsigned int
#define ll long long
#define MATRIX_EXPONENTIATION_CHECK_CREATED(ret) if (!created) return ret
#define MATRIX_EXPONENTIATION_ERROR -1
    struct matrix
    {
        std::vector<std::vector<int>>m;
        matrix() {}
        void create(uint n)
        {
            m.resize(n);
            for (uint i=0; i<n; ++i)
                m[i].resize(n,0);
        }
    };
    matrix mul(matrix a, matrix b)
    {
        matrix ans;
        ans.create(n);
        for (uint k=0; k<n; ++k)
            for (uint i=0; i<n; ++i)
                for (uint j=0; j<n; ++j)
                    ans.m[i][j] = (ans.m[i][j] + 1LL*a.m[i][k]*b.m[k][j]) % modulo;
        return ans;
    }
    matrix logExponentiation(matrix m, ll n)
    {
        if (!n) return iN;
        if (n&1)
            return mul(m,logExponentiation(mul(m,m),n>>1));
        return logExponentiation(mul(m,m), n>>1);
    }
    ll modulo;
    uint n;
    bool created;
    matrix reccurence, iN, base;
public:
    matrixExponentiation(): created(false) {}
    bool create(uint n, ll modulo)
    {
        if (created) return false;
        this->n = n;
        this->modulo = modulo;
        created = true;
        reccurence.create(n);
        iN.create(n);
        base.create(n);
        for (uint i=1; i<n; ++i)
            reccurence.m[i][i-1] = 1;
        for (uint i=0; i<n; ++i)
            iN.m[i][i] = 1;
        return true;
    }
    bool setReccurenceTerm(uint poz, int val)
    {
        MATRIX_EXPONENTIATION_CHECK_CREATED(MATRIX_EXPONENTIATION_ERROR);
        base.m[0][poz] = val;
        return true;
    }
    bool setBaseTerm(uint poz, int val)
    {
        MATRIX_EXPONENTIATION_CHECK_CREATED(MATRIX_EXPONENTIATION_ERROR);
        reccurence.m[0][poz] = val;
        return true;
    }
    ll calculateReccurence(ll nterm)
    {
        MATRIX_EXPONENTIATION_CHECK_CREATED(MATRIX_EXPONENTIATION_ERROR);
        matrix exp = logExponentiation(reccurence, nterm);
        matrix ans = mul(exp, base);
        return ans.m[0][0];
    }
};

#endif

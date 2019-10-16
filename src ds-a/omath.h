#ifndef OMATH_H
#define OMATH_H

namespace oMath
{
#define lld long long
    lld logExp(lld x, lld n, lld mod)
    {
        if (!n) return 1LL;
        if (n & 1) return (x*logExp((x*x)%mod, n>>1,mod))%mod;
        return logExp((x*x)%mod,n>>1,mod);
    }

    lld extendedGcd(lld &x, lld &y, lld a, lld b)
    {
        if (!b)
            x = 1, y = 0;
        else
        {
            extendedGcd(x, y, b, a%b);
            lld aux = x;
            x = y;
            y = aux - y*(a/b);
        }
    }

    lld modularInverse(lld a, lld n)
    {
        lld x, y;
        extendedGcd(x, y, a, n);
        if (x < 0) x = n + x;
        return x;
    }
}

#endif

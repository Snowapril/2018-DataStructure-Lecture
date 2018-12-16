#include <bits/stdc++.h>
using namespace std;
using I=int;
I n,i,m;
struct s {
    vector<I> c;
    I z;
    I x;
    bool operator<(s const& o)const{
        return z > o.z ? true : z == o.z ? c > o.c : false;
        if (z > o.z)
            return true;
        if (z == o.z)
            for (i=0;i<z&&c[i]>=o.c[i];++i)
                if (c[i]>o.c[i])
                    return true;
        return false;
    }
};
main () {
    freopen("rank.inp", "r", stdin);
    freopen("rank.out", "w", stdout);
    scanf("%d", &n);
    m=n;
    vector <s> d;
    vector <I> v;
    for (;n&&scanf("%d",&i);)
        if (i == -1) {
            sort(v.begin(), v.end());
            d.push_back( { v, v.size(), m-n--+1 });
            v.clear();
        }
        else
            v.push_back(i);
    stable_sort(d.begin(), d.end());
    for (i=0;i<m-1;++i)
        printf("%d\n", d[i].x);
    printf("%d",d[m-1].x);
    fclose(stdin);
    fclose(stdout);
}

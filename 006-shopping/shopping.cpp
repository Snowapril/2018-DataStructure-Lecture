#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

using paii = pair<int, int>;

int main(void) {
    freopen("shopping.inp", "r", stdin);
    freopen("shopping.out", "w", stdout);

    int N, K;
    scanf("%d %d", &N, &K);
    vector<queue<paii>> shop_mall(K, queue<paii>());
    vector<int> total_time(K, 0);

    for (int i = 0; i < N; ++i) {
        int id, num;
        scanf("%d %d", &id, &num);
        auto min_iter = min_element(total_time.begin(), total_time.end());
        auto idx = min_iter - total_time.begin();
        shop_mall[idx].push(make_pair(id, *min_iter + num));
        total_time[idx] += num;
    }

    vector<int> candidate;
    candidate.reserve(K);

    while (true) {
        for (auto rp = shop_mall.rbegin(); rp < shop_mall.rend(); ++rp)
            if (rp->empty())
                candidate.push_back(INT_MAX);
            else
                candidate.push_back(rp->front().second);

        auto min_iter = min_element(candidate.begin(), candidate.end());

        if (*min_iter == INT_MAX)
            break;
        else {
            auto idx = min_iter - candidate.begin();
            idx = K - idx - 1;
            printf("%d\n", shop_mall[idx].front().first);
            shop_mall[idx].pop();
            candidate.clear();
        }
    }

    fclose(stdout);
    fclose(stdin);
    return 0;
}
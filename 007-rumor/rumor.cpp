#include <bits/stdc++.h>

using namespace std;

int main(void) {
    freopen("rumor.inp", "r", stdin);
    freopen("rumor.out", "w", stdout);

    int N, x, d;
    scanf("%d %d %d", &N, &x, &d);

    vector<set<int>> network(N + 1);

    for (int idx = 0; idx < N; ++idx) {
        set<int> relation;

        int myself, neighbour;
        scanf("%d", &myself);

        while (scanf("%d", &neighbour) == 1 && neighbour)
            relation.insert(neighbour);

        network[myself] = move(relation);
    }

    bitset<51> visitFlag;
    queue<int> todayQueue;
    queue<int> tomorrowQueue;

    todayQueue.push(x);
    printf("%d\n", x);
    visitFlag.set(x);

    for (int i = 0; i < d; ++i) {

        while (!todayQueue.empty()) {
            int number = todayQueue.front();

            for (int neighbour : network[number])
                if (!visitFlag.test(neighbour)) {
                    printf("%d\n", neighbour);
                    tomorrowQueue.push(neighbour);
                    visitFlag.set(neighbour);
                }

            todayQueue.pop();
        }

        tomorrowQueue.swap(todayQueue);
    }

    fclose(stdout);
    fclose(stdin);
    return (EXIT_SUCCESS);
}

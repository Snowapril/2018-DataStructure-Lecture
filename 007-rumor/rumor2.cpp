#include <bits/stdc++.h>
using namespace std;

int main(void) {

    fstream input("rumor.inp"), output("rumor.out", ios::out);
    int N, x, d;
    input >> N >> x >> d;

    vector<set<int>> network(N + 1);

    for (int i = 0; i < N; ++i) {
        int number;
        input >> number;

        auto& relation = network[number];

        int neighbour;
        while (input >> neighbour && neighbour != 0)
            relation.insert(neighbour);
    }

    vector<vector<int>> partitions;
    vector<int> currentGraph;

    vector<bool> visitFlag(N + 1, false);

    queue<int> todayQueue;
    queue<int> nextQueue;

    todayQueue.push(x);
    currentGraph.push_back(x);
    visitFlag[x] = true;

    while (true) {

        while(!todayQueue.empty()) {
            int number = todayQueue.front();

            for (int neighbour : network[number]) {
                if (!visitFlag[neighbour]) {
                    visitFlag[neighbour] = true;
                    nextQueue.push(neighbour);
                    currentGraph.push_back(neighbour);
                }
            }

            todayQueue.pop();
        }

        if (nextQueue.empty()) {
            partitions.push_back(currentGraph);
            currentGraph.clear();

            auto iter = find(visitFlag.begin() + 1, visitFlag.end(), false);

            if (iter == visitFlag.end())
                break;

            auto distance = iter - visitFlag.begin();

            todayQueue = queue<int>();
            todayQueue.push(distance);

        } else {
            nextQueue.swap(todayQueue);
        }
    }

    for (int i = 0; i < partitions.size(); ++i) {
        output << i + 1 << "th partition with size : " << partitions[i].size() << endl << '\t';

        for (int k : partitions[i])
            output << k << ' ';
        output << endl;
    }


    return 0;
}

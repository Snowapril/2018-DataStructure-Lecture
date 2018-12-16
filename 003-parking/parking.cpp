#include <stdio.h>
#include <list>
#include <queue>
#include <functional>
#include <ctime>
#include <algorithm>

int slotNum[65537];

bool comp(int i, int j) {
    return slotNum[i] < slotNum[j];
}

int main(void) {

	freopen("parking.inp", "r", stdin);
	freopen("parking.out", "w", stdout);

	int K, N;
	scanf("%d %d", &K, &N);


	std::list<int> parking;

	const int minCapacity = K;
	int curCapacity = K;
	int compactionCapacity = curCapacity / 3;
	int nextSlot = 1;
	std::priority_queue<int, std::vector<int>, std::greater<int>> slotQueue;

	while (N--) {
		int carNumber;
		scanf("%d", &carNumber);

		if (carNumber > 0) {
			parking.push_back(carNumber);

			if (slotQueue.empty())
				slotNum[carNumber] = nextSlot++;
			else {
				slotNum[carNumber] = slotQueue.top();
				slotQueue.pop();
			}

			if (nextSlot - 1 == curCapacity) {
				curCapacity <<= 1;
				compactionCapacity = curCapacity / 3;
			}
		}
		else {
			carNumber = -carNumber;

			auto iter = parking.begin();
			auto endIter = parking.end();

			while (iter != endIter)
				if (*iter == carNumber)
					break;
				else
					++iter;

			parking.erase(iter);
			slotQueue.push(slotNum[carNumber]);

			if (compactionCapacity == nextSlot - 1 - slotQueue.size()) {

                parking.sort(comp);

				int startIdx = 1;

				for (const auto& number : parking)
					slotNum[number] = startIdx++;

				nextSlot = startIdx;
				slotQueue = std::priority_queue<int, std::vector<int>, std::greater<int>>();

				int newCapacity = curCapacity >> 1;
				curCapacity = newCapacity > minCapacity ? newCapacity : minCapacity;
				compactionCapacity = curCapacity / 3;
			}
		}
	}

	fclose(stdin);

	parking.sort(comp);

	auto iter = parking.begin();
	auto endIter = parking.end();
    int listSize = parking.size();
    int index = 0;

	while (index != listSize - 1) {
        printf("%d %d\n", slotNum[*iter], *iter);
        ++iter;
        ++index;
	}

	printf("%d %d", slotNum[*iter], *iter);

	fclose(stdout);

	return 0;
}

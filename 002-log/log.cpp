#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct Node {
    int day;
    int time;
    int count;
    int dummyVariable;
};

int main(void) {
    freopen("log.inp", "r", stdin);
    freopen("log.out", "w", stdout);

    int numPairs;
    scanf("%d", &numPairs);

    Node startDates[1000];
    Node endDates[1000];

    for (int i = 0; i < numPairs; ++i) {
        scanf("%d %d %d %d", &startDates[i].day, &startDates[i].time, &endDates[i].day, &endDates[i].time);

        startDates[i].count = 0;
        endDates[i].count = 0;
    }

    fclose(stdin);

    std::ifstream systemLog("syslog.txt");
    systemLog.tie(nullptr);

    std::string line;
    std::getline(systemLog, line);

    int totalCount = 0;
    while(systemLog.good()) {
        std::getline(systemLog, line);

        auto dayIdx = line.find_first_of(' ');
        int day = stoi(line.substr(0, dayIdx));

        totalCount += std::count(line.begin(), line.end(), ' ') - 1;

        for (int j = 0; j < numPairs; ++j) {
            if (startDates[j].day > day)
                startDates[j].count = totalCount;
            else if (startDates[j].day == day) {
                std::istringstream isstr(line);
                int time;
                isstr >> time;

                while (true) {
                    isstr >> time;

                    if (time == 0)
                        break;

                    if (startDates[j].time > time)
                        ++ startDates[j].count;
                    else
                        break;
                }
            }

            if (endDates[j].day > day)
                endDates[j].count = totalCount;
            else if (endDates[j].day == day) {
                std::istringstream isstr(line);
                int time;
                isstr >> time;

                while (true) {
                    isstr >> time;

                    if (time == 0)
                        break;

                    if (endDates[j].time >= time)
                        ++ endDates[j].count;
                    else
                        break;
                }
            }
        }
    }


    systemLog.close();

    for (int i = 0; i < numPairs - 1; ++i)
        printf("%d\n", endDates[i].count - startDates[i].count);

    printf("%d", endDates[numPairs - 1].count - startDates[numPairs - 1].count);

    fclose(stdout);
    fclose(stdin);

    return 0;
}

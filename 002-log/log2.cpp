#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;

int main(void) {

    freopen("log.inp", "r", stdin);
    freopen("log.out", "w", stdout);

    fstream syslog("syslog.txt");

    int numday;
    syslog >> numday;

    vector<uint> timetable;
    timetable.reserve(numday * 10000);

    uint day;
    while (syslog >> day) {
        day <<= 14;

        uint time;
        while (syslog >> time && time != 0)
            timetable.push_back(day + time);
    }

    int numcase;
    scanf("%d", &numcase);

    for (int i = 0; i < numcase; ++i) {
        uint d, t;
        scanf("%d %d", &d, &t);

        auto lower = lower_bound(timetable.begin(), timetable.end(), (d << 14) + t);

        scanf("%d %d", &d, &t);
        auto upper = upper_bound(timetable.begin(), timetable.end(), (d << 14) + t);

        auto dist = distance(lower, upper);

        printf("%d\n", dist);
    }

    return 0;
}

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int width, height;
    cin >> width >> height;

    int targetX, targetY, targetIndex;
    cin >> targetX >> targetY >> targetIndex;

    int x = 1, y = 0;
    int dx = 0, dy = 1;
    int degreeX = width - 1, degreeY = height;

    int answerX = - 1, answerY = -1, answerIndex = -1;
    int numPoints = width * height;
    int previ = -1;

    for (int i = 0; i < numPoints; ) {


        if (((x - 1) == y && dx == -1 ) || ((y == height - x + 1) && dy == 1) ||
             ((x == width - y + 1) && dy == -1) || ((width - x == height - y) && dx == 1)) {
            int temp = dx;
            dx = dy;
            dy = -temp;
        }

        cout << "(" << x << ", " << y << ")" << endl;

        x += dx * (degreeX);
        y += dy * (degreeY);

        previ = i;
        i += abs(dx) * degreeX + abs(dy) * degreeY;
        cout << i <<endl;

        if (previ < targetIndex && targetIndex <= i) {
            int diff = i - targetIndex;

            answerX = x - dx * diff;
            answerY = y - dy * diff;
        }

        if ((dx == 0) && (y == targetY)) {
            if ((dy == -1) && (y - dy * degreeY > targetY) || (dy == 1 && (y - dy * degreeY < targetY))) {
                answerIndex = i + dy * (targetY - y);
            }
        }
        else if ((dy == 0) && (x == targetX)) {
            if ((dx == -1) && (x - dx * degreeX > targetX) || (dx == 1 && (x - dx * degreeX < targetX))) {
                answerIndex = i + dx * (targetX - x);
            }
        }

        if (dy != 0)
            --degreeY;

        if (dx != 0)
            --degreeX;
    }

    cout << answerIndex << endl;
    cout << answerX << ' ' << answerY << endl;

    return 0;
}

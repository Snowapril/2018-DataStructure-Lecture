#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream inputFile("nanobot.inp");
    ofstream outputFile("nanobot.out");

    int width, height;
    inputFile >> width >> height;

    int targetX, targetY, targetIndex;
    inputFile >> targetX >> targetY >> targetIndex;

    int x = 1, y = 1;
    int dx = 0, dy = 1;

    int answerX, answerY, answerIndex;

    //O(NM) algorithm ,, any better else hmm
    for (int i = 0; i < width * height; ++i)
    {
        if (x == targetX && y == targetY)
            answerIndex = i + 1;
        if (i + 1 == targetIndex) {
            answerX = x;
            answerY = y;
        }

        if (((x - 1) == y && dx == -1 ) || ((y == height - x + 1) && dy == 1) ||
             ((x == width - y + 1) && dy == -1) || ((width - x == height - y) && dx == 1)) {
            int temp = dx;
            dx = dy;
            dy = -temp;
        }

        x += dx;
        y += dy;
    }

    outputFile << answerIndex << endl;
    outputFile << answerX << ' ' << answerY << endl;

    outputFile.close();
    inputFile.close();

    return 0;
}

#include <fstream>
#include <iostream>

using namespace std;

int main(void) {
    ifstream my("./log.out");
    ifstream answer("./sp3.out");

    int myNum, answerNum;

    while (my >> myNum && answer >> answerNum)

            cout << myNum << ' ' << answerNum;

    return 0;
}

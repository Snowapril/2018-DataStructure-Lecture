#include <vector>
#include <stack>
#include <bitset>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

using call = pair<int, char>;

int main(void) {
    fstream input("function.inp"), output("function.out", ios::out);

    int N, k1, k2;
    input >> N >> k1 >> k2;

    vector<vector<string>> program(N);
    vector<vector<call>> graph(N);
    unordered_map<char, int> callKey;

    for (int i = 0; i < N; ++i) {
        char name;
        input >> name;

        callKey[name] = i;

        string command;
        int commandCount = 0;
        do {
            input >> command;

            if (isupper(command.back())) {
                graph[i].push_back({commandCount, command.back()});
                commandCount = 0;
            }
            else {
                ++ commandCount;
                program[i].push_back(command);
            }

        } while (command.back() != '$');
        graph[i].push_back({commandCount - 1, '$'});
    }

    string str1, str2;

    bitset<10> visitFlag;
    stack<vector<call>::const_iterator> funcStack;
    stack<char> nameStack;

    auto iter = graph[0].cbegin();
    int callCount = 0;

    nameStack.push('M');
    funcStack.push(graph[0].cbegin());
    visitFlag.set(callKey['M']);

    while (!funcStack.empty()) {
        callCount += iter->first;

        if (str1.empty() && k1 <= callCount) {
            str1 = string({nameStack.top(), '-'}) + *(program[callKey[nameStack.top()]].rbegin() + (callCount - k1 + 1));
        }

        if (str2.empty() && k2 <= callCount) {
            str2 = string({nameStack.top(), '-'}) + *(program[callKey[nameStack.top()]].rbegin() + (callCount - k2 + 1));
        }

        if (iter->second == '$'){
            iter = funcStack.top() + 1;
            visitFlag.reset(callKey[nameStack.top()]);

            funcStack.pop();
            nameStack.pop();
        }
        else {
            funcStack.push(iter);
            nameStack.push(iter->second);

            if (visitFlag.test(callKey[iter->second])) {
                output << "DEADLOCK";
                return 0;
            }

            visitFlag.set(callKey[iter->second]);

            iter = graph[callKey[iter->second]].cbegin();
        }
    }

    output << (str1.empty() ? "NONE" : str1) << endl;
    output << (str2.empty() ? "NONE" : str2);

    output.close();
    input.close();

    return 0;
}

#include <bits/stdc++.h>

using namespace std;

class DijkstraGraph {
public:
    DijkstraGraph(size_t _num_vertices, vector<char>&& sequence);
public:
    void traverse_graph(initializer_list<char>&& start_vertices);
    pair<char, int> get_optimum_way(void) const;
private:
    int get_maximum(size_t index) const;
private:
    unordered_map<char, int> v_table;
    vector<vector<char>> graph;
    vector<vector<int>> distance;
    size_t num_vertices;
};

int main(void) {
    vector<char> input_sequence;
    size_t num_vertices;
    char a_loc, b_loc, c_loc;

    ios_base::sync_with_stdio(false);
    fstream input("./meeting.inp"), output("./meeting.out", ios_base::out);
    input.tie(nullptr); output.tie(nullptr);

    input >> num_vertices >> a_loc >> b_loc >> c_loc;
    copy(istream_iterator<char>(input), istream_iterator<char>(), back_inserter(input_sequence));

    DijkstraGraph graph(num_vertices, move(input_sequence));
    graph.traverse_graph({a_loc, b_loc, c_loc});

    const auto& answer = graph.get_optimum_way();
    output << answer.first << '\n' << answer.second;
    
    input.close();
    output.close();
    return 0;
}

DijkstraGraph::DijkstraGraph(size_t _num_vertices, vector<char>&& sequence) 
    : num_vertices(_num_vertices) {
    graph.resize(num_vertices, vector<char>());
    char node;
    bool is_first_node = true;
    int index = 0;

    for (char c : move(sequence)) {
        if (c == '$') 
            is_first_node = true;
        else {
            if (v_table.find(c) == end(v_table)) 
                v_table[c] = index++;
            if (is_first_node) {
                node = c;
                is_first_node = false;
            }
            else
                graph[v_table[node]].push_back(c);
        }
    }   
}

void DijkstraGraph::traverse_graph(initializer_list<char>&& start_vertices) {
    for (char v_start : move(start_vertices)) {
        vector<int>     local_distance  (num_vertices, numeric_limits<int>::max() >> 2);
        vector<bool>    visit_node      (num_vertices, false);
        local_distance[v_table[v_start]] = -2;
        
        queue<int> bfs_queue ( deque<int>{v_table[v_start]} );
        while (!bfs_queue.empty()) {
            int current_index = bfs_queue.front();
            visit_node[current_index] = true;
            bfs_queue.pop();
            
            for (char neighbour : graph[current_index]) {
                local_distance[v_table[neighbour]] = min(local_distance[v_table[neighbour]], 
                                                         local_distance[current_index] + 3);
                if (!visit_node[v_table[neighbour]]) {
                    visit_node[v_table[neighbour]] = true;
                    bfs_queue.push(v_table[neighbour]);
                }
            }
        }
        local_distance[v_table[v_start]] = 0;
        
        distance.emplace_back(move(local_distance));
    }
}

pair<char, int> DijkstraGraph::get_optimum_way(void) const {
    vector<int> shared_distance(num_vertices, numeric_limits<int>::max());
    for (size_t i = 0; i < num_vertices; ++i) 
        shared_distance[i] = get_maximum(i);
    
    unordered_map<int, char> flipped_table;
    for (const auto& pair : v_table)
        flipped_table[pair.second] = pair.first;

    int min_index = 0;
    for (int i = 1; i < num_vertices; ++i) {
        if (shared_distance[i] < shared_distance[min_index] ||
            (shared_distance[i] == shared_distance[min_index] && flipped_table[i] < flipped_table[min_index]))
            min_index = i;
    }

    return make_pair(flipped_table[min_index], shared_distance[min_index]);
}

int DijkstraGraph::get_maximum(size_t index) const {
    int max_distance = 0;
    for (const auto& dist : distance)
        max_distance = max(max_distance, dist[index]);
    return max_distance;
}
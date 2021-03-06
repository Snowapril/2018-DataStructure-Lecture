#include <bits/stdc++.h>

using namespace std;

class MicroAnalyzer {
public:
    MicroAnalyzer(int N, int M, vector<char>&& sequence);
public:
    void analyze            (int min_size);
    void dump_segments_info (const string& path) const;
private:
    bool is_in_bound        (int x, int y) const;
    bool is_virus           (int x, int y) const;
    int  dfs_pop_segments   (int start_x, int start_y);
private:
    vector<vector<char>> image;
    vector<int> segments;
    int width;
    int height;
};

int main(void) {
    ifstream input("micro.inp");
    vector<char> pixel_sequence;
    int N, M, k;

    input >> N >> M >> k;
    copy(istream_iterator<char>(input), istream_iterator<char>(), back_inserter(pixel_sequence));

    MicroAnalyzer analyzer(N, M, move(pixel_sequence));
    analyzer.analyze(k);

    analyzer.dump_segments_info("./micro.out");

    input.close();
    return 0;
}

MicroAnalyzer::MicroAnalyzer(int N, int M, vector<char>&& sequence)
    : width(M), height(N) {
    // 1-dimension sequence to 2-dimension array.
    vector<char> temp_sequence = move(sequence);
    auto sequence_iter = temp_sequence.begin();
    for (int i = 0; i < width; ++i) {
        image.push_back(vector<char>(sequence_iter, sequence_iter + height));
        sequence_iter = sequence_iter + height;
    }
}
void MicroAnalyzer::analyze(int min_size) {
    while (true) {
        int x, y, segment_size;

        for (x = 0; x < width; ++x)
            for (y = 0; y < height; ++y)
                if (image[x][y] == '#') goto FOUND; // break nested for loops

        FOUND: // goto is allowed in this specific situation. (in my opinion)
        if (x == width && y == height) break;

        segment_size = dfs_pop_segments(x, y);
        if (segment_size >= min_size) segments.push_back(segment_size);
    }
}

int  MicroAnalyzer::dfs_pop_segments(int start_x, int start_y) {
    stack<tuple<int, int>> pos_stack;
    int segment_size = 0, x, y;
    // push x, y to stack and remove virus simultaneously
    auto push_stack = [this, &pos_stack](int x, int y) {
        image[x][y] = '_';
        pos_stack.push(make_tuple(x, y));
    };

    push_stack(start_x, start_y);
    while (!pos_stack.empty()) {
        tie(x, y) = pos_stack.top();
        pos_stack.pop();
        ++segment_size;

        if (is_virus(x - 1, y    )) push_stack(x - 1, y    );
        if (is_virus(x + 1, y    )) push_stack(x + 1, y    );
        if (is_virus(x,     y - 1)) push_stack(x    , y - 1);
        if (is_virus(x,     y + 1)) push_stack(x    , y + 1);
    }
    return segment_size;
}

bool MicroAnalyzer::is_in_bound(int x, int y) const {
    return x >= 0 && x < width &&
           y >= 0 && y < height;
}

bool MicroAnalyzer::is_virus(int x, int y) const {
    return is_in_bound(x, y) && image[x][y] == '#'; // for preventing out of range error
}

void MicroAnalyzer::dump_segments_info(const string& path) const {
    ofstream output(path);

    int num_segments = segments.size();
    int max_segments = segments.empty() ? 0 : *max_element(begin(segments), end(segments));

    output << num_segments << ' ' << max_segments;

    output.close();
}

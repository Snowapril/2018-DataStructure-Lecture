#include <bits/stdc++.h>

using namespace std;

class Log {
	friend class GameLogger;
private:
	int64_t	id;
	int64_t base;
	bool 	is_open;
public:
	Log(int64_t _id, int64_t _base, int64_t _is_open);
	bool operator<(int64_t right) noexcept;
};

class Input {
	friend class GameLogger;
private:
	int64_t id;
	int64_t start;
	int64_t last;
public:
	Input(int64_t _id, int64_t _start, int64_t _end) ;
	bool operator<(const Input& other);
};

class GameLogger {
private:
	list<Log> log_list;
public:
	inline void addLogs(vector<Input>&& inputs);
	inline void dump_points(const char* path, vector<int64_t>&& times);
};

int main(void) {
	ifstream 		input("log.inp");
	int 			numLog, numCase;
	int64_t 		user_id, s, e;
	vector<Input>   input_list;
	vector<int64_t> dump_list;
	GameLogger 		logger;

	input >> numLog >> numCase;
	input_list.reserve(numLog);
	dump_list.reserve(numCase);

	for (int i = 0; i < numLog; ++i) {
		input >> user_id >> s >> e;
		input_list.emplace_back(user_id, s, e);
	}

	sort(begin(input_list), end(input_list));
	logger.addLogs(move(input_list));

	copy(istream_iterator<int64_t>(input), istream_iterator<int64_t>(), back_inserter(dump_list));
	logger.dump_points("log.out", move(dump_list));

	input.close();
	return 0;
}

inline void GameLogger::addLogs(vector<Input>&& inputs) {
	vector<Input>&& log_inputs = move(inputs);

	for_each(begin(log_inputs), end(log_inputs), [this](const Input& input) {
		auto start_iter = lower_bound(log_list.begin(), log_list.end(), input.start);
		log_list.insert(start_iter, { input.id, input.start, true});
		auto end_iter 	= lower_bound(start_iter, log_list.end(), input.last);
		log_list.insert(end_iter, { input.id, input.last, false});
	});
}

inline void GameLogger::dump_points(const char* path, vector<int64_t>&& times) {
	ofstream		output(path);
	vector<int64_t> dump_times = move(times);
	auto 			log_iter   = log_list.begin();

	for_each(dump_times.begin(), dump_times.end(), [&log_iter, this, &output](int64_t time) {
		set<int64_t> id_set;	

		log_iter = upper_bound(log_iter, log_list.end(), time, [](int64_t left, const Log& l) {
			return l.base > left;
		});
		for_each(log_list.begin(), log_iter, [&id_set, time](const Log& l) {
			if (l.is_open)
				id_set.insert(l.id);
			else if (l.base != time)
				id_set.erase(l.id);
		});
		
		if (id_set.empty())
			output << 0;
		else
			copy(id_set.begin(), id_set.end(), ostream_iterator<int64_t>(output, " "));
		output << endl;
	});

	output.close();
}

Log::Log(int64_t _id, int64_t _base, int64_t _is_open)
	: id(_id), base(_base), is_open(_is_open) {};

bool Log::operator<(int64_t right) noexcept {
	return base < right;
}

Input::Input(int64_t _id, int64_t _start, int64_t _end) 
	: id(_id), start(_start), last(_end) {};
	
bool Input::operator<(const Input& other) {
	return start < other.start;
}
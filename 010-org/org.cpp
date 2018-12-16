#include <bits/stdc++.h>

using namespace std;
using pb_table = unordered_map<string, string>;

class Node {
	friend class Organization;
public:
	Node(const string& _name, int _depth) noexcept;
private:
	list<Node*> childs;
	string name;
	int depth;
	int num_childs;
};

class Organization {
private:
	int calculate_num_childs(Node* node);
public:
    Organization(const string& root_name);
public:
	void organize_kary_tree(pb_table&& info_table);
	void dump_organization(const char* path) const;
private:
	vector<const Node*> registered_node;
	Node *root_node;
};

string retrieve_root(const pb_table& table);

int main(void) {
	pb_table table; //person boss table
	string   person, boss, root_name;
	int      num_node;

	ifstream input("org.inp");
	input >> num_node;

	for (int i = 0; i < num_node; ++i) {
		input >> person >> boss;
		table[person] = boss;
	}

	root_name = retrieve_root(table);

	Organization group(root_name);
	group.organize_kary_tree(move(table));
	group.dump_organization("org.out");

	input.close();
	return EXIT_SUCCESS;
}

string retrieve_root(const pb_table& table) {
	set <string>    people, bosses;
	vector<string>  outputs;

	for_each(pb_table.begin(), pb_table.end(), [&people, &bosses](const pair<string, string>& p) {
		people.insert(p.first);
		bosses.insert(p.second);
	});

	set_difference(begin(bosses), end(bosses), begin(people), end(people), back_inserter(outputs));
	return outputs.front();
}

Organization::Organization(const string& root_name)
	: root_node(new Node(root_name, 0)) {};

void Organization::organize_kary_tree(pb_table&& info_table) {
	pb_table table = move(info_table);
	queue<Node*>        q;
	int                 depth = 1;

	registered_node.reserve(table.size() + 1);
	registered_node.push_back(root_node);

	q.push(root_node);

	while (!table.empty()) {
		queue<Node*> next_queue;

		while (!q.empty()) {
			Node* temp = q.front();
			q.pop();

			for (auto iter = table.begin(); iter != table.end();) {
				if (iter->second == temp->name) {
					Node* new_child = new Node(iter->first, depth);
					temp->childs.push_back(new_child);
					registered_node.push_back(new_child);
					next_queue.push(new_child);
					iter = table.erase(iter);
				}
				else {
					++iter;
				}
			} // end of for
		} // end of while

		q.swap(next_queue);
		++depth;
	} // end of while

	calculate_num_childs(root_node);

	sort(registered_node.begin(), registered_node.end(), [](const Node* left, const Node* right) -> bool {
		return  (left->num_childs > right->num_childs)								    ||
                (left->num_childs == right->num_childs && left->depth < right->depth)	||
                (left->num_childs == right->num_childs && left->depth == right->depth && left->name < right->name);
	});
}

void Organization::dump_organization(const char* path) const {
	ofstream output(path);

	for (const auto* node : registered_node)
		output << node->name << ' ';

	output.close();
}

Node::Node(const string& _name, int _depth) noexcept
	: name(_name), depth(_depth), num_childs(0) {};

int Organization::calculate_num_childs(Node* node) {
	if (node->childs.empty()) {
		node->num_childs = 0;
		return 0;
	}

	int total_childs = accumulate(begin(node->childs), end(node->childs), 0, [this](int num, Node* temp) {
		return num + calculate_num_childs(temp);
	});

	return (node->num_childs = total_childs + node->childs.size());
}

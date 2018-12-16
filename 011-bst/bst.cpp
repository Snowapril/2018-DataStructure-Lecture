#include <bits/stdc++.h>

using namespace std;

class TreeNode {
	friend class BST;
public:
	TreeNode(const string& data);
	~TreeNode();
public:
	TreeNode* get_max_node(void);
private:
	string      value;
	TreeNode*   left;
	TreeNode*   right;
};

class BST {
public:
	BST(const string& path);
	~BST();
public:
	void insert_node(const string& data);
	void delete_node(const string& data);
	void dump_depth	(int depth) const;
	void dump_leaf	(void)      const;
private:
	mutable ofstream output_stream; // const keyword가 지정된 method에서 output_stream에 쓰는 것을 허용
	TreeNode*		 root_node;
};

int get_op_code(const string& op);

int main(void) {
	ifstream    input_stream("bst.inp");
	int         num_command, depth;
	string      command;
	BST         bst("bst.out");

	input_stream >> num_command;

	for (int i = 0; i < num_command; ++i) {
		input_stream >> command;
		int op_code = get_op_code(command);

		switch (op_code) {
		case 0:
			input_stream >> command;
			bst.insert_node(command);
			break;
		case 1:
			input_stream >> command;
			bst.delete_node(command);
			break;
		case 2:
			input_stream >> depth;
			bst.dump_depth(depth);
			break;
		case 3:
			bst.dump_leaf();
			break;
		default:
			break;
		}
	}

	input_stream.close();
	return 0;
}

int get_op_code(const string& op) {
	static const vector<string> command = { "+", "-", "depth", "leaf" }; // 한번만 생성되도록 static 키워드 지정

	ptrdiff_t pos = find(begin(command), end(command), op) - begin(command);
	return static_cast<int>(pos);
}

BST::BST(const string & path)
	: output_stream(path), root_node(nullptr) {}

BST::~BST() {
	output_stream.close();
	if (root_node)
		delete root_node;
}

void BST::insert_node(const string & data) {
	if (root_node == nullptr)
		root_node = new TreeNode(data);
	else {
        // recursive lambda function
		function<void(TreeNode*)> insert_node;
		insert_node = [&data, &insert_node](TreeNode* node) -> void {
			if (node->value > data) {
				if (node->left)
					insert_node(node->left);
				else
					node->left = new TreeNode(data);
			}
			else if (node->value < data) {
				if (node->right)
					insert_node(node->right);
				else
					node->right = new TreeNode(data);
			}
		};

		insert_node(root_node);
	}
}

void BST::delete_node(const string & data) {
	if (root_node) {
        // recursive lambda function
		function<TreeNode*(TreeNode*, const string&)> delete_node;
		delete_node = [&delete_node](TreeNode* node, const string& value) -> TreeNode* {
			if (node == nullptr)
				return nullptr;

			if (node->value > value)
				node->left	= delete_node(node->left, value);
			else if (node->value < value)
				node->right = delete_node(node->right, value);
			else {
				if (node->left == nullptr) {
                    // node->left가 비어있을 때, right node를 그대로
                    // node의 parent의 right로 교체.
					TreeNode* ret_node = node->right;
                    // node destructor가 호출될 때, 오른쪽 node까지 deallocate 되므로 nullptr 지정
					node->right = nullptr;
					delete node;
					return ret_node;
				}

                //왼쪽 sub-tree의 max node를 가져오는 동작.
				TreeNode* swap_node = node->left->get_max_node();
				//가져온 max-node의 value를 현재 node의 value에 할당.
				node->value = swap_node->value;
				//max-value로 왼쪽 sub-tree의 root부터 delete_node를 다시 호출
				//max-node를 deallocate 하기 위한 동작.
				node->left = delete_node(node->left, swap_node->value);
			}

			return node; // return으로 parent node에 대한 pointer를 따로 보관하지 않아도 parent node을 변경시킬 수 있다.
		};

		root_node = delete_node(root_node, data);
	}
}

void BST::dump_depth(int depth) const {
	auto& stream = this->output_stream;
	bool exists = false;
	// recursive lambda function
	function<void(const TreeNode*, int)> dump_depth;
	dump_depth = [depth, &stream, &dump_depth, &exists](const TreeNode* node, int current_depth) {
		if (node == nullptr)
			return;

		if (current_depth == depth) {
			stream << node->value << ' ';
			exists = true;
		}
		else {
			dump_depth(node->left, current_depth + 1);
			dump_depth(node->right, current_depth + 1);
		}
	};

	dump_depth(root_node, 1);
	if (exists) stream           << endl;
	else        stream <<  "NO"  << endl;
}

void BST::dump_leaf(void) const {
	auto& stream = this->output_stream;

	bool exists = false;
	// recursive lambda function
	function<void(const TreeNode*)> dump_leaf;
	dump_leaf = [&stream, &dump_leaf, &exists](const TreeNode* node) {
		if (node == nullptr)
			return;

		if (node->left == nullptr && node->right == nullptr) {
			stream << node->value << ' ';
			exists = true;
		}
		else {
			dump_leaf(node->left);
			dump_leaf(node->right);
		}
	};

	dump_leaf(root_node);
	if (exists) stream << endl;
}

TreeNode::TreeNode(const string& data)
	: value(data) {};

TreeNode::~TreeNode() {
	if (left)
		delete left;
	if (right)
		delete right;
}

TreeNode * TreeNode::get_max_node(void) {
	TreeNode* cur_node = this;

	while (cur_node->right)
		cur_node = cur_node->right;

	return cur_node;
}

#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <unordered_set>

class TreeNode {
public:
    int value;
    std::vector<std::shared_ptr<TreeNode>> neighbors;

    TreeNode(int val) : value(val) {}

    void addNeighbor(std::shared_ptr<TreeNode> node) {
        neighbors.push_back(node);
    }
};

class DFSTreeIterator {
    std::stack<std::shared_ptr<TreeNode>> nodeStack;
    std::unordered_set<std::shared_ptr<TreeNode>> visited;

public:
    DFSTreeIterator(std::shared_ptr<TreeNode> root) {
        if (root) {
            nodeStack.push(root);
            visited.insert(root);
        }
    }

    bool hasNext() const {
        return !nodeStack.empty();
    }

    std::shared_ptr<TreeNode> next() {
        if (!hasNext()) {
            throw std::out_of_range("No more elements in iterator");
        }

        auto current = nodeStack.top();
        nodeStack.pop();

        // Push neighbors in reverse order to visit them in order
        for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
            if (visited.find(*it) == visited.end()) {
                visited.insert(*it);
                nodeStack.push(*it);
            }
        }

        return current;
    }
};

// Demonstration
int main() {
    // Create nodes
    auto node1 = std::make_shared<TreeNode>(1);
    auto node2 = std::make_shared<TreeNode>(2);
    auto node3 = std::make_shared<TreeNode>(3);
    auto node4 = std::make_shared<TreeNode>(4);
    auto node5 = std::make_shared<TreeNode>(5);
    auto node6 = std::make_shared<TreeNode>(6);

    // Build the directed tree
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    node1->addNeighbor(node2);
    node1->addNeighbor(node3);
    node2->addNeighbor(node4);
    node2->addNeighbor(node5);
    node3->addNeighbor(node6);

    // Create DFS iterator starting from node1
    DFSTreeIterator dfs(node1);

    std::cout << "DFS traversal: ";
    while (dfs.hasNext()) {
        auto node = dfs.next();
        std::cout << node->value << " ";
    }
    std::cout << std::endl;

    return 0;
}

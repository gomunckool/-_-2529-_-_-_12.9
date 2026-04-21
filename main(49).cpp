#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insertBST(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);
    return root;
}

Node* createBinaryTree(int n) {
    if (n <= 0) return nullptr;
    int val;
    cout << "Vvedit znachennya: ";
    cin >> val;
    Node* root = new Node(val);
    root->left = createBinaryTree(n / 2);
    root->right = createBinaryTree(n - 1 - n / 2);
    return root;
}

Node* createBST(int n) {
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int val;
        cout << "Element " << i + 1 << ": ";
        cin >> val;
        root = insertBST(root, val);
    }
    return root;
}

void printTree(Node* root, int space, int currentTarget) {
    if (root == nullptr) return;
    space += 5;
    printTree(root->right, space, currentTarget);
    cout << endl;
    for (int i = 5; i < space; i++) cout << " ";
    
    if (root->data == currentTarget)
        cout << "[" << root->data << "]" << "\n";
    else
        cout << root->data << "\n";
        
    printTree(root->left, space, currentTarget);
}

void deleteBranch(Node*& root) {
    if (root == nullptr) return;
    deleteBranch(root->left);
    deleteBranch(root->right);
    delete root;
    root = nullptr;
}

Node* findMin(Node* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

Node* removeNode(Node* root, int key) {
    if (root == nullptr) return nullptr;

    if (key < root->data) root->left = removeNode(root->left, key);
    else if (key > root->data) root->right = removeNode(root->right, key);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = removeNode(root->right, temp->data);
        }
    }
    return root;
}

void storeInVector(Node* root, vector<Node*>& nodes) {
    if (root == nullptr) return;
    storeInVector(root->left, nodes);
    nodes.push_back(root);
    storeInVector(root->right, nodes);
}

Node* buildBalancedTree(vector<Node*>& nodes, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Node* root = nodes[mid];
    root->left = buildBalancedTree(nodes, start, mid - 1);
    root->right = buildBalancedTree(nodes, mid + 1, end);
    return root;
}

Node* balanceBST(Node* root) {
    if (root == nullptr) return nullptr;
    vector<Node*> nodes;
    storeInVector(root, nodes);
    return buildBalancedTree(nodes, 0, nodes.size() - 1);
}

int calculateSum(Node* root) {
    if (root == nullptr) return 0;
    return root->data + calculateSum(root->left) + calculateSum(root->right);
}

Node** findNodePtr(Node** root, int key) {
    if (*root == nullptr || (*root)->data == key) return root;
    if (key < (*root)->data) return findNodePtr(&((*root)->left), key);
    return findNodePtr(&((*root)->right), key);
}

void showMenu() {
    cout << "\n--- MENU --- \n";
    cout << "1. Stvoryty binarne derevo\n";
    cout << "2. Vyvesty derevo\n";
    cout << "3. Stvoryty BST\n";
    cout << "4. Dodaty element u BST\n";
    cout << "5. Zbalansuvaty BST\n";
    cout << "6-8. Vydalyty vuzol (0, 1, 2 nashchadky)\n";
    cout << "9. Vydalyty tsilu gilku\n";
    cout << "10. Obchyslyty sumu\n";
    cout << "0. Vykhid\n";
    cout << "Vybiraite diyu: ";
}

int main() {
    Node* root = nullptr;
    int choice, val, n;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Kilkist elementiv: "; cin >> n;
                root = createBinaryTree(n);
                break;
            case 2:
                cout << "Vvedit znachennya dlya pidsvitky (abo 0): "; cin >> val;
                printTree(root, 0, val);
                break;
            case 3:
                cout << "Kilkist elementiv: "; cin >> n;
                root = createBST(n);
                break;
            case 4:
                cout << "Vvedit chyslo: "; cin >> val;
                root = insertBST(root, val);
                break;
            case 5:
                root = balanceBST(root);
                cout << "Derevo zbalansovano.\n";
                break;
            case 6: case 7: case 8:
                cout << "Vvedit znachennya dlya vydalennya: "; cin >> val;
                root = removeNode(root, val);
                break;
            case 9:
                cout << "Vvedit korin gilky dlya vydalennya: "; cin >> val;
                {
                    Node** target = findNodePtr(&root, val);
                    if (*target) deleteBranch(*target);
                }
                break;
            case 10:
                cout << "Suma vsikh elementiv: " << calculateSum(root) << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

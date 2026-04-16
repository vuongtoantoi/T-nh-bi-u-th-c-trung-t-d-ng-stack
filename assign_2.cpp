#include <iostream>
using namespace std;
// Tao cay nhi phan
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};
// Ham chen gia tri vao cay nhi phan tim kiem.
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } 
    else {
        root->right = insert(root->right, value);
    }
    
    return root;
}
// Ham duyet in-order va luu vao mang
void storeSorted(Node* root, int arr[], int& index) {
    if (root != nullptr) {
        storeSorted(root->left, arr, index);   // Duyệt nhánh trái
        arr[index++] = root->data;             // Lấy giá trị nút gốc
        storeSorted(root->right, arr, index);  // Duyệt nhánh phải
    }
}
//Don dep bo nho say khi dung cay nhi phan
void freeTree(Node* root) {
    if (root != nullptr) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}
//Tree Sort
void treeSort(int arr[], int n) {
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }
    int index = 0;
    storeSorted(root, arr, index);
    freeTree(root);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[100];
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    for(int i = 0; i < n; i++) {
        cout << "Nhap phan tu thu " << i + 1 << ": ";
        cin >> arr[i];
    }
    cout << "Mang ban dau: ";
    printArray(arr, n);

    treeSort(arr, n);

    cout << "Mang sau khi sap xep (Tree Sort): ";
    printArray(arr, n);
    return 0;
}
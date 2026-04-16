#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Cấu trúc một nút của cây Huffman
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Khai báo toán tử so sánh cho Hàng đợi ưu tiên (Min-Heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; // Nút có tần suất nhỏ hơn sẽ nổi lên trên
    }
};

// Hàm đệ quy để duyệt cây và tạo từ điển mã Huffman
void generateCodes(Node* root, string code, unordered_map<char, string> &huffmanCodes) {
    if (root == nullptr) return;

    // Nếu là nút lá (không có con), lưu mã của ký tự đó
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Hàm dọn dẹp bộ nhớ cây
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

int main() {
    // Văn bản giả định đọc từ file text
    string text = "huffman coding is fun and efficient";
    cout << "Van ban goc:\n" << text << "\n\n";

    // 1. Đếm tần suất xuất hiện của từng ký tự
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // 2. Tạo Hàng đợi ưu tiên (Min-Heap) để lưu các nút lá
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // 3. Xây dựng cây Huffman
    while (pq.size() != 1) {
        // Lấy 2 nút có tần suất nhỏ nhất
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        // Tạo nút cha với tần suất bằng tổng 2 nút con. Ký tự '\0' biểu thị nút trung gian.
        Node *parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // Đẩy nút cha ngược lại vào hàng đợi
        pq.push(parent);
    }

    // Nút cuối cùng còn lại chính là Gốc (Root) của cây
    Node* root = pq.top();

    // 4. Tạo mã Huffman cho từng ký tự
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "Bang ma Huffman:\n";
    for (auto pair : huffmanCodes) {
        cout << "'" << pair.first << "' : " << pair.second << "\n";
    }

    // 5. Mã hóa văn bản
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCodes[ch];
    }
    cout << "\nChuoi da ma hoa:\n" << encodedString << "\n";

    // 6. Giải mã văn bản từ chuỗi đã mã hóa
    string decodedString = "";
    Node* curr = root;
    for (int i = 0; i < encodedString.length(); i++) {
        // Rẽ trái nếu gặp '0', rẽ phải nếu gặp '1'
        if (encodedString[i] == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        // Nếu chạm đến nút lá, lấy ký tự và quay lại gốc để xét tiếp
        if (!curr->left && !curr->right) {
            decodedString += curr->ch;
            curr = root;
        }
    }
    
    cout << "\nChuoi sau khi giai ma:\n" << decodedString << "\n";

    freeTree(root);
    return 0;
}
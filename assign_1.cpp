#include <iostream>
#include <string>
#include <stack>
using namespace std;

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
int main(){
    stack<char> s;
    cout<<"Nhap vao bieu thuc trung to: ";
    string str;
    getline(cin, str);
    if(str.empty()){
        cout<<"Bieu thuc rong!"<<endl;
        return 0;
    }
    string result;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (isalnum(c)) {
            result += c;
        }
        else if (c == '(') {
            s.push(c);
        }
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                result += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() == '(') {
                s.pop();
            }
            else{
                cout<<"Bieu thuc khong hop le!"<<endl;
                return 0;
            }
        }
        else {
            while (!s.empty() && precedence(c) <= precedence(s.top())) {
                result += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        if (s.top() == '(') {
            cout<<"Bieu thuc khong hop le!"<<endl;
            return 0;
        }
        result += s.top();
        s.pop();
    }
    cout<<"Bieu thuc hau to: "<<result<<endl;
    stack<int> eval;
    for (int i = 0; i < result.length(); i++) {
        char c = result[i];
        if (isalnum(c)) {
            eval.push(c - '0');
        }
        else {
            int val2 = eval.top();
            eval.pop();
            int val1 = eval.top();
            eval.pop();
            switch (c) {
                case '+':
                    eval.push(val1 + val2);
                    break;
                case '-':
                    eval.push(val1 - val2);
                    break;
                case '*':
                    eval.push(val1 * val2);
                    break;
                case '/':
                    eval.push(val1 / val2);
                    break;
            }
        }
    }
    cout<<"Ket qua: "<<eval.top()<<endl;
    return 0;
}
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Node {
    int l;
    int r;
    unordered_map<char, int> children;
};

vector<Node> sTree;



int insert(string& text, int i, int allNodes, int len) {
    int k = i;
    int currentNode = 0;
    int temp = 0;
    int oldR = 0;
    while (true) {
        if (currentNode == 0) {
            if (sTree[0].children.count(text[k])) {
                currentNode = sTree[0].children[text[k]];
                temp = sTree[currentNode].l;
            }
            else {
                sTree.push_back(Node());
                allNodes += 1;
                sTree[allNodes].l = k;
                sTree[allNodes].r = len;
                sTree[currentNode].children[text[k]] = allNodes;
                return allNodes;
            }
        }
        else {
            if (text[k] == text[temp] && temp != sTree[currentNode].r) { // идём внутри ребра + всё совпадает
                k += 1;
                temp += 1;
            }
            else if(text[k] == text[temp] && temp == sTree[currentNode].r){ //дошли до конца ребра 
                if (k == len) { //конец
                    return allNodes;
                }
                else { // не конец
                    k += 1;
                    if (sTree[currentNode].children.count(text[k])) {// если есть подходящий символ
                        currentNode = sTree[currentNode].children[text[k]];
                        temp = sTree[currentNode].l;
                    }
                    else {// если символа нет
                        sTree.push_back(Node());
                        allNodes += 1;
                        sTree[allNodes].l = k;
                        sTree[allNodes].r = len;
                        sTree[currentNode].children[text[k]] = allNodes;
                        return allNodes;
                    }
                }
            }
            else {//есть несовпадение символов => создаем 2 ребра в одном будет находится остаток этого, в другом остаток добавляемого
                oldR = sTree[currentNode].r;
                sTree[currentNode].r = (temp - 1);

                sTree.push_back(Node());// при разветвлении в кусок с остатком надо переносить детей (допилить)
                allNodes += 1;
                sTree[allNodes].l = temp;
                sTree[allNodes].r = oldR;
                sTree[allNodes].children = sTree[currentNode].children;//удалять старых детей
                sTree[currentNode].children.clear();
                sTree[currentNode].children[text[temp]] = allNodes;

                sTree.push_back(Node());
                allNodes += 1;
                sTree[allNodes].l = k;
                sTree[allNodes].r = len;
                sTree[currentNode].children[text[k]] = allNodes;
                return allNodes;
            }
        }
    }

}

int createSuffixTree(string& text) {
    int allNodes = 0;
    sTree.push_back(Node());
    int len = text.length() - 1;
    for (int i = 0; i < len; i++) {
        allNodes = insert(text, i, allNodes, len);
    }
    return allNodes;
}
//доделать кол-во вхождений для правых паттренов

void childrenSearch(int k, int len, int currentNode, int allNodes, int txtLen) {
    vector<bool> checked(allNodes + 1, 0);
    set<int> enters;
    int originalNode = currentNode;
    bool noChildren = 1;
    bool lastFound = 1;
    int way = sTree[originalNode].r - k;
    if (sTree[originalNode].r == txtLen) {
        cout << k - len + 2;
        return;
    }
    while (checked[originalNode] != 1) {
        if (sTree[currentNode].r == txtLen) {
            enters.insert(txtLen + 2 - way - len);
            checked[currentNode] = 1;
            currentNode = originalNode;
            way = sTree[originalNode].r - k;
        }
        else {
            noChildren = 1;
            for (const auto& nd : sTree[currentNode].children) {
                if(checked[nd.second] == 0){
                    currentNode = nd.second;
                    way += (sTree[currentNode].r - sTree[currentNode].l + 1);
                    noChildren = 0;
                    break;
                }
            }
            if (noChildren == 1) {
                checked[currentNode] = 1;
                currentNode = originalNode;
                way = sTree[originalNode].r - k;
            }
        }
    }
    int i = 1;
    int sz = enters.size();
    for (int n : enters) {
        cout << n;
        if (i != sz) {
            cout << ", ";
            i++;
        }
    }
}

void search(string& pattern, string& text, int patternCounter, int allNodes, int txtLen) {
    int len = pattern.length();
    int k = 0;
    int currentNode = 0;
    if (sTree[0].children.count(pattern[0])) {
        currentNode = sTree[0].children[pattern[0]];
        k = sTree[currentNode].l;
        for (int i = 0; i < len; i++) {
            if (pattern[i] == text[k] && k != sTree[currentNode].r && i != len -1) {//просто сравниваем внутри ребра
                k++;
            } 
            else if (pattern[i] == text[k] && k == sTree[currentNode].r) {//дошли до конца ребра
                if (i == len - 1) {//нашли вхождение в конце ребра!!!!!
                    if (k != txtLen) {
                        cout << patternCounter << ": ";
                        childrenSearch(k, len, currentNode, allNodes, txtLen);
                        cout << "\n";
                    }
                    else {
                        break;
                    }  
                }
                else {//не конец
                    if (sTree[currentNode].children.count(pattern[i+1])) {// если есть подходящий символ
                        currentNode = sTree[currentNode].children[pattern[i + 1]];
                        k = sTree[currentNode].l;
                    }
                    else {
                        break;
                    }
                }
            }
            else if (pattern[i] == text[k] && k != sTree[currentNode].r && i == len - 1) {//нашли вхождение внутри ребра!!!!
                cout << patternCounter << ": ";
                childrenSearch( k, len, currentNode, allNodes, txtLen);
                cout << "\n";
            }
            else {
                break;
            }
        }
    } 
}



int main()
{
    string text;
    string pattern;
    getline(cin, text);
    text += '$';
    int allNodes = createSuffixTree(text);
    int patternCounter = 0;
    int txtLen = text.length() - 1;
    while (getline(cin, pattern)) {
        if (pattern.empty() != true) {
            patternCounter++;
        }
        search(pattern, text, patternCounter, allNodes, txtLen);
    }
}

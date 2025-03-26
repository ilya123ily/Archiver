#ifndef HAFFMAN_H_
#define HAFFMAN_H_

#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>

#include "utilities.h"

class Node {
public:
    Node(size_t freq, Token token, Token min_token, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr)
        : token_(token), min_token_(min_token), freq_(freq), parent_(parent), left_(left), right_(right) {
    }
    ~Node();
    bool operator<(const Node& other) const;
    bool operator>(const Node& other) const;
    Token GetToken() const;
    Token GetMinToken() const;
    size_t GetFreq() const;
    Node* GetLeft() const;
    Node* GetRight() const;
    Node* GetParent() const;
    void PutToken(Token t);
    void PutLeft(Node* left);
    void PutRight(Node* right);
    void PutParent(Node* parent);

private:
    Token token_;
    Token min_token_;
    size_t freq_;
    Node* parent_;
    Node* left_;
    Node* right_;
};

class CompareNodes {
public:
    bool operator()(const Node* a, const Node* b);
};

class Haffman {
public:
    Haffman();
    ~Haffman();
    void BuildByFreq(const std::vector<size_t>& freq_tokens);
    void BuildByLen(const std::vector<size_t>& len_tokens);
    void AddNode(Node* node);
    Node* CollapseNodes(Node* left, Node* right);
    void BuildTreeByFreq();
    void BuildTreeByCode();
    void DFS(Node* cur_node, int len);
    void CodePlusOne(std::vector<bool>& code);
    void BuildCanonicalCodes();
    std::vector<std::pair<size_t, Token>> GetSymbols();
    std::vector<std::vector<bool>> GetCodeTokens();
    Node* GetRoot();

private:
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> nodes_;
    std::vector<size_t> len_tokens_;
    std::vector<std::vector<bool>> code_tokens_;
    std::vector<std::pair<size_t, Token>> symbols_;
    Node* root_;
};

#endif

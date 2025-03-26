#include "haffman.h"

Node::~Node() {
    delete left_;
    left_ = nullptr;
    delete right_;
    right_ = nullptr;
}

Token Node::GetToken() const {
    return token_;
}

size_t Node::GetFreq() const {
    return freq_;
}

Node* Node::GetLeft() const {
    return left_;
}

Node* Node::GetRight() const {
    return right_;
}

Node* Node::GetParent() const {
    return parent_;
}

Token Node::GetMinToken() const {
    return min_token_;
}

void Node::PutToken(Token t) {
    token_ = t;
}

void Node::PutLeft(Node* left) {
    left_ = left;
}

void Node::PutRight(Node* right) {
    right_ = right;
}

void Node::PutParent(Node* parent) {
    parent_ = parent;
}

bool Node::operator<(const Node& other) const {
    return std::tie(freq_, min_token_) < std::tie(other.freq_, other.min_token_);
}

bool Node::operator>(const Node& other) const {
    return std::tie(freq_, min_token_) > std::tie(other.freq_, other.min_token_);
}

bool CompareNodes::operator()(const Node* a, const Node* b) {
    return *a > *b;
}

Haffman::Haffman() : root_(nullptr) {
}

Haffman::~Haffman() {
    delete root_;
    root_ = nullptr;
}

void Haffman::AddNode(Node* node) {
    nodes_.push(node);
}

Node* Haffman::CollapseNodes(Node* left, Node* right) {
    Node* new_node = new Node(left->GetFreq() + right->GetFreq(), utilities::MID_NODE,
                              std::min(left->GetMinToken(), right->GetMinToken()), left, right);
    left->PutParent(new_node);
    right->PutParent(new_node);
    return new_node;
}

void Haffman::BuildByFreq(const std::vector<size_t>& freq_tokens) {
    len_tokens_.resize(utilities::ALPHABET_SIZE, 0);
    code_tokens_.resize(utilities::ALPHABET_SIZE);
    for (size_t i = 0; i < freq_tokens.size(); ++i) {
        if (freq_tokens[i] != 0) {
            Node* node = new Node(freq_tokens[i], static_cast<Token>(i), static_cast<Token>(i));
            nodes_.push(node);
        }
    }
    BuildTreeByFreq();
    DFS(root_, 0);
    BuildCanonicalCodes();
}

void Haffman::BuildByLen(const std::vector<size_t>& len_tokens) {
    len_tokens_ = len_tokens;
    code_tokens_.resize(utilities::ALPHABET_SIZE);
    for (size_t i = 0; i < len_tokens_.size(); ++i) {
        if (len_tokens_[i] != 0) {
            symbols_.push_back({len_tokens_[i], static_cast<Token>(i)});
        }
    }
    std::sort(symbols_.begin(), symbols_.end());
    root_ = new Node(0, utilities::MID_NODE, utilities::MID_NODE);
    BuildTreeByCode();
}

void Haffman::BuildTreeByFreq() {
    while (nodes_.size() > 1) {
        Node* left = nodes_.top();
        nodes_.pop();
        Node* right = nodes_.top();
        nodes_.pop();
        AddNode(CollapseNodes(left, right));
    }
    root_ = nodes_.top();
}

void Haffman::BuildTreeByCode() {
    Node* cur_node = root_;
    size_t cur_len = 0;
    for (std::pair<size_t, Token> symbol : symbols_) {
        while (cur_len < symbol.first) {
            Node* left = new Node(0, utilities::MID_NODE, utilities::MID_NODE);
            left->PutParent(cur_node);
            cur_node->PutLeft(left);
            cur_node = left;
            ++cur_len;
        }
        cur_node->PutToken(symbol.second);
        cur_node = cur_node->GetParent();
        while (cur_node->GetRight() != nullptr) {
            if (cur_node == root_) {
                return;
            }
            cur_node = cur_node->GetParent();
            --cur_len;
        }
        Node* right = new Node(0, utilities::MID_NODE, utilities::MID_NODE);
        right->PutParent(cur_node);
        cur_node->PutRight(right);
        cur_node = cur_node->GetRight();
    }
}

void Haffman::DFS(Node* cur_node, int len) {
    if (cur_node->GetToken() != utilities::MID_NODE) {
        len_tokens_[cur_node->GetToken()] = len;
    } else {
        len += 1;
        DFS(cur_node->GetLeft(), len);
        DFS(cur_node->GetRight(), len);
    }
}

void Haffman::CodePlusOne(std::vector<bool>& code) {
    for (size_t i = code.size() - 1; i >= 0; --i) {
        if (code[i] == true) {
            code[i] = false;
        } else {
            code[i] = true;
            return;
        }
        if (i == 0) {
            return;
        }
    }
}

void Haffman::BuildCanonicalCodes() {
    for (size_t i = 0; i < len_tokens_.size(); ++i) {
        if (len_tokens_[i] != 0) {
            symbols_.push_back({len_tokens_[i], static_cast<Token>(i)});
        }
    }
    std::sort(symbols_.begin(), symbols_.end());
    std::vector<bool> cur(1, false);
    for (std::pair<size_t, Token> symbol : symbols_) {
        if (cur.size() == 1 && cur[0] == false) {
            cur.resize(symbol.first, false);
        }
        if (cur.size() < symbol.first) {
            cur.resize(symbol.first, false);
        }
        code_tokens_[symbol.second] = cur;
        CodePlusOne(cur);
    }
}

std::vector<std::pair<size_t, Token>> Haffman::GetSymbols() {
    return symbols_;
}

std::vector<std::vector<bool>> Haffman::GetCodeTokens() {
    return code_tokens_;
}

Node* Haffman::GetRoot() {
    return root_;
}

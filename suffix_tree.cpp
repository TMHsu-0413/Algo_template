#include <bits/stdc++.h>
using namespace std;

int pos;
int remain;
int ActiveEdge, ActiveLen;
class Node {
public:
  int start, end;
  Node *slink;
  unordered_map<char, Node *> child;
  Node(int s, int e = INT_MAX) : start(s), end(e) { slink = nullptr; }
  int length() { return min(end, pos) - start + 1; }
};

class SuffixTree {
public:
  string str;
  Node *needSL;
  Node *Root;
  Node *ActiveNode;

  // Constructor
  SuffixTree(string s) {
    str = s;
    st_init();
    build();
  }
  // initialize
  void st_init() {
    remain = ActiveEdge = ActiveLen = 0;
    pos = -1;
    Node *node = new Node(-1, -1);
    Root = ActiveNode = node;
  }

  // add suffix link
  void add_SL(Node *Node) {
    if (needSL != Root)
      needSL->slink = Node;
    needSL = Node;
  }

  // get current word in string
  char active_edge() { return str[ActiveEdge]; }

  // 這個節點長度能否包含住目前剩餘的隱藏節點
  // 有個小地方要注意，因為隱藏節點代表藏了幾個，所以要檢查的是目前的長度是否有
  // >= ActiveLen的長度(要比較的是str[ActiveLen + 1]的這個字元)
  bool walk_down(Node *node) {
    if (ActiveLen >= node->length()) {
      ActiveEdge += node->length();
      ActiveLen -= node->length();
      ActiveNode = node;
      return true;
    }
    return false;
  }

  // build suffix tree
  void build() {
    for (auto &c : str) {
      pos++;
      needSL = Root;
      remain++;
      while (remain) {
        // 若沒有隱藏長度，那麼ActiveEdge的字元就從目前這個字開始
        if (ActiveLen == 0)
          ActiveEdge = pos;

        // 若原本沒有這個點，則新增這個點，並讓ActivrNode指向他
        if (!ActiveNode->child.count(active_edge())) {
          Node *Leaf = new Node(pos);
          ActiveNode->child[active_edge()] = Leaf;
          add_SL(ActiveNode);
        } else {
          // 若原本有這個點，要先走訪看看在這個點是否能滿足這次新增的長度
          // 若不夠的話，需要用walk_down走向下一個節點
          Node *nxtNode = ActiveNode->child[active_edge()];
          if (walk_down(nxtNode))
            continue;
          // 若走到後，原本樹上的字與這次新增的相同，則直接++ActiveLen，並把這個點設為下一個需要
          // 加suffix link的點

          // 若我目前的隱藏長度為2，那我需要比較的是第三個字元，所以取str[node->start
          // + ActiveLen]，因為 第三個字元在string內的index其實是2所以需要start
          // + (3 - 1) == start + 2 == start + ActiveLen
          if (str[nxtNode->start + ActiveLen] == c) {
            ActiveLen++;
            add_SL(ActiveNode);
            break;
          }
          // 分割點會從(2,end)變成(2,2)->(3,end) nxtNode
          //                           \>(4,end) leaf
          Node *split =
              new Node(nxtNode->start, nxtNode->start + ActiveLen - 1);
          ActiveNode->child[active_edge()] = split;
          Node *Leaf = new Node(pos);
          split->child[c] = Leaf;
          nxtNode->start += ActiveLen;
          split->child[str[nxtNode->start]] = nxtNode;
          add_SL(split);
        }
        remain--;
        if (ActiveNode == Root && ActiveLen > 0) {
          ActiveLen--;
          ActiveEdge = pos - remain + 1;
        } else {
          ActiveNode = ActiveNode->slink ? ActiveNode->slink : Root;
        }
      }
    }
  }
  // debug用，看有哪些node
  void dfs(Node *node) {
    cout << node->start << " " << node->end;
    if (node->slink)
      cout << "  Suffix link node:"
           << " " << node->slink->start << " " << node->slink->end << endl;
    else
      cout << endl;

    for (auto it : node->child)
      dfs(it.second);
    cout << endl;
  }

  // O(len(s))，找s這個字是否為建樹字串的substring
  bool find(string s) {
    Node *node = Root;
    for (int i = 0; i < s.size();) {
      if (node->child.count(s[i])) {
        node = node->child[s[i]];
        for (int j = node->start; j <= min(node->end, pos) && i < s.size();
             j++, i++) {
          if (s[i] != str[j])
            return false;
        }
      } else {
        return false;
      }
    }
    return true;
  }
};

int main() {
  SuffixTree *st = new SuffixTree("abcacadweacad");
  st->dfs(st->Root);
  cout << st->find("cacadw") << endl;
  cout << st->find("cawweqe") << endl;
  cout << st->find("wea") << endl;
  return 0;
}

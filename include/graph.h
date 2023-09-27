//
// Created by wjl on 2023/5/22.
//

#ifndef CPP_STL_GRAPH_H
#define CPP_STL_GRAPH_H

#pragma once

#include <climits>
#include <stack>
#include <vector>

#include <queue.h>

namespace stl {

typedef enum {
  UNDISCOVERED,// white
  DISCOVERED,  // gray
  VISITED,     // black
} v_status;

typedef enum {
  UNDETERMINED,
  TREE,
  CROSS,
  FORWARD,
  BACKWARD
} e_type;

/**
 * graph class
 */

template<class Tv, class Te>
class graph {
private:
  void reset();

  void _bfs(int, int &);
  void _dfs(int, int &);
  void _bcc(int, int &, std::stack<int> &);
  bool _tsort(int, int &, std::stack<Tv> *);
  template<class Pu>
  void _pfs(int, Pu);

public:
  int n;

  virtual v_status &status(int) = 0;
  virtual Tv &vertex(int) = 0;
  virtual int in_degree(int) = 0;
  virtual int out_degree(int) = 0;
  virtual int first_nbr(int) = 0;
  virtual int next_nbr(int, int) = 0;
  virtual int &d_time(int) = 0;
  virtual int &f_time(int) = 0;
  virtual int &parent(int) = 0;
  virtual int &prior(int) = 0;

  virtual int insert(const Tv &) = 0;
  virtual Tv remove(int) = 0;

  int e;

  virtual bool exists(int, int) = 0;
  virtual e_type &type(int, int) = 0;
  virtual Te &edge(int, int) = 0;
  virtual int &weight(int, int) = 0;

  virtual void insert(const Te &, int, int, int) = 0;
  virtual Te remove(int, int) = 0;

  void bfs(int);
  void dfs(int);
  void bcc(int);
  std::stack<Tv> *tsort(int);
  void prim(int);
  void dijkstra(int);
  template<class Pu>
  void pfs(int, Pu);
};

template<class Tv, class Te>
void graph<Tv, Te>::reset() {
  for (int i = 0; i < n; i++) {
    status(i) = UNDISCOVERED;
    d_time(i) = f_time(i) = -1;
    parent(i) = -1;
    prior(i) = INT_MAX;
    for (int j = 0; j < n; j++) {
      if (exists(i, j)) {
        type(i, j) = UNDETERMINED;
      }
    }
  }
}

template<class Tv, class Te>
void graph<Tv, Te>::_bfs(int s, int &clock) {
  queue<int> q;
  status(s) = DISCOVERED;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    d_time(u) = ++clock;
    for (int v = 0; v < this->n; v++) {
      if (exists(u, v)) {
        if (status(v) == UNDISCOVERED) {
          status(v) = DISCOVERED;
          q.push(v);
          type(u, v) = TREE;
          parent(v) = u;
        } else {
          type(u, v) = CROSS;
        }
      }
    }
    status(u) = VISITED;
  }
}

template<class Tv, class Te>
void graph<Tv, Te>::_dfs(int u, int &clock) {
  d_time(u) = ++clock;
  status(u) = DISCOVERED;
  for (int v = 0; v < this->n; v++) {
    if (exists(u, v)) {
      switch (status(v)) {
        case UNDISCOVERED:
          type(u, v) = TREE;
          parent(v) = u;
          _dfs(v, clock);
          break;
        case DISCOVERED:
          type(u, v) = BACKWARD;
          break;
        default:
          type(u, v) = (d_time(u) < d_time(v)) ? FORWARD : CROSS;
          break;
      }
    }
  }
  status(u) = VISITED;
  f_time(u) = ++clock;
}

template<class Tv, class Te>
void graph<Tv, Te>::_bcc(int, int &, std::stack<int> &) {
}

template<class Tv, class Te>
bool graph<Tv, Te>::_tsort(int u, int &clock, std::stack<Tv> *stk) {
  d_time(u) = ++clock;
  status(u) = DISCOVERED;
  for (int v = 0; v < this->n; v++) {
    if (exists(u, v)) {
      switch (status(v)) {
        case UNDISCOVERED:
          parent(v) = u;
          type(u, v) = TREE;
          if (!_tsort(v, clock, stk)) {
            return false;
          }
          break;
        case DISCOVERED:
          type(u, v) = BACKWARD;
          return false;
        default:
          type(u, v) = (d_time(u) < d_time(v)) ? FORWARD : CROSS;
          break;
      }
    }
  }
  status(u) = VISITED;
  stk->push(vertex(u));
  return true;
}

template<class Tv, class Te>
template<class Pu>
void graph<Tv, Te>::_pfs(int, Pu) {
}

template<class Tv, class Te>
void graph<Tv, Te>::bfs(int s) {
  reset();
  int clock = 0;
  int v = s;
  do {
    if (status(v) == UNDISCOVERED) {
      _bfs(v, clock);
    }
  } while (s != (v = (++v % this->n)));
}

template<class Tv, class Te>
void graph<Tv, Te>::dfs(int s) {
  reset();
  int clock = 0;
  int v = s;
  do {
    if (status(v) == UNDISCOVERED) {
      _dfs(v, clock);
    }
  } while (s != (v = (++v % n)));
}

template<class Tv, class Te>
void graph<Tv, Te>::bcc(int) {
}

template<class Tv, class Te>
std::stack<Tv> *graph<Tv, Te>::tsort(int s) {
  reset();
  int clock = 0;
  int v = s;
  std::stack<Tv> *stk = new std::stack<Tv>;
  do {
    if (status(v) == UNDISCOVERED) {
      if (!_tsort(v, clock, stk)) {
        while (!stk->empty()) {
          stk->pop();
        }
        break;
      }
    }
  } while (s != (v = (++v % n)));
  return stk;
}

template<class Tv, class Te>
void graph<Tv, Te>::prim(int) {
}

template<class Tv, class Te>
void graph<Tv, Te>::dijkstra(int) {
}

template<class Tv, class Te>
template<class Pu>
void graph<Tv, Te>::pfs(int, Pu) {
}

template<class Tv>
struct _vertex {
  Tv data;
  int in_degree;
  int out_degree;
  v_status status;
  int d_time;
  int f_time;
  int parent;
  int prior;

  _vertex(const Tv &d = (Tv) 0)
      : data(d), in_degree(0), out_degree(0), status(UNDISCOVERED),
        d_time(-1), f_time(-1), parent(-1), prior(INT_MAX) {}
};

template<class Te>
struct _edge {
  Te data;
  int weight;
  e_type type;

  _edge(const Te &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

template<class Tv, class Te>
class graph_matrix : public graph<Tv, Te> {
private:
  std::vector<_vertex<Tv>> V;
  std::vector<std::vector<_edge<Te> *>> E;

public:
  graph_matrix() {
    this->n = this->e = 0;
  }

  ~graph_matrix() {
    for (int j = 0; j < this->n; j++) {
      for (int k = 0; k < this->n; k++) {
        E[j][k] = NULL;
      }
    }
  }

  v_status &status(int i) override {
    return V[i].status;
  }

  Tv &vertex(int i) override {
    return V[i].data;
  }

  int in_degree(int i) override {
    return V[i].in_degree;
  }

  int out_degree(int i) override {
    return V[i].out_degree;
  }

  int first_nbr(int i) override {
    return next_nbr(i, this->n);
  }

  int next_nbr(int i, int j) override {
    while ((j > -1) && !exists(i, --j))
      ;
    return V[i].status;
  }

  int &d_time(int i) override {
    return V[i].d_time;
  }

  int &f_time(int i) override {
    return V[i].f_time;
  }

  int &parent(int i) override {
    return V[i].parent;
  }

  int &prior(int i) override {
    return V[i].prior;
  }

  int insert(const Tv &tv) override {
    for (int j = 0; j < this->n; j++) {
      E[j].push_back(NULL);
    }
    this->n++;
    E.push_back(std::vector<_edge<Te> *>(this->n, (_edge<Te> *) NULL));
    V.emplace_back(tv);
    return V.size() - 1;
  }

  Tv remove(int i) override {
    for (int j = 0; j < this->n; j++) {
      if (exists(i, j)) {
        E[i][j] = NULL;
        this->e--;
        V[j].in_degree--;
      }
    }
    E.erase(E.begin() + i);
    this->n--;
    Tv back = vertex(i);
    V.erase(V.begin() + i);
    for (int j = 0; j < this->n; j++) {
      _edge<Te> *e = *(E[j].begin() + i);
      E[j].erase(E[j].begin() + i);
      if (e != NULL) {
        this->e--;
        V[j].out_degree--;
      }
    }
    return back;
  }

  bool exists(int i, int j) override {
    return (i >= 0) && (i < this->n) && (j >= 0) && (j < this->n) && E[i][j] != NULL;
  }

  e_type &type(int i, int j) override {
    return E[i][j]->type;
  }

  Te &edge(int i, int j) override {
    return E[i][j]->data;
  }

  int &weight(int i, int j) override {
    return E[i][j]->weight;
  }

  void insert(const Te &te, int w, int i, int j) override {
    if (exists(i, j)) {
      return;
    }
    E[i][j] = new _edge<Te>(te, w);
    this->e++;
    V[i].out_degree++;
    V[j].in_degree++;
  }

  Te remove(int i, int j) override {
    if (exists(i, j)) {
      return NULL;
    }
    Te back = edge(i, j);
    E[i][j] = NULL;
    this->e--;
    V[i].out_degree--;
    V[i].in_degree--;
    return back;
  }

  void print_path(int s, int v) {
    if (v == s) {
      std::cout << s << " ";
    } else if (parent(v) == -1) {
      std::cout << "no path ";
    } else {
      print_path(s, parent(v));
      std::cout << v << " ";
    }
  }

  void print() {
    std::cout << "graph(" << this->n << ", " << this->e << "): \n";
    std::cout << "vertex: \n";
    for (int i = 0; i < V.size(); i++) {
      std::cout << "[" << i << ":parent=" << parent(i) << "] ";
    }
    std::cout << "\n";
    std::cout << "edge: \n";
    for (int i = 0; i < V.size(); i++) {
      for (int j = 0; j < V.size(); j++) {
        if (exists(i, j)) {
          std::cout << "[1] ";
        } else {
          std::cout << "[ ] ";
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
};

}// namespace stl

template<class Tv, class Te>
void generate_graph(stl::graph_matrix<Tv, Te> &g, int n, int e) {
  while (g.n < n || g.e < e) {
    if (g.n < n) {
      Tv vertex = (Tv) ('A' + rand() % 26);
      g.insert(vertex);
    }
    if (g.n > 1 && g.e < e) {
      int i = rand() % g.n;
      int j = rand() % g.n;
      Te te = (Te) ('a' + rand() % 26);
      int weight = rand() % (3 * n);
      if (!g.exists(i, j) && i != j) {
        g.insert(te, weight, i, j);
      }
    }
  }
}

void generate_bfs_graph(stl::graph_matrix<char, int> &g) {
  g.insert('S');
  for (int i = 0; i < 7; i++) {
    g.insert('A' + i);
  }
  g.insert(1, 1, 0, 1);
  g.insert(2, 2, 0, 3);
  g.insert(3, 3, 0, 4);
  g.insert(4, 4, 1, 3);
  g.insert(5, 3, 1, 5);
  g.insert(6, 2, 3, 2);
  g.insert(7, 1, 4, 2);
  g.insert(8, 2, 5, 6);
  g.insert(9, 3, 5, 7);
  g.insert(10, 5, 7, 2);
  g.insert(11, 5, 7, 6);
}

void generate_dfs_graph(stl::graph_matrix<char, int> &g) {
  for (int i = 0; i < 7; i++) {
    g.insert('A' + i);
  }
  g.insert(1, 1, 0, 1);
  g.insert(2, 2, 0, 2);
  g.insert(3, 3, 0, 5);
  g.insert(4, 4, 1, 2);
  g.insert(5, 3, 3, 0);
  g.insert(6, 2, 3, 4);
  g.insert(7, 1, 4, 5);
  g.insert(8, 2, 5, 6);
  g.insert(9, 3, 6, 0);
  g.insert(10, 5, 6, 2);
}

void generate_tsort_graph(stl::graph_matrix<char, int> &g) {
  for (int i = 0; i < 6; i++) {
    g.insert('A' + i);
  }
  g.insert(1, 1, 0, 2);
  g.insert(2, 1, 0, 3);
  g.insert(3, 1, 1, 2);
  g.insert(4, 1, 2, 3);
  g.insert(5, 1, 2, 4);
  g.insert(6, 1, 2, 5);
  g.insert(7, 1, 4, 5);
}

#endif//CPP_STL_GRAPH_H

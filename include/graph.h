//
// Created by wjl on 2023/5/22.
//

#ifndef CPP_STL_GRAPH_H
#define CPP_STL_GRAPH_H

#pragma once

#include "queue.h"
#include "stack.h"
#include <climits>
#include <vector>

namespace stl {

typedef enum {
  WHITE,// white
  GRAY, // gray
  BLACK,// black
} v_color;

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
  void _bcc(int, int &, stack<int> &);
  bool _tsort(int, int &, stack<Tv> *);
  template<class Pu>
  void _pfs(int, Pu);

public:
  int n;

  virtual v_color &color(int) = 0;
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
  stack<Tv> *tsort(int);
  void prim(int);
  void dijkstra(int);
  template<class Pu>
  void pfs(int, Pu);
};

template<class Tv, class Te>
void graph<Tv, Te>::reset() {
  for (int i = 0; i < n; i++) {
    color(i) = WHITE;
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
void graph<Tv, Te>::_bfs(int, int &) {
}

template<class Tv, class Te>
void graph<Tv, Te>::_dfs(int, int &) {
}

template<class Tv, class Te>
void graph<Tv, Te>::_bcc(int, int &, stack<int> &) {
}

template<class Tv, class Te>
bool graph<Tv, Te>::_tsort(int, int &, stack<Tv> *) {
  return false;
}

template<class Tv, class Te>
template<class Pu>
void graph<Tv, Te>::_pfs(int, Pu) {
}

template<class Tv, class Te>
void graph<Tv, Te>::bfs(int s) {
  reset();
  color(s) = GRAY;
  d_time(s) = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 0; v < this->n; v++) {
      if (exists(u, v) && color(v) == WHITE) {
        color(v) = GRAY;
        d_time(v) = d_time(u) + 1;
        parent(v) = u;
        q.push(v);
      }
    }
    color(u) = BLACK;
  }
}

template<class Tv, class Te>
void graph<Tv, Te>::dfs(int) {
}

template<class Tv, class Te>
void graph<Tv, Te>::bcc(int) {
}

template<class Tv, class Te>
stack<Tv> *graph<Tv, Te>::tsort(int) {
  return nullptr;
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
  v_color color;
  int d_time;
  int f_time;
  int parent;
  int prior;

  _vertex(const Tv &d = (Tv) 0)
      : data(d), in_degree(0), out_degree(0), color(WHITE),
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

  v_color &color(int i) override {
    return V[i].color;
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
    return V[i].color;
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
      _edge<Te> *e = *(E[j].erase(E[j].begin() + i));
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
    Te back = edge(i, j);
    E[i][j] = NULL;
    this->e--;
    V[i].out_degree--;
    V[i].in_degree--;
    return back;
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

void generate_example_graph(stl::graph_matrix<char, char> &g) {
  for (int i = 0; i < 5; i++) {
    g.insert('A' + i);
  }
  g.insert('a', 1, 0, 1);
  g.insert('b', 2, 0, 2);
  g.insert('c', 3, 0, 3);
  g.insert('d', 4, 0, 4);
  g.insert('e', 3, 1, 3);
  g.insert('f', 2, 2, 1);
  g.insert('g', 1, 2, 4);
  g.insert('h', 2, 3, 2);
  g.insert('i', 3, 4, 1);
  g.insert('j', 5, 4, 2);
}

#endif//CPP_STL_GRAPH_H

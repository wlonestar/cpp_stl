//
// Created by wjl on 2023/5/4.
//

#ifndef CPP_STL_GRAPH_H
#define CPP_STL_GRAPH_H

#pragma once

#include "queue.h"
#include "stack.h"
#include "vector.h"

namespace stl {

typedef enum {
  UNDISCOVERED = 0,
  DISCOVERED = 1,
  VISITED = 2,
} v_status;

typedef enum {
  UNDETERMINED = 0,
  TREE = 1,
  CROSS = 2,
  FORWARD = 3,
  BACKWARD = 4,
} e_type;

template<class V>
struct _vertex {
  V data;
  int in_degree;
  int out_degree;
  v_status status;
  int d_time;
  int f_time;
  int parent;
  int priority;

  _vertex(V const &d = (V) 0)
      : data(d), in_degree(0), out_degree(0), status(UNDISCOVERED),
        d_time(-1), f_time(-1), parent(-1), priority(INT_MAX) {}
};

template<class V>
std::ostream &operator<<(std::ostream &out, const _vertex<V> &vertex) {
  out << "vertex(data=" << vertex.data << ",in=" << vertex.in_degree << ",out="
      << vertex.out_degree << ",status=" << vertex.status << ",d=" << vertex.d_time << ",f="
      << vertex.f_time << ",parent=" << vertex.parent << ",prior=" << vertex.priority << ")\n";
  return out;
}

template<class E>
struct _edge {
  E data;
  int weight;
  e_type type;

  _edge() = default;
  _edge(E const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

template<class E>
std::ostream &operator<<(std::ostream &out, const _edge<E> &edge) {
  out << "edge(data=" << edge.data << ",weight=" << edge.weight << ",type=" << edge.type << ")\n";
  return out;
}

template<class V, class E>
class graph {
public:
  typedef std::size_t size_type;

public:
  size_type n_num;
  size_type e_num;
  vector<_vertex<V>> v;
  vector<vector<_edge<E> *>> e;

private:
  void reset() {
    for (int i = 0; i < n_num; i++) {
      status(i) = UNDISCOVERED;
      d_time(i) = f_time(i) = -1;
      parent(i) = -1;
      priority(i) = INT_MAX;
      for (int j = 0; j < n_num; j++) {
        if (exist(i, j)) {
          type(i, j) = UNDETERMINED;
        }
      }
    }
  }

  void _bfs(int p, int &clock) {
    queue<int> q;
    status(p) = DISCOVERED;
    q.push(p);
    while (!q.empty()) {
      int _v = q.front();
      q.pop();
      d_time(_v) = ++clock;
      for (int u = first_nbr(_v); u > -1; u = next_nbr(_v, u)) {
        if (status(u) == UNDISCOVERED) {
          status(u) = DISCOVERED;
          q.push(u);
          type(_v, u) = TREE;
          parent(u) = _v;
        } else {
          type(_v, u) = CROSS;
        }
      }
      status(_v) = VISITED;
    }
  }

  void _dfs(int, int &) {
    TODO();
  }

  void _bcc(int, int &, stack<int> &) {
    TODO();
  }

  bool _tsort(int, int &, stack<V> *) {
    TODO();
  }

  template<class PU>
  void _pfs(int, PU) {
    TODO();
  }

public:
  graph() {
    n_num = 0;
    e_num = 0;
  }

  ~graph() {
    for (int j = 0; j < n_num; j++) {
      for (int k = 0; k < n_num; k++) {
        e[j][k] = nullptr;
      }
    }
  }

  constexpr V &vertex(int i) {
    return v[i].data;
  }
  constexpr const V &vertex(int i) const {
    return v[i].data;
  }

  constexpr size_type in_degree(int i) {
    return v[i].in_degree;
  }
  constexpr const size_type in_degree(int i) const {
    return v[i].in_degree;
  }

  constexpr size_type out_degree(int i) {
    return v[i].out_degree;
  }
  constexpr const size_type out_degree(int i) const {
    return v[i].out_degree;
  }

  int first_nbr(int i) {
    return next_nbr(i, n_num);
  }

  int next_nbr(int i, int j) {
    while ((j > -1) && !exist(i, --j))
      ;
    return j;
  }

  constexpr v_status &status(int i) {
    return v[i].status;
  }
  constexpr const v_status &status(int i) const {
    return v[i].status;
  }

  constexpr int &d_time(int i) {
    return v[i].d_time;
  }
  constexpr const int &d_time(int i) const {
    return v[i].d_time;
  }

  constexpr int &f_time(int i) {
    return v[i].f_time;
  }
  constexpr const int &f_time(int i) const {
    return v[i].f_time;
  }

  constexpr int &parent(int i) {
    return v[i].parent;
  }
  constexpr const int &parent(int i) const {
    return v[i].parent;
  }

  constexpr int &priority(int i) {
    return v[i].priority;
  }
  constexpr const int &priority(int i) const {
    return v[i].priority;
  }

  constexpr E &edge(int i, int j) {
    return e[i][j]->data;
  }
  constexpr const E &edge(int i, int j) const {
    return e[i][j]->data;
  }

  constexpr e_type &type(int i, int j) {
    assert(e.size() >= i + 1 && e.size() <= i + 1 && e[i].size() >= j + 1 && e[i].size() <= j + 1);
    return e[i][j]->type;
  }
  constexpr const e_type &type(int i, int j) const {
    assert(e.size() >= i + 1 && e.size() <= i + 1 && e[i].size() >= j + 1 && e[i].size() <= j + 1);
    return e[i][j]->type;
  }

  constexpr int &weight(int i, int j) {
    return e[i][j]->weight;
  }
  constexpr const int &weight(int i, int j) const {
    return e[i][j]->weight;
  }

  int insert(V const &vertex) {
    for (int j = 0; j < n_num; j++) {
      e[j].push_back(nullptr);
    }
    n_num++;
    e.push_back(vector<_edge<E> *>(n_num, (_edge<E> *) nullptr));
    auto ret = v.emplace_back(vertex);
    return ret.data;
  }

  V remove(int i) {
    for (int j = 0; j < n_num; j++) {
      if (exist(i, j)) {
        delete e[i][j];
        v[j].in_degree--;
      }
    }
    e.remove(i);
    n_num--;
    V back = vertex(i);
    v.remove(i);
    for (int j = 0; j < n_num; j++) {
      if (_edge<E> *_e = e[j].remove(i)) {
        delete _e;
        v[j].out_degree--;
      }
    }
    return back;
  }

  bool exist(int i, int j) const {
    return (i >= 0) && (i < n_num) && (j >= 0) && (j < n_num) && e[i][j]->data != NULL;
  }

  void insert(E const &edge, int w, int i, int j) {
    if (exist(i, j)) {
      return;
    }
    e[i][j] = new _edge<E>(edge, w);
    e_num++;
    v[i].out_degree++;
    v[i].in_degree++;
  }

  E remove(int i, int j) {
    E back = edge(i, j);
    delete e[i][j];
    e[i][j] = nullptr;
    e_num--;
    v[i].in_degree--;
    v[i].out_degree--;
    return back;
  }

  void bfs(int s) {
    reset();
    int clock = 0;
    int p = s;
    do {
      if (status(p) == UNDISCOVERED) {
        _bfs(p, clock);
      }
    } while (s != (p = (++p % n_num)));
  }

  void dfs(int) {
    TODO();
  }

  void bcc(int) {
    TODO();
  }

  stack<V> *tsort(int) {
    TODO();
  }

  void prim(int) {
    TODO();
  }

  void dijkstra(int) {
    TODO();
  }

  template<class PU>
  void pfs(int, PU) {
    TODO();
  }

  void print() {
    std::cout << "graph(n=" << n_num << ", e=" << e_num << "): \n";
    v.for_each(v.begin(), v.end(), [](const _vertex<V> &vertex) {
      std::cout << vertex;
    });
    for (int i = 0; i < e.size(); i++) {
      for (int j = 0; j < e[i].size(); j++) {
        _edge<E> *edge = e[i][j];
        if (edge->data != NULL) {
          std::cout << "edge(data=" << edge->data << ",weight="
                    << edge->weight << ",type=" << edge->type << ")\n";
        }
      }
    }
    //    e.for_each(e.begin(), e.end(), [this](const vector<_edge<E>*> &sub) {
    //      assert(sub.size() == this->n_num);
    //      sub.for_each(sub.begin(), sub.end(), [](_edge<E> *edge) {
    //        std::cout << "edge(data=" << edge->data << ",weight="
    //                  << edge->weight << ",type=" << edge->type << ")\n";
    //      });
    //    });
  }
};

template<typename Tv, typename Te>
std::ostream &operator<<(std::ostream &out, const graph<Tv, Te> &g) {
  out << "graph"
      << " (" << g.n_num << ", " << g.e_num << "):\n";
  out << "vertex | ";
  for (int i = 0; i < g.n_num; i++) {
    out << g.vertex(i) << " ";
  }
  out << "\n";
  for (int i = 0; i < g.n_num; i++) {
    for (int j = 0; j < g.n_num; j++) {
      if (g.exist(i, j)) {
        out << "1 ";
      } else {
        out << "  ";
      }
    }
    out << "\n";
  }
  out << "\n    ";
  out << "\n";
  return out;
}

}// namespace stl

#endif//CPP_STL_GRAPH_H

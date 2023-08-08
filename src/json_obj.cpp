#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

class person {
private:
  std::string name;
  std::string address;
  int age;
public:
  person(std::string n, std::string addr, int a): name(n), address(addr), age(a) {}

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(person, name, address, age)
};

//template<class T>
struct node {
  int data;
  node *next;

  node(int val) : data(val), next(nullptr) {}

  friend void to_json(json &j, const node &t) {
    j["data"] = t.data;
    if (t.next != nullptr) {
      j["next"] = t.next->data;
    } else {
      j["next"] = -1;
    }
  }

};

//template<class T>
class list {
private:
  node *head;
  int size;

public:
  list() : size(0) {
    head = new node(-1);
  }

  void insert(int val) {
    assert(val > -1);
    node *p = new node(val);
    p->next = head->next;
    head->next = p;
  }

  friend void to_json(json &j, const list &t) {
    assert(t.head != nullptr);
    std::vector<node> v;
    node *p = t.head->next;
    while (p != nullptr) {
      v.push_back(*p);
      p = p->next;
    }
    j["data"] = v;
    j["size"] = t.size;
  }

};

int main() {
  list l;
  for (int i = 0; i < 5; i++) {
    l.insert(i);
  }

  json j;
  to_json(j, l);
  std::cout << j;

  return 0;
}

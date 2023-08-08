//
// Created by wjl on 2023/8/8.
//

#include <filesystem>
#include <fstream>
#include <rbtree.h>
#include <util.h>

using nlohmann::json;

template<class T>
bool exists(stl::vector<int> &v, int &value) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it == value) {
      return true;
    }
  }
  return false;
}

void generate_rbtree(stl::rbtree<int> &t, int n) {
  stl::vector<int> v;
  while (v.size() < n) {
    int val = stl::random_int(2 * n);
    if (!exists<int>(v, val)) {
      v.push_back(val);
    }
  }
  for (int &item: v) {
    t.insert(item);
  }
}

std::string write_to_file(json &j) {
  namespace fs = std::filesystem;
  using namespace stl::visual;

  // create directory if not exists
  auto directory = fs::path(fs::current_path().parent_path().string() + "/result");
  if (!fs::exists(directory)) {
    fs::create_directory(directory);
  }
  // get current timestamp
  auto dh_string = get_current_time();
  // data file path
  auto data_file = directory.string() + "/rbtree_data_" + dh_string + ".js";
  // content
  auto content = "const tree = " + j.dump(2) + "\n\n" + "const nodeDataArray = tree.nodes\nconst linkDataArray = tree.links";
  // write into data file
  std::ofstream ofs(data_file);
  ofs << content;
  ofs.close();
  // template and target html file path
  auto template_file = fs::path(fs::current_path().parent_path().string() + "/template/rbtree.html");
  auto html_file = directory.string() + "/rbtree_" + dh_string + ".html";
  // copy from template to html file
  fs::copy(template_file, html_file);
  // replace html specified line
  auto replace = "<script src=\"rbtree_data.js\"></script>";
  auto replace_with = "<script src=" + data_file + "></script>";
  replace_string_of_file(html_file, replace, replace_with);
  return html_file;
}

int main(int argc, char *argv[]) {
  int n = 10;
  if (argc >= 2) {
    n = atoi(argv[1]);
  }
  stl::rbtree<int> t;
  generate_rbtree(t, n);
  stl::vector<int> v;
  t.in_order(v);
  std::cout << "generate " << n << " different node into a rbtree: [ ";
  v.for_each(v.begin(), v.end(), [](const int &val) {
    std::cout << val << " ";
  });
  std::cout << "]\n";

  json j;
  to_json(j, t);
  auto path = write_to_file(j);
  std::cout << "use browser to see the visualize rbtree: " << path << "\n";
  return 0;
}

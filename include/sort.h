//
// Created by wjl on 2023/5/29.
//

#ifndef CPP_STL_SORT_H
#define CPP_STL_SORT_H

#pragma once

#include "util.h"
#include "vector.h"

namespace stl {

/**
 * insertion sort
 */

template<class T>
void insertion_sort(vector<T> &v, int lo, int hi);

template<class T>
void insertion_sort(vector<T> &v);

template<class T>
void insertion_sort(T *v, int lo, int hi);

template<class T>
void insertion_sort(T *v, int size);

/**
 * merge sort
 */

template<class T>
void merge_sort(vector<T> &v, int lo, int hi);

template<class T>
void merge_sort(vector<T> &v);

template<class T>
void merge_sort(T *v, int lo, int hi);

template<class T>
void merge_sort(T *v, int size);

/**
 * heap sort
 */

template<class T>
void heap_sort(T *a, int n);

/**
 * quick sort
 */

template<class T>
void quick_sort(vector<T> &v, int lo, int hi);

template<class T>
void quick_sort(vector<T> &v);

template<class T>
void quick_sort(T *a, int lo, int hi);

template<class T>
void quick_sort(T *a, int size);

///////////////////////////////////////////////////////////

/**
 * insertion sort implementation
 */

template<class T>
void insertion_sort(vector<T> &v, int lo, int hi) {
  for (int j = lo + 1; j < hi; j++) {
    T key = v[j];
    int i = j - 1;
    while (i >= 0 && v[i] > key) {
      v[i + 1] = v[i];
      i = i - 1;
    }
    v[i + 1] = key;
  }
}

template<class T>
void insertion_sort(vector<T> &v) {
  insertion_sort(v, 0, v.size());
}

template<class T>
void insertion_sort(T *v, int lo, int hi) {
  assert(lo <= hi);
  for (int j = lo + 1; j < hi; j++) {
    T key = v[j];
    int i = j - 1;
    while (i >= 0 && v[i] > key) {
      v[i + 1] = v[i];
      i = i - 1;
    }
    v[i + 1] = key;
  }
}

template<class T>
void insertion_sort(T *v, int size) {
  insertion_sort(v, 0, size);
}

/**
 * merge sort implementation
 */

template<class T>
static void merge(vector<T> &v, int lo, int mi, int hi) {
  assert(lo <= mi && mi <= hi);

  T left[mi - lo];
  for (int i = 0; i < mi - lo; i++) {
    left[i] = v[i + lo];
  }
  T right[hi - mi];
  for (int i = 0; i < hi - mi; i++) {
    right[i] = v[i + mi];
  }

  int i = 0, j = 0, k = lo;
  while (i < mi - lo && j < hi - mi) {
    if (left[i] <= right[j]) {
      v[k++] = left[i++];
    } else {
      v[k++] = right[j++];
    }
  }
  while (i < mi - lo) {
    v[k++] = left[i++];
  }
}

template<class T>
void merge_sort(vector<T> &v, int lo, int hi) {
  if (hi - lo < 2) {
    return;
  }
  assert(lo < hi);
  int mi = (lo + hi) / 2;
  merge_sort(v, lo, mi);
  merge_sort(v, mi, hi);
  merge(v, lo, mi, hi);
}

template<class T>
void merge_sort(vector<T> &v) {
  merge_sort(v, 0, v.size());
}

template<class T>
static void merge(T *v, int lo, int mi, int hi) {
  assert(lo <= mi && mi <= hi);

  T left[mi - lo];
  for (int i = 0; i < mi - lo; i++) {
    left[i] = v[i + lo];
  }
  T right[hi - mi];
  for (int i = 0; i < hi - mi; i++) {
    right[i] = v[i + mi];
  }

  int i = 0, j = 0, k = lo;
  while (i < mi - lo && j < hi - mi) {
    if (left[i] <= right[j]) {
      v[k++] = left[i++];
    } else {
      v[k++] = right[j++];
    }
  }
  while (i < mi - lo) {
    v[k++] = left[i++];
  }
}

template<class T>
void merge_sort(T *v, int lo, int hi) {
  if (hi - lo < 2) {
    return;
  }
  assert(lo < hi);
  int mi = (lo + hi) / 2;
  merge_sort(v, lo, mi);
  merge_sort(v, mi, hi);
  merge(v, lo, mi, hi);
}

template<class T>
void merge_sort(T *v, int size) {
  merge_sort(v, 0, size);
}

/**
 * heap sort implementation
 */

#define left(i) (2 * i + 1)
#define right(i) (2 * i + 2)
#define parent(i) (i - 1) / 2

template<class T>
static void max_heapify(T *a, int heap_size, int i) {
  int l = left(i);
  int r = right(i);
  int largest = i;
  if (l < heap_size && a[l] > a[i]) {
    largest = l;
  }
  if (r < heap_size && a[r] > a[largest]) {
    largest = r;
  }
  if (largest != i) {
    std::swap(a[i], a[largest]);
    max_heapify(a, heap_size, largest);
  }
}

template<class T>
static void build_max_heap(T *a, int n) {
  int heap_size = n;
  for (int i = heap_size / 2; i >= -1; i--) {
    max_heapify(a, heap_size, i);
  }
}

template<class T>
void heap_sort(T *a, int n) {
  build_max_heap(a, n);
  for (int i = n - 1; i >= 0; i--) {
    std::swap(a[i], a[0]);
    max_heapify(a, i, 0);
  }
}

/**
 * quick sort implementation
 */

template<class T>
static int partition(vector<T> &v, int lo, int hi) {
  int i = lo;
  int pivot = v[hi - 1];
  for (int j = lo; j < hi - 1; j++) {
    if (v[j] <= pivot) {
      std::swap(v[i], v[j]);
      i += 1;
    }
  }
  std::swap(v[i], v[hi - 1]);
  return i;
}

template<class T>
void quick_sort(vector<T> &v, int lo, int hi) {
  if (lo < hi) {
    int pivot = partition(v, lo, hi);
    quick_sort(v, lo, pivot);
    quick_sort(v, pivot + 1, hi);
  }
}

template<class T>
void quick_sort(vector<T> &v) {
  quick_sort(v, 0, v.size());
}

template<class T>
static int partition(T *a, int lo, int hi) {
  int i = lo;
  int pivot = a[hi - 1];
  for (int j = lo; j < hi - 1; j++) {
    if (a[j] <= pivot) {
      std::swap(a[i], a[j]);
      i += 1;
    }
  }
  std::swap(a[i], a[hi - 1]);
  return i;
}

template<class T>
void quick_sort(T *a, int lo, int hi) {
  if (lo < hi) {
    int pivot = partition(a, lo, hi);
    quick_sort(a, lo, pivot);
    quick_sort(a, pivot + 1, hi);
  }
}

template<class T>
void quick_sort(T *a, int size) {
  quick_sort(a, 0, size);
}

}// namespace stl

#endif//CPP_STL_SORT_H

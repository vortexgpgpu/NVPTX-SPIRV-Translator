//===--------------------------- Refcount.h ------------------------------===//
//
//                              SPIR Tools
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
/*
 * Contributed by: Intel Corporation
 */

#ifndef SPIRV_MANGLER_REFCOUNT_H
#define SPIRV_MANGLER_REFCOUNT_H

#include <assert.h>

namespace SPIR {

template <typename T> class RefCount {
public:
  RefCount() : Count(0), m_ptr(0) {}

  RefCount(T *ptr) : m_ptr(ptr) { Count = new int(1); }

  RefCount(const RefCount<T> &other) { cpy(other); }

  ~RefCount() {
    if (Count)
      dispose();
  }

  RefCount &operator=(const RefCount<T> &other) {
    if (this == &other)
      return *this;
    if (Count)
      dispose();
    cpy(other);
    return *this;
  }

  void init(T *ptr) {
    assert(!m_ptr && "overrunning non NULL pointer");
    assert(!Count && "overrunning non NULL pointer");
    Count = new int(1);
    m_ptr = ptr;
  }

  bool isNull() const { return (!m_ptr); }

  // Pointer access
  const T &operator*() const {
    sanity();
    return *m_ptr;
  }

  T &operator*() {
    sanity();
    return *m_ptr;
  }

  operator T *() { return m_ptr; }

  operator const T *() const { return m_ptr; }

  T *operator->() { return m_ptr; }

  const T *operator->() const { return m_ptr; }

private:
  void sanity() const {
    assert(m_ptr && "NULL pointer");
    assert(Count && "NULL ref counter");
    assert(*Count && "zero ref counter");
  }

  void cpy(const RefCount<T> &other) {
    Count = other.Count;
    m_ptr = other.m_ptr;
    if (Count)
      ++*Count;
  }

  void dispose() {
    sanity();
    if (0 == --*Count) {
      delete Count;
      delete m_ptr;
      m_ptr = 0;
      Count = 0;
    }
  }

  int *Count;
  T *m_ptr;
}; // End RefCount

} // namespace SPIR

#endif // SPIRV_MANGLER_REFCOUNT_H

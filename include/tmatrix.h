// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE) throw out_of_range("Vector size should be greater than zero");
      pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      if (v.pMem == nullptr) {
          sz = 0;
          pMem = nullptr;
      }
      else {
          sz = v.sz;
          pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept // принимаем на вход r-value ссылку на объект 
  {
      // noexcept - гарантирует, что конструктор не будет выбрасывать исключение
      pMem = nullptr; // гарантируем, что при обмене с другим объектом наш pMem пустой
      swap(v, *this); // this получит ресурсы, которые ранее принадлежали объекту v, а объект v теперь будет указывать на nullptr 
  }
  ~TDynamicVector()
  {
      if (pMem != nullptr) {
          delete[] pMem;
          sz = 0;
      }
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (pMem != nullptr) {
              delete[] pMem;
          }
          if (v.pMem == nullptr) {
              sz = 0;
              pMem = nullptr;
          }
          else {
              sz = v.sz;
              pMem = new T[sz];
              std::copy(v.pMem, v.pMem + sz, pMem);
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          if (pMem != nullptr) {
              delete[] pMem;
          }
          pMem = nullptr;
          swap(v, *this);
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind > sz) throw "error";
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind > sz) throw "error";
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (pMem == nullptr) throw "Error"
      if ((ind < 0) || (ind > sz)) throw "Error"
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (pMem == nullptr) throw "Error"
      if ((ind < 0) || (ind > sz)) throw "Error"
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) {
          return false;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) {
          return true;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return true;
          }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "error len";
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "error len";
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v) // noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw "error len";
      T res = T();
      for (int i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz < 0 || sz > MAX_MATRIX_SIZE || sz == 0) throw "error";
    for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz) return false;
      for (int i = 0; i < m.sz; i++) {
          if (pMem[i] != m.pMem[i]) return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) throw "error len"
      TDynamicVector tmp(sz);
      for (int i = 0; i < sz; i++) {
          T sum = T();
          for (int j = 0; j < sz; j++) {
              sum += pMem[i][j] * v[j];
          }
          tmp[i] = sum;
      }
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "error len";
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + m.pMem[i];
      }
      return tmp;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "error len";
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "error len";
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              T sum = T();
              for (int k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m.pMem[k][j];
              }
              tmp.pMem[i][j] = sum;
          }
      }
      return tmp;
  }

  size_t size() const noexcept { return sz; }
  // ввод/вывод
  // Оператор ввода для TDynamicMatrix
  friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.pMem[i].size(); j++) {
              istr >> m.pMem[i][j];
          }
      }
      return istr;
  }

  // Оператор вывода для TDynamicMatrix
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.pMem[i].size(); j++) {
              ostr << m.pMem[i][j] << ' ';
          }
          ostr << endl;
      }
      return ostr;
  }

};

#endif

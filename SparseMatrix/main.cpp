#include <iostream>
//#include "list.h"
#include "matrix.h"
using namespace std;

/*void Print(int &n, int&position) {
  cout<<n<<", " << position <<endl;
}*/

/*void Increase(int &n) {
  n++;
}*/

int main() {
  /*List<int> l;
  l.PushBack(4);
  l.PushBack(14);
  l.PushBack(24);
  l.PushBack(34);
  l.PushFront(3);
  l.PushFront(23);
  l.PushFront(13);
  l.PushFront(33);
  //l.ForEach(Print);
  */
  //l.ForEach(Increase);
  //l.ForEach(Print);
  Vector<int> v1{{{0, 2}, 9}, {{2, 2}, 3}, {{1, 2}, 10}, {{0,0}, 1}};
  Matrix<int> mat(3, 3, {{{0, 2}, 9}, {{2, 2}, 3}, {{1, 2}, 10}, {{1, 0}, 5}, {{0,0}, 1}});
  Matrix<int> mat5(3, 3, {{{0, 0}, 2}, {{0, 1}, 2}, {{0, 2}, 2}, {{1, 0}, 1}, {{2,0}, 1}});
  //mat.Print();
  //Matrix<int> mat2;
  //mat2.Print();
  //Matrix<int> mat2(mat);

  //mat2.Print();
  Matrix<int> mat3 = mat;
  //mat3.Print();
  //mat.Print();
  Matrix<int> rez = mat - mat3 + mat;
  rez.Print();
  std::cout << std::endl;
  rez = rez.transpose() ^ (-1);
  rez.Print();
  std::cout << std::endl;

  mat5 = mat5.exponentiate(3);
  mat5.Print();

  std::cout << std::endl;
  mat5 = mat5^mat5;
  mat5.Print();
  std::cout << std::endl;

}

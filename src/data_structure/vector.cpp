/*
vector deque 在c++11之前使用erase删除迭代器后该迭代器会失效，但是在c++11之后却不会

函数原型
#if __cplusplus >= 201103L
      erase(const_iterator __position)
      { return _M_erase(begin() + (__position - cbegin())); }
#else
      erase(iterator __position)
      { return _M_erase(__position); }
#endif

*/

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<int> vi;
  for (size_t i = 0; i < 10; i++)
  {
    vi.push_back(i);
  }

	for (vector<int>::iterator it = vi.begin(); it != vi.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

  vector<int>::iterator it = vi.begin();

  it++;
  it++;
  std::cout << "erase " << *it << endl;
  vector<int>::iterator eit = vi.erase(it);

	for (vector<int>::iterator it = vi.begin(); it != vi.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

  std::cout << *it << endl;
  it++;
  std::cout << *it << endl;
  std::cout << *eit << endl;

}
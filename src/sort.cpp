//排序算法
#include <stdio.h>
#include <random>
#include <iostream>
#include <vector>
#include <functional>
#include <time.h>

using namespace std;

//打印队列
void printfNums(std::vector<int>& nums)
{
  std::cout << "[";
  for (size_t i = 0; i < nums.size(); i++)
  {
    std::cout << nums.at(i) << ", ";
  }
  std::cout << "]" << std::endl;
}

//随机数生成
static std::vector<int> generateRandomArray(int size, int min, int max)
{
  vector<int> ret;
  std::uniform_int_distribution<unsigned> u(min, max);
  std::default_random_engine e;
  for (size_t i = 0; i < size; i++)
  {
    ret.push_back(u(e));
  }
  return ret;
}

//判断排序是否完成
static bool isSorted(std::vector<int> &nums)
{
  for (size_t i = 0; i < nums.size() - 1; i++)
  {
    if (nums.at(i) > nums.at(i + 1))
    {
      return false;
    }
  }
  return true;
}

//冒泡排序
static void bubbleSort(std::vector<int> &nums)
{
  for (int i = 0; i < nums.size() - 1; i++)
  {
    for (int j = 0; j < nums.size() - 1 - i; j++)
    {
      if (nums.at(j) > nums.at(j + 1))
      {
        swap(nums.at(j), nums.at(j + 1));
      }
    }
  }
}

//选择排序
static void selectionSort(vector<int>& nums)
{
  for (size_t i = 0; i < nums.size(); i++)
  {
    int min_index = i;
    for (size_t j = i + 1; j < nums.size(); j++)
    {
      if (nums.at(j) < nums.at(min_index))
      {
        min_index = j;
      }
    }
    swap(nums.at(min_index), nums.at(i));
  }
}

//插入排序
static void insertionSort(std::vector<int>& nums)
{
  for (size_t i = 1; i < nums.size(); i++)
  {
    int cur = nums.at(i);
    int position = i;
    while (nums.at(position - 1) > cur && position > 0)
    {
      nums.at(position) = nums.at(position - 1);
      position --;
    }
    nums.at(position) = cur;
  }
}

//希尔排序
//采用希尔增量方式
static void shellSort(std::vector<int>& nums)
{
  //增量gap，逐步缩小增量
  for (int gap = nums.size() / 2; gap > 0; gap /= 2)
  {
    //从gap个元素，逐个对其所在组进行直接插入排序操作
    for (int i = gap; i < nums.size(); i++)
    {
      int j = i;
      int temp = nums.at(j);
      if (nums.at(j) < nums.at(j - gap))
      {
        while (j - gap >= 0 && temp < nums.at(j - gap))
        {
          nums.at(j) = nums.at(j - gap);
          j -= gap;
        }
        nums.at(j) = temp;
      }
    }
  }
}

void test(int size, int min, int max)
{
  std::vector<std::function <void (std::vector<int>&)>>  fs;
  //冒泡排序
  fs.push_back(bubbleSort);

  //选择排序
  fs.push_back(selectionSort);

  //插入排序
  fs.push_back(insertionSort);

  //希尔排序
  fs.push_back(shellSort);

  int nums_size = 75;
  //随机数长度
  nums_size = rand() % 100;

  static std::vector<int> random_nums = generateRandomArray(nums_size, min, max);
  std::cout << "获取到随机数队列" << nums_size << "个 ：" << std::endl;
  printfNums(random_nums);

  std::vector<int> numbers = random_nums;
  fs.front()(numbers);
  std::cout << "我使用了冒泡排序， 排序结果: " << std::endl;
  printfNums(numbers);

  for (size_t i = 0; i < fs.size(); i++)
  {
    std::vector<int> nums = random_nums;
    clock_t start, finish;
    start = clock();
    //排序
    (fs.at(i))(nums);
    finish = clock();
    double totaltime = (double)(finish - start) / CLOCKS_PER_SEC * 1000.0;

    std::cout << "第" << i << "次排序";
    if (isSorted(nums))
    {
      std::cout << "成功，共耗时 :" << totaltime << " ms" << std::endl;
    }else{
      std::cout << "失败" << std::endl;
    }
  }
}


int main(int argc, char* argv[])
{
  test(50, 0, 200);
  return 0;
}
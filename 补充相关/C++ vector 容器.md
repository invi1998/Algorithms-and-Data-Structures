## C++ vector 容器

## 一、什么是vector？

向量（Vector）是一个封装了动态大小数组的顺序容器（Sequence Container）。跟任意其它类型容器一样，它能够存放各种类型的对象。可以简单的认为，向量是一个能够存放任意类型的动态数组。

------

## 二、容器特性

### 1.顺序序列

顺序容器中的元素按照严格的线性顺序排序。可以通过元素在序列中的位置访问对应的元素。

### 2.动态数组

支持对序列中的任意元素进行快速直接访问，甚至可以通过指针算述进行该操作。提供了在序列末尾相对快速地添加/删除元素的操作。

### 3.能够感知内存分配器的（Allocator-aware）

容器使用一个内存分配器对象来动态地处理它的存储需求。

------

## 三、基本函数实现

1.构造函数

- vector():创建一个空vector
- vector(int nSize):创建一个vector,元素个数为nSize
- vector(int nSize,const t& t):创建一个vector，元素个数为nSize,且值均为t
- vector(const vector&):复制构造函数
- vector(begin,end):复制[begin,end)区间内另一个数组的元素到vector中

### 2.增加函数

- void push_back(const T& x):向量尾部增加一个元素X
- iterator insert(iterator it,const T& x):向量中迭代器指向元素前增加一个元素x
- iterator insert(iterator it,int n,const T& x):向量中迭代器指向元素前增加n个相同的元素x
- iterator insert(iterator it,const_iterator first,const_iterator last):向量中迭代器指向元素前插入另一个相同类型向量的[first,last)间的数据

### 3.删除函数

- iterator erase(iterator it):删除向量中迭代器指向元素
- iterator erase(iterator first,iterator last):删除向量中[first,last)中元素
- void pop_back():删除向量中最后一个元素
- void clear():清空向量中所有元素

### 4.遍历函数

- reference at(int pos):返回pos位置元素的引用
- reference front():返回首元素的引用
- reference back():返回尾元素的引用
- iterator begin():返回向量头指针，指向第一个元素
- iterator end():返回向量尾指针，指向向量最后一个元素的下一个位置
- reverse_iterator rbegin():反向迭代器，指向最后一个元素
- reverse_iterator rend():反向迭代器，指向第一个元素之前的位置

### 5.判断函数

- bool empty() const:判断向量是否为空，若为空，则向量中无元素

### 6.大小函数

- int size() const:返回向量中元素的个数
- int capacity() const:返回当前向量所能容纳的最大元素值
- int max_size() const:返回最大可允许的vector元素数量值

### 7.其他函数

- void swap(vector&):交换两个同类型向量的数据
- void assign(int n,const T& x):设置向量中前n个元素的值为x
- void assign(const_iterator first,const_iterator last):向量中[first,last)中元素设置成当前向量元素

### 8.看着清楚

> 1.push_back 在数组的最后添加一个数据
>
> 2.pop_back 去掉数组的最后一个数据
>
> 3.at 得到编号位置的数据
>
> 4.begin 得到数组头的指针
>
> 5.end 得到数组的最后一个单元+1的指针
>
> 6．front 得到数组头的引用
>
> 7.back 得到数组的最后一个单元的引用
>
> 8.max_size 得到vector最大可以是多大
>
> 9.capacity 当前vector分配的大小
>
> 10.size 当前使用数据的大小
>
> 11.resize 改变当前使用数据的大小，如果它比当前使用的大，者填充默认值
>
> 12.reserve 改变当前vecotr所分配空间的大小
>
> 13.erase 删除指针指向的数据项
>
> 14.clear 清空当前的vector
>
> 15.rbegin 将vector反转后的开始指针返回(其实就是原来的end-1)
>
> 16.rend 将vector反转构的结束指针返回(其实就是原来的begin-1)
>
> 17.empty 判断vector是否为空
>
> 18.swap 与另一个vector交换数据

------

## 四、基本用法

```c++
#include < vector> 
using namespace std;
```

------

## 五、简单介绍

1. Vector<类型>标识符
2. Vector<类型>标识符(最大容量)
3. Vector<类型>标识符(最大容量,初始所有值)
4. Int i[5]={1,2,3,4,5}
   Vector<类型>vi(I,i+2);//得到i索引值为3以后的值
5. Vector< vector< int> >v; 二维向量//这里最外的<>要有空格。否则在比较旧的编译器下无法通过

------

## 实例

### 1.pop_back()&push_back(elem)实例在容器最后移除和插入数据

## 实例

```c++
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
 
int main()
{
    vector<int>obj;//创建一个向量存储容器 int
    for(int i=0;i<10;i++) // push_back(elem)在数组最后添加数据 
    {
        obj.push_back(i);
        cout<<obj[i]<<",";    
    }
 
    for(int i=0;i<5;i++)//去掉数组最后一个数据 
    {
        obj.pop_back();
    }
 
    cout<<"\n"<<endl;
 
    for(int i=0;i<obj.size();i++)//size()容器中实际数据个数 
    {
        cout<<obj[i]<<",";
    }
 
    return 0;
}
```



输出结果为：

```
0,1,2,3,4,5,6,7,8,9,

0,1,2,3,4,
```

### 2.clear()清除容器中所有数据

## 实例

```c++
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
 
int main()
{
    vector<int>obj;
    for(int i=0;i<10;i++)//push_back(elem)在数组最后添加数据 
    {
        obj.push_back(i);
        cout<<obj[i]<<",";
    }
 
    obj.clear();//清除容器中所以数据
    for(int i=0;i<obj.size();i++)
    {
        cout<<obj[i]<<endl;
    }
 
    return 0;
}
```



输出结果为：

```
0,1,2,3,4,5,6,7,8,9,
```

### 3.排序

## 实例

```c++
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
int main()
{
    vector<int>obj;
 
    obj.push_back(1);
    obj.push_back(3);
    obj.push_back(0);
 
    sort(obj.begin(),obj.end());//从小到大
 
    cout<<"从小到大:"<<endl;
    for(int i=0;i<obj.size();i++)
    {
        cout<<obj[i]<<",";  
    } 
 
    cout<<"\n"<<endl;
 
    cout<<"从大到小:"<<endl;
    reverse(obj.begin(),obj.end());//从大到小 
    for(int i=0;i<obj.size();i++)
    {
        cout<<obj[i]<<",";
    }
    return 0;
}
```



输出结果为：

```
从小到大:
0,1,3,

从大到小:
3,1,0,
```

1.注意 sort 需要头文件 **#include <algorithm>**

2.如果想 sort 来降序，可重写 sort

```c++
bool compare(int a,int b) 
{ 
    return a< b; //升序排列，如果改为return a>b，则为降序 
} 
int a[20]={2,4,1,23,5,76,0,43,24,65},i; 
for(i=0;i<20;i++) 
    cout<< a[i]<< endl; 
sort(a,a+20,compare);
```

### 4.访问（直接数组访问&迭代器访问）

## 实例

```c++
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
int main()
{
    //顺序访问
    vector<int>obj;
    for(int i=0;i<10;i++)
    {
        obj.push_back(i);   
    } 
 
    cout<<"直接利用数组："; 
    for(int i=0;i<10;i++)//方法一 
    {
        cout<<obj[i]<<" ";
    }
 
    cout<<endl; 
    cout<<"利用迭代器：" ;
    //方法二，使用迭代器将容器中数据输出 
    vector<int>::iterator it;//声明一个迭代器，来访问vector容器，作用：遍历或者指向vector容器的元素 
    for(it=obj.begin();it!=obj.end();it++)
    {
        cout<<*it<<" ";
    }
    return 0;
}
```



输出结果为：

```
直接利用数组：0 1 2 3 4 5 6 7 8 9 
利用迭代器：0 1 2 3 4 5 6 7 8 9
```

### 5.二维数组两种定义方法（结果一样）

## 方法一

```c++
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
 
int main()
{
    int N=5, M=6; 
    vector<vector<int> > obj(N); //定义二维动态数组大小5行 
    for(int i =0; i< obj.size(); i++)//动态二维数组为5行6列，值全为0 
    { 
        obj[i].resize(M); 
    } 
 
    for(int i=0; i< obj.size(); i++)//输出二维动态数组 
    {
        for(int j=0;j<obj[i].size();j++)
        {
            cout<<obj[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
```



## 方法二

```c++
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
 
int main()
{
    int N=5, M=6; 
    vector<vector<int> > obj(N, vector<int>(M)); //定义二维动态数组5行6列 
 
    for(int i=0; i< obj.size(); i++)//输出二维动态数组 
    {
        for(int j=0;j<obj[i].size();j++)
        {
            cout<<obj[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
```



输出结果为：

```
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
0 0 0 0 0 0 
```





# 数组去重

在 C++ 中，有多种方法可以实现数组去重，选择哪种方法取决于你的需求（是否要保持顺序、是否需要原地操作等）。以下是各种方法的详细说明：

## 一、使用 `std::unique` + `std::sort`（适合可排序类型）

### 1. **排序后去重（不保持原顺序）**
```cpp
#include <algorithm>
#include <vector>

std::vector<int> removeDuplicates(std::vector<int>& nums) {
    // 1. 先排序
    std::sort(nums.begin(), nums.end());
    
    // 2. 使用 unique 将重复元素移到末尾，返回去重后的新结尾
    auto new_end = std::unique(nums.begin(), nums.end());
    
    // 3. 删除重复元素
    nums.erase(new_end, nums.end());
    
    return nums;
}
```

### 2. **如果数组已排序**
```cpp
std::vector<int> removeDuplicatesFromSorted(std::vector<int>& nums) {
    // 数组已排序的情况下，直接去重
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    return nums;
}
```

## 二、使用哈希集合（保持原顺序）

### 1. **使用 `std::unordered_set`（不保持顺序）**
```cpp
#include <unordered_set>
#include <vector>

std::vector<int> removeDuplicatesUnordered(std::vector<int>& nums) {
    std::unordered_set<int> seen;
    std::vector<int> result;
    result.reserve(nums.size());
    
    for (int num : nums) {
        if (seen.insert(num).second) {  // insert 返回 pair<iterator, bool>
            result.push_back(num);
        }
    }
    
    return result;
}
```

### 2. **使用 `std::set`（保持插入顺序的近似）**
```cpp
#include <set>
#include <vector>

std::vector<int> removeDuplicatesOrdered(std::vector<int>& nums) {
    std::set<int> seen;
    std::vector<int> result;
    result.reserve(nums.size());
    
    for (int num : nums) {
        if (seen.insert(num).second) {
            result.push_back(num);
        }
    }
    
    return result;
}
```

### 3. **使用哈希集合 + 双指针（原地修改）**
```cpp
#include <unordered_set>
#include <vector>

std::vector<int> removeDuplicatesInPlace(std::vector<int>& nums) {
    std::unordered_set<int> seen;
    int write_index = 0;
    
    for (int read_index = 0; read_index < nums.size(); ++read_index) {
        if (seen.insert(nums[read_index]).second) {
            nums[write_index++] = nums[read_index];
        }
    }
    
    nums.resize(write_index);
    return nums;
}
```

## 三、针对特定场景的优化方法

### 1. **元素范围有限（如 0-1000）**
```cpp
#include <vector>
#include <bitset>

std::vector<int> removeDuplicatesLimitedRange(const std::vector<int>& nums, int max_value = 1000) {
    std::bitset<1001> seen;  // 假设最大值为1000
    std::vector<int> result;
    result.reserve(nums.size());
    
    for (int num : nums) {
        if (num >= 0 && num <= max_value && !seen.test(num)) {
            seen.set(num);
            result.push_back(num);
        }
    }
    
    return result;
}
```

### 2. **使用布尔数组代替哈希集合（更快）**
```cpp
#include <vector>

std::vector<int> removeDuplicatesBoolArray(const std::vector<int>& nums, int max_value) {
    std::vector<bool> seen(max_value + 1, false);
    std::vector<int> result;
    result.reserve(nums.size());
    
    for (int num : nums) {
        if (num >= 0 && num <= max_value && !seen[num]) {
            seen[num] = true;
            result.push_back(num);
        }
    }
    
    return result;
}
```

## 四、通用模板函数

### 1. **模板函数（支持任何容器）**
```cpp
#include <algorithm>
#include <unordered_set>
#include <vector>

template<typename T>
std::vector<T> removeDuplicates(const std::vector<T>& vec, bool keep_order = true) {
    if (!keep_order) {
        // 排序去重法
        std::vector<T> result = vec;
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    } else {
        // 哈希集合法（保持顺序）
        std::unordered_set<T> seen;
        std::vector<T> result;
        result.reserve(vec.size());
        
        for (const T& elem : vec) {
            if (seen.insert(elem).second) {
                result.push_back(elem);
            }
        }
        
        return result;
    }
}

// 使用示例
std::vector<int> vec = {3, 1, 2, 3, 4, 2, 1};
auto result1 = removeDuplicates(vec, true);    // 保持顺序：3, 1, 2, 4
auto result2 = removeDuplicates(vec, false);   // 排序去重：1, 2, 3, 4
```

### 2. **原地去重模板**
```cpp
template<typename T>
void removeDuplicatesInPlace(std::vector<T>& vec, bool keep_order = true) {
    if (!keep_order) {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    } else {
        std::unordered_set<T> seen;
        size_t write_index = 0;
        
        for (size_t read_index = 0; read_index < vec.size(); ++read_index) {
            if (seen.insert(vec[read_index]).second) {
                vec[write_index++] = vec[read_index];
            }
        }
        
        vec.resize(write_index);
    }
}
```

## 五、C++20 的简化写法

### 使用 `std::ranges`（C++20）
```cpp
#include <algorithm>
#include <ranges>
#include <vector>

std::vector<int> removeDuplicatesRanges(std::vector<int>& nums) {
    // 排序去重
    std::ranges::sort(nums);
    auto [new_end, _] = std::ranges::unique(nums);
    nums.erase(new_end, nums.end());
    return nums;
}
```

## 六、性能对比和选择建议

| 方法              | 时间复杂度 | 空间复杂度     | 是否保持顺序 | 适用场景                   |
| ----------------- | ---------- | -------------- | ------------ | -------------------------- |
| **排序+unique**   | O(n log n) | O(1) 原地      | 否           | 不需要保持顺序，可排序类型 |
| **unordered_set** | O(n)       | O(n)           | 是           | 需要保持顺序，任意类型     |
| **set**           | O(n log n) | O(n)           | 是           | 需要保持顺序且自动排序     |
| **布尔数组**      | O(n)       | O(max_value)   | 是           | 整数且范围有限             |
| **bitset**        | O(n)       | O(max_value/8) | 是           | 整数且范围有限，内存敏感   |

## 七、实际应用示例

### 示例1：快速去重（不关心顺序）
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    // 方法1：排序去重（最快，不保持顺序）
    std::sort(nums.begin(), nums.end());
    auto last = std::unique(nums.begin(), nums.end());
    nums.erase(last, nums.end());
    
    for (int n : nums) std::cout << n << " ";  // 1 2 3 4 5 6 9
    std::cout << std::endl;
    
    return 0;
}
```

### 示例2：保持顺序去重
```cpp
#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    // 方法2：哈希集合（保持顺序）
    std::unordered_set<int> seen;
    std::vector<int> result;
    
    for (int num : nums) {
        if (seen.find(num) == seen.end()) {
            seen.insert(num);
            result.push_back(num);
        }
    }
    
    for (int n : result) std::cout << n << " ";  // 3 1 4 5 9 2 6
    std::cout << std::endl;
    
    return 0;
}
```

### 示例3：C++17 结构化绑定简化
```cpp
#include <iostream>
#include <vector>
#include <unordered_set>

int main() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::unordered_set<int> seen;
    std::vector<int> result;
    
    for (int num : nums) {
        auto [_, inserted] = seen.insert(num);  // C++17
        if (inserted) {
            result.push_back(num);
        }
    }
    
    for (int n : result) std::cout << n << " ";
    std::cout << std::endl;
    
    return 0;
}
```

## 八、推荐的最佳实践

### 1. **如果需要保持原顺序**
```cpp
std::vector<int> removeDuplicatesKeepOrder(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    std::vector<int> result;
    result.reserve(nums.size());  // 预分配空间，提高性能
    
    for (int num : nums) {
        if (seen.insert(num).second) {
            result.push_back(num);
        }
    }
    
    return result;
}
```

### 2. **如果不需要保持顺序（追求性能）**
```cpp
std::vector<int> removeDuplicatesFast(std::vector<int>& nums) {
    // 原地去重，不保持顺序
    std::sort(nums.begin(), nums.end());
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    return nums;
}
```

### 3. **如果数组已排序**
```cpp
std::vector<int> removeDuplicatesFromSorted(std::vector<int>& nums) {
    // 假设 nums 已排序
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    return nums;
}
```

## 九、注意事项

1. **`std::unique` 只移除连续的重复元素**，所以必须先排序
2. **哈希集合方法会保持元素插入的顺序**
3. **如果元素类型没有定义哈希函数**，需要自定义哈希函数或使用 `std::set`
4. **对于自定义类型**，需要重载 `<` 运算符（用于排序）或 `==` 运算符（用于 `std::unique`）

### 自定义类型的去重示例：
```cpp
struct Point {
    int x, y;
    
    // 用于 unordered_set 需要定义相等和哈希
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 自定义哈希函数
struct PointHash {
    size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// 使用 unordered_set 去重自定义类型
std::vector<Point> removeDuplicates(const std::vector<Point>& points) {
    std::unordered_set<Point, PointHash> seen;
    std::vector<Point> result;
    
    for (const auto& p : points) {
        if (seen.insert(p).second) {
            result.push_back(p);
        }
    }
    
    return result;
}
```

根据你的具体需求选择合适的去重方法。一般来说：
- 如果需要保持顺序，用哈希集合
- 如果不需要保持顺序且可排序，用排序+unique
- 如果元素范围有限，用布尔数组或bitset
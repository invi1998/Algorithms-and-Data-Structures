# std::priority_queue

`std::priority_queue`（优先队列）是C++标准库中的一个**容器适配器**，它能保证你每次取出的元素都是当前队列中“优先级最高”的一个。其底层通常基于**堆（Heap）**数据结构实现，因此插入和删除操作非常高效。

### 📋 模板声明与核心概念
其标准模板声明如下：
```cpp
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```
*   **`T`**：队列中存储的元素类型。
*   **`Container`**：用于存储元素的底层容器类型，必须是支持`front()`、`push_back()`、`pop_back()`等操作的序列容器，如`std::vector`（默认）或`std::deque`。
*   **`Compare`**：用于定义优先级的比较函数对象类型。它决定了队列中元素的“顺序”。
    *   `Compare(a, b)` 返回 `true` 时，意味着 `a` 的优先级 **低于** `b`。
    *   **默认使用 `std::less<T>`**，这会形成一个**最大堆（大顶堆）**，即**值最大的元素被视为优先级最高**，位于队首。
    *   ️ 若需**最小堆（小顶堆）**，应指定 `std::greater<T>` 为比较器，此时值最小的元素优先级最高。

### 🏗️ 构造函数
`priority_queue` 提供了以下几种构造方式：
*   `priority_queue()`：默认构造函数，创建一个空的优先队列。
*   `explicit priority_queue(const Compare& compare)`：使用给定的比较器创建空队列。
*   `priority_queue(const Compare& compare, const Container& cont)`：使用给定比较器，并以容器 `cont` 的副本作为初始元素（需要手动建堆）。
*   `template< class InputIt > priority_queue(InputIt first, InputIt last, const Compare& compare = Compare())`：用迭代器范围 `[first, last)` 内的元素构造队列，并自动建堆。

### ⚙️ 成员函数概览

| 类别         | 函数名                                                   | 功能说明                                                     | 时间复杂度 |
| :----------- | :------------------------------------------------------- | :----------------------------------------------------------- | :--------- |
| **元素访问** | `const_reference top() const`                            | **返回队首（优先级最高）元素的常量引用**。队列空时行为未定义。 | O(1)       |
| **容量**     | `bool empty() const`                                     | 检查底层容器是否为空。                                       | O(1)       |
|              | `size_type size() const`                                 | 返回元素数量。                                               | O(1)       |
| **修改器**   | `void push(const T& value)`                              | 插入元素，并调整堆结构。                                     | O(log n)   |
|              | `void pop()`                                             | **移除队首元素**，并调整堆结构。                             | O(log n)   |
|              | `template< class... Args > void emplace(Args&&... args)` | 原位构造元素，效率通常优于 `push`。                          | O(log n)   |
|              | `void swap(priority_queue& other) noexcept`              | 交换两个优先队列的内容。                                     | O(1)       |

### 💡 重要特性与注意事项
1.  **访问限制**：你**只能访问队首 (`top()`)** 元素，不能随机访问或遍历其他元素。
2.  **迭代器**：`priority_queue` **不提供迭代器**。
3.  **自定义类型**：如果队列元素是自定义类型（如结构体），你必须提供比较方式。有两种方法：
    *   **重载 `<` 运算符**：为该类型定义 `operator<`，这样默认的 `std::less` 就能工作。
    *   **提供自定义比较器**：一个重载了 `operator()` 的结构体或函数对象。
4.  **底层容器**：底层容器作为**受保护成员 `c`** 存储，在需要时可以继承此类来访问（但通常不建议这么做）。

### 📝 基础用法示例

#### 1. 基础类型与最大/最小堆
```cpp
#include <iostream>
#include <queue>
#include <functional> // 需要引入 std::greater
int main() {
    // 默认最大堆
    std::priority_queue<int> max_pq;
    max_pq.push(3); max_pq.push(1); max_pq.push(4);
    std::cout << max_pq.top(); // 输出 4

    // 显式定义的最小堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    min_pq.push(3); min_pq.push(1); min_pq.push(4);
    std::cout << min_pq.top(); // 输出 1

    return 0;
}
```

#### 2. 使用 `std::pair`
`pair` 的比较规则是：先比较 `first`，若相等再比较 `second`。
```cpp
std::priority_queue<std::pair<int, int>> pq;
pq.push({1, 2}); pq.push({2, 5}); pq.push({1, 3});
// 出队顺序: {2,5} -> {1,3} -> {1,2}
```

#### 3. 使用自定义类型与比较器
假设任务 `Task` 的 `priority` 值越小越紧急。
```cpp
#include <queue>
#include <string>
struct Task {
    std::string name;
    int priority;
    Task(std::string n, int p) : name(n), priority(p) {}
};
// 方法1：重载 operator<
bool operator<(const Task& a, const Task& b) {
    // 注意：默认最大堆，要让“更紧急”（值小）的优先级“更高”，需要反向比较
    return a.priority > b.priority; 
}
// 方法2：自定义比较器仿函数
struct CompareTask {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority > b.priority; // 同样，构建最小堆
    }
};
int main() {
    // 使用方法1
    std::priority_queue<Task> pq1;
    pq1.push({"TaskA", 5}); pq1.push({"TaskB", 1}); // TaskB 会先出队

    // 使用方法2
    std::priority_queue<Task, std::vector<Task>, CompareTask> pq2;
    // ... 操作同上

    return 0;
}
```

总结来说，`std::priority_queue` 是一个功能强大且高效的“取极值”工具。理解其基于堆的实现原理、掌握比较器的定义方法（尤其是对自定义类型），是正确使用的关键。



## [373. 查找和最小的 K 对数字](https://leetcode.cn/problems/find-k-pairs-with-smallest-sums/)

给定两个以 **非递减顺序排列** 的整数数组 `nums1` 和 `nums2` , 以及一个整数 `k` 。

定义一对值 `(u,v)`，其中第一个元素来自 `nums1`，第二个元素来自 `nums2` 。

请找到和最小的 `k` 个数对 `(u1,v1)`, ` (u2,v2)` ...  `(uk,vk)` 。

 

**示例 1:**

```
输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [[1,2],[1,4],[1,6]]
解释: 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
```

**示例 2:**

```
输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [[1,1],[1,1]]
解释: 返回序列中的前 2 对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
```

 

**提示:**

- `1 <= nums1.length, nums2.length <= 105`
- `-109 <= nums1[i], nums2[i] <= 109`
- `nums1` 和 `nums2` 均为 **升序排列**
- `1 <= k <= 104`
- `k <= nums1.length * nums2.length`

```c++
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;
        // 添加容量预分配，避免频繁重新分配
        result.reserve(k);
        int idx1 = 0;
        int idx2 = 0;
        int n1 = nums1.size();
        int n2 = nums2.size();

        // 定义比较器仿函数
        auto ComparePair = [&nums1, &nums2](const pair<int, int>& p1, const pair<int, int>& p2)
        {
            // 最小堆比较器
            return nums1[p1.first] + nums2[p1.second] > nums1[p2.first] + nums2[p2.second];
        };

        priority_queue<pair<int, int>, std::vector<pair<int, int>>, decltype(ComparePair)> pq(ComparePair);

        // 注意：这里先只推入nums1和num2里第一个元素的组合
        for (int i = 0; i < min(k, n1); i++)
        {
            pq.push({i, 0});
        }

        while(k-- > 0 && !pq.empty())
        {
            // 然后在实际进行比较的时候，再更新num2的组合
            auto [i1, i2] = pq.top();
            pq.pop();
            result.emplace_back(initializer_list<int>{nums1[i1], nums2[i2]});
            // 如果不想使用初始化列表构造，也可以直接显式构造
            // result.emplace_back(vector<int>{nums1[i1], nums2[i2]});
            if (i2 + 1 < n2)
            {
                // 然后每次在得到一个最小数对后，继续推入一个num2的组合
                // 这里不需要将此前推入的num1的组合的最小和值拿出来和当前的num2的组合和值进行比较
                // 因为我们最小堆里推入的第一个最小值是[0, 0]索引，它必然是最小的，所以后续只需要不断地往优先队列里推入nums2的组合，他会自行更新
                pq.push({i1, i2 + 1});
            }
        }

        return result;
    }
};
```



使用**多路归并**的思路来找到和最小的k对数字：

```cpp
priority_queue<pair<int, int>, std::vector<pair<int, int>>, decltype(ComparePair)> pq(ComparePair);
```

## 代码分析

算法核心思想是：
1. 首先推入所有 `(nums1[i], nums2[0])` 组合
2. 每次弹出最小和组合后，推入 `(nums1[i], nums2[j+1])`
3. 利用最小堆维护当前最小和组合

## 详细讲解 `priority_queue` 声明中的知识点

### 1. **`decltype` 关键字**
`decltype` 用于推导表达式的类型，在编译时确定类型。

**示例：**
```cpp
auto ComparePair = [](const pair<int, int>& p1, const pair<int, int>& p2) { /* ... */ };
// decltype(ComparePair) 推导出 lambda 表达式的类型
```

**更多示例：**

```cpp
int x = 5;
decltype(x) y = 10;  // y 的类型为 int

vector<int> vec;
decltype(vec)::value_type z = 20;  // z 的类型为 int

auto func = [](int a) { return a * 2; };
decltype(func) copy_func = func;  // copy_func 与 func 类型相同
```

### 2. **比较器的多种实现方法**

#### **方法1：Lambda 表达式（你的代码使用的方法）**
```cpp
auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
    return a.first + a.second > b.first + b.second;
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
```

**特点：**
- 可以捕获外部变量（如你的代码捕获了 `nums1`, `nums2`）
- 简洁直观
- 类型需要通过 `decltype` 获取

#### **方法2：函数对象（仿函数 Functor）**
```cpp
struct ComparePair {
    const vector<int>& nums1;
    const vector<int>& nums2;
    
    ComparePair(const vector<int>& n1, const vector<int>& n2) 
        : nums1(n1), nums2(n2) {}
    
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const {
        return nums1[p1.first] + nums2[p1.second] > 
               nums1[p2.first] + nums2[p2.second];
    }
};

// 使用时
priority_queue<pair<int, int>, vector<pair<int, int>>, ComparePair> 
    pq(ComparePair(nums1, nums2));
```

**特点：**
- 可以存储状态（通过成员变量）
- 明确的类型，不需要 `decltype`
- 可以通过构造函数传递参数

#### **方法3：普通函数指针**
```cpp
bool comparePairs(const pair<int, int>& p1, const pair<int, int>& p2) {
    return p1.first + p1.second > p2.first + p2.second;
}

// 使用时
priority_queue<pair<int, int>, vector<pair<int, int>>, 
               bool(*)(const pair<int, int>&, const pair<int, int>&)> 
    pq(comparePairs);
```

**特点：**
- 简单函数可以使用
- 不能捕获外部变量
- 类型声明较冗长

#### **方法4：`std::function`**
```cpp
function<bool(const pair<int, int>&, const pair<int, int>&)> cmp = 
    [&nums1, &nums2](const pair<int, int>& p1, const pair<int, int>& p2) {
        return nums1[p1.first] + nums2[p1.second] > 
               nums1[p2.first] + nums2[p2.second];
    };

priority_queue<pair<int, int>, vector<pair<int, int>>, 
               function<bool(const pair<int, int>&, const pair<int, int>&)>> 
    pq(cmp);
```

**特点：**
- 通用性强，可以接受任何可调用对象
- 有运行时开销
- 类型清晰但冗长

### 3. **`priority_queue` 模板参数说明**
```cpp
template<
    class T,                        // 元素类型
    class Container = vector<T>,    // 底层容器
    class Compare = less<T>         // 比较器类型
> class priority_queue;
```

在你的代码中：
- `T = pair<int, int>`：存储索引对
- `Container = vector<pair<int, int>>`：使用 vector 作为底层容器
- `Compare = decltype(ComparePair)`：自定义比较器类型

### 4. **为什么需要传递 `ComparePair` 给构造函数**

Lambda 表达式在 C++ 中默认是**不可默认构造和不可赋值的**（除非不捕获任何变量）。当你使用捕获列表时，lambda 需要初始化数据成员来存储捕获的变量，因此需要显式传递一个实例给构造函数。

```cpp
// 错误：如果 ComparePair 捕获了变量，不能默认构造
// priority_queue<..., decltype(ComparePair)> pq;

// 正确：传递 ComparePair 的实例
priority_queue<..., decltype(ComparePair)> pq(ComparePair);
```

### 5. **可调用对象（Callable Objects）总结**

| 类型            | 语法                          | 特点               | 适用场景               |
| --------------- | ----------------------------- | ------------------ | ---------------------- |
| 函数指针        | `bool(*)(const T&, const T&)` | 简单，不能有状态   | 简单比较               |
| 函数对象        | 重载 `operator()` 的类        | 可以有状态，性能好 | 需要状态的复杂比较     |
| Lambda 表达式   | `[](params){...}`             | 简洁，可捕获变量   | 临时使用，需要闭包     |
| `std::function` | `function<bool(T,T)>`         | 类型擦除，通用     | 需要存储不同可调用对象 |

## 算法优化建议

你的算法已经是优化过的版本（时间复杂度 O(k log min(n, k))）。不过可以考虑以下改进：

```cpp
// 添加容量预分配，避免频繁重新分配
result.reserve(k);

// 在 while 循环中直接构造 vector，避免 initializer_list
while (k-- > 0 && !pq.empty()) {
    auto [i1, i2] = pq.top();
    pq.pop();
    result.push_back({nums1[i1], nums2[i2]});  // 直接使用 {} 构造
    // 或者：result.emplace_back(vector<int>{nums1[i1], nums2[i2]});
    
    if (i2 + 1 < n2) {
        pq.push({i1, i2 + 1});
    }
}
```




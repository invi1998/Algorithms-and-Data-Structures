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

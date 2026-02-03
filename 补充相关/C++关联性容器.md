# C++关联容器总结表格

## 1. 容器概览与基本特性对比

| 特性         | std::set | std::multiset | std::map | std::multimap | std::unordered_set | std::unordered_multiset | std::unordered_map | std::unordered_multimap |
| ------------ | -------- | ------------- | -------- | ------------- | ------------------ | ----------------------- | ------------------ | ----------------------- |
| **头文件**   | `<set>`  | `<set>`       | `<map>`  | `<map>`       | `<unordered_set>`  | `<unordered_set>`       | `<unordered_map>`  | `<unordered_map>`       |
| **是否有序** | 是       | 是            | 是       | 是            | 否                 | 否                      | 否                 | 否                      |
| **键唯一性** | 唯一     | 可重复        | 唯一     | 可重复        | 唯一               | 可重复                  | 唯一               | 可重复                  |
| **底层实现** | 红黑树   | 红黑树        | 红黑树   | 红黑树        | 哈希表             | 哈希表                  | 哈希表             | 哈希表                  |
| **C++版本**  | C++98    | C++98         | C++98    | C++98         | C++11              | C++11                   | C++11              | C++11                   |
| **内存布局** | 紧凑     | 紧凑          | 紧凑     | 紧凑          | 稀疏（桶）         | 稀疏（桶）              | 稀疏（桶）         | 稀疏（桶）              |

## 2. 时间复杂度对比

| 操作         | 有序容器 (set/map)     | 无序容器 (unordered_set/map) | 说明                         |
| ------------ | ---------------------- | ---------------------------- | ---------------------------- |
| **查找**     | O(log n)               | 平均O(1)，最坏O(n)           | 无序容器性能依赖哈希函数质量 |
| **插入**     | O(log n)               | 平均O(1)，最坏O(n)           | 无序容器插入可能触发rehash   |
| **删除**     | O(log n)               | 平均O(1)，最坏O(n)           |                              |
| **遍历**     | O(n)（有序）           | O(n)（无序）                 | 有序容器按排序顺序遍历       |
| **修改键**   | 不支持（需删除再插入） | 不支持（需删除再插入）       | 键不可修改                   |
| **范围查询** | O(log n + k)           | 不支持                       | k为范围内元素数量            |

## 3. 常用成员函数对比

| 函数类别         | 函数名                | 适用容器  | 功能描述              | 返回值/复杂度               |
| ---------------- | --------------------- | --------- | --------------------- | --------------------------- |
| **容量**         | `size()`              | 所有      | 返回元素数量          | O(1)                        |
|                  | `empty()`             | 所有      | 检查是否为空          | O(1)                        |
|                  | `max_size()`          | 所有      | 返回可能的最大元素数  | O(1)                        |
| **修改器**       | `insert(value)`       | 所有      | 插入元素              | O(log n) 或平均O(1)         |
|                  | `emplace(args...)`    | 所有      | 原地构造插入          | O(log n) 或平均O(1)         |
|                  | `erase(key/iterator)` | 所有      | 删除元素              | O(log n) 或平均O(1)         |
|                  | `clear()`             | 所有      | 清空所有元素          | O(n)                        |
|                  | `swap(other)`         | 所有      | 交换内容              | O(1)                        |
| **查找**         | `find(key)`           | 所有      | 查找特定键            | O(log n) 或平均O(1)         |
|                  | `count(key)`          | 所有      | 统计键的出现次数      | O(log n + count) 或平均O(1) |
|                  | `equal_range(key)`    | 所有      | 返回匹配键的范围      | O(log n) 或平均O(1)         |
|                  | `contains(key)`       | C++20+    | 检查是否包含键        | O(log n) 或平均O(1)         |
| **有序容器特有** | `lower_bound(key)`    | set/map   | 返回第一个≥key的元素  | O(log n)                    |
|                  | `upper_bound(key)`    | set/map   | 返回第一个>key的元素  | O(log n)                    |
|                  | `begin()/end()`       | 所有      | 返回迭代器            | O(1)                        |
| **无序容器特有** | `bucket_count()`      | unordered | 返回桶的数量          | O(1)                        |
|                  | `load_factor()`       | unordered | 返回负载因子          | O(1)                        |
|                  | `max_load_factor()`   | unordered | 返回/设置最大负载因子 | O(1)                        |
|                  | `rehash(n)`           | unordered | 设置桶数为至少n       | O(n)                        |
|                  | `reserve(n)`          | unordered | 为至少n个元素预留空间 | O(n)                        |

## 4. 迭代器特性对比

| 特性            | 有序容器                         | 无序容器                    |
| --------------- | -------------------------------- | --------------------------- |
| **迭代器类型**  | 双向迭代器                       | 前向迭代器（C++11起为双向） |
| **迭代顺序**    | 按键排序顺序                     | 无特定顺序（依赖哈希函数）  |
| **迭代器失效**  | 插入不失效，删除只使被删元素失效 | rehash使所有迭代器失效      |
| **范围for支持** | 是                               | 是                          |
| **反向迭代器**  | 支持                             | C++14起支持                 |

## 5. 自定义类型作为键的要求

| 容器类型     | 需要定义            | 默认使用                                | 自定义示例                     |
| ------------ | ------------------- | --------------------------------------- | ------------------------------ |
| **有序容器** | 比较函数            | `std::less<Key>`                        | `operator<` 或自定义比较类     |
| **无序容器** | 哈希函数 + 相等比较 | `std::hash<Key>` + `std::equal_to<Key>` | 特化`std::hash` + `operator==` |

## 6. 内存与性能特性

| 特性             | 有序容器              | 无序容器           |
| ---------------- | --------------------- | ------------------ |
| **内存开销**     | 较低（每个节点3指针） | 较高（哈希表+桶）  |
| **缓存友好性**   | 较好（连续内存较少）  | 较差（指针跳转多） |
| **最坏情况性能** | 稳定O(log n)          | 可能退化为O(n)     |
| **预分配能力**   | 无                    | 支持(`reserve()`)  |
| **哈希函数依赖** | 不依赖                | 高度依赖哈希质量   |

## 7. 应用场景选择指南

| 场景需求         | 推荐容器                                                     | 理由                            |
| ---------------- | ------------------------------------------------------------ | ------------------------------- |
| 需要有序遍历     | `std::set` / `std::map`                                      | 保持元素排序                    |
| 需要最高查询性能 | `std::unordered_set` / `std::unordered_map`                  | 平均O(1)查找                    |
| 需要范围查询     | `std::set` / `std::map`                                      | 支持`lower_bound`/`upper_bound` |
| 内存受限         | `std::set` / `std::map`                                      | 内存开销更小                    |
| 需要插入顺序保持 | `std::map`（或自定义哈希保持顺序）                           | 有序容器保持排序                |
| 键类型无良好哈希 | `std::set` / `std::map`                                      | 不依赖哈希函数                  |
| 需要键重复       | `multiset` / `multimap` / `unordered_multiset` / `unordered_multimap` | 允许重复键                      |
| 频繁插入删除     | 根据是否有序选择                                             | 有序O(log n)，无序平均O(1)      |

## 8. 线程安全与异常安全

| 安全类型       | 有序容器       | 无序容器       |
| -------------- | -------------- | -------------- |
| **基本保证**   | 是             | 是             |
| **强异常保证** | 插入单元素提供 | 插入单元素提供 |
| **线程安全**   | 否，需外部同步 | 否，需外部同步 |
| **迭代器安全** | 并发修改不安全 | 并发修改不安全 |

## 9. 特殊函数与C++新特性

| C++版本 | 新增特性                                      | 影响容器              |
| ------- | --------------------------------------------- | --------------------- |
| C++11   | 无序容器、移动语义、`emplace`                 | 所有容器              |
| C++14   | 无序容器的异构查找                            | 无序容器              |
| C++17   | 结构化绑定、`try_emplace`、`insert_or_assign` | `map`/`unordered_map` |
| C++20   | `contains()`、范围适配器                      | 所有容器              |

## 10. 示例代码速查

```cpp
// 快速初始化
std::set<int> s = {1, 2, 3, 4, 5};
std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
std::unordered_set<int> us = {1, 2, 3};

// 常用操作
auto it = m.find("key");      // 查找
m["new"] = 10;                // 插入或访问
m.insert({"key", 100});       // 插入
m.erase("key");               // 删除

// C++17结构化绑定
for (const auto& [key, value] : m) {
    // 使用key和value
}

// C++20 contains
if (m.contains("key")) {
    // 键存在
}
```

这个表格总结涵盖了C++关联容器的核心知识点，可以作为快速参考使用。在实际开发中，应根据具体需求选择合适的容器类型。



# C++关联容器详细介绍

## 1. 关联容器概览

C++中的关联容器提供了基于关键字的快速查找能力，主要分为**有序容器**和**无序容器**两大类。

### 有序容器（基于红黑树）
- `std::set`：唯一键集合
- `std::multiset`：键集合，允许重复键
- `std::map`：键值对映射，唯一键
- `std::multimap`：键值对映射，允许重复键

### 无序容器（基于哈希表，C++11引入）
- `std::unordered_set`：哈希集合，唯一键
- `std::unordered_multiset`：哈希集合，允许重复键
- `std::unordered_map`：哈希映射，唯一键
- `std::unordered_multimap`：哈希映射，允许重复键

## 2. 底层实现原理

### 2.1 有序容器底层：红黑树
```cpp
// 红黑树特性：
// 1. 每个节点非红即黑
// 2. 根节点是黑色
// 3. 红色节点的子节点必须是黑色
// 4. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点
// 时间复杂度：查找、插入、删除均为 O(log n)
```

### 2.2 无序容器底层：哈希表
```cpp
// 哈希表特性：
// 1. 使用哈希函数将键映射到桶
// 2. 使用链表或开放地址法解决冲突
// 3. 平均时间复杂度：O(1)，最坏情况：O(n)
// 4. 需要提供哈希函数和相等比较函数
```

## 3. 有序容器详解

### 3.1 std::set
```cpp
#include <iostream>
#include <set>

void setExample() {
    // 初始化
    std::set<int> s1 = {5, 2, 8, 1, 4};
    
    // 插入元素
    s1.insert(3);
    s1.insert(5);  // 重复，不会插入
    
    // 遍历（自动排序）
    for (const auto& val : s1) {
        std::cout << val << " ";  // 输出：1 2 3 4 5 8
    }
    std::cout << std::endl;
    
    // 查找
    auto it = s1.find(3);
    if (it != s1.end()) {
        std::cout << "Found: " << *it << std::endl;
    }
    
    // 删除
    s1.erase(4);
    s1.erase(s1.find(2));
    
    // 大小和容量
    std::cout << "Size: " << s1.size() << std::endl;
    std::cout << "Empty: " << std::boolalpha << s1.empty() << std::endl;
    
    // 边界查找
    auto lb = s1.lower_bound(3);  // >= 3的第一个元素
    auto ub = s1.upper_bound(5);  // > 5的第一个元素
}
```

### 3.2 std::multiset
```cpp
void multisetExample() {
    std::multiset<int> ms = {1, 2, 2, 3, 3, 3, 4};
    
    // 允许重复插入
    ms.insert(2);
    
    // 统计元素数量
    std::cout << "Count of 3: " << ms.count(3) << std::endl;
    
    // 查找所有等于某个值的元素
    auto range = ms.equal_range(3);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

### 3.3 std::map
```cpp
#include <map>
#include <string>

void mapExample() {
    // 初始化
    std::map<std::string, int> m1 = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    
    // 插入元素
    m1.insert({"David", 40});
    m1.emplace("Eve", 45);  // 原地构造
    m1["Frank"] = 50;  // 使用operator[]
    
    // 访问元素
    std::cout << "Alice's age: " << m1["Alice"] << std::endl;
    
    // 安全的访问方式
    auto it = m1.find("Bob");
    if (it != m1.end()) {
        std::cout << "Bob's age: " << it->second << std::endl;
    }
    
    // 使用at()（越界会抛出异常）
    try {
        std::cout << m1.at("Unknown") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Key not found" << std::endl;
    }
    
    // 遍历
    for (const auto& [key, value] : m1) {  // C++17结构化绑定
        std::cout << key << ": " << value << std::endl;
    }
    
    // 修改比较函数
    struct CaseInsensitiveCompare {
        bool operator()(const std::string& a, const std::string& b) const {
            return std::lexicographical_compare(
                a.begin(), a.end(), b.begin(), b.end(),
                [](char c1, char c2) {
                    return std::tolower(c1) < std::tolower(c2);
                });
        }
    };
    
    std::map<std::string, int, CaseInsensitiveCompare> caseInsensitiveMap;
}
```

### 3.4 std::multimap
```cpp
void multimapExample() {
    std::multimap<std::string, int> mm = {
        {"Alice", 25},
        {"Alice", 26},
        {"Bob", 30},
        {"Alice", 27}
    };
    
    // 插入重复键
    mm.insert({"Bob", 31});
    
    // 查找特定键的所有值
    auto range = mm.equal_range("Alice");
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}
```

## 4. 无序容器详解

### 4.1 std::unordered_set
```cpp
#include <unordered_set>
#include <functional>

void unorderedSetExample() {
    std::unordered_set<int> us = {1, 2, 3, 4, 5};
    
    // 插入
    us.insert(6);
    
    // 查找
    if (us.find(3) != us.end()) {
        std::cout << "3 found" << std::endl;
    }
    
    // 桶操作
    std::cout << "Bucket count: " << us.bucket_count() << std::endl;
    std::cout << "Load factor: " << us.load_factor() << std::endl;
    
    // 自定义哈希和相等比较
    struct Person {
        std::string name;
        int age;
        
        bool operator==(const Person& other) const {
            return name == other.name && age == other.age;
        }
    };
    
    struct PersonHash {
        std::size_t operator()(const Person& p) const {
            return std::hash<std::string>()(p.name) ^ 
                   std::hash<int>()(p.age);
        }
    };
    
    std::unordered_set<Person, PersonHash> personSet;
}
```

### 4.2 std::unordered_multiset
```cpp
void unorderedMultisetExample() {
    std::unordered_multiset<int> ums = {1, 2, 2, 3, 3, 3};
    
    // 统计
    std::cout << "Count of 3: " << ums.count(3) << std::endl;
    
    // 查找范围
    auto range = ums.equal_range(2);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

### 4.3 std::unordered_map
```cpp
#include <unordered_map>

void unorderedMapExample() {
    std::unordered_map<std::string, int> um = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    
    // 插入
    um.insert({"David", 40});
    um.emplace("Eve", 45);
    um["Frank"] = 50;
    
    // 保留接口
    um.reserve(100);  // 预分配空间
    
    // 哈希策略
    um.max_load_factor(0.7);  // 设置最大负载因子
    um.rehash(50);  // 重新哈希
    
    // 遍历桶
    for (size_t i = 0; i < um.bucket_count(); ++i) {
        std::cout << "Bucket " << i << ": ";
        for (auto it = um.begin(i); it != um.end(i); ++it) {
            std::cout << it->first << " ";
        }
        std::cout << std::endl;
    }
}
```

### 4.4 std::unordered_multimap
```cpp
void unorderedMultimapExample() {
    std::unordered_multimap<std::string, int> umm = {
        {"Alice", 25},
        {"Alice", 26},
        {"Bob", 30}
    };
    
    // 插入重复键
    umm.insert({"Bob", 31});
    
    // 查找所有值
    auto range = umm.equal_range("Alice");
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}
```

## 5. 常用成员函数对比

### 5.1 公共成员函数
```cpp
// 容量相关
size()           // 元素数量
empty()          // 是否为空
max_size()       // 可能的最大元素数

// 修改器
clear()          // 清空所有元素
insert()         // 插入元素
emplace()        // 原地构造插入
erase()          // 删除元素
swap()           // 交换内容

// 查找
find(key)        // 查找特定键
count(key)       // 统计键的数量
equal_range(key) // 返回匹配键的范围
```

### 5.2 特有成员函数
```cpp
// 有序容器特有
lower_bound(key)  // 返回第一个不小于key的元素
upper_bound(key)  // 返回第一个大于key的元素

// 无序容器特有
bucket_count()    // 返回桶的数量
load_factor()     // 返回负载因子
max_load_factor() // 返回或设置最大负载因子
rehash(n)         // 设置桶的数量为至少n
reserve(n)        // 预留空间
```

## 6. 性能对比和选择指南

### 6.1 时间复杂度对比
| 操作 | 有序容器 | 无序容器           |
| ---- | -------- | ------------------ |
| 查找 | O(log n) | O(1)平均，O(n)最坏 |
| 插入 | O(log n) | O(1)平均，O(n)最坏 |
| 删除 | O(log n) | O(1)平均，O(n)最坏 |
| 遍历 | 有序     | 无序               |

### 6.2 选择建议
1. **需要有序遍历** → 选择有序容器
2. **需要最高性能查找** → 选择无序容器
3. **内存受限** → 有序容器通常内存开销更小
4. **需要范围查询** → 选择有序容器
5. **键类型没有良好的哈希函数** → 选择有序容器
6. **需要插入顺序保持** → 考虑`std::map`或自定义哈希

## 7. 自定义比较和哈希函数示例

```cpp
#include <iostream>
#include <map>
#include <unordered_map>

// 自定义键类型
struct ComplexKey {
    int id;
    std::string name;
    
    // 为有序容器提供比较
    bool operator<(const ComplexKey& other) const {
        return std::tie(id, name) < std::tie(other.id, other.name);
    }
    
    // 为无序容器提供相等比较
    bool operator==(const ComplexKey& other) const {
        return id == other.id && name == other.name;
    }
};

// 自定义哈希函数
struct ComplexKeyHash {
    std::size_t operator()(const ComplexKey& k) const {
        std::size_t h1 = std::hash<int>{}(k.id);
        std::size_t h2 = std::hash<std::string>{}(k.name);
        return h1 ^ (h2 << 1);
    }
};

void customKeyExample() {
    // 使用自定义键的有序map
    std::map<ComplexKey, std::string> orderedMap;
    orderedMap[{1, "Alice"}] = "Value1";
    
    // 使用自定义键的无序map
    std::unordered_map<ComplexKey, std::string, ComplexKeyHash> unorderedMap;
    unorderedMap[{2, "Bob"}] = "Value2";
}
```

## 8. 重要注意事项

1. **迭代器失效**：
   - 有序容器：插入不会使迭代器失效，删除只会使被删除元素的迭代器失效
   - 无序容器：rehash会使所有迭代器失效

2. **内存管理**：
   ```cpp
   // 预分配可以提升性能
   std::unordered_map<int, int> map;
   map.reserve(1000);  // 预分配空间
   ```

3. **自定义类型作为键**：
   - 有序容器：需要定义`operator<`或提供比较函数
   - 无序容器：需要定义`operator==`和哈希函数

4. **线程安全**：
   - 标准关联容器不是线程安全的
   - 需要外部同步机制

## 9. 实际应用示例

```cpp
// 统计单词频率
std::map<std::string, int> wordCount(const std::string& text) {
    std::map<std::string, int> counter;
    std::istringstream iss(text);
    std::string word;
    
    while (iss >> word) {
        ++counter[word];
    }
    
    return counter;
}

// 缓存实现
template<typename Key, typename Value>
class LRUCache {
private:
    std::list<std::pair<Key, Value>> cacheList;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cacheMap;
    size_t capacity;
    
public:
    LRUCache(size_t cap) : capacity(cap) {}
    
    Value get(const Key& key) {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            throw std::runtime_error("Key not found");
        }
        
        // 移动到列表头部
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second;
    }
    
    void put(const Key& key, const Value& value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            it->second->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return;
        }
        
        if (cacheMap.size() == capacity) {
            // 删除最久未使用的
            auto last = cacheList.end();
            last--;
            cacheMap.erase(last->first);
            cacheList.pop_back();
        }
        
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};
```

## 总结

C++关联容器提供了强大的数据管理能力：
- 有序容器基于红黑树，提供稳定的O(log n)操作和有序遍历
- 无序容器基于哈希表，提供平均O(1)的高效操作
- 选择合适的容器需要考虑具体的使用场景、性能要求和功能需求
- 掌握各种容器的特性和底层实现有助于编写高效的C++代码
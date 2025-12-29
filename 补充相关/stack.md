# C++ 栈详细介绍

## 1. 栈的基本概念

**栈（Stack）** 是一种**后进先出（LIFO - Last In First Out）** 的线性数据结构，只允许在一端（栈顶）进行插入和删除操作。

### 主要特点：
- **后进先出**：最后入栈的元素最先出栈
- **操作受限**：只能从栈顶访问元素
- **两个主要操作**：压栈（push）和弹栈（pop）

## 2. C++ 中栈的实现方式

### 2.1 使用 STL 的 stack 容器
```cpp
#include <stack>
#include <iostream>

int main() {
    // 创建栈
    std::stack<int> s;
    
    // 压栈操作
    s.push(10);
    s.push(20);
    s.push(30);
    
    // 访问栈顶元素
    std::cout << "栈顶元素: " << s.top() << std::endl;  // 输出: 30
    
    // 弹栈操作
    s.pop();  // 移除30
    
    // 判断栈是否为空
    if (!s.empty()) {
        std::cout << "栈不为空，当前大小: " << s.size() << std::endl;
    }
    
    return 0;
}
```

### 2.2 使用数组手动实现栈
```cpp
#include <iostream>
#define MAX_SIZE 100

class ArrayStack {
private:
    int arr[MAX_SIZE];
    int top;
    
public:
    ArrayStack() : top(-1) {}
    
    // 压栈
    void push(int value) {
        if (top >= MAX_SIZE - 1) {
            std::cout << "栈已满!" << std::endl;
            return;
        }
        arr[++top] = value;
    }
    
    // 弹栈
    int pop() {
        if (isEmpty()) {
            std::cout << "栈为空!" << std::endl;
            return -1;
        }
        return arr[top--];
    }
    
    // 查看栈顶
    int peek() {
        if (isEmpty()) {
            std::cout << "栈为空!" << std::endl;
            return -1;
        }
        return arr[top];
    }
    
    // 判断是否为空
    bool isEmpty() {
        return top == -1;
    }
    
    // 获取栈大小
    int size() {
        return top + 1;
    }
};
```

### 2.3 使用链表实现栈
```cpp
#include <iostream>

class Node {
public:
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedListStack {
private:
    Node* top;
    
public:
    LinkedListStack() : top(nullptr) {}
    
    // 压栈
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }
    
    // 弹栈
    int pop() {
        if (isEmpty()) {
            std::cout << "栈为空!" << std::endl;
            return -1;
        }
        
        Node* temp = top;
        int poppedValue = temp->data;
        top = top->next;
        delete temp;
        
        return poppedValue;
    }
    
    // 查看栈顶
    int peek() {
        if (isEmpty()) {
            std::cout << "栈为空!" << std::endl;
            return -1;
        }
        return top->data;
    }
    
    bool isEmpty() {
        return top == nullptr;
    }
    
    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};
```

## 3. STL stack 的主要成员函数

| 函数          | 描述                   | 时间复杂度 |
| ------------- | ---------------------- | ---------- |
| `push(value)` | 将元素压入栈顶         | O(1)       |
| `pop()`       | 移除栈顶元素           | O(1)       |
| `top()`       | 返回栈顶元素（不删除） | O(1)       |
| `empty()`     | 检查栈是否为空         | O(1)       |
| `size()`      | 返回栈中元素数量       | O(1)       |

## 4. 栈的常见应用场景

### 4.1 表达式求值
```cpp
#include <stack>
#include <string>
#include <iostream>

bool isBalanced(const std::string& expr) {
    std::stack<char> s;
    
    for (char ch : expr) {
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.empty()) return false;
            
            char top = s.top();
            s.pop();
            
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) {
                return false;
            }
        }
    }
    
    return s.empty();
}
```

### 4.2 函数调用栈
```cpp
#include <iostream>

// 递归函数展示调用栈
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // 每次递归调用都会在调用栈中添加一层
}

int main() {
    std::cout << "5的阶乘: " << factorial(5) << std::endl;
    return 0;
}
```

### 4.3 浏览器历史记录
```cpp
#include <stack>
#include <string>
#include <iostream>

class BrowserHistory {
private:
    std::stack<std::string> backStack;
    std::stack<std::string> forwardStack;
    std::string currentPage;
    
public:
    void visit(const std::string& url) {
        if (!currentPage.empty()) {
            backStack.push(currentPage);
        }
        currentPage = url;
        // 清空前向栈
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
        std::cout << "访问: " << url << std::endl;
    }
    
    void goBack() {
        if (backStack.empty()) {
            std::cout << "无法后退" << std::endl;
            return;
        }
        forwardStack.push(currentPage);
        currentPage = backStack.top();
        backStack.pop();
        std::cout << "后退到: " << currentPage << std::endl;
    }
    
    void goForward() {
        if (forwardStack.empty()) {
            std::cout << "无法前进" << std::endl;
            return;
        }
        backStack.push(currentPage);
        currentPage = forwardStack.top();
        forwardStack.pop();
        std::cout << "前进到: " << currentPage << std::endl;
    }
};
```

### 4.4 深度优先搜索（DFS）
```cpp
#include <stack>
#include <vector>
#include <iostream>

void dfs(int start, const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> s;
    
    s.push(start);
    
    while (!s.empty()) {
        int vertex = s.top();
        s.pop();
        
        if (!visited[vertex]) {
            visited[vertex] = true;
            std::cout << "访问节点: " << vertex << std::endl;
            
            // 将邻接节点逆序压栈，保持顺序
            for (auto it = graph[vertex].rbegin(); it != graph[vertex].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
    }
}
```

## 5. 栈的变体和高级用法

### 5.1 最小栈（Min Stack）
```cpp
#include <stack>
#include <iostream>

class MinStack {
private:
    std::stack<int> mainStack;
    std::stack<int> minStack;
    
public:
    void push(int value) {
        mainStack.push(value);
        if (minStack.empty() || value <= minStack.top()) {
            minStack.push(value);
        }
    }
    
    void pop() {
        if (mainStack.empty()) return;
        
        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
    
    bool empty() {
        return mainStack.empty();
    }
};
```

### 5.2 使用两个栈实现队列
```cpp
#include <stack>
#include <iostream>

class QueueUsingStacks {
private:
    std::stack<int> inputStack;
    std::stack<int> outputStack;
    
    void transfer() {
        while (!inputStack.empty()) {
            outputStack.push(inputStack.top());
            inputStack.pop();
        }
    }
    
public:
    void enqueue(int value) {
        inputStack.push(value);
    }
    
    int dequeue() {
        if (empty()) {
            std::cout << "队列为空!" << std::endl;
            return -1;
        }
        
        if (outputStack.empty()) {
            transfer();
        }
        
        int value = outputStack.top();
        outputStack.pop();
        return value;
    }
    
    int front() {
        if (empty()) {
            std::cout << "队列为空!" << std::endl;
            return -1;
        }
        
        if (outputStack.empty()) {
            transfer();
        }
        
        return outputStack.top();
    }
    
    bool empty() {
        return inputStack.empty() && outputStack.empty();
    }
};
```

## 6. 性能分析和注意事项

### 时间复杂度：
- 所有基本操作（push, pop, top, empty）：O(1)
- 访问中间元素：O(n)（需要弹出所有上层元素）

### 内存考虑：
- 数组实现：固定大小，可能浪费空间或溢出
- 链表实现：动态大小，但每个节点有额外指针开销
- STL stack：基于deque（默认），内存使用较高效

### 使用建议：
1. **选择合适实现**：根据场景选择STL stack或自定义实现
2. **避免栈溢出**：递归深度过大或无限递归
3. **检查空栈**：pop()和top()前先检查empty()
4. **线程安全**：多线程环境下需要同步机制

## 7. 总结

栈是C++中基础但强大的数据结构，通过STL可以方便使用，也能自定义实现以满足特定需求。理解栈的原理和应用场景对于解决许多算法问题（如括号匹配、表达式求值、DFS等）至关重要。在实际开发中，合理使用栈可以提高代码效率和可读性。
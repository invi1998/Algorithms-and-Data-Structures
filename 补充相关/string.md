# C++ 现代字符串处理

C++ 中的现代字符串处理主要集中在 `std::string`、`std::string_view` 和相关工具上。以下是一个全面的指南：

## 1. **std::string（C++11 及以后）**

### 基本用法
```cpp
#include <string>
#include <iostream>

int main() {
    // 初始化方式
    std::string s1 = "Hello";
    std::string s2("World");
    std::string s3(5, 'A');  // "AAAAA"
    
    // C++11 统一初始化
    std::string s4{"Modern C++"};
    
    // 原始字符串字面量（C++11）
    std::string path = R"(C:\Users\Name\Documents)";
    std::string json = R"({
        "name": "John",
        "age": 30
    })";
    
    return 0;
}
```

### 用户定义字面量（C++14）
```cpp
#include <string>

// 自定义字符串字面量
std::string operator"" _s(const char* str, size_t len) {
    return std::string(str, len);
}

auto str = "Hello"_s;  // 类型为 std::string
```

## 2. **std::string_view（C++17）**

不拥有字符串数据，只提供视图，避免不必要的拷贝：

```cpp
#include <string>
#include <string_view>
#include <iostream>

void process(std::string_view sv) {
    // 轻量级，不拷贝字符串
    std::cout << "Length: " << sv.length() << '\n';
    std::cout << "First char: " << sv.front() << '\n';
    std::cout << "Last char: " << sv.back() << '\n';
    
    // 子字符串视图（O(1) 操作）
    auto sub = sv.substr(0, 5);
    
    // 查找
    size_t pos = sv.find("World");
    if (pos != std::string_view::npos) {
        std::cout << "Found at: " << pos << '\n';
    }
}

int main() {
    std::string str = "Hello, World!";
    const char* cstr = "C-string";
    
    process(str);          // 从 std::string
    process(cstr);         // 从 C 字符串
    process("Literal");    // 从字面量
    
    // 使用 string_view 作为返回值
    std::string_view get_prefix(const std::string& s) {
        return std::string_view(s.data(), 3);
    }
    
    return 0;
}
```

## 3. **现代字符串操作**

### 范围 for 循环（C++11）
```cpp
std::string str = "Hello";
for (char c : str) {
    std::cout << c << ' ';
}

// 引用修改
for (char& c : str) {
    c = std::toupper(c);
}

// 使用 auto
for (auto it = str.begin(); it != str.end(); ++it) {
    *it = std::tolower(*it);
}
```

### 字符串连接优化
```cpp
#include <string>

// C++11 move 语义优化
std::string create_string() {
    std::string result;
    // ... 构建字符串
    return result;  // 移动而非拷贝
}

// 使用 += 和 append 避免临时对象
std::string str;
str.reserve(100);  // 预分配内存
str += "Hello";
str.append(" World");
```

## 4. **字符串转换**

### 数字与字符串互转（C++11）
```cpp
#include <string>
#include <iostream>

int main() {
    // 数字转字符串
    std::string s1 = std::to_string(42);
    std::string s2 = std::to_string(3.14159);
    
    // 字符串转数字
    int i = std::stoi("123");
    double d = std::stod("3.14");
    long l = std::stol("1000000");
    
    // 错误处理
    try {
        int num = std::stoi("abc");  // 抛出 std::invalid_argument
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << '\n';
    }
    
    return 0;
}
```

### 高性能转换（C++17）
```cpp
#include <charconv>  // C++17
#include <string>
#include <iostream>

int main() {
    // std::to_chars - 不分配内存，高性能
    char buffer[20];
    int value = 12345;
    auto [ptr, ec] = std::to_chars(buffer, buffer + 20, value);
    
    if (ec == std::errc()) {
        std::string result(buffer, ptr);
        std::cout << result << '\n';
    }
    
    // std::from_chars - 不抛出异常
    const char* str = "123.45";
    double d;
    auto [p, err] = std::from_chars(str, str + 6, d);
    
    if (err == std::errc()) {
        std::cout << "Parsed: " << d << '\n';
    }
    
    return 0;
}
```

## 5. **字符串格式化（C++20）**

```cpp
#include <format>  // C++20
#include <string>
#include <iostream>
#include <numbers>

int main() {
    // 类型安全的格式化
    std::string message = std::format("Hello, {}!", "World");
    std::cout << message << '\n';
    
    // 位置参数
    std::string s = std::format("{1} {0}", "World", "Hello");
    
    // 格式说明符
    double pi = std::numbers::pi;
    std::string pi_str = std::format("Pi: {:.2f}", pi);
    
    // 输出到流
    std::cout << std::format("The answer is {}\n", 42);
    
    // 宽字符支持
    std::wstring wmsg = std::format(L"Unicode: {}", L"测试");
    
    return 0;
}
```

## 6. **UTF-8 字符串处理（C++20）**

```cpp
#include <string>
#include <iostream>

int main() {
    // C++20 char8_t 类型用于 UTF-8
    std::u8string utf8_str = u8"Hello 世界 🎉";
    
    // UTF-8 字面量
    const char8_t* utf8_literal = u8"UTF-8 字符串";
    
    // 转换为常规字符串视图（需要转换）
    std::string_view sv(reinterpret_cast<const char*>(utf8_str.data()));
    
    return 0;
}
```

## 7. **字符串搜索与替换**

```cpp
#include <string>
#include <algorithm>
#include <iostream>

int main() {
    std::string str = "Hello, World! Hello, C++!";
    
    // 使用 string_view 搜索（C++17）
    std::string_view needle = "Hello";
    size_t pos = str.find(needle);
    
    // 替换子串
    if (pos != std::string::npos) {
        str.replace(pos, needle.length(), "Hi");
    }
    
    // 使用算法
    std::replace(str.begin(), str.end(), '!', '?');
    
    // C++20 starts_with/ends_with
    if (str.starts_with("Hi")) {
        std::cout << "Starts with Hi\n";
    }
    
    if (str.ends_with("?")) {
        std::cout << "Ends with ?\n";
    }
    
    return 0;
}
```

## 8. **字符串分割（现代方法）**

```cpp
#include <string>
#include <vector>
#include <sstream>
#include <ranges>  // C++20
#include <algorithm>
#include <iostream>

// 传统方法
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// C++20 范围方法
auto split_string(std::string_view str, char delimiter) {
    return str 
        | std::views::split(delimiter)
        | std::views::transform([](auto&& range) {
            return std::string(range.begin(), range.end());
        });
}

int main() {
    std::string csv = "apple,banana,cherry";
    
    // C++20 方式
    for (const auto& word : split_string(csv, ',')) {
        std::cout << word << '\n';
    }
    
    return 0;
}
```

## 9. **性能最佳实践**

1. **使用 `string_view` 作为函数参数**
   ```cpp
   // 好：避免拷贝
   void process(std::string_view str);
   
   // 不好：可能产生不必要的拷贝
   void process(const std::string& str);
   ```

2. **预分配内存**
   ```cpp
   std::string result;
   result.reserve(1000);  // 避免多次重新分配
   ```

3. **使用移动语义**
   ```cpp
   std::string process() {
       std::string data = get_large_string();
       return data;  // 移动而非拷贝（RVO/NRVO）
   }
   ```

4. **避免临时字符串**
   ```cpp
   // 不好：创建临时字符串
   str = str + "a" + "b" + "c";
   
   // 好：使用 append 或 +=
   str.append("a").append("b").append("c");
   ```

## 10. **相关工具**

```cpp
#include <string>
#include <regex>    // 正则表达式
#include <sstream>  // 字符串流
#include <iomanip>  // 格式化输出

int main() {
    // 正则表达式（C++11）
    std::string text = "Email: test@example.com";
    std::regex email_pattern(R"((\w+@\w+\.\w+))");
    std::smatch matches;
    
    if (std::regex_search(text, matches, email_pattern)) {
        std::cout << "Found email: " << matches[1] << '\n';
    }
    
    // 字符串流
    std::ostringstream oss;
    oss << "Value: " << 42 << ", Pi: " << std::setprecision(3) << 3.14159;
    std::string formatted = oss.str();
    
    return 0;
}
```

## 总结

现代 C++ 字符串处理的核心要点：
- **优先使用 `std::string_view`** 作为只读字符串参数
- **利用移动语义** 避免不必要的拷贝
- **使用 `std::format`（C++20）** 进行类型安全的格式化
- **考虑性能**：预分配内存、避免临时对象
- **使用现代 API**：`starts_with`、`ends_with`（C++20）、范围算法

这些现代特性使得 C++ 字符串处理更加安全、高效和表达力强。



C++ 中数字与字符串之间的转换有多种方法，各有优缺点。以下是详细的分类介绍：

## 一、C++ 标准库方法（C++11+）

### 1. **数字转字符串** - `std::to_string()` 系列
```cpp
#include <string>

int n = 42;
double d = 3.14;

// 各种基本类型都有对应的重载
std::string s1 = std::to_string(n);     // "42"
std::string s2 = std::to_string(d);     // "3.140000"
std::string s3 = std::to_string(123L);  // "123"
std::string s4 = std::to_string(45u);   // "45"

// 注意：浮点数转换可能包含不必要的尾随零
```

### 2. **字符串转数字** - `std::stoi()` 系列
```cpp
#include <string>
#include <iostream>

// 基本转换
std::string s = "123";
int n1 = std::stoi(s);          // 123
long n2 = std::stol(s);         // 123L
long long n3 = std::stoll(s);   // 123LL
unsigned long n4 = std::stoul(s); // 123UL

// 浮点数
std::string f = "3.14";
float f1 = std::stof(f);        // 3.14f
double f2 = std::stod(f);       // 3.14
long double f3 = std::stold(f); // 3.14L

// 高级用法：指定进制和错误位置
std::string hex = "0xFF";
size_t pos;
int hex_val = std::stoi(hex, &pos, 16);  // pos=4, hex_val=255

std::string bin = "1010";
int bin_val = std::stoi(bin, nullptr, 2); // 10
```

### 3. **字符转数字/数字转字符**
```cpp
// 数字字符转数字
char c = '7';
int num = c - '0';  // 7

// 数字转数字字符（0-9）
int n = 5;
char digit = n + '0';  // '5'

// 检查是否是数字字符
bool is_digit = std::isdigit(c);

// 获取字符的ASCII值
int ascii = static_cast<int>(c);
// 或
int ascii = c;  // 隐式转换
```

## 二、C 标准库方法

### 1. **字符串转数字**
```cpp
#include <cstdlib>  // C标准库
#include <cstdio>   // printf/scanf系列

const char* s = "123";
const char* f = "3.14";

// 简单转换（不推荐：无错误检测）
int n1 = atoi(s);      // 字符串转int
long n2 = atol(s);     // 字符串转long
double d1 = atof(f);   // 字符串转double

// 安全转换（推荐：有错误检测）
char* end;
long n3 = strtol(s, &end, 10);  // 10进制
if (*end != '\0') { /* 转换失败或部分成功 */ }

double d2 = strtod(f, &end);
unsigned long n4 = strtoul(s, &end, 16);  // 16进制
```

### 2. **数字转字符串**
```cpp
#include <cstdio>

// sprintf系列（不安全，有缓冲区溢出风险）
char buffer[50];
int n = 123;
sprintf(buffer, "%d", n);        // "123"
sprintf(buffer, "%f", 3.14);     // "3.140000"
sprintf(buffer, "%x", 255);      // "ff" (十六进制)

// snprintf（安全，推荐）
snprintf(buffer, sizeof(buffer), "%d", n);

// 格式化输出
int year = 2024, month = 1, day = 1;
snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
// "2024-01-01"
```

## 三、流方法（`<sstream>`）

```cpp
#include <sstream>
#include <string>

// 1. 数字转字符串
std::ostringstream oss;
int n = 42;
double d = 3.14159;

oss << n << " " << d;            // "42 3.14159"
std::string s = oss.str();       // 获取字符串

// 重置流
oss.str("");  // 清空内容
oss.clear();  // 清除错误状态

// 格式化输出
oss << std::hex << 255;          // "ff"
oss << std::fixed << std::setprecision(2) << 3.14159;  // "3.14"

// 2. 字符串转数字
std::istringstream iss("123 3.14");
int num;
double val;
iss >> num >> val;  // num=123, val=3.14

// 处理整个字符串
std::string input = "10,20,30";
iss.str(input);
char comma;
int a, b, c;
iss >> a >> comma >> b >> comma >> c;
```

## 四、C++17 高性能转换（`<charconv>`）

```cpp
#include <charconv>  // C++17
#include <string>
#include <array>

// 1. 数字转字符串（高性能，无内存分配）
int value = 12345;
std::array<char, 10> buffer;
auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);

if (ec == std::errc()) {
    std::string result(buffer.data(), ptr);  // "12345"
}

// 支持不同进制
std::to_chars(buffer.data(), buffer.data() + buffer.size(), 255, 16);  // "ff"

// 浮点数转换
double pi = 3.1415926535;
auto [ptr2, ec2] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), 
                                 pi, std::chars_format::fixed, 2);
// "3.14"

// 2. 字符串转数字（高性能，不抛出异常）
std::string str = "12345";
int val;
auto [ptr3, ec3] = std::from_chars(str.data(), str.data() + str.size(), val);

if (ec3 == std::errc()) {
    // 转换成功，val = 12345
} else if (ec3 == std::errc::invalid_argument) {
    // 无效参数
} else if (ec3 == std::errc::result_out_of_range) {
    // 超出范围
}
```

## 五、格式化库（C++20 `<format>`）

```cpp
#include <format>  // C++20
#include <string>

// 现代化格式化
int n = 42;
double d = 3.14159;

std::string s1 = std::format("Value: {}", n);           // "Value: 42"
std::string s2 = std::format("Pi: {:.2f}", d);          // "Pi: 3.14"
std::string s3 = std::format("Hex: {:x}", 255);         // "Hex: ff"
std::string s4 = std::format("Date: {:%Y-%m-%d}", ...); // 日期格式化
```

## 六、Boost库方法

```cpp
#include <boost/lexical_cast.hpp>
#include <string>

// 简单双向转换
std::string s = boost::lexical_cast<std::string>(123);   // "123"
int n = boost::lexical_cast<int>("456");                 // 456
double d = boost::lexical_cast<double>("3.14");          // 3.14

// 转换失败会抛出 bad_lexical_cast 异常
try {
    int x = boost::lexical_cast<int>("abc");
} catch (const boost::bad_lexical_cast& e) {
    // 处理异常
}
```

## 七、自定义转换函数

```cpp
// 整数转字符串（手工实现）
std::string int_to_string(int n) {
    if (n == 0) return "0";
    
    bool negative = n < 0;
    if (negative) n = -n;
    
    std::string result;
    while (n > 0) {
        result = static_cast<char>('0' + n % 10) + result;
        n /= 10;
    }
    
    if (negative) result = "-" + result;
    return result;
}

// 字符串转整数（手工实现）
int string_to_int(const std::string& s) {
    int result = 0;
    bool negative = false;
    size_t i = 0;
    
    if (s[0] == '-') {
        negative = true;
        i = 1;
    }
    
    for (; i < s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            throw std::invalid_argument("Invalid character");
        }
        result = result * 10 + (s[i] - '0');
    }
    
    return negative ? -result : result;
}
```

## 性能对比和选择建议

| 方法                   | 优点                   | 缺点                     | 适用场景               |
| ---------------------- | ---------------------- | ------------------------ | ---------------------- |
| **`std::to_string()`** | 简单易用，类型安全     | 浮点数格式固定，性能一般 | 一般用途，快速原型     |
| **`std::stoi()`系列**  | 错误检测，支持进制     | 抛出异常，性能一般       | 需要错误处理的转换     |
| **`std::charconv`**    | 性能最优，不分配内存   | C++17，接口较复杂        | 高性能场景，大容量数据 |
| **`sprintf/snprintf`** | C兼容，格式控制强      | 缓冲区溢出风险，C风格    | C兼容代码，格式复杂    |
| **`stringstream`**     | 格式化灵活，类型安全   | 性能较差，代码冗长       | 复杂格式化，教学示例   |
| **`std::format`**      | 现代化，类型安全，易读 | C++20                    | 新项目，需要良好格式   |

## 推荐的最佳实践

### 1. **现代C++项目（C++17+）**
```cpp
// 高性能转换
#include <charconv>

// 数字转字符串
std::array<char, 20> buffer;
auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);
std::string result(buffer.data(), ptr);

// 字符串转数字
int value;
std::from_chars(str.data(), str.data() + str.size(), value);
```

### 2. **通用项目（C++11+）**
```cpp
// 简单转换
int n = std::stoi(str);
std::string s = std::to_string(n);

// 需要错误处理
try {
    size_t pos;
    int n = std::stoi(str, &pos);
    if (pos != str.size()) {
        // 部分转换或额外字符
    }
} catch (const std::invalid_argument& e) {
    // 无效参数
} catch (const std::out_of_range& e) {
    // 超出范围
}
```

### 3. **性能不敏感，需要灵活格式**
```cpp
#include <sstream>
#include <iomanip>

std::ostringstream oss;
oss << std::fixed << std::setprecision(2) << 3.14159;
std::string s = oss.str();  // "3.14"
```

### 4. **C兼容或嵌入式**
```cpp
char buffer[32];
int n = 123;
snprintf(buffer, sizeof(buffer), "%d", n);

const char* str = "456";
char* end;
long val = strtol(str, &end, 10);
if (*end != '\0') {
    // 处理错误
}
```

根据你的具体需求（性能要求、C++版本、错误处理需求）选择合适的转换方法。
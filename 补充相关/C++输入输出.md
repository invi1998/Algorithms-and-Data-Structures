# C++输入输出全面指南

## 一、基础输入输出头文件

### 1. 主要头文件
```cpp
#include <iostream>     // 标准输入输出流
#include <fstream>      // 文件流
#include <sstream>      // 字符串流
#include <iomanip>      // 输入输出格式控制
```

## 二、标准控制台I/O

### 1. 基本输出
```cpp
#include <iostream>
using namespace std;

cout << "Hello, World!" << endl;       // 输出并换行
cout << "No newline" << flush;         // 输出但不换行，立即刷新缓冲区
cout << "Value: " << 42 << "\n";       // 使用换行符
```

### 2. 基本输入
```cpp
int num;
double price;
string name;

cin >> num;                     // 读取整数（跳过前导空白符）
cin >> price;                   // 读取浮点数
cin >> name;                    // 读取单词（到空白符为止）
cin >> num >> price >> name;    // 连续读取
```

## 三、字符级输入输出

### 1. 逐个字符输入
```cpp
// 方法1: 使用cin.get()
char ch;
while (cin.get(ch)) {           // 读取包括空白字符
    cout << ch;
    if (ch == '\n') break;
}

// 方法2: 使用cin.get()的另一种形式
ch = cin.get();                 // 读取一个字符

// 方法3: 使用getchar()风格的cin.get()
char buffer[100];
cin.get(buffer, 100);           // 读取最多99个字符

// 方法4: 使用>>运算符（跳过空白字符）
char c;
while (cin >> c) {              // 跳过空格、制表符、换行符
    cout << c;
}
```

### 2. 逐个字符输出
```cpp
// 方法1: 使用cout.put()
char ch = 'A';
cout.put(ch);
cout.put('\n');

// 方法2: 使用<<运算符
cout << ch;
```

## 四、行级输入输出

### 1. 逐行输入
```cpp
// 方法1: 使用getline() (推荐)
string line;
while (getline(cin, line)) {    // 读取整行，丢弃换行符
    cout << "Line: " << line << endl;
}

// 方法2: 使用cin.getline() (C风格字符串)
char buffer[256];
while (cin.getline(buffer, 256)) {
    cout << "Buffer: " << buffer << endl;
}

// 方法3: 混合使用时注意缓冲区
int num;
string text;
cin >> num;                     // 读取数字
cin.ignore();                   // 丢弃换行符
getline(cin, text);             // 现在可以正确读取整行
```

### 2. 逐行输出
```cpp
// 方法1: 使用endl (刷新缓冲区)
cout << "Line 1" << endl;
cout << "Line 2" << endl;

// 方法2: 使用\n (不立即刷新缓冲区)
cout << "Line 1\n";
cout << "Line 2\n";

// 方法3: 多行字符串
cout << R"(First line
Second line
Third line)" << endl;
```

## 五、文件输入输出

### 1. 文件打开模式
| 模式        | 描述                 |
| ----------- | -------------------- |
| ios::in     | 打开用于读取         |
| ios::out    | 打开用于写入         |
| ios::app    | 追加模式             |
| ios::ate    | 打开后定位到文件末尾 |
| ios::trunc  | 如果文件存在则清空   |
| ios::binary | 二进制模式           |

### 2. 文件写入
```cpp
#include <fstream>

// 方法1: 使用ofstream
ofstream outFile("output.txt");
if (outFile.is_open()) {
    outFile << "Hello, File!" << endl;
    outFile << 42 << " " << 3.14 << endl;
    outFile.close();
}

// 方法2: 追加模式
ofstream appFile("log.txt", ios::app);
appFile << "New log entry" << endl;

// 方法3: 逐行写入
vector<string> lines = {"Line 1", "Line 2", "Line 3"};
for (const auto& line : lines) {
    outFile << line << "\n";
}
```

### 3. 文件读取
```cpp
// 方法1: 使用ifstream逐词读取
ifstream inFile("input.txt");
string word;
while (inFile >> word) {        // 逐个单词读取
    cout << word << " ";
}

// 方法2: 逐行读取
ifstream inFile2("input.txt");
string line;
while (getline(inFile2, line)) {
    cout << line << endl;
}

// 方法3: 逐个字符读取
ifstream inFile3("input.txt");
char ch;
while (inFile3.get(ch)) {       // 包括空白字符
    cout << ch;
}

// 方法4: 检查文件状态
ifstream testFile("data.txt");
if (!testFile) {
    cerr << "Error opening file!" << endl;
    return 1;
}
```

### 4. 文件位置操作
```cpp
ifstream file("data.txt");
file.seekg(0, ios::beg);        // 移动到文件开头
file.seekg(10, ios::cur);       // 从当前位置前进10字节
file.seekg(-5, ios::end);       // 从文件末尾后退5字节

streampos pos = file.tellg();   // 获取当前位置
```

## 六、字符串流

### 1. 字符串流使用
```cpp
#include <sstream>

// 字符串转其他类型
string str = "42 3.14 hello";
istringstream iss(str);
int num;
double val;
string text;
iss >> num >> val >> text;

// 其他类型转字符串
ostringstream oss;
oss << "Value: " << 42 << ", Pi: " << 3.14159;
string result = oss.str();

// 解析CSV行
string csv = "John,Doe,30,Engineer";
istringstream csvStream(csv);
string token;
while (getline(csvStream, token, ',')) {
    cout << token << endl;
}
```

## 七、格式化输入输出

### 1. 数字格式化
```cpp
#include <iomanip>

double pi = 3.14159265359;

cout << fixed << setprecision(2) << pi << endl;     // 3.14
cout << scientific << pi << endl;                   // 3.14e+00
cout << setw(10) << setfill('*') << 42 << endl;     // *******42
cout << hex << 255 << endl;                         // ff
cout << oct << 64 << endl;                          // 100
cout << dec << 100 << endl;                         // 100
```

### 2. 对齐和填充
```cpp
cout << left << setw(15) << "Name" << setw(10) << "Age" << endl;
cout << right << setw(15) << "John" << setw(10) << 30 << endl;
cout << internal << setw(10) << showpos << 42 << endl; // +     42
```

## 八、错误处理

### 1. 流状态检查
```cpp
int value;
cin >> value;

if (cin.fail()) {
    cout << "Invalid input!" << endl;
    cin.clear();                    // 清除错误状态
    cin.ignore(1000, '\n');         // 忽略错误输入
}

// 检查EOF
while (cin >> value) {
    // 正常处理
    if (cin.eof()) break;
}
```

## 九、二进制文件操作

### 1. 二进制读写
```cpp
struct Person {
    char name[50];
    int age;
    double salary;
};

// 写入二进制文件
Person p = {"John Doe", 30, 50000.0};
ofstream bOut("data.bin", ios::binary);
bOut.write(reinterpret_cast<char*>(&p), sizeof(p));

// 读取二进制文件
Person p2;
ifstream bIn("data.bin", ios::binary);
bIn.read(reinterpret_cast<char*>(&p2), sizeof(p2));

// 读取整个二进制文件
ifstream file("data.bin", ios::binary | ios::ate);
streamsize size = file.tellg();
file.seekg(0, ios::beg);
vector<char> buffer(size);
file.read(buffer.data(), size);
```

## 十、性能优化技巧

### 1. 提高I/O性能
```cpp
// 取消C和C++流的同步
ios_base::sync_with_stdio(false);

// 解除cin和cout的绑定
cin.tie(nullptr);

// 使用缓冲区
stringstream buffer;
buffer << "大量数据...";
cout << buffer.str();

// 预分配内存
vector<string> lines;
lines.reserve(1000);  // 预分配空间
```

## 十一、总结表格

| **类别**      | **方法**                   | **描述**                   | **示例**                            |
| ------------- | -------------------------- | -------------------------- | ----------------------------------- |
| **字符输入**  | `cin.get()`                | 读取单个字符（包括空白符） | `char ch; cin.get(ch);`             |
|               | `cin.get(char*, size)`     | 读取C风格字符串            | `char buf[100]; cin.get(buf, 100);` |
| **字符输出**  | `cout.put()`               | 输出单个字符               | `cout.put('A');`                    |
| **行输入**    | `getline(istream, string)` | 读取整行到string           | `getline(cin, str);`                |
|               | `cin.getline()`            | 读取整行到字符数组         | `cin.getline(buf, 100);`            |
| **文件读取**  | `ifstream`                 | 读取文件                   | `ifstream file("data.txt");`        |
| **文件写入**  | `ofstream`                 | 写入文件                   | `ofstream file("out.txt");`         |
| **字符串流**  | `istringstream`            | 从字符串读取               | `istringstream iss(str);`           |
|               | `ostringstream`            | 写入到字符串               | `ostringstream oss;`                |
| **格式控制**  | `<iomanip>`                | 格式化输出                 | `setw(), setprecision()`            |
| **二进制I/O** | `read()/write()`           | 二进制操作                 | `file.read(buffer, size);`          |
| **状态检查**  | `good(), eof(), fail()`    | 检查流状态                 | `if(cin.fail()) {...}`              |

### 选择指南：

1. **读取单词** → 使用 `cin >> variable`
2. **读取整行** → 使用 `getline(cin, str)`
3. **包含空格的字符串** → 使用 `getline()`
4. **文件操作** → 使用 `ifstream/ofstream/fstream`
5. **字符串解析** → 使用 `istringstream`
6. **格式化输出** → 使用 `<iomanip>` 操作符
7. **高性能I/O** → 取消流同步，使用缓冲区
8. **二进制数据** → 使用 `read()/write()` 和 `ios::binary`

### 最佳实践：
- 总是检查文件是否成功打开
- 使用 `getline()` 而不是 `cin >>` 读取整行输入
- 混合使用 `>>` 和 `getline()` 时要小心缓冲区
- 对于大量数据，考虑使用二进制格式
- 使用RAII原则管理文件资源

这个指南涵盖了C++输入输出的主要方面。根据具体需求选择合适的方法，并注意错误处理和资源管理。
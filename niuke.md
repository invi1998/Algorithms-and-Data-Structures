## 小美的游戏

小美有一个长度为 n*n* 的数组，她最多可以进行 k*k* 次操作，每次操作如下：

1. 选择两个整数 i,j(1≤i<j≤n)*i*,*j*(1≤*i*<*j*≤*n*)
2. 选择两个整数 x,y*x*,*y*，使得 x×y=ai×aj*x*×*y*=*a**i*​×*a**j*​
3. 将 ai*a**i*​ 替换为 x*x*，将 aj*a**j*​ 替换为 y*y*


她希望最多进行 k*k* 次操作之后，最后数组中的元素的总和尽可能大。

时间限制：C/C++ 1秒，其他语言2秒

空间限制：C/C++ 256M，其他语言512M

输入描述：

```
一行两个整数 ，表示数组的长度和操作的次数。
一行  个整数 ，表示数组的元素。
```

输出描述：

```
输出一个整数，表示最后数组中的元素的总和的最大值，由于答案可能很大，你只需要输出答案对  取模的结果。
```

示例1

输入例子：

```
5 2
1 2 3 4 5
```

输出例子：

```
65
```

例子说明：

```
第一次操作后，数组变为 [1, 2, 12, 1, 5]
第二次操作，数组变为 [1, 2, 60, 1, 1]
```



```c++
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007;

struct Node {
    long double log_val;  // 用于比较大小
    long long mod_val;    // 取模后的值
    // 定义比较运算符，用于优先队列（最大堆）
    bool operator<(const Node& other) const {
        return log_val < other.log_val; // 最大堆需要重载 < 为实际上的 >
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> a(n);
    long long sum_mod = 0;
    priority_queue<Node> pq; // 最大堆
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum_mod = (sum_mod + a[i]) % MOD;
        if (a[i] > 1) {
            Node node;
            node.log_val = log((long double)a[i]);
            node.mod_val = a[i] % MOD;
            pq.push(node);
        }
    }
    
    int m = pq.size();
    int t = min(k, max(0, m - 1)); // 有效操作次数
    
    while (t > 0 && pq.size() >= 2) {
        Node x = pq.top(); pq.pop();
        Node y = pq.top(); pq.pop();
        
        // 计算新的总和
        long long new_sum = (sum_mod + 1 + (x.mod_val * y.mod_val) % MOD - x.mod_val - y.mod_val) % MOD;
        // 处理负数
        sum_mod = (new_sum + MOD) % MOD;
        
        // 创建新节点
        Node z;
        z.log_val = x.log_val + y.log_val;
        z.mod_val = (x.mod_val * y.mod_val) % MOD;
        pq.push(z);
        
        t--;
    }
    
    cout << sum_mod << endl;
    
    return 0;
}
```



## 小红的字母填写

小红拿到了一排格子，每个格子的背景是红色或者蓝色。

小红希望你将每个格子上填写一个小写字母，需要满足相同的字母的背景颜色是相同的。

小红希望最终出现次数最多的字母的出现次数尽可能小。你能帮帮她吗？

时间限制：C/C++ 1秒，其他语言2秒

空间限制：C/C++ 256M，其他语言512M

输入描述：

```
一个仅由字符'0'和'1'组成的字符串，长度不超过200000。
字符串用于表示小红拿到的格子的颜色。第个字符为'0'代表第第个格子为蓝色背景，字符'1'代表红色背景。
```

输出描述：

```
一个仅由小写字母构成的字符串，第个字符为第个格子上填写的字母，请务必保证字符串是合法的。如果有多解，输出任意即可。
```

示例1

输入例子：

```
010
```

输出例子：

```
abc
```

例子说明：

```
'a'为蓝色，'b'为红色，'c'为蓝色。三种字母均只出现了一次
```

示例2

输入例子：

```
000000000000000000000000001
```

输出例子：

```
bbcdefghijklmnopqrstuvwxyza
```

例子说明：

```
我们这个填空方案中，两个'b'都是蓝色，符合题目要求。除了'b'出现2次以外，其余的字母均只出现了1次。
```

```c++
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    string backgroundStr;
    while (getline(cin, backgroundStr)) { // 注意 while 处理多个 case
        int n = backgroundStr.length();
        string result(n, ' ');
        // 分别统计红色和蓝色的数量
        int redIdx = 0, blueIdx = 0;

        for (int i = 0; i < n; i++)
        {
            if (backgroundStr[i] == '1')
            {
                // 红色背景使用前13个字母（a-m）
                result[i] = 'a' + (redIdx % 13);
                redIdx++;
            }
            else
            {
                // 蓝色背景使用后13个字母（n-z）
                result[i] = 'n' + (blueIdx % 13);
                blueIdx++;
            }
        }

        cout << result << endl;
    }
}
// 64 位输出请用 printf("%lld")
```



## 小美种果树

小美在手机上种果树，只要成熟了就可以领到免费的水果了。

小美每天可以给果树浇水，果树的成长值加 x*x*。同时也可以给果树施肥，两次施肥至少需要间隔 2 天，果树的成长值加 y*y*。果树成长值达到 z*z* 就成熟了。

小红想知道，最少需要多少天可以领到免费的水果。

时间限制：C/C++ 1秒，其他语言2秒

空间限制：C/C++ 256M，其他语言512M

输入描述：

```
一行三个整数 ，分别表示浇水的成长值，施肥的成长值，果树成熟的成长值。
```

输出描述：

```
一行一个整数，表示最少需要多少天可以领到免费的水果。
```

示例1

输入例子：

```
1 2 10
```

输出例子：

```
6
```

例子说明：

```
第一天施肥浇水，成长值为 3。
第二天浇水，成长值为 3 + 1 = 4。
第三天浇水，成长值为 4 + 1 = 5。
第四天施肥浇水，成长值为 5 + 3 = 8。
第五天浇水，成长值为 8 + 1 = 9。
第六天浇水，成长值为 9 + 1 = 10。
果树成熟了，可以领到免费水果了！
```

```c++
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    int x, y, z;
    while (cin >> x >> y >> z) {
        ll left = 1, right = 2e9; // 设置一个足够大的上界，比如2e9
        while (left < right) {
            ll mid = left + (right - left) / 2;
            ll f_max = (mid + 2) / 3; // 最多可以施肥的次数
            ll total = mid * x + f_max * y;
            if (total >= z) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        cout << left << endl;
    }
    return 0;
}
```





给出一个长度为n的仅由A和B构成的字符串，你可以对这个字符串进行m次操作，每一次操作可以任选下面一种：

1. 交换字符串中两个字符。
2. 将字符串中的任意一个字符换成另一个字符。

请问在经过m次操作后，所能得到的字典序最小的字符串是什么。

**输入描述**
   输入第一行包含两个整数n，m，含义如题所示。(1<=n，m<=100000)
   输入第二行包含一个长度为n的仅包含A和B的字符串。

**输出描述**
   输出一个长度为n的仅包含A和B的字符串，表示字典序最大的字符串。

**输入样例**
5 2
ABBAB

**输出样例**
AAAAB



```c++
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    
    // 计算前缀和，preA[i] 表示 s[0..i-1] 中 'A' 的个数（前 i 个字符）
    int preA[n+1];
    preA[0] = 0;
    for (int i = 1; i <= n; i++) {
        preA[i] = preA[i-1] + (s[i-1] == 'A' ? 1 : 0);
    }
    
    int max_x = 0;  // 记录满足条件的最大 x
    for (int x = 0; x <= n; x++) {
        int b = x - preA[x];  // 前 x 个位置中 'B' 的个数
        int a = preA[n] - preA[x];  // 后 n-x 个位置中 'A' 的个数
        if (max(b, a) <= m) {
            max_x = x;
        }
    }
    
    // 构造结果字符串：前 max_x 个 'A'，后面是 'B'
    string result(max_x, 'A') + string(n - max_x, 'B');
    cout << result << endl;
    
    return 0;
}
```





Alice和Bob正在玩扑克游戏，他们的扑克中只有A、2、3、4、5、6、7这七种牌，牌的点数从大到小分为是：A、7、6、5、4、3、2。每种牌都有6张，共42张牌。
他们的扑克游戏规则如下：每个人发三张牌，然后根据牌型来比大小分胜负。
牌型有以下几种：
  “三条”：三张牌的点数都相同；
  “一对”：三张牌中恰有两张的点数相同；
  “高牌”：三张牌的点数都不相同。
在这三种牌型中，“三条”大于“一对”，“一对”大于“高牌”。
若同为“三条”，则比较点数大小；
若同为“一对”，则先比较组成对子的点数大小，若相同则再比较剩下一张牌的大小；
若同为“高牌”，则先比较点数最大的，相同则比较次大的，再相同则比较第三大的。
现在需要你作为裁判来判断Alice和Bob的胜负（较大者胜，二者相同则平局）。

**输入描述**
第一行是一个整数T，表示Alice和Bob接下来要进行T局游戏，1<=T<=200。
接下来T行，每行有6个用空格隔开的字符，第i行表示第i局游戏二人发到的牌，其中前3个表示Alice发到的牌，后3个表示Bob发到的牌。
**输出描述**
T行，其中第i行表示第i局游戏的结果。若Alice胜利则输出”Alice”，若Bob胜利则输出”Bob”，平局则输出”Tie”。
**输入样例1**
3
A A 7 A A A
2 3 2 4 A 3
3 2 4 4 3 2
**输出样例1**
Bob
Alice
Tie

```c++
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

// 将牌面字符映射为数值
int cardToRank(char card) {
    static map<char, int> rankMap = {
        {'A', 14}, {'7', 13}, {'6', 12}, {'5', 11},
        {'4', 10}, {'3', 9}, {'2', 8}
    };
    return rankMap[card];
}

// 评估三张牌的牌力，返回一个用于比较的元组
tuple<int, int, int, int> evaluateHand(const vector<char>& cards) {
    // 将牌面转换为数值
    vector<int> ranks;
    for (char card : cards) {
        ranks.push_back(cardToRank(card));
    }
    
    // 统计每种点数的出现次数
    map<int, int> count;
    for (int rank : ranks) {
        count[rank]++;
    }
    
    // 检查牌型
    if (count.size() == 1) {
        // 三条
        return make_tuple(2, ranks[0], 0, 0);
    } else if (count.size() == 2) {
        // 一对
        int pairRank = 0, singleRank = 0;
        for (const auto& p : count) {
            if (p.second == 2) {
                pairRank = p.first;
            } else {
                singleRank = p.first;
            }
        }
        return make_tuple(1, pairRank, singleRank, 0);
    } else {
        // 高牌
        sort(ranks.begin(), ranks.end(), greater<int>());
        return make_tuple(0, ranks[0], ranks[1], ranks[2]);
    }
}

int main() {
    int T;
    cin >> T;
    cin.ignore(); // 忽略换行符
    
    vector<string> results;
    
    for (int i = 0; i < T; i++) {
        vector<char> aliceCards(3);
        vector<char> bobCards(3);
        
        // 读取6张牌
        for (int j = 0; j < 3; j++) {
            cin >> aliceCards[j];
        }
        for (int j = 0; j < 3; j++) {
            cin >> bobCards[j];
        }
        
        // 评估牌力
        auto aliceHand = evaluateHand(aliceCards);
        auto bobHand = evaluateHand(bobCards);
        
        // 比较牌力
        if (aliceHand > bobHand) {
            results.push_back("Alice");
        } else if (aliceHand < bobHand) {
            results.push_back("Bob");
        } else {
            results.push_back("Tie");
        }
    }
    
    // 输出结果
    for (const auto& result : results) {
        cout << result << endl;
    }
    
    return 0;
}
```



给你一个n行n列的矩阵，你需要对它进行q次操作，操作种类有如下两种：
  1 r: 表示将矩阵的第r行向右循环移位1位。
  2 c: 表示将矩阵的第c列向上循环移位1位。
假设矩阵的某一行元素从左向右为a_1,a_2,…,a_n，其向右循环移位1位后的结果是a_n, a_1, a_2, …, a_{n-1}。将矩阵的某一列向上循环位移类似，具体可以参看样例解释。最后输出q次操作后的结果矩阵。
**输入描述**
第一行两个正整数n、q，分别表示矩阵的行列数均为n，要进行的操作数为q。1<=n<=100, q<=200。
接下来n行每行n个整数，第i行的第j个数表示矩阵第i行第j列的元素值。
接下来q行每行两个整数ti和xi，其中ti表示操作的种类(1或2)，xi表示操作对应的r或c，保证1<=xi<=n。
**输出描述**
输出一个n行n列的矩阵，表示q次操作后的结果矩阵。
**输入样例1**
3 2
1 2 3
4 5 6
7 8 9
2 2
1 2
**输出样例1**
1 5 3
6 4 8
7 2 9
**样例解释1**
第一个操作是将矩阵的第2列向上循环移位1位，矩阵变为：
1 5 3
4 8 6
7 2 9
第二个操作是将矩阵的第2行向右循环位移1位，矩阵变为：
1 5 3
6 4 8
7 2 9

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    
    // 初始化矩阵
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // 处理q次操作
    for (int k = 0; k < q; k++) {
        int t, x;
        cin >> t >> x;
        x--; // 转换为0-based索引
        
        if (t == 1) {
            // 第x行向右循环移位1位
            int temp = matrix[x][n-1];
            for (int j = n-1; j > 0; j--) {
                matrix[x][j] = matrix[x][j-1];
            }
            matrix[x][0] = temp;
        } else if (t == 2) {
            // 第x列向上循环移位1位
            int temp = matrix[0][x];
            for (int i = 0; i < n-1; i++) {
                matrix[i][x] = matrix[i+1][x];
            }
            matrix[n-1][x] = temp;
        }
    }
    
    // 输出结果矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j];
            if (j < n-1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```


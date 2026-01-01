

## [88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)

给你两个按 **非递减顺序** 排列的整数数组 `nums1` 和 `nums2`，另有两个整数 `m` 和 `n` ，分别表示 `nums1` 和 `nums2` 中的元素数目。

请你 **合并** `nums2` 到 `nums1` 中，使合并后的数组同样按 **非递减顺序** 排列。

**注意：**最终，合并后数组不应由函数返回，而是存储在数组 `nums1` 中。为了应对这种情况，`nums1` 的初始长度为 `m + n`，其中前 `m` 个元素表示应合并的元素，后 `n` 个元素为 `0` ，应忽略。`nums2` 的长度为 `n` 。

```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int>::reverse_iterator it1 = nums1.rbegin() + n;
        vector<int>::reverse_iterator it2 = nums2.rbegin();
        vector<int>::reverse_iterator it3 = nums1.rbegin();

        while(it1 != nums1.rend() && it2 != nums2.rend() && it3 != nums1.rend())
        {
            if (*it1 > *it2){
                *it3 = *it1;
                it1++;
            }
            else{
                *it3 = *it2;
                it2++;
            }
            it3++;
        }

        // 说明nums2里面还有剩余元素，直接复制到num1最前面
        while(it2 != nums2.rend() && it3 != nums1.rend())
        {
            *it3 = *it2;
            it3++;
            it2++;
        }

        // int i = m - 1;  // nums1有效部分的最后一个元素
        // int j = n - 1;  // nums2的最后一个元素
        // int k = m + n - 1;  // nums1的最后一个位置
        
        // // 从后向前合并
        // while (i >= 0 && j >= 0) {
        //     if (nums1[i] > nums2[j]) {
        //         nums1[k] = nums1[i];
        //         i--;
        //     } else {
        //         nums1[k] = nums2[j];
        //         j--;
        //     }
        //     k--;
        // }
        
        // // 如果nums2还有剩余元素，复制到nums1的前面
        // while (j >= 0) {
        //     nums1[k] = nums2[j];
        //     j--;
        //     k--;
        // }
        // // 如果nums1还有剩余元素，它们已经在正确的位置，不需要移动

    }
};
```






## [27. 移除元素](https://leetcode.cn/problems/remove-element/)

给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素。元素的顺序可能发生改变。然后返回 `nums` 中与 `val` 不同的元素的数量。

假设 `nums` 中不等于 `val` 的元素数量为 `k`，要通过此题，您需要执行以下操作：

- 更改 `nums` 数组，使 `nums` 的前 `k` 个元素包含不等于 `val` 的元素。`nums` 的其余元素和 `nums` 的大小并不重要。
- 返回 `k`。

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        vector<int>::iterator it1 = nums.begin();
        vector<int>::iterator it2 = nums.end() - 1;
        int k = 0;
        while(it1 != nums.end() && it1 != it2)
        {
            if(*it1 == val)
            {
                k++;
                if (*it2 != val)
                {
                    *it1 = *it2;
                    it1++;
                    it2--;
                }
                else{
                    it2--;
                }
            }
            else{
                if (*it2 == val)
                {
                    it2--;
                    k++;
                }
                it1++;
            }
            // 针对偶数长度的数组情况
            if (it1-1 == it2) break;
        }
        if (it1 == it2)
        {
            if (*it1 == val)
            {
                k++;
            }
        }
        k = nums.size() - k;
        return k;
    }
};
```



## [26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)

给你一个 **非严格递增排列** 的数组 `nums` ，请你**[ 原地](http://baike.baidu.com/item/原地算法)** 删除重复出现的元素，使每个元素 **只出现一次** ，返回删除后数组的新长度。元素的 **相对顺序** 应该保持 **一致** 。然后返回 `nums` 中唯一元素的个数。

考虑 `nums` 的唯一元素的数量为 `k`。去重后，返回唯一元素的数量 `k`。

`nums` 的前 `k` 个元素应包含 **排序后** 的唯一数字。下标 `k - 1` 之后的剩余元素可以忽略。

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();

        vector<int>::iterator it1 = nums.begin();
        vector<int>::iterator itRaw = nums.begin();
        vector<int>::iterator it2 = nums.begin() + 1;

        int k = 1;
        while(it2 != nums.end())
        {
            if (*it1 == *it2)
            {
                it2++;
            }
            else
            {
                itRaw++;
                *itRaw = *it2;
                it1 = it2;
                k++;
                it2++;
            }

        }

        return k;
        
    }
};
```



## [80. 删除有序数组中的重复项 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/)

给你一个有序数组 `nums` ，请你**[ 原地](http://baike.baidu.com/item/原地算法)** 删除重复出现的元素，使得出现次数超过两次的元素**只出现两次** ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 **[原地 ](https://baike.baidu.com/item/原地算法)修改输入数组** 并在使用 O(1) 额外空间的条件下完成。

**说明：**

为什么返回数值是整数，但输出的答案是数组呢？

请注意，输入数组是以**「引用」**方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

```
// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

 

**示例 1：**

```
输入：nums = [1,1,1,2,2,3]
输出：5, nums = [1,1,2,2,3]
解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。 不需要考虑数组中超出新长度后面的元素。
```

**示例 2：**

```
输入：nums = [0,0,1,1,1,1,2,3,3]
输出：7, nums = [0,0,1,1,2,3,3]
解释：函数应返回新长度 length = 7, 并且原数组的前七个元素被修改为 0, 0, 1, 1, 2, 3, 3。不需要考虑数组中超出新长度后面的元素。
```



```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();

        vector<int>::iterator it1 = nums.begin() + 2;
        vector<int>::iterator it2 = nums.begin() + 2;

        int k = 2;
        for (;it1 != nums.end(); it1++)
        {
            if (*it1 != *(it2 - 2))
            {
                *it2 = *it1;
                it2++;
                k++;
            }
        }
        return k;

    }
};
```





## [169. 多数元素](https://leetcode.cn/problems/majority-element/)

给定一个大小为 `n` 的数组 `nums` ，返回其中的多数元素。多数元素是指在数组中出现次数 **大于** `⌊ n/2 ⌋` 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

 

**示例 1：**

```
输入：nums = [3,2,3]
输出：3
```

**示例 2：**

```
输入：nums = [2,2,1,1,1,2,2]
输出：2
```



```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {

        // 使用哈希表
        // unordered_map<int, int> counts;
        // int majorty = 0;
        // int maxCount = 0;
        // for (int num : nums)
        // {
        //     counts[num]++;
        //     if (counts[num] > maxCount)
        //     {
        //         maxCount = counts[num];
        //         majorty = num;
        //     }
        // }

        // return majorty;

        // 使用投票算法
        int Candidate = nums[0];
        int count = 1;

        for (vector<int>::iterator it = nums.begin() + 1; it != nums.end(); ++it)
        {
            if (count == 0)
            {
                Candidate = *it;
                count = 1;
            }
            else if (*it == Candidate)
            {
                count++;
            }
            else
            {
                count--;
            }
        }

        return Candidate;


    }
};
```



## [189. 轮转数组](https://leetcode.cn/problems/rotate-array/)

给定一个整数数组 `nums`，将数组中的元素向右轮转 `k` 个位置，其中 `k` 是非负数。

**示例 1:**

```
输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右轮转 1 步: [7,1,2,3,4,5,6]
向右轮转 2 步: [6,7,1,2,3,4,5]
向右轮转 3 步: [5,6,7,1,2,3,4]
```

**示例 2:**

```
输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释: 
向右轮转 1 步: [99,-1,-100,3]
向右轮转 2 步: [3,99,-1,-100]
```

```c++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // 使用3次翻转，第一次翻转整个数组，第二次翻转前K个元素，第三次翻转剩余元素
        int n = nums.size();
        k = k % n;      // 取模，因为翻转n次等同于不翻转
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```



## [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)

给定一个数组 `prices` ，它的第 `i` 个元素 `prices[i]` 表示一支给定股票第 `i` 天的价格。

你只能选择 **某一天** 买入这只股票，并选择在 **未来的某一个不同的日子** 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 `0` 。

**示例 1：**

```
输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
```

**示例 2：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
```

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;

        // 依旧使用投票算法
        vector<int>::iterator it1 = prices.begin();
        vector<int>::iterator it2 = prices.begin() + 1;
        
        int val = 0;
        int minVal = *it1;
        while(it2 != prices.end())
        {
            if (*it1 < *it2)
            {
                int temp = *it2 - *it1;
                val = temp > val ? temp : val;
            }
            else
            {
                it1 = it2;
            }
            it2++;
        }
        return val;


    }
};
```



## [122. 买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/)

给你一个整数数组 `prices` ，其中 `prices[i]` 表示某支股票第 `i` 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 **最多** 只能持有 **一股** 股票。然而，你可以在 **同一天** 多次买卖该股票，但要确保你持有的股票不超过一股。

返回 *你能获得的 **最大** 利润* 。

 

**示例 1：**

```
输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3。
最大总利润为 4 + 3 = 7 。
```

**示例 2：**

```
输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
最大总利润为 4 。
```

**示例 3：**

```
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0。
```

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;

        vector<int>::iterator it1 = prices.begin();
        vector<int>::iterator it2 = prices.begin() + 1;

        int profit = 0;
        int minVal = *it1;
        int tempProfit = 0;

        while(it2 != prices.end())
        {
            if (*it1 < *it2)
            {
                int temp = *it2 - *it1;
                if (temp < tempProfit)
                {
                    profit += tempProfit;
                    it1 = it2;
                    tempProfit = 0;
                }
                else{
                    tempProfit = temp;
                }
            }
            else
            {
                profit += tempProfit;
                tempProfit = 0;
                it1 = it2;
            }

            it2++;
        }

        // 这条代码是为了避免那中一路走高的情况
        profit += tempProfit;

        return profit;

    }
};
```



## [55. 跳跃游戏](https://leetcode.cn/problems/jump-game/)

给你一个非负整数数组 `nums` ，你最初位于数组的 **第一个下标** 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
```

**示例 2：**

```
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
```

 

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {

        int n = nums.size();
        int far = 0;

        for (int i = 0; i < n; i++)
        {
            if (i > far)
            {
                return false;
            }

            // 贪心算法，记录每个位置能到达的最远下标，然后将最远处保留比较
            far = max(far, i + nums[i]);
            if (far >= n-1)
            {
                return true;
            }
        }

        return true;
        
    }
};
```



## [45. 跳跃游戏 II](https://leetcode.cn/problems/jump-game-ii/)

给定一个长度为 `n` 的 **0 索引**整数数组 `nums`。初始位置在下标 0。

每个元素 `nums[i]` 表示从索引 `i` 向后跳转的最大长度。换句话说，如果你在索引 `i` 处，你可以跳转到任意 `(i + j)` 处：

- `0 <= j <= nums[i]` 且
- `i + j < n`

返回到达 `n - 1` 的最小跳跃次数。测试用例保证可以到达 `n - 1`。

 

**示例 1:**

```
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
```

**示例 2:**

```
输入: nums = [2,3,0,1,4]
输出: 2
```

 ```c++
 class Solution {
 public:
     int jump(vector<int>& nums) {
         int jums = 0;
         int current_end = 0;
         int farthest = 0;
         int n = nums.size();
 
         for (int i = 0; i < n - 1; i++)
         {
             farthest = max(farthest, i + nums[i]);
 
             if (i == current_end)
             {
                 jums++;
                 current_end = farthest;
 
                 if (current_end >= n-1)
                 {
                     break;
                 }
             }
 
         }
         return jums;
 
     }
 };
 ```



## [274. H 指数](https://leetcode.cn/problems/h-index/)

给你一个整数数组 `citations` ，其中 `citations[i]` 表示研究者的第 `i` 篇论文被引用的次数。计算并返回该研究者的 **`h` 指数**。

根据维基百科上 [h 指数的定义](https://baike.baidu.com/item/h-index/3991452?fr=aladdin)：`h` 代表“高引用次数” ，一名科研人员的 `h` **指数** 是指他（她）至少发表了 `h` 篇论文，并且 **至少** 有 `h` 篇论文被引用次数大于等于 `h` 。如果 `h` 有多种可能的值，**`h` 指数** 是其中最大的那个。

**示例 1：**

```
输入：citations = [3,0,6,1,5]
输出：3 
解释：给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
     由于研究者有 3 篇论文每篇 至少 被引用了 3 次，其余两篇论文每篇被引用 不多于 3 次，所以她的 h 指数是 3。
```

**示例 2：**

```
输入：citations = [1,3,1]
输出：1
```

 

```c++
class Solution {
public:
    int hIndex(vector<int>& citations) {
        // 排序法
        // int n = citations.size();

        // // 从小到大排序
        // sort(citations.begin(), citations.end());

        // for(int i = 0; i < n; i++)
        // {
        //     if (citations[i] >= n-i)
        //     {
        //         return n-i;
        //     }
        // }

        // return 0;

        // 计数排序法
        int n = citations.size();
        if (n == 0) return 0;

        // 创建统计数组
        vector<int> count(n+1);

        // 统计各引用次数的论文
        for (int c : citations)
        {
            if (c >= n)
            {
                count[n] += 1;  // 超过n的标记为n
            }
            else
            {
                count[c] += 1;
            }
        }

        // 从高到低累加论文数
        int total = 0;
        for (int i = n; i >= 0; i--)
        {
            total += count[i];
            if (total >= i)
            {
                return i;
            }
        }

        return 0;


    }
};
```




## [380. O(1) 时间插入、删除和获取随机元素](https://leetcode.cn/problems/insert-delete-getrandom-o1/)

实现`RandomizedSet` 类：

- `RandomizedSet()` 初始化 `RandomizedSet` 对象
- `bool insert(int val)` 当元素 `val` 不存在时，向集合中插入该项，并返回 `true` ；否则，返回 `false` 。
- `bool remove(int val)` 当元素 `val` 存在时，从集合中移除该项，并返回 `true` ；否则，返回 `false` 。
- `int getRandom()` 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 **相同的概率** 被返回。

你必须实现类的所有函数，并满足每个函数的 **平均** 时间复杂度为 `O(1)` 。

 

**示例：**

```
输入
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
输出
[null, true, false, true, 2, true, false, 2]

解释
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
randomizedSet.insert(2); // 2 已在集合中，所以返回 false 。
randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
```

```c++
class RandomizedSet {
public:
    RandomizedSet()
    {
    }
    
    bool insert(int val) {
        // 插入元素，如果集合中已经存在，则返回false
        if (valToIndex.find(val) != valToIndex.end())
        {
            return false;
        }

        nums.push_back(val);
        // 在哈希表中记录该值的索引
        valToIndex[val] = nums.size() -1;
        return true;
    }
    
    bool remove(int val) {
        // 如果元素不存在，返回false
        if (valToIndex.find(val) == valToIndex.end())
        {
            return false;
        }

        // 获取要删除的元素索引
        int index = valToIndex[val];
        // 获取数组最后一个元素
        int lastVal = nums.back();

        // 将最后一个元素移动到要删除元素的位置
        nums[index] = lastVal;
        // 跟新hash
        valToIndex[lastVal] = index;

        // 删除最后一个元素
        nums.pop_back();
        // 哈希表删除其中的映射
        valToIndex.erase(val);
        return true;

    }
    
    int getRandom() {
        if (nums.empty())
        {
            throw std::runtime_error("set is empty");
        }

        // 生成随机索引
        int randomIndex = rand()%nums.size();
        return nums[randomIndex];

    }

private:
    unordered_map<int, int> valToIndex;     // 元素值到索引的映射
    vector<int> nums;       // 存储元素


};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```





## [238. 除自身以外数组的乘积](https://leetcode.cn/problems/product-of-array-except-self/)



给你一个整数数组 `nums`，返回 数组 `answer` ，其中 `answer[i]` 等于 `nums` 中除 `nums[i]` 之外其余各元素的乘积 。

题目数据 **保证** 数组 `nums`之中任意元素的全部前缀元素和后缀的乘积都在 **32 位** 整数范围内。

请 **不要使用除法，**且在 `O(n)` 时间复杂度内完成此题。

**示例 1:**

```
输入: nums = [1,2,3,4]
输出: [24,12,8,6]
```

**示例 2:**

```
输入: nums = [-1,1,0,-3,3]
输出: [0,0,9,0,0]
```

```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // 分别记录每一个元素左边乘积和右边乘积
        // int n = nums.size();
        // vector<int> res(n);
        // vector<int>::iterator it = res.begin();
        // vector<int>::iterator itNums = nums.begin();

        // while(it != res.end() && itNums != nums.end())
        // {
        //     if (itNums == nums.begin())
        //     {
        //         *it = std::ranges::fold_left(itNums + 1, nums.end(), 1, std::multiplies{});
        //     }
        //     else if (itNums == nums.end()-1)
        //     {
        //         *it = std::ranges::fold_left(nums.begin(), itNums, 1, std::multiplies{});
        //     }
        //     else
        //     {
        //         *it = std::ranges::fold_left(nums.begin(), itNums, 1, std::multiplies{}) *
        //                 std::ranges::fold_left(itNums + 1, nums.end(), 1, std::multiplies{});
        //     }

        //     it++;
        //     itNums++;
            
        // }

        // return res;

        // 两次遍历
        // int n = nums.size();
        // vector<int> res(n, 1);
        // int left = 1;
        // int right = 1;

        // vector<int>::iterator it = res.begin();
        // vector<int>::iterator itNums = nums.begin();

        // while(it != res.end() && itNums != nums.end())
        // {
        //     if (itNums == nums.begin())
        //     {
        //         it++;
        //         itNums++;
        //         continue;
        //     }

        //     left = *(itNums -1)*left;
        //     *it = left;
        //     it++;
        //     itNums++;
        // }

        // // 然后反向遍历
        // vector<int>::reverse_iterator rit = res.rbegin();
        // vector<int>::reverse_iterator ritNums = nums.rbegin();

        // while(rit != res.rend() && ritNums != nums.rend())
        // {
        //     if (ritNums == nums.rbegin())
        //     {
        //         rit++;
        //         ritNums++;
        //         continue;
        //     }

        //     right = *(ritNums-1) * right;
        //     *rit = *rit * right;
        //     rit++;
        //     ritNums++;

        // }

        // return res;

        // 使用C++20新特性优化
        // int n = nums.size();
        // vector<int>answer(n, 1);

        // // 使用views::iota创建索引序列
        // // 计算左侧乘积
        // int left = 1;
        // for (int i : std::views::iota(0, n))
        // {
        //     answer[i] = left;
        //     left *= nums[i];
        // }

        // // 计算右侧乘积
        // int right = 1;
        // for (int i : std::views::iota(0, n) | std::views::reverse)
        // {
        //     answer[i] *= right;
        //     right *= nums[i];
        // }

        // return answer;

        // 使用std::exclusive_scan的高性能版本
        // int n = nums.size();
        // std::vector<int> left(n, 1);
        // std::vector<int> right(n, 1);
        // std::vector<int> answer(n);

        // // 计算从左到右的前缀积（不含自身）
        // std::exclusive_scan(nums.begin(), nums.end(), left.begin(), 1, std::multiplies{});

        // // 计算从右到左的后缀积（不含自身）
        // std::exclusive_scan(nums.rbegin(), nums.rend(), right.rbegin(), 1, std::multiplies{});

        // // 合并结果
        // for (int i = 0; i < n; i++)
        // {
        //     answer[i] = left[i] * right[i];
        // }

        // return answer;

        // 同时计算左右乘积，单遍扫描
        int n = nums.size();
        vector<int> answer(n, 1);
        int left = 1, right = 1;

        for (int i = 0; i < n; i++)
        {
            // 左侧
            answer[i] *= left;
            left *= nums[i];

            // 右侧
            answer[n-1-i] *= right;
            right *= nums[n-i-1];

        }

        return answer;

    }
};
```




## [134. 加油站](https://leetcode.cn/problems/gas-station/)

在一条环路上有 `n` 个加油站，其中第 `i` 个加油站有汽油 `gas[i]` 升。

你有一辆油箱容量无限的的汽车，从第 `i` 个加油站开往第 `i+1` 个加油站需要消耗汽油 `cost[i]` 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 `gas` 和 `cost` ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 `-1` 。如果存在解，则 **保证** 它是 **唯一** 的。

 

**示例 1:**

```
输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
```

**示例 2:**

```
输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。
```

```c++
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // 使用贪心算法
        int start = 0;
        int totalGas = 0, currentGas = 0;
        int n = gas.size();

        for (int i = 0; i < n; i++)
        {
            totalGas += gas[i] - cost[i];
            currentGas += gas[i] - cost[i];     // 当前油量

            // 如果当前油量为负，表示不能从该点到达下一站，重置起点，重置当前油量
            if (currentGas < 0)
            {
                start = i +1;
                currentGas = 0;
            }
        }

        return totalGas >= 0 ? start : -1;

    }
};
```





## [135. 分发糖果](https://leetcode.cn/problems/candy/)

`n` 个孩子站成一排。给你一个整数数组 `ratings` 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

- 每个孩子至少分配到 `1` 个糖果。
- 相邻两个孩子中，评分更高的那个会获得更多的糖果。

请你给每个孩子分发糖果，计算并返回需要准备的 **最少糖果数目** 。

**示例 1：**

```
输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
```

**示例 2：**

```
输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
```

```c++
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n <= 1) return n;
        if (n == 2) return ratings[0] == ratings[1] ? 2 : 3;

        // // 三次遍历
        // vector<int> left(n, 1);
        // vector<int> right(n, 1);

        // for (int i = 1; i < n; i++)
        // {
        //     if (ratings[i] > ratings[i-1])
        //     {
        //         left[i] = left[i-1] + 1;
        //     }
        // }

        // for (int i = n -2; i >= 0; i--)
        // {
        //     if (ratings[i] > ratings[i+1])
        //     {
        //         right[i] = right[i+1]+1;
        //     }
        // }

        // int candies = 0;
        // for (int i = 0; i < n; i++)
        // {
        //     candies += std::max(left[i], right[i]);
        // }

        // return candies;

        // 单次遍历的优化版本
        int candies = 0;
        int up = 0, down = 0;
        int old_slope = 0;      // 前一段的斜率

        for (int i = 1; i < n; i++) {
            // 处理平坡：结束当前坡，开始新的坡
            if (ratings[i] == ratings[i-1]) {
                candies += count(up) + count(down) + max(up, down);
                up = 0;
                down = 0;
                candies++;  // 平坡本身
                continue;
            }
            
            if (ratings[i] > ratings[i-1]) {
                // 如果是下降转上升，结束上一个坡
                if (down > 0) {
                    candies += count(up) + count(down) + max(up, down);
                    up = 0;
                    down = 0;
                }
                up++;
            } else { // ratings[i] < ratings[i-1]
                down++;
            }
        }
        
        // 加上最后一个坡
        candies += count(up) + count(down) + max(up, down) + 1;
        return candies;

    }

private:
    // 计算1+2+3+...+n
    int count(int n)
    {
        return n*(n+1)/2;
    }

};
```



## [42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/)

给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

 

**示例 1：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2018/10/22/rainwatertrap.png)

```
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
```

**示例 2：**

```
输入：height = [4,2,0,3,2,5]
输出：9
```

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        
        // // 3次遍历(简化后可以两次遍历)
        // int n = height.size();
        // vector<int> left(n);
        // vector<int> right(n);

        // // 从左边开始蓄水
        // int leftHeight = 0;
        // for (int i = 0; i < n; i++)
        // {
        //     leftHeight = max(leftHeight, height[i]);
        //     if (height[i] < leftHeight)
        //     {
        //         left[i] = leftHeight - height[i];
        //     }
        // }
        // // 从右边开始蓄水, 然后比较两边蓄水，取每个位置的小值作为结果
        // int rightHeight = 0;
        // int total = 0;
        // for (int i = n -1; i >= 0; i--)
        // {
        //     rightHeight = max(rightHeight, height[i]);
        //     if (height[i] < rightHeight)
        //     {
        //         right[i] = rightHeight - height[i];
        //     }

        //     total += min(left[i], right[i]);
        // }

        // return total;

        // 优化方案，双指针法，空间优化到O(1)
        int n = height.size();
        if (n < 3) return 0;

        int left = 0, right = n-1;
        int left_max = 0, right_max = 0;
        int water = 0;

        while(left < right)
        {
            if (height[left] < height[right])
            {
                // 左指针移动
                if (height[left] >= left_max)
                {
                    left_max = height[left];
                }
                else
                {
                    water += left_max - height[left];
                }
                left++;
            }
            else
            {
                // 右指针移动
                if (height[right] >= right_max)
                {
                    right_max = height[right];
                }
                else
                {
                    water += right_max - height[right];
                }
                right--;
            }
        }
        return water;

        // // 单调栈法（另一种思路）
        // int n = height.size();
        // if (n < 3) return 0;
        
        // stack<int> stk;  // 存储索引，栈底到栈顶高度递减
        // int water = 0;
        
        // for (int i = 0; i < n; i++) {
        //     while (!stk.empty() && height[i] > height[stk.top()]) {
        //         int bottom = stk.top();
        //         stk.pop();
                
        //         if (stk.empty()) break;
                
        //         int left = stk.top();
        //         int width = i - left - 1;
        //         int bounded_height = min(height[i], height[left]) - height[bottom];
                
        //         water += width * bounded_height;
        //     }
        //     stk.push(i);
        // }
        
        // return water;


    }
};
```



## [13. 罗马数字转整数](https://leetcode.cn/problems/roman-to-integer/)

罗马数字包含以下七种字符: `I`， `V`， `X`， `L`，`C`，`D` 和 `M`。

```
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

例如， 罗马数字 `2` 写做 `II` ，即为两个并列的 1 。`12` 写做 `XII` ，即为 `X` + `II` 。 `27` 写做 `XXVII`, 即为 `XX` + `V` + `II` 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 `IIII`，而是 `IV`。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 `IX`。这个特殊的规则只适用于以下六种情况：

- `I` 可以放在 `V` (5) 和 `X` (10) 的左边，来表示 4 和 9。
- `X` 可以放在 `L` (50) 和 `C` (100) 的左边，来表示 40 和 90。 
- `C` 可以放在 `D` (500) 和 `M` (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。

**示例 1:**

```
输入: s = "III"
输出: 3
```

**示例 2:**

```
输入: s = "IV"
输出: 4
```

**示例 3:**

```
输入: s = "IX"
输出: 9
```

**示例 4:**

```
输入: s = "LVIII"
输出: 58
解释: L = 50, V= 5, III = 3.
```

**示例 5:**

```
输入: s = "MCMXCIV"
输出: 1994
解释: M = 1000, CM = 900, XC = 90, IV = 4.
```

```c++
class Solution {
public:
    int romanToInt(string s) {
        
        int ret = 0;
        int prev = 0;

        // 从右向左遍历
        for (int i = s.size() - 1; i >= 0; i--)
        {
            int current = getValue(s[i]);
            if (current < prev)
            {
                ret -= current;
            }
            else
            {
                ret += current;
            }

            prev = current;
        }

        return ret;
    }

private:
    int getValue(char c)
    {
        switch(c)
        {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }


};
```



## [12. 整数转罗马数字](https://leetcode.cn/problems/integer-to-roman/)

七个不同的符号代表罗马数字，其值如下：

| 符号 | 值   |
| ---- | ---- |
| I    | 1    |
| V    | 5    |
| X    | 10   |
| L    | 50   |
| C    | 100  |
| D    | 500  |
| M    | 1000 |

罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：

- 如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
- 如果该值以 4 或 9 开头，使用 **减法形式**，表示从以下符号中减去一个符号，例如 4 是 5 (`V`) 减 1 (`I`): `IV` ，9 是 10 (`X`) 减 1 (`I`)：`IX`。仅使用以下减法形式：4 (`IV`)，9 (`IX`)，40 (`XL`)，90 (`XC`)，400 (`CD`) 和 900 (`CM`)。
- 只有 10 的次方（`I`, `X`, `C`, `M`）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (`V`)，50 (`L`) 或 500 (`D`)。如果需要将符号附加4次，请使用 **减法形式**。

给定一个整数，将其转换为罗马数字。

 

**示例 1：**

**输入：**num = 3749

**输出：** "MMMDCCXLIX"

**解释：**

```
3000 = MMM 由于 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC 由于 500 (D) + 100 (C) + 100 (C)
  40 = XL 由于 50 (L) 减 10 (X)
   9 = IX 由于 10 (X) 减 1 (I)
注意：49 不是 50 (L) 减 1 (I) 因为转换是基于小数位
```

**示例 2：**

**输入：**num = 58

**输出：**"LVIII"

**解释：**

```
50 = L
 8 = VIII
```

**示例 3：**

**输入：**num = 1994

**输出：**"MCMXCIV"

**解释：**

```
1000 = M
 900 = CM
  90 = XC
   4 = IV
```

```c++
class Solution {
// public:
//     string intToRoman(int num) {
//         // 将数字拆分成可映射的数组
//         vector<int> roman;
//         int Base = 1;
//         while(num != 0)
//         {
//             int val = num%10 * Base;
//             if (romanMap.find(val) != romanMap.end())
//             {
//                 roman.push_back(val);
//             }
//             else
//             {
//                 if (val < Base * 5)
//                 {
//                     for (int i = Base; i <= val; i+=Base)
//                     {
//                         roman.push_back(Base);
//                     }
//                 }
//                 else if (val > Base * 5)
//                 {
//                     for (int i = Base; i <= val - (Base*5); i+=Base)
//                     {
//                         roman.push_back(Base);
//                     }
//                     roman.push_back(Base*5);
//                 }
//             }
            
//             num /= 10;
//             Base *= 10;
//         }
//         std::reverse(roman.begin(), roman.end());   // 从高位到低排
//         string ret{};
//         for (int n: roman)
//         {
//             ret+=romanMap[n];
//         }
//         return ret;
//     }

// private:
//     std::unordered_map<int, string> romanMap = {
//             {9, "IX"},
//             {90, "XC"},
//             {900, "CM"},
//             {4, "IV"},
//             {40, "XL"},
//             {400, "CD"},
//             {1, "I"},
//             {5, "V"},
//             {10, "X"},
//             {50, "L"},
//             {100, "C"},
//             {500, "D"},
//             {1000, "M"}
//     };

public:
    string intToRoman(int num) {
        // // 使用贪心算法
        // vector<int> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        // vector<string> symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        // string result;
        // for (int i = 0; i < values.size() && num > 0; i++)
        // {
        //     while(num >= values[i])
        //     {
        //         num -= values[i];
        //         result += symbols[i];
        //     }
        // }

        // return result;

        // 直接硬编码
        string thousands[] = {"", "M", "MM", "MMM"};
        string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
        string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

        return thousands[num / 1000] + hundreds[(num % 1000) / 100] + tens[(num % 100) /10] + ones[num % 10];

    }


};

```





## [58. 最后一个单词的长度](https://leetcode.cn/problems/length-of-last-word/)

给你一个字符串 `s`，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 **最后一个** 单词的长度。

**单词** 是指仅由字母组成、不包含任何空格字符的最大子字符串。

**示例 1：**

```
输入：s = "Hello World"
输出：5
解释：最后一个单词是“World”，长度为 5。
```

**示例 2：**

```
输入：s = "   fly me   to   the moon  "
输出：4
解释：最后一个单词是“moon”，长度为 4。
```

**示例 3：**

```
输入：s = "luffy is still joyboy"
输出：6
解释：最后一个单词是长度为 6 的“joyboy”。
```

```c++
class Solution {
public:
    int lengthOfLastWord(string s) {
        // 直接反序遍历取最后一个单词
        string::reverse_iterator it = s.rbegin();
        int n = 0;
        int leng = 0;
        while (it != s.rend() && n < 2)
        {
            if (*it == ' ')
            {
                n = leng > 0 ? n + 1 : n;
            }
            else
            {
                n = n == 0 ? 1:n;
                leng++;
            }
            it++;
        }
        return leng;
    }
};
```



## [14. 最长公共前缀](https://leetcode.cn/problems/longest-common-prefix/)

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 `""`。

**示例 1：**

```
输入：strs = ["flower","flow","flight"]
输出："fl"
```

**示例 2：**

```
输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
```

 

**提示：**

- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- `strs[i]` 如果非空，则仅由小写英文字母组成

```c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix = strs[0];
        for (string& s : strs)
        {
            if (s.size() == 0)
            {
                return "";
            }
            if (prefix == s) continue;
            int n = min(s.size(), prefix.size());
            string temp = "";
            for (int i = 0; i < n; i++)
            {
                if (s[i] == prefix[i])
                {
                    temp+=s[i];
                }
                else
                {
                    if (i == 0)
                    {
                        return "";
                    }
                    break;
                }
            }
            prefix = temp;
        }

        return prefix;
    }
};
```



## [151. 反转字符串中的单词](https://leetcode.cn/problems/reverse-words-in-a-string/)

给你一个字符串 `s` ，请你反转字符串中 **单词** 的顺序。

**单词** 是由非空格字符组成的字符串。`s` 中使用至少一个空格将字符串中的 **单词** 分隔开。

返回 **单词** 顺序颠倒且 **单词** 之间用单个空格连接的结果字符串。

**注意：**输入字符串 `s`中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

 

**示例 1：**

```
输入：s = "the sky is blue"
输出："blue is sky the"
```

**示例 2：**

```
输入：s = "  hello world  "
输出："world hello"
解释：反转后的字符串中不能存在前导空格和尾随空格。
```

**示例 3：**

```
输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
```

 

**提示：**

- `1 <= s.length <= 104`
- `s` 包含英文大小写字母、数字和空格 `' '`
- `s` 中 **至少存在一个** 单词

```c++
class Solution {
public:
    string reverseWords(string s) {
        // std::vector<string_view> str_view = split_string_view(s, ' ');
        // string ret = "";
        // for (vector<string_view>::reverse_iterator it = str_view.rbegin(); it != str_view.rend(); ++it)
        // {
        //     if (!it->empty())
        //     {
        //         if (!ret.empty())
        //         {
        //             ret += " ";
        //         }
        //         ret.append(it->data(), it->size());
        //     }
        // }

        // return ret;

        // 原地翻转
        reverse(s.begin(), s.end());

        int n = s.size();
        int idx = 0;

        for (int start = 0; start < n; ++start)
        {
            if (s[start] != ' ')
            {
                // 填充一个合适的位置
                if (idx != 0)
                {
                    s[idx++] = ' ';
                }
                int end = start;
                while (end < n && s[end] != ' ')
                {
                    s[idx++] = s[end++];
                }

                // 然后翻转当前单词
                reverse(s.begin() + idx - (end - start), s.begin() + idx);
                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;

    }

private:
    // 零拷贝，高性能的字符串分隔
    std::vector<std::string_view> split_string_view(std::string_view s, char delimiter)
    {
        std::vector<std::string_view> result;
        size_t start = 0;
        size_t end = 0;

        while ((end = s.find(delimiter, start)) != string_view::npos)
        {
            if (end > start)
            {
                // 避免出现空单词
                result.push_back(s.substr(start, end - start));
            }
            start = end + 1;
        }

        // 添加最后一个子串
        if (start < s.size())
        {
            result.push_back(s.substr(start));
        }
        return result;
    }


};
```



## [6. Z 字形变换](https://leetcode.cn/problems/zigzag-conversion/)

将一个给定字符串 `s` 根据给定的行数 `numRows` ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 `"PAYPALISHIRING"` 行数为 `3` 时，排列如下：

```
P   A   H   N
A P L S I I G
Y   I   R
```

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如：`"PAHNAPLSIIGYIR"`。

请你实现这个将字符串进行指定行数变换的函数：

```
string convert(string s, int numRows);
```

 

**示例 1：**

```
输入：s = "PAYPALISHIRING", numRows = 3
输出："PAHNAPLSIIGYIR"
```

**示例 2：**

```
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P     I    N
A   L S  I G
Y A   H R
P     I
```

**示例 3：**

```
输入：s = "A", numRows = 1
输出："A"
```

 

**提示：**

- `1 <= s.length <= 1000`
- `s` 由英文字母（小写和大写）、`','` 和 `'.'` 组成
- `1 <= numRows <= 1000`

```c++
class Solution {
public:
    string convert(string s, int numRows) {
        // 模拟排布轨迹
        if (numRows == 1) return s;
        vector<string> rows(min(numRows, static_cast<int>(s.size())));
        bool down = true;
        int idx = 0;        // 当前字符所在的行
        for (int i = 0; i < s.size(); i++)
        {
            rows[idx] += s[i];
            if (idx == 0)
            {
                idx++;
                down = true;    // 向下
            }
            else if (idx == numRows-1)
            {
                idx--;
                down = false;   // 向上
            }
            else
            {
                idx = down ? idx + 1 : idx - 1;
            }
        }

        string result{};
        for (string str : rows)
        {
            result+=str;
        }
        return result;
    }
};
```



## [28. 找出字符串中第一个匹配项的下标](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/)

给你两个字符串 `haystack` 和 `needle` ，请你在 `haystack` 字符串中找出 `needle` 字符串的第一个匹配项的下标（下标从 0 开始）。如果 `needle` 不是 `haystack` 的一部分，则返回 `-1` 。



**示例 1：**

```
输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
```

**示例 2：**

```
输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
```

 

**提示：**

- `1 <= haystack.length, needle.length <= 104`
- `haystack` 和 `needle` 仅由小写英文字符组成

```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        // if (haystack.find(needle) != string::npos)
        if (haystack.contains(needle))
        {
            return haystack.find(needle);
        }
        else
        {
            return -1;
        }
    }
};
```





## [68. 文本左右对齐](https://leetcode.cn/problems/text-justification/)

给定一个单词数组 `words` 和一个长度 `maxWidth` ，重新排版单词，使其成为每行恰好有 `maxWidth` 个字符，且左右两端对齐的文本。

你应该使用 “**贪心算法**” 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 `' '` 填充，使得每行恰好有 *maxWidth* 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入**额外的**空格。

**注意:**

- 单词是指由非空格字符组成的字符序列。
- 每个单词的长度大于 0，小于等于 *maxWidth*。
- 输入单词数组 `words` 至少包含一个单词。

 

**示例 1:**

```
输入: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
输出:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
```

**示例 2:**

```
输入:words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
输出:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
解释: 注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
     因为最后一行应为左对齐，而不是左右两端对齐。       
     第二行同样为左对齐，这是因为这行只包含一个单词。
```

**示例 3:**

```
输入:words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]，maxWidth = 20
输出:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
```

 

```c++
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result{};
        int idx = 0;
        int currentLineCharLength = 0;
        int currentLineWorldLength = 0;
        int starIdx = 0;
        int entIdx = 0;
        int wordNumThisLine = 0;
        for (int i = 0; i < words.size(); i++)
        {
            int wordLength = words[i].size();
            
            if (currentLineCharLength + wordLength > maxWidth)
            {
                
                // 说明该单词不能添加到这一行
                // 那就将starIdx到endIdx这段单词组合进result中
                int spaceNum = maxWidth - currentLineWorldLength;   // 空格数
                int evlSpaceNum = spaceNum / max(wordNumThisLine - 1, 1);
                string NormalStr(evlSpaceNum, ' ');
                int mo = spaceNum%max(wordNumThisLine - 1, 1);
                // 然后将剩余空格全部分给第一个字符后面
                string str{};
                for (int j = starIdx; j <= entIdx; j++)
                {
                    str += words[j];
                    str += NormalStr;
                    if (mo > 0)
                    {
                        str += ' ';
                        mo--;
                    }
                }
                // 然后剔除多余字符
                str.erase(str.begin() + maxWidth, str.end());
                result.push_back(str);
                currentLineCharLength = 0;
                currentLineWorldLength = 0;
                wordNumThisLine = 0;
                starIdx = i;
                entIdx = i;

            }
            else if (currentLineCharLength + wordLength == maxWidth)
            {
                // 恰好能完美添加到这行，当然这种方式也说明从starIdx到endIdx之间的每一个单词都只需要一个空格分隔
                string str{};
                entIdx = i;
                for (int j = starIdx; j <= entIdx; j++)
                {
                    str += words[j];
                    if (j < entIdx)
                    {
                        str += ' ';
                    }
                }
                result.push_back(str);
                currentLineCharLength = 0;
                currentLineWorldLength = 0;
                wordNumThisLine = 0;
                starIdx = i+1;
                entIdx = i+1;
                continue;

            }

            // 能添加进来，但是不饱和，就贪心的添加进来，这种添加方式都自带一个空格
            currentLineCharLength += (wordLength + 1);
            currentLineWorldLength += wordLength;
            wordNumThisLine += 1;
            // 然后更新endIdx为当前索引
            entIdx = i;
            
        }

        if (currentLineCharLength != 0)
        {
            // 表示还有最后一行没有处理
            string str;
            string spacestr(maxWidth, ' ');
            for (int i = starIdx; i <= entIdx; i++)
            {
                str += words[i];
                if (i == entIdx)
                {
                    str += spacestr;
                }
                else
                {
                    str += ' ';
                }
                
            }
            str.erase(str.begin() + maxWidth, str.end());
            result.push_back(str);
        }

        return result;
    }
};
```





## [125. 验证回文串](https://leetcode.cn/problems/valid-palindrome/)

如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 **回文串** 。

字母和数字都属于字母数字字符。

给你一个字符串 `s`，如果它是 **回文串** ，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入: s = "A man, a plan, a canal: Panama"
输出：true
解释："amanaplanacanalpanama" 是回文串。
```

**示例 2：**

```
输入：s = "race a car"
输出：false
解释："raceacar" 不是回文串。
```

**示例 3：**

```
输入：s = " "
输出：true
解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
由于空字符串正着反着读都一样，所以是回文串。
```

 

**提示：**

- `1 <= s.length <= 2 * 105`
- `s` 仅由可打印的 ASCII 字符组成

```c++
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.size() <= 1) return true;
        int left = 0;
        int right = s.size() - 1;
        while(left < right)
        {
            char a = s[left];
            char b = s[right];
            if (a == b)
            {
                left++;
                right--;
                continue;
            }
            if (std::isalpha(a) && std::isalpha(b))
            {
                if (std::tolower(a) == std::tolower(b))
                {
                    left++;
                    right--;
                    continue;
                }
                else{
                    return false;
                }
            }
            if (std::isdigit(a) && std::isdigit(b))
            {
                if (a != b)
                {
                    return false;
                }
            }
            if ((std::isalpha(a) && std::isdigit(b)) || (std::isalpha(b) && std::isdigit(a)))
            {
                return false;
            }
            if (!std::isalpha(a) && !std::isdigit(a))
            {
                left++;
            }
            if (!std::isalpha(b) && !std::isdigit(b))
            {
                right--;
            }
        }
        return true;
    }

private:
    bool areEqualIgoreCase(char a, char b)
    {
        if (a == b) return true;
        if (std::isalpha(a) && std::isalpha(b))
        {
            return std::tolower(a) == std::tolower(b);
        }

        return false;
    }
};
```





## [392. 判断子序列](https://leetcode.cn/problems/is-subsequence/)

给定字符串 **s** 和 **t** ，判断 **s** 是否为 **t** 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，`"ace"`是`"abcde"`的一个子序列，而`"aec"`不是）。

**进阶：**

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

**致谢：**

特别感谢 [@pbrother ](https://leetcode.com/pbrother/)添加此问题并且创建所有测试用例。

 

**示例 1：**

```
输入：s = "abc", t = "ahbgdc"
输出：true
```

**示例 2：**

```
输入：s = "axc", t = "ahbgdc"
输出：false
```

 

**提示：**

- `0 <= s.length <= 100`
- `0 <= t.length <= 10^4`
- 两个字符串都只由小写字符组成。

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.size() == 0 && t.size() == 0) return true;
        if (s.size() > t.size()) return false;
        auto its = s.begin();
        auto itt = t.begin();
        while(its != s.end() && itt != t.end())
        {
            if (*its == *itt)
            {
                its++;
            }
            itt++;
        }

        return (its == s.end());

    }
};
```





## [167. 两数之和 II - 输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/)



给你一个下标从 **1** 开始的整数数组 `numbers` ，该数组已按 **非递减顺序排列** ，请你从数组中找出满足相加之和等于目标数 `target` 的两个数。如果设这两个数分别是 `numbers[index1]` 和 `numbers[index2]` ，则 `1 <= index1 < index2 <= numbers.length` 。

以长度为 2 的整数数组 `[index1, index2]` 的形式返回这两个整数的下标 `index1` 和 `index2`。

你可以假设每个输入 **只对应唯一的答案** ，而且你 **不可以** 重复使用相同的元素。

你所设计的解决方案必须只使用常量级的额外空间。

**示例 1：**

```
输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释：2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
```

**示例 2：**

```
输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2 与 4 之和等于目标数 6 。因此 index1 = 1, index2 = 3 。返回 [1, 3] 。
```

**示例 3：**

```
输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1 与 0 之和等于目标数 -1 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
```

 

**提示：**

- `2 <= numbers.length <= 3 * 104`
- `-1000 <= numbers[i] <= 1000`
- `numbers` 按 **非递减顺序** 排列
- `-1000 <= target <= 1000`
- **仅存在一个有效答案**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = numbers.size() - 1;
        while (i < j)
        {
            if (numbers[i] + numbers[j] == target) return vector<int>{i+1, j+1};
            if (numbers[i] + numbers[j] < target)
            {
                i++;
            }
            else if (numbers[i] + numbers[j] > target)
            {
                j--;
            }
        }

        return vector<int>();
    }
};
```



## [11. 盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/)

给定一个长度为 `n` 的整数数组 `height` 。有 `n` 条垂线，第 `i` 条线的两个端点是 `(i, 0)` 和 `(i, height[i])` 。

找出其中的两条线，使得它们与 `x` 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

**说明：**你不能倾斜容器。

 

**示例 1：**

![img](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/07/25/question_11.jpg)

```
输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
```

**示例 2：**

```
输入：height = [1,1]
输出：1
```

 

**提示：**

- `n == height.length`
- `2 <= n <= 105`
- `0 <= height[i] <= 104`

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxwater = 0;
        int left = 0;
        int right = height.size() - 1;

        while (left < right && left < (height.size() - 1))
        {
            int currentArea = (right - left) * min(height[left], height[right]);
            maxwater = max(maxwater, currentArea);
            
            if (height[left] >= height[right])
            {
                right--;
            }
            else
            {
                left++;
            }

        }

        return maxwater;
        
    }
};
```





## [15. 三数之和](https://leetcode.cn/problems/3sum/)

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请你返回所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。

**示例 1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
```

**示例 2：**

```
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
```

**示例 3：**

```
输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
```

 

**提示：**

- `3 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        // 先排序
        sort(nums.begin(), nums.end());

        // 遍历固定第一个数
        for (int i = 0; i < n - 2; i++)
        {
            // 如果当前数大于0，则后面的数都大于0，不可能和值为0
            if (nums[i] > 0) break;

            // 跳过重复的第一个数
            if (i > 0 && nums[i] == nums[i-1]) continue;

            // 使用双指针找另外两个数
            int left = i+1;
            int right = n-1;
            int target = -nums[i];

            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (sum == target)
                {
                    // 找到一组解
                    result.push_back({nums[i], nums[left], nums[right]});

                    // 跳过重复的left和right
                    while(left < right && nums[left] == nums[left+1]) left++;
                    while(left < right && nums[right] == nums[right-1]) right--;

                    // 继续移动指针寻找
                    left++;
                    right--;
                }
                else if (sum > target)
                {
                    // 和值太大，需要从小值寻找
                    right--;
                }
                else
                {
                    left++;
                }
            }

        }

        return result;


    }
};
```





## [209. 长度最小的子数组 (滑动窗口)](https://leetcode.cn/problems/minimum-size-subarray-sum/)

给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**

找出该数组中满足其总和大于等于 `target` 的长度最小的 **子数组** `[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。

**示例 1：**

```
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```

**示例 2：**

```
输入：target = 4, nums = [1,4,4]
输出：1
```

**示例 3：**

```
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
```

 

**提示：**

- `1 <= target <= 109`
- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 104`

```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int currentSum = 0;
        int left = 0;
        int right = 0;
        int n = nums.size();
        int minlen = INT_MAX;

        // 使用滑动窗口来解决
        for (; right < n; right++)
        {
            if (nums[right] >= target) return 1;

            // 扩张右侧窗口
            currentSum += nums[right];

            while(currentSum >= target)
            {
                minlen = min(right - left + 1, minlen);
                currentSum -= nums[left];
                // 收缩左侧窗口
                left++;
            }
            
        }

        minlen = minlen == INT_MAX ? 0 : minlen;
        return minlen;
    }
};
```





## [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/)

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长 子串** 的长度。

**示例 1:**

```
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
```

**示例 2:**

```
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```

**示例 3:**

```
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

 

**提示：**

- `0 <= s.length <= 5 * 104`
- `s` 由英文字母、数字、符号和空格组成

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        if (n <= 1) return n;

        int left = 0;
        int maxsublen = 0;

        unordered_set<char> charset;        // 存储当前窗口中的字符

        // 滑动窗口
        for (int right = 0; right < n; right++)
        {
            while(charset.count(s[right]))
            {
                charset.erase(s[left]);
                left++;
            }
            // 将当前字符添加到窗口
            charset.insert(s[right]);
            // 更新最大长度
            maxsublen = max(maxsublen, right - left + 1);
        }

        return maxsublen;

    }
};
```



## [30. 串联所有单词的子串](https://leetcode.cn/problems/substring-with-concatenation-of-all-words/)



给定一个字符串 `s` 和一个字符串数组 `words`**。** `words` 中所有字符串 **长度相同**。

 `s` 中的 **串联子串** 是指一个包含 `words` 中所有字符串以任意顺序排列连接起来的子串。

- 例如，如果 `words = ["ab","cd","ef"]`， 那么 `"abcdef"`， `"abefcd"`，`"cdabef"`， `"cdefab"`，`"efabcd"`， 和 `"efcdab"` 都是串联子串。 `"acdbef"` 不是串联子串，因为他不是任何 `words` 排列的连接。

返回所有串联子串在 `s` 中的开始索引。你可以以 **任意顺序** 返回答案。

 

**示例 1：**

```
输入：s = "barfoothefoobarman", words = ["foo","bar"]
输出：[0,9]
解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
输出顺序无关紧要。返回 [9,0] 也是可以的。
```

**示例 2：**

```
输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
输出：[]
解释：因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
所以我们返回一个空数组。
```

**示例 3：**

```
输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
输出：[6,9,12]
解释：因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。
```

 

**提示：**

- `1 <= s.length <= 104`
- `1 <= words.length <= 5000`
- `1 <= words[i].length <= 30`
- `words[i]` 和 `s` 由小写英文字母组成

```c++
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        int n = words.size();
        if (n == 0) return result;
        int wordlen = words[0].size();
        int substrlen = n * wordlen;
        if (s.size() < substrlen) return result;

        // 使用滑动窗口来遍历字符串s，使用哈希表来记录字符串里的子串是否在worlds里        
        unordered_map<string, int> wordTimesMap;
        for (const string& word : words)
        {
            wordTimesMap[word]++;
        }

        unordered_map<string, int> wordTimes;

        // 这种滑动方式是每次只滑动一个字符，会导致每次滑动都需要重新处理窗口内的字符
        // for (int left = 0; left <= s.size()-substrlen; left++)
        // {
        //     int right = left + substrlen;
        //     wordTimes.clear();
        //     bool valid = true;
        //     for (int i = 0; i < n; i++)
        //     {
        //         // std::string_view sv(s.data() + left + i, wordlen);
        //         // 计算当前单词的起始位置
        //         int startPos = left+i * wordlen;
        //         string sv = s.substr(startPos, wordlen);
        //         if (wordTimesMap.find(sv) != wordTimesMap.end())
        //         {
        //             wordTimes[sv]++;
        //             // 说明该子串里的这段字符串是words里的单词
        //             // 但是这里需要检查该单词的出现次数是否已经超出worlds里的次数
        //             if (wordTimes[sv] > wordTimesMap[sv])
        //             {
        //                 valid = false;
        //                 // 就说明该left-right不是链接子串
        //                 break;
        //             }
        //         }
        //         else
        //         {
        //             valid = false;
        //             break;
        //         }
        //     }
        //     if (valid)
        //     {
        //         result.push_back(left);
        //     }
        // }

        // 改良法：每次滑动一个单词，这样，每次滑动，就只需要处理新划进来的那个单词就行，能大幅提升效率
        for (int offset =0; offset < wordlen; offset++)
        {
            unordered_map<string, int> windowCount;
            int left = offset;
            int count = 0;      // 窗口内匹配的单词数

            // 每次移动一个单词
            for (int right = offset; right+wordlen <= s.size(); right+=wordlen)
            {
                string word = s.substr(right, wordlen);
                if (wordTimesMap.find(word) != wordTimesMap.end())
                {
                    windowCount[word]++;
                    count++;

                    // 如果当前单词出现过多，移动左侧边界
                    while (windowCount[word] > wordTimesMap[word])
                    {
                        string leftWord = s.substr(left, wordlen);
                        windowCount[leftWord]--;
                        count--;
                        left += wordlen;
                    }

                    // 如果窗口大小正好是substrlen，记录位置
                    if (count == n)
                    {
                        result.push_back(left);
                        // 移动左侧边界，继续寻找 （需要将左侧的这个单词次数减去）
                        string leftWord = s.substr(left, wordlen);
                        windowCount[leftWord]--;
                        count--;
                        left += wordlen;
                    }
                }
                else
                {
                    // 说明当前单词不是worlds里的单词
                    windowCount.clear();
                    count = 0;
                    left = right + wordlen;
                }
            }

        }

        return result;

    }
};
```



## [76. 最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring/)

给定两个字符串 `s` 和 `t`，长度分别是 `m` 和 `n`，返回 s 中的 **最短窗口 子串**，使得该子串包含 `t` 中的每一个字符（**包括重复字符**）。如果没有这样的子串，返回空字符串 `""`。

测试用例保证答案唯一。

 

**示例 1：**

```
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
```

**示例 2：**

```
输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
```

**示例 3:**

```
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
```

 

**提示：**

- `m == s.length`
- `n == t.length`
- `1 <= m, n <= 105`
- `s` 和 `t` 由英文字母组成

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";
        
        unordered_map<char, int> need;  // t 中字符出现次数
        unordered_map<char, int> window; // 窗口中字符出现次数
        
        // 统计 t 中字符出现次数
        for (char c : t) {
            need[c]++;
        }
        
        int left = 0, right = 0;
        int valid = 0;  // 窗口中满足 need 条件的字符个数

        int start = 0;  // 最下窗口的起始位置
        int minlen = INT_MAX;   // 最小窗口长度

        while (right < s.size())
        {
            // 右移，扩大窗口
            char c = s[right];
            right++;

            // 更新窗口数据
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                {
                    // 该字符满足条件
                    valid++;
                }
            }

            // 判断左侧窗口是否需要收紧
            while (valid == need.size())
            {
                // 跟新最小覆盖子串
                if (right - left < minlen)
                {
                    start = left;
                    minlen = right - left;
                }
                // 将要移出窗口的字符
                char d = s[left];
                left++;

                // 更新窗口数据
                if (need.count(d))
                {
                    if (window[d] == need[d])
                    {
                        valid--;        // 该字符不再满足条件
                    }
                    window[d]--;
                }
            }

        }

        return minlen == INT_MAX ? "" : s.substr(start, minlen);

    }
};
```



## [36. 有效的数独](https://leetcode.cn/problems/valid-sudoku/)

请你判断一个 `9 x 9` 的数独是否有效。只需要 **根据以下规则** ，验证已经填入的数字是否有效即可。

1. 数字 `1-9` 在每一行只能出现一次。
2. 数字 `1-9` 在每一列只能出现一次。
3. 数字 `1-9` 在每一个以粗实线分隔的 `3x3` 宫内只能出现一次。（请参考示例图）

 

**注意：**

- 一个有效的数独（部分已被填充）不一定是可解的。
- 只需要根据以上规则，验证已经填入的数字是否有效即可。
- 空白格用 `'.'` 表示。

 

**示例 1：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2021/04/12/250px-sudoku-by-l2g-20050714svg.png)

```
输入：board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：true
```

**示例 2：**

```
输入：board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：false
解释：除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。 但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
```

 

**提示：**

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j]` 是一位数字（`1-9`）或者 `'.'`

```c++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        
        // 使用3个哈希表来记录
        // vector<unordered_set<char>> rows(9);    // 每一行里出现的的数字
        // vector<unordered_set<char>> cols(9);    // 每一列里出现的数字
        // vector<unordered_set<char>> boxes(9);   // 每个小的3*3子盒子里出现的数字

        // for (int i = 0; i < 9; i++)
        // {
        //     for (int j = 0; j < 9; j++)
        //     {
        //         char c = board[i][j];
        //         if (c == '.') continue;

        //         // 计算属于哪个3*3 (比如下面这种计算方式就是从左到右，然后再从上到下)
        //         int boxindex = (i/3) * 3 + (j/3);

        //         // 检查当前数字（字符）是否已经存在行里，列里，或者子盒里
        //         if (rows[i].count(c) || cols[j].count(c) || boxes[boxindex].count(c))
        //         {
        //             return false;
        //         }

        //         // 不在，那么就添加该字符的信息
        //         rows[i].insert(c);
        //         cols[j].insert(c);
        //         boxes[boxindex].insert(c);

        //     }
        // }

        // return true;

        // 使用位运算优化算法空间
        // 使用3个整数数组，每个元素用9位二进制表示数字1-9的出现情况
        // 第k位置位1表示数字k+1已经出现过
        int rows[9] = {0};
        int cols[9] = {0};
        int boxes[9] = {0};

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char c = board[i][j];
                if (c == '.') continue;

                int num = c - '1';  // 0-8 (需要将字符转为对应的数字，这里减去1是因为对应的下标就是存储该数字的信息，下标就是数字，不过因为是C风格的从0开始的数组，所以需要减去1)
                int mask = 1 << num;    // 使用位移运算，将1左移位

                // 计算3*3宫格的索引
                int boxindex = (i/3)*3+(j/3);

                // 检查该字符是否已经出现
                // 使用位运算（与），检查mask和待检测数的位值上是否已经存在，如果已经存在返回1，否则返回0，来检查该字符是否已经出现过
                if ((rows[i] & mask) != 0 ||
                    (cols[j] & mask) != 0 ||
                    (boxes[boxindex] & mask) != 0 )
                {
                    return false;
                }

                // 记录字符出现信息
                // 使用对应位置的数字与当前字符的位信息进行或操作，然后将结果保存到位置里
                rows[i] |= mask;
                cols[j] |= mask;
                boxes[boxindex] |= mask;
            }
        }

        return true;
    }
};
```





## [54. 螺旋矩阵](https://leetcode.cn/problems/spiral-matrix/)



给你一个 `m` 行 `n` 列的矩阵 `matrix` ，请按照 **顺时针螺旋顺序** ，返回矩阵中的所有元素。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/11/13/spiral1.jpg)

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/11/13/spiral.jpg)

```
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
```

 

**提示：**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 10`
- `-100 <= matrix[i][j] <= 100`

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};

        int m = matrix.size();      // 行数
        int n = matrix[0].size();   // 列数

        vector<int> result;
        int top = 0, bottom = m-1, left = 0, right = n-1;   // 上下左右边界

        while (top <= bottom && left <= right)
        {
            // 从左到右遍历上边界
            for (int i = left; i <= right; i++)
            {
                result.push_back(matrix[top][i]);
            }
            top++;

            // 从上到下遍历右边界
            for (int j = top; j <= bottom; j++)
            {
                result.push_back(matrix[j][right]);
            }
            right--;

            // 从右到左遍历下边界，需要检查是否还有行
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                {
                    result.push_back(matrix[bottom][i]);
                }
                bottom--;
            }

            // 从下到上遍历左边界，需要检查是否还有列
            if (left <= right)
            {
                for (int j = bottom; j >= top; j--)
                {
                    result.push_back(matrix[j][left]);
                }
                left++;
            }
        }

        return result;

    }
};
```



## [48. 旋转图像](https://leetcode.cn/problems/rotate-image/)



给定一个 *n* × *n* 的二维矩阵 `matrix` 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在**[ 原地](https://baike.baidu.com/item/原地算法)** 旋转图像，这意味着你需要直接修改输入的二维矩阵。**请不要** 使用另一个矩阵来旋转图像。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/08/28/mat1.jpg)

```
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/08/28/mat2.jpg)

```
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

 

**提示：**

- `n == matrix.length == matrix[i].length`
- `1 <= n <= 20`
- `-1000 <= matrix[i][j] <= 1000`

 

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // // 线性代数里，对于n*n的矩阵旋转，我们可以使用转置矩阵（即行和列互换），然后再翻转每一行
        // // 当然，上述是对于顺时针旋转90度，如果是逆时针，我们需要先转置，然后翻转每一列
        // int n = matrix.size();

        // // 先转置，行列交换
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = i; j < n; j++)
        //     {
        //         // 将行变成列，列变成行
        //         swap(matrix[i][j], matrix[j][i]);
        //     }
        // }

        // // 翻转每一行
        // for (int i = 0; i < n; i++)
        // {
        //     reverse(matrix[i].begin(), matrix[i].end());
        // }


        // 解法2：四元素交换
        int n = matrix.size();
        // 对于每一个位置的元素，找到旋转后对应的4个位置
        // 注意，这里只需要遍历一半的元素就行，而遍历一半，其实也不严谨，因为x和y我们都只遍历一半，相当于这个矩阵我只处理了左上角这4分子一部分，而这部分里的每一个元素我们都会去寻找它旋转后对应的位置，
        // 而在找到他的位置后，我们又会继续处理它旋转后位置的原始数据的旋转后位置，以此类推
        // 这个方法的原理是每次同时交换四个相关的元素，这四个元素在旋转后互相移动到对方的位置。
        // 所以，如果我们遍历整个n，实际上是做了4次90度旋转，就又旋转回原来的数据了
        for (int i = 0; i < (n+1)/2; i++)
        {
            for (int j = 0; j < n/2; j++)
            {
                // 获取当前位置的4个对应位置元素
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = temp;
            }
        }
    }
};
```

### 1. **时间复杂度分析**

cpp

```
/*
转置 + 反转方法：
- 转置：O(n²)（实际上只遍历了矩阵的一半）
- 反转每行：O(n²)
总时间复杂度：O(n²)

分层旋转方法：
- 每个元素只被访问一次：O(n²)

四元素交换方法：
- 每个元素只被访问一次：O(n²)

对于 n x n 矩阵，所有方法都是 O(n²) 时间复杂度
*/
```



### 2. **空间复杂度分析**

cpp

```
/*
原地旋转方法：
- 转置 + 反转：O(1) 额外空间
- 分层旋转：O(1) 额外空间
- 四元素交换：O(1) 额外空间

非原地旋转方法（矩形矩阵）：
- 需要 O(m x n) 额外空间
*/
```





## [73. 矩阵置零](https://leetcode.cn/problems/set-matrix-zeroes/)

给定一个 `*m* x *n*` 的矩阵，如果一个元素为 **0** ，则将其所在行和列的所有元素都设为 **0** 。请使用 **[原地](http://baike.baidu.com/item/原地算法)** 算法**。**

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/08/17/mat1.jpg)

```
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/08/17/mat2.jpg)

```
输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

 

**提示：**

- `m == matrix.length`
- `n == matrix[0].length`
- `1 <= m, n <= 200`
- `-231 <= matrix[i][j] <= 231 - 1`

 

**进阶：**

- 一个直观的解决方案是使用  `O(*m**n*)` 的额外空间，但这并不是一个好的解决方案。
- 一个简单的改进方案是使用 `O(*m* + *n*)` 的额外空间，但这仍然不是最好的解决方案。
- 你能想出一个仅使用常量空间的解决方案吗？

```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        // 需要两次遍历，第一次遍历找出0在的位置，第二次遍历置0
        int m = matrix.size();
        int n = matrix[0].size();

        // // 提供两个数组，一个保存行里0所在的位置，一个保存列里0所在位置
        // // 更进一步，可以使用位运算，这样将两个方向的0位置信息保存在两个整数里就行
        // // 但是这种使用位运算有个潜在问题，就是当元素个数（m，或者 n）超出系统位数时（32或者64），位运算就会溢出
        // int zerorow = 0;     // 行里0的位置（即第几行有0）
        // int zercol = 0;     // 列里0的位置（即第几列有0）

        // for (int i = 0; i < m; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         if (matrix[i][j] == 0)
        //         {
        //             // 将i和j的信息保存到zerorow和zerocol中
        //             int mask_row = 1 << i;
        //             zerorow |= mask_row;
        //             int mask_col = 1 << j;
        //             zercol |= mask_col;
        //         }
        //     }
        // }

        // // 这次遍历，染色，将0所在行或者所在列置为0
        // for (int i = 0; i < m; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         int mask_row = 1 << i;
        //         int mask_col = 1 << j;
        //         if (((zerorow & mask_row) != 0) || ((zercol & mask_col) != 0))
        //         {
        //             // 只要列或者行里有0标记，就置0
        //             matrix[i][j] = 0;
        //         }
        //     }
        // }

        // 为了避免数据量过大导致位运算溢出的问题，可以使用vector数组来保存0位置信息，但是这样在数据量过大的情况下依旧会有很大内存消耗，
        // 所以我们可以使用原始矩阵里的第一列和第一行来保存0位置信息，这样就能实现无任何额外空间消耗
        bool firstRowZero = false, firstColZero = false;

        // 先检查首列和首行是否包含0，因为后续遍历过程首列和首行已经作为标记位，标记后将无法获知原始数据，所以需要将此信息提前保存下来
        for (int j = 0; j < n; j++)
        {
            if (matrix[0][j] == 0)
            {
                firstRowZero = true;
                break;
            }
        }

        for (int i = 0; i < m; i++)
        {
            if (matrix[i][0] == 0)
            {
                firstColZero = true;
                break;
            }
        }

        // 标记
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    // 将i和j的信息保存到zerorow和zerocol中
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 这次遍历，染色，将0所在行或者所在列置为0
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        // 处理第一行和第一列
        if (firstRowZero)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[0][j] = 0;
            }
        }
        if (firstColZero)
        {
            for (int i = 0; i < m; i++)
            {
                matrix[i][0] = 0;
            }
        }

    }
};
```





## [289. 生命游戏](https://leetcode.cn/problems/game-of-life/)

根据 [百度百科](https://baike.baidu.com/item/生命游戏/2926434?fr=aladdin) ， **生命游戏** ，简称为 **生命** ，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

给定一个包含 `m × n` 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态： `1` 即为 **活细胞** （live），或 `0` 即为 **死细胞** （dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

1. 如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
2. 如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
3. 如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
4. 如果死细胞周围正好有三个活细胞，则该位置死细胞复活；

下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是 **同时** 发生的。给你 `m x n` 网格面板 `board` 的当前状态，返回下一个状态。

给定当前 `board` 的状态，**更新** `board` 到下一个状态。

**注意** 你不需要返回任何东西。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/12/26/grid1.jpg)

```
输入：board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
输出：[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/12/26/grid2.jpg)

```
输入：board = [[1,1],[1,0]]
输出：[[1,1],[1,1]]
```

 

**提示：**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 25`
- `board[i][j]` 为 `0` 或 `1`

 

**进阶：**

- 你可以使用原地算法解决本题吗？请注意，面板上所有格子需要同时被更新：你不能先更新某些格子，然后使用它们的更新后的值再更新其他格子。
- 本题中，我们使用二维数组来表示面板。原则上，面板是无限的，但当活细胞侵占了面板边界时会造成问题。你将如何解决这些问题？

```c++
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        // 原地解决生命游戏
        // 第一次遍历，我们将原本活着的但是下次更新后就死亡的格子填充为2（活着->死亡 = 2）
        // （死亡->活着 = 3）, 所以在遍历过程中，遇到0,3都是死亡，遇到1,2都是活着
        // 然后第二次遍历，将2填充为0,3填充为1

        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int alivenum = 0;
                int deathnum = 0;
                // 左上
                if ((i-1) >= 0 && (j-1) >= 0)
                {
                    int val = board[i-1][j-1];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 上
                if ((i-1) >= 0)
                {
                    int val = board[i-1][j];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 右上
                if ((i-1) >= 0 && (j+1) < n)
                {
                    int val = board[i-1][j+1];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 右
                if ((j+1) < n)
                {
                    int val = board[i][j+1];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 右下
                if ((i+1) < m && (j+1) < n)
                {
                    int val = board[i+1][j+1];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 下
                if ((i+1) < m)
                {
                    int val = board[i+1][j];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 左下
                if ((i+1) < m && (j-1) >= 0)
                {
                    int val = board[i+1][j-1];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                // 左
                if ((j-1) >= 0)
                {
                    int val = board[i][j-1];
                    if (val == 0 || val == 3) deathnum++;
                    if (val == 1 || val == 2) alivenum++;
                }

                int currentcell = board[i][j];
                if (currentcell == 1)
                {
                    if (alivenum < 2 || alivenum > 3)
                    {
                        board[i][j] = 2;    // 活变死
                    }
                }
                else if (currentcell == 0)
                {
                    if (alivenum == 3)
                    {
                        board[i][j] = 3;    // 死变活
                    }
                }
                
            }
        }

        // 再次遍历，整理数据
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 2)
                {
                    board[i][j] = 0;
                }
                else if (board[i][j] == 3)
                {
                    board[i][j] = 1;
                }
            }

        }

    }
};
```





## [383. 赎金信](https://leetcode.cn/problems/ransom-note/)

给你两个字符串：`ransomNote` 和 `magazine` ，判断 `ransomNote` 能不能由 `magazine` 里面的字符构成。

如果可以，返回 `true` ；否则返回 `false` 。

`magazine` 中的每个字符只能在 `ransomNote` 中使用一次。

 

**示例 1：**

```
输入：ransomNote = "a", magazine = "b"
输出：false
```

**示例 2：**

```
输入：ransomNote = "aa", magazine = "ab"
输出：false
```

**示例 3：**

```
输入：ransomNote = "aa", magazine = "aab"
输出：true
```

 

**提示：**

- `1 <= ransomNote.length, magazine.length <= 105`
- `ransomNote` 和 `magazine` 由小写英文字母组成

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int m = ransomNote.size();
        int n = magazine.size();

        if (m > n) return false;

        int alphanums[26] = {0};        // 长度为26的数组，记录26个字母在magazine里的出现次数
        
        for (char c : magazine)
        {
            alphanums[c - 'a']++;
        }

        for (char c : ransomNote)
        {
            if (--alphanums[c - 'a'] < 0)
            {
                return false;
            }
        }

        return true;


    }
};
```

时间复杂度为 O(m+n)，空间复杂度为 O(1)





## [205. 同构字符串](https://leetcode.cn/problems/isomorphic-strings/)



给定两个字符串 `s` 和 `t` ，判断它们是否是同构的。

如果 `s` 中的字符可以按某种映射关系替换得到 `t` ，那么这两个字符串是同构的。

每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。



**示例 1:**

```
输入：s = "egg", t = "add"
输出：true
```

**示例 2：**

```
输入：s = "foo", t = "bar"
输出：false
```

**示例 3：**

```
输入：s = "paper", t = "title"
输出：true
```

 

**提示：**

- `1 <= s.length <= 5 * 104`
- `t.length == s.length`
- `s` 和 `t` 由任意有效的 ASCII 字符组成

```c++
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, int> smap;      // 字符串s里的字符的首次出现索引
        unordered_map<char, int> tmap;      // 字符串t里的字符的首次出现索引

        int n = s.size();
        if (n <= 1) return true;

        for (int i = 0; i < n; i++)
        {
            char cs = s[i];
            char ct = t[i];
            if (smap.count(cs) && tmap.count(ct) && smap[cs] == tmap[ct])
            {
                continue;
            }
            else if (!smap.count(cs) && !tmap.count(ct))
            {
                smap[cs] = i;
                tmap[ct] = i;
            }
            else
            {
                return false;
            }
        }

        return true;


    }
};
```





## [290. 单词规律](https://leetcode.cn/problems/word-pattern/)



给定一种规律 `pattern` 和一个字符串 `s` ，判断 `s` 是否遵循相同的规律。

这里的 **遵循** 指完全匹配，例如， `pattern` 里的每个字母和字符串 `s` 中的每个非空单词之间存在着双向连接的对应规律。具体来说：

- `pattern` 中的每个字母都 **恰好** 映射到 `s` 中的一个唯一单词。
- `s` 中的每个唯一单词都 **恰好** 映射到 `pattern` 中的一个字母。
- 没有两个字母映射到同一个单词，也没有两个单词映射到同一个字母。

 

**示例1:**

```
输入: pattern = "abba", s = "dog cat cat dog"
输出: true
```

**示例 2:**

```
输入:pattern = "abba", s = "dog cat cat fish"
输出: false
```

**示例 3:**

```
输入: pattern = "aaaa", s = "dog cat cat dog"
输出: false
```

 

**提示:**

- `1 <= pattern.length <= 300`
- `pattern` 只包含小写英文字母
- `1 <= s.length <= 3000`
- `s` 只包含小写英文字母和 `' '`
- `s` **不包含** 任何前导或尾随对空格
- `s` 中每个单词都被 **单个空格** 分隔

```c++
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string_view> svvec = split_string_view(s);
        int n = pattern.size();
        int sl = svvec.size();
        if (n != sl) return false;

        unordered_map<char, string_view> p2s;      // pattern里的字符到s里的单词的起始下标映射
        unordered_map<string_view, char> s2p;   // s里的单词对应的字符

        for (int i = 0; i < n; i++)
        {
            char c = pattern[i];
            if (p2s.count(c))
            {
                if (p2s[c] != svvec[i])
                {
                    return false;
                }
            }
            else if (s2p.count(svvec[i]))
            {
                if (c != s2p[svvec[i]])
                {
                    return false;
                }
            }
            p2s[c] = svvec[i];
            s2p[svvec[i]] = c;
        }

        return true;
    }

private:
    std::vector<std::string_view> split_string_view(std::string_view str, char delimiter = ' ')
    {
        vector<std::string_view> result;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string_view::npos)
        {
            if (end != start)
            {
                result.push_back(str.substr(start, end - start));
            }

            start = end + 1;
            end = str.find(delimiter, start);
        }

        // 添加最后一个单词
        if (start < str.length())
        {
            result.push_back(str.substr(start));
        }

        return result;

    }

};
```





[242. 有效的字母异位词](https://leetcode.cn/problems/valid-anagram/)



给定两个字符串 `s` 和 `t` ，编写一个函数来判断 `t` 是否是 `s` 的 字母异位词。



**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

 

**提示:**

- `1 <= s.length, t.length <= 5 * 104`
- `s` 和 `t` 仅包含小写字母

 

**进阶:** 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        // vector<int> svec(26);
        // for (int i = 0; i < s.size(); i++)
        // {
        //     int idxs = s[i]-'a';
        //     int idxt = t[i]-'a';
        //     svec[idxs]++;
        //     svec[idxt]--;
        // }
        // for (int i : svec)
        // {
        //     if (i != 0) return false;
        // }

        // return true;

        if (s.size() != t.size()) return false;
        
        array<int, 26> count = {};  // 使用array替代vector，栈上分配更快
        
        for (char c : s) count[c - 'a']++;
        for (char c : t) count[c - 'a']--;
        
        // 使用范围for循环和短路优化
        for (int n : count) {
            if (n != 0) return false;
        }
        
        return true;
    }
};
```





## [49. 字母异位词分组](https://leetcode.cn/problems/group-anagrams/)

给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

 

**示例 1:**

**输入:** strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

**输出:** [["bat"],["nat","tan"],["ate","eat","tea"]]

**解释：**

- 在 strs 中没有字符串可以通过重新排列来形成 `"bat"`。
- 字符串 `"nat"` 和 `"tan"` 是字母异位词，因为它们可以重新排列以形成彼此。
- 字符串 `"ate"` ，`"eat"` 和 `"tea"` 是字母异位词，因为它们可以重新排列以形成彼此。

**示例 2:**

**输入:** strs = [""]

**输出:** [[""]]

**示例 3:**

**输入:** strs = ["a"]

**输出:** [["a"]]

 

**提示：**

- `1 <= strs.length <= 104`
- `0 <= strs[i].length <= 100`
- `strs[i]` 仅包含小写字母

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> resultmap;
        for (const string& str : strs)
        {
            string rawstr = str;
            sort(rawstr.begin(), rawstr.end());
            resultmap[rawstr].push_back(str);
        }

        vector<vector<string>> result;
        result.reserve(resultmap.size());       // 预先分配空间，提升性能，避免数据量大的时候频繁扩容
        // for (const std::pair<string, vector<string>>& re : resultmap)
        // {
        //     result.push_back(re.second);
        // }

        for (auto& [_, group] : resultmap)
        {
            result.push_back(move(group));
        }

        return result;


        // // 上述代码需要对每个单词都进行排序，这一步消耗很大，考虑使用频率计数来优化
        // // 自定义哈希函数，避免排序
        // auto getkey = [](const string& str)->string
        // {
        //     vector<int> count(26, 0);
        //     for (char c: str) count[c-'a']++;

        //     string key;
        //     for (int i = 0; i < 26; i++)
        //     {
        //         if (count[i]>0)
        //         {
        //             key += char('a'+i);
        //             key += to_string(count[i]);
        //             key += '#';
        //         }
        //     }
        //     return key;
        // };

        // unordered_map<string, vector<string>> resultmap;
        
        // for (const string& str : strs)
        // {
        //     resultmap[getkey(str)].push_back(str);
        // }

        // vector<vector<string>> result;
        // result.reserve(resultmap.size());       // 预先分配空间，提升性能，避免数据量大的时候频繁扩容

        // for (auto& [_, group] : resultmap)
        // {
        //     result.push_back(move(group));
        // }

        // return result;

        // 为什么排序版本更快？
        // 常数因子更小：现代CPU的排序算法（如introsort）优化得非常好

        // 字符串长度通常较短：LeetCode测试用例中单词长度通常在0-100之间

        // 内存局部性好：排序是在连续内存上操作

        // 哈希键更短：排序后的键长度与原单词相同，而频率计数的键可能更长


    }
};
```

**为什么排序版本更快？**

1. **常数因子更小**：现代CPU的排序算法（如introsort）优化得非常好
2. **字符串长度通常较短**：LeetCode测试用例中单词长度通常在0-100之间
3. **内存局部性好**：排序是在连续内存上操作
4. **哈希键更短**：排序后的键长度与原单词相同，而频率计数的键可能更长





## [202. 快乐数](https://leetcode.cn/problems/happy-number/)



编写一个算法来判断一个数 `n` 是不是快乐数。

**「快乐数」** 定义为：

- 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
- 然后重复这个过程直到这个数变为 1，也可能是 **无限循环** 但始终变不到 1。
- 如果这个过程 **结果为** 1，那么这个数就是快乐数。

如果 `n` 是 *快乐数* 就返回 `true` ；不是，则返回 `false` 。

 

**示例 1：**

```
输入：n = 19
输出：true
解释：
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

**示例 2：**

```
输入：n = 2
输出：false
```

 

**提示：**

- `1 <= n <= 231 - 1`

```c++
class Solution {
public:
    bool isHappy(int n) {
        // 方法1：使用哈希表检测循环
        // unordered_set<int> unhappyset;

        // while (n != 1 && !unhappyset.count(n))
        // {
        //     unhappyset.insert(n);
        //     n = getNext(n);
        // }

        // return n == 1;

        // 方法2：使用快慢指针检测循环（Floyd判圈算法）
        int slow = n;
        int fast = getNext(n);

        // 当fast到达1，或者快慢指针相遇时退出循环
        while (fast != 1 && slow != fast)
        {
            slow = getNext(slow);       // 慢指针走一步
            fast = getNext(getNext(fast));      // 快指针走两步
        }

        return fast == 1;

    }

private:
    int getNext(int n)
    {
        int sum = 0;
        while (n > 0)
        {
            int digit = n % 10;
            sum += (digit * digit);
            n /= 10;
        }

        return sum;
    }


};
```

### 快慢指针（Floyd判圈算法）

详细解释一下**快慢指针（Floyd判圈算法）** 在快乐数问题中的应用。这是一种非常巧妙且高效的方法。

#### 什么是快慢指针法？

快慢指针法（也叫Floyd判圈算法）用于检测一个序列中是否存在环。基本思想是：
- 让两个指针以不同的速度遍历序列
- 如果存在环，快指针最终会追上慢指针
- 如果不存在环，快指针会先到达终点

#### 在快乐数问题中的应用

##### 问题背景：
对于一个数字n，我们不断计算其各位数字的平方和，得到下一个数字：
```
f(19) = 1² + 9² = 82
f(82) = 8² + 2² = 68
f(68) = 6² + 8² = 100
f(100) = 1² + 0² + 0² = 1
```

这个过程形成了一个序列：19 → 82 → 68 → 100 → 1 → 1 → 1...

##### 关键观察：
1. **如果n是快乐数**：序列最终会到达1，然后一直在1循环（1 → 1 → 1...）
2. **如果n不是快乐数**：序列会进入一个不包含1的循环（如4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4...）

### 为什么可以用快慢指针？

我们可以把序列看作一个隐式的链表：
- 每个节点是一个数字
- 节点的"next"指针指向 `f(n)`（各位数字的平方和）
- 问题变为：判断链表是否有环，以及环的入口是否是1

### 算法详解：

#### 步骤1：定义两个指针
```cpp
int slow = n;      // 慢指针，每次走一步
int fast = getNext(n);  // 快指针，每次走两步
```

#### 步骤2：开始追逐
```cpp
while (fast != 1 && slow != fast) {
    slow = getNext(slow);           // 慢指针走一步
    fast = getNext(getNext(fast));  // 快指针走两步
}
```

#### 步骤3：判断结果
```cpp
return fast == 1;  // 如果快指针到达1，说明是快乐数
```

### 示例演示：

#### 示例1：19（快乐数）
```
初始: slow = 19, fast = 82

迭代1:
  slow = f(19) = 82
  fast = f(f(82)) = f(68) = 100
  
迭代2:
  slow = f(82) = 68
  fast = f(f(100)) = f(1) = 1
  
此时 fast = 1，循环结束，返回true
```

#### 示例2：2（非快乐数）
```
初始: slow = 2, fast = 4

迭代1:
  slow = f(2) = 4
  fast = f(f(4)) = f(16) = 37
  
迭代2:
  slow = f(4) = 16
  fast = f(f(37)) = f(58) = 89
  
迭代3:
  slow = f(16) = 37
  fast = f(f(89)) = f(145) = 42
  
迭代4:
  slow = f(37) = 58
  fast = f(f(42)) = f(20) = 16
  
迭代5:
  slow = f(58) = 89
  fast = f(f(16)) = f(37) = 58
  
迭代6:
  slow = f(89) = 145
  fast = f(f(58)) = f(89) = 145
  
此时 slow = fast = 145（相遇），但 fast != 1，返回false
```

### 可视化理解：

```
对于非快乐数（如2）：
2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 (循环)

慢指针路径：2 → 4 → 16 → 37 → 58 → 89 → 145
快指针路径：4 → 37 → 89 → 16 → 58 → 145 → 145

它们最终在145相遇。

对于快乐数（如19）：
19 → 82 → 68 → 100 → 1 → 1 → 1...

慢指针路径：19 → 82 → 68 → 100 → 1
快指针路径：82 → 100 → 1 → 1 → 1

快指针先到达1，然后慢指针也会到达1。
```

### 数学证明为什么快指针会追上慢指针：

假设环的周长为L，从起点到环入口的距离为a，从环入口到相遇点的距离为b。

1. 慢指针走了 a + b 步
2. 快指针走了 a + b + kL 步（k为正整数）
3. 因为快指针速度是慢指针的2倍：2(a + b) = a + b + kL
4. 简化得：a + b = kL

这说明慢指针走的距离是环周长的整数倍，所以快慢指针一定会相遇。

### 代码实现：

```cpp
class Solution {
public:
    bool isHappy(int n) {
        // 辅助函数：计算下一个数字
        auto getNext = [](int num) {
            int sum = 0;
            while (num > 0) {
                int digit = num % 10;
                sum += digit * digit;
                num /= 10;
            }
            return sum;
        };
        
        int slow = n;            // 慢指针
        int fast = getNext(n);   // 快指针先走一步
        
        // 当快指针不等于1且快慢指针不相遇时，继续循环
        while (fast != 1 && slow != fast) {
            slow = getNext(slow);           // 慢指针走一步
            fast = getNext(getNext(fast));  // 快指针走两步
        }
        
        // 如果快指针是1，说明是快乐数
        return fast == 1;
    }
};
```

### 复杂度分析：

- **时间复杂度**：O(log n)
  - 每次计算平方和需要 O(log n) 时间（数字的位数）
  - 快慢指针最多走 O(log n) 步就会相遇（原因见下）
  
- **空间复杂度**：O(1)
  - 只用了常数空间存储两个指针

### 为什么时间复杂度是 O(log n)？

对于任意数字n，其下一个数字 `f(n)` 的最大值是多少？
- 假设n有d位，每位最大是9，平方和最大是 81d
- 当 n ≥ 1000 时，81d < n
- 所以序列中的数字会迅速减小

例如：
- n=999 → f(n)=243
- n=9999 → f(n)=324
- n=99999 → f(n)=405

这意味着序列长度是 O(log n) 级别的。

### 与哈希集合方法的对比：

| 方法     | 时间复杂度 | 空间复杂度 | 优点               |
| -------- | ---------- | ---------- | ------------------ |
| 快慢指针 | O(log n)   | O(1)       | 不需要额外存储空间 |
| 哈希集合 | O(log n)   | O(log n)   | 简单直观           |

### 练习理解：

你可以手动模拟以下案例，加深理解：

1. **n = 7**（快乐数）：
   ```
   7 → 49 → 97 → 130 → 10 → 1
   ```

2. **n = 116**（非快乐数）：
   ```
   116 → 38 → 73 → 58 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58（循环开始）
   ```

### 总结：

快慢指针法之所以能用于快乐数问题，是因为：
1. 快乐数的计算过程形成了一个隐式链表
2. 快乐数会进入1的循环，非快乐数会进入其他循环
3. 快慢指针可以检测是否存在环
4. 如果快指针到达1，说明是快乐数

这种方法非常优雅，既节省空间又高效，是解决这类"隐式链表环检测"问题的经典方法。







## [219. 存在重复元素 II](https://leetcode.cn/problems/contains-duplicate-ii/)

给你一个整数数组 `nums` 和一个整数 `k` ，判断数组中是否存在两个 **不同的索引** `i` 和 `j` ，满足 `nums[i] == nums[j]` 且 `abs(i - j) <= k` 。如果存在，返回 `true` ；否则，返回 `false` 。

 

**示例 1：**

```
输入：nums = [1,2,3,1], k = 3
输出：true
```

**示例 2：**

```
输入：nums = [1,0,1,1], k = 1
输出：true
```

**示例 3：**

```
输入：nums = [1,2,3,1,2,3], k = 2
输出：false
```

 

```c++
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        // 边界情况：k=0或数组为空
        if (nums.empty() || k == 0) return false;
        
        unordered_map<int, int> numIdxMap;
        numIdxMap.reserve(nums.size());     // 预先分配空间，避免后续的多次扩容照成的时间浪费

        for (int i = 0; i < nums.size(); i++)
        {
            int val = nums[i];
            auto it = numIdxMap.find(val);
            if (it != numIdxMap.end())
            {
                int idx = it->second;
                if (abs(i-idx) <= k) return true;
                it->second = i;
            }
            else
            {
                numIdxMap[val] = i;
            }
        }

        return false;

    }
};
```





## [128. 最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/)

给定一个未排序的整数数组 `nums` ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 `O(n)` 的算法解决此问题。

 

**示例 1：**

```
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
```

**示例 2：**

```
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
```

**示例 3：**

```
输入：nums = [1,0,1,2]
输出：3
```

 

**提示：**

- `0 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`

```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return n;

        int maxLen = 0;
        int left = 0;
        int right = 0;

        // 先排序
        sort(nums.begin(), nums.end());
        // 再去重
        nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

        // 使用滑动窗口
        while (right < nums.size())
        {
            if (nums[right] == nums[left] + (right - left))
            {
                maxLen = max(maxLen, (right - left + 1));
            }
            else
            {
                left = right;
            }
            right++;
        }

        return maxLen;

        // // 方法2：使用哈希表记录边界长度
        // unordered_map<int, int> boundaryLen;
        // int maxLen = 0;

        // for (int num : nums)
        // {
        //     // 如果已经处理过（遇到重复元素），则跳过
        //     if (boundaryLen.count(num)) continue;

        //     // 获取左右相邻的序列的长度
        //     int leftLen = boundaryLen.count(num-1) ? boundaryLen[num-1] : 0;
        //     int rightLen = boundaryLen.count(num+1) ? boundaryLen[num+1] : 0;

        //     // 计算当前序列长度
        //     int currentlen = leftLen + 1 + rightLen;

        //     // 更新最大序列长度
        //     maxLen = max(maxLen, currentlen);

        //     boundaryLen[num] = currentlen;

        //     // 更新边界记录
        //     if (leftLen > 0) boundaryLen[num-leftLen] = currentlen;
        //     if (rightLen > 0) boundaryLen[num+rightLen] = currentlen;  

        // }

        // return maxLen;
        
    }
};
```





## [228. 汇总区间](https://leetcode.cn/problems/summary-ranges/)



给定一个  **无重复元素** 的 **有序** 整数数组 `nums` 。

区间 `[a,b]` 是从 `a` 到 `b`（包含）的所有整数的集合。

返回 ***恰好覆盖数组中所有数字** 的 **最小有序** 区间范围列表* 。也就是说，`nums` 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个区间但不属于 `nums` 的数字 `x` 。

列表中的每个区间范围 `[a,b]` 应该按如下格式输出：

- `"a->b"` ，如果 `a != b`
- `"a"` ，如果 `a == b`

 

**示例 1：**

```
输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
```

**示例 2：**

```
输入：nums = [0,2,3,4,6,8,9]
输出：["0","2->4","6","8->9"]
解释：区间范围是：
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"
```

 

**提示：**

- `0 <= nums.length <= 20`
- `-231 <= nums[i] <= 231 - 1`
- `nums` 中的所有值都 **互不相同**
- `nums` 按升序排列

```c++
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        // if (n == 0) return {};
        // if (n == 1)
        // {
        //     string s = std::format("{}", nums[0]);
        //     return {s};
        // }

        // if (nums[n-1] == nums[0] + n - 1)
        // {
        //     string s = std::format("{0}->{1}", nums[0], nums[n-1]);
        //     return {s};
        // }

        // vector<string> result;

        // // 滑动窗口
        // int left = 0;
        // int right = 0;
        // while (right < n)
        // {
        //     // 注意这里要使用减法，因为避免出现极端大数（元素值为最大整形数）时使用加法导致整形溢出的问题
        //     if (nums[left] != (nums[right] - (right - left)))
        //     {
        //         if (left < right - 1)
        //         {
        //             string s = std::format("{0}->{1}", nums[left], nums[right-1]);
        //             result.push_back(s);
        //         }
        //         else if (left == right-1)
        //         {
        //             string s = std::format("{}", nums[left]);
        //             result.push_back(s);
        //         }
        //         left = right;
        //     }
        //     right++;
        // }

        // if (left != right)
        // {
        //     if (left < right - 1)
        //     {
        //         string s = std::format("{0}->{1}", nums[left], nums[right-1]);
        //         result.push_back(s);
        //     }
        //     else if (left == right-1)
        //     {
        //         string s = std::format("{}", nums[left]);
        //         result.push_back(s);
        //     }
        // }

        // return result;

        vector<string> result;

        for (int i = 0; i < n; i++)
        {
            int start = nums[i];
            while (i+1 < n && nums[i+1] == nums[i]+1)
            {
                i++;
            }
            if (start == nums[i])
            {
                result.push_back(std::format("{}", start));
            }
            else
            {
                result.push_back(std::format("{}->{}", start, nums[i]));
            }
        }

        return result;

    }
};
```





## [56. 合并区间](https://leetcode.cn/problems/merge-intervals/)

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 *一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间* 。

 

**示例 1：**

```
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
```

**示例 2：**

```
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```

**示例 3：**

```
输入：intervals = [[4,7],[1,4]]
输出：[[1,7]]
解释：区间 [1,4] 和 [4,7] 可被视为重叠区间。
```

 

**提示：**

- `1 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 104`

```c++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        if (intervals.empty()) return {};

        // 先排序，按起始值由低到高排序
        // std::sort(intervals.begin(), intervals.end(), 
        //     [](const vector<int>& a, const vector<int>& b)->bool
        //     {
        //         return a[0] < b[0];
        //     }
        // );
        // 当然，我们也可以直接使用vector的默认排序规则，因为vector的默认排序就是按照第一个元素进行排序的
        std::sort(intervals.begin(), intervals.end());

        vector<vector<int>> result;
        int left = -1;
        int right = -1;
        for (const vector<int>& vals : intervals)
        {
            if (left == -1)
            {
                left = vals[0];
                right = vals[1];
                continue;
            }

            if (vals[0] <= right)
            {
                right = max(right, vals[1]);
            }
            else
            {
                result.push_back({left, right});
                left = vals[0];
                right = vals[1];
            }
        }

        if (left != -1)
        {
            result.push_back({left, right});
        }
        
        return result;
    }
};
```





## [57. 插入区间](https://leetcode.cn/problems/insert-interval/)

给你一个 **无重叠的** *，*按照区间起始端点排序的区间列表 `intervals`，其中 `intervals[i] = [starti, endi]` 表示第 `i` 个区间的开始和结束，并且 `intervals` 按照 `starti` 升序排列。同样给定一个区间 `newInterval = [start, end]` 表示另一个区间的开始和结束。

在 `intervals` 中插入区间 `newInterval`，使得 `intervals` 依然按照 `starti` 升序排列，且区间之间不重叠（如果有必要的话，可以合并区间）。

返回插入之后的 `intervals`。

**注意** 你不需要原地修改 `intervals`。你可以创建一个新数组然后返回它。

 

**示例 1：**

```
输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]
```

**示例 2：**

```
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
```

 

**提示：**

- `0 <= intervals.length <= 104`
- `intervals[i].length == 2`
- `0 <= starti <= endi <= 105`
- `intervals` 根据 `starti` 按 **升序** 排列
- `newInterval.length == 2`
- `0 <= start <= end <= 105`

```c++
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        vector<vector<int>> result;
        int i = 0;
        int n = intervals.size();

        // 找到合并开始的位置
        while (i < n && intervals[i][1] < newInterval[0])
        {
            result.push_back(intervals[i]);
            i++;
        }

        // 合并重叠区间
        int merge_start = newInterval[0];
        int merge_end = newInterval[1];
        while (i < n && intervals[i][0] <= merge_end)
        {
            merge_start = min(merge_start, intervals[i][0]);
            merge_end = max(merge_end, intervals[i][1]);
            i++;
        }
        result.push_back({merge_start, merge_end});

        // 添加剩余区间
        while (i < n)
        {
            result.push_back(intervals[i]);
            i++;
        }

        return result;
    }
};
```





## [452. 用最少数量的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 `points` ，其中`points[i] = [xstart, xend]` 表示水平直径在 `xstart` 和 `xend`之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 **完全垂直** 地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `xstart`，`xend`， 且满足  `xstart ≤ x ≤ xend`，则该气球会被 **引爆** 。可以射出的弓箭的数量 **没有限制** 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 `points` ，*返回引爆所有气球所必须射出的 **最小** 弓箭数* 。

**示例 1：**

```
输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。
```

**示例 2：**

```
输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。
```

**示例 3：**

```
输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。
```

 

**提示:**

- `1 <= points.length <= 105`
- `points[i].length == 2`
- `-231 <= xstart < xend <= 231 - 1`

```c++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() <= 1) return points.size();

        sort(points.begin(), points.end());
        int arrownum = 0;

        int left = points[0][0];
        int right = points[0][1];
        for (auto it = points.begin() + 1; it != points.end(); ++it)
        {
            if ((*it)[0] > right)
            {
                // 不和前面的区间相交
                arrownum++;
                left = (*it)[0];
                right = (*it)[1];
            }
            else
            {
                left = max(left, (*it)[0]);
                right = min(right, (*it)[1]);
            }
        }

        arrownum++;

        return arrownum;

    }
};
```





## [20. 有效的括号](https://leetcode.cn/problems/valid-parentheses/)

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s` ，判断字符串是否有效。

有效字符串需满足：

1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 每个右括号都有一个对应的相同类型的左括号。

 

**示例 1：**

**输入：**s = "()"

**输出：**true

**示例 2：**

**输入：**s = "()[]{}"

**输出：**true

**示例 3：**

**输入：**s = "(]"

**输出：**false

**示例 4：**

**输入：**s = "([])"

**输出：**true

**示例 5：**

**输入：**s = "([)]"

**输出：**false

 

**提示：**

- `1 <= s.length <= 104`
- `s` 仅由括号 `'()[]{}'` 组成

```c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s)
        {
            if (st.empty())
            {
                if (c == '}' || c == ')' || c == ']') return false;
                st.push(c);
            }
            else
            {
                char topc = st.top();
                if (c == ')' && topc == '(') st.pop();
                else if (c == ']' && topc == '[') st.pop();
                else if (c == '}' && topc == '{') st.pop();
                else
                {
                    st.push(c);
                }
            }
        }

        return st.empty();
    }
};
```







## [71. 简化路径](https://leetcode.cn/problems/simplify-path/)

给你一个字符串 `path` ，表示指向某一文件或目录的 Unix 风格 **绝对路径** （以 `'/'` 开头），请你将其转化为 **更加简洁的规范路径**。

在 Unix 风格的文件系统中规则如下：

- 一个点 `'.'` 表示当前目录本身。
- 此外，两个点 `'..'` 表示将目录切换到上一级（指向父目录）。
- 任意多个连续的斜杠（即，`'//'` 或 `'///'`）都被视为单个斜杠 `'/'`。
- 任何其他格式的点（例如，`'...'` 或 `'....'`）均被视为有效的文件/目录名称。

返回的 **简化路径** 必须遵循下述格式：

- 始终以斜杠 `'/'` 开头。
- 两个目录名之间必须只有一个斜杠 `'/'` 。
- 最后一个目录名（如果存在）**不能** 以 `'/'` 结尾。
- 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 `'.'` 或 `'..'`）。

返回简化后得到的 **规范路径** 。

 

**示例 1：**

**输入：**path = "/home/"

**输出：**"/home"

**解释：**

应删除尾随斜杠。

**示例 2：**

**输入：**path = "/home//foo/"

**输出：**"/home/foo"

**解释：**

多个连续的斜杠被单个斜杠替换。

**示例 3：**

**输入：**path = "/home/user/Documents/../Pictures"

**输出：**"/home/user/Pictures"

**解释：**

两个点 `".."` 表示上一级目录（父目录）。

**示例 4：**

**输入：**path = "/../"

**输出：**"/"

**解释：**

不可能从根目录上升一级目录。

**示例 5：**

**输入：**path = "/.../a/../b/c/../d/./"

**输出：**"/.../b/d"

**解释：**

`"..."` 在这个问题中是一个合法的目录名。

 

**提示：**

- `1 <= path.length <= 3000`
- `path` 由英文字母，数字，`'.'`，`'/'` 或 `'_'` 组成。
- `path` 是一个有效的 Unix 风格绝对路径。

```c++
class Solution {
public:
    string simplifyPath(string path) {
        stack<string> pathStack;
        stringstream ss(path);
        string dir;

        // 使用getline按照'/'来分割路径
        while (getline(ss, dir, '/'))
        {
            if (dir.empty() || dir == ".")
            {
                continue;
            }
            else if (dir == "..")
            {
                if (!pathStack.empty())
                {
                    pathStack.pop();   // 返回上一个目录
                }
            }
            else
            {
                pathStack.push(dir);    // 有效的目录名
            }
        }
        string result;
        while (!pathStack.empty())
        {
            result = "/" + pathStack.top() + result;
            pathStack.pop();
        }

        return result.empty() ? "/" : result;

    }
};
```







## [155. 最小栈](https://leetcode.cn/problems/min-stack/)

设计一个支持 `push` ，`pop` ，`top` 操作，并能在常数时间内检索到最小元素的栈。

实现 `MinStack` 类:

- `MinStack()` 初始化堆栈对象。
- `void push(int val)` 将元素val推入堆栈。
- `void pop()` 删除堆栈顶部的元素。
- `int top()` 获取堆栈顶部的元素。
- `int getMin()` 获取堆栈中的最小元素。

 

**示例 1:**

```
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
```

 

**提示：**

- `-231 <= val <= 231 - 1`
- `pop`、`top` 和 `getMin` 操作总是在 **非空栈** 上调用
- `push`, `pop`, `top`, and `getMin`最多被调用 `3 * 104` 次

```c++
class MinStack {
public:
    MinStack() {
        
    }
    
    void push(int val) {
        st.push(val);
        if (!minvalst.empty())
        {
            // 查看当前最小值堆栈里的记录的最小值是否小于当前值
            minvalst.push(min(minvalst.top(), val));
        }
        else
        {
            minvalst.push(val);
        }
    }
    
    void pop() {
        st.pop();
        minvalst.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minvalst.top();
    }

private:
    stack<int> st;
    stack<int> minvalst;    // 存储最小值

};
```





## [150. 逆波兰表达式求值](https://leetcode.cn/problems/evaluate-reverse-polish-notation/)

给你一个字符串数组 `tokens` ，表示一个根据 [逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437) 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

**注意：**

- 有效的算符为 `'+'`、`'-'`、`'*'` 和 `'/'` 。
- 每个操作数（运算对象）都可以是一个整数或者另一个表达式。
- 两个整数之间的除法总是 **向零截断** 。
- 表达式中不含除零运算。
- 输入是一个根据逆波兰表示法表示的算术表达式。
- 答案及所有中间计算结果可以用 **32 位** 整数表示。

 

**示例 1：**

```
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```

**示例 2：**

```
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
```

**示例 3：**

```
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
```

 

**提示：**

- `1 <= tokens.length <= 104`
- `tokens[i]` 是一个算符（`"+"`、`"-"`、`"*"` 或 `"/"`），或是在范围 `[-200, 200]` 内的一个整数

 

**逆波兰表达式：**

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

- 平常使用的算式则是一种中缀表达式，如 `( 1 + 2 ) * ( 3 + 4 )` 。
- 该算式的逆波兰表达式写法为 `( ( 1 2 + ) ( 3 4 + ) * )` 。

逆波兰表达式主要有以下两个优点：

- 去掉括号后表达式无歧义，上式即便写成 `1 2 + 3 4 + * `也可以依据次序计算出正确结果。
- 适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> numberStack;
        for (const string& str : tokens)
        {
            if (str == "+")
            {
                int num1 = numberStack.top();
                numberStack.pop();
                int num2 = numberStack.top();
                numberStack.pop();
                int sum = num1 + num2;
                numberStack.push(sum);
            }
            else if (str == "-")
            {
                int num1 = numberStack.top();
                numberStack.pop();
                int num2 = numberStack.top();
                numberStack.pop();
                int sub = num2 - num1;
                numberStack.push(sub);
            }
            else if (str == "*")
            {
                int num1 = numberStack.top();
                numberStack.pop();
                int num2 = numberStack.top();
                numberStack.pop();
                int mul = num1 * num2;
                numberStack.push(mul);
            }
            else if (str == "/")
            {
                int num1 = numberStack.top();
                numberStack.pop();
                int num2 = numberStack.top();
                numberStack.pop();
                int div = num2 / num1;
                numberStack.push(div);
            }
            else
            {
                // 将字符串转为数字
                int num = std::stoi(str);
                numberStack.push(num);
            }
        }

        return numberStack.top();

    }
};
```







## [224. 基本计算器](https://leetcode.cn/problems/basic-calculator/)



给你一个字符串表达式 `s` ，请你实现一个基本计算器来计算并返回它的值。

注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 `eval()` 。



**示例 1：**

```
输入：s = "1 + 1"
输出：2
```

**示例 2：**

```
输入：s = " 2-1 + 2 "
输出：3
```

**示例 3：**

```
输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23
```

 

**提示：**

- `1 <= s.length <= 3 * 105`
- `s` 由数字、`'+'`、`'-'`、`'('`、`')'`、和 `' '` 组成
- `s` 表示一个有效的表达式
- `'+'` 不能用作一元运算(例如， `"+1"` 和 `"+(2 + 3)"` 无效)
- `'-'` 可以用作一元运算(即 `"-1"` 和 `"-(2 + 3)"` 是有效的)
- 输入中不存在两个连续的操作符
- 每个数字和运行的计算将适合于一个有符号的 32位 整数

```c++
class Solution {
public:
    int calculate(string s) {
        stack<long> nums;
        stack<char> ops;
        long num = 0;
        long result = 0;

        // 初始化，先压入一个加号
        ops.push('+');

        for (int i = 0; i <= s.size(); i++)
        {
            char c = i < s.size() ? s[i] : '+';
            if (c == ' ') continue;
            if (isdigit(c))
            {
                // 因为我们是一个字符一个字符读取的，所以相当于先读了千分位，百分位，十分位，个位这样
                // 所以，每读取到一位就需要在先前的基础上*10
                num = num * 10 + (c - '0');
            }
            else if (c == '(')
            {
                // 保存当前状态
                nums.push(result);
                ops.push('+');
                result = 0;
                num = 0;
            }
            else if (c == '+' || c == '-' || c == ')')
            {
                // 处理前一个数字
                char op = ops.top();
                if (op == '+') result += num;
                else result -= num;
                num = 0;

                if (c == ')')
                {
                    ops.pop();  // 弹出当前符号
                    num = result;
                    result = nums.top();
                    nums.pop();
                }
                else
                {
                    ops.pop();
                    ops.push(c);
                }
            }
        }

        return (int)result;

    }
};
```







## [141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/)



给你一个链表的头节点 `head` ，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（索引从 0 开始）。**注意：`pos` 不作为参数进行传递** 。仅仅是为了标识链表的实际情况。

*如果链表中存在环* ，则返回 `true` 。 否则，返回 `false` 。

 

**示例 1：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。
```

**示例 2：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test2.png)

```
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。
```

**示例 3：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test3.png)

```
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
```

 

**提示：**

- 链表中节点的数目范围是 `[0, 104]`
- `-105 <= Node.val <= 105`
- `pos` 为 `-1` 或者链表中的一个 **有效索引** 。

 

**进阶：**你能用 `O(1)`（即，常量）内存解决此问题吗？

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        // 快慢指针判圈算法（Floyd判圈算法）
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }

        return false;

    }
};
```





## [2. 两数相加](https://leetcode.cn/problems/add-two-numbers/)



给你两个 **非空** 的链表，表示两个非负的整数。它们每位数字都是按照 **逆序** 的方式存储的，并且每个节点只能存储 **一位** 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

 

**示例 1：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2021/01/02/addtwonumber1.jpg)

```
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
```

**示例 2：**

```
输入：l1 = [0], l2 = [0]
输出：[0]
```

**示例 3：**

```
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
```

 

**提示：**

- 每个链表中的节点数在范围 `[1, 100]` 内
- `0 <= Node.val <= 9`
- 题目数据保证列表表示的数字不含前导零

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // ListNode* result = l1;      // 以l1为结果链
        // ListNode* prev = nullptr;       // 记录上一个节点
        // int carry = 0;

        // // 同时遍历两个链表
        // while (l1 || l2)
        // {
        //     int val1 = l1 ? l1->val : 0;
        //     int val2 = l2 ? l2->val : 0;
        //     int sum = val1  + val2 + carry;

        //     carry = sum / 10;
        //     if (l1)
        //     {
        //         l1->val = sum % 10;     // 直接修改l1
        //         prev = l1;              // 每次在l1还存在的时候都进行保存，以防l1提前结束丢失尾部信息
        //         l1 = l1->next;
        //     }
        //     else
        //     {
        //         // 表明l1已经结束，但是l2还有，需要创建新节点
        //         prev->next = new ListNode(sum % 10);
        //         prev = prev->next;
        //     }
        //     if (l2)
        //     {
        //         l2 = l2->next;
        //     }
        // }

        // // 处理最后的进位
        // if (carry > 0)
        // {
        //     prev->next = new ListNode(carry);
        // }

        // return result;

        bool carry = false;
        ListNode* curr1 = l1;
        ListNode* curr2 = l2;
        ListNode* lastNode = nullptr;  // 记录最后一个处理的节点
        
        // 第一阶段：同时处理两个链表
        while (curr1 && curr2) {
            int sum = curr1->val + curr2->val + (carry ? 1 : 0);
            carry = sum >= 10;
            
            // 同时更新两个链表的值
            curr1->val = curr2->val = sum % 10;
            lastNode = curr1;  // 任意记录一个即可
            
            // 如果两个都到头且还有进位，需要特殊处理
            if (!curr1->next && !curr2->next && carry) {
                curr1->next = new ListNode(1);
                return l1;
            }
            
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        
        // 第二阶段：处理剩余的链表部分
        ListNode* remaining = curr1 ? curr1 : curr2;
        ListNode* result = curr1 ? l1 : l2;
        
        // 如果还有剩余节点且需要处理进位
        if (remaining && carry) {
            while (remaining && carry) {
                int sum = remaining->val + 1;
                carry = sum == 10;
                remaining->val = carry ? 0 : sum;
                
                // 更新最后一个节点
                lastNode = remaining;
                
                // 如果这是最后一个节点且有进位
                if (!remaining->next && carry) {
                    remaining->next = new ListNode(1);
                    return result;
                }
                
                remaining = remaining->next;
            }
        }
        
        return result;
    }
};
```





## [21. 合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/)



将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg)

```
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
```

**示例 2：**

```
输入：l1 = [], l2 = []
输出：[]
```

**示例 3：**

```
输入：l1 = [], l2 = [0]
输出：[0]
```

 

**提示：**

- 两个链表的节点数目范围是 `[0, 50]`
- `-100 <= Node.val <= 100`
- `l1` 和 `l2` 均按 **非递减顺序** 排列

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // if (!list1) return list2;
        // if (!list2) return list1;
        // ListNode* result = new ListNode(min(list1->val, list2->val));
        // ListNode* rawResult = result;
        // if (list1->val <= list2->val)
        // {
        //     list1 = list1->next;
        // }
        // else
        // {
        //     list2 = list2->next;
        // }
        // while (list1 || list2)
        // {
        //     if (list1 && list2)
        //     {
        //         if (list1->val <= list2->val)
        //         {
        //             result->next = new ListNode(list1->val);
        //             list1 = list1->next;
        //             result = result->next;
        //         }
        //         else
        //         {
        //             result->next = new ListNode(list2->val);
        //             list2 = list2->next;
        //             result = result->next;
        //         }
        //     }
        //     else if (list1)
        //     {
        //         result->next = new ListNode(list1->val);
        //         list1 = list1->next;
        //         result = result->next;
        //     }
        //     else if (list2)
        //     {
        //         result->next = new ListNode(list2->val);
        //         list2 = list2->next;
        //         result = result->next;
        //     }
        // }

        // return rawResult;


        // 直接链接原始节点，不创建新节点，优化内存
        if (!list1) return list2;
        if (!list2) return list1;

        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;

        while (list1 && list2)
        {
            if (list1->val <= list2->val)
            {
                current->next = list1;
                list1 = list1->next;
            }
            else
            {
                current->next = list2;
                list2 = list2->next;
            }

            current = current->next;
        }

        // 处理剩余部分
        current->next = list1 ? list1 : list2;
        // 去除虚拟头部
        ListNode* result = dummy->next;
        delete dummy;
        return result;

    }
};
```







## [138. 随机链表的复制](https://leetcode.cn/problems/copy-list-with-random-pointer/)



给你一个长度为 `n` 的链表，每个节点包含一个额外增加的随机指针 `random` ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 **[深拷贝](https://baike.baidu.com/item/深拷贝/22785317?fr=aladdin)**。 深拷贝应该正好由 `n` 个 **全新** 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 `next` 指针和 `random` 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。**复制链表中的指针都不应指向原链表中的节点** 。

例如，如果原链表中有 `X` 和 `Y` 两个节点，其中 `X.random --> Y` 。那么在复制链表中对应的两个节点 `x` 和 `y` ，同样有 `x.random --> y` 。

返回复制链表的头节点。

用一个由 `n` 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 `[val, random_index]` 表示：

- `val`：一个表示 `Node.val` 的整数。
- `random_index`：随机指针指向的节点索引（范围从 `0` 到 `n-1`）；如果不指向任何节点，则为 `null` 。

你的代码 **只** 接受原链表的头节点 `head` 作为传入参数。

 

**示例 1：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/01/09/e1.png)

```
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
```

**示例 2：**

![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/01/09/e2.png)

```
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
```

**示例 3：**

**![img](https://assets.leetcode.cn/aliyun-lc-upload/uploads/2020/01/09/e3.png)**

```
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
```

 

**提示：**

- `0 <= n <= 1000`
- `-104 <= Node.val <= 104`
- `Node.random` 为 `null` 或指向链表中的节点。

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> oldToNew ;   // 新旧节点指针映射
        Node* dummy = new Node(-1);
        Node* current = dummy;
        while (head)
        {
            Node* temp = new Node(head->val);
            temp->random = head->random;
            oldToNew [head] = temp;
            current->next = temp;
            head = head->next;
            current = current->next;
        }
        // 删除头部虚拟节点
        Node* result = dummy->next;
        delete dummy;
        // 再次遍历，依据指针映射重新拷贝random节点
        Node* current2 = result;
        while (current2)
        {
            current2->random = oldToNew .contains(current2->random) ? oldToNew [current2->random] : nullptr;
            current2 = current2->next;
        }

        return result;
    }
};
```





## [92. 反转链表 II](https://leetcode.cn/problems/reverse-linked-list-ii/)



给你单链表的头指针 `head` 和两个整数 `left` 和 `right` ，其中 `left <= right` 。请你反转从位置 `left` 到位置 `right` 的链表节点，返回 **反转后的链表** 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/02/19/rev2ex2.jpg)

```
输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]
```

**示例 2：**

```
输入：head = [5], left = 1, right = 1
输出：[5]
```

 

**提示：**

- 链表中节点数目为 `n`
- `1 <= n <= 500`
- `-500 <= Node.val <= 500`
- `1 <= left <= right <= n`

 

**进阶：** 你可以使用一趟扫描完成反转吗？

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (right == left) return head;

        ListNode* current = head;
        ListNode* dummy = new ListNode(-1);
        dummy->next = current;
        ListNode* leftNode = nullptr;
        ListNode* preLeftNode = nullptr;
        ListNode* nextRightNode = nullptr;
        ListNode* preNode = dummy;
        for (int i = 1; i <= right; i++)
        {
            if (i == left)
            {
                leftNode = current;
                preLeftNode = preNode;
            }
            
            ListNode* temp = current->next;
            
            if (i>left && i < right)
            {
                current->next = preNode;
            }

            if (i == right)
            {
                preLeftNode->next = current;
                nextRightNode  = current->next;
                current->next = preNode;
            }
            
            preNode = current;
            current = temp;

        }

        leftNode->next = nextRightNode;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
        
    }
};
```







## [25. K 个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/)



给你链表的头节点 `head` ，每 `k` 个节点一组进行翻转，请你返回修改后的链表。

`k` 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 `k` 的整数倍，那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex1.jpg)

```
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex2.jpg)

```
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5]
```

 

**提示：**

- 链表中的节点数目为 `n`
- `1 <= k <= n <= 5000`
- `0 <= Node.val <= 1000`

 

**进阶：**你可以设计一个只用 `O(1)` 额外内存空间的算法解决此问题吗？

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // if (k <= 1) return head;

        // // 先完整遍历一遍，获取到节点个数
        // ListNode* currentNum = head;
        // int n = 0;
        // while (currentNum)
        // {
        //     n++;
        //     currentNum = currentNum->next;
        // }

        // int times = (n/k) * k;

        // ListNode* current = head;
        // ListNode* dummy = new ListNode(-1);
        // dummy->next = current;
        // ListNode* leftNode = nullptr;
        // ListNode* preLeftNode = dummy;
        // ListNode* preNode = dummy;

        // int left = 1;
        // int right = k;
        // for (int i = 1; i <= times; i++)
        // {
        //     ListNode* tempNoe = current->next;
        //     if (i == left)
        //     {
        //         leftNode = current;
        //         // preLeftNode = preNode;
        //         preNode = current;
        //     }
        //     else if (i > left && i < right)
        //     {
        //         current->next = preNode;
        //         preNode = current;
                
        //     }
        //     else if (i == right)
        //     {
                
        //         preLeftNode->next = current;
        //         leftNode->next = current->next;
        //         current->next = preNode;
        //         // 然后重置PreLeftNode为当前节点，方便后续拼接
        //         preLeftNode = leftNode;
        //         left += k;
        //         right += k;
        //     }

        //     current = tempNoe;
        // }

        // ListNode* result = dummy->next;
        // delete dummy;
        // return result;
        

        // 更清晰的头插法版本
        if (k <= 1 || !head) return head;
        
        // 计算链表长度
        int length = 0;
        ListNode* temp = head;
        while (temp) {
            length++;
            temp = temp->next;
        }
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        
        for (int i = 0; i < length / k; i++) {
            ListNode* start = prev->next;  // 当前组的第一个节点
            ListNode* then = start->next;  // 当前组的第二个节点
            
            // 反转k-1次（头插法）
            for (int j = 1; j < k; j++) {
                start->next = then->next;
                then->next = prev->next;
                prev->next = then;
                then = start->next;
            }
            
            prev = start;  // 移动到下一组的前一个节点
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;

    }
};
```







## [19. 删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)



给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```

**示例 2：**

```
输入：head = [1], n = 1
输出：[]
```

**示例 3：**

```
输入：head = [1,2], n = 1
输出：[1]
```

 

**提示：**

- 链表中结点的数目为 `sz`
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

 

**进阶：**你能尝试使用一趟扫描实现吗？

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // unordered_map<int, vector<ListNode*>> idxWithPrevNextPoint;     // 每个索引的前置节点和后续节点的指针
        // ListNode* dummy = new ListNode();
        // dummy->next = head;
        // ListNode* prev = dummy;
        // ListNode* current = head;
        // int i = 0;
        // while (current)
        // {
        //     idxWithPrevNextPoint[i] = {prev, current->next};
        //     prev = current;
        //     current = current->next;
        //     i++;
        // }

        // int delIdx = i - n;
        // vector<ListNode*> nodes = idxWithPrevNextPoint[delIdx];
        // ListNode* toDelNode = nodes[0];
        // delete toDelNode;
        // toDelNode = nullptr;
        // nodes[0]->next = nodes[1];

        // ListNode* result = dummy->next;
        // delete dummy;
        // return result;

        // 上面是使用哈希表来记录节点的前驱和后继信息，这种方法使用了O(n)的额外空间

        // 使用快慢指针来优化空间
        ListNode* dummy = new ListNode();
        dummy->next = head;

        ListNode* fast = dummy;
        ListNode* slow = dummy;

        // 先让快指针行走n+1步
        for (int i = 0; i <= n; i++)
        {
            fast = fast->next;
        }

        // 同时移动fast和slow，直到fast到达末尾
        while (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }

        // 当fast到达末尾时，表明我们的slow指针指向了需要删除的前一个节点处
        ListNode* toDelNode = slow->next;
        slow->next = slow->next->next;

        // 清理内存
        delete toDelNode;
        toDelNode = nullptr;

        ListNode* result = dummy->next;
        delete dummy;
        return result;


    }
};
```





## [82. 删除排序链表中的重复元素 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/)



给定一个已排序的链表的头 `head` ， *删除原始链表中所有重复数字的节点，只留下不同的数字* 。返回 *已排序的链表* 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/01/04/linkedlist1.jpg)

```
输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/01/04/linkedlist2.jpg)

```
输入：head = [1,1,1,2,3]
输出：[2,3]
```

 

**提示：**

- 链表中节点数目在范围 `[0, 300]` 内
- `-100 <= Node.val <= 100`
- 题目数据保证链表已经按升序 **排列**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;
        ListNode* current = head;
        while (current)
        {
            int currentVal = current->val;
            if (current->next && current->next->val == currentVal)
            {
                while (current && (current->val == currentVal))
                {
                    ListNode* toDelNode = current;
                    current = current->next;
                    delete toDelNode;
                    toDelNode = nullptr;
                }
                prev->next = current;
            }
            else
            {
                prev = current;
                current = current->next;
            }
            
        }

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};
```







## [61. 旋转链表](https://leetcode.cn/problems/rotate-list/)



给你一个链表的头节点 `head` ，旋转链表，将链表每个节点向右移动 `k` 个位置。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/11/13/rotate1.jpg)

```
输入：head = [1,2,3,4,5], k = 2
输出：[4,5,1,2,3]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/11/13/roate2.jpg)

```
输入：head = [0,1,2], k = 4
输出：[2,0,1]
```

 

**提示：**

- 链表中节点的数目在范围 `[0, 500]` 内
- `-100 <= Node.val <= 100`
- `0 <= k <= 2 * 109`

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next) return head;

        ListNode* current = head;
        int n = 0;
        while (current)
        {
            n++;
            if (!current->next)
            {
                break;
            }
            current = current->next;
        }
        int times = k % n;
        if (times == 0) return head;

        // 先连接成环
        current->next = head;

        // 定位到需要断开的节点处
        for (int i = 0; i < (n - times); i++)
        {
            current = current->next;
        }

        // 获得旋转后的头部节点
        ListNode* result = current->next;
        // 断开环
        current->next = nullptr;
        return result;

    }
};
```








## [86. 分隔链表](https://leetcode.cn/problems/partition-list/)

给你一个链表的头节点 `head` 和一个特定值 `x` ，请你对链表进行分隔，使得所有 **小于** `x` 的节点都出现在 **大于或等于** `x` 的节点之前。

你应当 **保留** 两个分区中每个节点的初始相对位置。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/01/04/partition.jpg)

```
输入：head = [1,4,3,2,5,2], x = 3
输出：[1,2,2,4,3,5]
```

**示例 2：**

```
输入：head = [2,1], x = 2
输出：[1,2]
```

 

**提示：**

- 链表中节点的数目在范围 `[0, 200]` 内
- `-100 <= Node.val <= 100`
- `-200 <= x <= 200`

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* lessHead = new ListNode(0);
        ListNode* greaterHead = new ListNode(0);
        ListNode* less = lessHead;
        ListNode* greater = greaterHead;
        
        while (head) {
            if (head->val < x) {
                less->next = head;
                less = less->next;
            } else {
                greater->next = head;
                greater = greater->next;
            }
            head = head->next;
        }
        
        // 关键：断开greater链表的尾部连接
        greater->next = nullptr;
        
        // 连接两个链表
        less->next = greaterHead->next;
        
        ListNode* result = lessHead->next;
        delete lessHead;
        delete greaterHead;
        return result;
        
    }
};
```







## [146. LRU 缓存](https://leetcode.cn/problems/lru-cache/)



请你设计并实现一个满足 [LRU (最近最少使用) 缓存](https://baike.baidu.com/item/LRU) 约束的数据结构。

实现 `LRUCache` 类：

- `LRUCache(int capacity)` 以 **正整数** 作为容量 `capacity` 初始化 LRU 缓存
- `int get(int key)` 如果关键字 `key` 存在于缓存中，则返回关键字的值，否则返回 `-1` 。
- `void put(int key, int value)` 如果关键字 `key` 已经存在，则变更其数据值 `value` ；如果不存在，则向缓存中插入该组 `key-value` 。如果插入操作导致关键字数量超过 `capacity` ，则应该 **逐出** 最久未使用的关键字。

函数 `get` 和 `put` 必须以 `O(1)` 的平均时间复杂度运行。

 

**示例：**

```
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
```

 

**提示：**

- `1 <= capacity <= 3000`
- `0 <= key <= 10000`
- `0 <= value <= 105`
- 最多调用 `2 * 105` 次 `get` 和 `put`

```c++
struct Node
{
    int key;
    int val;
    Node* prev;
    Node* next;
    Node(int k, int v)
    {
        key = k;
        val = v;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache {
public:
    LRUCache(int capacity) {
        cacheCapacity = capacity;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache()
    {
        Node* current = head->next;
        while (current != tail)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = nullptr;
        delete tail;
        tail = nullptr;
    }
    
    int get(int key) {
        if (!datamap.contains(key)) return -1;
        Node* current = datamap[key];
        moveToHead(current);       // 移动到头部，标记未最新访问的节点
        return current->val;
    }
    
    void put(int key, int value) {
        if (datamap.contains(key))
        {
            // 如果缓存里已经有该数据，直接更新就行
            Node* current = datamap[key];
            current->val = value;
            moveToHead(current);
        }
        else
        {
            Node* current = new Node(key, value);
            // 查看缓存是否已满
            if (datamap.size() == cacheCapacity)
            {
                Node* tailNode = removeTail();
                datamap.erase(tailNode->key);
                delete tailNode;
            }

            // 添加新节点
            AddToHead(current);
            datamap[key] = current;
        }

    }

private:
    // 使用双向链表维护访问顺序
    Node* head;     // 头部节点指向最近访问的节点
    Node* tail;     // 尾部节点指向最久未访问的节点

    int cacheCapacity;

    // 使用哈希表存储键值(key = 键， value = 节点指针)
    unordered_map<int, Node*> datamap;

    void AddToHead(Node* node)
    {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void RemoveNode(Node* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node)
    {
        RemoveNode(node);
        AddToHead(node);
    }

    Node* removeTail()
    {
        Node* node = tail->prev;
        RemoveNode(node);
        return node;
    }


};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```





## [104. 二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

给定一个二叉树 `root` ，返回其最大深度。

二叉树的 **最大深度** 是指从根节点到最远叶子节点的最长路径上的节点数。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/11/26/tmp-tree.jpg)

 

```
输入：root = [3,9,20,null,null,15,7]
输出：3
```

**示例 2：**

```
输入：root = [1,null,2]
输出：2
```

 

**提示：**

- 树中节点的数量在 `[0, 104]` 区间内。
- `-100 <= Node.val <= 100`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // 方法1：广度优先搜索

    // int maxDepth(TreeNode* root) {
    //     // 要获取二叉树的深度信息，使用广度优先遍历（层序遍历）
    //     // 对于广度优先遍历，我们需要一个辅助队列来进行节点信息存储(后进先出)
    //     std::queue<TreeNode*> nodequeue;
    //     if (root) nodequeue.push(root);
    //     int level = 0;
    //     while (!nodequeue.empty())
    //     {
    //         // 不同于遍历元素每次只取一个元素，要获取层级信息，就需要每次都把队列里的元素清空（每次都需要一次性处理完这一层的节点）
            
    //         int n = nodequeue.size();
    //         for (int i = 0; i < n; i++)
    //         {
    //             // 每次遍历需要从队列里取出头部元素(保证在n次遍历前取到的都是上一个层级的节点)
    //             TreeNode* node = nodequeue.front();
    //             // 获取到元素后就可以让这个元素出列
    //             nodequeue.pop();

    //             // 然后看当前节点是否有左右孩子节点，如果有，就将孩子入列
    //             if (node->left)
    //             {
    //                 nodequeue.push(node->left);
    //             }
    //             if (node->right)
    //             {
    //                 nodequeue.push(node->right);
    //             }
    //         }
    //         level++;

    //     }

    //     return level;
    // }

    // 方法2：深度优先搜索
    int maxDepth(TreeNode* root)
    {
        if (root == nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

};
```







## [100. 相同的树](https://leetcode.cn/problems/same-tree/)

给你两棵二叉树的根节点 `p` 和 `q` ，编写一个函数来检验这两棵树是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/12/20/ex1.jpg)

```
输入：p = [1,2,3], q = [1,2,3]
输出：true
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/12/20/ex2.jpg)

```
输入：p = [1,2], q = [1,null,2]
输出：false
```

**示例 3：**

![img](https://assets.leetcode.com/uploads/2020/12/20/ex3.jpg)

```
输入：p = [1,2,1], q = [1,1,2]
输出：false
```

 

**提示：**

- 两棵树上的节点数目都在范围 `[0, 100]` 内
- `-104 <= Node.val <= 104`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 直接深度优先遍历
        if ((!p && q) || (p && !q)) return false;
        if (!p && !q) return true;
        if (p->val != q->val) return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

    // 使用迭代实现深度遍历（DFS），避免在树的层级过深导致栈溢出的极端情况
    // bool isSameTree(TreeNode* p, TreeNode* q)
    // {
    //     stack<pair<TreeNode*, TreeNode*>> stk;
    //     stk.push({p, q});

    //     while (!stk.empty())
    //     {
    //         auto [node1, node2] = stk.top();
    //         stk.pop();
    //         if (!node1 && !node2) continue;
    //         // 一个为空一个不为空，或者值不同
    //         if (!node1 || !node2 || node1->val != node2->val) return false;
    //         stk.push({node1->left, node2->left});
    //         stk.push({node1->right, node2->right});
    //     }
    //     return true;
    // }

    // // BFS (广度优先)
    // bool isSameTree(TreeNode* p, TreeNode* q)
    // {
    //     queue<pair<TreeNode*, TreeNode*>> que;
    //     que.push({p, q});
        
    //     while (!que.empty()) {
    //         auto [node1, node2] = que.front();
    //         que.pop();
            
    //         // 两个都为空，继续
    //         if (!node1 && !node2) continue;
            
    //         // 一个为空一个不为空，或者值不同
    //         if (!node1 || !node2 || node1->val != node2->val) 
    //             return false;
            
    //         // 子节点入队
    //         que.push({node1->left, node2->left});
    //         que.push({node1->right, node2->right});
    //     }
    //     return true;
    // }
};
```





## [226. 翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/)



给你一棵二叉树的根节点 `root` ，翻转这棵二叉树，并返回其根节点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/03/14/invert1-tree.jpg)

```
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/03/14/invert2-tree.jpg)

```
输入：root = [2,1,3]
输出：[2,3,1]
```

**示例 3：**

```
输入：root = []
输出：[]
```

 

**提示：**

- 树中节点数目范围在 `[0, 100]` 内
- `-100 <= Node.val <= 100`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // // DFS深度优先递归版本
        // if (!root) return root;
        // swap(root->left, root->right);
        // invertTree(root->left);
        // invertTree(root->right);
        // return root;

        // BFS层序遍历版本
        if (!root) return nullptr;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // 交换左右子树
            swap(node->left, node->right);
            
            // 将子节点加入队列
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        return root;
    }
};
```





## [101. 对称二叉树](https://leetcode.cn/problems/symmetric-tree/)



给你一个二叉树的根节点 `root` ， 检查它是否轴对称。

 

**示例 1：**

![img](https://pic.leetcode.cn/1698026966-JDYPDU-image.png)

```
输入：root = [1,2,2,3,4,4,3]
输出：true
```

**示例 2：**

![img](https://pic.leetcode.cn/1698027008-nPFLbM-image.png)

```
输入：root = [1,2,2,null,3,null,3]
输出：false
```

 

**提示：**

- 树中节点数目在范围 `[1, 1000]` 内
- `-100 <= Node.val <= 100`

 

**进阶：**你可以运用递归和迭代两种方法解决这个问题吗？

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;

        // 递归版本（DFS，深度优先），有栈溢出风险
        // return checkIsSymmetric(root->left, root->right);

        // 迭代版本（BFS，广度优先）
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push({root->left, root->right});
        while (!q.empty())
        {
            auto [left, right] = q.front();
            q.pop();
            
            if (!left && !right) continue;
            if (!left || !right) return false;
            if (left->val != right->val) return false;

            // 对称取值
            q.push({left->left, right->right});     // 左节点的左叶子和右节点的右叶子比较
            q.push({left->right, right->left});     // 左节点的右叶子和右节点的左叶子比较
        }

        return true;
    }

private:
    // 对于是否对称，我们只能在第二层开始进行比较
    // 将第二层的左右子树当成两颗独立二叉树进行递归，每次传入的比较节点为，左->左和右->右比较，同时左->右和右->左比较
    // 即对称取值比较
    bool checkIsSymmetric(TreeNode* l, TreeNode* r)
    {
        if ((!l && r) || (l && !r)) return false;
        if (!l && !r) return true;
        if (l->val != r->val) return false;
        return checkIsSymmetric(l->left, r->right) && checkIsSymmetric(l->right, r->left);
    }

};
```







## [105. 从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)



给定两个整数数组 `preorder` 和 `inorder` ，其中 `preorder` 是二叉树的**先序遍历**， `inorder` 是同一棵树的**中序遍历**，请构造二叉树并返回其根节点。

 

**示例 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)

```
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
```

**示例 2:**

```
输入: preorder = [-1], inorder = [-1]
输出: [-1]
```

 

**提示:**

- `1 <= preorder.length <= 3000`
- `inorder.length == preorder.length`
- `-3000 <= preorder[i], inorder[i] <= 3000`
- `preorder` 和 `inorder` 均 **无重复** 元素
- `inorder` 均出现在 `preorder`
- `preorder` **保证** 为二叉树的前序遍历序列
- `inorder` **保证** 为二叉树的中序遍历序列

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 前序遍历的第一个数是当前子树的根节点
        // 在中序遍历中找到这个根节点，根节点的左边部分就是左子树的中序遍历，右部分就是右子树的中序遍历
        // 根据左子树中序遍历的长度，我们可以在前序遍历总确定左子树的前序遍历和右子树的前序遍历
        // 递归的构造左右子树

        // if (preorder.empty() || inorder.empty()) return nullptr;

        // int currentRootVal = preorder[0];
        // // 当前树的根节点
        // TreeNode* root = new TreeNode(currentRootVal);
        // // 取出值后，将该节点从数组中删除
        // preorder.erase(preorder.begin());
        // // 从中序遍历中找到该值所在位置
        // vector<int>::iterator itInorder = find(inorder.begin(), inorder.end(), currentRootVal);
        // // 在该位置左边的都是当前根节点的左子树节点
        // // 然后取出中序遍历里的当前节点左侧的子数组作为左子树的遍历数组
        // vector<int> leftValArray;
        // leftValArray.assign(inorder.begin(), itInorder);
        // root->left = buildTree(preorder, leftValArray);
        // // 左子树构建完后，开始构建右子树
        // vector<int> rightValArray;
        // rightValArray.assign(itInorder + 1, inorder.end());
        // root->right = buildTree(preorder, rightValArray);

        // return root;

        // 建立中序遍历值到索引的映射
        for (int i = 0; i < inorder.size(); i++) {
            indexMap[inorder[i]] = i;
        }
        return helperFunc(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);

    }


private:
    // 上述方法总的来说没有问题，只是每次都要创建新的子数组，这一步很耗时，可以优化一下
    TreeNode* helperFunc(vector<int>& preorder, int preStart, int preEnd,
                        vector<int>& inorder, int inStart, int inEnd)
    {
        if (preStart > preEnd || inStart > inEnd)
        {
            return nullptr;
        }

        // 从前序遍历中获取根节点
        TreeNode* root = new TreeNode(preorder[preStart]);

        // 然后在中序遍历中找到根节点位置
        int rootIdx = indexMap[preorder[preStart]];

        // 计算左子树节点个数
        int leftSize = rootIdx - inStart;

        // 递归构建左右子树
        // 左子树：前序[preStart+1, preStart+leftSize]，中序[inStart, rootIdx-1]
        root->left = helperFunc(preorder, preStart + 1, preStart + leftSize, inorder, inStart, rootIdx - 1);
        // 右子树：前序[preStart+leftSize+1, preEnd]，中序[rootIdx+1, inEnd]
        root->right = helperFunc(preorder, preStart+leftSize+1, preEnd, inorder, rootIdx+1, inEnd);

        // 返回构建好的子树
        return root;
    }

    unordered_map<int, int> indexMap;


};
```





## [106. 从中序与后序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)



给定两个整数数组 `inorder` 和 `postorder` ，其中 `inorder` 是二叉树的中序遍历， `postorder` 是同一棵树的后序遍历，请你构造并返回这颗 *二叉树* 。

 

**示例 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)

```
输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]
```

**示例 2:**

```
输入：inorder = [-1], postorder = [-1]
输出：[-1]
```

 

**提示:**

- `1 <= inorder.length <= 3000`
- `postorder.length == inorder.length`
- `-3000 <= inorder[i], postorder[i] <= 3000`
- `inorder` 和 `postorder` 都由 **不同** 的值组成
- `postorder` 中每一个值都在 `inorder` 中
- `inorder` **保证**是树的中序遍历
- `postorder` **保证**是树的后序遍历

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // 和先序遍历版本的构造思路想同，只不过，对于后续遍历，二叉树的根节点一定在数组的最末尾
        for (int i = 0; i < inorder.size(); i++) {
            indexMap[inorder[i]] = i;
        }
        return helper(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
    }


private:
    unordered_map<int, int> indexMap;
    TreeNode* helper(vector<int>& inorder, int inStart, int inEnd,
                    vector<int>& postorder, int postStart, int postEnd)
    {
        if (inStart > inEnd || postStart > postEnd) return nullptr;

        // 从后续遍历的尾部获取当前子树的根节点
        TreeNode* root = new TreeNode(postorder[postEnd]);
        // 然后在中序遍历中找到根节点位置
        int rootIndex = indexMap[postorder[postEnd]];

        // 计算左子树节点个数
        int leftSize = rootIndex - inStart;
        // 递归构建左右子树
        // 左子树：中序[inStart, rootIndex-1]，后序[postStart, postStart+leftSize-1]
        root->left = helper(inorder, inStart, rootIndex - 1, postorder, postStart, postStart+leftSize-1);
        // 右子树：中序[rootIndex+1, inEnd]，后序[postStart+leftSize, postEnd-1]
        root->right = helper(inorder, rootIndex+1, inEnd, postorder, postStart+leftSize, postEnd-1);

        // 返回构建好的子树
        return root;

    }


};
```





## [117. 填充每个节点的下一个右侧节点指针 II](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/)



给定一个二叉树：

```
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
```

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 `NULL` 。

初始状态下，所有 next 指针都被设置为 `NULL` 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2019/02/15/117_sample.png)

```
输入：root = [1,2,3,4,5,null,7]
输出：[1,#,2,3,#,4,5,7,#]
解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。序列化输出按层序遍历顺序（由 next 指针连接），'#' 表示每层的末尾。
```

**示例 2：**

```
输入：root = []
输出：[]
```

 

**提示：**

- 树中的节点数在范围 `[0, 6000]` 内
- `-100 <= Node.val <= 100`

**进阶：**

- 你只能使用常量级额外空间。
- 使用递归解题也符合要求，本题中递归程序的隐式栈空间不计入额外空间复杂度。

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        // if (!root) return root;

        // std::queue<Node*> q;
        // q.push(root);
        // while (!q.empty())
        // {
        //     // 使用层序遍历（广度优先搜索），每次都完整遍历当前层级里的所有节点
        //     int levelNodeNums = q.size();
        //     Node* preNode = nullptr;
        //     while (levelNodeNums)
        //     {
        //         Node* current = q.front();
        //         q.pop();
        //         if (preNode)
        //         {
        //             preNode->next = current;
        //         }
        //         preNode = current;
        //         levelNodeNums--;

        //         // 将当前节点的子节点添加到队列末尾
        //         if (current->left) q.push(current->left);
        //         if (current->right) q.push(current->right);
        //     }
            
        // }

        // return root;

        // 上述实现方式使用广度优先搜索，需要使用O(W)的额外空间（w是该树的最大宽度）
        // 如果需要在常数级别的额外空间实现该算法，可以考虑使用已经建立的next指针
        if (!root) return root;

        Node* leftMost = root;

        while (leftMost)
        {
            Node* current = leftMost;
            Node* prev = nullptr;
            Node* nextLeftMost = nullptr;

            // 遍历当前层，建立下一层的链接
            while (current)
            {
                // 处理左子节点
                if (current->left)
                {
                    if (prev)
                    {
                        prev->next = current->left;
                    }
                    else
                    {
                        nextLeftMost = current->left;
                    }
                    prev = current->left;
                }

                // 处理右子节点
                if (current->right)
                {
                    if (prev)
                    {
                        prev->next = current->right;
                    }
                    else
                    {
                        nextLeftMost = current->right;
                    }
                    prev = current->right;
                }

                current = current->next;        // 移动到当前层级的下一个节点
            }

            // 当前层遍历完毕，移动到下一层
            leftMost = nextLeftMost;
            
        }

        return root;


    }
};
```









## [114. 二叉树展开为链表](https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/)



给你二叉树的根结点 `root` ，请你将它展开为一个单链表：

- 展开后的单链表应该同样使用 `TreeNode` ，其中 `right` 子指针指向链表中下一个结点，而左子指针始终为 `null` 。
- 展开后的单链表应该与二叉树 [**先序遍历**](https://baike.baidu.com/item/先序遍历/6442839?fr=aladdin) 顺序相同。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/01/14/flaten.jpg)

```
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [0]
输出：[0]
```

 

**提示：**

- 树中结点数在范围 `[0, 2000]` 内
- `-100 <= Node.val <= 100`

 

**进阶：**你可以使用原地算法（`O(1)` 额外空间）展开这棵树吗？

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root) {
        // 对于当前节点，如果左子树不为空，那么我们需要将其插入到当前节点和右子树之间
        // 找到当前节点左子树的最右节点（即左子树中最后一个被访问的节点，也就是左子树中值最大的节点）
        // 但是这里不是BST，只是按照前序遍历的顺序，左子树的最右节点在访问时是左子树的最后一个节点
        // 将当前节点的右子树接到左子树的最右节点上
        // 将当前节点的左子树放到当前节点的右子树位置，将左子树置空
        // 重复上述过程，直到节点为空
        TreeNode* current = root;
        while (current)
        {
            if (current->left)
            {
                // 找到最右节点
                TreeNode* pre = current->left;
                while (pre->right)
                {
                    pre = pre->right;
                }
                // 将当前节点的右子树拼接到左子树最右节点处
                pre->right = current->right;
                // 将左子树移动到右子树位置
                current->right = current->left;
                current->left = nullptr;
            }
            // 处理下一个节点
            current = current->right;
        }

        // // 递归版本
        // if (!root) return;
        // // 先处理右子树，在处理左子树(类似后序遍历，)
        // flatten(root->right);
        // flatten(root->left);

        // // 将前一个拼接到当前节点节点的右侧
        // root->right = prev;
        // root->left = nullptr;
        // prev = root;
    }

private:
    TreeNode* prev = nullptr;

};
```





## [112. 路径总和](https://leetcode.cn/problems/path-sum/)

给你二叉树的根节点 `root` 和一个表示目标和的整数 `targetSum` 。判断该树中是否存在 **根节点到叶子节点** 的路径，这条路径上所有节点值相加等于目标和 `targetSum` 。如果存在，返回 `true` ；否则，返回 `false` 。

**叶子节点** 是指没有子节点的节点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/01/18/pathsum1.jpg)

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
解释：等于目标和的根节点到叶节点路径如上图所示。
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/01/18/pathsum2.jpg)

```
输入：root = [1,2,3], targetSum = 5
输出：false
解释：树中存在两条根节点到叶子节点的路径：
(1 --> 2): 和为 3
(1 --> 3): 和为 4
不存在 sum = 5 的根节点到叶子节点的路径。
```

**示例 3：**

```
输入：root = [], targetSum = 0
输出：false
解释：由于树是空的，所以不存在根节点到叶子节点的路径。
```

 

**提示：**

- 树中节点的数目在范围 `[0, 5000]` 内
- `-1000 <= Node.val <= 1000`
- `-1000 <= targetSum <= 1000`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        int targetSumTemp = targetSum - root->val;
        if (!root->left && !root->right && targetSumTemp == 0) return true; 

        return hasPathSum(root->left, targetSumTemp) || hasPathSum(root->right, targetSumTemp);
    }


};
```





## [129. 求根节点到叶节点数字之和](https://leetcode.cn/problems/sum-root-to-leaf-numbers/)



给你一个二叉树的根节点 `root` ，树中每个节点都存放有一个 `0` 到 `9` 之间的数字。

每条从根节点到叶节点的路径都代表一个数字：

- 例如，从根节点到叶节点的路径 `1 -> 2 -> 3` 表示数字 `123` 。

计算从根节点到叶节点生成的 **所有数字之和** 。

**叶节点** 是指没有子节点的节点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/02/19/num1tree.jpg)

```
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径 1->2 代表数字 12
从根到叶子节点路径 1->3 代表数字 13
因此，数字总和 = 12 + 13 = 25
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/02/19/num2tree.jpg)

```
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径 4->9->5 代表数字 495
从根到叶子节点路径 4->9->1 代表数字 491
从根到叶子节点路径 4->0 代表数字 40
因此，数字总和 = 495 + 491 + 40 = 1026
```

 

**提示：**

- 树中节点的数目在范围 `[1, 1000]` 内
- `0 <= Node.val <= 9`
- 树的深度不超过 `10`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode* root, int sum = 0) {
        if (!root) return 0;
        sum = sum * 10 + root->val;

        if (!root->left && !root->right) return sum;

        return sumNumbers(root->left, sum) + sumNumbers(root->right, sum);

    }


};
```







## [124. 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)



二叉树中的 **路径** 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 **至多出现一次** 。该路径 **至少包含一个** 节点，且不一定经过根节点。

**路径和** 是路径中各节点值的总和。

给你一个二叉树的根节点 `root` ，返回其 **最大路径和** 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/13/exx1.jpg)

```
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg)

```
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
```

 

**提示：**

- 树中节点数目范围是 `[1, 3 * 104]`
- `-1000 <= Node.val <= 1000`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        maxSum = INT_MIN;
        dfs(root);
        return maxSum;
    }

private:
    int maxSum = 0;

    // 使用递归。对于每个节点，我们计算以该节点为“根”的路径的最大和（即从该节点出发向下延伸的路径）。同时，在递归过程中，我们更新全局最大路径和。
    // 虽然是这么说，但是这是该算法的直观解法，实际我们并不能真的从每个节点为跟作为新的树进行遍历了，因为要这样做，我们就得基于此构建一颗新树
    // 对于每个节点，我们计算以该节点为“根”的路径的最大和，即节点值加上左子树的最大路径和（如果左子树的最大路径和大于0）加上右子树的最大路径和（如果右子树的最大路径和大于0）。
    // 注意：这里左子树的最大路径和是指从该节点左孩子出发向下延伸的路径（不能同时走左右两边，因为这样就不是一条路径了）。但是，当我们计算以该节点为“根”的路径时，我们可以同时走左右两边，因为从该节点出发，向左走一段再向右走一段，仍然是一条路径（相当于以该节点为转折点）
    // 然而，在递归返回时，我们只能返回从该节点出发向下的单边路径的最大和（即只能选择左或右的一边），因为要供上层节点使用（上层节点需要的是从它出发向下的一条路径）
    
    int dfs(TreeNode* node)
    {
        if (!node) return 0;

        // 计算左右子树的贡献值（复值则取0）
        int left_gain = max(dfs(node->left), 0);
        int right_gain = max(dfs(node->right), 0);

        // 当前节点为转折点的路径和
        int current_path_sum = node->val + left_gain + right_gain;

        // 更新全局最大值
        maxSum = max(maxSum, current_path_sum);

        // 返回当前节点的最大贡献值
        return node->val + max(left_gain, right_gain); 

    }




};
```





## [173. 二叉搜索树迭代器](https://leetcode.cn/problems/binary-search-tree-iterator/)



实现一个二叉搜索树迭代器类`BSTIterator` ，表示一个按中序遍历二叉搜索树（BST）的迭代器：

- `BSTIterator(TreeNode root)` 初始化 `BSTIterator` 类的一个对象。BST 的根节点 `root` 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
- `boolean hasNext()` 如果向指针右侧遍历存在数字，则返回 `true` ；否则返回 `false` 。
- `int next()`将指针向右移动，然后返回指针处的数字。

注意，指针初始化为一个不存在于 BST 中的数字，所以对 `next()` 的首次调用将返回 BST 中的最小元素。

你可以假设 `next()` 调用总是有效的，也就是说，当调用 `next()` 时，BST 的中序遍历中至少存在一个下一个数字。

 

**示例：**

![img](https://assets.leetcode.com/uploads/2018/12/25/bst-tree.png)

```
输入
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
输出
[null, 3, 7, true, 9, true, 15, true, 20, false]

解释
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // 返回 3
bSTIterator.next();    // 返回 7
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 9
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 15
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 20
bSTIterator.hasNext(); // 返回 False
```

 

**提示：**

- 树中节点的数目在范围 `[1, 105]` 内
- `0 <= Node.val <= 106`
- 最多调用 `105` 次 `hasNext` 和 `next` 操作

 

**进阶：**

- 你可以设计一个满足下述条件的解决方案吗？`next()` 和 `hasNext()` 操作均摊时间复杂度为 `O(1)` ，并使用 `O(h)` 内存。其中 `h` 是树的高度。

```c++
// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  * };
//  */
//  #include <coroutine>

// class BSTIterator {
// public:
// private:
//     // 协程生成器类型
//     struct Generator {
//         struct promise_type {
//             int current_value;
            
//             Generator get_return_object() {
//                 return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
//             }
//             std::suspend_always initial_suspend() { return {}; }
//             std::suspend_always final_suspend() noexcept { return {}; }
//             void unhandled_exception() { std::terminate(); }
            
//             std::suspend_always yield_value(int value) {
//                 current_value = value;
//                 return {};
//             }
//             void return_void() {}
//         };
        
//         std::coroutine_handle<promise_type> handle;
        
//         explicit Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
//         ~Generator() { if (handle) handle.destroy(); }
        
//         Generator(const Generator&) = delete;
//         Generator& operator=(const Generator&) = delete;
//         Generator(Generator&& other) noexcept : handle(other.handle) {
//             other.handle = nullptr;
//         }
//         Generator& operator=(Generator&& other) noexcept {
//             if (this != &other) {
//                 if (handle) handle.destroy();
//                 handle = other.handle;
//                 other.handle = nullptr;
//             }
//             return *this;
//         }
        
//         bool move_next() {
//             if (handle && !handle.done()) {
//                 handle.resume();
//                 return !handle.done();
//             }
//             return false;
//         }
        
//         int current_value() const {
//             return handle.promise().current_value;
//         }
        
//         bool done() const {
//             return !handle || handle.done();
//         }
//     };
    
//     Generator generator;
    
//     // 中序遍历协程
//     static Generator inorder_traversal(TreeNode* root) {
//         std::stack<TreeNode*> stack;
//         TreeNode* current = root;
        
//         while (current || !stack.empty()) {
//             while (current) {
//                 stack.push(current);
//                 current = current->left;
//             }
            
//             current = stack.top();
//             stack.pop();
            
//             co_yield current->val;  // 在这里暂停，等待下一次调用
            
//             current = current->right;
//         }
//     }
    
// public:
//     BSTIterator(TreeNode* root) : generator(inorder_traversal(root)) {
//         // 初始化时先让协程运行到第一个yield
//         if (root) generator.move_next();
//     }
    
//     // 获取下一个值
//     int next() {
//         if (generator.done()) {
//             throw std::out_of_range("No more elements");
//         }
        
//         int value = generator.current_value();
//         generator.move_next();
//         return value;
//     }
    
//     // 检查是否还有下一个元素
//     bool hasNext() const {
//         return !generator.done();
//     }
    
//     // 重置迭代器
//     void reset(TreeNode* root) {
//         if (generator.handle) {
//             generator.handle.destroy();
//         }
//         generator = inorder_traversal(root);
//         if (root) generator.move_next();
//     }
// };

// /**
//  * Your BSTIterator object will be instantiated and called as such:
//  * BSTIterator* obj = new BSTIterator(root);
//  * int param_1 = obj->next();
//  * bool param_2 = obj->hasNext();
//  */


class BSTIterator {
private:
    std::stack<TreeNode*> st;
    
    // 将节点的所有左子节点压入栈
    void pushAllLeft(TreeNode* node) {
        while (node)
        {
            st.push(node);
            node = node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        pushAllLeft(root);
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode* topNode = st.top();
        st.pop();
        // 如果当前节点有右子树
        if (topNode->right)
        {
            pushAllLeft(topNode->right);
        }
        return topNode->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !st.empty();
    }
};
```





## [222. 完全二叉树的节点个数](https://leetcode.cn/problems/count-complete-tree-nodes/)



给你一棵 **完全二叉树** 的根节点 `root` ，求出该树的节点个数。

[完全二叉树](https://baike.baidu.com/item/完全二叉树/7773232?fr=aladdin) 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 `h` 层（从第 0 层开始），则该层包含 `1~ 2h` 个节点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/01/14/complete.jpg)

```
输入：root = [1,2,3,4,5,6]
输出：6
```

**示例 2：**

```
输入：root = []
输出：0
```

**示例 3：**

```
输入：root = [1]
输出：1
```

 

**提示：**

- 树中节点的数目范围是`[0, 5 * 104]`
- `0 <= Node.val <= 5 * 104`
- 题目数据保证输入的树是 **完全二叉树**

 

**进阶：**遍历树来统计节点是一种时间复杂度为 `O(n)` 的简单解决方案。你可以设计一个更快的算法吗？

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        int count = 0;
        std::function<void(TreeNode*)> factorial = [&](TreeNode* node)->void
        {
            if (!node) return;
            count++;
            factorial(node->left);
            factorial(node->right);
        };

        factorial(root);
        return count;

    }

};
```





## [236. 二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/)



给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

[百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
```

**示例 3：**

```
输入：root = [1,2], p = 1, q = 2
输出：1
```

 

**提示：**

- 树中节点数目在范围 `[2, 105]` 内。
- `-109 <= Node.val <= 109`
- 所有 `Node.val` `互不相同` 。
- `p != q`
- `p` 和 `q` 均存在于给定的二叉树中。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || p == root || q == root) return root;
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right) return root;
        
        return left ? left : right;
    }
};
```





## [199. 二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/)

给定一个二叉树的 **根节点** `root`，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

 

**示例 1：**

**输入：**root = [1,2,3,null,5,null,4]

**输出：**[1,3,4]

**解释：**

![img](https://assets.leetcode.com/uploads/2024/11/24/tmpd5jn43fs-1.png)

**示例 2：**

**输入：**root = [1,2,3,4,null,null,null,5]

**输出：**[1,3,4,5]

**解释：**

![img](https://assets.leetcode.com/uploads/2024/11/24/tmpkpe40xeh-1.png)

**示例 3：**

**输入：**root = [1,null,3]

**输出：**[1,3]

**示例 4：**

**输入：**root = []

**输出：**[]

 

**提示:**

- 二叉树的节点个数的范围是 `[0,100]`
- `-100 <= Node.val <= 100` 

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        queue<TreeNode*> q;
        q.push(root);

        vector<int> result;
        while (!q.empty())
        {
            int n = q.size();
            int value = 0;
            while (n--)
            {
                TreeNode* node = q.front();
                value = node->val;
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(value);
        }

        return result;
    }
};
```


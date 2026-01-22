// Chapter 7: STL (標準模板庫)

// 在 C 語言裡，如果你想要一個「長度可以隨意變大變小」的陣列
// 你得用 malloc + realloc 寫到哭。 
// 在 C++ 裡，我們用 std::vector，一行搞定。

// 1. 超級陣列：Vector
// vector 是 C++ 最重要的容器。你可以把它想像成一個**「有彈性的陣列」**。
// Header: #include <vector>
// 特色:
// a. 不用管記憶體 (自動 new/delete)。
// b. 不用管大小 (塞東西進去，它自動變大)。
// c. 依然可以用 [] 來存取。
// 語法筆記 :
// 這裡你會看到尖括號 < >，這叫 Template (樣板)
// vector<int> 意思就是：「我要一個裝 int 的 vector」
// vector<Player*> 意思就是：「我要一個裝 Player指標 的 vector」。

// 程式碼範例:
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 宣告一個整數 vector (一開始是空的)
    vector<int> v;

    // 塞資料 (push_back)
    // 它會自動排隊塞在尾端，如果空間不夠，它會自動搬家擴充
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    cout << "現在陣列大小: " << v.size() << endl;  // 輸出 3

    // 修改資料 (就像用陣列一樣)
    v[0] = 99;

    // 刪除最後一個元素
    v.pop_back();  // 30 被移除了，大小變回 2

    return 0;
}


// 2. 超級字串：String
// 你以前在 C 語言寫字串處理，是不是很怕：
// a. 忘記寫 \0 (Null Terminator)。
// b. strcat 接字串時 buffer 不夠大，直接炸掉 (Buffer Overflow)。
// c. strcmp 回傳 0 才是相等，很反直覺。
// C++ 的 std::string 把這些問題全解了。
// Header: #include <string>

// 程式碼範例:
#include <iostream>
#include <string>
using namespace std;
int main() {
    // 宣告與賦值
    string s1 = "Hello";
    string s2 = "world";

    // 字串相接 (直接用 + 號)
    string s3 = s1 + ", " + s2 + "!";
    cout << s3 << endl; // 輸出: Hello, World!

    // 字串比對 (直接用 ==)
    if (s1 == "Hello") {
        cout << "是 Hello 沒錯！" << endl;
    }

    // 取得長度
    cout << "長度: " << s3.length() << endl;

    // 也可以像陣列一樣修改裡面某個字
    s1[0] = 'h'; // 變成了 "hello"

    return 0;
}


// 3. 現代化的走訪 (Range-based for loop)
// 既然用了 Vector 和 String
// C++11 提供了一種超帥的迴圈寫法，讓你不用再寫 i = 0; i < n; i++。
// 這叫做 「範圍迴圈 (Range-based for loop)」。

// 程式碼範例:
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> score = {10,20,30,40,50};
    
    // 【新式寫法 (C++ Style)】：
    // 翻譯：把 scores 裡面的東西，一個一個拿出來放到 x 裡
    // "auto" 是自動推斷型別 (編譯器知道它是 int)
    for (auto x : score) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

// 總結:
// A. Vector: 用來取代 malloc 出來的動態陣列。用 push_back 加資料，用 size() 看大小。
// B. String: 用來取代 char*。用 + 接字串，用 == 比對。
// C. Auto: 讓編譯器自己猜型別，寫迴圈超方便。

// Chapter 8: 萬用的模具 (Templates)

// 1. 發現痛點：重複勞動
// 假設你要寫一個「加法」函式。
// 為了整數，你寫了 int add(int a, int b) { return a + b; }
// 為了浮點數，你又要寫 double add(double a, double b) { return a + b; }
// 邏輯明明一模一樣，只因為型別不同，就要複製貼上好幾遍？這太笨了。
// 在 C++ 裡，我們可以製作一個 「模具 (Template)」，把型別留空，等要用的時候再填進去。

// 2. 函式樣板 (Function Template)
// 我們用一個代號 T 來代表「任意型別」。
// 語法關鍵字：template <typename T> (或者寫 <class T> 也可以，意思一樣)。
// 意思：接下來的這個函式，裡面用到 T 的地方，請把它當作一個「未知的型別」。
// 程式碼範例 :
#include <iostream>
#include <string>
using namespace std;
// 【宣告樣板】：告訴編譯器，T 是一個待定的型別
template <typename T>
T add(T a, T b) {
    return a+b;   // 不管 a, b 是什麼，反正把它們加起來回傳就對了
}
int main() {
    // 用在整數 (T 自動變成 int)
    cout << "Int: " << add(10, 20) << endl;

    // 用在浮點數 (T 自動變成 double)
    cout << "Double: " << add(1.5, 2.5) << endl;

    // 用在字串 (T 自動變成 string)
    string s1 = "Hello ";
    string s2 = "World";
    cout << "String: " << add(s1, s2) << endl;

    return 0;
}
// 編譯器非常聰明。當你呼叫 add(10, 20) 時，它發現參數是 int
// 它就會在背後偷偷幫你寫出一個 int 版本的函式。
// 這叫做「樣板具現化 (Instantiation)」

// 3. 類別樣板 (Class Template)
// 這就是 vector 的原理。我們也可以設計一個「萬能容器」。
// 假設我們想做一個簡單的 Box (盒子)，裡面可以裝任何東西。
// 程式碼範例：萬能盒子
#include <iostream>
using namespace std;
// 定義一個樣板類別
template <typename T>
class Box {
private:
    T item;  // 盒子裡裝的東西，型別是 T (未知)
public:
    // 建構子：把東西裝進去
    Box(T i) : item(i) {}

    // 把東西印出來
    void show() {
        cout << "盒子裡裝的是: " << item << endl;
    }
};
int main() {
    //【使用樣板類別時，必須在 < > 明確指定型別】
    // 1. 裝整數的盒子
    Box<int> intBox(100);
    intBox.show();

    // 2. 裝浮點數的盒子
    Box<double> doubleBox(3.14159);
    doubleBox.show();

    // 3. 裝字元 (char) 的盒子
    Box<char> charBox('A');
    charBox.show();

    return 0;
}

// 4. 進階：多個代號
// 如果不只一種型別怎麼辦？例如 Map (字典) 需要一個 Key 和一個 Value。 
// 我們可以定義多個代號，用逗號隔開：template <typename K, typename V>。
// 程式碼範例 :
#include <iostream>
using namespace std;
template <typename T1, typename T2>
void printPair(T1 a, T2 b) {
    cout << "第一個是: " << a << ", 第二個是: " << b << endl;
}

int main() {
    // T1 是 string, T2 是 int
    printPair("年齡", 18); 
    
    // T1 是 double, T2 是 double
    printPair(3.5, 4.5);
    
    return 0;
}

// 總結:
// 為什麼要用 Template？ 為了「程式碼重用」。不要因為型別不同就重寫一樣的邏輯。
// 核心語法： template <typename T>。把 T 當作一個佔位符 (Placeholder)，以後再填空。
// 兩種應用：
// Function Template: add(1, 2) (通常編譯器會自動推導，不用寫 <int>)。
// Class Template: vector<int>, Box<double> (必須明確寫出 <...> 來指定型別)。

// 現在知道為什麼 vector 後面要加 <int> 了吧？
// 因為 vector 本身就是一個寫好的 Class Template

// 不需要從變數宣告或 if-else 這種基礎重頭教起，
// 而是專注於 C++ 如何改良 C 的痛點（如字串處理、記憶體管理），以及最重要的「物件導向」與「STL（標準模板庫）」。

// Chapter 1: C++ 的見面禮 (I/O 與 參考)

// 1. 輸入與輸出 (cin / cout)
// 核心觀念： 
// C++ 使用「串流 (Stream)」的概念來處理輸入輸出。
// 你不需要再像 C 語言那樣去記 %d (整數)、%s (字串) 或 %f (浮點數) 這種格式控制符，編譯器會自動判斷變數型態。

// 與 C 的差異：
// C: printf("Age: %d", age); (容易寫錯格式，例如把 float 印成 int)。
// C++: std::cout << "Age: " << age; (自動識別，型別安全)。

// 範例:
#include <iostream>  // C++ 的標準輸入輸出函式庫 (取代 stdio.h)
using namespace std;  // 讓我們可以直接用 cout 而不用打 std::cout (固定會寫的)
int main() {
    int age;
    float height;

    // 輸出 (cout = console out)
    // "<<" 的方向代表資料流向螢幕
    cout << "Enter your age and height: ";

    // 輸入 (cin = console in)
    // ">>" 的方向代表資料流向變數
    // 可以連續輸入，不需要像 scanf 那樣寫 &age (除非是指標，但 cin 幫你處理好了)
    cin >> age >> height;
    cout<<"Your are "<<age<<" years old, your height is "<<height<<" cm."<<endl; // endl = 換行

    return 0;
}


// 2. 參考 (reference)
// 這是一個在 C 語言沒看過，但在 C++ 極度重要的觀念。
// 核心觀念：
// 「參考」就是一個變數的別名 (Alias)。
// 說白了，它就是「不需要解參照 (dereference) 的指標」。
// 一旦你把一個參考綁定到一個變數上，操作這個參考就等於操作原本那個變數。

// 為什麼要學:
// 在 C 語言中，如果你想在函式裡修改外面的變數，你必須傳指標
// C++ 的 Reference 讓你像用普通變數一樣簡單，但卻能達到「修改原始數值」的效果。

// 語法對照：
// int &ref = a;  (讀作：ref 是 a 的參考)

// 範例(交換數值 Swap):
#include <iostream>
using namespace std;
// 這裡的 & 不是「取地址」，而是「宣告這是一個參考」
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
int main() {
    int x = 10;
    int y = 20;
    // 很直覺，直接傳變數，就像傳值一樣簡單
    swap(x,y);
    cout << "x:"<< x << " , y:" << y << endl;
    return 0;
}


// 本章總結
// 1. Header 變了：用 #include <iostream> 取代 #include <stdio.h>。
// 2. I/O 變簡單：cin (輸入) 和 cout (輸出) 自動判斷型別，不用背 %d。
// 3. Reference (參考)：它是變數的別名。
// 在函式參數中使用 type &name，可以讓我們直接修改外部變數，卻不用處理討厭的指標符號 * 和 &。


// Reference 補充筆記：指標 vs. 參考
// 範例一：唯讀的效率傳輸 (const Reference)
// 在 C 語言中，如果你有一個很大的 struct 要傳進函式，為了避免複製整份資料（效能差），
// 你會傳「指標」。但缺點是函式內部可能不小心改到它，而且要用 -> 來取值。
// C++ 的 const Reference 完美解決了這個問題：「我不複製資料（像指標一樣快），
// 但我保證不修改它（像傳值一樣安全），而且寫法很乾淨。」
#include <iostream>
using namespace std;
struct player {
    int hp;
    int mp;
    int exp;
};
//【C++ 寫法】：傳 const 參考 (const Reference)
// 優點：
// 1. & 代表只傳地址 (不複製 struct，省效能)
// 2. const 代表唯讀 (保證不會偷改 hp)
// 3. 用法像普通變數 (直接用 . )
void showplayer(const player &p) {
    cout<<"HP: "<<p.hp<<endl;
}
int main() {
    player hero = {100,50,0};
    showplayer(hero);
    return 0;
}
// 核心觀念： 
// 以後在 C++ 看到函式參數寫 const string &s 或 const Vector &v，就是這個意思：「我只讀不改，而且我不複製。」

// 範例二：參考的「忠誠度」 (不能重導向)
// 參考是「死忠粉」，一旦初始化綁定誰，這輩子就是誰的分身，不能換人。
#include <iostream>
using namespace std;
int main() {
    int a = 10;
    int b = 20;
    int &ref = a;  // 參考 ref 綁定 a (ref 從此就是 a 的分身)

    // 這行 *不是* 讓 ref 改指 b！
    // 這裡是說：「把 b 的值，指派給 ref (也就是 a)」
    // 所以，a 的值變成了 b 目前的值 (20)。ref 依然是 a 的分身。
    ref = b;

    cout<<"a: "<<a<<endl;  // a 被改成 20 了
    cout <<"Address of ref: "<<&ref<<endl;  // 地址跟 a 一模一樣
    return 0;
}
// 核心觀念： 
// 參考必須在宣告時就初始化（int &r = a;），而且之後永遠不能改變指向的對象。
// 如果你需要可以隨時切換指向目標的功能，那你還是得用指標。
// 只有這 3 種情況：請退回去用「指標 (Pointer)」
// 情況 A：你需要「空值」(nullptr)
// 情況 B：你需要「更換指向的對象」
// 情況 C：相容 C 語言舊程式庫

// 範例三：參考作為回傳值 (進階應用)
// 既然參考就是變數本身，那如果函式回傳的是「參考」，就代表我們可以把函式呼叫放在等號的左邊（L-value)
#include <iostream>
using namespace std;
int arr[5] = {1,2,3,4,5};
// 回傳 arr[index] 的「參考」(也就是那個記憶體位置本身，而不是數值的複製)
int &getElement(int index) {
    return arr[index];
}
int main() {
    // 因為回傳的是 Reference，所以可以直接賦值給它
    getElement(2) = 99;
    cout<<"arr[2]: "<<arr[2]<<endl;  // output 99
    return 0;
}
// 注意：千萬不要回傳區域變數 (Local Variable) 的參考。
// 因為函式結束後，區域變數就被銷毀了，你的參考會變成「懸空參考 (Dangling Reference)」
// 這跟 C 語言「回傳區域變數的指標」是一樣嚴重的錯誤。

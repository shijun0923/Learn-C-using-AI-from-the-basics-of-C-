// C 語言看重的是「流程 (Procedure)」
// C++ 看重的是「物件 (Object)」。
// 這章的目標，就是把你在 C 語言寫的 struct 進行超級進化

// Chapter 2: 封裝的藝術 (Class & Object)

// 1. 觀念進化：從 Struct 到 Class
// C 語言的作法 (資料與動作分離)：
// 你定義一個 struct Student (只有資料)，然後另外寫一堆函式像來操作它。
// 資料是死的，函式是活的，它們分家。
// C++ 的作法 (資料與動作合體)：
// 我們認為「學生」不應該只是一堆數據，學生應該自帶功能（自己會印成績單、自己會算平均分
// 所以，我們把「變數 (Data)」和「函式 (Function)」包在同一個大括號裡，這就是 Class (類別)。

// 2. 權限控制：Public vs. Private
// 這是 C 語言完全沒有的概念。在 C 語言的 struct 裡，所有資料都是「裸奔」的，任何人都能隨意修改 s.score = -100
// C++ 引入了「存取權限」，把不該被外面亂動的資料鎖起來，只開放安全的窗口。
// private (私有)：只有 Class 內部自己的函式可以存取。
// public (公開)：外面的 main 函式可以用。

// 實戰程式碼：銀行帳戶
#include <iostream>
#include <string>
using namespace std;
// 定義一個 Class (類別) -> 這只是設計圖，還不是真正的記憶體物件
class bankaccount {
private:
// 【私有區】：這裡的東西，main 函式完全看不到，也改不了
// 這就是「封裝 (Encapsulation)」：把細節藏起來
    string owner;
    int balance;

public:
// 【公開區】：這是對外的「介面 (Interface)」，大家只能透過這些函式來操作
    // 這是「設定資料」的函式，我們可以在這裡做檢查！
    void init(string n, int amount) {
        owner = n;
        if (amount<0) {
            balance = 0;  // 防呆：不能有負的開戶金
            cout<<"Error!"<<endl;
        }
        else {
            balance = amount;
        }
    }

    // 存款功能
    void deposit(int amount) {
        if (amount>0) {
            balance += amount;
            cout<<owner<<" have deposited "<<amount<<" dollars."<<endl;
        }
    }

    // 查詢功能 (只讀不改)
    void showbalence() {
        cout<<"Recent balance: "<<balance<<" dollars."<<endl;
    }
};
int main() {
    // 這時候記憶體才真正被分配出來
    bankaccount account1;
    account1.init("Justin", 1000);

    account1.deposit(500);
    account1.showbalence();

    // 嘗試駭客行為
    // account1.balance = 9999999; 
    // [錯誤]：'int BankAccount::balance' is private
    // 編譯器直接擋下來：除了 BankAccount 內部的函式，誰都不准碰 balance！
}

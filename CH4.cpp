// Chapter 4: 記憶體新法 (New & Delete)

// 學習 C++ 是如何讓動態記憶體管理變得「像人話一樣」簡單。

// 1. 核心觀念：New 的「二步曲」
// 當你寫下 new Pet(); 時，C++ 實際上在後台幫你做了兩件大事，順序非常重要：
// 分配空間 (Allocation)：先去 Heap (堆積區) 找一塊足夠大的空地。
// 呼叫建構子 (Construction)：立刻在那塊空地上執行建構子，把物件初始化（設定數值、買裝備）。
// 結果：回傳一個指向該物件的「指標 (Pointer)」。

// 2. 核心觀念：Delete 的「二步曲」
// 當你寫下 delete ptr; 時，C++ 也幫你做了兩件事，順序是反過來的：
// 呼叫解構子 (Destruction)：先執行物件的遺言（釋放內部資源、關檔）。
// 釋放空間 (Deallocation)：把這塊地皮還給作業系統。
// 筆記：這就是為什麼 C++ 的動態物件有靈魂，因為它們經歷了完整的生與死。

// 語法筆記 :
// 假設有一個簡單的 player 類別。
// A. 針對「單一物件」
// new :  player* p = new player("Hero");
// delete : delete p;

// B. 針對「陣列物件」 (注意括號)
// new : int *numbers = new int[10];
// delete : delete[] numbers;  // 一定要加 []，不然只會刪第一格

// 程式碼範例:
#include <iostream>
#include <string>
using namespace std;
class player {
public:
    string name;
    // 【建構子】：出生時執行
    player(string n) {
        name = n;
        cout << ">>玩家 " << name << " 上線了" << endl;
    }
    // 【解構子】：死亡時執行
    ~player() {
        cout << ">>玩家 " << name << " 下線了" << endl;
    }

    void attack() {
        cout << name << " 揮了一劍！" << endl;
    }
};
int main() {
    cout << "--- 遊戲伺服器啟動 ---" << endl;

    // 使用 new 建立物件
    // 此時會發生：配置記憶體 -> 呼叫 player("Kirito")
    player *p1 = new player("Justin");

    // 透過指標操作物件
    // 因為 p1 是指標，所以要用箭頭 ->
    p1->attack();

    // 使用 delete 刪除物件
    // 此時會發生：呼叫 ~Player() -> 歸還記憶體
    delete p1;
    // 注意：如果你這裡忘了 delete p1，直到程式結束前，
    // "Justin" 的解構子都永遠不會被執行！(這就是 Memory Leak)

    cout << "--- 遊戲伺服器關閉 ---" << endl;
    return 0;
}

// 本章重點整理 :
// new 是全自動的：它幫你找記憶體，同時幫你按開關（建構子）。
// delete 也是全自動的：它幫你按關機（解構子），同時幫你還記憶體。
// 配對原則：
// 有 new 就要有 delete。
// 有 new [] (陣列) 就要有 delete []。

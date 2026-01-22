// 在 Chapter 4 我叫你「忘了 malloc」
// 那現在我要叫你 「忘了 new 和 delete」。
// 在專業的 C++ 專案裡，我們幾乎不直接寫 delete
// 因為人腦是不可靠的，我們把這個責任交給 「智慧指標 (Smart Pointers)」

// Chapter 9: 智慧指標 (Smart Pointers)

// 1. 為什麼要用它？ 
// 回想一下傳統指標 (Raw Pointer) 的痛點：
// a. 忘記 delete -> Memory Leak (記憶體洩漏)。
// b. 提早 delete -> Dangling Pointer (懸空指標，還沒用完就刪了)。
// c. 重複 delete -> Double Free (程式崩潰)。
// 智慧指標就是一個 「包著指標的 Class」。利用我們學過的 解構子 (Destructor) 機制
// 讓指標在「死亡」的時候，自動去按 delete。
// 我們主要學這兩大天王：unique_ptr 和 shared_ptr。

// 2. 獨佔王者：unique_ptr
// 這是在 90% 的情況下你的首選。
// 特性：「這塊記憶體是我的，誰都別想跟我搶。」
// 它保證同一時間只有一個指標能指向這塊物件。
// 當這個指標消失時，物件立刻被刪除。
// 不能複製 (Copy)，只能轉移 (Move)。

// 程式碼範例 (引入 <memory>) :
// 用 make_unique 來建立，這比用 new 更安全
#include <iostream>
#include <memory>
#include <string>
using namespace std;
class Pet {
public:
    string name;
    Pet(string n) : name(n) {
        cout<< name << " 出生了" << endl;
    }
    ~Pet() {
        cout << name << " 隨著指標一起消滅了" << endl;
    }
    void bark() {
        cout << name << ": 汪！" << endl;
    }
};
int main() {
    cout << "--- Scope 開始 ---" << endl;

    {
        // 語法：unique_ptr<型別> 變數名 = make_unique<型別>(參數);
        unique_ptr<Pet> p1 = make_unique<Pet>("小黑");
        // 使用起來跟普通指標一模一樣 (用 ->)
        p1->bark();

        // unique_ptr<Pet> p2 = p1; 
        //【錯誤！】: 不能複製！小黑只能有一個主人

        // 可以「轉移所有權 (Move)」
        unique_ptr<Pet> p2 = move(p1); 
        // 現在 p2 是主人，p1 變成了空指標 (nullptr)
        if (p1 == nullptr) cout << "p1 手上已經空了" << endl;
        p2->bark();
    }   // 這裡離開大括號 -> p2 死亡 -> 自動觸發 delete -> 小黑死亡

    cout << "--- Scope 結束 ---" << endl;
    return 0;
}
// 重點筆記：
// 不用寫 delete。只要變數離開 {}，記憶體自動釋放。
// 效能：跟傳統指標一模一樣快 (Zero Overhead)，沒有額外負擔。


// 3. 分享大師：std::shared_ptr
// 有些情況比較複雜：「這個物件同時被好幾個人用，最後一個人用完才能刪。」
// 特性：「記數器機制 (Reference Counting)」。
// 每多一個指標指向它，計數器 +1。
// 每少一個指標指向它，計數器 -1。
// 當計數器變成 0 時，自動刪除物件。

// 程式碼範例 :
// 用 make_shared 來建立
#include <iostream>
#include <memory>
using namespace std;
class Pet {
public:
    Pet() { 
        cout << "Pet 建構" << endl; 
    }
    ~Pet() { 
        cout << "Pet 解構" << endl; 
    }
};
int main() {
    // 建立一個 shared_ptr，計數器 = 1
    shared_ptr<Pet> ptr1 = make_shared<Pet>();
    cout << "目前使用者: " << ptr1.use_count() << endl; // 輸出 1
    // use_count() 是 shared_ptr 裡面的一個功能函式，意思是：「現在有多少人正在共用這塊記憶體？」

    {
        // 複製給別人 (unique_ptr 做不到這件事)
        shared_ptr<Pet> ptr2 = ptr1;
        cout << "目前使用者: " << ptr1.use_count() << endl; // 輸出 2 (因為 ptr1 和 ptr2 都在用)

    }   // 離開小區塊，ptr2 死亡，計數器 -1

    cout << "目前使用者: " << ptr1.use_count() << endl; // 輸出 1 (剩下 ptr1 在用)

    // main 結束，ptr1 死亡，計數器 = 0 -> 自動 delete Pet
    return 0;
}

// 4. 該怎麼選？ 
// 這其實很簡單，請遵守這個規則：
// 預設使用 unique_ptr
// 絕大多數時候，一個物件只需要一個擁有者。這最快、最安全。
// 真的需要共享才用 shared_ptr。
// 例如：你寫了一個遊戲，一張「地圖貼圖」同時被 100 個怪物共用
// 這時候就適合用 shared_ptr，確保所有怪物都死光了，貼圖才能釋放。

// 總結:
// Header: #include <memory>
// unique_ptr: 獨佔所有權，不能複製，離開 Scope 自動刪除。這應該是你的預設選擇。
// shared_ptr: 共享所有權，靠計數器決定生死。
// make_unique / make_shared: 用這兩個函式來生出指標，不要直接用 new。

// 這章的重點只有一個：「不要重複造輪子」

// Chapter 5: 繼承 (Inheritance)

// 核心觀念：Is-a 關係 (He is a XXX)
// 想像你正在寫一個遊戲，裡面有「劍士」、「法師」、「弓箭手」。 他們都有名字、都會走路、都有血量。
// 笨方法：
// 寫三個 Class，把 name, hp, walk() 在裡面各寫三遍。
// 聰明方法 (繼承)：
// 先寫一個通用的 「角色 (Character)」 類別，把大家都一樣的功能寫在這裡。
// 然後讓劍士、法師去 「繼承」 角色。
// 這樣他們自動就擁有了名字和走路的功能，只需要專注寫自己獨有的技能
// 這就是 「繼承」：子類別 (Child) 自動擁有 父類別 (Parent) 的所有特徵。

// 語法筆記 :
// class 子類別 : public 父類別 {
//     這裡只要寫子類別獨有的東西就好
// };
// 父類別 (Base Class)：被繼承的那個（例如：角色）。
// 子類別 (Derived Class)：去繼承別人的那個（例如：劍士）。
// public：這裡的意思是「公開繼承」，代表父類別原本公開的功能，傳到子類別依然是公開的。

// 程式碼範例：RPG 角色系統
#include <iostream>
#include <string>
using namespace std;
//【父類別】：通用角色
// 把所有職業共用的屬性都放在這裡
class character {
public:
    string name;
    int hp;

    character(string n) {
        name = n;
        hp = 100;  // 預設血量
    }
    void eat() {
        hp += 10;
        cout << name << " 吃了一塊肉, HP 恢復到 " << hp << endl;
    }
};
//【子類別】：戰士 (繼承自 character)
// 翻譯：Warrior 是一種 (is a) character
class warrior : public character {
public:
    // 建構子 
    // 在建立戰士 (Warrior) 之前，先用參數 n 把裡面的角色 (Character) 初始化好。
    // 這就是所謂的「委派父類別建構子」
    warrior(string n) : character(n) {
        // 這裡可以做戰士特別的初始化 (如果沒有也不能省略，因為出生時要給名字)
    }

    // 戰士獨有的技能
    void slash() {
        cout << name << " 使用了「旋風斬」！" << endl;
    }
};
// 【子類別】：法師 (繼承自 Character)
class wizard : public character {
public:
    wizard(string n) : character(n) {
        // 這裡可以做巫師特別的初始化
    }

    // 巫師獨有的技能
    void fireball() {
        cout << name << " 丟出了「大火球」！" << endl;
    }
};
int main() {
    // 建立一個戰士
    warrior w("Arthur");
    // 呼叫繼承來的功能
    w.eat();
    // 呼叫自己的功能
    w.slash();
    // w.fireball(); // 錯誤！戰士不能用大火球

    // 建立一個巫師
    wizard s("jennie");
    s.eat();
    s.fireball();

    return 0;
}

// 重點筆記: 權限的新成員 protected
// private：私人的。只有自己能用，連兒子（子類別）都拿不到。
// public：公開的。誰都能用。
// 如果你想把遺產留給兒子，但不想公開給外人，就用 protected。
// 簡單範例:
#include <iostream>
using namespace std;
class father {
private:
    int private_money = 1000;  //【私房錢】：只有 Father 自己能動
protected:
    int family_money = 500;    //【傳家寶】：Father 和 Son 都能動
public:
    int public_money = 3000;   //【零錢】：誰都能拿
};
// 兒子繼承了爸爸
class son : public father {
public:
    void spend() {
        // 試圖拿爸爸的「私房錢」
        // private_money = 0; 
        // 【錯誤】：'private_money' is private。兒子也沒權限！

        // 試圖拿家裡的「傳家寶」
        family_money -= 200;
        //【成功】：protected 對兒子是開放的！

        // 試圖拿門口的「零錢」
        public_money -= 100;
        //【成功】：這當然沒問題。
    }
};
int main() {
    son s;
    // --- 測試 1: 兒子自己在內部花錢 ---
    s.spend(); // 這會成功，因為是在 Son 類別「裡面」執行的

    // --- 測試 2: 外人 (main) 想要直接拿錢 ---
    // s.family_money = 0;  
    //【失敗！】這就是 protected 的重點。
    // 對 main (外人) 來說，protected 就等於 private，是鎖住的！

    s.public_money = 0;     // 【成功】公開的，外人可以碰
    return 0;
}

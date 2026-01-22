// 這一章的 「多型 (Polymorphism)」 才是物件導向的靈魂。
// 沒有學會這個，你的 C++ 就只是「有 Class 的 C 語言」而已。
// 這絕對是 「最重要、最難、也是 C++ 最強大」 的一章。

// Chapter 6: 多型與虛擬函式 (Polymorphism & Virtual)

// 1. 發現問題：指鹿為馬
// 在上一章，我們知道 Warrior 是 Character 的兒子。 
// 根據 C 語言的指標規則，父類別的指標，可以指向子類別的物件（因為兒子也是一種父親）。
// 但這裡有個嚴重的 Bug，請看這段程式碼：
// Character *p = new Warrior("Arthur"); // 指標是 Character，實體是 Warrior
// p->attack();  
// 你的預期：它是戰士，應該要用戰士的「旋風斬」。
// 實際結果：它用了普通角色的「揮拳」。
// 因為 C++ 預設是靜態連結 (Static Binding)
// 編譯器只看 p 是一個 Character* 指標，它就決定好要呼叫 Character 的 attack 了
// 它不管你實際指到的物件到底是什麼

// 2. 解決方案：虛擬函式 (Virtual Function)
// 要解決這個問題，我們只需要在父類別的函式前面加上一個魔法關鍵字：virtual
// 它的意思是告訴編譯器：
//「這是一個虛擬的介面。當有人透過指標呼叫這個函式時
// 請先去檢查一下這個物件的『真實身分』是誰，然後呼叫它那個版本的函式。」
// 這叫做 動態連結 (Dynamic Binding)。

// 程式碼範例：真正的 RPG 戰鬥
#include <iostream>
#include <string>
using namespace std;
class Character {
public:
    string name;

    Character(string n) : name(n) {}

    // 【關鍵點】：加上 virtual
    // 這代表允許子類別「覆寫 (Override)」這個函式
    virtual void attack() {
        cout << name << " 揮了一拳 (普通攻擊)" << endl;
    }
};
class Warrior : public Character {
public:
    Warrior(string n) : Character(n) {}  // 繼承專屬的語法

    //【覆寫】：這裡是戰士的版本
    // override 關鍵字是 C++11 加的，雖非強制但強烈建議加上，
    // 它可以幫你檢查你有沒有打錯字 (例如把 attack 打成 atack)
    void attack() override {
        cout << name << " 使用了旋風斬！" << endl;
    }
};
class Wizard : public Character {
public:
    Wizard(string n) : Character(n) {}

    void attack() override {
        cout << name << " 唱出了大火球！" << endl;
    }
};
int main() {
    // 我們宣告一個 "Character 指標陣列"，裡面卻裝著不同的職業
    Character* party[3];

    party[0] = new Warrior("亞瑟");   // 戰士
    party[1] = new Wizard("梅林");    // 法師
    party[2] = new Character("路人"); // 普通人
    
    cout << "--- 戰鬥開始 ---" << endl;

    for (int i=0;i<3;i++) {
        // 因為 attack 是 virtual 的，
        // 系統會自動判斷這個指標「當下」指到的是誰
        party[i]->attack();
    }

    cout << "--- 戰鬥結束 ---" << endl;
    return 0;
}


// 純虛擬函式 (Pure Virtual Function)
// 最後一個觀念。 有時候，父類別根本不應該有實作。 
// 例如「形狀 (Shape)」這個類別，你問我「形狀的面積怎麼算？」我答不出來，因為只有圓形或方形才有面積公式。
// 這時候我們可以把它設為 「純虛擬函式」，語法是在後面寫 = 0。
// 舉例: 圓形
#include <iostream>
using namespace std;
class shape {
public:
    //【純虛擬函式】
    // 翻譯：我不會算，但我規定我的兒子們「一定」要會算
    virtual double getArea() = 0;
};
class circle : public shape {
private:
    double radius;
public:
    circle(double r) : radius(r) {}   // = circle(doubel r) {
                                      //       radius = r;
                                      //   }

    //【實作關鍵】：把 = 0 拿掉，寫上真正的邏輯
    double getArea() override {
        return 3.14*radius*radius;
    }
};
// 這種包含純虛擬函式的類別，我們稱為 「抽象類別 (Abstract Class)」。
// 它就像是一份「契約書」，它不能用來 new 物件（你不能 new Shape）
// 它存在的唯一目的就是規範兒子們一定要有 area() 功能。

// 本章總結:
// A. 問題：父類別指標指向子類別物件時，預設會呼叫到父類別的函式（連結錯誤）。
// B. 關鍵字 virtual：加在父類別函式前。告訴編譯器要看「物件本體」而不是「指標型別」。
// C. 關鍵字 override：加在子類別函式後。確保你真的有覆寫成功（防呆用）。
// D. 多型 (Polymorphism)：「一個介面，多種行為」。用同一個指標 attack()，戰士會砍、法師會燒。

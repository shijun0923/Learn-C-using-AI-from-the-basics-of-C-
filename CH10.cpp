// Chapter 10: 匿名函式 (Lambda Expressions)

// 如果你只是想要寫一個「超級簡單、只用一次」的小功能（比如比大小、過濾數字）
// 你卻被迫要大費周章去外面宣告一個完整的函式。Lambda 就是為了解決這個「囉唆」而生的。

// 1. 這是什麼？ (隨手寫的便利貼)
// Lambda 其實就是一個「沒有名字的函式」。 你可以直接把它寫在程式碼的中間，用完即丟。
// 語法公式： [捕捉清單] (參數) { 程式碼本體 };
// 看起來有點像外星符號？別怕，我們拆解一下：
// []：捕捉 (Capture)。決定這個 Lambda 能不能偷看外面的變數。
// ()：參數 (Parameters)。跟普通函式一樣，決定輸入是什麼。
// {}：內容 (Body)。要做什麼事

// 程式碼範例: 排序
// 假設我們有一個陣列 v = {1, 5, 2, 4, 3}。 
// C++ 的 std::sort 預設是由小排到大。
// 如果我們想「由大排到小」怎麼辦？
// (Lambda)直接把邏輯寫在 sort 裡面，一行搞定！
#include <iostream>
#include <vector>
#include <algorithm>  // sort 
using namespace std;
int main() {
    vector<int> v = {1, 5, 2, 4, 3};

    //【Lambda 登場】
    // [] : 不需要抓外面的變數，所以空著
    // (int a, int b) : 這是兩個要比較的數字
    // { return a > b; } : 比較的邏輯
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });

    // 對於 v 裡面的每一個元素，我們輪流把它拿出來，暫時叫做 i
    for (int i : v) cout << i << " "; // 輸出: 5 4 3 2 1
    
    return 0;
}

// 最強功能：捕捉變數 (Capture)
// 普通函式看不到 main 裡面的變數，但 Lambda 可以透過 [] 捕捉進來用
// 假設我們要計算「有多少個數字大於 threshold (門檻)」？
#include <iostream>
#include <vector>
#include <algorithm>  // count_if
using namespace std;
int main() {
    vector<int> v = {10,20,30,40,50};
    int threshold = 25;

    // 我們想算有幾個數字 > 25
    // 如果是普通函式，根本拿不到 threshold 這個變數
    int count = count_if(v.begin(), v.end(), [threshold](int n){
        // 在 [] 裡寫上變數名，就可以在 {} 裡面用了！
        return n > threshold;
    });

    cout << "大於 " << threshold << " 的數字有 " << count << " 個" << endl;
    return 0;
}
// 捕捉清單的寫法大全：
// [x]：只抓變數 x 進來 (複製一份，唯讀)。
// [&x]：只抓變數 x 進來 (用 Reference，可以修改 x)。
// [=]：懶人包。外面所有變數都抓進來 (全部複製，唯讀)。
// [&]：懶人包。外面所有變數都抓進來 (全部 Reference，可修改)。
// 新手建議：一開始先用 [=] 最簡單，反正通常我們只是要讀取數值而已。


// 把它存起來:
// 雖然 Lambda 通常是用完即丟，但你也可以把它存到變數裡，重複使用
// 這時候你需要用 auto (因為 Lambda 的真實型別名字很長很醜，只有編譯器知道)。
// auto sayHello = [](string n) {
//     cout << "Hello, " << name << "!" << endl;
// };
// sayHello("Gemini");


// 總結:
// Lambda：[]() { ... }。
// 用途：專門寫那些「很短、只用一次、不想特地命名」的小函式。
// 搭配：通常跟 STL 演算法 (如 sort, for_each, count_if) 一起出現。
// 捕捉：善用 [] 來使用外部變數，這是它最強的地方。

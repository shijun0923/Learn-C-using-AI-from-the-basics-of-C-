// 在 C 語言裡，如果函式出錯了，你通常會 return -1 或是回傳 NULL。 但這很爛：
// 如果 -1 剛好是正確答案怎麼辦？ (例如計算溫度)
// 如果使用者忘了檢查回傳值怎麼辦？ (程式繼續跑，然後在後面炸得更慘)
// C++ 引入了 「異常處理 (Exception Handling)」
// 用一種暴力且優雅的方式告訴你：「出事了！如果你不處理，我就讓程式直接當掉！」

// Chapter 11: 異常處理 (Exception Handling)

// 核心三劍客：Throw, Try, Catch
// 這就像是一場「接球遊戲」：
// Throw (丟出)：函式發現不對勁，把錯誤往外丟。
// Try (嘗試)：監控這段可能會出事的程式碼。
// Catch (接住)：當有人丟球出來時，這裡負責接住並處理（例如印出錯誤訊息）。

// 程式碼範例：除以零的悲劇
// 我們寫一個除法函式，如果分母是 0，我們就丟出一個異常。
#include <iostream>
#include <stdexcept>  // 裡面定義了標準錯誤類型
using namespace std;
// 定義一個可能會出錯的函式
double divide(double a, double b) {
    if (b == 0) {
        //【Throw】: 發現分母為 0，丟出一個炸彈 (runtime_error)
        // 程式會立刻從這裡跳出去，後面的 return 都不會執行！
        throw runtime_error("分母不能為 0"); 
    }
    return a / b;
}
int main() {
    double x = 10.0;
    double y = 0.0;

    //【Try】: 包住危險區域
    try {
        // 這行會觸發 throw
        double result = divide(x, y); 
        
        // 因為上面炸了，所以這行絕對不會被執行
        cout << "結果是: " << result << endl; 
    }

    //【Catch】: 處理善後
    // 語法：catch (錯誤型別& 變數名)
    // 建議一定要加 const ... & (避免複製)
    catch (const exception& e) {  // 可以背下來的寫法
        cout << "!!! 發生錯誤 !!!" << endl;
        cout << "錯誤原因: " << e.what() << endl; // what() 會印出剛剛 throw 裡面的字串
    }

    cout << "程式安全結束 (沒有當機)。" << endl;
    return 0;
}

// 進階觀念：Stack Unwinding (解構的骨牌效應)
// 這點最重要，也是 C++ 異常處理最強大的地方。 
// 當 throw 發生時，程式會從目前的函式一路往外跳 (Jump out)，直到找到 catch 為止。
// 在這個「往外跳」的過程中，沿路所有 Stack 上的物件，都會被自動呼叫解構子 (Destructor)！
// 這意味著：如果你使用了 unique_ptr 或 vector，就算函式中間發生錯誤跳出去了
// 記憶體依然會被完美釋放，不會有 Memory Leak。

// void badFunction() {
//     unique_ptr<int> p = make_unique<int>(100); // 拿了記憶體
//    
//     突然丟出異常！
//     throw runtime_error("Oops"); 
//     
//     這裡雖然沒跑到，但 p 的解構子會在 throw 發生時自動被呼叫
// }


// 總結:
// Throw: throw runtime_error("訊息"); 用來報警。
// Try-Catch: 用來接住錯誤。catch(const exception& e) 是標準姿勢。
// 安全性: 搭配 RAII (智慧指標)，就算發生異常，資源也能自動回收，這是 C++ 最讓人安心的設計。

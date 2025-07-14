# 雙人終端機貪食蛇 SnakeV2 (C++ / ncurses)

這是我用 C++ 與 `ncurses` 製作的 **雙人貪食蛇遊戲** V2 ，在V1的基礎上，增加了雙人操作的競技性。

---

## 遊戲特色
- 使用 `ncurses` 製作終端畫面（即時刷新與無閃爍輸入）
- 雙人模式（WSAD + 方向鍵 控制）
- 減肥藥設計（吃了會縮短蛇）
- 支援牆壁、自己、他人碰撞偵測
- 使用 class 管理 Snake 邏輯（V2 改進）

---

## 專案結構

| 檔案 | 功能 |
|------|------|
| `main.cpp` | 主程式入口，初始化遊戲與回圈邏輯 |
| `Snake.h` / `Snake.cpp` | Snake 類別與邏輯封裝（移動、碰撞、吃藥等） |

---

## 編譯與執行方式（Linux/macOS）

```bash
sudo apt install libncurses5-dev        # Ubuntu / Debian
brew install ncurses                    # macOS
g++ main.cpp Snake.cpp -lncurses -o snakeV2

# SnakeV2

利用 C++ 與 ncurses 製作的 **雙人貪食蛇遊戲**，在V1的基礎上，增加了雙人操作的競技性。

---

## 遊戲特色
- 使用 ncurses 製作終端畫面（即時刷新）
- 雙人模式（WSAD + 方向鍵 控制）
- 減肥藥設計（吃了會使蛇長縮短）
- 牆壁、自撞與互撞偵測
- 使用 class 管理 Snake 邏輯

---

## 編譯與執行方式

```bash
sudo apt install libncurses5-dev        # Ubuntu / Debian
brew install ncurses                    # macOS
```
### 執行指令
```bash
g++ main.cpp Snake.cpp -lncurses -o snakeV2
```
## 執行範例
[初始介面:兩條互不相撞的蛇](./初始畫面.png)
[判斷造成相撞者或蛇長以決定輸贏](./結果顯示.png)

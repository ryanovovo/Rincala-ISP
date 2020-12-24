# Rincala-ISP

## 可調用的member function & variable
### log
* `player` 移動該步的玩家
* `init_stack` 玩家移動該堆的編號
* `init_stack_size` 移動該堆的大小
* `direction` 移動的方向
* `player_obtain_points` 玩家移動該堆獲得的分數
* `final_stack` 移動後最後一顆棋所在的堆序列號
### game_status
* `game_log[]` 取得整體遊戲log
* `stack_nums` 遊戲盤面總堆數
* `color_nums` 遊戲棋子顏色種類（不同顏色代表不同分數）
* `chess_num` 遊戲盤面棋子總數
* `player_nums` 玩家總數
* `game_board[][]` 當前盤面
* `player_point[]` 玩家分數
### rincala
* `void clear()` 清理盤面
* `bool game_over()` 判斷遊戲是否結束
* `void init_game_status(總堆數, 棋子顏色總數, 棋子總數, 玩家總數)`
* `void init_game_status()` 手動輸入遊戲初始值
* `void manual_setup() ` 手動指定某一堆的某一個棋子
* `void auto_setup` 依照`init_game_status()`隨機分配盤面
* `void move(移動堆的編號, 移動方向, 移動玩家編號)`
* `int calculate_points(移動堆的編號, 移動方向)`取得移動該堆獲得的分數
* `void show_game_status()`輸出當前盤面及各玩家之分數
* `void undo() 回復上一動`

Shield: [![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]

This work is licensed under a
[Attribution-NonCommercial-NoDerivatives 4.0 International License][cc-by-nc-nd].

[![CC BY-NC-ND 4.0][cc-by-nc-nd-image]][cc-by-nc-nd]

[cc-by-nc-nd]: https://creativecommons.org/licenses/by-nc-nd/4.0/
[cc-by-nc-nd-image]: https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png
[cc-by-nc-nd-shield]: https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg

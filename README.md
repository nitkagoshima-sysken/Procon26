# Procon26 競技部門 モジュール仕様書 (ver1.2)

## 1.概要
モジュールは、問題の入出力、石の回転・反転等を行う関数・構造体・クラス群である
。各ソルバは、基本的に本モジュールを用いて作成する。

本モジュールの構成については以下に示す。

|        名称          |                   概要                    |
| :------------------ | :---------------------------------------- |
| procon26_module.hpp | 石・ボードの構造体やクラスの定義や各定数等の定義部 |
| procon26_modio.hpp  | 問題の入出力に関する関数等の定義部             |
| procon26_modlib.hpp | 石・ボードに対する処理に関するモジュールの定義部    |
| procon26_module.cpp | クラスの実装部                               |
| procon26_modio.cpp  | 入出力関数の実装部                           |
| procon26_modlib.cpp | 石・ボードに対する関数の実装部                  |

## 2.用語
各種用語を以下に定義する。

|  用語  |                                概要                                     |
| :---- | :---------------------------------------------------------------------- |
| block | 石や敷地を構成する最小単位であり、大きさは1[zuku]。                             |
| stone | 複数のblockを辺でつなげたもの。8*8[zuku]の正方形で与えられる。                  |
| board | 石を敷き詰める場所。問題で与えられる"敷地"と同義。32*32[zuku]の正方形で与えられる。 |

## 3.インターフェース
### 3.1 procon26_module
procon26_moduleの構成について以下に示す。

|     定数名      | 概要 |
| :------------- | :------ |
| STONE_SIZE     | stoneの一辺大きさ。                                                                 |
| BOARD_SIZE     | boardの一辺の大きさ。                                                               |
| NULL_POINT     | 石が置けないときに指定する座標。                                                       |
| struct Stoen   | stoneを表す構造体。 unsigned char型8個の配列で表す。                                  |
| struct Board   | boardを表す構造体。 unsigned char型128個の配列で表す。                                |
| struct Problem | 問題を表す構造体。boardとstoneの数、stoneを保持する。                                   |
| class Answer   | 各stoneを置いた座標、回転、反転の情報を保持する。stoneが置けなかった場合(NULL_POINT, NULL_POINT)を示す。<br> メンバ関数ToString()を持つ。|
| struct Answers | 解答を表す構造体。 Answerクラスのリストを保持する。                                       |

### 3.2 procon26_modio
procon26_modioの構成について以下に示す。

+ 定数 ` block_0 ` showStone/showBoard関数で出力する "0" 文字の設定
+ 定数 ` block_1 ` showStone/showBoard関数で出力する "1" 文字の設定


+ ` Stone *getStoneByString(std::string stone)`  
文字列からstoneに変換する関数
 + stone : stoneの情報を持つ文字列(64文字)
 + return : 引数で与えられた文字列をStone構造体に格納し返す


+ ` Board *getBoardByString(std::string board)`  
文字列からboardに変換する関数
 + board : boardの情報を持つ文字列(1024文字)
 + return : 引数で与えられた文字列をBoard構造体に格納し返す


+ ` void inputStone(Stone *stone, int n)`   
標準入力からstoneを読み込み引数で与えたStone構造体のポインタに格納する関数
 + stone : 読み込んだstoneを格納するstone構造体ポインタ
 + n : 読み込む石の個数


+ ` void inputBoard(Board *board)`  
標準入力からboardを読み込み引数で与えたBoard構造体のポインタに格納する関数
 + board : 読み込んだboardを格納するBoard構造体のポインタ


+ ` void showStone(const Stone *stone)`  
標準出力にstoneを出力する関数
 + stone : 出力するstoneの構造体ポインタ


+ ` void showBoard(const Board *board)`  
標準出力にboardを出力する関数
 + board : 出力するboardの構造体ポインタ


+ ` Problem *readProblem(string filePath)`  
引数filePathで与えられたファイルから問題を読み込み、Problem構造体に格納しそのポインタを返す関数
 + filePath : 問題ファイルのパス
 + 使用例 : <br>
    `
    Problem *prob = readProblem("quest.txt");
    `

### 3.3 procon26_modlib(編集中)
procon26_modlibの構成について以下に示す。

+ ` int countBit(unsigned char bit)`  
unsigned char型の1のビットを数える関数  

+ ` int countBitOfStone(const Stone *stone)`  
Stone構造体の1(ブロック)の数を数える関数  

+ ` int countBitOfBoard(const Board *board)`  
Board構造体の1(ブロック)の数を数える関数  

+ ` Stone *quarryStone(const Board *board, int x, int y, bool filler)`  
boardの任意の座標から石(8*8[zuku])をコピーする関数  

+ ` Stone *shiftUp(const Stone *stone, int times, int filler)`  
stoneを上にtimes回シフトし、fillerを詰める関数  

+ ` Stone *shiftDown(const Stone *stone, int times, int filler)`  
stoneを下にtimes回シフトし、fillerを詰める関数  

+ ` Stone *shiftRight(const Stone *stone, int times, int filler)`  
stoneを右にtimes回シフトし、fillerを詰める関数  

+ ` Stone *shiftLeft(const Stone *stone, int times, int filler)`  
stoneを左にtimes回シフトし、fillerを詰める関数  

+ ` Stone *rotate(const Stone *stone, int n)`  
stoneをn*90°回転する関数  

+ ` Stone *rotate90(const Stone *stone)`  
stoneを右に90°回転する関数  

+ ` Stone *rotate180(const Stone *stone)`  
stoneを右に180°回転する関数  

+ ` Stone *rotate270(const Stone *stone)`  
stoneを右に270°回転する関数  

+ ` Stone *flip(const Stone *stone)`  
stoneを反転する関数  

+ ` Stone *NOT(const Stone *stone)`  
stoneのNOTをとる関数(1と0の反転)

+ ` Stone *AND(const Stone *stone1, const Stone *stone2)`  
2つのstoneのANDをとる関数  

+ ` Stone *OR(const Stone *stone1, const Stone *stone2)`  
2つのstoneのORをとる関数  

+ ` Stone *XOR(const Stone *stone1, const Stone *stone2)`  
2つのstoneのXORをとる関数  

+ ` bool isEmptyStone(const Stone *stone)`  
stoneが空(0[zuku])かどうか調べる関数  

+ ` bool isEmptyBoard(const Board *board)`  
boardが空(0[zuku])かどうか調べる関数  

+ ` Stone *getTouchingStone(const Board *board, const Stone *stone, int x, int y, bool filler)`  
stoneが今まで置いたstoneに触れているか調べる関数(fillerは、はみ出た部分を触れていないとする場合はtrue)  

+ ` Board *placeStone(const Board *board, const Stone *stone, int x, int y)`  
boardにstoneを置く関数  

+ ` bool canPlace(const Board *board, const Board *board_diff, const Stone *stone, int x, int y, bool first)`  
boardにstoneが置けるか調べる関数(board_diffは今までに置いたstoneだけのboardを渡す)  

+ ` int checkPlacingStone(const Board *board, const Board *board_diff, const Stone *stone, int x, int y)`  
boardにstoneを置いたときに触れている数を返す関数(board_diffは今までに置いたstoneだけのboardを渡す)  

+ ` bool isEqualStone(const Stone *stone1, const Stone *stone2)`  
2つのstoneが等しいか調べる関数  

+ ` bool isEqualBoard(const Board *board1, const Board *board2)`  
2つのboardが等しいか調べる関数

+ ` Stone *cloneStone(const Stone *stone)`  
stoneのコピーを作る関数  

+ ` Board *cloneBoard(const Board *board)`  
boardのコピーを作る関数  

+ ` inline bool getCellOfStone(const Stone *stone, int x, int y)`  
stoneの指定した座標にブロックがあるか(1かどうか)調べる関数  

+ ` inline bool getCellOfBoard(const Board *board, int x, int y)`  
boardの指定した座標にブロックがあるか(1かどうか)調べる関数  

+ ` inline void setCellOfStone(Stone *stone, int x, int y, bool value)`  
stoneの指定した座標にブロックを置く(1を入れる)関数  

+ ` inline void setCellOfBoard(Board *board, int x, int y, bool value)`  
boardの指定した座標にブロックを置く(1を入れる)関数  

+ ` void getGroupsCountStone(Stone *stone, bool target, int *groups_count, int *count)`  
stoneの中のtarget(1のときtrue, 0のときfalse)のまとまりの数をint型のポインタgroups_countに代入する関数  

+ ` int getGroupsCountStoneInternal(Stone *stone, Stone *done, bool target, int x, int y)`  
"getGroupsCountStone"の内部で用いている再起関数(一般的には使用しない)  

+ ` void getGroupsCountBoard(Board *board, bool target, int *groups_count, int *count)`  
boardの中のtarget(1のときtrue, 0のときfalse)のまとまりの数をint型のポインタgroups_countに代入する関数  

+ ` int getGroupsCountBoardInternal(Board *board, Board *done, bool target, int x, int y)`  
"getGroupsCountBoard"の内部で用いている再起関数(一般的には使用しない)  

+ ` void getGroupsStone(Stone *stone, bool target, std::vector<Stone *> &stones, int *groups_count, int *count)`  
stoneの中のtarget(1のときtrue, 0のときfalse)のまとまりのリストを返す関数  

+ ` int getGroupsStoneInternal(Stone *stone, Stone *done, Stone *result, bool target, int x, int y)`  
"getGroupsStone"の内部で用いている再起関数(一般的には使用しない)  

+ ` void getGroupsBoard(Board *board, bool target, std::vector<Board *> &boards, int *groups_count, int *count)`  
boardの中のtarget(1のときtrue, 0のときfalse)のまとまりのリストを返す関数  

+ ` int getGroupsBoardInternal(Board *board, Board *done, Board *result, bool target, int x, int y)`  
"getGroupsBoard"の内部で用いている再起関数(一般的には使用しない)  

+ ` Stone *normalizeStone(const Stone *stone)`  
stoneを左上に詰める関数  

+ ` void getStatesOfStone(const Stone *source, std::vector<Stone *> &states)`  
stoneの回転・反転による状態のうちnormalizeすると同じになるものを除いて1~8の状態を返す関数  

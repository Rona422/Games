//1ヘッダー
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
//2定数
#define F_WIDTH (12)       //2_1フィールドの幅
#define F_HEIGHT (18)      //2_2フィールドの高さ
#define B_WIDTH_MAX (4)    //2_3ブロックの最大幅
#define B_HEIGHT_MAX (4)   //2_4ブロックの最大高さ
#define FPS3 (1)            //2_5一秒あたりの描画頻度を定義
#define INTERVAL3 (1000/FPS3)//2_6描画間隔を定義(ミリ秒)
//3列挙体
//3_1ブロックの種類
enum {
	B_NONE,//3_1_1ブロックなし
	B_HARD,//3_1_2消せないブロック
    B_SOFT,//3_1_3消せるブロック
    B_FALL,//3_1_4落下ブロック
	B_MAX  //3_1_5ブロックの種類数
};
//3_2落下ブロックの種類の種類
enum {
    B_S_I, //3_2_1I型
    B_S_L, //3_2_2L型
    B_S_T,
    B_S_O,
    B_S_Z,
    B_S_S,
    B_S_MAX//3_2_3落下ブロックの種類数
};
//4構造体
//4_1落下ブロックの形状の構造体を宣言する
typedef struct {
    int size;//4_1_1幅と高さ
    bool patterm[B_HEIGHT_MAX][B_WIDTH_MAX];//4_1_2形状
}BS;
//4_2落下ブロックの構造体を宣言する
typedef struct {
    int x, y;//4_2_1座標
    BS shape;//4_2_2形状
}B;
//5変数
//5_1落下ブロックの形状を宣言する
const BS bS[B_S_MAX] = {
    //5_1_1B_S_I I型
    {
        4,//5_1_2int size 幅と高さ
        //5_1_3bool pattern[B_HEIGHT_MAX][B_WIDTH_MAX] 形状
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
        }
    },
    //5_1_4B_S_L L型
    {
        3,//5_1_5int size 幅と高さ
        //5_1_6bool pattern[B_HEIGHT_MAX][B_WIDTH_MAX] 形状
        {
            {1,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,0,0,0},
        }
    },
    {
       3,
       {
           {1,0,0,0},
           {1,1,0,0},
           {1,0,0,0},
           {0,0,0,0},
       }
    },
    {
       2,
       {
           {1,1,0,0},
           {1,1,0,0},
           {0,0,0,0},
           {0,0,0,0},
       }
    },
    {
       3,
       {
           {0,1,0,0},
           {1,1,0,0},
           {1,0,0,0},
           {0,0,0,0},
       }
    },
    {
       3,
       {
           {1,0,0,0},
           {1,1,0,0},
           {0,1,0,0},
           {0,0,0,0},
       }
    },
};
//5_2フィールドを宣言する
int field[F_HEIGHT][F_WIDTH];
//5_3フィールドの初期状態を宣言する
int defaultfield[F_HEIGHT][F_WIDTH]{
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
};
//5_4落下ブロックを宣言
B block;
int con = 0;
//6関数
//6_1落下ブロックとフィールドの当たり判定を行う関数
bool BIF() {
    //6_1_1落下ブロックの行分反復
    for (int y = 0; y < block.shape.size; y++) {
        //6_1_2落下ブロックの列分反復
        for (int x = 0; x < block.shape.size; x++) {
            //6_1_3対象のマスにブロックがあるかどうかを判定
            if (block.shape.patterm[y][x]){
                //6_1_4ブロックのフィールド上の列を宣言する
                int globalX = block.x + x;
                //6_1_5ブロックのフィールド上の行を宣言する
                int globalY = block.y + y;
                //6_1_6ブロックとフィールドの当たり判定
                if ((globalX<0)||(globalX>=F_WIDTH)||//列が左外or右外かどうか
                    (globalY<0)||(globalY>=F_HEIGHT)||//行が上外or下外かどうか
                    //フィールド上にブロックがあるかどうか
                    (field[globalY][globalX]!=B_NONE)
                    ){
                    //6_1_7当たったという結果を返す
                    return true;
                }
            }
        }
    }
    //6_1_8当たらなかった結果を返す
    return false;
}
//6_2そろった行のブロックを削除する関数
void EraseL() {
    //6_2_1すべての行を反復
    for (int y = 0; y < F_HEIGHT; y++) {
        //6_2_2その行がそろったかどうかのフラグを宣言
        bool completed = true;
        //6_2_3すべての列を反復
        for (int x = 0; x < F_WIDTH; x++) {
            //6_2_4対象のマスにブロックがないかどうか判定
            if (field[y][x]==B_NONE){
                //6_2_5そろわなかった
                completed = false;
                //6_2_6その行のチェックを抜ける
                break;
            }
        }
        //6_2_7その行がそろったかどうか判定
        if (completed){
            con++;
            //6_2_8対象の列を反復
            for (int x = 0; x < F_WIDTH; x++) {
                //6_2_9対象のマスが消せるブロックなら
                if (field[y][x]==B_SOFT){
                    //6_2_10対象のマスのブロックを消す
                    field[y][x] = B_NONE;
                }
            }
            //6_2_11すべての列を反復
            for (int x = 0; x < F_WIDTH; x++) {
                //6_2_12消えた行から先頭の行まで反復
                for (int y2 = y; y2 >= 0; y2--){
                    //6_2_13消せないブロックが見つかったら反復終了
                    if (field[y2][x]==B_HARD){
                        break;
                    }
                    //6_2_14先頭の行か判定
                    if (y2==0){
                        //6_2_15ブロックを消す
                        field[y2][x] = B_NONE;
                    }
                    //6_2_16先頭の行でなければ
                    else {
                        //6_2_17上のマスが消せないブロックでないか判定
                        if (field[y2-1][x]!=B_HARD){
                            //6_2_18上のマスを下のマスにコピー
                            field[y2][x] = field[y2 - 1][x];
                        }
                    }
                }
            }
        }
    }
}
//6_3描画処理
void DS() {
    //6_3_1画面バッファーを宣言
    int screen[F_HEIGHT][F_WIDTH];
    //6_3_2フィールドを画面バッファーにコピー
    memcpy(screen,field,sizeof field);
    //6_3_3フィールドの行分反復
    for (int y = 0; y < B_HEIGHT_MAX; y++){
        //6_3_4フィールドの列分反復
        for (int x = 0; x < B_WIDTH_MAX; x++){
            //6_3_5ブロックがあるかどうかを判定
            if (block.shape.patterm[y][x]){
                //6_3_6画面バッファーに落下ブロックを書き込む
                screen[block.y + y][block.x + x] = B_FALL;
            }
        }
    }
    //6_3_7画面クリア
    system("cls");
    printf("スコア:%d\n", con*100);
    //6_3_8フィールドすべての行を反復する
    for (int y = 0; y < F_HEIGHT; y++){
        //6_3_9フィールドすべての列を反復する
        for (int x = 0; x < F_WIDTH; x++){
            //6_3_10ブロックの種類で分岐する
            switch (screen[y][x]) {
            case B_NONE://6_3_11ブロックなし
                printf("　");
                break;
            case B_HARD://6_3_12消せないブロック
                printf("□");
                break;
            case B_SOFT://6_3_13消せるブロック
                printf("□");
                break;
            case B_FALL://6_3_14落下ブロック
                printf("■");
                break;
            }
        }
        //6_3_15改行
        printf("\n");
    }
}
//6_4落下ブロックを回転させる関数
void RB() {
    //6_4_1回転後のブロックを宣言
    B rB = block;
    //6_4_2落下ブロックの行分反復
    for (int y = 0; y < block.shape.size; y++){
        //6_4_3落下ブロックの列分反復
        for (int x = 0; x < block.shape.size; x++) {
            //6_4_4回転後のブロックの形状を作成
            rB.shape.patterm[block.shape.size - 1 - x][y] =
            block.shape.patterm[y][x];
        }
    }
    //6_4_5回転後のブロックを適用
    block = rB;
}
//6_5落下ブロックの初期化関数
void InitB() {
    //6_5_1落下ブロックの形状をランダムに設定する
    block.shape = bS[rand()%B_S_MAX];
    //6_5_2落下ブロックの列を中心にする
    block.x = F_WIDTH / 2 - block.shape.size / 2;
    //6_5_3落下ブロックの行を先頭に
    block.y = 0;
    //6_5_4落下ブロックを回転させる回数を宣言する
    int rC = rand() % 4;
    //6_5_5落下ブロックを回転させる回数だけ反復する
    for (int i = 0; i < rC; i++){
        //6_5_6落下ブロックを回転させる
        RB();
    }
}
//6_6初期化する処理
void Init() {
    //6_6_1フィールドに初期状態をコピーする
    memcpy(field,defaultfield,sizeof field);
    //6_2_2ブロックを初期化する関数を呼び出す
    InitB();
	//6_6_3画面を描画する関数を呼び出す
	DS();
}
//6_7落下ブロックを落下させる関数
void FB() {
    //6_7_1ブロックの移動前の状態を宣言する
    B lastB = block;
    //6_7_2ブロックを落下させる
    block.y++;
    //6_7_3ブロックとフィールドが重なったかどうか判定
    if (BIF()){
        //6_7_4落下ブロックを移動前の状態に戻す
        block = lastB;
        //6_7_5落下ブロックのすべての行分反復
        for (int y = 0; y < B_HEIGHT_MAX; y++) {
            //6_7_6落下ブロックのすべての列分反復
            for (int x = 0; x < B_WIDTH_MAX; x++) {
                //6_7_7ブロックがあるマスかどうかを判定
                if (block.shape.patterm[y][x]){
                    //6_7_8フィールドに消せるブロックを書き込む
                    field[block.y+y][block.x+x] = B_SOFT;
                }
            }
        }
        //6_7_9そろったブロックを削除する関数を呼び出す
        EraseL();
        //6_7_10ブロックを初期化
        InitB();
        //6_7_11ブロックとフィールドが重なったかどうか判定
        if (BIF()){
            //6_4_12ゲームを初期化
            Init();
        }
    }
    //6_7_13画面描画
    DS();
}
//6_8メイン関数
int main() {
    //6_8_1乱数をシャッフル
    srand((unsigned int)time(NULL));
	//6_8_2ゲームの初期化
	Init();
    //6_8_3前回の更新時刻を保持する変数を宣言
    time_t lastClock = clock();
	//6_8_4メインループ
	while (1) {
        //6_8_5現在の時刻を宣言
        time_t newClock = clock();
        //6_8_6待機時間を経過したら
        if (newClock >= lastClock+INTERVAL3){
            //6_8_7前回の更新時刻を現在の時刻で更新
            lastClock = newClock;
            //6_8_8落下ブロックを落下させる関数を呼び出す
            FB();
        }
        //6_8_9キーボード入力を判定
        if (_kbhit()){
            //6_8_10ブロックの移動前の状態を宣言する
            B lastB = block;
            //6_8_11入力されたキーによって分岐する
            switch(_getch()){
            case'w'://6_8_12wキーが押されたら
                    break;
            case's'://6_8_13sキーが押されたら
                block.y++;//6_8_14ブロックを下に移動
                break;
            case'a'://6_8_15aキーが押されたら
                block.x--;//6_8_16ブロックを左に移動
                break;
            case'd'://6_8_17sキーが押されたら
                block.x++;//6_8_18ブロックを右に移動
                break;
            default://6_8_19それ以外のキーが押されたら
                RB();//6_8_20ブロックを回転させる関数を呼び出す
                break;
            }
            //6_8_21ブロックとフィールドが重なったかどうか判定
            if (BIF()){
                //6_8_22ブロックを移動前の状態に戻す
                block = lastB;

            }
            //6_8_23ブロックとフィールドが重ならなければ
            else {
                //6_8_24画面を描写
                DS();
            }
        }
	}
}
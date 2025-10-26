//1ヘッダー
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
#include<vector>  //1_6
//2定数
#define M_WIDTH (19)       //2_1迷路の幅
#define M_HEIGHT (19)      //2_2迷路の高さ
#define FPS (2)            //2_3一秒あたりの更新頻度
#define FPS2 (10)
#define INTERVAL (1000/FPS)//2_4更新ごとの待機時間(ミリ秒)
#define INTERVAL2 (1000/FPS2)//2_4更新ごとの待機時間(ミリ秒)
#define THAWORLD (7)       //★アイテムの停止時間(更新回数)
#define PUTI (26)           //★アイテムの加速時間
//3列挙体
//3_1キャラクターの種類を定義
enum {
    C_PLAYER,//3_1_1プレイヤー
    C_RANDOM,//3_1_2気まぐれモンスター
    C_CHASE, //3_1_3追いかけモンスター
    C_AMBUSH,//3_1_4先回りモンスター
    C_SIEGE, //3_1_5挟み撃ちモンスター
    C_WP,
    C_MAX    //3_1_6キャラクター数
};
//3_2方向の種類を定義
enum {
    D_U,//3_2_1上
    D_L,//3_2_2左
    D_D,//3_2_3下
    D_R,//3_2_4右
    D_MAX//3_2_5方向の数
};
//4構造体
//4_1ベクトルの構造体
typedef struct {
    int x, y;//4_1_1座標
}VEC2;
//4_2キャラクターの構造体
typedef struct {
    VEC2 position;      //4_2_1座標
    const VEC2 defaultP;//4_2_2初期座標
    VEC2 lastP;         //4_2_3前回の座標
}C;
//5変数
int a = 0,b=0,c=0,cun=0;
//5_1迷路を宣言
char maze[M_HEIGHT][M_WIDTH+1];
// [5-2]迷路の初期状態を宣言
const char defaultMaze[M_HEIGHT][M_WIDTH + 1] =
{
    "#########o#########",
    "#ooooooo#o#ooooooo#",
    "#o###o#o#o#o#o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o###o###o###o#",
    "#ooooooooooooooooo#",
    "#o###o###o###o###o#",
    "#oog#o#oooop#o#ooo#",
    "###o#o#o###o#o#o###",
    "oooooooo# #oooooooo",
    "###o#o#o###o#o#o###",
    "#ooo#o#ooooo#o#ooo#",
    "#o###o###o###o###o#",
    "#oooooooo oooooooo#",
    "#o###o###o###o###o#",
    "#o# #o#pooog#o# #o#",
    "#o###o#o#o#o#o###o#",
    "#ooooooo#o#ooooooo#",
    "#########o#########"
};
//5_3キャラクターの配列を宣言
C characters[C_MAX] = {
    //5_3_1C_PLAYER
    {
        //5_3_2VEC2 position 座標
        {},
        //5_3_3const VEC2 defaultP 初期座標
        {9,13},
        //5_3_4VEC2lastP 前回の座標
        {},
    },
    //5_2_5C_RANDPM 気まぐれモンスター
    {
        //5_3_6VEC2 position 座標
        {},
        //5_3_7const VEC2 defaultP 初期座標
        {1,1},
        //5_3_8VEC2lastP 前回の座標
        {},
    },
    //5_3_9C_CHASE 追いかけモンスター
    {
        //5_3_10VEC2 position 座標
        {},
        //5_3_11const VEC2 defaultP 初期座標
        {17,1},
        //5_3_12VEC2lastP 前回の座標
        {},
    },
    //5_3_13C_AMBUSH 先回りモンスター
    {
        //5_3_14VEC2 position 座標
        {},
        //5_3_15const VEC2 defaultP 初期座標
        {1,17},
        //5_3_16VEC2lastP 前回の座標
        {},
    },
    //5_3_17C_SIEGE 挟み撃ちモンスター
    {
        //5_3_18VEC2 position 座標
        {},
        //5_3_19const VEC2 defaultP 初期座標
        {17,17},
        //5_3_20VEC2lastP 前回の座標
        {},
    },
    //5_3_17C_SIEGE 挟み撃ちモンスター
{
    //5_3_18VEC2 position 座標
    {},
    //5_3_19const VEC2 defaultP 初期座標
    {2,2},
    //5_3_20VEC2lastP 前回の座標
    {},
},
};
//5_4方向のベクトルの配列を宣言
VEC2 directions[D_MAX] = {
    {0,-1},//5_4_1D_U上
    {-1,0},//5_4_2D_L左
    {0,1}, //5_4_3D_D下
    {1,0}  //5_4_4D_R右
};
//6関数
//6_1ベクトル加算する関数
VEC2 Vec2add(VEC2 _v0, VEC2 _v1) {
    //6_1_1加算したベクトルを返す
    return{
        _v0.x+_v1.x,
        _v0.y+_v1.y
    };
}
//6_2ベクトルを減算する関数
VEC2 Vec2S(VEC2 _v0, VEC2 _v1) {
    //6_2_1減算したベクトルを返す
    return{
        _v0.x - _v1.x,
        _v0.y - _v1.y
    };
}
//6_3ベクトル同士が等しいかどうか判定する関数
bool Vec2E(VEC2 _v0, VEC2 _v1) {
    //6_3_1ベクトル同士が等しいかどうかを返す
    return(_v0.x == _v1.x) && (_v0.y == _v1.y);
}
//6_4上下左右にループした座標を取得する関数
VEC2 GetLP(VEC2 _position) {
    //6_4_1上下ループした座標を返す
    return{
        (M_WIDTH+_position.x)% M_WIDTH,
        (M_HEIGHT+_position.y) % M_HEIGHT
    };
}
//6_5ランダムな移動先を取得する関数
VEC2 GetRP(C _character) {
    //6_5_1移動先の候補のリストを宣言
    std::vector<VEC2>positions;
    //6_5_2すべての方向を反復する
    for (int i = 0; i < D_MAX; i++) {
        //6_5_3各方面の座標を宣言
        VEC2 newP = Vec2add(_character.position,directions[i]);
        //6_5_4対象の座標を上下左右にループ
        newP = GetLP(newP);
        //6_5_5対象の座標に移動可能か判定
        //壁ではない&&前回の座標と同じではない
        if ((maze[newP.y][newP.x]!='#')&&(!Vec2E(newP,_character.lastP))) {
            //6_5_6対象の座標を移動先の候補にリストに追加
            positions.push_back(newP);
        }
    }
    //6_5_7移動先の候補の中からランダムで座標を返す
    return positions[rand()%positions.size()];
}
//6_5ランダムな移動先を取得する関数
VEC2 GetWP(C _character) {
    //6_5_1移動先の候補のリストを宣言
    std::vector<VEC2>positions;
    //6_10_1迷路のすべての行分反復
    for (int y = 0; y < M_HEIGHT; y++) {
        //6_10_2迷路のすべての列分反復
        for (int x = 0; x < M_WIDTH; x++) {
                //6_5_3各方面の座標を宣言
                VEC2 newP;
                newP.y = y; newP.x = x;
                //6_5_5対象の座標に移動可能か判定
                //壁ではない
                if (maze[newP.y][newP.x] != '#') {
                    //6_5_6対象の座標を移動先の候補にリストに追加
                    positions.push_back(newP);
                }
        }
    }
    //6_5_7移動先の候補の中からランダムで座標を返す
    return positions[rand() % positions.size()];
}
//6_6最短経路の最初の座標取得関数
VEC2 GetCP(C _character,VEC2 _targetP) {
    //6_6_1経路を添削すべき座標のリストを宣言
    std::vector<VEC2>toCP;
    //6_6_2探索するキャラクター自身の座標を探索の座標リストに追加
    toCP.push_back(_character.position);
    //6_6_3探索開始地点から書くマスへの距離を保持する配列を宣言
    int distances[M_HEIGHT][M_WIDTH];
    //6_8_4迷路のすべての行を反復
    for (int y = 0; y < M_HEIGHT; y++){
        //6_6_5迷路のすべての列を反復
        for (int x = 0; x < M_WIDTH; x++){
            //6_6_6対象のマスへの距離を未設定として初期化
            distances[y][x] = -1;
        }
    }
    //6_6_7探索するキャラクターの座標への距離は0に設定
    distances[_character.position.y][_character.position.x] = 0;
    //6_6_8探索開始地点から書くマスへの経路を保持する配列を宣言
    std::vector<VEC2> routes[M_HEIGHT][M_WIDTH];
    //6_6_9探索の座標リストが空になるまで反復
    while (!toCP.empty()) {
        //6_6_10すべての方向を反復
        for (int i = 0; i < D_MAX; i++){
            //6_6_11探索中の座標に隣接する各方向に座標を取得
            VEC2 newP = Vec2add(toCP.front(),directions[i]);
            //6_6_12対象の座標を上下左右にループさせた座標に変換
            newP = GetLP(newP);
            //6_6_13対象の座標への距離を宣言
            int newD = distances[toCP.front().y][toCP.front().x] + 1;
            //6_6_14対象の座標を探索すべきかどうか判定
            //未設定||最短距離
            if ((distances[newP.y][newP.x]<0)||(newD<distances[newP.y][newP.x])&&(maze[newP.y][newP.x]!='#')) {
                //6_6_15対象の座標への距離を更新
                distances[newP.y][newP.x] = newD;
                //6_6_16対象の座標を探索の座標リストへ追加
                toCP.push_back(newP);
                //6_6_17対象の座標への経路を前の座標の経路で初期化
                routes[newP.y][newP.x] = routes[toCP.front().y][toCP.front().x];
                //6_6_18対象の座標への経路に対象の座標を追加
                routes[newP.y][newP.x].push_back(newP);

            }
        }
        //6_6_19探索の座標リストから先頭の座標を削除
        toCP.erase(toCP.begin());
        //6_6_20の経路がある&&前回と違う座標か判定
        if ((!routes[_targetP.y][_targetP.x].empty())&&(!Vec2E(routes[_targetP.y][_targetP.x].front(),_character.lastP))) {
            //6_6_21目標地点への経路の一つ目の座標を返す
            return routes[_targetP.y][_targetP.x].front();
        }
        //6_6_22目標地点への経路がなければ
        else {
            //6_6_23ランダムな座標を返す
            return GetRP(_character);
        }
    }
}
//6_7迷路を描画する関数
void DM() {
    //6_7_1画面バッファーを宣言
    char screen[M_HEIGHT][M_WIDTH + 1];
    //6_7_2画面バッファーに迷路をコピー
    memcpy(screen,maze,sizeof maze);
    //6_7_3すべてのキャラクター分反復
    for (int i = 0; i < C_MAX; i++){
        //6_7_4キャラクターの番号を画面バッファーに書き込む
        screen[characters[i].position.y][characters[i].position.x] = i;
    }
    //6_7_5画面クリア
    system("cls");
    a++;
    //6_7_6迷路のすべての行分反復
    for (int y = 0; y < M_HEIGHT; y++){
        //6_7_7迷路のすべての列分反復
        for (int x = 0; x < M_WIDTH; x++){
            //6_7_8マスの描画
            switch (screen[y][x]) {
            case ' '://6_7_9床
                printf("　");
                break;
            case '#'://6_7_10壁
                printf("■");
                break;
            case 'o'://6_7_11ドット
                printf("・");
                break;
            case 'g':
                printf("β");
                break;
            case 'p':
                printf("Ｂ");
                break;
            case C_PLAYER://6_7_12プレイヤー
                if (a %= 2)printf("□");
                else printf("凹");
                break;
            case C_RANDOM://6_7_13気まぐれモンスター
                printf("☆");
                break;
            case C_CHASE://6_7_14追いかけモンスター
                printf("凸");
                break;
            case C_AMBUSH://6_7_15先回りモンスター
                printf("◇");
                break;
            case C_SIEGE://6_7_16挟み撃ちモンスター
                printf("○");
                break;
            case C_WP://6_7_13気まぐれモンスター
                printf("▽");
                break;
            }
        }
        //6_7_17改行
        printf("\n");
    }
}
//6_8ゲームを初期化する関数
void Init() {
    int a = 0, b = 0, c = 0, cun = 0;
    memcpy(maze,defaultMaze,sizeof maze);
    //6_8_2すべてのキャラクター分反復
    for (int i = 0; i < C_MAX; i++){
        //6_8_3キャラクターの座標を初期化
        characters[i].position =characters[i].lastP = characters[i].defaultP;
    }
}
//6_9ゲームオーバーの関数
bool GO() {
    //6_9_1すべてのモンスターを反復
    for (int i = C_PLAYER+1; i < C_MAX; i++){
        //6_9_2対象のモンスターとプレイヤーの座標が同じかどうか判定
        if (Vec2E(characters[i].position,characters[C_PLAYER].position)) {
            //6_9_3画面クリア
            system("cls");
            //6_9_4迷路の高さの半分だけ反復
            for (int j = 0; j < M_HEIGHT/2; j++){
                //6_9_5改行
                printf("\n");
            }
            //6_9_6ゲームオーバーのメッセージを表示
            printf("　　　　　ＧＡＭＥ　ＯＶＥＲ");
            //6_9_7キーボード入力待ち
            _getch();
            //6_9_8ゲームオーバーになった結果を返す
            return true;
        }
    }
    //6_9_9ゲームオーバーにならなかったという結果を返す
    return false;
}
//6_10エンディング関数
bool Com() {
    //6_10_1迷路のすべての行分反復
    for (int y = 0; y < M_HEIGHT; y++){
        //6_10_2迷路のすべての列分反復
        for (int x = 0; x < M_WIDTH; x++){
            //6_10_3対象のマスがドットか判定
            if (maze[y][x]=='o'){
                //6_10_4クリアではないという結果を返す
                return false;
            }
        }
    }
    //6_10_5画面クリア
    system("cls");
    //6_10_6迷路の高さの半分だけ反復
    for (int i = 0; i < M_HEIGHT/2; i++){
        //6_10_7改行
        printf("\n");
    }
    //6_10_8エンディングのメッセージを表示
    printf("　　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ！");
    //6_10_9キーボード入力待ち
    _getch();
    //6_10_10クリアした結果を返す
    return true;

}
//6_11メイン関数
int main() {
    //6_11_1乱数を現在の時刻でシャッフル
    srand((unsigned int)time(NULL));
start://6_11_2ゲーム開始ラベル
    ;//6_11_3空分
    //6_11_4ゲームを初期化する関数
    Init();
    //6_11_5迷路を描画する関数
    DM();
    //6_11_6前回の更新時刻を宣言
    time_t lastC = clock();
	//6_11_7無限ループ
    while (1) {
        //6_11_8現在の時刻を宣言
        time_t newC = clock();
        if (c > 0) {
            if (newC > lastC + INTERVAL2) {
                c--;
                //6_11_10前回の更新時刻を現在の時刻で更新
                lastC = newC;
                cun++;
                if (b > 0)b--;
                if (b == 0) {
                    //6_11_11すべてのモンスター分反復
                    for (int i = C_PLAYER + 1; i < C_MAX; i++) {
                        //6_11_12移動先の座標を宣言
                        VEC2 newP = characters[i].position;
                        //6_11_13モンスターの種類で分岐
                        switch (i) {
                            //6_11_14気まぐれモンスター
                        case C_RANDOM: {
                            //6_11_15ランダムな移動先の座標を設定
                            newP = GetRP(characters[i]);
                            break;
                        }
                                     //6_11_16追いかけモンスター
                        case C_CHASE: {
                            //6_11_17プレイヤーを追いかける座標を設定
                            newP = GetCP(characters[i], characters[C_PLAYER].position);
                            break;
                        }
                                    //6_11_18先回りモンスター
                        case C_AMBUSH: {
                            //6_11_19プレイヤーの向きベクトルを宣言
                            VEC2 playerD = Vec2S(characters[C_PLAYER].position, characters[C_PLAYER].lastP);
                            //6_11_20目標地点を宣言
                            VEC2 targetP = characters[C_PLAYER].position;
                            //6_11_21三回反復
                            for (int j = 0; j < 3; j++) {
                                //6_11_22目標地点にプレイヤーの向きベクトルを加算
                                targetP = Vec2add(targetP, playerD);
                            }
                            //6_11_23目標地点を上下左右にループさせた座標に変換
                            targetP = GetLP(targetP);
                            //6_11_24目標地点を目指す座標を設定
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                                     //6_11_25挟み撃ちモンスター
                        case C_SIEGE: {
                            //6_11_26追いかけモンスターからプレイヤーへのベクトルを取得
                            VEC2 chaseTP = Vec2S(characters[C_PLAYER].position, characters[C_CHASE].position);
                            //6_11_27目的地宣言
                            VEC2 targetP = Vec2add(characters[C_PLAYER].position, chaseTP);
                            //6_11_28目標地点を上下左右にループさせた座標に変換
                            targetP = GetLP(targetP);
                            //6_11_29目標地点を目指す座標を設定
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                        case C_WP: {
                            //6_11_15ランダムな移動先の座標を設定
                            newP = GetRP(characters[i]);
                            //6_5_7移動先の候補の中からランダムで座標を返す
                            int cun =rand() % 100;
                            if (cun %= 80) {
                                newP = GetWP(characters[i]);
                            }
                            break;
                        }
                        }
                        //6_11_30前回の座標を現在の座標で更新
                        characters[i].lastP = characters[i].position;
                        //6_11_31移動先に移動させる
                        characters[i].position = newP;
                    }
                    //6_11_32ゲームオーバーになったか判定
                    if (GO()) {
                        //6_11_33ゲームの開始ラベルにジャンプ
                        goto start;
                    }
                }
                //6_11_34再描画
                DM();
            }
        }
        else {
            //6_11_9前回の更新から待機時間が経過したか判定
            if (newC > lastC + INTERVAL) {
                //6_11_10前回の更新時刻を現在の時刻で更新
                lastC = newC;
                cun++;
                if (b > 0)b--;
                if (b == 0) {
                    //6_11_11すべてのモンスター分反復
                    for (int i = C_PLAYER + 1; i < C_MAX; i++) {
                        //6_11_12移動先の座標を宣言
                        VEC2 newP = characters[i].position;
                        //6_11_13モンスターの種類で分岐
                        switch (i) {
                            //6_11_14気まぐれモンスター
                        case C_RANDOM: {
                            //6_11_15ランダムな移動先の座標を設定
                            newP = GetRP(characters[i]);
                            break;
                        }
                                     //6_11_16追いかけモンスター
                        case C_CHASE: {
                            //6_11_17プレイヤーを追いかける座標を設定
                            newP = GetCP(characters[i], characters[C_PLAYER].position);
                            break;
                        }
                                    //6_11_18先回りモンスター
                        case C_AMBUSH: {
                            //6_11_19プレイヤーの向きベクトルを宣言
                            VEC2 playerD = Vec2S(characters[C_PLAYER].position, characters[C_PLAYER].lastP);
                            //6_11_20目標地点を宣言
                            VEC2 targetP = characters[C_PLAYER].position;
                            //6_11_21三回反復
                            for (int j = 0; j < 3; j++) {
                                //6_11_22目標地点にプレイヤーの向きベクトルを加算
                                targetP = Vec2add(targetP, playerD);
                            }
                            //6_11_23目標地点を上下左右にループさせた座標に変換
                            targetP = GetLP(targetP);
                            //6_11_24目標地点を目指す座標を設定
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                                     //6_11_25挟み撃ちモンスター
                        case C_SIEGE: {
                            //6_11_26追いかけモンスターからプレイヤーへのベクトルを取得
                            VEC2 chaseTP = Vec2S(characters[C_PLAYER].position, characters[C_CHASE].position);
                            //6_11_27目的地宣言
                            VEC2 targetP = Vec2add(characters[C_PLAYER].position, chaseTP);
                            //6_11_28目標地点を上下左右にループさせた座標に変換
                            targetP = GetLP(targetP);
                            //6_11_29目標地点を目指す座標を設定
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                        case C_WP: {
                            //6_11_15ランダムな移動先の座標を設定
                            newP = GetRP(characters[i]);
                            //6_5_7移動先の候補の中からランダムで座標を返す
                            int cun =rand() % 100;
                            if (cun >80) {
                                newP = GetWP(characters[i]);
                            }
                            break;
                        }
                        }
                        //6_11_30前回の座標を現在の座標で更新
                        characters[i].lastP = characters[i].position;
                        //6_11_31移動先に移動させる
                        characters[i].position = newP;
                    }
                    //6_11_32ゲームオーバーになったか判定
                    if (GO()) {
                        //6_11_33ゲームの開始ラベルにジャンプ
                        goto start;
                    }
                }
                //6_11_34再描画
                DM();
            }
        }
        //6_11_35キーボード入力を判定
        if (_kbhit()) {
            //6_11_36プレイ屋の新しい座標
            VEC2 newP = characters[C_PLAYER].position;
            //6_11_37入力されたキーによって分岐
            switch(_getch()) {
                case'w'://6_11_38wがおされたら上へ移動
                    newP.y--;
                    break;
                case's'://6_11_39sがおされたら上へ移動
                    newP.y++;
                    break;
                case'a'://6_11_40aがおされたら上へ移動
                    newP.x--;
                    break;
                case'd'://6_11_41dがおされたら上へ移動
                    newP.x++;
                    break;
            }
            //6_11_42移動先の座標を上下左右にループさせる
            newP = GetLP(newP);
            //6_11_43移動先が壁でないかどうか判定
            if (maze[newP.y][newP.x] != '#') {
                //6_11_44プレイヤーの前回の座標をぜんざいの座標で更新
                characters[C_PLAYER].lastP = characters[C_PLAYER].position;
                //6_11_45プレイヤーの座標を更新
                characters[C_PLAYER].position = newP;
                if (b == 0) {
                    //6_11_46ゲームをーバーになったか判定
                    if (GO()) {
                        //6_11_47ゲームの開始ラベルにジャンプ
                        goto start;
                    }
                }
                //6_11_48プレイヤーの座標にドットがあるかどうかを判定する
                if (maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] == 'o') {
                    //6_11_49プレイヤーの座標のドットを消す
                    maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] = ' ';
                    //6_11_50クリアしたか判定
                    if (Com()){
                        //6_11_51ゲームの開始ラベルにジャンプ
                        goto start;
                    }
                }
                //6_11_48プレイヤーの座標にドットがあるかどうかを判定する
                if (maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] == 'g') {
                    //6_11_49プレイヤーの座標のドットを消す
                    maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] = ' ';
                    b = THAWORLD;
                }
                //6_11_48プレイヤーの座標にドットがあるかどうかを判定する
                if (maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] == 'p') {
                    //6_11_49プレイヤーの座標のドットを消す
                    maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] = ' ';
                    c = PUTI;
                }
            }
            //6_11_52再描画
            DM();
        }
	}
}
//1ヘッダー
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<time.h>  //1_3
#include<conio.h> //1_4
#include<vector>  //1_5
#include<string.h>  //1_5
//2定数
#define MAZE_WIDTH  (8)//2_1迷路の幅を定義する
#define MAZE_HEIGHT (8)//2_2迷路の高さを定義する
#define GOAL_X (MAZE_WIDTH-1)
#define GOAL_Y (MAZE_HEIGHT-1)
//3列挙体
//3_1方位の種類を定義
enum{
    DIRECTION_NORTH,//3_1_1北
    DIRECTION_WEST, //3_1_2西
    DIRECTION_SOUTH,//3_1_3南
    DIRECTION_EAST, //3_1_4東
    DIRECTION_MAX   //3_1_5方位の数
};
//3_2プレイヤーからの相対位置の種類を定義する
enum{
    LOCATION_FRONT_LEFT,    // [3-2-1]左前
    LOCATION_FRONT_RIGHT,   // [3-2-2]右前
    LOCATION_FRONT,         // [3-2-3]前
    LOCATION_LEFT,          // [3-2-4]左
    LOCATION_RIGHT,         // [3-2-5]右
    LOCATION_CENTER,        // [3-2-6]中心
    LOCATION_MAX            // [3-2-7]位置の数
};
//4構造体
//4_1ベクトルの構造体を宣言する
typedef struct {
    int x, y;//4_1_1座標
} VEC2;
//4_2迷路のマスの構造体を宣言する
typedef struct {
    bool walls[DIRECTION_MAX];//4_2_1各方位の壁の有無
} TILE;
//4 - 3]プレイヤーの構造体を宣言する
typedef struct {
    VEC2 position;  //4_3_1座標
    int direction;  //4_3_1向いている方位
} CHARACTER;
//5変数
//5_1各方位のベクトルを宣言する
VEC2 directions[] =
{
    { 0,-1},    // DIRECTION_NORTH  北
    {-1, 0},    // DIRECTION_WEST   西
    { 0, 1},    // DIRECTION_SOUTH  南
    { 1, 0}     // DIRECTION_EAST   東
};
//5_2基準となるアスキーアートを宣言する
const char* all =
"L       /\n"
"#L     /#\n"
"#|L _ /|#\n"
"#|#|#|#|#\n"
"#|#|_|#|#\n"
"#|/   L|#\n"
"#/     L#\n"
"/       L\n";

//5_3左前方前の壁のアスキーアートを宣言する
const char* frontLeftNorth =
"         \n"
"         \n"
"  _      \n"
" |#|     \n"
" |_|     \n"
"         \n"
"         \n"
"         \n";

//5_4右前方前の壁のアスキーアートを宣言する
const char* frontRightNorth =
"         \n"
"         \n"
"      _  \n"
"     |#| \n"
"     |_| \n"
"         \n"
"         \n"
"         \n";

//5_5前方前の壁のアスキーアートを宣言する
const char* frontNorth =
"         \n"
"         \n"
"    _    \n"
"   |#|   \n"
"   |_|   \n"
"         \n"
"         \n"
"         \n";

//5_6前方左の壁のアスキーアートを宣言する
const char* frontWest =
"         \n"
"         \n"
" |L      \n"
" |#|     \n"
" |#|     \n"
" |/      \n"
"         \n"
"         \n";

//5_7前方右の壁のアスキーアートを宣言する
const char* frontEast =
"         \n"
"         \n"
"      /| \n"
"     |#| \n"
"     |#| \n"
"      L| \n"
"         \n"
"         \n";

// [5-8]左方前の壁のアスキーアートを宣言する
const char* leftNorth =
"         \n"
"_        \n"
"#|       \n"
"#|       \n"
"#|       \n"
"_|       \n"
"         \n"
"         \n";

// [5-9]右方前の壁のアスキーアートを宣言する
const char* rightNorth =
"         \n"
"        _\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |_\n"
"         \n"
"         \n";

// 5_10前の壁のアスキーアートを宣言する
const char* north =
"         \n"
"  _____  \n"
" |#####| \n"
" |#####| \n"
" |#####| \n"
" |_____| \n"
"         \n"
"         \n";
//5_11左の壁のアスキーアートを宣言する
const char* west =
"L        \n"
"#L       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#/       \n"
"/        \n";
//5_12右の壁のアスキーアートを宣言する
const char* east =
"        /\n"
"       /#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       L#\n"
"        L\n";
//5_13アスキーアートのテーブルを宣言する
const char* aaTable[LOCATION_MAX][DIRECTION_MAX] ={
    // LOCATION_FRONT_LEFT  左前
    {
        frontLeftNorth,     // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },
    // LOCATION_FRONT_RIGHT 右前
    {
        frontRightNorth,    // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },
    // LOCATION_FRONT       前
    {
        frontNorth,         // DIRECTION_NORTH  北
        frontWest,          // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        frontEast           // DIRECTION_EAST   東
    },
    // LOCATION_LEFT        左
    {
        leftNorth,          // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },
    // LOCATION_RIGHT       右
    {
        rightNorth,         // DIRECTION_NORTH  北
        NULL,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        NULL                // DIRECTION_EAST   東
    },
    // LOCATION_CENTER      中心
    {
        north,              // DIRECTION_NORTH  北
        west,               // DIRECTION_WEST   西
        NULL,               // DIRECTION_SOUTH  南
        east                // DIRECTION_EAST   東
    }
};
// [5-14]プレイヤーからの相対座標のテーブルを宣言する
VEC2 locations[DIRECTION_MAX][LOCATION_MAX] =
{
    // DIRECTION_NORTH  北
    {
        {-1,-1},    // LOCATION_FRONT_LEFT  左前
        { 1,-1},    // LOCATION_FRONT_RIGHT 右前
        { 0,-1},    // LOCATION_FRONT       前
        {-1, 0},    // LOCATION_LEFT        左
        { 1, 0},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    },
    // DIRECTION_WEST   西
    {
        {-1, 1},    // LOCATION_FRONT_LEFT  左前
        {-1,-1},    // LOCATION_FRONT_RIGHT 右前
        {-1, 0},    // LOCATION_FRONT       前
        { 0, 1},    // LOCATION_LEFT        左
        { 0,-1},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    },
    // DIRECTION_SOUTH  南
    {
        { 1, 1},    // LOCATION_FRONT_LEFT  左前
        {-1, 1},    // LOCATION_FRONT_RIGHT 右前
        { 0, 1},    // LOCATION_FRONT       前
        { 1, 0},    // LOCATION_LEFT        左
        {-1, 0},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    },
    // DIRECTION_EAST   東
    {
        { 1,-1},    // LOCATION_FRONT_LEFT  左前
        { 1, 1},    // LOCATION_FRONT_RIGHT 右前
        { 1, 0},    // LOCATION_FRONT       前
        { 0,-1},    // LOCATION_LEFT        左
        { 0, 1},    // LOCATION_RIGHT       右
        { 0, 0}     // LOCATION_CENTER      中心
    }
};
//5_15迷路を宣言する
TILE maze[MAZE_HEIGHT][MAZE_WIDTH];
//5_16プレイヤー
CHARACTER player;
//6関数
//6_1ベクトルを加算する関数を宣言する
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]ベクトルを加算して返す
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}
//6_2対象の座標が迷路の範囲内かどうかを判定する関数を宣言する
bool IsInsideMaze(VEC2 _position){
    //6_2_1対象の座標が迷路の範囲内かどうかを返す
    return (_position.x >= 0)
        && (_position.x < MAZE_WIDTH)
        && (_position.y >= 0)
        && (_position.y < MAZE_HEIGHT);
}
//6_3壁を掘る関数
void DigWall(VEC2 _position, int _direction) {
    //3_3_1対象の座標が迷路ないか判定
    if (!IsInsideMaze(_position)){
        //3_3_2関数を抜ける
        return;
    }
    //6_3_3対象の壁を掘る
    maze[_position.y][_position.x].walls[_direction] = false;
    //6_3_4隣のマスの座標
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);
    //6_3_5隣のマスが範囲内か判定
    if (IsInsideMaze(_position)) {
        //6_3_6隣の部屋の掘る壁の方向
        int nextDirection=(_direction+2)%DIRECTION_MAX;
        //6_3_7隣の壁を掘る
        maze[nextPosition.y][nextPosition.x].walls[nextDirection] = false;
    }
}
//6_4対象の壁を掘ってもよいかどうかを判定する関数を宣言する
bool CanDigWall(VEC2 _position, int _direction){
    //6_4_1隣の座標
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);
    //6_4_2隣の座標が迷路外か判定
    if (!IsInsideMaze(nextPosition)) {
        return false;//6_4_3掘ってはいけない
    }
    //6_4_4方向分繰り返し
    for (int i = 0; i < DIRECTION_MAX; i++) {
        //6_4_5壁が掘られているか判定
        if (!maze[nextPosition.y][nextPosition.x].walls[i]){
            return false;//6_4_6掘ってはいけない
        }
    }
    return true;//6_4_7掘って良し！
}
//6-5迷路をランダムで生成する関数を宣言する
void GenerateMap() {
    // [6-5-1]迷路のすべての行を反復する
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        // [6-5-2]迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++) {
            // [6-5-3]マスのすべての方位を反復する
            for (int i = 0; i < DIRECTION_MAX; i++) {
                //6_5_4全方向に対して壁にする
                maze[y][x].walls[i] = true;
            }
        }
    }
    //6_5_5現座標
    VEC2 currentPosition = { 0,0 };
    //6_5_6壁を掘るべきマスのリストを宣言する
    std::vector<VEC2>toDigWallPositions;
    //6_5_7リストに現座標を追加
    toDigWallPositions.push_back(currentPosition);
    //6_5_8無限ループ
    while (1) {
        //6_5_9掘る壁の方向リスト
        std::vector<int>canDigDirections;
        //6_5_10すべての方向を繰り返し
        for (int i = 0; i < DIRECTION_MAX; i++){
            //6_5_11対象の方向の壁が掘れるか判定
            if (CanDigWall(currentPosition,i)){
                canDigDirections.push_back(i);
            }
        }
        //6_5_13掘れる壁があるかを判定
        if (canDigDirections.size()>0){
            //6_5_14掘る壁の方向を決定
            int diggDirection = canDigDirections[rand() % canDigDirections.size()];
            //6_5_15壁を掘る
            DigWall(currentPosition,diggDirection);
            //6_5_16掘った壁に移動
            currentPosition = VecAdd(currentPosition, directions[diggDirection]);
            //6_5_17壁を掘るべきマスのリストに追加
            toDigWallPositions.push_back(currentPosition);
        }
        //6_5_18惚れるものがない
        else {
            //6_5_19壁を掘るべきマスのリストから現在のマスを削除
            toDigWallPositions.erase(toDigWallPositions.begin());
            //6_5_20壁を掘るべきマスのリストが空かどうかを判定
            if (toDigWallPositions.size()<=0){
                //6_5_21ループ終了
                break;
            }
            //6_5_22壁を掘るべきマスのリストから先頭のマスを取得し移動する
            currentPosition = toDigWallPositions.front();
        }
    }
}
//6_6描画処理
void DrawMap() {
    //6_6_1迷路の行分
    for (int y = 0; y < MAZE_HEIGHT; y++){
        //6_6_2迷路の列分
        for (int x = 0; x < MAZE_WIDTH; x++) {
            //  [6-6-3]北の壁を描画する
            printf("＋%s＋", maze[y][x].walls[DIRECTION_NORTH] ? "―" : "　");
        }
        //6_6_4改行
        printf("\n");
        //6_6_5迷路のすべての列を反復
        for (int x = 0; x < MAZE_WIDTH; x++){
                //6_6_6床のアスキーアートを宣言する
                char floorAA[] = "　";
                //6_6_7プレイヤーの座標を描画中
                if ((x==player.position.x)&&(y == player.position.y)){
                    //6_6_8方位のアスキーアートを宣言する
                    const char* directionAA[] ={
                        "↑",    // DIRECTION_NORTH  北
                        "←",    // DIRECTION_WEST   西
                        "↓",    // DIRECTION_SOUTH  南
                        "→"     // DIRECTION_EAST   東
                    };
                    //6_6_9アスキーアートを表示（コピー
                    strcpy_s(floorAA,directionAA[player.direction]);
                }
                //6_6_10ゴールの描画
                else if ((x == GOAL_X) && (y == GOAL_Y)) {
                    //6_6_11
                    strcpy_s(floorAA, "Ｇ");
                }
                //6_6_12西の壁、中心の床、東の壁を描画する
                printf("%s%s%s",
                    maze[y][x].walls[DIRECTION_WEST] ? "｜" : "　",
                    floorAA,
                    maze[y][x].walls[DIRECTION_EAST] ? "｜" : "　");
        }
        //6_6_13改行
        printf("\n");
        //6_6_14迷路のすべての列を反復する
        for (int x = 0; x < MAZE_WIDTH; x++){
            //6_6_15南の壁を描画する
            printf("＋%s＋", maze[y][x].walls[DIRECTION_SOUTH] ? "―" : "　");
        }
        printf("\n"); //6_6_16改行
    }
}
//6_73D描画処理
void Draw3D() {
    //6_7_1画面バッファーを宣言する
    char screen[] =
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n";
    //6_7_2相対位置分繰り返し
    for (int i = 0; i < LOCATION_MAX; i++){
        //6_7_3絶対位置
        VEC2 position = VecAdd(player.position, locations[player.direction][i]);
        //6_7_4絶対位置が迷路の範囲外かどうか判定
        if (!IsInsideMaze(position)) {
            continue;//6_7_5次の相対位置へスキップ
        }
        //6_7_6方向分繰り返し
        for (int j = 0; j < DIRECTION_MAX; j++){
            //6_7_7プレイヤーからの相対方向
            int direction = (DIRECTION_MAX + j - player.direction) % DIRECTION_MAX;
            //6_7_8対象の壁がないか判定
            if (!maze[position.y][position.x].walls[j]){
                continue;//6_7_9次の方位へスキップする
            }
            //6_7_10合成するアスキーアートがないかどうかを判定する
            if (!aaTable[i][direction]){
                continue;//6_7_11次の相対位置へスキップする
            }
            //6_7_12画面バッファーのすべての文字を反復する
            for (int k = 0; k < sizeof(screen); k++){
                //6_7_13対象の文字がスペースでないかどうか判定する
                if (aaTable[i][direction][k] != ' '){
                    //6_7_14画面バッファーに合成するアスキーアートを書き込む
                    screen[k] = aaTable[i][direction][k];
                }
            }
        }
    }
    //6_7_15画面バッファーのすべての文字を反復する
    for (int i = 0; i < sizeof(screen); i++){
        //6_7_16画面バッファーの半角文字を全角文字に変換して描画する
        switch (screen[i]){
        case ' ':   printf("　");    break; //6_7_17「 」を「　」として描画する
        case '#':   printf("　");    break; //6_7_18「#」を「　」として描画する
        case '_':   printf("＿");    break; //6_7_19「_」を「＿」として描画する
        case '|':   printf("｜");    break; //6_7_20「|」を「｜」として描画する
        case '/':   printf("／");    break; //6_7_21「/」を「／」として描画する
        case 'L':   printf("＼");    break; //6_7_22「L」を「＼」として描画する
        default:
            //6_7_23上記以外の文字はそのまま描画する
            printf("%c", screen[i]);
            break;
        }
    }
}
//6_8ゲームの初期化
void Init() {
    //6_8_1迷路をランダムで生成
    GenerateMap();
    //6_8_2プレイヤーの座標
    player.position = { 0,0 };
    //6_8_3プレイヤーの方向（北
    player.direction = DIRECTION_NORTH;
}
//6_9メイン
int main() {
    //6_9_1乱数をシャッフルする
    srand((unsigned int)time(NULL));
    //6_9_2ゲーム初期化
    Init();
	//6_9_3メインループ
	while (1) {
        //6_9_4画面クリア
        system("cls");
        //6_9_5迷路の3D描画
        Draw3D();
        //6_9_6マップ描画
        DrawMap();
        //6_9_7
        switch (_getch()) {
        case'w'://6_9_8
            //6_9_9壁か判定
            if (!maze[player.position.y][player.position.x].walls[player.direction]) {
                //6_9_10前進先の座標を宣言する
                VEC2 nextPosition = VecAdd(player.position, directions[player.direction]);
                //6_9_11迷路ないか判定
                if (IsInsideMaze(nextPosition)){
                    //6_9_12一つ前に移動
                    player.position = nextPosition;
                    //6_9_13ゴールに到達したか判定
                    if ((player.position.x==GOAL_X)&&(player.position.y == GOAL_Y)){
                        system("cls");//6_9_14画面をクリアする
                        //6_9_15メッセージを表示する
                        printf(
                            "\n"
                            "\n"
                            "　＊　＊　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ　＊　＊\n"
                            "\n"
                            "\n"
                            "　あなたはついに　でんせつのまよけを　てにいれた！\n"
                            "\n"
                            "　しかし、くらくをともにした　「なかま」という\n"
                            "かけがえのない　たからをてにした　あなたにとって、\n"
                            "まよけのかがやきも　いろあせて　みえるのであった…\n"
                            "\n"
                            "　　　　　　　～　ＴＨＥ　ＥＮＤ　～\n");
                        _getch();// [6-9-16]キーボード入力を待つ
                        Init();// [6-9-17]ゲームを初期化する
                    }
                }
            }
            break;
        case's'://6_9_18
            player.direction+=2;//6_9_19後ろを向く
            break;
        case'a'://6_9_20
            player.direction++;//6_9_21左を向く
            break;
        case'd'://6_9_22
            player.direction--;//6_9_23右を向く
            break;
        }
        //6_9_24プレイヤーの向いている方位を範囲内に補正する
        player.direction = (DIRECTION_MAX + player.direction) % DIRECTION_MAX;
	}
}
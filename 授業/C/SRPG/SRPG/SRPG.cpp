//1ソースファイル
#include<stdio.h>   //1_1
#include <stdlib.h> //1_2
#include <time.h>   //1_3
#include <conio.h>  //1_4
#include <vector>   //1_5
#include <algorithm>//1_6
//2定数
#define TROOP_BASE (5)   //2_1基本兵数
#define TROOP_MAX (9)    //2_2最大兵数
#define TROOP_UNIT (1000)//2_3一兵数の単位
#define START_YEAR (1570)//2_4開始年
#define CHRONOLOGY_MAX (1024)//2_5年表の最大文字数を定義する
//3列挙体
//3_1大名の種類
enum {
    LORD_DATE,     //3_1_1伊達輝宗
    LORD_UESUGI,   //3_1_2]上杉謙信
    LORD_TAKEDA,   //3_1_3武田信玄
    LORD_HOJO,     //3_1_4北条氏政
    LORD_TOKUGAWA, //3_1_5徳川家康
    LORD_ODA,      //3_1_6織田信長
    LORD_ASHIKAGA, //3_1_7足利義昭
    LORD_MORI,     //3_1_8毛利元就
    LORD_CHOSOKABE,//3_1_9長宗我部元親
    LORD_SIMAZU,   //3_1_10島津義久
    LORD_MAX       //3_1_11種類の数
};
// [3-2]城の種類を定義する
enum
{
    CASTLE_YONEZAWA,       //3_2_1米沢城
    CASTLE_KASUGAYAMA,     //3_2_2春日山城
    CASTLE_TSUTSUJIGASAKI, //3_2_3躑躅ヶ崎館
    CASTLE_ODAWARA,        //3_2_4小田原城
    CASTLE_OKAZAKI,        //3_2_5岡崎城
    CASTLE_GIFU,           //3_2_6岐阜城
    CASTLE_NIJO,           //3_2_7二条城
    CASTLE_YOSHIDAKORIYAMA,//3_2_8吉田郡山城
    CASTLE_OKO,            //3_2_9岡豊城
    CASTLE_UCHI,           //3_2_10内城
    CASTLE_MAX             //3_2_11種類の数
};
//4構造体
//4_1大名の構造体
typedef struct {
	char familyName[16];//4_1_1姓
    char firstName[16]; //4_1_2名
}LORD;
//4_2城の構造体
typedef struct {
    const char* name;//4_2_1名前
    char owner;      //4_2_2城主
    char troopCount; //4_2_3兵数
    std::vector<int>connectedCastles;
}CASTLE;
//5変数
//5_1大名の配列を宣言する
LORD lords[LORD_MAX] = {
    {"伊達",    "輝宗"},//5_1_1LORD_DATE        伊達輝宗
    {"上杉",    "謙信"},//5_1_2LORD_UESUGI      上杉謙信
    {"武田",    "信玄"},//5_1_3LORD_TAKEDA      武田信玄
    {"北条",    "氏政"},//5_1_4LORD_HOJO        北条氏政
    {"徳川",    "家康"},//5_1_5LORD_TOKUGAWA    徳川家康
    {"織田",    "信長"},//5_1_6LORD_ODA         織田信長
    {"足利",    "義昭"},//5_1_7LORD_ASHIKAGA    足利義昭
    {"毛利",    "元就"},//5_1_8LORD_MORI        毛利元就
    {"長宗我部","元親"},//5_1_9LORD_CHOSOKABE   長宗我部元親
    {"島津",    "義久"} //5_1_10LORD_SIMAZU      島津義久
};
//5_2城の配列を宣言する
CASTLE castles[CASTLE_MAX] ={
    //5_2_1CASTLE_YONEZAWA   米沢城
    {
        "米沢城",   // const char* name         名前
        LORD_DATE,  // int owner                城主
        TROOP_BASE, // int troopCount           兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KASUGAYAMA,  // 春日山城
            CASTLE_ODAWARA      // 小田原城
        }
    },
    //5_2_2CASTLE_KASUGAYAMA 春日山城
    {
        "春日山城",     // const char* name     名前
        LORD_UESUGI,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YONEZAWA,        // 米沢城
            CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
            CASTLE_GIFU             // 岐阜城
        }
    },
    //5_2_3CASTLE_TSUTSUJIGASAKI 躑躅ヶ崎館
    {
        "躑躅ヶ崎館",   // const char* name     名前
        LORD_TAKEDA,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KASUGAYAMA,  // 春日山城
            CASTLE_ODAWARA,     // 小田原城
            CASTLE_OKAZAKI      // 岡崎城
        }
    },
    //5_2_4CASTLE_ODAWARA    小田原城
    {
        "小田原城", // const char* name         名前
        LORD_HOJO,  // int owner                城主
        TROOP_BASE, // int troopCount           兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YONEZAWA,        // 米沢城
            CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
            CASTLE_OKAZAKI          // 岡崎城
        }
    },
    //5_2_5CASTLE_OKAZAKI    岡崎城
    {
        "岡崎城",       // const char* name     名前
        LORD_TOKUGAWA,  // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_TSUTSUJIGASAKI,  // 躑躅ヶ崎館
            CASTLE_ODAWARA,         // 小田原城
            CASTLE_GIFU             // 岐阜城
        }
    },
    //5_2_6CASTLE_GIFU   岐阜城
    {
        "岐阜城",   // const char* name         名前
        LORD_ODA,   // int owner                城主
        TROOP_BASE, // int troopCount           兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_KASUGAYAMA,  // 春日山城
            CASTLE_OKAZAKI,     // 岡崎城
            CASTLE_NIJO         // 二条城
        }
    },
    //5_2_7CASTLE_NIJO   二条城
    {
        "二条城",       // const char* name     名前
        LORD_ASHIKAGA,  // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_GIFU,            // 岐阜城
            CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
            CASTLE_OKO              // 岡豊城
        }
    },
    //5_2_8CASTLE_YOSHIDAKORIYAMA    吉田郡山城
    {
        "吉田郡山城",   // const char* name     名前
        LORD_MORI,      // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_NIJO,    // 二条城
            CASTLE_OKO,     // 岡豊城
            CASTLE_UCHI     // 内城
        }
    },
    //5_2_9CASTLE_OKO    岡豊城
    {
        "岡豊城",       // const char* name     名前
        LORD_CHOSOKABE, // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_NIJO,            // 二条城
            CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
            CASTLE_UCHI             // 内城
        }
    },
    //5_2_10CASTLE_UCHI  内城
    {
        "内城",         // const char* name     名前
        LORD_SIMAZU,    // int owner            城主
        TROOP_BASE,     // int troopCount       兵数
        // std::vector<int> connectedCastles    接続された城のリスト
        {
            CASTLE_YOSHIDAKORIYAMA, // 吉田郡山城
            CASTLE_OKO              // 岡豊城
        }
    }
};
//5_3現在の年
int year;
//5_4プレイヤーの大名
int playerLord;
//5_5年表を宣言する
char chronology[CHRONOLOGY_MAX];
//6関数
//6_1城の数を数える処理
int GetCastleCount(int _lord) {
    //6_1_1城の数を宣言する
    int castleCount = 0;
    //6_1_2すべての城を反復する
    for (int i = 0; i < CASTLE_MAX; i++){
        //6_1_3対象の城の城主が、対象の大名かどうかを判定する
        if (castles[i].owner == _lord){
            //6_1_4城の数を加算する
            castleCount++;
        }
    }

    // [6-1-5]城の数を返す
    return castleCount;
}
//6_2基本情報描画
void DrowScreen() {
    //6_2_1画面クリア
    system("cls");
    //6_2_1.5地図のサンプルを描画する
    /*printf("%s",
        "1570ねん　～～～～～～～～～～～～～～～～　　　　　～\n"      // 01
        "　　　　　～～～～～～～～～～～～～～～～　0米沢5　～\n"      // 02
        "～～～～～～～～～～～～～～～～～～1春日5　伊達　～～\n"      // 03
        "～～～～～～～～～～～～～～～　～～上杉　　　　　～～\n"      // 04
        "～～～～～～～～～～～～～～～　～　　　　　　　　～～\n"      // 05
        "～～～～～～～～～～～～～～　　　　　2躑躅5　　　～～\n"      // 06
        "～～～～～～～～～～～～～　　　　　　武田　　　～～～\n"      // 07
        "～～～～～～　　　　　　　5岐阜5　　　　　　　　～～～\n"      // 08
        "～～～～　7吉田5　6二条5　織田　4岡崎5　3小田5　～～～\n"      // 09
        "～～～　　毛利　　足利　　　　　徳川　　北条～～～～～\n"      // 10
        "～～　～～～～～～～　　　～～～～～～～～～～～～～～\n"      // 11
        "～　　　～　8岡豊5～～　～～～～～～～～～～～～～～～\n"      // 12
        "～　　　～～長宗～～～～～～～～～～～～～～～～～～～\n"      // 13
        "～9内城5～～～～～～～～～～～～～～～～～～～～～～～\n"      // 14
        "～島津～～～～～～～～～～～～～～～～～～～～～～～～\n"      // 15
        "～～～～～～～～～～～～～～～～～～～～～～～～～～～\n");    // 16
        */
    //6_2_2地図の1行目を描画する
    printf("%dねん　～～～～～～～～～～～～～～～～　　　　　～\n", year);
    //6_2_3地図の2行目を描画する
    printf("　　　　　～～～～～～～～～～～～～～～～　%d%.4s%d　～\n",
        CASTLE_YONEZAWA,
        castles[CASTLE_YONEZAWA].name, castles[CASTLE_YONEZAWA].troopCount);
    //6_2_4地図の3行目を描画する
    printf("～～～～～～～～～～～～～～～～～～%d%.4s%d　%.4s　～～\n",
        CASTLE_KASUGAYAMA, castles[CASTLE_KASUGAYAMA].name, castles[CASTLE_KASUGAYAMA].troopCount,
        lords[castles[CASTLE_YONEZAWA].owner].familyName);
    //6_2_5地図の4行目を描画する
    printf("～～～～～～～～～～～～～～～　～～%.4s　　　　　～～\n",
        lords[castles[CASTLE_KASUGAYAMA].owner].familyName);
    //6_2_6地図の5行目を描画する
    printf("～～～～～～～～～～～～～～～　～　　　　　　　　～～\n");
    //6_2_7地図の6行目を描画する
    printf("～～～～～～～～～～～～～～　　　　　%d%.4s%d　　　～～\n",
        CASTLE_TSUTSUJIGASAKI, castles[CASTLE_TSUTSUJIGASAKI].name, castles[CASTLE_TSUTSUJIGASAKI].troopCount);
    //6_2_8地図の7行目を描画する
    printf("～～～～～～～～～～～～～　　　　　　%.4s　　　～～～\n",
        lords[castles[CASTLE_TSUTSUJIGASAKI].owner].familyName);
    //6_2_9地図の8行目を描画する
    printf("～～～～～～　　　　　　　%d%.4s%d　　　　　　　　～～～\n",
        CASTLE_GIFU, castles[CASTLE_GIFU].name, castles[CASTLE_GIFU].troopCount);
    //6_2_10地図の9行目を描画する
    printf("～～～～　%d%.4s%d　%d%.4s%d　%.4s　　　　　%d%.4s%d　～～～\n",
        CASTLE_YOSHIDAKORIYAMA, castles[CASTLE_YOSHIDAKORIYAMA].name,
        castles[CASTLE_YOSHIDAKORIYAMA].troopCount, CASTLE_NIJO, castles[CASTLE_NIJO].name,
        castles[CASTLE_NIJO].troopCount, lords[castles[CASTLE_GIFU].owner].familyName,
        CASTLE_ODAWARA, castles[CASTLE_ODAWARA].name, castles[CASTLE_ODAWARA].troopCount);
    //6_2_11地図の10行目を描画する
    printf("～～～　　%.4s　　%.4s　～　　　%d%.4s%d　%.4s～～～～～\n",
        lords[castles[CASTLE_YOSHIDAKORIYAMA].owner].familyName, lords[castles[CASTLE_NIJO].owner].familyName,
        CASTLE_OKAZAKI, castles[CASTLE_OKAZAKI].name, castles[CASTLE_OKAZAKI].troopCount,
        lords[castles[CASTLE_ODAWARA].owner].familyName);
    //6_2_12地図の11行目を描画する
    printf("～～　～～～～～～～　　　　～～%.4s～　～　～～～～～\n",
        lords[castles[CASTLE_OKAZAKI].owner].familyName);
    //6_2_13地図の12行目を描画する
    printf("～　　　～　%d%.4s%d　～　　　　～～～～～～～～～～～～\n",
        CASTLE_OKO, castles[CASTLE_OKO].name, castles[CASTLE_OKO].troopCount);
    //6_2_14地図の13行目を描画する**
    printf("～　　　～　%.4s　～～　　～～～～～～～～～～～～～～\n",
        lords[castles[CASTLE_OKO].owner].familyName);
    //6_2_15地図の14行目を描画する
    printf("～%d%.4s%d～～～～～～～～～～～～～～～～～～～～～～～\n",
        CASTLE_UCHI, castles[CASTLE_UCHI].name, castles[CASTLE_UCHI].troopCount);
    //6_2_16地図の15行目を描画する
    printf("～%.4s～～～～～～～～～～～～～～～～～～～～～～～～\n",
        lords[castles[CASTLE_UCHI].owner].familyName);
    //6_2_17地図の16行目を描画する
    printf("～～～～～～～～～～～～～～～～～～～～～～～～～～～\n");
    //6_2_181行空けておく
    printf("\n");
}
//6_3初期化
void Init() {
    //6_3_1年をリセット
    year = START_YEAR;
    //6_3_2すべての城を反復する
    for (int i = 0; i < CASTLE_MAX; i++){
        //6_3_3城主を初期化する
        castles[i].owner = i;
        //6_3_4兵数を初期化する
        castles[i].troopCount = TROOP_BASE;
    }
    //6_3_5年表をクリア
    sprintf_s(chronology, "");
    //6_3_6基本情報描画
    DrowScreen();
    //6_3_7大名の選択を促すメッセージを表示する
    printf("おやかたさま、われらがしろは　このちずの\n"
        "どこに　ありまするか？！（0～%d）\n",
        CASTLE_MAX - 1);    // 城番号の最大値
    //6_3_8改行
    printf("\n");
    //6_3_9選択された城を保持
    int selectedCastle;
    //6_3_10範囲内の城番号が入力されるまで反復する
    do {
        //6_3_11城番号を入力する
        selectedCastle = _getch() - '0';
    } while ((selectedCastle < 0) || (selectedCastle >= CASTLE_MAX));
    //6_3_12選択した城の城主をプレイヤーの大名とする
    playerLord = castles[selectedCastle].owner;
    //6_3_13決定した大名を通知するメッセージを表示する
    printf("%sさま、%sから　てんかとういつを\nめざしましょうぞ！\n",
        lords[playerLord].firstName,//選択された大名の名
        castles[playerLord].name);  //選択された城の名前
    //6_3_14入力待
    _getch();
}
//6_4攻城戦の関数
void Siege(
    int _offensiveLord,         // 攻め込んだ大名
    int _offensiveTroopCount,   // 攻め込んだ兵数
    int _castle) {               // 攻め込まれた城
    //6_4_1画面クリア
    system("cls");
    //6_4_2攻城戦の名前を表示する
    printf("～%sの　たたかい～\n", castles[_castle].name);
    // [6-4-3]改行
    printf("\n");
    //6_4_4攻め込まれた大名
    int defensiveLord = castles[_castle].owner;
    //6_4_5
    while (1) {
        //6_4_6合戦の経過を表示する
        printf("%sぐん（%4dにん）　Ｘ　%sぐん（%4dにん）\n",
            lords[_offensiveLord].familyName,// 攻め込んだ大名の姓
            _offensiveTroopCount * TROOP_UNIT,// 攻め込んだ兵数
            lords[defensiveLord].familyName,// 攻め込まれた大名の姓
            castles[_castle].troopCount * TROOP_UNIT);// 攻め込まれた城の兵数
        //6_4_7入力待
        _getch();
        //6_4_8攻守いずれかの兵数が0以下かどうか判定する
        if ((_offensiveTroopCount <= 0) || (castles[_castle].troopCount <= 0)){
            break;//6_4_9ループを抜ける
        }
        //6_4_10乱数が0だった場合
        if (rand()%3==0){
            //6_4_11守備側の兵を減らす
            castles[_castle].troopCount--;
        }
        else {
            //6_4_13攻撃側の兵を減らす
            _offensiveTroopCount--;
        }
    }
    //6_4_14改行
    printf("\n");
    //6_4_15守備側が全滅したか判定
    if (castles[_castle].troopCount<=0){
        //6_4_16落城したメッセージを表示する
        printf("%s　らくじょう！！\n", castles[_castle].name);
        //6_4_17改行
        printf("\n");
        //6_4_18
        castles[_castle].owner = _offensiveLord;
        //6_4_19
        castles[_castle].troopCount = _offensiveTroopCount;
        //6_4_20城主が攻め込んだ大名に変わったメッセージを表示する
        printf("%sは　%sけの　ものとなります\n",castles[_castle].name,lords[_offensiveLord].familyName);
        //6_4_21改行
        printf("\n");
        //6_4_22守備側の大名が城をすべて失ったか判定
        if (GetCastleCount(defensiveLord)<=0){

        }
    }
    //6_4_26守備側が全滅していない場合
    else {
        //6_4_27攻撃側が全滅したメッセージを表示する
        printf("%sぐん　かいめつ！！\n"
            "\n"
            "%sぐんが　%sを　まもりきりました！\n",
            lords[_offensiveLord].familyName,lords[defensiveLord].familyName,castles[_castle].name);
    }
}
//6_5メイン関数
int main() {
    //6_5_1乱数をシャッフルする
    srand((unsigned int)time(NULL));
start://6_5_2開始ラベル
    ;//6_5_3空分
    //6_5_4初期化
    Init();
	//6_5_5メインループ
	while (1) {
        //6_5_6ターンの順のテーブルを宣言する
        int turnOrder[CASTLE_MAX];
        //6_5_7ターンの順を初期化する
        for (int i = 0; i < CASTLE_MAX; i++){
            //6_5_8ターンの順を初期化する
            turnOrder[i] = i;
        }
        //6_5_9
        for (int i = 0; i < CASTLE_MAX; i++) {
            //6_5_10ターンをランダムに入れ替え
            std::swap(turnOrder[i],turnOrder[rand()%CASTLE_MAX]);
        }
        //6_5_11
        for (int i = 0; i < CASTLE_MAX; i++) {
            //6_5_12描画
            DrowScreen();
            //6_5_13
            for (int j = 0; j < CASTLE_MAX; j++) {
                //6_5_14現在のターンの城にカーソルを描画する
                printf("%s", (j == i) ? "＞" : "　");
                //6_5_15各ターンの城の名前を描画する
                printf("%.4s", castles[turnOrder[j]].name);
            }
            //6_5_16改行
            printf("\n");
            //6_5_17現ターンの城の番号
            int currentCastle = turnOrder[i];
            //6_5_18メッセージの表示
            printf("%sけの　%sの　ひょうじょうちゅう…\n",
                   lords[castles[currentCastle].owner].familyName, // 城主の姓
                   castles[currentCastle].name);                   // 城の名前
            //6_5_191行空ける
            printf("\n");
            //6_5_20現在の城主がプレイヤーかどうか判定
            if (castles[currentCastle].owner==playerLord){
                //進軍先の城の指定を促すメッセージを表示
                printf("%sさま　どこに　しんぐん　しますか\n？", lords[castles[currentCastle].owner].firstName);
                //6_5_21改行
                printf("\n");
                // [6-5-23]すべての接続された城を反復する
                for (int j = 0; j < (int)castles[currentCastle].connectedCastles.size(); j++){
                    // [6-5-24]接続された城の番号と名前を表示する
                    printf("%d %s\n",
                        castles[currentCastle].connectedCastles[j],
                        castles[castles[currentCastle].connectedCastles[j]].name);
                }
                //6_5_25改行
                printf("\n");
                //6_5_26進軍先の城を入力
                int targetCastle = _getch() - '0';
                //6_5_27現在の城と対象の城が接続しているかのフラグ
                bool isConnected = false;
                //6_5_28現在の城と接続しているすべての城を反復する
                for (int castle : castles[currentCastle].connectedCastles){
                    //6_5_29対象の城との接続が確認できたら
                    if (castle == targetCastle){
                        isConnected = true;//6_5_30接続の有無のフラグを立てる
                        break;//6_5_31反復を抜ける
                    }
                }
                //6_5_32接続している城が選ばれなかった
                if (!isConnected){
                    //6_5_33進軍を取りやめるメッセージを表示する
                    printf("しんぐんを　とりやめました\n");
                    _getch();//6_5_34キーボード入力を待つ
                    continue;//6_5_35次の国の評定にスキップする
                }
                //6_5_36現在の城の兵数の最大進軍数
                int troopMax = castles[currentCastle].troopCount;
                //6_5_37進軍先のプレイヤーの城か判定
                if (castles[targetCastle].owner==playerLord){
                    //6_5_38進軍先の城の空き兵数を宣言する
                    int targetCapacity = TROOP_MAX - castles[targetCastle].troopCount;
                    //6_5_39現在の城の兵数か、進軍先の空き兵数の少ないほうを最大進軍兵数とする
                    troopMax = std::min(troopMax, targetCapacity);
                }
                //6_5_40入力された城を通知して、移動する兵数の入力を促すメッセージを表示する
                printf("%sに　なんぜんにん　しんぐん　しますか？（0～%d）\n",
                    castles[targetCastle].name,	// 進軍先の城の名前
                    troopMax);					// 進軍兵数
                //6_5_41進軍兵数を宣言する
                int troopCount;
                //6_5_42範囲内の兵数が入力されるまで反復する
                do {
                    troopCount = _getch() - '0';//6_5_43進軍兵数を入力する
                } while ((troopCount < 0) || (troopCount > troopMax));
                //6_5_44現在の城の兵数を移動する分減らす
                castles[currentCastle].troopCount -= troopCount;
                //6_5_45進軍先のプレイヤーの城か判定
                if (castles[targetCastle].owner == playerLord) {
                    //6_5_46進軍先に移動した兵数を加算
                    castles[currentCastle].troopCount *= troopCount;
                }
                //6_5_47改行する
                printf("\n");
                //6_5_48入力された進軍兵数を通知する
                printf("%sに　%dにん%s",
                    castles[targetCastle].name, // 進軍先の城の名前
                    troopCount * TROOP_UNIT,	// 進軍兵数
                    // 進軍先の城の城主がプレイヤーかどうかを判定する
                    (castles[targetCastle].owner == playerLord)
                    ? "　いどう　しました"          // プレイヤーの城なら
                    : "で　しゅつじんじゃ～！！");  // 敵の城なら
                //6_5_49進軍先が敵の城か判定
                if (castles[targetCastle].owner != playerLord) {
                    //6_5_50入力待
                    _getch();
                    //6_5_51攻城戦の関数を呼び出す
                    Siege(
                        playerLord,     // int _offensiveLord       攻め込んだ大名
                        troopCount,     // int _offensiveTroopCount 攻め込んだ兵数
                        targetCastle);  // int _castle              攻め込まれた城
                }
            }
            //6_5_52現在の城主がプレイヤーでない場合
            else {
                //6_5_53接続された敵の城のリストを宣言する
                std::vector<int> connectedEnemyCastles;
                //6_5_54すべての接続された城を反復する
                for (int j = 0;j < (int)castles[currentCastle].connectedCastles.size();j++){
                    //6_5_55敵の城かどうかを判定する
                    if (castles[castles[currentCastle].connectedCastles[j]].owner
                        != castles[currentCastle].owner){
                        //6_5_56接続された敵の城のリストに加える
                        connectedEnemyCastles.push_back(
                            castles[currentCastle].connectedCastles[j]);
                    }
                }
                //6_5_57接続された敵の城があるかどうかを判定する
                if (connectedEnemyCastles.size() > 0) {
                    //6_5_58兵の少ない順に並び替える
                    sort(connectedEnemyCastles.begin(), connectedEnemyCastles.end(),
                        // 2つの城を比較するラムダ
                        [](int _castle0, int _castle1){
                            // リストの後ろの城のほうが、兵が多いかどうかを判定して返す
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );
                    //6_5_59最も兵の少ない城のみになるまで反復する
                    while (
                        // 隣接する敵の城が2城以上で&&最も兵数の少ない城よりも兵数の多い城
                        (connectedEnemyCastles.size() > 1)
                        && (castles[connectedEnemyCastles.front()].troopCount
                            < castles[connectedEnemyCastles.back()].troopCount)) {
                        //6_5_60リストの最後尾を削除
                        connectedEnemyCastles.pop_back();
                    }
                    //6_5_61攻め込む城を宣言する
                    int targetCastle =connectedEnemyCastles[rand() % connectedEnemyCastles.size()];
                    //6_5_62
                    if ((castles[currentCastle].troopCount>=TROOP_BASE)||
                        (castles[currentCastle].troopCount-1 >= castles[targetCastle].troopCount*2)) {
                        //6_5_63攻め込む兵数を宣言する
                        int troopCount = std::max(castles[currentCastle].troopCount - 1, 0);
                        //6_5_64現在の城の兵数から攻め込む兵数を減算する
                        castles[currentCastle].troopCount -= troopCount;
                        //6_5_65攻め込むメッセージを表示する
                        printf("%sの　%s%sが　%sに　せめこみました！\n",
                            castles[currentCastle].name,
                            lords[castles[currentCastle].owner].familyName,
                            lords[castles[currentCastle].owner].firstName,
                            castles[targetCastle].name);
                        _getch();//6_5_66キーボード入力を待つ
                        //6_5_67攻城戦の関数を呼び出す
                        Siege(
                            // int _offensiveLord       攻め込んだ大名
                            castles[currentCastle].owner,
                            // int _offensiveTroopCount 攻め込んだ兵数
                            troopCount,
                            // int _castle              攻め込まれた城
                            targetCastle);
                    }
                }
                //6_5_68接続された敵の城がなければ
                else {
                    //6_5_69敵と隣接する見方の城のリストを宣言
                    std::vector<int>frontCastles;
                    //6_5_70すべての接続された城を反復する
                    for (int neighbor : castles[currentCastle].connectedCastles) {
                        //6_5_71隣接する城に接続されたすべての城を反復する
                        for (int neighborNeighbor : castles[neighbor].connectedCastles) {
                            //6_5_72対象の城が敵の城に隣接しているかどうかを判定する
                            if (castles[neighborNeighbor].owner != castles[neighbor].owner) {
                                //6_5_73前線の城のリストに追加
                                frontCastles.push_back(neighbor);
                                break;//6_5_74
                            }
                        }
                    }
                    //6_5_75兵を送る城のリストを宣言する
                    std::vector<int> destCastles =
                        //前線の城がないかどうかを判定する
                        frontCastles.empty()
                        //なければ接続された城のリストを設定する
                        ? castles[currentCastle].connectedCastles
                        //あれば前線の城のリストを設定する
                        : frontCastles;
                    //6_5_76兵の少ない順に並び変える
                    sort(destCastles.begin(), destCastles.end(), [](int _castle0, int _castle1) {
                        return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );
                    //6_5_77もっとも兵の少ない城のみになるまで反復
                    //兵を送る先の城候補が複数&&もっとも兵数の少ない城よりも兵数の多い
                    while ((destCastles.size() > 1) && (
                        castles[destCastles.front()].troopCount < castles[destCastles.back()].troopCount)) {
                        //6_5_78リストから最後尾を削除
                        destCastles.pop_back();
                    }
                    //6_5_79兵を送る城を宣言
                    int targetCastle = destCastles[rand() % destCastles.size()];
                    //6_5_80送る兵数
                    int sendTroopCount = TROOP_MAX - castles[targetCastle].troopCount;
                    //6_5_81兵を送る先が前線か判定
                    if (!frontCastles.empty()) {
                        //6_5_82送り先の空き兵数と送り元の兵数のうち少ない兵数
                        sendTroopCount = std::min<int>(sendTroopCount, castles[currentCastle].troopCount);
                    }
                    //6_5_83前線でない場合
                    else {
                        //6_5_84送り元の空き兵数と送り元の余剰兵数のうち少ない兵数
                        sendTroopCount = std::min<int>(sendTroopCount, castles[currentCastle].troopCount - (TROOP_BASE - 1));
                    }
                    //6_5_85送る兵がいるか判定
                    if (sendTroopCount>0){
                        //6_5_86送り元の兵を減らす
                        castles[currentCastle].troopCount -= sendTroopCount;
                        //6_5_86送り元の兵を減らす
                        castles[targetCastle].troopCount -= sendTroopCount;
                        //6_5_88兵士が移動したメッセージを表示する
                        printf("%sから　%sに　%dにん　いどうしました\n",
                            castles[currentCastle].name,
                            castles[targetCastle].name,
                            sendTroopCount* TROOP_UNIT);
                    }
                }
            }
            //6_5_89入力待
            _getch();
            //6_5_90プレイヤーの城がないか判定
            if (GetCastleCount(playerLord) <= 0) {
                //6_5_91描画
                DrowScreen();
                //6_5_92年表を表示する
                printf("%s", chronology);
                //6_5_93改行
                printf("\n");
                //6_5_94ゲームオーバーのメッセージを表示
                printf("ＧＡＭＥ　ＯＶＥＲ\n");
                //6_5_95入力待
                _getch();
                //6_5_96開始ラベルへジャンプ
                goto start;
            }
            //6_5_97プレイヤーが天下統一した場合
            else if (GetCastleCount(playerLord) >= CASTLE_MAX) {
                //6_5_98描画
                DrowScreen();
                //6_5_99年表を表示
                printf("%s", chronology);
                //6_5_100エンディングのメッセージを表示
                printf("%dねん　%s%sが　せいいたいしょうぐんに　にんぜられる\n"
                    "%dねん　%s%sが　%sばくふを　ひらく\n"
                    "\n"
                    "ＴＨＥ　ＥＮＤ",
                    year + 3,                       // 征夷大将軍になった年
                    lords[playerLord].familyName,   // プレイヤーの大名の姓
                    lords[playerLord].firstName,    // プレイヤーの大名の名
                    year + 3,                       // 幕府を開いた年
                    lords[playerLord].familyName,   // プレイヤーの大名の姓
                    lords[playerLord].firstName,    // プレイヤーの大名の名
                    lords[playerLord].familyName);  // 幕府の名前
                //6_5_101入力待
                _getch();
                //6_5_102開始ラベルにジャンプ
                goto start;
            }
        }
        //6_5_103年を進める
        year++;
        //6_5_104すべての城を反復する
        for (int i = 0; i < CASTLE_MAX; i++){
            //6_5_105対象の城の兵数が基本兵数未満かどうかを判定する
            if (castles[i].troopCount < TROOP_BASE){
                //6_5_106兵数を増やす
                castles[i].troopCount++;
            }
            //6_5_107対象の城の兵数が基本兵数より多いかどうかを判定する
            else if (castles[i].troopCount > TROOP_BASE){
                //6_5_108兵数を減らす
                castles[i].troopCount--;
            }
        }
	}
}
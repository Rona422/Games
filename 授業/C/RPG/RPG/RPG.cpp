//1ヘッダーファイルをインクルード
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
//2定数を定義
//2_1呪文の消費MP
#define SPELL_COST (3)
//3列挙定数を定義
//3_1モンスター
enum {
	MON_PLAYER,//3_1_1プレイヤー
	MON_SLIME, //3_1_2スライム
	MON_garuda,
	MON_BOSS,  //3_1_3ボス
	MON_MAX    //3_1_4モンスターの種類数
};
//3_2キャラクターの種類
enum {
	CHA_PLAYER, //3_2_1プレイヤー
	CHA_MONSTER,//3_2_2モンスター
	CHA_MAX     //3_2_3キャラクターの種類数
};
//3_3コマンドの種類
enum {
	CMD_FIGHT,//3_3_1たたかう
	CMD_SPELL,//3_3_2じゅもん
	CMD_RUN,  //3_3_3にげる
	CMD_MAX,  //3_3_4
};
//4構造体を宣言
//4_1キャラクターの構造体
typedef struct {
	int hp;          //4_1_1HP
	int maxhp;       //4_1_2最大HP
	int mp;          //4_1_3MP
	int maxmp;       //4_1_4最大MP
	int attack;      //4_1_5攻撃力
	int def;
	char name[4*2+1];//4_1_6(全角4文字・終端文字)
	char aa[256];    //4_1_7アスキーアート
	int command;     //4_1_8コマンド
	int target;      //4_1_9攻撃対象
}CHARATCTER;
//5変数を宣言
//5_1モンスターのステータスの配列宣言
CHARATCTER monsters[MON_MAX] = {
	//5_1_1プレイヤーの初期値の設定
	{
		100,        //5_1_2HP
		100,        //5_1_3最大HP 
		15,        //5_1_4MP
		999,        //5_1_5最大MP
		75,         //5_1_6攻撃力
		15,
		"ゆうしゃ",//5_1_7名前
	},
	//5_1_8
	{
		3,	  	   //5_1_9HP
		3,		   //5_1_10最大HP
		0,		   //5_1_11MP
		0,		   //5_1_12最大MP
		10,         //5_1_13攻撃力
		0,
		"スライム",//5_1_14名前
		"／◎ノ◎＼\n"
		"～～～～～～"//5_1_15アスキーアート
	},
	//[★]
	{
		50,
		50,
		0,
		0,
		40,
		10,
		"ガルーダ",
		"（と・てノ）\n"
		"～～～～～～"	
	},
	//5_1_16
	{
		256,
		256,
		0,
		0,
		100,
		20,
		"まおう",
		"　　Ａx　xＡ\n"
		"(<＠>ノ皿＼<＠>)"
	}
};
//5_2キャラクターの配列宣言
CHARATCTER characters[CHA_MAX];
//5_3コマンドの名前に関する配列宣言
char commandnames[CMD_MAX][4 * 2 + 1] = {
	"たたかう",
	"じゅもん",
	"にげる"
};
//6関数を宣言
//6_1ゲームの初期化処理
void Init() {
	characters[CHA_PLAYER] = monsters[MON_PLAYER];
}
//6_2戦闘シーンの描画処理
void DrawBattle() {
	//6_2_1画面クリア
	system("cls");
	//6_2_2プレイヤーの名前表示
	printf("%s\n", characters[CHA_PLAYER].name);
	//6-2-3プレイヤーのステータスを表示
	printf("ＨＰ:%d／%dＭＰ:%d／%d\n",
			characters[CHA_PLAYER].hp,
			characters[CHA_PLAYER].maxhp,
			characters[CHA_PLAYER].mp,
			characters[CHA_PLAYER].maxmp);
	//6_2_4
	printf("\n");
	//6_2_5
	printf("%s",characters[CHA_MONSTER].aa);
	printf("(ＨＰ:%d／%d)\n",
		characters[CHA_MONSTER].hp,
		characters[CHA_MONSTER].maxhp);
	//6_2_7
	printf("\n");
}
//6_3コマンド選択処理
void SelectCMD() {
	//6_3_1プレイヤーのコマンドを初期化
	characters[CHA_PLAYER].command = CMD_FIGHT;
	//6_3_2コマンドが決定されるまでループ
	while (1) {
		//6_3_3戦闘描画
		DrawBattle();
		//6_3_4コマンド一覧
		for (int i = 0; i < CMD_MAX; i++){
			//6_3_5選択コマンドなら
			if (i==characters[CHA_PLAYER].command){
				//6_3_6カーソルの描画
				printf("＞");
			}
			//6_3_7選択コマンドで無いなら
			else{
				//6_3_8全角スペースの描画
				printf("　");
			}
			//6_3_9コマンドの名前の表示
			printf("%s\n", commandnames[i]);
		}
		//6_3_10キーボードの入力待ち
		switch(_getch()) {
			case'w'://6_3_11ｗキーが押された場合
				//6_3_12上のコマンドに切り替え
				characters[CHA_PLAYER].command--;
				break;
			case's'://6_3_13ｓキーが押された場合
				//6_3_14下のコマンドに切り替え
				characters[CHA_PLAYER].command++;
				break;
			default://6_3_15上記以外のキーが押された場合
				return;//6_3_16関数を抜ける
		}
		//6_3_17カーソルを上下にループ
		characters[CHA_PLAYER].command =
			(CMD_MAX+characters[CHA_PLAYER].command) % CMD_MAX;
	}
}
//6_4 戦闘処理
//引数　_monsterモンスター種類を指定
void Battle(int _monster) {
	//6_4_1
	characters[CHA_MONSTER] = monsters[_monster];
	//6-4-2プレイヤーの攻撃対象をモンスターに設定する
	characters[CHA_PLAYER].target = CHA_MONSTER;
	//6-4-3モンスターの攻撃対象をプレイヤーに設定する
	characters[CHA_MONSTER].target = CHA_PLAYER;
	//6_4_4
	DrawBattle();
	//6_4_5
	printf("%sが　あらわれた！\n",characters[CHA_MONSTER].name);
	//6_4_6
	_getch();//キーボード入力待ち
	int damage;
	//6_4_7戦闘終了までループ
	while (1) {
		//6_4_8コマンド選択処理関数を呼び出す
		SelectCMD();
		//6_4_9キャラクター分ループ
		for (int i = 0; i < CHA_MAX; i++){
			DrawBattle();//6_4_10戦闘描画の関数
			//6_4_11選択されたコマンドで分岐
			switch (characters[i].command) {
				case CMD_FIGHT://コマンドがたたかうの場合
					//6_4_13攻撃するメッセージを表示
					printf("%sの　こうげき", characters[i].name);
					characters[i].mp ++;
					//6_4_14
					_getch();//キーボード入力待ち
					//6_4_15敵に与えるダメージを計算する
					damage = 1 + rand() % ((characters[i].attack-characters[i].def) /2);
					//6_4_16敵にダメージを与える
					characters[characters[i].target].hp -= damage;
					//6_4_17敵のHPが負の値になった場合
					if (characters[characters[i].target].hp < 0){
						//6_4_18HPを0にする
						characters[characters[i].target].hp = 0;
					}
					//6_4_19戦闘描写処理関数
					DrawBattle();
					//6_4_20ダメージの表示
					printf("%sに　%d　ダメージ！\n",
						characters[characters[i].target].name,damage);
					_getch();
					break;
					//6_4_22コマンドがじゅもんの場合
				case CMD_SPELL:
					//6_4_23MPが足りるか判定
					if (characters[i].mp< SPELL_COST){
						//6_4_24MPがたりないメッセージを表示
						printf("ＭＰが　たりない！");
						//6_4_25キーボード入力待ち
						_getch();
						//6_4_26
						break;
					}
					//6_4_27MPを消費する
					characters[i].mp-= SPELL_COST;
					//6_4_28戦闘描画処理関数
					DrawBattle();
					//6_4_29呪文を唱えたメッセージを表示
					printf("%sは　を　となえた！\n", characters[i].name);
					//6_4_30キーボード入力待ち
					_getch();
					//6_4_31HPを回復(全回復)
					characters[i].hp = characters[i].maxhp;
					//6_4_32戦闘描画処理関数
					DrawBattle();
					//6_4_33回復メッセージを表示
					printf("%sのきずが　かいふくした\n",characters[i].name);
					break;
					//6_4_35コマンドがにげるの場合
				case CMD_RUN:
					//6_4_36にげたメッセージを表示
					printf("%sは　にげだした！",characters[i].name);
					//6_4_37キーボード入力待ち
					_getch();
					//6_4_38戦闘シーン関数終了
					return;
					break;
			}
			//6_4_39攻撃対象を倒したかを判定する
			if (characters[characters[i].target].hp <= 0){
				//6_4_40
				switch (characters[i].target){
					//6_4_41攻撃対象がプレイヤー
					case CHA_PLAYER:
						//6_4_42プレイヤー死亡表示
						printf("%sは　ちからつきた",characters[i].name);
						return;
						break;
					//6_4_43攻撃対象がモンスター
					case CHA_MONSTER:
						//6_4_44アスキーアートの表示を削除
						strcat_s(characters[characters[i].target].aa,"\n");
						//6_4_45
						DrawBattle();
						//6_4_46モンスターを倒したメッセージを表示
						printf("%sを　たおした！\n",
							characters[characters[i].target].name);
						return;
						break;
				}
				//6_4_47キーボード入力待ち
				_getch();
				//6_4_48戦闘シーン関数終了
				return;
			}
		}
	}
}
//6_6
int main() {
	//6_6_1
	srand((unsigned int)time(NULL));
	//6_6_2
	Init();
	//6_6_3
	Battle(MON_SLIME);
	Battle(MON_garuda);
	Battle(MON_BOSS);
}
//プロパティ130*65　フォントサイズ14
//プロパティ35*30　フォントサイズ36
//フォント　美咲ゴシック第２
//wasd移動キー qステータス画面開閉 eインベントリ開閉 その他:決定
//★ボス部屋の追加
//★レベルアップとステータスの割り振り
//★インベントリとアイテムの追加
//★そうび
//★エピローグ・エンディングの追加
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define F_WIDTH (32)
#define F_HEIGHT (32)
#define AREA_MAX (64)
#define AREA_SIZE_MIN (8)
#define AREA_SIZE_MIN_bos (16)
#define SCREEN_R (8)
#define INTERVAL (300)
#define FPS (4)
#define INTERVAL2 (1000/FPS)
#define R_SUKU (75)//★スクロールの出現率
#define R_BUKI (75)//★そうびのドロップ率
//セルの状態
enum {
	C_T_NONE,  //床
	C_T_WALL,  //壁
	C_T_STAIRS,//階段
	C_T_AMULET,//宝
	C_T_PLAYER,//プレイヤー
	C_T_ENEMY, //敵
	C_T_bos,   //ボス
	C_T_bos_R, //ボス右
	C_T_bos_L, //ボス左
	C_T_bos_T, //ボス上
	C_T_E_1,   //アイテム
	C_T_E_2,   //アイテム2
	C_T_E_3,   //アイテム3
	C_T_ROAD,//壁
	C_T_ROAD2,//壁2
	C_T_ROAD3,//壁3
	C_T_ROAD4,//壁4
	C_T_ROAD5,//壁5
	C_T_ROAD6,//門
	C_T_ROAD7,//門
};
//ルームの構造体
typedef struct {
	int x, y, w, h;
}ROOM;
//エリアの構造体
typedef struct {
	int x, y, w, h;
	ROOM room;
}AREA;
//キャラクターの構造体
typedef struct {
	int x, y;
	int hp, maxhp;
	int att;
	int ex;
}C;
//アイテムの構造体
typedef struct {
	int x, y;
	int kouka;
	bool e;
}E;
//プレイヤーの宣言
C player;
//敵の宣言
C enemy;
//ボスの宣言
C bos;
//アイテム
E suku;
E kenn;
E tate;
//エリアの宣言
AREA areas[AREA_MAX];
//階層の宣言とか
int flo=1,lv=1,exnow=0,point=1,hpp=0,attp = 0,soubiatt=0,soubihp=0;
//ボス改装
int boss = 0;
bool bossP=false;
//アイテム管理
int inv[3][10]{};
//アイテム番号
int Isuu[3] = { 0,0,0 };
//壁と床のアスキーアート
char cellAA[][2 + 1] = {
	"．",//C_T_NONE
	"㌶",//C_T_WALL
	"〓",//C_T_STAIRS
	"㍼",//C_T_AMULET
	"嚼",//C_T_PLAYER
	"ё",//C_T_ENEMY
	"㈱",//C_T_bos
	"㌔",//C_T_bos_R
	"㌃",//C_T_bos_L
	"箒",//C_T_bos_T
	"∬",//C_T_E_1
	"†",//C_T_E_2
	"圏",//C_T_E_3
	"У",//C_T_ROAD
	"λ",//C_T_ROAD2
	"森",//C_T_ROAD3
	"冊",//C_T_ROAD4
	"申",//C_T_ROAD5
	"皿",//C_T_ROAD6
	"　",//C_T_ROAD6
};
//エリア数
int areaC;
//フィールドの宣言
int field[F_HEIGHT][F_WIDTH];
int fieldend[(SCREEN_R+ SCREEN_R/2)*2][(SCREEN_R)*2];
//表示関数
void DS() {
	int buffer[F_HEIGHT][F_WIDTH];
	memcpy(buffer, field, sizeof field);
	//各オブジェクトの表示可否
	{
		if (!bossP){
			//ボス部屋で死んでいなければ表示
			if ((bos.hp > 0) && (flo >= boss)) {
				buffer[bos.y][bos.x] = C_T_bos;
				buffer[bos.y][bos.x + 1] = C_T_bos_R;
				buffer[bos.y][bos.x - 1] = C_T_bos_L;
				buffer[bos.y - 1][bos.x] = C_T_bos_T;
			}
			//死んでいなければ表示
			if (player.hp > 0) {
				buffer[player.y][player.x] = C_T_PLAYER;
			}
		}
		else {
			//ボス部屋で死んでいなければ表示
			if ((bos.hp > 0) && (flo >= boss)) {
				buffer[bos.y][bos.x] = C_T_PLAYER;
			}
			//死んでいなければ表示
			if (player.hp > 0) {
				buffer[player.y][player.x] = C_T_bos;
				buffer[player.y][player.x + 1] = C_T_bos_R;
				buffer[player.y][player.x - 1] = C_T_bos_L;
				buffer[player.y - 1][player.x] = C_T_bos_T;
			}
		}
		//死んでいなければ表示
		if (enemy.hp > 0) {
			buffer[enemy.y][enemy.x] = C_T_ENEMY;
		}
		//取得していないなら表示
		if (suku.e) {
			buffer[suku.y][suku.x] = C_T_E_1;
		}
		if (kenn.e) {
			buffer[kenn.y][kenn.x] = C_T_E_2;
		}
		if (tate.e) {
			buffer[tate.y][tate.x] = C_T_E_3;
		}
	}
	//画面クリア
	system("cls");
	//UI
		printf("%2dF Lv%2d HP:%2d/%2d EXP:%2d/%2d SP%2d\n", flo, lv, player.hp, player.maxhp, exnow, player.ex, point);
		//プレイヤーの周りだけ表示
		for (int y = player.y - SCREEN_R; y < player.y + SCREEN_R; y++) {
			for (int x = player.x - SCREEN_R; x < player.x + SCREEN_R; x++) {
				//エリア外
				if ((x < 0) || (x >= F_WIDTH) || (y < 0) || (y >= F_HEIGHT)) {
					printf("㌍");
				}
				else {
					printf("%s", cellAA[buffer[y][x]]);
				}
			}
			printf("\n");
		}
}
//表示関数 使わない
void DA() {
	int buffer[F_HEIGHT][F_WIDTH] = {};
	for (int i = 0; i < areaC; i++) {
		for (int y = areas[i].y; y < areas[i].y + areas[i].h; y++) {
			for (int x = areas[i].x; x < areas[i].x + areas[i].w; x++) {
				buffer[y][x] = i;
			}
		}
	}
	system("cls");
	for (int y = 0; y < F_HEIGHT; y++) {
		for (int x = 0; x < F_WIDTH; x++) {
			char str[] = "０";
			str[1] += buffer[y][x] %10;
			printf("%s", str);
		}
		printf("\n");
	}
}
//フィールド分割関数
void spritA(int _areaI) {
	int newareaI = areaC;
	//一つ前を保存
	int w = areas[_areaI].w;
	int h = areas[_areaI].h;
	//縦分割と横分割をランダムに
	if (rand() % 2) {
			//縦分割neareaの縦と横の座標
			areas[_areaI].w /= 2;
			areas[newareaI].x = areas[_areaI].x + areas[_areaI].w;
			areas[newareaI].y = areas[_areaI].y;
			areas[newareaI].w = w - areas[_areaI].w;
			areas[newareaI].h = areas[_areaI].h;
		}
	else {
			//横分割neareaの縦と横の座標
			areas[_areaI].h /= 2;
			areas[newareaI].x = areas[_areaI].x;
			areas[newareaI].y = areas[_areaI].y + areas[_areaI].h;
			areas[newareaI].w = areas[_areaI].w;
			areas[newareaI].h = h - areas[_areaI].h;
		}
	//ボス部屋
	if (flo>=boss){
		//分割がもうできない場合(ランダムで選ばれたほうが)
		if ((areas[_areaI].w < AREA_SIZE_MIN_bos) || (areas[_areaI].h < AREA_SIZE_MIN_bos) ||
			(areas[newareaI].w < AREA_SIZE_MIN_bos) || (areas[newareaI].h < AREA_SIZE_MIN_bos)) {
			//一つ前に戻す
			areas[_areaI].w = w;
			areas[_areaI].h = h;
			return;//終了
		}
	}
	else {
		//分割がもうできない場合(ランダムで選ばれたほうが)
		if ((areas[_areaI].w < AREA_SIZE_MIN) || (areas[_areaI].h < AREA_SIZE_MIN) ||
			(areas[newareaI].w < AREA_SIZE_MIN) || (areas[newareaI].h < AREA_SIZE_MIN)) {
			//一つ前に戻す
			areas[_areaI].w = w;
			areas[_areaI].h = h;
			return;//終了
		}
	}
	areaC++;//エリア番号
	spritA(_areaI);//余ったほうを再分割
	spritA(newareaI);//新しくできたほうを再分割
}
//ランダムポジション
void GRP(int *_px,int *_py){
	//ドットイートでやったやつ（候補はエリア単位
	int areaI = rand() % areaC;
	*_px = areas[areaI].room.x + rand() % areas[areaI].room.w;
	*_py = areas[areaI].room.y + rand() % areas[areaI].room.h;
}
//エリア生成
void generateF() {
	areaC = 0;//エリア番号
	areas[0].x = areas[0].y = 0;
	areas[0].w = F_WIDTH, areas[0].h = F_HEIGHT;
	areaC++;
	//分割関数
	spritA(0);
	//一旦全部壁で埋める
	for (int y = 0; y <  + F_HEIGHT; y++) {
		for (int x = 0; x < F_WIDTH; x++) {
			field[y][x] = C_T_WALL;
		}
	}
	//それぞれのルームの定義
	for (int i = 0; i < areaC; i++) {
		//通路分外枠残してルームの定義
		areas[i].room.x = areas[i].x + 2;
		areas[i].room.y = areas[i].y + 2;
		areas[i].room.w = areas[i].w - 4;
		areas[i].room.h = areas[i].h - 4;
		//ルームをC_T_NONEに
		for (int y = areas[i].room.y; y < areas[i].room.y + areas[i].room.h; y++) {
			for (int x = areas[i].room.x; x < areas[i].room.x + areas[i].room.w; x++) {
				field[y][x] = C_T_NONE;
			}
		}
		//ルームの右に通路
		for (int x = areas[i].x; x < areas[i].x + areas[i].w; x++) {
			field[areas[i].y + areas[i].h - 1][x] = C_T_NONE;
		}
		//ルームの下に通路
		for (int y = areas[i].y; y < areas[i].y + areas[i].h; y++) {
			field[y][areas[i].x + areas[i].w - 1] = C_T_NONE;
		}
		//ルームの上に穴
		for (int y2 = areas[i].y; y2 < areas[i].room.y; y2++) {
			field[y2][areas[i].x+areas[i].room.w/2] = C_T_NONE;
		}
		//ルームの下に穴
		for (int y2 = areas[i].room.y+ areas[i].room.h; y2 < areas[i].y+ areas[i].h; y2++) {
			field[y2][areas[i].x + areas[i].room.w / 2] = C_T_NONE;
		}
		//ルームの左に穴
		for (int x2 = areas[i].x; x2 < areas[i].room.x; x2++) {
			field[areas[i].y+areas[i].room.h/2][x2] = C_T_NONE;
		}
		//ルームの右に穴
		for (int x2 = areas[i].room.x+ areas[i].room.w; x2 < areas[i].x+ areas[i].w; x2++) {
			field[areas[i].y + areas[i].room.h / 2][x2] = C_T_NONE;
		}
	}
	//下の端をC_T_WALLで埋める
	for (int y = 0; y < F_HEIGHT; y++) {
		field[y][F_WIDTH - 1] = C_T_WALL;
	}
	//右の端をC_T_WALLで埋める
	for (int x = 0; x < F_WIDTH; x++) {
		field[F_WIDTH-1][x] = C_T_WALL;
	}
	//行き止まりをC_T_WALLで埋める
	while (1) {
		//埋まってるかのフラグ
		bool fill = false;
		for (int y = 0; y < F_HEIGHT; y++) {
			for (int x = 0; x < F_WIDTH; x++) {
				if (field[y][x] == C_T_WALL)
					continue;
				int v[][2] = {
					{0,-1},
					{-1,0},
					{0,1},
					{1,0},
				};
				int n = 0;
				for (int i = 0; i < 4; i++) {
					int x2 = x + v[i][0];
					int y2 = y + v[i][1];
					if ((x2 < 0) || (x2 >= F_WIDTH) || (y2 < 0) || (y2 >= F_HEIGHT)) {
						n++;
					}
					else if (field[y2][x2] == C_T_WALL) {
						n++;
					}
				}
				if (n >= 3) {
					field[y][x] = C_T_WALL;
					fill = true;
				}
			}
		}
		if (!fill)break;
	}
	//プレイヤーにランダムな座標を
	GRP(&player.x,&player.y);
	//階段にランダムな座標を
	if (flo < boss){
		int x, y;
		GRP(&x,&y);
		field[y][x] = C_T_STAIRS;
	}
	//階段の代わりにボス
	else {
		if (!bossP){
			//敵にランダムな座標を
			GRP(&bos.x, &bos.y);
			bos.hp = bos.maxhp = 20 + flo * 6;
			bos.att = 4 + flo * 4;
			bos.ex = 5 + flo * 5;
		}
		else{
			//敵にランダムな座標を
			GRP(&bos.x, &bos.y);
			bos.hp = bos.maxhp = 25 + flo * 7;
			bos.att = 5 + flo * 5;
			bos.ex = 5 + flo * 8;
		}
	}
	//敵にランダムな座標を
	if(!bossP){
		GRP(&enemy.x, &enemy.y);
		enemy.hp = enemy.maxhp = 2 + flo * 2;
		enemy.att = 2 + flo;
		enemy.ex = 2 + flo;
	}
	//出現をランダムに
	int syutugen = rand() % 100;
	if(syutugen<=R_SUKU){
		suku.e = true;
		//スクロールにランダムな座標を
		GRP(&suku.x, &suku.y);
		field[suku.y][suku.x] = C_T_E_1;
		suku.kouka = 1+rand()% 2;
	}
}
//エリアの表示　使わない
void DF() {
	system("cls");
	for (int y = 0; y < +F_HEIGHT; y++) {
		for (int x = 0; x < F_WIDTH; x++) {
			if ((x == player.x) && y == player.y)
				printf("㏄");
			else
			printf("%s", cellAA[field[y][x]]);
		}
		printf("\n");
	}
}
//どこの部屋にいるか
int getR(int _x, int _y) {
	//部屋分ループ
	for (int i = 0; i < areaC; i++){
		//部屋にいるか判定
		if ((_x>=areas[i].room.x)&&(_x<areas[i].room.x+areas[i].room.w)&&
			(_y>=areas[i].room.y)&&(_y<areas[i].room.y+areas[i].room.h)){
			return i;
		}
	}
	return -1;
}
//★ステイタス画面
void steitas() {
	int senntaku = 0;
	while (1) {
	system("cls");
	for (int i = 0; i < SCREEN_R/3; i++){
		printf("\n");
	}
		printf("　　ステータスポイント割り振り\n\n\n");
		printf("　　　残りポイント　%d\n\n",point);
		if (!(senntaku%2)){
			printf(" 　　  　↓\n");
		}
		else{
			printf(" 　  　 　　　　　 　　↓\n");
		}
		printf("   　 　ＨＰ　　　　こうげき\n\n");
		printf("   　 　HP:%d　　　 attack:%d\n",player.maxhp,player.att);
		//二択を切り替え
		switch (_getch()) {
		case'a':
			senntaku++;
			break;
		case'd':
			senntaku++;
			break;
			//終了
		case'q':
			DS();
			return;
			break;
		default:
			if (point!=0){
				if (!(senntaku % 2)) {
					hpp += 3 + rand() % 2;
					player.maxhp = 15 + hpp + lv + soubihp;
					//上昇分だけ回復
					player.hp += hpp;
				}
				else {
					attp += 2 + rand() % 1;
					player.att = 4 + attp + lv + soubiatt;
				}
				point--;
			}
			break;
		}
	}
}
//そうび中アイテム
int soubi = 11, soubi2 = 11;
//★インベントリ
void INVE() {
	int senntaku = 0;
	int senntate = 0;
	//senntateの初期化
	for (int j = 1; j < 3; j++) {
		for (int i = 0; i < 9; i++) {
			if (inv[j][i] != 0) {
				if (j == 2) {
					senntate = i + 10;
					break;
				}
				else if (j == 1) {
					senntate = i;
					break;
				}
			}
		}
	}
	while (1) {
		system("cls");
		//選択中を表示
		if (!(senntaku % 2)) {
			printf(" 　  　　 ↓\n");
		}
		else {
			printf(" 　　 　　　　　 　　　　 ↓\n");
		}
		//選択一覧
		printf("   　 スクロール　　　　そうび\n\n");
		//スクロール
		if (!(senntaku % 2)) {
			for (int i = 0; i < 9; i++){
				if (inv[0][i] == 0) {
					continue;
				}
				//選択コマンドなら
				if (i==senntate) {
					//6_3_6カーソルの描画
					printf("　　　＞");
				}
				//6_3_7選択コマンドで無いなら
				else {
					//6_3_8全角スペースの描画
					printf("　　　　");
				}
				if (inv[0][i]==1) {
					printf("　ワープのまきもの");
					printf("\n");
				}
				else if (inv[0][i]==2){
					printf("　回復のまきもの");
					printf("\n");
				}
			}
		}
		//武具
		else{
			for (int j = 1; j < 3; j++) {
				for (int i = 0; i < 9; i++) {
					if (inv[j][i] == 0) {
						continue;
					}
					//武器なら
					if (j == 1) {
						//選択コマンドなら
						if (i == senntate) {
							//6_3_6カーソルの描画
							printf("　＞");
						}
						//選択コマンドで無いなら
						else {
							//全角スペースの描画
							printf("　　");
						}
						if (inv[j][i] == 3) {
							printf("　木のこん棒　 attack%2d", inv[j][i]);
						}
						else if (inv[j][i] == 6) {
							printf("　鉄のこん棒　 attack%2d", inv[j][i]);
						}
						else if (inv[j][i] == 9) {
							printf("　真のこん棒　 attack%2d", inv[j][i]);
						}
						if (soubi == i) {
							printf("　E");
						}
						printf("\n");
					}
					//防具なら
					else if (j==2){
						//選択コマンドなら
						if (i+10 == senntate) {
							//6_3_6カーソルの描画
							printf("　＞");
						}
						//選択コマンドで無いなら
						else {
							//6_3_8全角スペースの描画
							printf("　　");
						}
						if (inv[j][i] == 4) {
							printf("　 なべぶた　　　　HP%2d", inv[j][i]);
						}
						else if (inv[j][i] == 8) {
							printf(" 排水溝のふた　　　HP%2d", inv[j][i]);
						}
						else if (inv[j][i] == 12) {
							printf("　 瓶のふた　　　　HP%2d", inv[j][i]);
						}
						if (soubi2 == i) {
							printf("　E");
						}
						printf("\n");
					}
				}
			}
			printf("\n   　 　ＨＰ　　　　こうげき\n\n");
			printf("   　 　HP:%d　　　 attack:%d\n", player.maxhp, player.att);
		}
		//前回の移動を保存
		int stmae = 0;
		//入力
		switch (_getch()) {
		case'a':
			senntaku++;
			break;
		case'd':
			senntaku++;
			break;
		case'w':
			senntate--;
			stmae = 1;
			break;
		case's':
			senntate++;
			stmae = 2;
			break;
		case'e':
			DS();
			return;//終了
			break;
		default://使用
			//スクロールの使用
			if (!(senntaku % 2)) {
				if (inv[0][senntate] == 1) {
					printf("\n\n　  プレイヤーはワープした");
					int px, py;
					GRP(&px, &py);
					player.x = px;
					player.y = py;
					_getch();
				}
				else if (inv[0][senntate] == 2) {
					printf("\n\n　　　　　　　%d →", player.hp);
					player.hp = player.maxhp;
					printf(" %d\n", player.hp);
					_getch();
				}
				inv[0][senntate] = 0;
			}
			//そうび
			else{
				if (9>senntate){
					soubiatt = inv[1][senntate];
					soubi = senntate;
					player.att = 4 + attp + lv + soubiatt;
				}
				else{
					soubihp = inv[2][senntate - 10];
					soubi2 = senntate - 10;
					player.maxhp = 15 + hpp + lv + soubihp;
				}
			}
			break;
		}
		//移動を自然に前回移動した時だけ
		if ((stmae == 2)||(stmae == 1)) {
			//スクロールかそうびか
			if (!(senntaku % 2)) {
				//選択をループと空いてるところをスキップ
				for (int i = 0; i < 9; i++) {
					//senntateをループ
					senntate = (senntate + 9) % 9;
					if (inv[0][senntate] == 0) {
						if (stmae == 1) {
							senntate--;
						}
						else if (stmae == 2) {
							senntate++;
						}
					}
					else {
						break;
					}
				}
			}
			else {
				for (int i = 0; i < 18; i++) {
					//senntateをループ
					senntate = (senntate + 18) % 18;
					//8まで
					if (senntate <= 8) {
						if (inv[1][senntate] == 0) {
							if (stmae == 1) {
								senntate--;
							}
							else if (stmae == 2) {
								senntate++;
							}
						}
						else {
							break;
						}
					}
					//9から
					else if (senntate >= 9) {
						if (inv[2][senntate-10] == 0) {
							if (stmae == 1) {
								senntate--;
							}
							else if (stmae == 2) {
								senntate++;
							}
						}
						else {
							break;
						}
					}
				}
			}
		}
	}
}
//★エンディング
void con() {
	//部屋作成
	{
		//壁で埋める
		for (int y = 0; y < SCREEN_R*3; y++) {
			for (int x = 0; x < SCREEN_R*2; x++) {
				fieldend[y][x] = C_T_WALL;
			}
		}
		//部屋を作る
		for (int y = 5; y < SCREEN_R*3 -5; y++) {
			for (int x = 2; x < SCREEN_R*2-2; x++) {
				fieldend[y][x] = C_T_NONE;
			}
		}
		//通路
		for (int y = 0; y < SCREEN_R*3; y++){
			fieldend[y][SCREEN_R] = C_T_NONE;
		}
		for (int y = 0; y < SCREEN_R * 3; y++) {
			fieldend[y][SCREEN_R-1] = C_T_NONE;
		}
		for (int y = 0; y < SCREEN_R * 3; y++) {
			fieldend[y][SCREEN_R + 1] = C_T_NONE;
		}
	}
	int con = 0;
	int i = 0;
	//前回の更新時刻を宣言
	time_t lastC = clock();
	while (1) {
		//現在の時刻を宣言
		time_t newC = clock();
		if (newC > lastC + INTERVAL2) {
			lastC = newC;
			system("cls");
			if (con >=40){
				return;
			}
			if (con <= 4) {
				player.y = SCREEN_R * 2 - 4, player.x = SCREEN_R;
				bos.y = SCREEN_R * 2 - 6, bos.x = SCREEN_R;
				fieldend[player.y][player.x] = C_T_PLAYER;
				fieldend[bos.y][bos.x] = C_T_bos;
				fieldend[bos.y][bos.x - 1] = C_T_bos_L;
				fieldend[bos.y][bos.x + 1] = C_T_bos_R;
				fieldend[bos.y - 1][bos.x] = C_T_bos_T;
			}
			else if (con <= 5) {
				fieldend[player.y][player.x] = C_T_NONE;
				fieldend[player.y - 1][player.x] = C_T_PLAYER;
			}
			else if (con <= 6) {
				fieldend[player.y - 1][player.x] = C_T_NONE;
				fieldend[player.y][player.x] = C_T_PLAYER;
				fieldend[bos.y][bos.x] = C_T_NONE;
				fieldend[bos.y][bos.x - 1] = C_T_NONE;
				fieldend[bos.y][bos.x + 1] = C_T_NONE;
				fieldend[bos.y - 1][bos.x] = C_T_NONE;
			}
			else if (con <= 7) {
				fieldend[bos.y][bos.x] = C_T_bos;
				fieldend[bos.y][bos.x - 1] = C_T_bos_L;
				fieldend[bos.y][bos.x + 1] = C_T_bos_R;
				fieldend[bos.y - 1][bos.x] = C_T_bos_T;
			}
			else if (con <= 8) {
				fieldend[bos.y][bos.x] = C_T_NONE;
				fieldend[bos.y][bos.x - 1] = C_T_NONE;
				fieldend[bos.y][bos.x + 1] = C_T_NONE;
				fieldend[bos.y - 1][bos.x] = C_T_NONE;
			}
			else if (con <= 10) {
				fieldend[bos.y][bos.x - 2] = C_T_bos_L;
				fieldend[bos.y - 1][bos.x + 2] = C_T_bos_R;
				fieldend[bos.y - 3][bos.x] = C_T_bos_T;
				fieldend[bos.y][bos.x] = C_T_AMULET;
			}
			else if (con <= 13) {
				fieldend[player.y][player.x] = C_T_NONE;
				fieldend[player.y - 1][player.x] = C_T_PLAYER;
			}
			else if (con <= 15) {
				fieldend[player.y-1][player.x] = C_T_NONE;
				fieldend[bos.y][bos.x] = C_T_NONE;
				fieldend[player.y - 2][player.x] = C_T_PLAYER;
			}
			else if (con <= 16) {
				fieldend[player.y - 2][player.x] = C_T_bos;
			}
			else if (con <= 17) {
				fieldend[player.y - 2][player.x] = C_T_PLAYER;
			}
			else if (con <= 18) {
				fieldend[player.y - 2][player.x] = C_T_bos;
			}
			else if (con <= 22) {
				fieldend[bos.y][bos.x - 2] = C_T_NONE;
				fieldend[bos.y - 1][bos.x + 2] = C_T_NONE;
				fieldend[bos.y - 3][bos.x] = C_T_NONE;
				fieldend[bos.y][bos.x - 1] = C_T_bos_L;
				fieldend[bos.y - 1][bos.x + 1] = C_T_bos_R;
				fieldend[bos.y - 2][bos.x] = C_T_bos_T;
			}
			else if (con <= 26) {
				fieldend[bos.y - 1][bos.x + 1] = C_T_NONE;
				fieldend[bos.y - 2][bos.x] = C_T_NONE;
				fieldend[bos.y][bos.x + 1] = C_T_bos_R;
				fieldend[bos.y - 1][bos.x] = C_T_bos_T;
			}
			else if (con > 27) {
					fieldend[bos.y-i][bos.x] = C_T_NONE;
					fieldend[bos.y-i][bos.x - 1] = C_T_NONE;
					fieldend[bos.y-i][bos.x + 1] = C_T_NONE;
					fieldend[bos.y -i- 1][bos.x] = C_T_NONE;
					fieldend[bos.y-i-1][bos.x] = C_T_bos;
					fieldend[bos.y-i-1][bos.x - 1] = C_T_bos_L;
					fieldend[bos.y-i-1][bos.x + 1] = C_T_bos_R;
					fieldend[bos.y-i - 2][bos.x] = C_T_bos_T;
					i++;
			}
			int buffer2[SCREEN_R * 3][SCREEN_R * 2];
			memcpy(buffer2, fieldend, sizeof fieldend);
			for (int y = 0; y < (SCREEN_R + SCREEN_R / 2) * 2; y++) {
				for (int x = 0; x < SCREEN_R * 2; x++) {
					printf("%s", cellAA[buffer2[y][x]]);
				}
				printf("\n");
			}
			con++;
		}
	}
	_getch();
}
//★エピローグ
void epi() {
	int con = 0;
	int i = 0;
	int end = 30 + rand() % 5;
	//部屋作成
	{
		//壁で埋める
		for (int y = 0; y < SCREEN_R * 3; y++) {
			for (int x = 0; x < SCREEN_R * 2; x++) {
				if (50 <= rand() % 100) {
					fieldend[y][x] = C_T_ROAD;
				}
				else {
					fieldend[y][x] = C_T_ROAD2;
				}
			}
		}
		//地面を作る
		for (int y = SCREEN_R; y < SCREEN_R * 3; y++) {
			for (int x = 0; x < SCREEN_R * 2; x++) {
				fieldend[y][x] = C_T_ROAD3;
			}
		}
		//道
		for (int y = SCREEN_R; y < SCREEN_R * 3; y++) {
			for (int x = SCREEN_R - 2; x < SCREEN_R + 3; x++) {
				fieldend[y][x] = C_T_NONE;
			}
		}
		//柵
		for (int x = SCREEN_R - 2; x < SCREEN_R + 3; x++) {
			if ( x == SCREEN_R + 1) {
				continue;
			}
			fieldend[SCREEN_R + 2][x] = C_T_ROAD4;
		}
		//看板
		fieldend[SCREEN_R + 3][SCREEN_R] = C_T_ROAD5;
		//入口枠
		for (int y = SCREEN_R - 4; y < SCREEN_R; y++) {
			for (int x = SCREEN_R - 2; x < SCREEN_R + 3; x++) {
				fieldend[y][x] = C_T_ROAD6;
			}
		}
		//入口
		for (int y = SCREEN_R - 3; y < SCREEN_R; y++) {
			for (int x = SCREEN_R - 1; x < SCREEN_R + 2; x++) {
				fieldend[y][x] = C_T_ROAD7;
			}
		}
	}
	//前回の更新時刻を宣言
	time_t lastC = clock();
	while (1) {
		//現在の時刻を宣言
		time_t newC = clock();
		if (newC > lastC + INTERVAL2) {
			lastC = newC;
			con++;
			system("cls");
			if (con <= 12) {
				player.y = SCREEN_R * 3 - 1, player.x = SCREEN_R;
				fieldend[player.y - i][player.x] = C_T_PLAYER;
				fieldend[player.y - i + 1][player.x] = C_T_NONE;
				i++;
			}
			else if (con <= 13) {
				fieldend[player.y-i+1][player.x+1] = C_T_PLAYER;
				fieldend[player.y-i+1][player.x] = C_T_NONE;
			}
			else if (con <=17){
				fieldend[player.y - i][player.x+1] = C_T_PLAYER;
				fieldend[player.y - i + 1][player.x+1] = C_T_NONE;
				i++;
			}
			else if (con <= 18) {
				fieldend[player.y - i + 1][player.x] = C_T_PLAYER;
				fieldend[player.y - i + 1][player.x+1] = C_T_NONE;
			}
			else if (con <= 19) {
				fieldend[player.y - i][player.x] = C_T_PLAYER;
				fieldend[player.y - i + 1][player.x] = C_T_NONE;
			}
			else if (con <= 20) {
				fieldend[player.y - i][player.x]  = C_T_ROAD7;
			}
			else if (con <= 23) {
				system("cls");
				continue;
			}
			else if (con <= end) {
				for (int i = 0; i < SCREEN_R; i++) {
					printf("\n");
				}
				printf("　　　　不思議のダンジョン\n");
				for (int i = 0; i < SCREEN_R * 3 - 10; i++) {
					printf("\n");
				}
				//nowloadingの表示
				{
					if (con % 4 == 0)
						printf("　　　　　　　　NowLoading");
					else if (con % 4 == 1)
						printf("　　　　　　　　NowLoading．");
					else if (con % 4 == 2)
						printf("　　　　　　　　NowLoading．．");
					else if (con % 4 == 3)
						printf("　　　　　　　　NowLoading．．．");
				}
				continue;
			}
			else if (con <= end + 1) {
				return;
			}
			int buffer2[SCREEN_R * 3][SCREEN_R * 2];
			memcpy(buffer2, fieldend, sizeof fieldend);
			for (int y = 0; y < (SCREEN_R + SCREEN_R / 2) * 2; y++) {
				for (int x = 0; x < SCREEN_R * 2; x++) {
					printf("%s", cellAA[buffer2[y][x]]);
				}
				printf("\n");
			}
		}
	}
	_getch();
}
//メイン関数
int main() {
	//乱数
	srand((unsigned int)time(NULL));
	//ターンの宣言
	int turn = 0;
	//ボス階層
	boss = 3+rand() % 3;
start://ゲーム開始ラベル
	;//空分
	Sleep(INTERVAL);
	epi();
	//経験値上限の宣言
	player.ex = 3 + lv * 2;
	//プレイヤーのステイタスの宣言
	player.hp = player.maxhp = 15 + hpp+lv+soubihp;
	player.att = 4 + attp + lv+soubiatt;
	//ダンジョン生成
	generateF();
	while (1) {
		//表示
		DS();
		int x = player.x, y = player.y;
		//行動ターン分岐
		int g = 1;
		if (bossP) {
			g = 2;
		}
		//魔王が生きているなら&&ボス部屋なら
		if (!(turn % g)) {
			//プレイヤーの操作
			switch (_getch()) {
			case'w'://6_11_38wがおされたら上へ移動
				y--;
				break;
			case's'://6_11_39sがおされたら上へ移動
				y++;
				break;
			case'a'://6_11_40aがおされたら上へ移動
				x--;
				break;
			case'd'://6_11_41dがおされたら上へ移動
				x++;
				break;
			case'q'://★qがおされたらステイタス画面へ移動
				steitas();
				continue;
				break;
			case'e'://★eがおされたらインベントリへ移動
				INVE();
				continue;
				break;
			}
		}
		//当たり判定分岐
		int g2 = -1;
		if (bossP){
			g2 = 1;
		}
		//行先にいる魔物に攻撃
		if (((x == enemy.x) && (y == enemy.y)) &&
			(enemy.hp > 0)) {
			printf("勇者の攻撃！\n");
			Sleep(INTERVAL);
			//ダメージ計算（最低値att/2　最高値att*1.5
			int att = player.att / 2 + rand() % player.att;
			//ダメージ処理
			enemy.hp -= att;
			printf("魔物Lv%dに%dのダメージ!", flo, att);
			Sleep(INTERVAL);
			_getch();
			//敵が倒れたら
			if (enemy.hp <= 0) {
				DS();
				printf("魔物Lv%dを倒した！\n", flo);
				exnow += enemy.ex;
				//★経験値が上がったら
				while (1) {
					if (player.ex <= exnow) {
						exnow = exnow - player.ex;
						//次の必要経験値を更新
						player.ex = 3 + lv * 2;
						lv++;
						point++;
						player.maxhp = 15 + hpp + lv + soubihp;
						player.att = 4 + attp + lv + soubiatt;
					}
					if (player.ex > exnow)break;
				}
				//★ドロップ判定
				int syutugen = rand() % 100;
				if (syutugen <= R_BUKI) {
					//ランダムで剣
					if (50 <= rand() % 100) {
						kenn.e = true;
						kenn.y = enemy.y;
						kenn.x = enemy.x;
						field[kenn.y][kenn.x] = C_T_E_2;
						//アイテムの効果
						kenn.kouka = 3 + (rand() % 2) * 3;
					}
					//ランダムで盾
					else {
						tate.e = true;
						tate.y = enemy.y;
						tate.x = enemy.x;
						field[tate.y][tate.x] = C_T_E_3;
						//アイテムの効果
						tate.kouka = 4 + (rand() % 3) * 4;
					}
				}
				Sleep(INTERVAL);
				_getch();
			}
		}
		//★行先にいる魔王に攻撃
		else if ((((x == bos.x) && (y == bos.y)) ||
			((x == bos.x - 1) && (y == bos.y)) ||
			((x == bos.x + 1) && (y == bos.y)) ||
			((x == bos.x) && (y == bos.y +g2))) &&
			(bos.hp > 0)) {
			if (!bossP) {
				printf("勇者の攻撃！\n");
			}
			else {
				printf("魔王の攻撃！\n");
			}
			Sleep(INTERVAL);
			//ダメージ計算（最低値att/2　最高値att*1.5
			int att = player.att / 2 + rand() % player.att;
			//ダメージ処理
			bos.hp -= att;
			if (!bossP) {
				printf("魔王に%dのダメージ!", att);
			}
			else {
				printf("勇者に%dのダメージ!", att);
			}
			Sleep(INTERVAL);
			_getch();
			if (bos.hp <= 0) {
				if (!bossP) {
					DS();
					printf("死闘の末 魔王を倒した！\n");
					Sleep(INTERVAL);
					//魔王が倒れたら宝を出現
					field[bos.y][bos.x] = C_T_AMULET;
					exnow += bos.ex;
				}
				else {
					DS();
					printf("死闘の末 勇者を退けた\n");
					Sleep(INTERVAL);
					goto start;
				}
				//★経験値が上がったら
				if (player.ex <= exnow) {
					exnow = exnow - player.ex;
					//次の必要経験値を更新
					player.ex = 3 + lv * 2;
					lv++;
					point++;
				}
				_getch();
			}
		}
		//行先に魔物がいなければ移動
		else {
			//行先のセル別の行動
			switch (field[y][x]) {
				//地面ならば移動
			case C_T_NONE:
				//移動先を確定
				player.x = x;
				player.y = y;
				//10ターン経過したら回復
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
				//壁ならば動かない
			case C_T_WALL:
				break;
				//階段ならばマップ更新
			case C_T_STAIRS:
				//階層加算
				flo++;
				//新しいエリア
				generateF();
				break;
				//宝ならクリア
			case C_T_AMULET:
				con();
				system("cls");
				bossP = true;
				bos.hp = bos.maxhp;
				//終わり
				goto start;
				break;
				//★アイテムを拾う(スクロール)
			case C_T_E_1:
				if (suku.e) {
					if (Isuu[0] >= 10) {
						DS();
						printf("勇者はスクロールを見飽きている");
					}
					else {
						inv[0][Isuu[0]] = suku.kouka;
						Isuu[0] += 1;
						suku.e = false;
						field[suku.y][suku.x] = C_T_NONE;
					}
				}
				DS();
				//移動先を確定
				player.x = x;
				player.y = y;
				//10ターン経過したら回復
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
				//★アイテムを拾う(剣)
			case C_T_E_2:
				if (kenn.e) {
					if (Isuu[1] >= 10) {
						DS();
						printf("勇者は武器を見飽きている");
						_getch();
					}
					else {
						inv[1][Isuu[1]] = kenn.kouka;
						Isuu[1] += 1;
						kenn.e = false;
						field[kenn.y][kenn.x] = C_T_NONE;
					}
				}
				DS();
				//移動先を確定
				player.x = x;
				player.y = y;
				//10ターン経過したら回復
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
				//★アイテムを拾う(盾)
			case C_T_E_3:
				if (tate.e) {
					if (Isuu[2] >= 10) {
						DS();
						printf("勇者は防具を見飽きている");
						_getch();
					}
					else {
						inv[2][Isuu[2]] = tate.kouka;
						Isuu[2] += 1;
						tate.e = false;
						field[tate.y][tate.x] = C_T_NONE;
					}
				}
				DS();
				//移動先を確定
				player.x = x;
				player.y = y;
				//10ターン経過したら回復
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
			}
		}
		//魔物が生きているなら
		if (enemy.hp > 0) {
			//自分のいる部屋の値を獲得
			int room = getR(enemy.x, enemy.y);
			//プレイヤーとの距離を獲得
			int distance = abs(player.x - enemy.x) + abs(player.y - enemy.y);
			//隣にプレイヤーがいたら
			if (distance == 1) {
				//表示関数
				DS();
				printf("魔物Lv%dの攻撃！\n", flo);
				Sleep(INTERVAL);
				//ダメージ計算（最低値att/2　最高値att*1.5
				int att = enemy.att / 2 + rand() % enemy.att;
				//ダメージ処理
				player.hp -= att;
				printf("勇者に%dのダメージ!", att);
				Sleep(INTERVAL);
				_getch();
				//プレイヤーが倒れたら
				if (player.hp <= 0) {
					DS();
					printf("迷宮をさまよう魔物と化してしまった…\n");
					printf("ＧＡＭＥ　ＯＶＥＲ\n\a");
					Sleep(INTERVAL);
					_getch();
					//終わり
					return 0;
				}
			}
			//同じ部屋にプレイヤーがいて離れていたら
			else if (((room >= 0) && (room == getR(player.x, player.y)))
				|| (distance <= 10)) {
				//座標を一時保存
				int x = enemy.x;
				int y = enemy.y;
				//移動結果を保存
				int xory = 0;
				//プレイヤーのいるほうへ移動
				//離れている軸を移動先に
				if ((abs(x - player.x)) > (abs(y - player.y))) {
					if (x < player.x) { x++; xory = 1; }
					else if (x > player.x) { x--; xory = 1; }
				}
				else {
					if (y < player.y) { y++; xory = 2; }
					else if (y > player.y) { y--; xory = 2; }
				}
				//壁にぶつかったら違う軸で移動
				if (field[y][x] == C_T_WALL) {
					//前回取り消し
					x = enemy.x;
					y = enemy.y;
					if (xory == 1) {
						if (y < player.y) { y++; }
						else if (y > player.y) { y--; }
					}
					else if (xory == 2) {
						if (x < player.x) { x++; }
						else if (x > player.x) { x--; }
					}
				}
				//重ならない式
				//プレイヤーと重ならない 
				if (((x == player.x) && (y == player.y)) ||
					//ボスと重ならない
					((y == bos.y) && ((x == bos.x) || (x == bos.x + 1) || (x == bos.x - 1))) ||
					//ボスの頭と重ならない
					((y == bos.y - 1) && (x == bos.x))) {
				}
				//移動先が壁ならば戻る
				else if (field[y][x] != C_T_WALL) {
					enemy.x = x;
					enemy.y = y;
				}
			}
		}
		//行動ターン分岐
		int g3 = 2;
		if (bossP){
			g3 = 1;
		}
		//魔王が生きているなら&&ボス部屋なら
		if ((bos.hp > 0) && (flo >= boss) && !(turn % g3)) {
			//プレイヤーとの距離を獲得
			int distance = abs(player.x - bos.x) + abs(player.y - bos.y);
			//攻撃範囲
			int g = 3;
			if (bossP){
				g = 2;
			}
			//隣にプレイヤーがいたら
			if (distance <= g) {
				//表示関数
				DS();
				if (!bossP) {
					printf("魔王の攻撃！\n");
				}
				else {
					printf("勇者の攻撃！\n");
				}
				Sleep(INTERVAL);
				//ダメージ計算（最低値att/2　最高値att*1.5
				int att = bos.att / 2 + rand() % bos.att;
				//ダメージ処理
				player.hp -= att;
				if (!bossP) {
					printf("勇者に%dのダメージ!", att);
				}
				else {
					printf("魔王に%dのダメージ!", att);
				}
				Sleep(INTERVAL);
				_getch();
				//プレイヤーが倒れたら
					if (player.hp <= 0) {
						if (!bossP) {
							DS();
							printf("迷宮をさまよう魔物と化してしまった…\n");
							printf("ＧＡＭＥ　ＯＶＥＲ\n\a");
							Sleep(INTERVAL);
							_getch();
							//終わり
							return 0;
						}
						else {
							DS();
							printf("元勇者は力尽きた…\n");
							printf("ＧＡＭＥ　ＯＶＥＲ\n\a");
							Sleep(INTERVAL);
							con();
							_getch();
							//終わり
							return 0;
						}
					}
			}
			//魔王の移動
			else {
				//座標を一時保存
				int x = bos.x;
				int y = bos.y;
				//移動結果を保存
				int xory = 0;
				//プレイヤーのいるほうへ移動
				//離れている軸を移動先に
				if ((abs(x - player.x)) > (abs(y - player.y))) {
					if (x < player.x) { x++; xory = 1; }
					else if (x > player.x) { x--; xory = 1; }
				}
				else {
					if (y < player.y) { y++; xory = 2; }
					else if (y > player.y) { y--; xory = 2; }
				}
				//壁にぶつかったら違う軸で移動
				if (field[y][x] == C_T_WALL) {
					//前回取り消し
					x = bos.x;
					y = bos.y;
					if (xory == 1) {
						if (y < player.y) { y++; }
						else if (y > player.y) { y--; }
					}
					else if (xory == 2) {
						if (x < player.x) { x++; }
						else if (x > player.x) { x--; }
					}
				}
				//プレイヤーと重ならない
				if (((y == player.y) && ((x == player.x) || (x == player.x + 1) || (x == player.x - 1))) ||
					((y == player.y + 1) && (x == player.x)) ||
					//魔物と重ならない
					((y == enemy.y) && ((x == enemy.x) || (x == enemy.x + 1) || (x == enemy.x - 1))) ||
					//魔物と重ならない
					((y == enemy.y + 1) && (x == enemy.x))) {
				}
				//移動先が壁ならば戻る
				else if (field[y][x] != C_T_WALL) {
					bos.x = x;
					bos.y = y;
				}

			}
		}
		//ターン経過
		turn++;
	}
}
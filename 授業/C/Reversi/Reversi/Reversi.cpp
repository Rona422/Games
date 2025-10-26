//1ヘッダー
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<time.h>  //1_3
#include<conio.h> //1_4
#include<vector>  //1_5
//2定数
#define BOARD_WIDTH (8)//2_1盤面の幅
#define BOARD_HRIGHT (8)//2_2盤面の高さ
//3列挙体
//3_1ターンの種類を定義する
enum {
	TURN_BLACK,//3_1_1黒
	TURN_WHITE,//3_1_2白
	TURN_NONE, //3_1_3なし
	TURN_MAX   //3_1_4ターン数
};
//3_2方向の種類
enum {
	//3_2_1~9上,左上,左,下,右下,右,右上,方向の数
	D_U, D_U_L, D_L, D_D_L, D_D, D_D_R, D_R, D_U_R, D_MAX
};
//3_3ゲームモードの種類
enum {
	//3_3_1~3CPUと対戦,人間同士の対戦,モード数
	M_1P,M_2P,M_WATCH,M_MAX
};
//4構造体
//4_1ベクトル構造体
typedef struct{
	int x, y;//4_1_1座標
}VEC2;
//5_1
const char* diskAA[TURN_MAX] = {
	"○",
	"●",
	"・"
};
//5_2変数
const char* turnN[] = {
	"黒",
	"白"
};
//5_3モードの名前
const char* modeN[] = {
	"１Ｐ ＧＡＭＥ",
	"２Ｐ ＧＡＭＥ",
	"ＷＡＴＣＨ"
};
//5_4方向の座標配列
VEC2 directions[D_MAX] = {
	//3_2_1~9上,左上,左,下,右下,右,右上
	{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}
};
//5_5盤面の状態
int board[BOARD_HRIGHT][BOARD_WIDTH];
VEC2 cursorP;//5_6カーソルの座標の宣言
int turn;//5_7現在のターン
//5_8現在のプレイモード
int mode;
//5_9現在のターンがプレイヤーのものか
bool isPlayer[TURN_MAX];
//6関数
//6_1ベクトルを加算する処理
VEC2 VecAbb(VEC2 _v0,VEC2 _v1){
	//6_1_2加算したベクトルを返す
	return{
		_v0.x + _v1.x,
		_v0.y + _v1.y
	};
}
//6_2石が置けるかどうかを判定する処理
bool CCP(int _color,VEC2 _position,bool _turnOver = false) {
	//6_2_1置けるかどうかのフラグ
	bool canPlace = false;
	//6_2_2対象の座標に石が置かれていないかを判定
	if (board[_position.y][_position.x]!=TURN_NONE){
		//6_2_3石が置けていたらfalse
		return false;
	}
	//6_2_4相手の石の色の宣言
	int opponent = _color ^ 1;
	//6_2_5すべての方向を繰り返し
	for (int i = 0; i < D_MAX; i++){
		//6_2_6現在チェック中の座標を宣言
		VEC2 currentP = _position;
		//6_2_7隣接するマスに移動
		currentP = VecAbb(currentP,directions[i]);
		//6_2_8相手の石でないか判定
		if (board[currentP.y][currentP.x]!=opponent){
			//6_2_9相手の意思でない倍、次の隣接へ
			continue;
		}
		//6_2_10無限ループ
		while (1){
			//6_2_11隣接するマスに移動
			currentP = VecAbb(currentP, directions[i]);
			//6_2_12チェックするマスが盤面内でないか判定
			if ((currentP.x<0)||(currentP.x>= BOARD_WIDTH)||
				(currentP.y < 0)||(currentP.y >= BOARD_HRIGHT)){
				//6_2_13盤面の外に出てしまったら現在のチェックを抜ける
				break;
			}
			//6_2_14チェックするマスに石がないか判定
			if (board[currentP.y][currentP.x] == TURN_NONE) {
				//6_2_15石がなければ現在のチェックを抜ける
				break;
			}
			//6_2_16チェックするマスに自分の石があれば
			if (board[currentP.y][currentP.x] == _color) {
				//6_2_17石を置けることが確定する
				canPlace = true;
			}
			//6_2_18反転処理
			if (_turnOver){
				//6_2_19ひっくり返す座標
				VEC2 reverseP = _position;
				//6_2_20隣接のマスに移動
				reverseP = VecAbb(reverseP,directions[i]);
				//6_2_21現在のターンの石が見つかれるまで繰り返し
				do{
					//6_2_22相手の石をひっくり返す
					board[reverseP.y][reverseP.x] = _color;
					//6_2_23隣接のマスに移動
					reverseP = VecAbb(reverseP, directions[i]);
				} while (board[reverseP.y][reverseP.x]!=_color);
			}
		}
	}
	//6_2_24フラグを返す
	return canPlace;
}
//6_3盤面上に石を置けるマスがあるかどうか判定する処理
bool CCPA(int _color) {
	//6_3_1盤面の行分を繰り返し
	for (int y = 0;y< BOARD_HRIGHT; y++){
		//6_3_2盤面の列分を繰り返し
		for (int x = 0;x<BOARD_WIDTH; x++){
			//6_3_3判定する座標
			VEC2 position = { x,y };
			//6_3_4対象の石に置けるかどうか判定
			if (CCP(_color,position)){
				//6_3_5
				return true;
			}
		}
	}
	//6_3_3
	return false;
}
//6_4任意の石の数を数える処理
int GDCount(int _color) {
	//6_4_1数える医師の数を保持する変数
	int count = 0;
	//6_4_2盤面のすべての列分繰り返し
	for (int y = 0; y < BOARD_HRIGHT; y++) {
		//6_4_3盤面のすべての行分繰り返し
		for (int x = 0; x < BOARD_WIDTH; x++) {
			//6_4_4対象の石があるかどうかを判定
			if (board[y][x] == _color) {
				//6_4_5石の数を加算する
				count++;
			}
		}
	}
	//6_4_6数えた石の数を返す
	return count;
}
//6_5描画処理
void DS() {
	//6_5_1画面クリア
	system("cls");
	//6_5_2盤面のすべての列分繰り返し
	for (int y = 0; y < BOARD_HRIGHT; y++) {
		//6_5_3盤面のすべての行分繰り返し
		for (int x = 0; x < BOARD_WIDTH; x++) {
			//6_5_4石の描画
			printf("%s", diskAA[board[y][x]]);
		}
		//6_5_5プレイヤーだった場合
		if (isPlayer[turn]) {
			//6_5_6対象の行がカーソルと同じ行か判定
			if (y == cursorP.y) {
				printf("←");//6_5_7カーソル(行)を描画
			}
			printf("　");
		}
		//6_5_8改行
		printf("\n");
	}
	//6_5_9プレイヤーだった場合
	if (isPlayer[turn]) {
		//6_5_10盤面のすべての行分繰り返し
		for (int x = 0; x < BOARD_WIDTH; x++) {
			//6_5_11対象の列がカーソルと同じ列か判定
			if (x == cursorP.x) {
				printf("↑");//6_5_12カーソル(列)を描画
			}
			else {
				printf("　");//6_5_13全角スペースを描画
			}
		}
	}
	//6_5_14改行
	printf("\n");
	//6_5_15決着がついたかの判定
	if (turn!=TURN_NONE) {
		//6_5_16ターン表示
		printf("%sのターンです\n", turnN[turn]);
	}
	//6_5_17決着がついた場合
	else{
		//6_5_18黒い石の数をカウント
		int blackC =GDCount(TURN_BLACK);
		//6_5_19白い石の数をカウント
		int whiteC = GDCount(TURN_WHITE);
		//6_5_20勝者を保持する変数
		int winner;
		//6_5_21勝者を判定
		if (blackC > whiteC) {//6_5_22黒が多かった場合
			winner = TURN_BLACK;//6_5_23
		}
		else if (whiteC>blackC){//6_5_24白が多かった場合
			winner = TURN_WHITE;//6_5_25
		}
		else{//6_5_26同じ数の場合
			winner = TURN_NONE;//6_5_27
		}
		//6_5_28両者の石の数を表示する
		printf("%s%d---%s%d",turnN[TURN_BLACK],GDCount(TURN_BLACK),
							 turnN[TURN_WHITE], GDCount(TURN_WHITE));
		//6_5_29引き分けかどうか判定
		if (winner == TURN_NONE){
			printf("引き分け\n");
		}
		else {
			printf("%sの勝ち", turnN[winner]);
		}
		_getch();
	}
}
//6_6モード選択処理
void SM() {
	//6_6_1ゲームモードの初期化
	mode = M_1P;
	//6_6_2無限ループ
	while (1) {
		//6_6_3画面クリア
		system("cls");
		printf("モードを　選択して\nください\n");//6_6_4
		printf("\n\n");//6_6_5
		//6_6_6モード数分繰り返し
		for (int i = 0; i < M_MAX; i++){
			printf("%s　",(i==mode)?"＞":"　");//6_6_7
			printf("%s\n",modeN[i]);//6_6_8
			printf("\n");//6_6_9
		}
		//6_6_10入力
		switch(_getch()){
		case'w'://6_6_11wの場合
			mode--;//6_6_12前のモードに切り替え
			break;
		case's'://6_6_13sの場合
			mode++;//6_6_14次のモードに切り替え
			break;
		default://6_6_15
			//6_6_16モードでの分岐
			switch (mode) {
				//6_6_17ＣＰＵと対戦モード
				case M_1P:
					//6_6_18黒をプレイヤー
					isPlayer[TURN_BLACK] = true;
					//6_6_19白をＣＰＵ
					isPlayer[TURN_WHITE] = false;
					break;
				//6_6_20人間同士対戦モード
				case M_2P:
					//6_6_21両方プレイヤー
					isPlayer[TURN_BLACK] = isPlayer[TURN_WHITE] = true;
					break;
				//6_6_22CPU同氏の対戦
				case M_WATCH:
					//6_6_23両者をCPUにする
					isPlayer[TURN_BLACK] = isPlayer[TURN_WHITE] = false;
			}
				return;//6_6_24モード選択を抜ける
		}
		//6_6_25カーソルを上下にループ
		mode = (M_MAX + mode) % M_MAX;
	}
}
//6_7ゲームを初期化
void Init() {
	//6_7_1盤面のすべての列分繰り返し
	for (int y = 0; y < BOARD_HRIGHT; y++){
		//6_7_2盤面のすべての行分繰り返し
		for (int x = 0; x < BOARD_WIDTH; x++){
			//6_7_3対象マスを石が置かれていない状態にする
			board[y][x] = TURN_NONE;
		}
	}
	//6_7_4盤面中央の右上と左下に黒い石を置く
	board[4][3] = board[3][4] = TURN_BLACK;
	//6_7_5盤面中央の右下と左上に黒い石を置く
	board[3][3] = board[4][4] = TURN_WHITE;
	//6_7_6
	turn = TURN_BLACK;
	//6_7_7カーソル座標の初期化
	cursorP = {3,3};
	//6_7_8描画処理を呼び出す
	DS();
}
//6_8石を置くマスを選択する処理
VEC2 InputP() {
	//6_8_1選択するまで無限ループ
	while (1) {
		//6_5_2画面の描画
		DS();
		//6_5_3キーボード入力
		switch (_getch()) {
		case 'w'://6_8_4wが入力された場合
			cursorP.y--;//6_8_5カーソルを上に移動
			break;
		case 's'://6_8_6sが入力された場合
			cursorP.y++;//6_8_7カーソルを下に移動
			break;
		case 'a'://6_8_8aが入力された場合
			cursorP.x--;//6_8_9カーソルを左に移動
			break;
		case 'd'://6_8_10dが入力された場合
			cursorP.x++;//6_8_11カーソルを右に移動
			break;
		default://6_5_12上記以外のキーが押された場合
			if (CCP(turn,cursorP)) {
				return cursorP;;//6_5_13カーソルの座標を返す
			}
			else {
				//6_8_16置けないと表示
				printf("そこにはおけません");
				//6_8_17キーボード入力待ち
				_getch();
			}
			break;
		}
		//6_8_18カーソルを左右にループ
		cursorP.x = (BOARD_WIDTH + cursorP.x)% BOARD_WIDTH;
		//6_8_19カーソルを上下にループ
		cursorP.y = (BOARD_HRIGHT + cursorP.y) % BOARD_HRIGHT;
	}
}
//6_9メイン関数
int main() {
	srand((unsigned int)time(NULL));//6_9_1
start://6_9_2開始ラベル
	;//6_9_3
	SM();//6_9_4モード選択
	//6_9_5初期化する処理を呼び出す
	Init();
	//6_9_6ループ
	while (1) {
		//6_9_7置けるマスがないかどうか判定
		if (!CCPA(turn)){
			//6_9_8ターン切り替え
			turn ^= 1;
			//6_9_9置けるマスがないかどうか判定
			if (!CCPA(turn)){
				//6_9_10決着
				turn = TURN_NONE;
				//6_9_11画面描画
				DS();
				//6_9_12キーボード入力待ち
				_getch;
				goto start;//6_9_13開始ラベルにジャンプ
			}
			//6_9_14相手に置けるマスがあれば
			else {
				//6_9_15相手のターンへ
				continue;
			}
		}
		//6_9_16石を置くマスを宣言
		VEC2 plaseP;
		//6_9_17
		if (isPlayer[turn]) {
			//6_9_18石を置くマスを選択する関数を呼び出す
			plaseP = InputP();

			_getch();
		}
		//6_9_19ＣＰＵだった場合
		else {
			//6_9_20画面描写
			DS();
			//6_9_21キーボード入力待ち
			_getch();
			//6_9_22置ける座標を保持するベクター
			std::vector<VEC2>positions;
			//6_9_23盤面のすべての列分繰り返し
			for (int y = 0; y < BOARD_HRIGHT; y++) {
				//6_9_24盤面のすべての行分繰り返し
				for (int x = 0; x < BOARD_WIDTH; x++) {
					//6_9_25
					VEC2 position = { x,y };
					//6_9_26対象の座標に石を置けるか判定
					if (CCP(turn,position)){
						//6_9_27座標リストに対象の座標を追加
						positions.push_back(position);
					}
				}
			}
			//6_9_28置ける場所をランダムに取得
			plaseP = positions[rand()%positions.size()];
		}
		//6_9_29石をひっくり返す
		CCP(turn,plaseP,true);
		//6_9_30現在のターンの石を置く
		board[plaseP.y][plaseP.x] = turn;
		//6_9_31ターンを切り替え
		turn ^= 1;
	}
}
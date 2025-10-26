//1ヘッダー
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
//2定数
#define FIELD_WIDTH (16)   //2_1フィールドの幅
#define FIELD_HEIGHT (16)  //2_2フィールドの高さ
#define FPS (1)           //2_3一秒値の更新回数を定義する
#define INTERVAL (100/FPS)//2_4更新間隔(ミリ秒)
//3変数
//3_1フィールドの宣言
//bool:true(1)/false(0)の型
bool field[FIELD_WIDTH][FIELD_HEIGHT] = {
	/*{0,1,1,1},
	{0,1,0,1},
	{0,0,1,1},
	{1,1,1,0}*/
};
//4関数
//4_1描画処理
void DrowField() {
	//4_1_1画面クリア
	system("cls");
	//4_1_2すべての行分繰り返し
	for (int i = 0; i < FIELD_HEIGHT; i++){
		//4_1_3すべての列分繰り返し
		for (int j = 0; j < FIELD_WIDTH; j++){
			//4_1_4セルが生きている場合「■」偽である場合「　」
			printf("%s", field[i][j] ? "■" : "　"); 
		}
		//4_1_5一行描画するたびに改行
		printf("\n");
	}
}
//4_2対象のセルと隣接する生のセルの数を取得する関数
int GCC(int _i, int _j) {
	//4_2_1生のセルを数える変数
	int cnt = 0;
	//4_2_2対象のセルの上下1マスを繰り返し
	for (int j = _j-1; j <=_j+1; j++){
		//4_2_3範囲内かどうか判定
		/*if ((j < 0) || (j >= FIELD_HEIGHT))
			continue;//4_2_4範囲外なので次へ*/
		//4_2_5上下にループしたｙ座標
		int roopy = (FIELD_HEIGHT + j) % FIELD_HEIGHT;
		//4_2_6対象のセルの左右1マスを繰り返し
		for (int i = _i + -1; i <=_i+1; i++){
			//4_2_7範囲内かどうか判定
			/*if ((i< 0) || (i >= FIELD_WIDTH))
				continue;//4_2_8範囲外なので次へ*/
			//4_2_9上下にループしたｘ座標
			int roopx = (FIELD_WIDTH + i) % FIELD_WIDTH;
			//4_2_10
			if ((roopx==_i)&&(roopy==_j)){
				continue;//4_2_11対象の座標をスキップ
			}
			//4_2_12生のセルをカウント
			cnt += field[roopy][roopx];
		}
	}
	//4_2_13生のセルの数を返す
	return cnt;
}
//4_3シミュレーション処理
void SS() {
	//4_3_1次の世代のフィールド
	bool nextF[FIELD_WIDTH][FIELD_HEIGHT] = {};
	//4_3_2すべての行分繰り返し
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		//4_3_3すべての列分繰り返し
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//4_3_4対象のセルと隣接する生のセルをカウント
			int livingCC = GCC(j, i);
			//4_3_5生存セルが1以下の場合
			if (livingCC <= 1){
				//4_3_6セルを死亡状態にする
				nextF[i][j] = false;
			}
			//4_3_7生存セルが2だった場合
			else if (livingCC == 2){
				//4_3_8セルを現状維持
				nextF[i][j] = field[i][j];
			}
			//4_3_9生存セルが3だった場合
			else if (livingCC == 3) {
				//4_3_10セルを生存状態にする
				nextF[i][j] = true;
			}
			//4_3_11それ以外(4以上)
			else{
				//4_3_12セルを死亡状態にする
				nextF[i][j] = false;
			}
		}
	}
	//4_3_13次の世代を現在の世代へコピーコピー
	//memcpy(コピー先,コピー元,サイズ)
	memcpy(field,nextF,sizeof(field));
}
//4_4パターンをフィールドにコピーする処理
void PatternT(int _destx, int _desty, int _srcw, int _srch, bool* _pp) {
//コピー先の原点の座標X,Y,書き込むパターンのサイズの幅,高さ,データのアドレス
	//4_4_1パターン内の行分の繰り返し
	for (int y = 0; y < _srcw; y++){
		//4_4_1パターン内の列分の繰り返し
		for (int x = 0; x < _srch; x++){
			//4_4_3パターンをフィールドにコピー
			field[_desty + y][_destx + x] = _pp[y*_srcw+x];
		}
	}
}
//4_5メイン関数
int main() {
	//4_5_1パターンの幅
	const int patternw = 15;
	//4_5_2パターンの高さ
	const int patternh = 15;
	//4_5_3パターンを宣言
	bool pattern[patternh][patternw] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	//4_5_4パターンをフィールドの中心にコピー
	PatternT(FIELD_WIDTH / 2 - patternw / 2,
		FIELD_HEIGHT / 2 - patternh / 2,
		patternw, patternh, (bool*)pattern);
	//4_5_5前回の経過時間を設定
	clock_t lastClock = clock();
	//4_5_6
	while (1){
		//4_5_7現在の経過時間を設定
		clock_t newClock = clock();
		//4_5_8前回の経過時間から、待機時間が経過していなければ
		if (newClock<lastClock+INTERVAL){
			//4_5_9次のループへ
			continue;
		}
		//4_5_10前回の経過時間を、現在の経過時間で更新する
		lastClock = newClock;
		//4_5_11描画処理を呼び出す	
		DrowField();
		//4_5_12キーボード入力待ち
		//_getch();
		//4_5_13シミュレーション処理
		SS();
	}
}
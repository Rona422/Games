//�v���p�e�B130*65�@�t�H���g�T�C�Y14
//�v���p�e�B35*30�@�t�H���g�T�C�Y36
//�t�H���g�@����S�V�b�N��Q
//wasd�ړ��L�[ q�X�e�[�^�X��ʊJ�� e�C���x���g���J�� ���̑�:����
//���{�X�����̒ǉ�
//�����x���A�b�v�ƃX�e�[�^�X�̊���U��
//���C���x���g���ƃA�C�e���̒ǉ�
//��������
//���G�s���[�O�E�G���f�B���O�̒ǉ�
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
#define R_SUKU (75)//���X�N���[���̏o����
#define R_BUKI (75)//�������т̃h���b�v��
//�Z���̏��
enum {
	C_T_NONE,  //��
	C_T_WALL,  //��
	C_T_STAIRS,//�K�i
	C_T_AMULET,//��
	C_T_PLAYER,//�v���C���[
	C_T_ENEMY, //�G
	C_T_bos,   //�{�X
	C_T_bos_R, //�{�X�E
	C_T_bos_L, //�{�X��
	C_T_bos_T, //�{�X��
	C_T_E_1,   //�A�C�e��
	C_T_E_2,   //�A�C�e��2
	C_T_E_3,   //�A�C�e��3
	C_T_ROAD,//��
	C_T_ROAD2,//��2
	C_T_ROAD3,//��3
	C_T_ROAD4,//��4
	C_T_ROAD5,//��5
	C_T_ROAD6,//��
	C_T_ROAD7,//��
};
//���[���̍\����
typedef struct {
	int x, y, w, h;
}ROOM;
//�G���A�̍\����
typedef struct {
	int x, y, w, h;
	ROOM room;
}AREA;
//�L�����N�^�[�̍\����
typedef struct {
	int x, y;
	int hp, maxhp;
	int att;
	int ex;
}C;
//�A�C�e���̍\����
typedef struct {
	int x, y;
	int kouka;
	bool e;
}E;
//�v���C���[�̐錾
C player;
//�G�̐錾
C enemy;
//�{�X�̐錾
C bos;
//�A�C�e��
E suku;
E kenn;
E tate;
//�G���A�̐錾
AREA areas[AREA_MAX];
//�K�w�̐錾�Ƃ�
int flo=1,lv=1,exnow=0,point=1,hpp=0,attp = 0,soubiatt=0,soubihp=0;
//�{�X����
int boss = 0;
bool bossP=false;
//�A�C�e���Ǘ�
int inv[3][10]{};
//�A�C�e���ԍ�
int Isuu[3] = { 0,0,0 };
//�ǂƏ��̃A�X�L�[�A�[�g
char cellAA[][2 + 1] = {
	"�D",//C_T_NONE
	"�f",//C_T_WALL
	"��",//C_T_STAIRS
	"��",//C_T_AMULET
	"��",//C_T_PLAYER
	"�v",//C_T_ENEMY
	"��",//C_T_bos
	"�`",//C_T_bos_R
	"�e",//C_T_bos_L
	"�",//C_T_bos_T
	"��",//C_T_E_1
	"��",//C_T_E_2
	"��",//C_T_E_3
	"�T",//C_T_ROAD
	"��",//C_T_ROAD2
	"�X",//C_T_ROAD3
	"��",//C_T_ROAD4
	"�\",//C_T_ROAD5
	"�M",//C_T_ROAD6
	"�@",//C_T_ROAD6
};
//�G���A��
int areaC;
//�t�B�[���h�̐錾
int field[F_HEIGHT][F_WIDTH];
int fieldend[(SCREEN_R+ SCREEN_R/2)*2][(SCREEN_R)*2];
//�\���֐�
void DS() {
	int buffer[F_HEIGHT][F_WIDTH];
	memcpy(buffer, field, sizeof field);
	//�e�I�u�W�F�N�g�̕\����
	{
		if (!bossP){
			//�{�X�����Ŏ���ł��Ȃ���Ε\��
			if ((bos.hp > 0) && (flo >= boss)) {
				buffer[bos.y][bos.x] = C_T_bos;
				buffer[bos.y][bos.x + 1] = C_T_bos_R;
				buffer[bos.y][bos.x - 1] = C_T_bos_L;
				buffer[bos.y - 1][bos.x] = C_T_bos_T;
			}
			//����ł��Ȃ���Ε\��
			if (player.hp > 0) {
				buffer[player.y][player.x] = C_T_PLAYER;
			}
		}
		else {
			//�{�X�����Ŏ���ł��Ȃ���Ε\��
			if ((bos.hp > 0) && (flo >= boss)) {
				buffer[bos.y][bos.x] = C_T_PLAYER;
			}
			//����ł��Ȃ���Ε\��
			if (player.hp > 0) {
				buffer[player.y][player.x] = C_T_bos;
				buffer[player.y][player.x + 1] = C_T_bos_R;
				buffer[player.y][player.x - 1] = C_T_bos_L;
				buffer[player.y - 1][player.x] = C_T_bos_T;
			}
		}
		//����ł��Ȃ���Ε\��
		if (enemy.hp > 0) {
			buffer[enemy.y][enemy.x] = C_T_ENEMY;
		}
		//�擾���Ă��Ȃ��Ȃ�\��
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
	//��ʃN���A
	system("cls");
	//UI
		printf("%2dF Lv%2d HP:%2d/%2d EXP:%2d/%2d SP%2d\n", flo, lv, player.hp, player.maxhp, exnow, player.ex, point);
		//�v���C���[�̎��肾���\��
		for (int y = player.y - SCREEN_R; y < player.y + SCREEN_R; y++) {
			for (int x = player.x - SCREEN_R; x < player.x + SCREEN_R; x++) {
				//�G���A�O
				if ((x < 0) || (x >= F_WIDTH) || (y < 0) || (y >= F_HEIGHT)) {
					printf("�i");
				}
				else {
					printf("%s", cellAA[buffer[y][x]]);
				}
			}
			printf("\n");
		}
}
//�\���֐� �g��Ȃ�
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
			char str[] = "�O";
			str[1] += buffer[y][x] %10;
			printf("%s", str);
		}
		printf("\n");
	}
}
//�t�B�[���h�����֐�
void spritA(int _areaI) {
	int newareaI = areaC;
	//��O��ۑ�
	int w = areas[_areaI].w;
	int h = areas[_areaI].h;
	//�c�����Ɖ������������_����
	if (rand() % 2) {
			//�c����nearea�̏c�Ɖ��̍��W
			areas[_areaI].w /= 2;
			areas[newareaI].x = areas[_areaI].x + areas[_areaI].w;
			areas[newareaI].y = areas[_areaI].y;
			areas[newareaI].w = w - areas[_areaI].w;
			areas[newareaI].h = areas[_areaI].h;
		}
	else {
			//������nearea�̏c�Ɖ��̍��W
			areas[_areaI].h /= 2;
			areas[newareaI].x = areas[_areaI].x;
			areas[newareaI].y = areas[_areaI].y + areas[_areaI].h;
			areas[newareaI].w = areas[_areaI].w;
			areas[newareaI].h = h - areas[_areaI].h;
		}
	//�{�X����
	if (flo>=boss){
		//�����������ł��Ȃ��ꍇ(�����_���őI�΂ꂽ�ق���)
		if ((areas[_areaI].w < AREA_SIZE_MIN_bos) || (areas[_areaI].h < AREA_SIZE_MIN_bos) ||
			(areas[newareaI].w < AREA_SIZE_MIN_bos) || (areas[newareaI].h < AREA_SIZE_MIN_bos)) {
			//��O�ɖ߂�
			areas[_areaI].w = w;
			areas[_areaI].h = h;
			return;//�I��
		}
	}
	else {
		//�����������ł��Ȃ��ꍇ(�����_���őI�΂ꂽ�ق���)
		if ((areas[_areaI].w < AREA_SIZE_MIN) || (areas[_areaI].h < AREA_SIZE_MIN) ||
			(areas[newareaI].w < AREA_SIZE_MIN) || (areas[newareaI].h < AREA_SIZE_MIN)) {
			//��O�ɖ߂�
			areas[_areaI].w = w;
			areas[_areaI].h = h;
			return;//�I��
		}
	}
	areaC++;//�G���A�ԍ�
	spritA(_areaI);//�]�����ق����ĕ���
	spritA(newareaI);//�V�����ł����ق����ĕ���
}
//�����_���|�W�V����
void GRP(int *_px,int *_py){
	//�h�b�g�C�[�g�ł������i���̓G���A�P��
	int areaI = rand() % areaC;
	*_px = areas[areaI].room.x + rand() % areas[areaI].room.w;
	*_py = areas[areaI].room.y + rand() % areas[areaI].room.h;
}
//�G���A����
void generateF() {
	areaC = 0;//�G���A�ԍ�
	areas[0].x = areas[0].y = 0;
	areas[0].w = F_WIDTH, areas[0].h = F_HEIGHT;
	areaC++;
	//�����֐�
	spritA(0);
	//��U�S���ǂŖ��߂�
	for (int y = 0; y <  + F_HEIGHT; y++) {
		for (int x = 0; x < F_WIDTH; x++) {
			field[y][x] = C_T_WALL;
		}
	}
	//���ꂼ��̃��[���̒�`
	for (int i = 0; i < areaC; i++) {
		//�ʘH���O�g�c���ă��[���̒�`
		areas[i].room.x = areas[i].x + 2;
		areas[i].room.y = areas[i].y + 2;
		areas[i].room.w = areas[i].w - 4;
		areas[i].room.h = areas[i].h - 4;
		//���[����C_T_NONE��
		for (int y = areas[i].room.y; y < areas[i].room.y + areas[i].room.h; y++) {
			for (int x = areas[i].room.x; x < areas[i].room.x + areas[i].room.w; x++) {
				field[y][x] = C_T_NONE;
			}
		}
		//���[���̉E�ɒʘH
		for (int x = areas[i].x; x < areas[i].x + areas[i].w; x++) {
			field[areas[i].y + areas[i].h - 1][x] = C_T_NONE;
		}
		//���[���̉��ɒʘH
		for (int y = areas[i].y; y < areas[i].y + areas[i].h; y++) {
			field[y][areas[i].x + areas[i].w - 1] = C_T_NONE;
		}
		//���[���̏�Ɍ�
		for (int y2 = areas[i].y; y2 < areas[i].room.y; y2++) {
			field[y2][areas[i].x+areas[i].room.w/2] = C_T_NONE;
		}
		//���[���̉��Ɍ�
		for (int y2 = areas[i].room.y+ areas[i].room.h; y2 < areas[i].y+ areas[i].h; y2++) {
			field[y2][areas[i].x + areas[i].room.w / 2] = C_T_NONE;
		}
		//���[���̍��Ɍ�
		for (int x2 = areas[i].x; x2 < areas[i].room.x; x2++) {
			field[areas[i].y+areas[i].room.h/2][x2] = C_T_NONE;
		}
		//���[���̉E�Ɍ�
		for (int x2 = areas[i].room.x+ areas[i].room.w; x2 < areas[i].x+ areas[i].w; x2++) {
			field[areas[i].y + areas[i].room.h / 2][x2] = C_T_NONE;
		}
	}
	//���̒[��C_T_WALL�Ŗ��߂�
	for (int y = 0; y < F_HEIGHT; y++) {
		field[y][F_WIDTH - 1] = C_T_WALL;
	}
	//�E�̒[��C_T_WALL�Ŗ��߂�
	for (int x = 0; x < F_WIDTH; x++) {
		field[F_WIDTH-1][x] = C_T_WALL;
	}
	//�s���~�܂��C_T_WALL�Ŗ��߂�
	while (1) {
		//���܂��Ă邩�̃t���O
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
	//�v���C���[�Ƀ����_���ȍ��W��
	GRP(&player.x,&player.y);
	//�K�i�Ƀ����_���ȍ��W��
	if (flo < boss){
		int x, y;
		GRP(&x,&y);
		field[y][x] = C_T_STAIRS;
	}
	//�K�i�̑���Ƀ{�X
	else {
		if (!bossP){
			//�G�Ƀ����_���ȍ��W��
			GRP(&bos.x, &bos.y);
			bos.hp = bos.maxhp = 20 + flo * 6;
			bos.att = 4 + flo * 4;
			bos.ex = 5 + flo * 5;
		}
		else{
			//�G�Ƀ����_���ȍ��W��
			GRP(&bos.x, &bos.y);
			bos.hp = bos.maxhp = 25 + flo * 7;
			bos.att = 5 + flo * 5;
			bos.ex = 5 + flo * 8;
		}
	}
	//�G�Ƀ����_���ȍ��W��
	if(!bossP){
		GRP(&enemy.x, &enemy.y);
		enemy.hp = enemy.maxhp = 2 + flo * 2;
		enemy.att = 2 + flo;
		enemy.ex = 2 + flo;
	}
	//�o���������_����
	int syutugen = rand() % 100;
	if(syutugen<=R_SUKU){
		suku.e = true;
		//�X�N���[���Ƀ����_���ȍ��W��
		GRP(&suku.x, &suku.y);
		field[suku.y][suku.x] = C_T_E_1;
		suku.kouka = 1+rand()% 2;
	}
}
//�G���A�̕\���@�g��Ȃ�
void DF() {
	system("cls");
	for (int y = 0; y < +F_HEIGHT; y++) {
		for (int x = 0; x < F_WIDTH; x++) {
			if ((x == player.x) && y == player.y)
				printf("�t");
			else
			printf("%s", cellAA[field[y][x]]);
		}
		printf("\n");
	}
}
//�ǂ��̕����ɂ��邩
int getR(int _x, int _y) {
	//���������[�v
	for (int i = 0; i < areaC; i++){
		//�����ɂ��邩����
		if ((_x>=areas[i].room.x)&&(_x<areas[i].room.x+areas[i].room.w)&&
			(_y>=areas[i].room.y)&&(_y<areas[i].room.y+areas[i].room.h)){
			return i;
		}
	}
	return -1;
}
//���X�e�C�^�X���
void steitas() {
	int senntaku = 0;
	while (1) {
	system("cls");
	for (int i = 0; i < SCREEN_R/3; i++){
		printf("\n");
	}
		printf("�@�@�X�e�[�^�X�|�C���g����U��\n\n\n");
		printf("�@�@�@�c��|�C���g�@%d\n\n",point);
		if (!(senntaku%2)){
			printf(" �@�@  �@��\n");
		}
		else{
			printf(" �@  �@ �@�@�@�@�@ �@�@��\n");
		}
		printf("   �@ �@�g�o�@�@�@�@��������\n\n");
		printf("   �@ �@HP:%d�@�@�@ attack:%d\n",player.maxhp,player.att);
		//�����؂�ւ�
		switch (_getch()) {
		case'a':
			senntaku++;
			break;
		case'd':
			senntaku++;
			break;
			//�I��
		case'q':
			DS();
			return;
			break;
		default:
			if (point!=0){
				if (!(senntaku % 2)) {
					hpp += 3 + rand() % 2;
					player.maxhp = 15 + hpp + lv + soubihp;
					//�㏸��������
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
//�����ђ��A�C�e��
int soubi = 11, soubi2 = 11;
//���C���x���g��
void INVE() {
	int senntaku = 0;
	int senntate = 0;
	//senntate�̏�����
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
		//�I�𒆂�\��
		if (!(senntaku % 2)) {
			printf(" �@  �@�@ ��\n");
		}
		else {
			printf(" �@�@ �@�@�@�@�@ �@�@�@�@ ��\n");
		}
		//�I���ꗗ
		printf("   �@ �X�N���[���@�@�@�@������\n\n");
		//�X�N���[��
		if (!(senntaku % 2)) {
			for (int i = 0; i < 9; i++){
				if (inv[0][i] == 0) {
					continue;
				}
				//�I���R�}���h�Ȃ�
				if (i==senntate) {
					//6_3_6�J�[�\���̕`��
					printf("�@�@�@��");
				}
				//6_3_7�I���R�}���h�Ŗ����Ȃ�
				else {
					//6_3_8�S�p�X�y�[�X�̕`��
					printf("�@�@�@�@");
				}
				if (inv[0][i]==1) {
					printf("�@���[�v�̂܂�����");
					printf("\n");
				}
				else if (inv[0][i]==2){
					printf("�@�񕜂̂܂�����");
					printf("\n");
				}
			}
		}
		//����
		else{
			for (int j = 1; j < 3; j++) {
				for (int i = 0; i < 9; i++) {
					if (inv[j][i] == 0) {
						continue;
					}
					//����Ȃ�
					if (j == 1) {
						//�I���R�}���h�Ȃ�
						if (i == senntate) {
							//6_3_6�J�[�\���̕`��
							printf("�@��");
						}
						//�I���R�}���h�Ŗ����Ȃ�
						else {
							//�S�p�X�y�[�X�̕`��
							printf("�@�@");
						}
						if (inv[j][i] == 3) {
							printf("�@�؂̂���_�@ attack%2d", inv[j][i]);
						}
						else if (inv[j][i] == 6) {
							printf("�@�S�̂���_�@ attack%2d", inv[j][i]);
						}
						else if (inv[j][i] == 9) {
							printf("�@�^�̂���_�@ attack%2d", inv[j][i]);
						}
						if (soubi == i) {
							printf("�@E");
						}
						printf("\n");
					}
					//�h��Ȃ�
					else if (j==2){
						//�I���R�}���h�Ȃ�
						if (i+10 == senntate) {
							//6_3_6�J�[�\���̕`��
							printf("�@��");
						}
						//�I���R�}���h�Ŗ����Ȃ�
						else {
							//6_3_8�S�p�X�y�[�X�̕`��
							printf("�@�@");
						}
						if (inv[j][i] == 4) {
							printf("�@ �ȂׂԂ��@�@�@�@HP%2d", inv[j][i]);
						}
						else if (inv[j][i] == 8) {
							printf(" �r���a�̂ӂ��@�@�@HP%2d", inv[j][i]);
						}
						else if (inv[j][i] == 12) {
							printf("�@ �r�̂ӂ��@�@�@�@HP%2d", inv[j][i]);
						}
						if (soubi2 == i) {
							printf("�@E");
						}
						printf("\n");
					}
				}
			}
			printf("\n   �@ �@�g�o�@�@�@�@��������\n\n");
			printf("   �@ �@HP:%d�@�@�@ attack:%d\n", player.maxhp, player.att);
		}
		//�O��̈ړ���ۑ�
		int stmae = 0;
		//����
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
			return;//�I��
			break;
		default://�g�p
			//�X�N���[���̎g�p
			if (!(senntaku % 2)) {
				if (inv[0][senntate] == 1) {
					printf("\n\n�@  �v���C���[�̓��[�v����");
					int px, py;
					GRP(&px, &py);
					player.x = px;
					player.y = py;
					_getch();
				}
				else if (inv[0][senntate] == 2) {
					printf("\n\n�@�@�@�@�@�@�@%d ��", player.hp);
					player.hp = player.maxhp;
					printf(" %d\n", player.hp);
					_getch();
				}
				inv[0][senntate] = 0;
			}
			//������
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
		//�ړ������R�ɑO��ړ�����������
		if ((stmae == 2)||(stmae == 1)) {
			//�X�N���[���������т�
			if (!(senntaku % 2)) {
				//�I�������[�v�Ƌ󂢂Ă�Ƃ�����X�L�b�v
				for (int i = 0; i < 9; i++) {
					//senntate�����[�v
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
					//senntate�����[�v
					senntate = (senntate + 18) % 18;
					//8�܂�
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
					//9����
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
//���G���f�B���O
void con() {
	//�����쐬
	{
		//�ǂŖ��߂�
		for (int y = 0; y < SCREEN_R*3; y++) {
			for (int x = 0; x < SCREEN_R*2; x++) {
				fieldend[y][x] = C_T_WALL;
			}
		}
		//���������
		for (int y = 5; y < SCREEN_R*3 -5; y++) {
			for (int x = 2; x < SCREEN_R*2-2; x++) {
				fieldend[y][x] = C_T_NONE;
			}
		}
		//�ʘH
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
	//�O��̍X�V������錾
	time_t lastC = clock();
	while (1) {
		//���݂̎�����錾
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
//���G�s���[�O
void epi() {
	int con = 0;
	int i = 0;
	int end = 30 + rand() % 5;
	//�����쐬
	{
		//�ǂŖ��߂�
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
		//�n�ʂ����
		for (int y = SCREEN_R; y < SCREEN_R * 3; y++) {
			for (int x = 0; x < SCREEN_R * 2; x++) {
				fieldend[y][x] = C_T_ROAD3;
			}
		}
		//��
		for (int y = SCREEN_R; y < SCREEN_R * 3; y++) {
			for (int x = SCREEN_R - 2; x < SCREEN_R + 3; x++) {
				fieldend[y][x] = C_T_NONE;
			}
		}
		//��
		for (int x = SCREEN_R - 2; x < SCREEN_R + 3; x++) {
			if ( x == SCREEN_R + 1) {
				continue;
			}
			fieldend[SCREEN_R + 2][x] = C_T_ROAD4;
		}
		//�Ŕ�
		fieldend[SCREEN_R + 3][SCREEN_R] = C_T_ROAD5;
		//�����g
		for (int y = SCREEN_R - 4; y < SCREEN_R; y++) {
			for (int x = SCREEN_R - 2; x < SCREEN_R + 3; x++) {
				fieldend[y][x] = C_T_ROAD6;
			}
		}
		//����
		for (int y = SCREEN_R - 3; y < SCREEN_R; y++) {
			for (int x = SCREEN_R - 1; x < SCREEN_R + 2; x++) {
				fieldend[y][x] = C_T_ROAD7;
			}
		}
	}
	//�O��̍X�V������錾
	time_t lastC = clock();
	while (1) {
		//���݂̎�����錾
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
				printf("�@�@�@�@�s�v�c�̃_���W����\n");
				for (int i = 0; i < SCREEN_R * 3 - 10; i++) {
					printf("\n");
				}
				//nowloading�̕\��
				{
					if (con % 4 == 0)
						printf("�@�@�@�@�@�@�@�@NowLoading");
					else if (con % 4 == 1)
						printf("�@�@�@�@�@�@�@�@NowLoading�D");
					else if (con % 4 == 2)
						printf("�@�@�@�@�@�@�@�@NowLoading�D�D");
					else if (con % 4 == 3)
						printf("�@�@�@�@�@�@�@�@NowLoading�D�D�D");
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
//���C���֐�
int main() {
	//����
	srand((unsigned int)time(NULL));
	//�^�[���̐錾
	int turn = 0;
	//�{�X�K�w
	boss = 3+rand() % 3;
start://�Q�[���J�n���x��
	;//��
	Sleep(INTERVAL);
	epi();
	//�o���l����̐錾
	player.ex = 3 + lv * 2;
	//�v���C���[�̃X�e�C�^�X�̐錾
	player.hp = player.maxhp = 15 + hpp+lv+soubihp;
	player.att = 4 + attp + lv+soubiatt;
	//�_���W��������
	generateF();
	while (1) {
		//�\��
		DS();
		int x = player.x, y = player.y;
		//�s���^�[������
		int g = 1;
		if (bossP) {
			g = 2;
		}
		//�����������Ă���Ȃ�&&�{�X�����Ȃ�
		if (!(turn % g)) {
			//�v���C���[�̑���
			switch (_getch()) {
			case'w'://6_11_38w�������ꂽ���ֈړ�
				y--;
				break;
			case's'://6_11_39s�������ꂽ���ֈړ�
				y++;
				break;
			case'a'://6_11_40a�������ꂽ���ֈړ�
				x--;
				break;
			case'd'://6_11_41d�������ꂽ���ֈړ�
				x++;
				break;
			case'q'://��q�������ꂽ��X�e�C�^�X��ʂֈړ�
				steitas();
				continue;
				break;
			case'e'://��e�������ꂽ��C���x���g���ֈړ�
				INVE();
				continue;
				break;
			}
		}
		//�����蔻�蕪��
		int g2 = -1;
		if (bossP){
			g2 = 1;
		}
		//�s��ɂ��閂���ɍU��
		if (((x == enemy.x) && (y == enemy.y)) &&
			(enemy.hp > 0)) {
			printf("�E�҂̍U���I\n");
			Sleep(INTERVAL);
			//�_���[�W�v�Z�i�Œ�latt/2�@�ō��latt*1.5
			int att = player.att / 2 + rand() % player.att;
			//�_���[�W����
			enemy.hp -= att;
			printf("����Lv%d��%d�̃_���[�W!", flo, att);
			Sleep(INTERVAL);
			_getch();
			//�G���|�ꂽ��
			if (enemy.hp <= 0) {
				DS();
				printf("����Lv%d��|�����I\n", flo);
				exnow += enemy.ex;
				//���o���l���オ������
				while (1) {
					if (player.ex <= exnow) {
						exnow = exnow - player.ex;
						//���̕K�v�o���l���X�V
						player.ex = 3 + lv * 2;
						lv++;
						point++;
						player.maxhp = 15 + hpp + lv + soubihp;
						player.att = 4 + attp + lv + soubiatt;
					}
					if (player.ex > exnow)break;
				}
				//���h���b�v����
				int syutugen = rand() % 100;
				if (syutugen <= R_BUKI) {
					//�����_���Ō�
					if (50 <= rand() % 100) {
						kenn.e = true;
						kenn.y = enemy.y;
						kenn.x = enemy.x;
						field[kenn.y][kenn.x] = C_T_E_2;
						//�A�C�e���̌���
						kenn.kouka = 3 + (rand() % 2) * 3;
					}
					//�����_���ŏ�
					else {
						tate.e = true;
						tate.y = enemy.y;
						tate.x = enemy.x;
						field[tate.y][tate.x] = C_T_E_3;
						//�A�C�e���̌���
						tate.kouka = 4 + (rand() % 3) * 4;
					}
				}
				Sleep(INTERVAL);
				_getch();
			}
		}
		//���s��ɂ��閂���ɍU��
		else if ((((x == bos.x) && (y == bos.y)) ||
			((x == bos.x - 1) && (y == bos.y)) ||
			((x == bos.x + 1) && (y == bos.y)) ||
			((x == bos.x) && (y == bos.y +g2))) &&
			(bos.hp > 0)) {
			if (!bossP) {
				printf("�E�҂̍U���I\n");
			}
			else {
				printf("�����̍U���I\n");
			}
			Sleep(INTERVAL);
			//�_���[�W�v�Z�i�Œ�latt/2�@�ō��latt*1.5
			int att = player.att / 2 + rand() % player.att;
			//�_���[�W����
			bos.hp -= att;
			if (!bossP) {
				printf("������%d�̃_���[�W!", att);
			}
			else {
				printf("�E�҂�%d�̃_���[�W!", att);
			}
			Sleep(INTERVAL);
			_getch();
			if (bos.hp <= 0) {
				if (!bossP) {
					DS();
					printf("�����̖� ������|�����I\n");
					Sleep(INTERVAL);
					//�������|�ꂽ�����o��
					field[bos.y][bos.x] = C_T_AMULET;
					exnow += bos.ex;
				}
				else {
					DS();
					printf("�����̖� �E�҂�ނ���\n");
					Sleep(INTERVAL);
					goto start;
				}
				//���o���l���オ������
				if (player.ex <= exnow) {
					exnow = exnow - player.ex;
					//���̕K�v�o���l���X�V
					player.ex = 3 + lv * 2;
					lv++;
					point++;
				}
				_getch();
			}
		}
		//�s��ɖ��������Ȃ���Έړ�
		else {
			//�s��̃Z���ʂ̍s��
			switch (field[y][x]) {
				//�n�ʂȂ�Έړ�
			case C_T_NONE:
				//�ړ�����m��
				player.x = x;
				player.y = y;
				//10�^�[���o�߂������
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
				//�ǂȂ�Γ����Ȃ�
			case C_T_WALL:
				break;
				//�K�i�Ȃ�΃}�b�v�X�V
			case C_T_STAIRS:
				//�K�w���Z
				flo++;
				//�V�����G���A
				generateF();
				break;
				//��Ȃ�N���A
			case C_T_AMULET:
				con();
				system("cls");
				bossP = true;
				bos.hp = bos.maxhp;
				//�I���
				goto start;
				break;
				//���A�C�e�����E��(�X�N���[��)
			case C_T_E_1:
				if (suku.e) {
					if (Isuu[0] >= 10) {
						DS();
						printf("�E�҂̓X�N���[�������O���Ă���");
					}
					else {
						inv[0][Isuu[0]] = suku.kouka;
						Isuu[0] += 1;
						suku.e = false;
						field[suku.y][suku.x] = C_T_NONE;
					}
				}
				DS();
				//�ړ�����m��
				player.x = x;
				player.y = y;
				//10�^�[���o�߂������
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
				//���A�C�e�����E��(��)
			case C_T_E_2:
				if (kenn.e) {
					if (Isuu[1] >= 10) {
						DS();
						printf("�E�҂͕�������O���Ă���");
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
				//�ړ�����m��
				player.x = x;
				player.y = y;
				//10�^�[���o�߂������
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
				//���A�C�e�����E��(��)
			case C_T_E_3:
				if (tate.e) {
					if (Isuu[2] >= 10) {
						DS();
						printf("�E�҂͖h������O���Ă���");
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
				//�ړ�����m��
				player.x = x;
				player.y = y;
				//10�^�[���o�߂������
				if ((turn % 10 == 0) && (player.hp < player.maxhp)) {
					player.hp++;
				}
				break;
			}
		}
		//�����������Ă���Ȃ�
		if (enemy.hp > 0) {
			//�����̂��镔���̒l���l��
			int room = getR(enemy.x, enemy.y);
			//�v���C���[�Ƃ̋������l��
			int distance = abs(player.x - enemy.x) + abs(player.y - enemy.y);
			//�ׂɃv���C���[��������
			if (distance == 1) {
				//�\���֐�
				DS();
				printf("����Lv%d�̍U���I\n", flo);
				Sleep(INTERVAL);
				//�_���[�W�v�Z�i�Œ�latt/2�@�ō��latt*1.5
				int att = enemy.att / 2 + rand() % enemy.att;
				//�_���[�W����
				player.hp -= att;
				printf("�E�҂�%d�̃_���[�W!", att);
				Sleep(INTERVAL);
				_getch();
				//�v���C���[���|�ꂽ��
				if (player.hp <= 0) {
					DS();
					printf("���{�����܂悤�����Ɖ����Ă��܂����c\n");
					printf("�f�`�l�d�@�n�u�d�q\n\a");
					Sleep(INTERVAL);
					_getch();
					//�I���
					return 0;
				}
			}
			//���������Ƀv���C���[�����ė���Ă�����
			else if (((room >= 0) && (room == getR(player.x, player.y)))
				|| (distance <= 10)) {
				//���W���ꎞ�ۑ�
				int x = enemy.x;
				int y = enemy.y;
				//�ړ����ʂ�ۑ�
				int xory = 0;
				//�v���C���[�̂���ق��ֈړ�
				//����Ă��鎲���ړ����
				if ((abs(x - player.x)) > (abs(y - player.y))) {
					if (x < player.x) { x++; xory = 1; }
					else if (x > player.x) { x--; xory = 1; }
				}
				else {
					if (y < player.y) { y++; xory = 2; }
					else if (y > player.y) { y--; xory = 2; }
				}
				//�ǂɂԂ�������Ⴄ���ňړ�
				if (field[y][x] == C_T_WALL) {
					//�O�������
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
				//�d�Ȃ�Ȃ���
				//�v���C���[�Əd�Ȃ�Ȃ� 
				if (((x == player.x) && (y == player.y)) ||
					//�{�X�Əd�Ȃ�Ȃ�
					((y == bos.y) && ((x == bos.x) || (x == bos.x + 1) || (x == bos.x - 1))) ||
					//�{�X�̓��Əd�Ȃ�Ȃ�
					((y == bos.y - 1) && (x == bos.x))) {
				}
				//�ړ��悪�ǂȂ�Ζ߂�
				else if (field[y][x] != C_T_WALL) {
					enemy.x = x;
					enemy.y = y;
				}
			}
		}
		//�s���^�[������
		int g3 = 2;
		if (bossP){
			g3 = 1;
		}
		//�����������Ă���Ȃ�&&�{�X�����Ȃ�
		if ((bos.hp > 0) && (flo >= boss) && !(turn % g3)) {
			//�v���C���[�Ƃ̋������l��
			int distance = abs(player.x - bos.x) + abs(player.y - bos.y);
			//�U���͈�
			int g = 3;
			if (bossP){
				g = 2;
			}
			//�ׂɃv���C���[��������
			if (distance <= g) {
				//�\���֐�
				DS();
				if (!bossP) {
					printf("�����̍U���I\n");
				}
				else {
					printf("�E�҂̍U���I\n");
				}
				Sleep(INTERVAL);
				//�_���[�W�v�Z�i�Œ�latt/2�@�ō��latt*1.5
				int att = bos.att / 2 + rand() % bos.att;
				//�_���[�W����
				player.hp -= att;
				if (!bossP) {
					printf("�E�҂�%d�̃_���[�W!", att);
				}
				else {
					printf("������%d�̃_���[�W!", att);
				}
				Sleep(INTERVAL);
				_getch();
				//�v���C���[���|�ꂽ��
					if (player.hp <= 0) {
						if (!bossP) {
							DS();
							printf("���{�����܂悤�����Ɖ����Ă��܂����c\n");
							printf("�f�`�l�d�@�n�u�d�q\n\a");
							Sleep(INTERVAL);
							_getch();
							//�I���
							return 0;
						}
						else {
							DS();
							printf("���E�҂͗͐s�����c\n");
							printf("�f�`�l�d�@�n�u�d�q\n\a");
							Sleep(INTERVAL);
							con();
							_getch();
							//�I���
							return 0;
						}
					}
			}
			//�����̈ړ�
			else {
				//���W���ꎞ�ۑ�
				int x = bos.x;
				int y = bos.y;
				//�ړ����ʂ�ۑ�
				int xory = 0;
				//�v���C���[�̂���ق��ֈړ�
				//����Ă��鎲���ړ����
				if ((abs(x - player.x)) > (abs(y - player.y))) {
					if (x < player.x) { x++; xory = 1; }
					else if (x > player.x) { x--; xory = 1; }
				}
				else {
					if (y < player.y) { y++; xory = 2; }
					else if (y > player.y) { y--; xory = 2; }
				}
				//�ǂɂԂ�������Ⴄ���ňړ�
				if (field[y][x] == C_T_WALL) {
					//�O�������
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
				//�v���C���[�Əd�Ȃ�Ȃ�
				if (((y == player.y) && ((x == player.x) || (x == player.x + 1) || (x == player.x - 1))) ||
					((y == player.y + 1) && (x == player.x)) ||
					//�����Əd�Ȃ�Ȃ�
					((y == enemy.y) && ((x == enemy.x) || (x == enemy.x + 1) || (x == enemy.x - 1))) ||
					//�����Əd�Ȃ�Ȃ�
					((y == enemy.y + 1) && (x == enemy.x))) {
				}
				//�ړ��悪�ǂȂ�Ζ߂�
				else if (field[y][x] != C_T_WALL) {
					bos.x = x;
					bos.y = y;
				}

			}
		}
		//�^�[���o��
		turn++;
	}
}
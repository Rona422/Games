//1�w�b�_�[�t�@�C�����C���N���[�h
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
//2�萔���`
//2_1�����̏���MP
#define SPELL_COST (3)
//3�񋓒萔���`
//3_1�����X�^�[
enum {
	MON_PLAYER,//3_1_1�v���C���[
	MON_SLIME, //3_1_2�X���C��
	MON_garuda,
	MON_BOSS,  //3_1_3�{�X
	MON_MAX    //3_1_4�����X�^�[�̎�ސ�
};
//3_2�L�����N�^�[�̎��
enum {
	CHA_PLAYER, //3_2_1�v���C���[
	CHA_MONSTER,//3_2_2�����X�^�[
	CHA_MAX     //3_2_3�L�����N�^�[�̎�ސ�
};
//3_3�R�}���h�̎��
enum {
	CMD_FIGHT,//3_3_1��������
	CMD_SPELL,//3_3_2�������
	CMD_RUN,  //3_3_3�ɂ���
	CMD_MAX,  //3_3_4
};
//4�\���̂�錾
//4_1�L�����N�^�[�̍\����
typedef struct {
	int hp;          //4_1_1HP
	int maxhp;       //4_1_2�ő�HP
	int mp;          //4_1_3MP
	int maxmp;       //4_1_4�ő�MP
	int attack;      //4_1_5�U����
	int def;
	char name[4*2+1];//4_1_6(�S�p4�����E�I�[����)
	char aa[256];    //4_1_7�A�X�L�[�A�[�g
	int command;     //4_1_8�R�}���h
	int target;      //4_1_9�U���Ώ�
}CHARATCTER;
//5�ϐ���錾
//5_1�����X�^�[�̃X�e�[�^�X�̔z��錾
CHARATCTER monsters[MON_MAX] = {
	//5_1_1�v���C���[�̏����l�̐ݒ�
	{
		100,        //5_1_2HP
		100,        //5_1_3�ő�HP 
		15,        //5_1_4MP
		999,        //5_1_5�ő�MP
		75,         //5_1_6�U����
		15,
		"�䂤����",//5_1_7���O
	},
	//5_1_8
	{
		3,	  	   //5_1_9HP
		3,		   //5_1_10�ő�HP
		0,		   //5_1_11MP
		0,		   //5_1_12�ő�MP
		10,         //5_1_13�U����
		0,
		"�X���C��",//5_1_14���O
		"�^���m���_\n"
		"�`�`�`�`�`�`"//5_1_15�A�X�L�[�A�[�g
	},
	//[��]
	{
		50,
		50,
		0,
		0,
		40,
		10,
		"�K���[�_",
		"�i�ƁE�ăm�j\n"
		"�`�`�`�`�`�`"	
	},
	//5_1_16
	{
		256,
		256,
		0,
		0,
		100,
		20,
		"�܂���",
		"�@�@�`x�@x�`\n"
		"(<��>�m�M�_<��>)"
	}
};
//5_2�L�����N�^�[�̔z��錾
CHARATCTER characters[CHA_MAX];
//5_3�R�}���h�̖��O�Ɋւ���z��錾
char commandnames[CMD_MAX][4 * 2 + 1] = {
	"��������",
	"�������",
	"�ɂ���"
};
//6�֐���錾
//6_1�Q�[���̏���������
void Init() {
	characters[CHA_PLAYER] = monsters[MON_PLAYER];
}
//6_2�퓬�V�[���̕`�揈��
void DrawBattle() {
	//6_2_1��ʃN���A
	system("cls");
	//6_2_2�v���C���[�̖��O�\��
	printf("%s\n", characters[CHA_PLAYER].name);
	//6-2-3�v���C���[�̃X�e�[�^�X��\��
	printf("�g�o:%d�^%d�l�o:%d�^%d\n",
			characters[CHA_PLAYER].hp,
			characters[CHA_PLAYER].maxhp,
			characters[CHA_PLAYER].mp,
			characters[CHA_PLAYER].maxmp);
	//6_2_4
	printf("\n");
	//6_2_5
	printf("%s",characters[CHA_MONSTER].aa);
	printf("(�g�o:%d�^%d)\n",
		characters[CHA_MONSTER].hp,
		characters[CHA_MONSTER].maxhp);
	//6_2_7
	printf("\n");
}
//6_3�R�}���h�I������
void SelectCMD() {
	//6_3_1�v���C���[�̃R�}���h��������
	characters[CHA_PLAYER].command = CMD_FIGHT;
	//6_3_2�R�}���h�����肳���܂Ń��[�v
	while (1) {
		//6_3_3�퓬�`��
		DrawBattle();
		//6_3_4�R�}���h�ꗗ
		for (int i = 0; i < CMD_MAX; i++){
			//6_3_5�I���R�}���h�Ȃ�
			if (i==characters[CHA_PLAYER].command){
				//6_3_6�J�[�\���̕`��
				printf("��");
			}
			//6_3_7�I���R�}���h�Ŗ����Ȃ�
			else{
				//6_3_8�S�p�X�y�[�X�̕`��
				printf("�@");
			}
			//6_3_9�R�}���h�̖��O�̕\��
			printf("%s\n", commandnames[i]);
		}
		//6_3_10�L�[�{�[�h�̓��͑҂�
		switch(_getch()) {
			case'w'://6_3_11���L�[�������ꂽ�ꍇ
				//6_3_12��̃R�}���h�ɐ؂�ւ�
				characters[CHA_PLAYER].command--;
				break;
			case's'://6_3_13���L�[�������ꂽ�ꍇ
				//6_3_14���̃R�}���h�ɐ؂�ւ�
				characters[CHA_PLAYER].command++;
				break;
			default://6_3_15��L�ȊO�̃L�[�������ꂽ�ꍇ
				return;//6_3_16�֐��𔲂���
		}
		//6_3_17�J�[�\�����㉺�Ƀ��[�v
		characters[CHA_PLAYER].command =
			(CMD_MAX+characters[CHA_PLAYER].command) % CMD_MAX;
	}
}
//6_4 �퓬����
//�����@_monster�����X�^�[��ނ��w��
void Battle(int _monster) {
	//6_4_1
	characters[CHA_MONSTER] = monsters[_monster];
	//6-4-2�v���C���[�̍U���Ώۂ������X�^�[�ɐݒ肷��
	characters[CHA_PLAYER].target = CHA_MONSTER;
	//6-4-3�����X�^�[�̍U���Ώۂ��v���C���[�ɐݒ肷��
	characters[CHA_MONSTER].target = CHA_PLAYER;
	//6_4_4
	DrawBattle();
	//6_4_5
	printf("%s���@�����ꂽ�I\n",characters[CHA_MONSTER].name);
	//6_4_6
	_getch();//�L�[�{�[�h���͑҂�
	int damage;
	//6_4_7�퓬�I���܂Ń��[�v
	while (1) {
		//6_4_8�R�}���h�I�������֐����Ăяo��
		SelectCMD();
		//6_4_9�L�����N�^�[�����[�v
		for (int i = 0; i < CHA_MAX; i++){
			DrawBattle();//6_4_10�퓬�`��̊֐�
			//6_4_11�I�����ꂽ�R�}���h�ŕ���
			switch (characters[i].command) {
				case CMD_FIGHT://�R�}���h�����������̏ꍇ
					//6_4_13�U�����郁�b�Z�[�W��\��
					printf("%s�́@��������", characters[i].name);
					characters[i].mp ++;
					//6_4_14
					_getch();//�L�[�{�[�h���͑҂�
					//6_4_15�G�ɗ^����_���[�W���v�Z����
					damage = 1 + rand() % ((characters[i].attack-characters[i].def) /2);
					//6_4_16�G�Ƀ_���[�W��^����
					characters[characters[i].target].hp -= damage;
					//6_4_17�G��HP�����̒l�ɂȂ����ꍇ
					if (characters[characters[i].target].hp < 0){
						//6_4_18HP��0�ɂ���
						characters[characters[i].target].hp = 0;
					}
					//6_4_19�퓬�`�ʏ����֐�
					DrawBattle();
					//6_4_20�_���[�W�̕\��
					printf("%s�Ɂ@%d�@�_���[�W�I\n",
						characters[characters[i].target].name,damage);
					_getch();
					break;
					//6_4_22�R�}���h���������̏ꍇ
				case CMD_SPELL:
					//6_4_23MP������邩����
					if (characters[i].mp< SPELL_COST){
						//6_4_24MP������Ȃ����b�Z�[�W��\��
						printf("�l�o���@����Ȃ��I");
						//6_4_25�L�[�{�[�h���͑҂�
						_getch();
						//6_4_26
						break;
					}
					//6_4_27MP�������
					characters[i].mp-= SPELL_COST;
					//6_4_28�퓬�`�揈���֐�
					DrawBattle();
					//6_4_29���������������b�Z�[�W��\��
					printf("%s�́@���@�ƂȂ����I\n", characters[i].name);
					//6_4_30�L�[�{�[�h���͑҂�
					_getch();
					//6_4_31HP����(�S��)
					characters[i].hp = characters[i].maxhp;
					//6_4_32�퓬�`�揈���֐�
					DrawBattle();
					//6_4_33�񕜃��b�Z�[�W��\��
					printf("%s�̂������@�����ӂ�����\n",characters[i].name);
					break;
					//6_4_35�R�}���h���ɂ���̏ꍇ
				case CMD_RUN:
					//6_4_36�ɂ������b�Z�[�W��\��
					printf("%s�́@�ɂ��������I",characters[i].name);
					//6_4_37�L�[�{�[�h���͑҂�
					_getch();
					//6_4_38�퓬�V�[���֐��I��
					return;
					break;
			}
			//6_4_39�U���Ώۂ�|�������𔻒肷��
			if (characters[characters[i].target].hp <= 0){
				//6_4_40
				switch (characters[i].target){
					//6_4_41�U���Ώۂ��v���C���[
					case CHA_PLAYER:
						//6_4_42�v���C���[���S�\��
						printf("%s�́@���������",characters[i].name);
						return;
						break;
					//6_4_43�U���Ώۂ������X�^�[
					case CHA_MONSTER:
						//6_4_44�A�X�L�[�A�[�g�̕\�����폜
						strcat_s(characters[characters[i].target].aa,"\n");
						//6_4_45
						DrawBattle();
						//6_4_46�����X�^�[��|�������b�Z�[�W��\��
						printf("%s���@���������I\n",
							characters[characters[i].target].name);
						return;
						break;
				}
				//6_4_47�L�[�{�[�h���͑҂�
				_getch();
				//6_4_48�퓬�V�[���֐��I��
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
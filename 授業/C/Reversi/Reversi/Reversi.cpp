//1�w�b�_�[
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<time.h>  //1_3
#include<conio.h> //1_4
#include<vector>  //1_5
//2�萔
#define BOARD_WIDTH (8)//2_1�Ֆʂ̕�
#define BOARD_HRIGHT (8)//2_2�Ֆʂ̍���
//3�񋓑�
//3_1�^�[���̎�ނ��`����
enum {
	TURN_BLACK,//3_1_1��
	TURN_WHITE,//3_1_2��
	TURN_NONE, //3_1_3�Ȃ�
	TURN_MAX   //3_1_4�^�[����
};
//3_2�����̎��
enum {
	//3_2_1~9��,����,��,��,�E��,�E,�E��,�����̐�
	D_U, D_U_L, D_L, D_D_L, D_D, D_D_R, D_R, D_U_R, D_MAX
};
//3_3�Q�[�����[�h�̎��
enum {
	//3_3_1~3CPU�Ƒΐ�,�l�ԓ��m�̑ΐ�,���[�h��
	M_1P,M_2P,M_WATCH,M_MAX
};
//4�\����
//4_1�x�N�g���\����
typedef struct{
	int x, y;//4_1_1���W
}VEC2;
//5_1
const char* diskAA[TURN_MAX] = {
	"��",
	"��",
	"�E"
};
//5_2�ϐ�
const char* turnN[] = {
	"��",
	"��"
};
//5_3���[�h�̖��O
const char* modeN[] = {
	"�P�o �f�`�l�d",
	"�Q�o �f�`�l�d",
	"�v�`�s�b�g"
};
//5_4�����̍��W�z��
VEC2 directions[D_MAX] = {
	//3_2_1~9��,����,��,��,�E��,�E,�E��
	{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}
};
//5_5�Ֆʂ̏��
int board[BOARD_HRIGHT][BOARD_WIDTH];
VEC2 cursorP;//5_6�J�[�\���̍��W�̐錾
int turn;//5_7���݂̃^�[��
//5_8���݂̃v���C���[�h
int mode;
//5_9���݂̃^�[�����v���C���[�̂��̂�
bool isPlayer[TURN_MAX];
//6�֐�
//6_1�x�N�g�������Z���鏈��
VEC2 VecAbb(VEC2 _v0,VEC2 _v1){
	//6_1_2���Z�����x�N�g����Ԃ�
	return{
		_v0.x + _v1.x,
		_v0.y + _v1.y
	};
}
//6_2�΂��u���邩�ǂ����𔻒肷�鏈��
bool CCP(int _color,VEC2 _position,bool _turnOver = false) {
	//6_2_1�u���邩�ǂ����̃t���O
	bool canPlace = false;
	//6_2_2�Ώۂ̍��W�ɐ΂��u����Ă��Ȃ����𔻒�
	if (board[_position.y][_position.x]!=TURN_NONE){
		//6_2_3�΂��u���Ă�����false
		return false;
	}
	//6_2_4����̐΂̐F�̐錾
	int opponent = _color ^ 1;
	//6_2_5���ׂĂ̕������J��Ԃ�
	for (int i = 0; i < D_MAX; i++){
		//6_2_6���݃`�F�b�N���̍��W��錾
		VEC2 currentP = _position;
		//6_2_7�אڂ���}�X�Ɉړ�
		currentP = VecAbb(currentP,directions[i]);
		//6_2_8����̐΂łȂ�������
		if (board[currentP.y][currentP.x]!=opponent){
			//6_2_9����̈ӎv�łȂ��{�A���̗אڂ�
			continue;
		}
		//6_2_10�������[�v
		while (1){
			//6_2_11�אڂ���}�X�Ɉړ�
			currentP = VecAbb(currentP, directions[i]);
			//6_2_12�`�F�b�N����}�X���Ֆʓ��łȂ�������
			if ((currentP.x<0)||(currentP.x>= BOARD_WIDTH)||
				(currentP.y < 0)||(currentP.y >= BOARD_HRIGHT)){
				//6_2_13�Ֆʂ̊O�ɏo�Ă��܂����猻�݂̃`�F�b�N�𔲂���
				break;
			}
			//6_2_14�`�F�b�N����}�X�ɐ΂��Ȃ�������
			if (board[currentP.y][currentP.x] == TURN_NONE) {
				//6_2_15�΂��Ȃ���Ό��݂̃`�F�b�N�𔲂���
				break;
			}
			//6_2_16�`�F�b�N����}�X�Ɏ����̐΂������
			if (board[currentP.y][currentP.x] == _color) {
				//6_2_17�΂�u���邱�Ƃ��m�肷��
				canPlace = true;
			}
			//6_2_18���]����
			if (_turnOver){
				//6_2_19�Ђ�����Ԃ����W
				VEC2 reverseP = _position;
				//6_2_20�אڂ̃}�X�Ɉړ�
				reverseP = VecAbb(reverseP,directions[i]);
				//6_2_21���݂̃^�[���̐΂��������܂ŌJ��Ԃ�
				do{
					//6_2_22����̐΂��Ђ�����Ԃ�
					board[reverseP.y][reverseP.x] = _color;
					//6_2_23�אڂ̃}�X�Ɉړ�
					reverseP = VecAbb(reverseP, directions[i]);
				} while (board[reverseP.y][reverseP.x]!=_color);
			}
		}
	}
	//6_2_24�t���O��Ԃ�
	return canPlace;
}
//6_3�Ֆʏ�ɐ΂�u����}�X�����邩�ǂ������肷�鏈��
bool CCPA(int _color) {
	//6_3_1�Ֆʂ̍s�����J��Ԃ�
	for (int y = 0;y< BOARD_HRIGHT; y++){
		//6_3_2�Ֆʂ̗񕪂��J��Ԃ�
		for (int x = 0;x<BOARD_WIDTH; x++){
			//6_3_3���肷����W
			VEC2 position = { x,y };
			//6_3_4�Ώۂ̐΂ɒu���邩�ǂ�������
			if (CCP(_color,position)){
				//6_3_5
				return true;
			}
		}
	}
	//6_3_3
	return false;
}
//6_4�C�ӂ̐΂̐��𐔂��鏈��
int GDCount(int _color) {
	//6_4_1�������t�̐���ێ�����ϐ�
	int count = 0;
	//6_4_2�Ֆʂ̂��ׂĂ̗񕪌J��Ԃ�
	for (int y = 0; y < BOARD_HRIGHT; y++) {
		//6_4_3�Ֆʂ̂��ׂĂ̍s���J��Ԃ�
		for (int x = 0; x < BOARD_WIDTH; x++) {
			//6_4_4�Ώۂ̐΂����邩�ǂ����𔻒�
			if (board[y][x] == _color) {
				//6_4_5�΂̐������Z����
				count++;
			}
		}
	}
	//6_4_6�������΂̐���Ԃ�
	return count;
}
//6_5�`�揈��
void DS() {
	//6_5_1��ʃN���A
	system("cls");
	//6_5_2�Ֆʂ̂��ׂĂ̗񕪌J��Ԃ�
	for (int y = 0; y < BOARD_HRIGHT; y++) {
		//6_5_3�Ֆʂ̂��ׂĂ̍s���J��Ԃ�
		for (int x = 0; x < BOARD_WIDTH; x++) {
			//6_5_4�΂̕`��
			printf("%s", diskAA[board[y][x]]);
		}
		//6_5_5�v���C���[�������ꍇ
		if (isPlayer[turn]) {
			//6_5_6�Ώۂ̍s���J�[�\���Ɠ����s������
			if (y == cursorP.y) {
				printf("��");//6_5_7�J�[�\��(�s)��`��
			}
			printf("�@");
		}
		//6_5_8���s
		printf("\n");
	}
	//6_5_9�v���C���[�������ꍇ
	if (isPlayer[turn]) {
		//6_5_10�Ֆʂ̂��ׂĂ̍s���J��Ԃ�
		for (int x = 0; x < BOARD_WIDTH; x++) {
			//6_5_11�Ώۂ̗񂪃J�[�\���Ɠ����񂩔���
			if (x == cursorP.x) {
				printf("��");//6_5_12�J�[�\��(��)��`��
			}
			else {
				printf("�@");//6_5_13�S�p�X�y�[�X��`��
			}
		}
	}
	//6_5_14���s
	printf("\n");
	//6_5_15�������������̔���
	if (turn!=TURN_NONE) {
		//6_5_16�^�[���\��
		printf("%s�̃^�[���ł�\n", turnN[turn]);
	}
	//6_5_17�����������ꍇ
	else{
		//6_5_18�����΂̐����J�E���g
		int blackC =GDCount(TURN_BLACK);
		//6_5_19�����΂̐����J�E���g
		int whiteC = GDCount(TURN_WHITE);
		//6_5_20���҂�ێ�����ϐ�
		int winner;
		//6_5_21���҂𔻒�
		if (blackC > whiteC) {//6_5_22�������������ꍇ
			winner = TURN_BLACK;//6_5_23
		}
		else if (whiteC>blackC){//6_5_24�������������ꍇ
			winner = TURN_WHITE;//6_5_25
		}
		else{//6_5_26�������̏ꍇ
			winner = TURN_NONE;//6_5_27
		}
		//6_5_28���҂̐΂̐���\������
		printf("%s%d---%s%d",turnN[TURN_BLACK],GDCount(TURN_BLACK),
							 turnN[TURN_WHITE], GDCount(TURN_WHITE));
		//6_5_29�����������ǂ�������
		if (winner == TURN_NONE){
			printf("��������\n");
		}
		else {
			printf("%s�̏���", turnN[winner]);
		}
		_getch();
	}
}
//6_6���[�h�I������
void SM() {
	//6_6_1�Q�[�����[�h�̏�����
	mode = M_1P;
	//6_6_2�������[�v
	while (1) {
		//6_6_3��ʃN���A
		system("cls");
		printf("���[�h���@�I������\n��������\n");//6_6_4
		printf("\n\n");//6_6_5
		//6_6_6���[�h�����J��Ԃ�
		for (int i = 0; i < M_MAX; i++){
			printf("%s�@",(i==mode)?"��":"�@");//6_6_7
			printf("%s\n",modeN[i]);//6_6_8
			printf("\n");//6_6_9
		}
		//6_6_10����
		switch(_getch()){
		case'w'://6_6_11w�̏ꍇ
			mode--;//6_6_12�O�̃��[�h�ɐ؂�ւ�
			break;
		case's'://6_6_13s�̏ꍇ
			mode++;//6_6_14���̃��[�h�ɐ؂�ւ�
			break;
		default://6_6_15
			//6_6_16���[�h�ł̕���
			switch (mode) {
				//6_6_17�b�o�t�Ƒΐ탂�[�h
				case M_1P:
					//6_6_18�����v���C���[
					isPlayer[TURN_BLACK] = true;
					//6_6_19�����b�o�t
					isPlayer[TURN_WHITE] = false;
					break;
				//6_6_20�l�ԓ��m�ΐ탂�[�h
				case M_2P:
					//6_6_21�����v���C���[
					isPlayer[TURN_BLACK] = isPlayer[TURN_WHITE] = true;
					break;
				//6_6_22CPU�����̑ΐ�
				case M_WATCH:
					//6_6_23���҂�CPU�ɂ���
					isPlayer[TURN_BLACK] = isPlayer[TURN_WHITE] = false;
			}
				return;//6_6_24���[�h�I���𔲂���
		}
		//6_6_25�J�[�\�����㉺�Ƀ��[�v
		mode = (M_MAX + mode) % M_MAX;
	}
}
//6_7�Q�[����������
void Init() {
	//6_7_1�Ֆʂ̂��ׂĂ̗񕪌J��Ԃ�
	for (int y = 0; y < BOARD_HRIGHT; y++){
		//6_7_2�Ֆʂ̂��ׂĂ̍s���J��Ԃ�
		for (int x = 0; x < BOARD_WIDTH; x++){
			//6_7_3�Ώۃ}�X��΂��u����Ă��Ȃ���Ԃɂ���
			board[y][x] = TURN_NONE;
		}
	}
	//6_7_4�Ֆʒ����̉E��ƍ����ɍ����΂�u��
	board[4][3] = board[3][4] = TURN_BLACK;
	//6_7_5�Ֆʒ����̉E���ƍ���ɍ����΂�u��
	board[3][3] = board[4][4] = TURN_WHITE;
	//6_7_6
	turn = TURN_BLACK;
	//6_7_7�J�[�\�����W�̏�����
	cursorP = {3,3};
	//6_7_8�`�揈�����Ăяo��
	DS();
}
//6_8�΂�u���}�X��I�����鏈��
VEC2 InputP() {
	//6_8_1�I������܂Ŗ������[�v
	while (1) {
		//6_5_2��ʂ̕`��
		DS();
		//6_5_3�L�[�{�[�h����
		switch (_getch()) {
		case 'w'://6_8_4w�����͂��ꂽ�ꍇ
			cursorP.y--;//6_8_5�J�[�\������Ɉړ�
			break;
		case 's'://6_8_6s�����͂��ꂽ�ꍇ
			cursorP.y++;//6_8_7�J�[�\�������Ɉړ�
			break;
		case 'a'://6_8_8a�����͂��ꂽ�ꍇ
			cursorP.x--;//6_8_9�J�[�\�������Ɉړ�
			break;
		case 'd'://6_8_10d�����͂��ꂽ�ꍇ
			cursorP.x++;//6_8_11�J�[�\�����E�Ɉړ�
			break;
		default://6_5_12��L�ȊO�̃L�[�������ꂽ�ꍇ
			if (CCP(turn,cursorP)) {
				return cursorP;;//6_5_13�J�[�\���̍��W��Ԃ�
			}
			else {
				//6_8_16�u���Ȃ��ƕ\��
				printf("�����ɂ͂����܂���");
				//6_8_17�L�[�{�[�h���͑҂�
				_getch();
			}
			break;
		}
		//6_8_18�J�[�\�������E�Ƀ��[�v
		cursorP.x = (BOARD_WIDTH + cursorP.x)% BOARD_WIDTH;
		//6_8_19�J�[�\�����㉺�Ƀ��[�v
		cursorP.y = (BOARD_HRIGHT + cursorP.y) % BOARD_HRIGHT;
	}
}
//6_9���C���֐�
int main() {
	srand((unsigned int)time(NULL));//6_9_1
start://6_9_2�J�n���x��
	;//6_9_3
	SM();//6_9_4���[�h�I��
	//6_9_5���������鏈�����Ăяo��
	Init();
	//6_9_6���[�v
	while (1) {
		//6_9_7�u����}�X���Ȃ����ǂ�������
		if (!CCPA(turn)){
			//6_9_8�^�[���؂�ւ�
			turn ^= 1;
			//6_9_9�u����}�X���Ȃ����ǂ�������
			if (!CCPA(turn)){
				//6_9_10����
				turn = TURN_NONE;
				//6_9_11��ʕ`��
				DS();
				//6_9_12�L�[�{�[�h���͑҂�
				_getch;
				goto start;//6_9_13�J�n���x���ɃW�����v
			}
			//6_9_14����ɒu����}�X�������
			else {
				//6_9_15����̃^�[����
				continue;
			}
		}
		//6_9_16�΂�u���}�X��錾
		VEC2 plaseP;
		//6_9_17
		if (isPlayer[turn]) {
			//6_9_18�΂�u���}�X��I������֐����Ăяo��
			plaseP = InputP();

			_getch();
		}
		//6_9_19�b�o�t�������ꍇ
		else {
			//6_9_20��ʕ`��
			DS();
			//6_9_21�L�[�{�[�h���͑҂�
			_getch();
			//6_9_22�u������W��ێ�����x�N�^�[
			std::vector<VEC2>positions;
			//6_9_23�Ֆʂ̂��ׂĂ̗񕪌J��Ԃ�
			for (int y = 0; y < BOARD_HRIGHT; y++) {
				//6_9_24�Ֆʂ̂��ׂĂ̍s���J��Ԃ�
				for (int x = 0; x < BOARD_WIDTH; x++) {
					//6_9_25
					VEC2 position = { x,y };
					//6_9_26�Ώۂ̍��W�ɐ΂�u���邩����
					if (CCP(turn,position)){
						//6_9_27���W���X�g�ɑΏۂ̍��W��ǉ�
						positions.push_back(position);
					}
				}
			}
			//6_9_28�u����ꏊ�������_���Ɏ擾
			plaseP = positions[rand()%positions.size()];
		}
		//6_9_29�΂��Ђ�����Ԃ�
		CCP(turn,plaseP,true);
		//6_9_30���݂̃^�[���̐΂�u��
		board[plaseP.y][plaseP.x] = turn;
		//6_9_31�^�[����؂�ւ�
		turn ^= 1;
	}
}
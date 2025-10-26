//1�w�b�_�[
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
//2�萔
#define FIELD_WIDTH (16)   //2_1�t�B�[���h�̕�
#define FIELD_HEIGHT (16)  //2_2�t�B�[���h�̍���
#define FPS (1)           //2_3��b�l�̍X�V�񐔂��`����
#define INTERVAL (100/FPS)//2_4�X�V�Ԋu(�~���b)
//3�ϐ�
//3_1�t�B�[���h�̐錾
//bool:true(1)/false(0)�̌^
bool field[FIELD_WIDTH][FIELD_HEIGHT] = {
	/*{0,1,1,1},
	{0,1,0,1},
	{0,0,1,1},
	{1,1,1,0}*/
};
//4�֐�
//4_1�`�揈��
void DrowField() {
	//4_1_1��ʃN���A
	system("cls");
	//4_1_2���ׂĂ̍s���J��Ԃ�
	for (int i = 0; i < FIELD_HEIGHT; i++){
		//4_1_3���ׂĂ̗񕪌J��Ԃ�
		for (int j = 0; j < FIELD_WIDTH; j++){
			//4_1_4�Z���������Ă���ꍇ�u���v�U�ł���ꍇ�u�@�v
			printf("%s", field[i][j] ? "��" : "�@"); 
		}
		//4_1_5��s�`�悷�邽�тɉ��s
		printf("\n");
	}
}
//4_2�Ώۂ̃Z���Ɨאڂ��鐶�̃Z���̐����擾����֐�
int GCC(int _i, int _j) {
	//4_2_1���̃Z���𐔂���ϐ�
	int cnt = 0;
	//4_2_2�Ώۂ̃Z���̏㉺1�}�X���J��Ԃ�
	for (int j = _j-1; j <=_j+1; j++){
		//4_2_3�͈͓����ǂ�������
		/*if ((j < 0) || (j >= FIELD_HEIGHT))
			continue;//4_2_4�͈͊O�Ȃ̂Ŏ���*/
		//4_2_5�㉺�Ƀ��[�v���������W
		int roopy = (FIELD_HEIGHT + j) % FIELD_HEIGHT;
		//4_2_6�Ώۂ̃Z���̍��E1�}�X���J��Ԃ�
		for (int i = _i + -1; i <=_i+1; i++){
			//4_2_7�͈͓����ǂ�������
			/*if ((i< 0) || (i >= FIELD_WIDTH))
				continue;//4_2_8�͈͊O�Ȃ̂Ŏ���*/
			//4_2_9�㉺�Ƀ��[�v���������W
			int roopx = (FIELD_WIDTH + i) % FIELD_WIDTH;
			//4_2_10
			if ((roopx==_i)&&(roopy==_j)){
				continue;//4_2_11�Ώۂ̍��W���X�L�b�v
			}
			//4_2_12���̃Z�����J�E���g
			cnt += field[roopy][roopx];
		}
	}
	//4_2_13���̃Z���̐���Ԃ�
	return cnt;
}
//4_3�V�~�����[�V��������
void SS() {
	//4_3_1���̐���̃t�B�[���h
	bool nextF[FIELD_WIDTH][FIELD_HEIGHT] = {};
	//4_3_2���ׂĂ̍s���J��Ԃ�
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		//4_3_3���ׂĂ̗񕪌J��Ԃ�
		for (int j = 0; j < FIELD_WIDTH; j++) {
			//4_3_4�Ώۂ̃Z���Ɨאڂ��鐶�̃Z�����J�E���g
			int livingCC = GCC(j, i);
			//4_3_5�����Z����1�ȉ��̏ꍇ
			if (livingCC <= 1){
				//4_3_6�Z�������S��Ԃɂ���
				nextF[i][j] = false;
			}
			//4_3_7�����Z����2�������ꍇ
			else if (livingCC == 2){
				//4_3_8�Z��������ێ�
				nextF[i][j] = field[i][j];
			}
			//4_3_9�����Z����3�������ꍇ
			else if (livingCC == 3) {
				//4_3_10�Z���𐶑���Ԃɂ���
				nextF[i][j] = true;
			}
			//4_3_11����ȊO(4�ȏ�)
			else{
				//4_3_12�Z�������S��Ԃɂ���
				nextF[i][j] = false;
			}
		}
	}
	//4_3_13���̐�������݂̐���փR�s�[�R�s�[
	//memcpy(�R�s�[��,�R�s�[��,�T�C�Y)
	memcpy(field,nextF,sizeof(field));
}
//4_4�p�^�[�����t�B�[���h�ɃR�s�[���鏈��
void PatternT(int _destx, int _desty, int _srcw, int _srch, bool* _pp) {
//�R�s�[��̌��_�̍��WX,Y,�������ރp�^�[���̃T�C�Y�̕�,����,�f�[�^�̃A�h���X
	//4_4_1�p�^�[�����̍s���̌J��Ԃ�
	for (int y = 0; y < _srcw; y++){
		//4_4_1�p�^�[�����̗񕪂̌J��Ԃ�
		for (int x = 0; x < _srch; x++){
			//4_4_3�p�^�[�����t�B�[���h�ɃR�s�[
			field[_desty + y][_destx + x] = _pp[y*_srcw+x];
		}
	}
}
//4_5���C���֐�
int main() {
	//4_5_1�p�^�[���̕�
	const int patternw = 15;
	//4_5_2�p�^�[���̍���
	const int patternh = 15;
	//4_5_3�p�^�[����錾
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
	//4_5_4�p�^�[�����t�B�[���h�̒��S�ɃR�s�[
	PatternT(FIELD_WIDTH / 2 - patternw / 2,
		FIELD_HEIGHT / 2 - patternh / 2,
		patternw, patternh, (bool*)pattern);
	//4_5_5�O��̌o�ߎ��Ԃ�ݒ�
	clock_t lastClock = clock();
	//4_5_6
	while (1){
		//4_5_7���݂̌o�ߎ��Ԃ�ݒ�
		clock_t newClock = clock();
		//4_5_8�O��̌o�ߎ��Ԃ���A�ҋ@���Ԃ��o�߂��Ă��Ȃ����
		if (newClock<lastClock+INTERVAL){
			//4_5_9���̃��[�v��
			continue;
		}
		//4_5_10�O��̌o�ߎ��Ԃ��A���݂̌o�ߎ��ԂōX�V����
		lastClock = newClock;
		//4_5_11�`�揈�����Ăяo��	
		DrowField();
		//4_5_12�L�[�{�[�h���͑҂�
		//_getch();
		//4_5_13�V�~�����[�V��������
		SS();
	}
}
//1�w�b�_�[
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
//2�萔
#define F_WIDTH (12)       //2_1�t�B�[���h�̕�
#define F_HEIGHT (18)      //2_2�t�B�[���h�̍���
#define B_WIDTH_MAX (4)    //2_3�u���b�N�̍ő啝
#define B_HEIGHT_MAX (4)   //2_4�u���b�N�̍ő卂��
#define FPS3 (1)            //2_5��b������̕`��p�x���`
#define INTERVAL3 (1000/FPS3)//2_6�`��Ԋu���`(�~���b)
//3�񋓑�
//3_1�u���b�N�̎��
enum {
	B_NONE,//3_1_1�u���b�N�Ȃ�
	B_HARD,//3_1_2�����Ȃ��u���b�N
    B_SOFT,//3_1_3������u���b�N
    B_FALL,//3_1_4�����u���b�N
	B_MAX  //3_1_5�u���b�N�̎�ސ�
};
//3_2�����u���b�N�̎�ނ̎��
enum {
    B_S_I, //3_2_1I�^
    B_S_L, //3_2_2L�^
    B_S_T,
    B_S_O,
    B_S_Z,
    B_S_S,
    B_S_MAX//3_2_3�����u���b�N�̎�ސ�
};
//4�\����
//4_1�����u���b�N�̌`��̍\���̂�錾����
typedef struct {
    int size;//4_1_1���ƍ���
    bool patterm[B_HEIGHT_MAX][B_WIDTH_MAX];//4_1_2�`��
}BS;
//4_2�����u���b�N�̍\���̂�錾����
typedef struct {
    int x, y;//4_2_1���W
    BS shape;//4_2_2�`��
}B;
//5�ϐ�
//5_1�����u���b�N�̌`���錾����
const BS bS[B_S_MAX] = {
    //5_1_1B_S_I I�^
    {
        4,//5_1_2int size ���ƍ���
        //5_1_3bool pattern[B_HEIGHT_MAX][B_WIDTH_MAX] �`��
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
        }
    },
    //5_1_4B_S_L L�^
    {
        3,//5_1_5int size ���ƍ���
        //5_1_6bool pattern[B_HEIGHT_MAX][B_WIDTH_MAX] �`��
        {
            {1,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,0,0,0},
        }
    },
    {
       3,
       {
           {1,0,0,0},
           {1,1,0,0},
           {1,0,0,0},
           {0,0,0,0},
       }
    },
    {
       2,
       {
           {1,1,0,0},
           {1,1,0,0},
           {0,0,0,0},
           {0,0,0,0},
       }
    },
    {
       3,
       {
           {0,1,0,0},
           {1,1,0,0},
           {1,0,0,0},
           {0,0,0,0},
       }
    },
    {
       3,
       {
           {1,0,0,0},
           {1,1,0,0},
           {0,1,0,0},
           {0,0,0,0},
       }
    },
};
//5_2�t�B�[���h��錾����
int field[F_HEIGHT][F_WIDTH];
//5_3�t�B�[���h�̏�����Ԃ�錾����
int defaultfield[F_HEIGHT][F_WIDTH]{
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
};
//5_4�����u���b�N��錾
B block;
int con = 0;
//6�֐�
//6_1�����u���b�N�ƃt�B�[���h�̓����蔻����s���֐�
bool BIF() {
    //6_1_1�����u���b�N�̍s������
    for (int y = 0; y < block.shape.size; y++) {
        //6_1_2�����u���b�N�̗񕪔���
        for (int x = 0; x < block.shape.size; x++) {
            //6_1_3�Ώۂ̃}�X�Ƀu���b�N�����邩�ǂ����𔻒�
            if (block.shape.patterm[y][x]){
                //6_1_4�u���b�N�̃t�B�[���h��̗��錾����
                int globalX = block.x + x;
                //6_1_5�u���b�N�̃t�B�[���h��̍s��錾����
                int globalY = block.y + y;
                //6_1_6�u���b�N�ƃt�B�[���h�̓����蔻��
                if ((globalX<0)||(globalX>=F_WIDTH)||//�񂪍��Oor�E�O���ǂ���
                    (globalY<0)||(globalY>=F_HEIGHT)||//�s����Oor���O���ǂ���
                    //�t�B�[���h��Ƀu���b�N�����邩�ǂ���
                    (field[globalY][globalX]!=B_NONE)
                    ){
                    //6_1_7���������Ƃ������ʂ�Ԃ�
                    return true;
                }
            }
        }
    }
    //6_1_8������Ȃ��������ʂ�Ԃ�
    return false;
}
//6_2��������s�̃u���b�N���폜����֐�
void EraseL() {
    //6_2_1���ׂĂ̍s�𔽕�
    for (int y = 0; y < F_HEIGHT; y++) {
        //6_2_2���̍s������������ǂ����̃t���O��錾
        bool completed = true;
        //6_2_3���ׂĂ̗�𔽕�
        for (int x = 0; x < F_WIDTH; x++) {
            //6_2_4�Ώۂ̃}�X�Ƀu���b�N���Ȃ����ǂ�������
            if (field[y][x]==B_NONE){
                //6_2_5�����Ȃ�����
                completed = false;
                //6_2_6���̍s�̃`�F�b�N�𔲂���
                break;
            }
        }
        //6_2_7���̍s������������ǂ�������
        if (completed){
            con++;
            //6_2_8�Ώۂ̗�𔽕�
            for (int x = 0; x < F_WIDTH; x++) {
                //6_2_9�Ώۂ̃}�X��������u���b�N�Ȃ�
                if (field[y][x]==B_SOFT){
                    //6_2_10�Ώۂ̃}�X�̃u���b�N������
                    field[y][x] = B_NONE;
                }
            }
            //6_2_11���ׂĂ̗�𔽕�
            for (int x = 0; x < F_WIDTH; x++) {
                //6_2_12�������s����擪�̍s�܂Ŕ���
                for (int y2 = y; y2 >= 0; y2--){
                    //6_2_13�����Ȃ��u���b�N�����������甽���I��
                    if (field[y2][x]==B_HARD){
                        break;
                    }
                    //6_2_14�擪�̍s������
                    if (y2==0){
                        //6_2_15�u���b�N������
                        field[y2][x] = B_NONE;
                    }
                    //6_2_16�擪�̍s�łȂ����
                    else {
                        //6_2_17��̃}�X�������Ȃ��u���b�N�łȂ�������
                        if (field[y2-1][x]!=B_HARD){
                            //6_2_18��̃}�X�����̃}�X�ɃR�s�[
                            field[y2][x] = field[y2 - 1][x];
                        }
                    }
                }
            }
        }
    }
}
//6_3�`�揈��
void DS() {
    //6_3_1��ʃo�b�t�@�[��錾
    int screen[F_HEIGHT][F_WIDTH];
    //6_3_2�t�B�[���h����ʃo�b�t�@�[�ɃR�s�[
    memcpy(screen,field,sizeof field);
    //6_3_3�t�B�[���h�̍s������
    for (int y = 0; y < B_HEIGHT_MAX; y++){
        //6_3_4�t�B�[���h�̗񕪔���
        for (int x = 0; x < B_WIDTH_MAX; x++){
            //6_3_5�u���b�N�����邩�ǂ����𔻒�
            if (block.shape.patterm[y][x]){
                //6_3_6��ʃo�b�t�@�[�ɗ����u���b�N����������
                screen[block.y + y][block.x + x] = B_FALL;
            }
        }
    }
    //6_3_7��ʃN���A
    system("cls");
    printf("�X�R�A:%d\n", con*100);
    //6_3_8�t�B�[���h���ׂĂ̍s�𔽕�����
    for (int y = 0; y < F_HEIGHT; y++){
        //6_3_9�t�B�[���h���ׂĂ̗�𔽕�����
        for (int x = 0; x < F_WIDTH; x++){
            //6_3_10�u���b�N�̎�ނŕ��򂷂�
            switch (screen[y][x]) {
            case B_NONE://6_3_11�u���b�N�Ȃ�
                printf("�@");
                break;
            case B_HARD://6_3_12�����Ȃ��u���b�N
                printf("��");
                break;
            case B_SOFT://6_3_13������u���b�N
                printf("��");
                break;
            case B_FALL://6_3_14�����u���b�N
                printf("��");
                break;
            }
        }
        //6_3_15���s
        printf("\n");
    }
}
//6_4�����u���b�N����]������֐�
void RB() {
    //6_4_1��]��̃u���b�N��錾
    B rB = block;
    //6_4_2�����u���b�N�̍s������
    for (int y = 0; y < block.shape.size; y++){
        //6_4_3�����u���b�N�̗񕪔���
        for (int x = 0; x < block.shape.size; x++) {
            //6_4_4��]��̃u���b�N�̌`����쐬
            rB.shape.patterm[block.shape.size - 1 - x][y] =
            block.shape.patterm[y][x];
        }
    }
    //6_4_5��]��̃u���b�N��K�p
    block = rB;
}
//6_5�����u���b�N�̏������֐�
void InitB() {
    //6_5_1�����u���b�N�̌`��������_���ɐݒ肷��
    block.shape = bS[rand()%B_S_MAX];
    //6_5_2�����u���b�N�̗�𒆐S�ɂ���
    block.x = F_WIDTH / 2 - block.shape.size / 2;
    //6_5_3�����u���b�N�̍s��擪��
    block.y = 0;
    //6_5_4�����u���b�N����]������񐔂�錾����
    int rC = rand() % 4;
    //6_5_5�����u���b�N����]������񐔂�����������
    for (int i = 0; i < rC; i++){
        //6_5_6�����u���b�N����]������
        RB();
    }
}
//6_6���������鏈��
void Init() {
    //6_6_1�t�B�[���h�ɏ�����Ԃ��R�s�[����
    memcpy(field,defaultfield,sizeof field);
    //6_2_2�u���b�N������������֐����Ăяo��
    InitB();
	//6_6_3��ʂ�`�悷��֐����Ăяo��
	DS();
}
//6_7�����u���b�N�𗎉�������֐�
void FB() {
    //6_7_1�u���b�N�̈ړ��O�̏�Ԃ�錾����
    B lastB = block;
    //6_7_2�u���b�N�𗎉�������
    block.y++;
    //6_7_3�u���b�N�ƃt�B�[���h���d�Ȃ������ǂ�������
    if (BIF()){
        //6_7_4�����u���b�N���ړ��O�̏�Ԃɖ߂�
        block = lastB;
        //6_7_5�����u���b�N�̂��ׂĂ̍s������
        for (int y = 0; y < B_HEIGHT_MAX; y++) {
            //6_7_6�����u���b�N�̂��ׂĂ̗񕪔���
            for (int x = 0; x < B_WIDTH_MAX; x++) {
                //6_7_7�u���b�N������}�X���ǂ����𔻒�
                if (block.shape.patterm[y][x]){
                    //6_7_8�t�B�[���h�ɏ�����u���b�N����������
                    field[block.y+y][block.x+x] = B_SOFT;
                }
            }
        }
        //6_7_9��������u���b�N���폜����֐����Ăяo��
        EraseL();
        //6_7_10�u���b�N��������
        InitB();
        //6_7_11�u���b�N�ƃt�B�[���h���d�Ȃ������ǂ�������
        if (BIF()){
            //6_4_12�Q�[����������
            Init();
        }
    }
    //6_7_13��ʕ`��
    DS();
}
//6_8���C���֐�
int main() {
    //6_8_1�������V���b�t��
    srand((unsigned int)time(NULL));
	//6_8_2�Q�[���̏�����
	Init();
    //6_8_3�O��̍X�V������ێ�����ϐ���錾
    time_t lastClock = clock();
	//6_8_4���C�����[�v
	while (1) {
        //6_8_5���݂̎�����錾
        time_t newClock = clock();
        //6_8_6�ҋ@���Ԃ��o�߂�����
        if (newClock >= lastClock+INTERVAL3){
            //6_8_7�O��̍X�V���������݂̎����ōX�V
            lastClock = newClock;
            //6_8_8�����u���b�N�𗎉�������֐����Ăяo��
            FB();
        }
        //6_8_9�L�[�{�[�h���͂𔻒�
        if (_kbhit()){
            //6_8_10�u���b�N�̈ړ��O�̏�Ԃ�錾����
            B lastB = block;
            //6_8_11���͂��ꂽ�L�[�ɂ���ĕ��򂷂�
            switch(_getch()){
            case'w'://6_8_12w�L�[�������ꂽ��
                    break;
            case's'://6_8_13s�L�[�������ꂽ��
                block.y++;//6_8_14�u���b�N�����Ɉړ�
                break;
            case'a'://6_8_15a�L�[�������ꂽ��
                block.x--;//6_8_16�u���b�N�����Ɉړ�
                break;
            case'd'://6_8_17s�L�[�������ꂽ��
                block.x++;//6_8_18�u���b�N���E�Ɉړ�
                break;
            default://6_8_19����ȊO�̃L�[�������ꂽ��
                RB();//6_8_20�u���b�N����]������֐����Ăяo��
                break;
            }
            //6_8_21�u���b�N�ƃt�B�[���h���d�Ȃ������ǂ�������
            if (BIF()){
                //6_8_22�u���b�N���ړ��O�̏�Ԃɖ߂�
                block = lastB;

            }
            //6_8_23�u���b�N�ƃt�B�[���h���d�Ȃ�Ȃ����
            else {
                //6_8_24��ʂ�`��
                DS();
            }
        }
	}
}
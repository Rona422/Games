//1�w�b�_�[
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<string.h>//1_3
#include<time.h>  //1_4
#include<conio.h> //1_5
#include<vector>  //1_6
//2�萔
#define M_WIDTH (19)       //2_1���H�̕�
#define M_HEIGHT (19)      //2_2���H�̍���
#define FPS (2)            //2_3��b������̍X�V�p�x
#define FPS2 (10)
#define INTERVAL (1000/FPS)//2_4�X�V���Ƃ̑ҋ@����(�~���b)
#define INTERVAL2 (1000/FPS2)//2_4�X�V���Ƃ̑ҋ@����(�~���b)
#define THAWORLD (7)       //���A�C�e���̒�~����(�X�V��)
#define PUTI (26)           //���A�C�e���̉�������
//3�񋓑�
//3_1�L�����N�^�[�̎�ނ��`
enum {
    C_PLAYER,//3_1_1�v���C���[
    C_RANDOM,//3_1_2�C�܂��ꃂ���X�^�[
    C_CHASE, //3_1_3�ǂ����������X�^�[
    C_AMBUSH,//3_1_4���胂���X�^�[
    C_SIEGE, //3_1_5���݌��������X�^�[
    C_WP,
    C_MAX    //3_1_6�L�����N�^�[��
};
//3_2�����̎�ނ��`
enum {
    D_U,//3_2_1��
    D_L,//3_2_2��
    D_D,//3_2_3��
    D_R,//3_2_4�E
    D_MAX//3_2_5�����̐�
};
//4�\����
//4_1�x�N�g���̍\����
typedef struct {
    int x, y;//4_1_1���W
}VEC2;
//4_2�L�����N�^�[�̍\����
typedef struct {
    VEC2 position;      //4_2_1���W
    const VEC2 defaultP;//4_2_2�������W
    VEC2 lastP;         //4_2_3�O��̍��W
}C;
//5�ϐ�
int a = 0,b=0,c=0,cun=0;
//5_1���H��錾
char maze[M_HEIGHT][M_WIDTH+1];
// [5-2]���H�̏�����Ԃ�錾
const char defaultMaze[M_HEIGHT][M_WIDTH + 1] =
{
    "#########o#########",
    "#ooooooo#o#ooooooo#",
    "#o###o#o#o#o#o###o#",
    "#o# #o#ooooo#o# #o#",
    "#o###o###o###o###o#",
    "#ooooooooooooooooo#",
    "#o###o###o###o###o#",
    "#oog#o#oooop#o#ooo#",
    "###o#o#o###o#o#o###",
    "oooooooo# #oooooooo",
    "###o#o#o###o#o#o###",
    "#ooo#o#ooooo#o#ooo#",
    "#o###o###o###o###o#",
    "#oooooooo oooooooo#",
    "#o###o###o###o###o#",
    "#o# #o#pooog#o# #o#",
    "#o###o#o#o#o#o###o#",
    "#ooooooo#o#ooooooo#",
    "#########o#########"
};
//5_3�L�����N�^�[�̔z���錾
C characters[C_MAX] = {
    //5_3_1C_PLAYER
    {
        //5_3_2VEC2 position ���W
        {},
        //5_3_3const VEC2 defaultP �������W
        {9,13},
        //5_3_4VEC2lastP �O��̍��W
        {},
    },
    //5_2_5C_RANDPM �C�܂��ꃂ���X�^�[
    {
        //5_3_6VEC2 position ���W
        {},
        //5_3_7const VEC2 defaultP �������W
        {1,1},
        //5_3_8VEC2lastP �O��̍��W
        {},
    },
    //5_3_9C_CHASE �ǂ����������X�^�[
    {
        //5_3_10VEC2 position ���W
        {},
        //5_3_11const VEC2 defaultP �������W
        {17,1},
        //5_3_12VEC2lastP �O��̍��W
        {},
    },
    //5_3_13C_AMBUSH ���胂���X�^�[
    {
        //5_3_14VEC2 position ���W
        {},
        //5_3_15const VEC2 defaultP �������W
        {1,17},
        //5_3_16VEC2lastP �O��̍��W
        {},
    },
    //5_3_17C_SIEGE ���݌��������X�^�[
    {
        //5_3_18VEC2 position ���W
        {},
        //5_3_19const VEC2 defaultP �������W
        {17,17},
        //5_3_20VEC2lastP �O��̍��W
        {},
    },
    //5_3_17C_SIEGE ���݌��������X�^�[
{
    //5_3_18VEC2 position ���W
    {},
    //5_3_19const VEC2 defaultP �������W
    {2,2},
    //5_3_20VEC2lastP �O��̍��W
    {},
},
};
//5_4�����̃x�N�g���̔z���錾
VEC2 directions[D_MAX] = {
    {0,-1},//5_4_1D_U��
    {-1,0},//5_4_2D_L��
    {0,1}, //5_4_3D_D��
    {1,0}  //5_4_4D_R�E
};
//6�֐�
//6_1�x�N�g�����Z����֐�
VEC2 Vec2add(VEC2 _v0, VEC2 _v1) {
    //6_1_1���Z�����x�N�g����Ԃ�
    return{
        _v0.x+_v1.x,
        _v0.y+_v1.y
    };
}
//6_2�x�N�g�������Z����֐�
VEC2 Vec2S(VEC2 _v0, VEC2 _v1) {
    //6_2_1���Z�����x�N�g����Ԃ�
    return{
        _v0.x - _v1.x,
        _v0.y - _v1.y
    };
}
//6_3�x�N�g�����m�����������ǂ������肷��֐�
bool Vec2E(VEC2 _v0, VEC2 _v1) {
    //6_3_1�x�N�g�����m�����������ǂ�����Ԃ�
    return(_v0.x == _v1.x) && (_v0.y == _v1.y);
}
//6_4�㉺���E�Ƀ��[�v�������W���擾����֐�
VEC2 GetLP(VEC2 _position) {
    //6_4_1�㉺���[�v�������W��Ԃ�
    return{
        (M_WIDTH+_position.x)% M_WIDTH,
        (M_HEIGHT+_position.y) % M_HEIGHT
    };
}
//6_5�����_���Ȉړ�����擾����֐�
VEC2 GetRP(C _character) {
    //6_5_1�ړ���̌��̃��X�g��錾
    std::vector<VEC2>positions;
    //6_5_2���ׂĂ̕����𔽕�����
    for (int i = 0; i < D_MAX; i++) {
        //6_5_3�e���ʂ̍��W��錾
        VEC2 newP = Vec2add(_character.position,directions[i]);
        //6_5_4�Ώۂ̍��W���㉺���E�Ƀ��[�v
        newP = GetLP(newP);
        //6_5_5�Ώۂ̍��W�Ɉړ��\������
        //�ǂł͂Ȃ�&&�O��̍��W�Ɠ����ł͂Ȃ�
        if ((maze[newP.y][newP.x]!='#')&&(!Vec2E(newP,_character.lastP))) {
            //6_5_6�Ώۂ̍��W���ړ���̌��Ƀ��X�g�ɒǉ�
            positions.push_back(newP);
        }
    }
    //6_5_7�ړ���̌��̒����烉���_���ō��W��Ԃ�
    return positions[rand()%positions.size()];
}
//6_5�����_���Ȉړ�����擾����֐�
VEC2 GetWP(C _character) {
    //6_5_1�ړ���̌��̃��X�g��錾
    std::vector<VEC2>positions;
    //6_10_1���H�̂��ׂĂ̍s������
    for (int y = 0; y < M_HEIGHT; y++) {
        //6_10_2���H�̂��ׂĂ̗񕪔���
        for (int x = 0; x < M_WIDTH; x++) {
                //6_5_3�e���ʂ̍��W��錾
                VEC2 newP;
                newP.y = y; newP.x = x;
                //6_5_5�Ώۂ̍��W�Ɉړ��\������
                //�ǂł͂Ȃ�
                if (maze[newP.y][newP.x] != '#') {
                    //6_5_6�Ώۂ̍��W���ړ���̌��Ƀ��X�g�ɒǉ�
                    positions.push_back(newP);
                }
        }
    }
    //6_5_7�ړ���̌��̒����烉���_���ō��W��Ԃ�
    return positions[rand() % positions.size()];
}
//6_6�ŒZ�o�H�̍ŏ��̍��W�擾�֐�
VEC2 GetCP(C _character,VEC2 _targetP) {
    //6_6_1�o�H��Y�킷�ׂ����W�̃��X�g��錾
    std::vector<VEC2>toCP;
    //6_6_2�T������L�����N�^�[���g�̍��W��T���̍��W���X�g�ɒǉ�
    toCP.push_back(_character.position);
    //6_6_3�T���J�n�n�_���珑���}�X�ւ̋�����ێ�����z���錾
    int distances[M_HEIGHT][M_WIDTH];
    //6_8_4���H�̂��ׂĂ̍s�𔽕�
    for (int y = 0; y < M_HEIGHT; y++){
        //6_6_5���H�̂��ׂĂ̗�𔽕�
        for (int x = 0; x < M_WIDTH; x++){
            //6_6_6�Ώۂ̃}�X�ւ̋����𖢐ݒ�Ƃ��ď�����
            distances[y][x] = -1;
        }
    }
    //6_6_7�T������L�����N�^�[�̍��W�ւ̋�����0�ɐݒ�
    distances[_character.position.y][_character.position.x] = 0;
    //6_6_8�T���J�n�n�_���珑���}�X�ւ̌o�H��ێ�����z���錾
    std::vector<VEC2> routes[M_HEIGHT][M_WIDTH];
    //6_6_9�T���̍��W���X�g����ɂȂ�܂Ŕ���
    while (!toCP.empty()) {
        //6_6_10���ׂĂ̕����𔽕�
        for (int i = 0; i < D_MAX; i++){
            //6_6_11�T�����̍��W�ɗאڂ���e�����ɍ��W���擾
            VEC2 newP = Vec2add(toCP.front(),directions[i]);
            //6_6_12�Ώۂ̍��W���㉺���E�Ƀ��[�v���������W�ɕϊ�
            newP = GetLP(newP);
            //6_6_13�Ώۂ̍��W�ւ̋�����錾
            int newD = distances[toCP.front().y][toCP.front().x] + 1;
            //6_6_14�Ώۂ̍��W��T�����ׂ����ǂ�������
            //���ݒ�||�ŒZ����
            if ((distances[newP.y][newP.x]<0)||(newD<distances[newP.y][newP.x])&&(maze[newP.y][newP.x]!='#')) {
                //6_6_15�Ώۂ̍��W�ւ̋������X�V
                distances[newP.y][newP.x] = newD;
                //6_6_16�Ώۂ̍��W��T���̍��W���X�g�֒ǉ�
                toCP.push_back(newP);
                //6_6_17�Ώۂ̍��W�ւ̌o�H��O�̍��W�̌o�H�ŏ�����
                routes[newP.y][newP.x] = routes[toCP.front().y][toCP.front().x];
                //6_6_18�Ώۂ̍��W�ւ̌o�H�ɑΏۂ̍��W��ǉ�
                routes[newP.y][newP.x].push_back(newP);

            }
        }
        //6_6_19�T���̍��W���X�g����擪�̍��W���폜
        toCP.erase(toCP.begin());
        //6_6_20�̌o�H������&&�O��ƈႤ���W������
        if ((!routes[_targetP.y][_targetP.x].empty())&&(!Vec2E(routes[_targetP.y][_targetP.x].front(),_character.lastP))) {
            //6_6_21�ڕW�n�_�ւ̌o�H�̈�ڂ̍��W��Ԃ�
            return routes[_targetP.y][_targetP.x].front();
        }
        //6_6_22�ڕW�n�_�ւ̌o�H���Ȃ����
        else {
            //6_6_23�����_���ȍ��W��Ԃ�
            return GetRP(_character);
        }
    }
}
//6_7���H��`�悷��֐�
void DM() {
    //6_7_1��ʃo�b�t�@�[��錾
    char screen[M_HEIGHT][M_WIDTH + 1];
    //6_7_2��ʃo�b�t�@�[�ɖ��H���R�s�[
    memcpy(screen,maze,sizeof maze);
    //6_7_3���ׂẴL�����N�^�[������
    for (int i = 0; i < C_MAX; i++){
        //6_7_4�L�����N�^�[�̔ԍ�����ʃo�b�t�@�[�ɏ�������
        screen[characters[i].position.y][characters[i].position.x] = i;
    }
    //6_7_5��ʃN���A
    system("cls");
    a++;
    //6_7_6���H�̂��ׂĂ̍s������
    for (int y = 0; y < M_HEIGHT; y++){
        //6_7_7���H�̂��ׂĂ̗񕪔���
        for (int x = 0; x < M_WIDTH; x++){
            //6_7_8�}�X�̕`��
            switch (screen[y][x]) {
            case ' '://6_7_9��
                printf("�@");
                break;
            case '#'://6_7_10��
                printf("��");
                break;
            case 'o'://6_7_11�h�b�g
                printf("�E");
                break;
            case 'g':
                printf("��");
                break;
            case 'p':
                printf("�a");
                break;
            case C_PLAYER://6_7_12�v���C���[
                if (a %= 2)printf("��");
                else printf("��");
                break;
            case C_RANDOM://6_7_13�C�܂��ꃂ���X�^�[
                printf("��");
                break;
            case C_CHASE://6_7_14�ǂ����������X�^�[
                printf("��");
                break;
            case C_AMBUSH://6_7_15���胂���X�^�[
                printf("��");
                break;
            case C_SIEGE://6_7_16���݌��������X�^�[
                printf("��");
                break;
            case C_WP://6_7_13�C�܂��ꃂ���X�^�[
                printf("��");
                break;
            }
        }
        //6_7_17���s
        printf("\n");
    }
}
//6_8�Q�[��������������֐�
void Init() {
    int a = 0, b = 0, c = 0, cun = 0;
    memcpy(maze,defaultMaze,sizeof maze);
    //6_8_2���ׂẴL�����N�^�[������
    for (int i = 0; i < C_MAX; i++){
        //6_8_3�L�����N�^�[�̍��W��������
        characters[i].position =characters[i].lastP = characters[i].defaultP;
    }
}
//6_9�Q�[���I�[�o�[�̊֐�
bool GO() {
    //6_9_1���ׂẴ����X�^�[�𔽕�
    for (int i = C_PLAYER+1; i < C_MAX; i++){
        //6_9_2�Ώۂ̃����X�^�[�ƃv���C���[�̍��W���������ǂ�������
        if (Vec2E(characters[i].position,characters[C_PLAYER].position)) {
            //6_9_3��ʃN���A
            system("cls");
            //6_9_4���H�̍����̔�����������
            for (int j = 0; j < M_HEIGHT/2; j++){
                //6_9_5���s
                printf("\n");
            }
            //6_9_6�Q�[���I�[�o�[�̃��b�Z�[�W��\��
            printf("�@�@�@�@�@�f�`�l�d�@�n�u�d�q");
            //6_9_7�L�[�{�[�h���͑҂�
            _getch();
            //6_9_8�Q�[���I�[�o�[�ɂȂ������ʂ�Ԃ�
            return true;
        }
    }
    //6_9_9�Q�[���I�[�o�[�ɂȂ�Ȃ������Ƃ������ʂ�Ԃ�
    return false;
}
//6_10�G���f�B���O�֐�
bool Com() {
    //6_10_1���H�̂��ׂĂ̍s������
    for (int y = 0; y < M_HEIGHT; y++){
        //6_10_2���H�̂��ׂĂ̗񕪔���
        for (int x = 0; x < M_WIDTH; x++){
            //6_10_3�Ώۂ̃}�X���h�b�g������
            if (maze[y][x]=='o'){
                //6_10_4�N���A�ł͂Ȃ��Ƃ������ʂ�Ԃ�
                return false;
            }
        }
    }
    //6_10_5��ʃN���A
    system("cls");
    //6_10_6���H�̍����̔�����������
    for (int i = 0; i < M_HEIGHT/2; i++){
        //6_10_7���s
        printf("\n");
    }
    //6_10_8�G���f�B���O�̃��b�Z�[�W��\��
    printf("�@�@�b�n�m�f�q�`�s�t�k�`�s�h�n�m�r�I");
    //6_10_9�L�[�{�[�h���͑҂�
    _getch();
    //6_10_10�N���A�������ʂ�Ԃ�
    return true;

}
//6_11���C���֐�
int main() {
    //6_11_1���������݂̎����ŃV���b�t��
    srand((unsigned int)time(NULL));
start://6_11_2�Q�[���J�n���x��
    ;//6_11_3��
    //6_11_4�Q�[��������������֐�
    Init();
    //6_11_5���H��`�悷��֐�
    DM();
    //6_11_6�O��̍X�V������錾
    time_t lastC = clock();
	//6_11_7�������[�v
    while (1) {
        //6_11_8���݂̎�����錾
        time_t newC = clock();
        if (c > 0) {
            if (newC > lastC + INTERVAL2) {
                c--;
                //6_11_10�O��̍X�V���������݂̎����ōX�V
                lastC = newC;
                cun++;
                if (b > 0)b--;
                if (b == 0) {
                    //6_11_11���ׂẴ����X�^�[������
                    for (int i = C_PLAYER + 1; i < C_MAX; i++) {
                        //6_11_12�ړ���̍��W��錾
                        VEC2 newP = characters[i].position;
                        //6_11_13�����X�^�[�̎�ނŕ���
                        switch (i) {
                            //6_11_14�C�܂��ꃂ���X�^�[
                        case C_RANDOM: {
                            //6_11_15�����_���Ȉړ���̍��W��ݒ�
                            newP = GetRP(characters[i]);
                            break;
                        }
                                     //6_11_16�ǂ����������X�^�[
                        case C_CHASE: {
                            //6_11_17�v���C���[��ǂ���������W��ݒ�
                            newP = GetCP(characters[i], characters[C_PLAYER].position);
                            break;
                        }
                                    //6_11_18���胂���X�^�[
                        case C_AMBUSH: {
                            //6_11_19�v���C���[�̌����x�N�g����錾
                            VEC2 playerD = Vec2S(characters[C_PLAYER].position, characters[C_PLAYER].lastP);
                            //6_11_20�ڕW�n�_��錾
                            VEC2 targetP = characters[C_PLAYER].position;
                            //6_11_21�O�񔽕�
                            for (int j = 0; j < 3; j++) {
                                //6_11_22�ڕW�n�_�Ƀv���C���[�̌����x�N�g�������Z
                                targetP = Vec2add(targetP, playerD);
                            }
                            //6_11_23�ڕW�n�_���㉺���E�Ƀ��[�v���������W�ɕϊ�
                            targetP = GetLP(targetP);
                            //6_11_24�ڕW�n�_��ڎw�����W��ݒ�
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                                     //6_11_25���݌��������X�^�[
                        case C_SIEGE: {
                            //6_11_26�ǂ����������X�^�[����v���C���[�ւ̃x�N�g�����擾
                            VEC2 chaseTP = Vec2S(characters[C_PLAYER].position, characters[C_CHASE].position);
                            //6_11_27�ړI�n�錾
                            VEC2 targetP = Vec2add(characters[C_PLAYER].position, chaseTP);
                            //6_11_28�ڕW�n�_���㉺���E�Ƀ��[�v���������W�ɕϊ�
                            targetP = GetLP(targetP);
                            //6_11_29�ڕW�n�_��ڎw�����W��ݒ�
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                        case C_WP: {
                            //6_11_15�����_���Ȉړ���̍��W��ݒ�
                            newP = GetRP(characters[i]);
                            //6_5_7�ړ���̌��̒����烉���_���ō��W��Ԃ�
                            int cun =rand() % 100;
                            if (cun %= 80) {
                                newP = GetWP(characters[i]);
                            }
                            break;
                        }
                        }
                        //6_11_30�O��̍��W�����݂̍��W�ōX�V
                        characters[i].lastP = characters[i].position;
                        //6_11_31�ړ���Ɉړ�������
                        characters[i].position = newP;
                    }
                    //6_11_32�Q�[���I�[�o�[�ɂȂ���������
                    if (GO()) {
                        //6_11_33�Q�[���̊J�n���x���ɃW�����v
                        goto start;
                    }
                }
                //6_11_34�ĕ`��
                DM();
            }
        }
        else {
            //6_11_9�O��̍X�V����ҋ@���Ԃ��o�߂���������
            if (newC > lastC + INTERVAL) {
                //6_11_10�O��̍X�V���������݂̎����ōX�V
                lastC = newC;
                cun++;
                if (b > 0)b--;
                if (b == 0) {
                    //6_11_11���ׂẴ����X�^�[������
                    for (int i = C_PLAYER + 1; i < C_MAX; i++) {
                        //6_11_12�ړ���̍��W��錾
                        VEC2 newP = characters[i].position;
                        //6_11_13�����X�^�[�̎�ނŕ���
                        switch (i) {
                            //6_11_14�C�܂��ꃂ���X�^�[
                        case C_RANDOM: {
                            //6_11_15�����_���Ȉړ���̍��W��ݒ�
                            newP = GetRP(characters[i]);
                            break;
                        }
                                     //6_11_16�ǂ����������X�^�[
                        case C_CHASE: {
                            //6_11_17�v���C���[��ǂ���������W��ݒ�
                            newP = GetCP(characters[i], characters[C_PLAYER].position);
                            break;
                        }
                                    //6_11_18���胂���X�^�[
                        case C_AMBUSH: {
                            //6_11_19�v���C���[�̌����x�N�g����錾
                            VEC2 playerD = Vec2S(characters[C_PLAYER].position, characters[C_PLAYER].lastP);
                            //6_11_20�ڕW�n�_��錾
                            VEC2 targetP = characters[C_PLAYER].position;
                            //6_11_21�O�񔽕�
                            for (int j = 0; j < 3; j++) {
                                //6_11_22�ڕW�n�_�Ƀv���C���[�̌����x�N�g�������Z
                                targetP = Vec2add(targetP, playerD);
                            }
                            //6_11_23�ڕW�n�_���㉺���E�Ƀ��[�v���������W�ɕϊ�
                            targetP = GetLP(targetP);
                            //6_11_24�ڕW�n�_��ڎw�����W��ݒ�
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                                     //6_11_25���݌��������X�^�[
                        case C_SIEGE: {
                            //6_11_26�ǂ����������X�^�[����v���C���[�ւ̃x�N�g�����擾
                            VEC2 chaseTP = Vec2S(characters[C_PLAYER].position, characters[C_CHASE].position);
                            //6_11_27�ړI�n�錾
                            VEC2 targetP = Vec2add(characters[C_PLAYER].position, chaseTP);
                            //6_11_28�ڕW�n�_���㉺���E�Ƀ��[�v���������W�ɕϊ�
                            targetP = GetLP(targetP);
                            //6_11_29�ڕW�n�_��ڎw�����W��ݒ�
                            newP = GetCP(characters[i], targetP);
                            break;
                        }
                        case C_WP: {
                            //6_11_15�����_���Ȉړ���̍��W��ݒ�
                            newP = GetRP(characters[i]);
                            //6_5_7�ړ���̌��̒����烉���_���ō��W��Ԃ�
                            int cun =rand() % 100;
                            if (cun >80) {
                                newP = GetWP(characters[i]);
                            }
                            break;
                        }
                        }
                        //6_11_30�O��̍��W�����݂̍��W�ōX�V
                        characters[i].lastP = characters[i].position;
                        //6_11_31�ړ���Ɉړ�������
                        characters[i].position = newP;
                    }
                    //6_11_32�Q�[���I�[�o�[�ɂȂ���������
                    if (GO()) {
                        //6_11_33�Q�[���̊J�n���x���ɃW�����v
                        goto start;
                    }
                }
                //6_11_34�ĕ`��
                DM();
            }
        }
        //6_11_35�L�[�{�[�h���͂𔻒�
        if (_kbhit()) {
            //6_11_36�v���C���̐V�������W
            VEC2 newP = characters[C_PLAYER].position;
            //6_11_37���͂��ꂽ�L�[�ɂ���ĕ���
            switch(_getch()) {
                case'w'://6_11_38w�������ꂽ���ֈړ�
                    newP.y--;
                    break;
                case's'://6_11_39s�������ꂽ���ֈړ�
                    newP.y++;
                    break;
                case'a'://6_11_40a�������ꂽ���ֈړ�
                    newP.x--;
                    break;
                case'd'://6_11_41d�������ꂽ���ֈړ�
                    newP.x++;
                    break;
            }
            //6_11_42�ړ���̍��W���㉺���E�Ƀ��[�v������
            newP = GetLP(newP);
            //6_11_43�ړ��悪�ǂłȂ����ǂ�������
            if (maze[newP.y][newP.x] != '#') {
                //6_11_44�v���C���[�̑O��̍��W�����񂴂��̍��W�ōX�V
                characters[C_PLAYER].lastP = characters[C_PLAYER].position;
                //6_11_45�v���C���[�̍��W���X�V
                characters[C_PLAYER].position = newP;
                if (b == 0) {
                    //6_11_46�Q�[�����[�o�[�ɂȂ���������
                    if (GO()) {
                        //6_11_47�Q�[���̊J�n���x���ɃW�����v
                        goto start;
                    }
                }
                //6_11_48�v���C���[�̍��W�Ƀh�b�g�����邩�ǂ����𔻒肷��
                if (maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] == 'o') {
                    //6_11_49�v���C���[�̍��W�̃h�b�g������
                    maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] = ' ';
                    //6_11_50�N���A����������
                    if (Com()){
                        //6_11_51�Q�[���̊J�n���x���ɃW�����v
                        goto start;
                    }
                }
                //6_11_48�v���C���[�̍��W�Ƀh�b�g�����邩�ǂ����𔻒肷��
                if (maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] == 'g') {
                    //6_11_49�v���C���[�̍��W�̃h�b�g������
                    maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] = ' ';
                    b = THAWORLD;
                }
                //6_11_48�v���C���[�̍��W�Ƀh�b�g�����邩�ǂ����𔻒肷��
                if (maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] == 'p') {
                    //6_11_49�v���C���[�̍��W�̃h�b�g������
                    maze[characters[C_PLAYER].position.y][characters[C_PLAYER].position.x] = ' ';
                    c = PUTI;
                }
            }
            //6_11_52�ĕ`��
            DM();
        }
	}
}
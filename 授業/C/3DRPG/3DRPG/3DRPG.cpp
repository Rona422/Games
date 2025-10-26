//1�w�b�_�[
#include<stdio.h> //1_1
#include<stdlib.h>//1_2
#include<time.h>  //1_3
#include<conio.h> //1_4
#include<vector>  //1_5
#include<string.h>  //1_5
//2�萔
#define MAZE_WIDTH  (8)//2_1���H�̕����`����
#define MAZE_HEIGHT (8)//2_2���H�̍������`����
#define GOAL_X (MAZE_WIDTH-1)
#define GOAL_Y (MAZE_HEIGHT-1)
//3�񋓑�
//3_1���ʂ̎�ނ��`
enum{
    DIRECTION_NORTH,//3_1_1�k
    DIRECTION_WEST, //3_1_2��
    DIRECTION_SOUTH,//3_1_3��
    DIRECTION_EAST, //3_1_4��
    DIRECTION_MAX   //3_1_5���ʂ̐�
};
//3_2�v���C���[����̑��Έʒu�̎�ނ��`����
enum{
    LOCATION_FRONT_LEFT,    // [3-2-1]���O
    LOCATION_FRONT_RIGHT,   // [3-2-2]�E�O
    LOCATION_FRONT,         // [3-2-3]�O
    LOCATION_LEFT,          // [3-2-4]��
    LOCATION_RIGHT,         // [3-2-5]�E
    LOCATION_CENTER,        // [3-2-6]���S
    LOCATION_MAX            // [3-2-7]�ʒu�̐�
};
//4�\����
//4_1�x�N�g���̍\���̂�錾����
typedef struct {
    int x, y;//4_1_1���W
} VEC2;
//4_2���H�̃}�X�̍\���̂�錾����
typedef struct {
    bool walls[DIRECTION_MAX];//4_2_1�e���ʂ̕ǂ̗L��
} TILE;
//4 - 3]�v���C���[�̍\���̂�錾����
typedef struct {
    VEC2 position;  //4_3_1���W
    int direction;  //4_3_1�����Ă������
} CHARACTER;
//5�ϐ�
//5_1�e���ʂ̃x�N�g����錾����
VEC2 directions[] =
{
    { 0,-1},    // DIRECTION_NORTH  �k
    {-1, 0},    // DIRECTION_WEST   ��
    { 0, 1},    // DIRECTION_SOUTH  ��
    { 1, 0}     // DIRECTION_EAST   ��
};
//5_2��ƂȂ�A�X�L�[�A�[�g��錾����
const char* all =
"L       /\n"
"#L     /#\n"
"#|L _ /|#\n"
"#|#|#|#|#\n"
"#|#|_|#|#\n"
"#|/   L|#\n"
"#/     L#\n"
"/       L\n";

//5_3���O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontLeftNorth =
"         \n"
"         \n"
"  _      \n"
" |#|     \n"
" |_|     \n"
"         \n"
"         \n"
"         \n";

//5_4�E�O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontRightNorth =
"         \n"
"         \n"
"      _  \n"
"     |#| \n"
"     |_| \n"
"         \n"
"         \n"
"         \n";

//5_5�O���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontNorth =
"         \n"
"         \n"
"    _    \n"
"   |#|   \n"
"   |_|   \n"
"         \n"
"         \n"
"         \n";

//5_6�O�����̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontWest =
"         \n"
"         \n"
" |L      \n"
" |#|     \n"
" |#|     \n"
" |/      \n"
"         \n"
"         \n";

//5_7�O���E�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* frontEast =
"         \n"
"         \n"
"      /| \n"
"     |#| \n"
"     |#| \n"
"      L| \n"
"         \n"
"         \n";

// [5-8]�����O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* leftNorth =
"         \n"
"_        \n"
"#|       \n"
"#|       \n"
"#|       \n"
"_|       \n"
"         \n"
"         \n";

// [5-9]�E���O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* rightNorth =
"         \n"
"        _\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |_\n"
"         \n"
"         \n";

// 5_10�O�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* north =
"         \n"
"  _____  \n"
" |#####| \n"
" |#####| \n"
" |#####| \n"
" |_____| \n"
"         \n"
"         \n";
//5_11���̕ǂ̃A�X�L�[�A�[�g��錾����
const char* west =
"L        \n"
"#L       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#|       \n"
"#/       \n"
"/        \n";
//5_12�E�̕ǂ̃A�X�L�[�A�[�g��錾����
const char* east =
"        /\n"
"       /#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       |#\n"
"       L#\n"
"        L\n";
//5_13�A�X�L�[�A�[�g�̃e�[�u����錾����
const char* aaTable[LOCATION_MAX][DIRECTION_MAX] ={
    // LOCATION_FRONT_LEFT  ���O
    {
        frontLeftNorth,     // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },
    // LOCATION_FRONT_RIGHT �E�O
    {
        frontRightNorth,    // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },
    // LOCATION_FRONT       �O
    {
        frontNorth,         // DIRECTION_NORTH  �k
        frontWest,          // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        frontEast           // DIRECTION_EAST   ��
    },
    // LOCATION_LEFT        ��
    {
        leftNorth,          // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },
    // LOCATION_RIGHT       �E
    {
        rightNorth,         // DIRECTION_NORTH  �k
        NULL,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        NULL                // DIRECTION_EAST   ��
    },
    // LOCATION_CENTER      ���S
    {
        north,              // DIRECTION_NORTH  �k
        west,               // DIRECTION_WEST   ��
        NULL,               // DIRECTION_SOUTH  ��
        east                // DIRECTION_EAST   ��
    }
};
// [5-14]�v���C���[����̑��΍��W�̃e�[�u����錾����
VEC2 locations[DIRECTION_MAX][LOCATION_MAX] =
{
    // DIRECTION_NORTH  �k
    {
        {-1,-1},    // LOCATION_FRONT_LEFT  ���O
        { 1,-1},    // LOCATION_FRONT_RIGHT �E�O
        { 0,-1},    // LOCATION_FRONT       �O
        {-1, 0},    // LOCATION_LEFT        ��
        { 1, 0},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    },
    // DIRECTION_WEST   ��
    {
        {-1, 1},    // LOCATION_FRONT_LEFT  ���O
        {-1,-1},    // LOCATION_FRONT_RIGHT �E�O
        {-1, 0},    // LOCATION_FRONT       �O
        { 0, 1},    // LOCATION_LEFT        ��
        { 0,-1},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    },
    // DIRECTION_SOUTH  ��
    {
        { 1, 1},    // LOCATION_FRONT_LEFT  ���O
        {-1, 1},    // LOCATION_FRONT_RIGHT �E�O
        { 0, 1},    // LOCATION_FRONT       �O
        { 1, 0},    // LOCATION_LEFT        ��
        {-1, 0},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    },
    // DIRECTION_EAST   ��
    {
        { 1,-1},    // LOCATION_FRONT_LEFT  ���O
        { 1, 1},    // LOCATION_FRONT_RIGHT �E�O
        { 1, 0},    // LOCATION_FRONT       �O
        { 0,-1},    // LOCATION_LEFT        ��
        { 0, 1},    // LOCATION_RIGHT       �E
        { 0, 0}     // LOCATION_CENTER      ���S
    }
};
//5_15���H��錾����
TILE maze[MAZE_HEIGHT][MAZE_WIDTH];
//5_16�v���C���[
CHARACTER player;
//6�֐�
//6_1�x�N�g�������Z����֐���錾����
VEC2 VecAdd(VEC2 _v0, VEC2 _v1)
{
    // [6-1-1]�x�N�g�������Z���ĕԂ�
    return
    {
        _v0.x + _v1.x,
        _v0.y + _v1.y
    };
}
//6_2�Ώۂ̍��W�����H�͈͓̔����ǂ����𔻒肷��֐���錾����
bool IsInsideMaze(VEC2 _position){
    //6_2_1�Ώۂ̍��W�����H�͈͓̔����ǂ�����Ԃ�
    return (_position.x >= 0)
        && (_position.x < MAZE_WIDTH)
        && (_position.y >= 0)
        && (_position.y < MAZE_HEIGHT);
}
//6_3�ǂ��@��֐�
void DigWall(VEC2 _position, int _direction) {
    //3_3_1�Ώۂ̍��W�����H�Ȃ�������
    if (!IsInsideMaze(_position)){
        //3_3_2�֐��𔲂���
        return;
    }
    //6_3_3�Ώۂ̕ǂ��@��
    maze[_position.y][_position.x].walls[_direction] = false;
    //6_3_4�ׂ̃}�X�̍��W
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);
    //6_3_5�ׂ̃}�X���͈͓�������
    if (IsInsideMaze(_position)) {
        //6_3_6�ׂ̕����̌@��ǂ̕���
        int nextDirection=(_direction+2)%DIRECTION_MAX;
        //6_3_7�ׂ̕ǂ��@��
        maze[nextPosition.y][nextPosition.x].walls[nextDirection] = false;
    }
}
//6_4�Ώۂ̕ǂ��@���Ă��悢���ǂ����𔻒肷��֐���錾����
bool CanDigWall(VEC2 _position, int _direction){
    //6_4_1�ׂ̍��W
    VEC2 nextPosition = VecAdd(_position, directions[_direction]);
    //6_4_2�ׂ̍��W�����H�O������
    if (!IsInsideMaze(nextPosition)) {
        return false;//6_4_3�@���Ă͂����Ȃ�
    }
    //6_4_4�������J��Ԃ�
    for (int i = 0; i < DIRECTION_MAX; i++) {
        //6_4_5�ǂ��@���Ă��邩����
        if (!maze[nextPosition.y][nextPosition.x].walls[i]){
            return false;//6_4_6�@���Ă͂����Ȃ�
        }
    }
    return true;//6_4_7�@���ėǂ��I
}
//6-5���H�������_���Ő�������֐���錾����
void GenerateMap() {
    // [6-5-1]���H�̂��ׂĂ̍s�𔽕�����
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        // [6-5-2]���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++) {
            // [6-5-3]�}�X�̂��ׂĂ̕��ʂ𔽕�����
            for (int i = 0; i < DIRECTION_MAX; i++) {
                //6_5_4�S�����ɑ΂��ĕǂɂ���
                maze[y][x].walls[i] = true;
            }
        }
    }
    //6_5_5�����W
    VEC2 currentPosition = { 0,0 };
    //6_5_6�ǂ��@��ׂ��}�X�̃��X�g��錾����
    std::vector<VEC2>toDigWallPositions;
    //6_5_7���X�g�Ɍ����W��ǉ�
    toDigWallPositions.push_back(currentPosition);
    //6_5_8�������[�v
    while (1) {
        //6_5_9�@��ǂ̕������X�g
        std::vector<int>canDigDirections;
        //6_5_10���ׂĂ̕������J��Ԃ�
        for (int i = 0; i < DIRECTION_MAX; i++){
            //6_5_11�Ώۂ̕����̕ǂ��@��邩����
            if (CanDigWall(currentPosition,i)){
                canDigDirections.push_back(i);
            }
        }
        //6_5_13�@���ǂ����邩�𔻒�
        if (canDigDirections.size()>0){
            //6_5_14�@��ǂ̕���������
            int diggDirection = canDigDirections[rand() % canDigDirections.size()];
            //6_5_15�ǂ��@��
            DigWall(currentPosition,diggDirection);
            //6_5_16�@�����ǂɈړ�
            currentPosition = VecAdd(currentPosition, directions[diggDirection]);
            //6_5_17�ǂ��@��ׂ��}�X�̃��X�g�ɒǉ�
            toDigWallPositions.push_back(currentPosition);
        }
        //6_5_18�������̂��Ȃ�
        else {
            //6_5_19�ǂ��@��ׂ��}�X�̃��X�g���猻�݂̃}�X���폜
            toDigWallPositions.erase(toDigWallPositions.begin());
            //6_5_20�ǂ��@��ׂ��}�X�̃��X�g���󂩂ǂ����𔻒�
            if (toDigWallPositions.size()<=0){
                //6_5_21���[�v�I��
                break;
            }
            //6_5_22�ǂ��@��ׂ��}�X�̃��X�g����擪�̃}�X���擾���ړ�����
            currentPosition = toDigWallPositions.front();
        }
    }
}
//6_6�`�揈��
void DrawMap() {
    //6_6_1���H�̍s��
    for (int y = 0; y < MAZE_HEIGHT; y++){
        //6_6_2���H�̗�
        for (int x = 0; x < MAZE_WIDTH; x++) {
            //  [6-6-3]�k�̕ǂ�`�悷��
            printf("�{%s�{", maze[y][x].walls[DIRECTION_NORTH] ? "�\" : "�@");
        }
        //6_6_4���s
        printf("\n");
        //6_6_5���H�̂��ׂĂ̗�𔽕�
        for (int x = 0; x < MAZE_WIDTH; x++){
                //6_6_6���̃A�X�L�[�A�[�g��錾����
                char floorAA[] = "�@";
                //6_6_7�v���C���[�̍��W��`�撆
                if ((x==player.position.x)&&(y == player.position.y)){
                    //6_6_8���ʂ̃A�X�L�[�A�[�g��錾����
                    const char* directionAA[] ={
                        "��",    // DIRECTION_NORTH  �k
                        "��",    // DIRECTION_WEST   ��
                        "��",    // DIRECTION_SOUTH  ��
                        "��"     // DIRECTION_EAST   ��
                    };
                    //6_6_9�A�X�L�[�A�[�g��\���i�R�s�[
                    strcpy_s(floorAA,directionAA[player.direction]);
                }
                //6_6_10�S�[���̕`��
                else if ((x == GOAL_X) && (y == GOAL_Y)) {
                    //6_6_11
                    strcpy_s(floorAA, "�f");
                }
                //6_6_12���̕ǁA���S�̏��A���̕ǂ�`�悷��
                printf("%s%s%s",
                    maze[y][x].walls[DIRECTION_WEST] ? "�b" : "�@",
                    floorAA,
                    maze[y][x].walls[DIRECTION_EAST] ? "�b" : "�@");
        }
        //6_6_13���s
        printf("\n");
        //6_6_14���H�̂��ׂĂ̗�𔽕�����
        for (int x = 0; x < MAZE_WIDTH; x++){
            //6_6_15��̕ǂ�`�悷��
            printf("�{%s�{", maze[y][x].walls[DIRECTION_SOUTH] ? "�\" : "�@");
        }
        printf("\n"); //6_6_16���s
    }
}
//6_73D�`�揈��
void Draw3D() {
    //6_7_1��ʃo�b�t�@�[��錾����
    char screen[] =
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n"
        "         \n";
    //6_7_2���Έʒu���J��Ԃ�
    for (int i = 0; i < LOCATION_MAX; i++){
        //6_7_3��Έʒu
        VEC2 position = VecAdd(player.position, locations[player.direction][i]);
        //6_7_4��Έʒu�����H�͈̔͊O���ǂ�������
        if (!IsInsideMaze(position)) {
            continue;//6_7_5���̑��Έʒu�փX�L�b�v
        }
        //6_7_6�������J��Ԃ�
        for (int j = 0; j < DIRECTION_MAX; j++){
            //6_7_7�v���C���[����̑��Ε���
            int direction = (DIRECTION_MAX + j - player.direction) % DIRECTION_MAX;
            //6_7_8�Ώۂ̕ǂ��Ȃ�������
            if (!maze[position.y][position.x].walls[j]){
                continue;//6_7_9���̕��ʂփX�L�b�v����
            }
            //6_7_10��������A�X�L�[�A�[�g���Ȃ����ǂ����𔻒肷��
            if (!aaTable[i][direction]){
                continue;//6_7_11���̑��Έʒu�փX�L�b�v����
            }
            //6_7_12��ʃo�b�t�@�[�̂��ׂĂ̕����𔽕�����
            for (int k = 0; k < sizeof(screen); k++){
                //6_7_13�Ώۂ̕������X�y�[�X�łȂ����ǂ������肷��
                if (aaTable[i][direction][k] != ' '){
                    //6_7_14��ʃo�b�t�@�[�ɍ�������A�X�L�[�A�[�g����������
                    screen[k] = aaTable[i][direction][k];
                }
            }
        }
    }
    //6_7_15��ʃo�b�t�@�[�̂��ׂĂ̕����𔽕�����
    for (int i = 0; i < sizeof(screen); i++){
        //6_7_16��ʃo�b�t�@�[�̔��p������S�p�����ɕϊ����ĕ`�悷��
        switch (screen[i]){
        case ' ':   printf("�@");    break; //6_7_17�u �v���u�@�v�Ƃ��ĕ`�悷��
        case '#':   printf("�@");    break; //6_7_18�u#�v���u�@�v�Ƃ��ĕ`�悷��
        case '_':   printf("�Q");    break; //6_7_19�u_�v���u�Q�v�Ƃ��ĕ`�悷��
        case '|':   printf("�b");    break; //6_7_20�u|�v���u�b�v�Ƃ��ĕ`�悷��
        case '/':   printf("�^");    break; //6_7_21�u/�v���u�^�v�Ƃ��ĕ`�悷��
        case 'L':   printf("�_");    break; //6_7_22�uL�v���u�_�v�Ƃ��ĕ`�悷��
        default:
            //6_7_23��L�ȊO�̕����͂��̂܂ܕ`�悷��
            printf("%c", screen[i]);
            break;
        }
    }
}
//6_8�Q�[���̏�����
void Init() {
    //6_8_1���H�������_���Ő���
    GenerateMap();
    //6_8_2�v���C���[�̍��W
    player.position = { 0,0 };
    //6_8_3�v���C���[�̕����i�k
    player.direction = DIRECTION_NORTH;
}
//6_9���C��
int main() {
    //6_9_1�������V���b�t������
    srand((unsigned int)time(NULL));
    //6_9_2�Q�[��������
    Init();
	//6_9_3���C�����[�v
	while (1) {
        //6_9_4��ʃN���A
        system("cls");
        //6_9_5���H��3D�`��
        Draw3D();
        //6_9_6�}�b�v�`��
        DrawMap();
        //6_9_7
        switch (_getch()) {
        case'w'://6_9_8
            //6_9_9�ǂ�����
            if (!maze[player.position.y][player.position.x].walls[player.direction]) {
                //6_9_10�O�i��̍��W��錾����
                VEC2 nextPosition = VecAdd(player.position, directions[player.direction]);
                //6_9_11���H�Ȃ�������
                if (IsInsideMaze(nextPosition)){
                    //6_9_12��O�Ɉړ�
                    player.position = nextPosition;
                    //6_9_13�S�[���ɓ��B����������
                    if ((player.position.x==GOAL_X)&&(player.position.y == GOAL_Y)){
                        system("cls");//6_9_14��ʂ��N���A����
                        //6_9_15���b�Z�[�W��\������
                        printf(
                            "\n"
                            "\n"
                            "�@���@���@�b�n�m�f�q�`�s�t�k�`�s�h�n�m�r�@���@��\n"
                            "\n"
                            "\n"
                            "�@���Ȃ��͂��Ɂ@�ł񂹂̂܂悯���@�Ăɂ��ꂽ�I\n"
                            "\n"
                            "�@�������A���炭���Ƃ��ɂ����@�u�Ȃ��܁v�Ƃ���\n"
                            "���������̂Ȃ��@��������Ăɂ����@���Ȃ��ɂƂ��āA\n"
                            "�܂悯�̂����₫���@���날���ā@�݂���̂ł������c\n"
                            "\n"
                            "�@�@�@�@�@�@�@�`�@�s�g�d�@�d�m�c�@�`\n");
                        _getch();// [6-9-16]�L�[�{�[�h���͂�҂�
                        Init();// [6-9-17]�Q�[��������������
                    }
                }
            }
            break;
        case's'://6_9_18
            player.direction+=2;//6_9_19��������
            break;
        case'a'://6_9_20
            player.direction++;//6_9_21��������
            break;
        case'd'://6_9_22
            player.direction--;//6_9_23�E������
            break;
        }
        //6_9_24�v���C���[�̌����Ă�����ʂ�͈͓��ɕ␳����
        player.direction = (DIRECTION_MAX + player.direction) % DIRECTION_MAX;
	}
}
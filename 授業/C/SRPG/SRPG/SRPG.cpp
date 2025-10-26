//1�\�[�X�t�@�C��
#include<stdio.h>   //1_1
#include <stdlib.h> //1_2
#include <time.h>   //1_3
#include <conio.h>  //1_4
#include <vector>   //1_5
#include <algorithm>//1_6
//2�萔
#define TROOP_BASE (5)   //2_1��{����
#define TROOP_MAX (9)    //2_2�ő啺��
#define TROOP_UNIT (1000)//2_3�ꕺ���̒P��
#define START_YEAR (1570)//2_4�J�n�N
#define CHRONOLOGY_MAX (1024)//2_5�N�\�̍ő啶�������`����
//3�񋓑�
//3_1�喼�̎��
enum {
    LORD_DATE,     //3_1_1�ɒB�P�@
    LORD_UESUGI,   //3_1_2]�㐙���M
    LORD_TAKEDA,   //3_1_3���c�M��
    LORD_HOJO,     //3_1_4�k������
    LORD_TOKUGAWA, //3_1_5����ƍN
    LORD_ODA,      //3_1_6�D�c�M��
    LORD_ASHIKAGA, //3_1_7�����`��
    LORD_MORI,     //3_1_8�ї����A
    LORD_CHOSOKABE,//3_1_9���@�䕔���e
    LORD_SIMAZU,   //3_1_10���Ë`�v
    LORD_MAX       //3_1_11��ނ̐�
};
// [3-2]��̎�ނ��`����
enum
{
    CASTLE_YONEZAWA,       //3_2_1�đ��
    CASTLE_KASUGAYAMA,     //3_2_2�t���R��
    CASTLE_TSUTSUJIGASAKI, //3_2_3�U�P�����
    CASTLE_ODAWARA,        //3_2_4���c����
    CASTLE_OKAZAKI,        //3_2_5�����
    CASTLE_GIFU,           //3_2_6�򕌏�
    CASTLE_NIJO,           //3_2_7�����
    CASTLE_YOSHIDAKORIYAMA,//3_2_8�g�c�S�R��
    CASTLE_OKO,            //3_2_9���L��
    CASTLE_UCHI,           //3_2_10����
    CASTLE_MAX             //3_2_11��ނ̐�
};
//4�\����
//4_1�喼�̍\����
typedef struct {
	char familyName[16];//4_1_1��
    char firstName[16]; //4_1_2��
}LORD;
//4_2��̍\����
typedef struct {
    const char* name;//4_2_1���O
    char owner;      //4_2_2���
    char troopCount; //4_2_3����
    std::vector<int>connectedCastles;
}CASTLE;
//5�ϐ�
//5_1�喼�̔z���錾����
LORD lords[LORD_MAX] = {
    {"�ɒB",    "�P�@"},//5_1_1LORD_DATE        �ɒB�P�@
    {"�㐙",    "���M"},//5_1_2LORD_UESUGI      �㐙���M
    {"���c",    "�M��"},//5_1_3LORD_TAKEDA      ���c�M��
    {"�k��",    "����"},//5_1_4LORD_HOJO        �k������
    {"����",    "�ƍN"},//5_1_5LORD_TOKUGAWA    ����ƍN
    {"�D�c",    "�M��"},//5_1_6LORD_ODA         �D�c�M��
    {"����",    "�`��"},//5_1_7LORD_ASHIKAGA    �����`��
    {"�ї�",    "���A"},//5_1_8LORD_MORI        �ї����A
    {"���@�䕔","���e"},//5_1_9LORD_CHOSOKABE   ���@�䕔���e
    {"����",    "�`�v"} //5_1_10LORD_SIMAZU      ���Ë`�v
};
//5_2��̔z���錾����
CASTLE castles[CASTLE_MAX] ={
    //5_2_1CASTLE_YONEZAWA   �đ��
    {
        "�đ��",   // const char* name         ���O
        LORD_DATE,  // int owner                ���
        TROOP_BASE, // int troopCount           ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_KASUGAYAMA,  // �t���R��
            CASTLE_ODAWARA      // ���c����
        }
    },
    //5_2_2CASTLE_KASUGAYAMA �t���R��
    {
        "�t���R��",     // const char* name     ���O
        LORD_UESUGI,    // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_YONEZAWA,        // �đ��
            CASTLE_TSUTSUJIGASAKI,  // �U�P�����
            CASTLE_GIFU             // �򕌏�
        }
    },
    //5_2_3CASTLE_TSUTSUJIGASAKI �U�P�����
    {
        "�U�P�����",   // const char* name     ���O
        LORD_TAKEDA,    // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_KASUGAYAMA,  // �t���R��
            CASTLE_ODAWARA,     // ���c����
            CASTLE_OKAZAKI      // �����
        }
    },
    //5_2_4CASTLE_ODAWARA    ���c����
    {
        "���c����", // const char* name         ���O
        LORD_HOJO,  // int owner                ���
        TROOP_BASE, // int troopCount           ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_YONEZAWA,        // �đ��
            CASTLE_TSUTSUJIGASAKI,  // �U�P�����
            CASTLE_OKAZAKI          // �����
        }
    },
    //5_2_5CASTLE_OKAZAKI    �����
    {
        "�����",       // const char* name     ���O
        LORD_TOKUGAWA,  // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_TSUTSUJIGASAKI,  // �U�P�����
            CASTLE_ODAWARA,         // ���c����
            CASTLE_GIFU             // �򕌏�
        }
    },
    //5_2_6CASTLE_GIFU   �򕌏�
    {
        "�򕌏�",   // const char* name         ���O
        LORD_ODA,   // int owner                ���
        TROOP_BASE, // int troopCount           ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_KASUGAYAMA,  // �t���R��
            CASTLE_OKAZAKI,     // �����
            CASTLE_NIJO         // �����
        }
    },
    //5_2_7CASTLE_NIJO   �����
    {
        "�����",       // const char* name     ���O
        LORD_ASHIKAGA,  // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_GIFU,            // �򕌏�
            CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
            CASTLE_OKO              // ���L��
        }
    },
    //5_2_8CASTLE_YOSHIDAKORIYAMA    �g�c�S�R��
    {
        "�g�c�S�R��",   // const char* name     ���O
        LORD_MORI,      // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_NIJO,    // �����
            CASTLE_OKO,     // ���L��
            CASTLE_UCHI     // ����
        }
    },
    //5_2_9CASTLE_OKO    ���L��
    {
        "���L��",       // const char* name     ���O
        LORD_CHOSOKABE, // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_NIJO,            // �����
            CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
            CASTLE_UCHI             // ����
        }
    },
    //5_2_10CASTLE_UCHI  ����
    {
        "����",         // const char* name     ���O
        LORD_SIMAZU,    // int owner            ���
        TROOP_BASE,     // int troopCount       ����
        // std::vector<int> connectedCastles    �ڑ����ꂽ��̃��X�g
        {
            CASTLE_YOSHIDAKORIYAMA, // �g�c�S�R��
            CASTLE_OKO              // ���L��
        }
    }
};
//5_3���݂̔N
int year;
//5_4�v���C���[�̑喼
int playerLord;
//5_5�N�\��錾����
char chronology[CHRONOLOGY_MAX];
//6�֐�
//6_1��̐��𐔂��鏈��
int GetCastleCount(int _lord) {
    //6_1_1��̐���錾����
    int castleCount = 0;
    //6_1_2���ׂĂ̏�𔽕�����
    for (int i = 0; i < CASTLE_MAX; i++){
        //6_1_3�Ώۂ̏�̏�傪�A�Ώۂ̑喼���ǂ����𔻒肷��
        if (castles[i].owner == _lord){
            //6_1_4��̐������Z����
            castleCount++;
        }
    }

    // [6-1-5]��̐���Ԃ�
    return castleCount;
}
//6_2��{���`��
void DrowScreen() {
    //6_2_1��ʃN���A
    system("cls");
    //6_2_1.5�n�}�̃T���v����`�悷��
    /*printf("%s",
        "1570�˂�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�`\n"      // 01
        "�@�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@0�đ�5�@�`\n"      // 02
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`1�t��5�@�ɒB�@�`�`\n"      // 03
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�`�㐙�@�@�@�@�@�`�`\n"      // 04
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�@�@�@�@�@�@�@�@�`�`\n"      // 05
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@2�U�P5�@�@�@�`�`\n"      // 06
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�@���c�@�@�@�`�`�`\n"      // 07
        "�`�`�`�`�`�`�@�@�@�@�@�@�@5��5�@�@�@�@�@�@�@�@�`�`�`\n"      // 08
        "�`�`�`�`�@7�g�c5�@6���5�@�D�c�@4����5�@3���c5�@�`�`�`\n"      // 09
        "�`�`�`�@�@�ї��@�@�����@�@�@�@�@����@�@�k���`�`�`�`�`\n"      // 10
        "�`�`�@�`�`�`�`�`�`�`�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 11
        "�`�@�@�@�`�@8���L5�`�`�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 12
        "�`�@�@�@�`�`���@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 13
        "�`9����5�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 14
        "�`���Á`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n"      // 15
        "�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n");    // 16
        */
    //6_2_2�n�}��1�s�ڂ�`�悷��
    printf("%d�˂�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�`\n", year);
    //6_2_3�n�}��2�s�ڂ�`�悷��
    printf("�@�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@%d%.4s%d�@�`\n",
        CASTLE_YONEZAWA,
        castles[CASTLE_YONEZAWA].name, castles[CASTLE_YONEZAWA].troopCount);
    //6_2_4�n�}��3�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`%d%.4s%d�@%.4s�@�`�`\n",
        CASTLE_KASUGAYAMA, castles[CASTLE_KASUGAYAMA].name, castles[CASTLE_KASUGAYAMA].troopCount,
        lords[castles[CASTLE_YONEZAWA].owner].familyName);
    //6_2_5�n�}��4�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�`%.4s�@�@�@�@�@�`�`\n",
        lords[castles[CASTLE_KASUGAYAMA].owner].familyName);
    //6_2_6�n�}��5�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�`�@�@�@�@�@�@�@�@�`�`\n");
    //6_2_7�n�}��6�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@%d%.4s%d�@�@�@�`�`\n",
        CASTLE_TSUTSUJIGASAKI, castles[CASTLE_TSUTSUJIGASAKI].name, castles[CASTLE_TSUTSUJIGASAKI].troopCount);
    //6_2_8�n�}��7�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�@�@�@�@�@�@%.4s�@�@�@�`�`�`\n",
        lords[castles[CASTLE_TSUTSUJIGASAKI].owner].familyName);
    //6_2_9�n�}��8�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�@�@�@�@�@�@�@%d%.4s%d�@�@�@�@�@�@�@�@�`�`�`\n",
        CASTLE_GIFU, castles[CASTLE_GIFU].name, castles[CASTLE_GIFU].troopCount);
    //6_2_10�n�}��9�s�ڂ�`�悷��
    printf("�`�`�`�`�@%d%.4s%d�@%d%.4s%d�@%.4s�@�@�@�@�@%d%.4s%d�@�`�`�`\n",
        CASTLE_YOSHIDAKORIYAMA, castles[CASTLE_YOSHIDAKORIYAMA].name,
        castles[CASTLE_YOSHIDAKORIYAMA].troopCount, CASTLE_NIJO, castles[CASTLE_NIJO].name,
        castles[CASTLE_NIJO].troopCount, lords[castles[CASTLE_GIFU].owner].familyName,
        CASTLE_ODAWARA, castles[CASTLE_ODAWARA].name, castles[CASTLE_ODAWARA].troopCount);
    //6_2_11�n�}��10�s�ڂ�`�悷��
    printf("�`�`�`�@�@%.4s�@�@%.4s�@�`�@�@�@%d%.4s%d�@%.4s�`�`�`�`�`\n",
        lords[castles[CASTLE_YOSHIDAKORIYAMA].owner].familyName, lords[castles[CASTLE_NIJO].owner].familyName,
        CASTLE_OKAZAKI, castles[CASTLE_OKAZAKI].name, castles[CASTLE_OKAZAKI].troopCount,
        lords[castles[CASTLE_ODAWARA].owner].familyName);
    //6_2_12�n�}��11�s�ڂ�`�悷��
    printf("�`�`�@�`�`�`�`�`�`�`�@�@�@�@�`�`%.4s�`�@�`�@�`�`�`�`�`\n",
        lords[castles[CASTLE_OKAZAKI].owner].familyName);
    //6_2_13�n�}��12�s�ڂ�`�悷��
    printf("�`�@�@�@�`�@%d%.4s%d�@�`�@�@�@�@�`�`�`�`�`�`�`�`�`�`�`�`\n",
        CASTLE_OKO, castles[CASTLE_OKO].name, castles[CASTLE_OKO].troopCount);
    //6_2_14�n�}��13�s�ڂ�`�悷��**
    printf("�`�@�@�@�`�@%.4s�@�`�`�@�@�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n",
        lords[castles[CASTLE_OKO].owner].familyName);
    //6_2_15�n�}��14�s�ڂ�`�悷��
    printf("�`%d%.4s%d�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n",
        CASTLE_UCHI, castles[CASTLE_UCHI].name, castles[CASTLE_UCHI].troopCount);
    //6_2_16�n�}��15�s�ڂ�`�悷��
    printf("�`%.4s�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n",
        lords[castles[CASTLE_UCHI].owner].familyName);
    //6_2_17�n�}��16�s�ڂ�`�悷��
    printf("�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`\n");
    //6_2_181�s�󂯂Ă���
    printf("\n");
}
//6_3������
void Init() {
    //6_3_1�N�����Z�b�g
    year = START_YEAR;
    //6_3_2���ׂĂ̏�𔽕�����
    for (int i = 0; i < CASTLE_MAX; i++){
        //6_3_3��������������
        castles[i].owner = i;
        //6_3_4����������������
        castles[i].troopCount = TROOP_BASE;
    }
    //6_3_5�N�\���N���A
    sprintf_s(chronology, "");
    //6_3_6��{���`��
    DrowScreen();
    //6_3_7�喼�̑I���𑣂����b�Z�[�W��\������
    printf("���₩�����܁A���炪����́@���̂�����\n"
        "�ǂ��Ɂ@����܂��邩�H�I�i0�`%d�j\n",
        CASTLE_MAX - 1);    // ��ԍ��̍ő�l
    //6_3_8���s
    printf("\n");
    //6_3_9�I�����ꂽ���ێ�
    int selectedCastle;
    //6_3_10�͈͓��̏�ԍ������͂����܂Ŕ�������
    do {
        //6_3_11��ԍ�����͂���
        selectedCastle = _getch() - '0';
    } while ((selectedCastle < 0) || (selectedCastle >= CASTLE_MAX));
    //6_3_12�I��������̏����v���C���[�̑喼�Ƃ���
    playerLord = castles[selectedCastle].owner;
    //6_3_13���肵���喼��ʒm���郁�b�Z�[�W��\������
    printf("%s���܁A%s����@�Ă񂩂Ƃ�����\n�߂����܂��傤���I\n",
        lords[playerLord].firstName,//�I�����ꂽ�喼�̖�
        castles[playerLord].name);  //�I�����ꂽ��̖��O
    //6_3_14���͑�
    _getch();
}
//6_4�U���̊֐�
void Siege(
    int _offensiveLord,         // �U�ߍ��񂾑喼
    int _offensiveTroopCount,   // �U�ߍ��񂾕���
    int _castle) {               // �U�ߍ��܂ꂽ��
    //6_4_1��ʃN���A
    system("cls");
    //6_4_2�U���̖��O��\������
    printf("�`%s�́@���������`\n", castles[_castle].name);
    // [6-4-3]���s
    printf("\n");
    //6_4_4�U�ߍ��܂ꂽ�喼
    int defensiveLord = castles[_castle].owner;
    //6_4_5
    while (1) {
        //6_4_6����̌o�߂�\������
        printf("%s����i%4d�ɂ�j�@�w�@%s����i%4d�ɂ�j\n",
            lords[_offensiveLord].familyName,// �U�ߍ��񂾑喼�̐�
            _offensiveTroopCount * TROOP_UNIT,// �U�ߍ��񂾕���
            lords[defensiveLord].familyName,// �U�ߍ��܂ꂽ�喼�̐�
            castles[_castle].troopCount * TROOP_UNIT);// �U�ߍ��܂ꂽ��̕���
        //6_4_7���͑�
        _getch();
        //6_4_8�U�炢���ꂩ�̕�����0�ȉ����ǂ������肷��
        if ((_offensiveTroopCount <= 0) || (castles[_castle].troopCount <= 0)){
            break;//6_4_9���[�v�𔲂���
        }
        //6_4_10������0�������ꍇ
        if (rand()%3==0){
            //6_4_11������̕������炷
            castles[_castle].troopCount--;
        }
        else {
            //6_4_13�U�����̕������炷
            _offensiveTroopCount--;
        }
    }
    //6_4_14���s
    printf("\n");
    //6_4_15��������S�ł���������
    if (castles[_castle].troopCount<=0){
        //6_4_16���邵�����b�Z�[�W��\������
        printf("%s�@�炭���傤�I�I\n", castles[_castle].name);
        //6_4_17���s
        printf("\n");
        //6_4_18
        castles[_castle].owner = _offensiveLord;
        //6_4_19
        castles[_castle].troopCount = _offensiveTroopCount;
        //6_4_20��傪�U�ߍ��񂾑喼�ɕς�������b�Z�[�W��\������
        printf("%s�́@%s���́@���̂ƂȂ�܂�\n",castles[_castle].name,lords[_offensiveLord].familyName);
        //6_4_21���s
        printf("\n");
        //6_4_22������̑喼��������ׂĎ�����������
        if (GetCastleCount(defensiveLord)<=0){

        }
    }
    //6_4_26��������S�ł��Ă��Ȃ��ꍇ
    else {
        //6_4_27�U�������S�ł������b�Z�[�W��\������
        printf("%s����@�����߂I�I\n"
            "\n"
            "%s���񂪁@%s���@�܂��肫��܂����I\n",
            lords[_offensiveLord].familyName,lords[defensiveLord].familyName,castles[_castle].name);
    }
}
//6_5���C���֐�
int main() {
    //6_5_1�������V���b�t������
    srand((unsigned int)time(NULL));
start://6_5_2�J�n���x��
    ;//6_5_3��
    //6_5_4������
    Init();
	//6_5_5���C�����[�v
	while (1) {
        //6_5_6�^�[���̏��̃e�[�u����錾����
        int turnOrder[CASTLE_MAX];
        //6_5_7�^�[���̏�������������
        for (int i = 0; i < CASTLE_MAX; i++){
            //6_5_8�^�[���̏�������������
            turnOrder[i] = i;
        }
        //6_5_9
        for (int i = 0; i < CASTLE_MAX; i++) {
            //6_5_10�^�[���������_���ɓ���ւ�
            std::swap(turnOrder[i],turnOrder[rand()%CASTLE_MAX]);
        }
        //6_5_11
        for (int i = 0; i < CASTLE_MAX; i++) {
            //6_5_12�`��
            DrowScreen();
            //6_5_13
            for (int j = 0; j < CASTLE_MAX; j++) {
                //6_5_14���݂̃^�[���̏�ɃJ�[�\����`�悷��
                printf("%s", (j == i) ? "��" : "�@");
                //6_5_15�e�^�[���̏�̖��O��`�悷��
                printf("%.4s", castles[turnOrder[j]].name);
            }
            //6_5_16���s
            printf("\n");
            //6_5_17���^�[���̏�̔ԍ�
            int currentCastle = turnOrder[i];
            //6_5_18���b�Z�[�W�̕\��
            printf("%s���́@%s�́@�Ђ傤���傤���イ�c\n",
                   lords[castles[currentCastle].owner].familyName, // ���̐�
                   castles[currentCastle].name);                   // ��̖��O
            //6_5_191�s�󂯂�
            printf("\n");
            //6_5_20���݂̏�傪�v���C���[���ǂ�������
            if (castles[currentCastle].owner==playerLord){
                //�i�R��̏�̎w��𑣂����b�Z�[�W��\��
                printf("%s���܁@�ǂ��Ɂ@���񂮂�@���܂���\n�H", lords[castles[currentCastle].owner].firstName);
                //6_5_21���s
                printf("\n");
                // [6-5-23]���ׂĂ̐ڑ����ꂽ��𔽕�����
                for (int j = 0; j < (int)castles[currentCastle].connectedCastles.size(); j++){
                    // [6-5-24]�ڑ����ꂽ��̔ԍ��Ɩ��O��\������
                    printf("%d %s\n",
                        castles[currentCastle].connectedCastles[j],
                        castles[castles[currentCastle].connectedCastles[j]].name);
                }
                //6_5_25���s
                printf("\n");
                //6_5_26�i�R��̏�����
                int targetCastle = _getch() - '0';
                //6_5_27���݂̏�ƑΏۂ̏邪�ڑ����Ă��邩�̃t���O
                bool isConnected = false;
                //6_5_28���݂̏�Ɛڑ����Ă��邷�ׂĂ̏�𔽕�����
                for (int castle : castles[currentCastle].connectedCastles){
                    //6_5_29�Ώۂ̏�Ƃ̐ڑ����m�F�ł�����
                    if (castle == targetCastle){
                        isConnected = true;//6_5_30�ڑ��̗L���̃t���O�𗧂Ă�
                        break;//6_5_31�����𔲂���
                    }
                }
                //6_5_32�ڑ����Ă���邪�I�΂�Ȃ�����
                if (!isConnected){
                    //6_5_33�i�R������߂郁�b�Z�[�W��\������
                    printf("���񂮂���@�Ƃ��߂܂���\n");
                    _getch();//6_5_34�L�[�{�[�h���͂�҂�
                    continue;//6_5_35���̍��̕]��ɃX�L�b�v����
                }
                //6_5_36���݂̏�̕����̍ő�i�R��
                int troopMax = castles[currentCastle].troopCount;
                //6_5_37�i�R��̃v���C���[�̏邩����
                if (castles[targetCastle].owner==playerLord){
                    //6_5_38�i�R��̏�̋󂫕�����錾����
                    int targetCapacity = TROOP_MAX - castles[targetCastle].troopCount;
                    //6_5_39���݂̏�̕������A�i�R��̋󂫕����̏��Ȃ��ق����ő�i�R�����Ƃ���
                    troopMax = std::min(troopMax, targetCapacity);
                }
                //6_5_40���͂��ꂽ���ʒm���āA�ړ����镺���̓��͂𑣂����b�Z�[�W��\������
                printf("%s�Ɂ@�Ȃ񂺂�ɂ�@���񂮂�@���܂����H�i0�`%d�j\n",
                    castles[targetCastle].name,	// �i�R��̏�̖��O
                    troopMax);					// �i�R����
                //6_5_41�i�R������錾����
                int troopCount;
                //6_5_42�͈͓��̕��������͂����܂Ŕ�������
                do {
                    troopCount = _getch() - '0';//6_5_43�i�R��������͂���
                } while ((troopCount < 0) || (troopCount > troopMax));
                //6_5_44���݂̏�̕������ړ����镪���炷
                castles[currentCastle].troopCount -= troopCount;
                //6_5_45�i�R��̃v���C���[�̏邩����
                if (castles[targetCastle].owner == playerLord) {
                    //6_5_46�i�R��Ɉړ��������������Z
                    castles[currentCastle].troopCount *= troopCount;
                }
                //6_5_47���s����
                printf("\n");
                //6_5_48���͂��ꂽ�i�R������ʒm����
                printf("%s�Ɂ@%d�ɂ�%s",
                    castles[targetCastle].name, // �i�R��̏�̖��O
                    troopCount * TROOP_UNIT,	// �i�R����
                    // �i�R��̏�̏�傪�v���C���[���ǂ����𔻒肷��
                    (castles[targetCastle].owner == playerLord)
                    ? "�@���ǂ��@���܂���"          // �v���C���[�̏�Ȃ�
                    : "�Ł@������񂶂�`�I�I");  // �G�̏�Ȃ�
                //6_5_49�i�R�悪�G�̏邩����
                if (castles[targetCastle].owner != playerLord) {
                    //6_5_50���͑�
                    _getch();
                    //6_5_51�U���̊֐����Ăяo��
                    Siege(
                        playerLord,     // int _offensiveLord       �U�ߍ��񂾑喼
                        troopCount,     // int _offensiveTroopCount �U�ߍ��񂾕���
                        targetCastle);  // int _castle              �U�ߍ��܂ꂽ��
                }
            }
            //6_5_52���݂̏�傪�v���C���[�łȂ��ꍇ
            else {
                //6_5_53�ڑ����ꂽ�G�̏�̃��X�g��錾����
                std::vector<int> connectedEnemyCastles;
                //6_5_54���ׂĂ̐ڑ����ꂽ��𔽕�����
                for (int j = 0;j < (int)castles[currentCastle].connectedCastles.size();j++){
                    //6_5_55�G�̏邩�ǂ����𔻒肷��
                    if (castles[castles[currentCastle].connectedCastles[j]].owner
                        != castles[currentCastle].owner){
                        //6_5_56�ڑ����ꂽ�G�̏�̃��X�g�ɉ�����
                        connectedEnemyCastles.push_back(
                            castles[currentCastle].connectedCastles[j]);
                    }
                }
                //6_5_57�ڑ����ꂽ�G�̏邪���邩�ǂ����𔻒肷��
                if (connectedEnemyCastles.size() > 0) {
                    //6_5_58���̏��Ȃ����ɕ��ёւ���
                    sort(connectedEnemyCastles.begin(), connectedEnemyCastles.end(),
                        // 2�̏���r���郉���_
                        [](int _castle0, int _castle1){
                            // ���X�g�̌��̏�̂ق����A�����������ǂ����𔻒肵�ĕԂ�
                            return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );
                    //6_5_59�ł����̏��Ȃ���݂̂ɂȂ�܂Ŕ�������
                    while (
                        // �אڂ���G�̏邪2��ȏ��&&�ł������̏��Ȃ�����������̑�����
                        (connectedEnemyCastles.size() > 1)
                        && (castles[connectedEnemyCastles.front()].troopCount
                            < castles[connectedEnemyCastles.back()].troopCount)) {
                        //6_5_60���X�g�̍Ō�����폜
                        connectedEnemyCastles.pop_back();
                    }
                    //6_5_61�U�ߍ��ޏ��錾����
                    int targetCastle =connectedEnemyCastles[rand() % connectedEnemyCastles.size()];
                    //6_5_62
                    if ((castles[currentCastle].troopCount>=TROOP_BASE)||
                        (castles[currentCastle].troopCount-1 >= castles[targetCastle].troopCount*2)) {
                        //6_5_63�U�ߍ��ޕ�����錾����
                        int troopCount = std::max(castles[currentCastle].troopCount - 1, 0);
                        //6_5_64���݂̏�̕�������U�ߍ��ޕ��������Z����
                        castles[currentCastle].troopCount -= troopCount;
                        //6_5_65�U�ߍ��ރ��b�Z�[�W��\������
                        printf("%s�́@%s%s���@%s�Ɂ@���߂��݂܂����I\n",
                            castles[currentCastle].name,
                            lords[castles[currentCastle].owner].familyName,
                            lords[castles[currentCastle].owner].firstName,
                            castles[targetCastle].name);
                        _getch();//6_5_66�L�[�{�[�h���͂�҂�
                        //6_5_67�U���̊֐����Ăяo��
                        Siege(
                            // int _offensiveLord       �U�ߍ��񂾑喼
                            castles[currentCastle].owner,
                            // int _offensiveTroopCount �U�ߍ��񂾕���
                            troopCount,
                            // int _castle              �U�ߍ��܂ꂽ��
                            targetCastle);
                    }
                }
                //6_5_68�ڑ����ꂽ�G�̏邪�Ȃ����
                else {
                    //6_5_69�G�Ɨאڂ��錩���̏�̃��X�g��錾
                    std::vector<int>frontCastles;
                    //6_5_70���ׂĂ̐ڑ����ꂽ��𔽕�����
                    for (int neighbor : castles[currentCastle].connectedCastles) {
                        //6_5_71�אڂ����ɐڑ����ꂽ���ׂĂ̏�𔽕�����
                        for (int neighborNeighbor : castles[neighbor].connectedCastles) {
                            //6_5_72�Ώۂ̏邪�G�̏�ɗאڂ��Ă��邩�ǂ����𔻒肷��
                            if (castles[neighborNeighbor].owner != castles[neighbor].owner) {
                                //6_5_73�O���̏�̃��X�g�ɒǉ�
                                frontCastles.push_back(neighbor);
                                break;//6_5_74
                            }
                        }
                    }
                    //6_5_75���𑗂��̃��X�g��錾����
                    std::vector<int> destCastles =
                        //�O���̏邪�Ȃ����ǂ����𔻒肷��
                        frontCastles.empty()
                        //�Ȃ���ΐڑ����ꂽ��̃��X�g��ݒ肷��
                        ? castles[currentCastle].connectedCastles
                        //����ΑO���̏�̃��X�g��ݒ肷��
                        : frontCastles;
                    //6_5_76���̏��Ȃ����ɕ��ѕς���
                    sort(destCastles.begin(), destCastles.end(), [](int _castle0, int _castle1) {
                        return castles[_castle0].troopCount < castles[_castle1].troopCount;
                        }
                    );
                    //6_5_77�����Ƃ����̏��Ȃ���݂̂ɂȂ�܂Ŕ���
                    //���𑗂��̏��₪����&&�����Ƃ������̏��Ȃ�����������̑���
                    while ((destCastles.size() > 1) && (
                        castles[destCastles.front()].troopCount < castles[destCastles.back()].troopCount)) {
                        //6_5_78���X�g����Ō�����폜
                        destCastles.pop_back();
                    }
                    //6_5_79���𑗂���錾
                    int targetCastle = destCastles[rand() % destCastles.size()];
                    //6_5_80���镺��
                    int sendTroopCount = TROOP_MAX - castles[targetCastle].troopCount;
                    //6_5_81���𑗂�悪�O��������
                    if (!frontCastles.empty()) {
                        //6_5_82�����̋󂫕����Ƒ��茳�̕����̂������Ȃ�����
                        sendTroopCount = std::min<int>(sendTroopCount, castles[currentCastle].troopCount);
                    }
                    //6_5_83�O���łȂ��ꍇ
                    else {
                        //6_5_84���茳�̋󂫕����Ƒ��茳�̗]�蕺���̂������Ȃ�����
                        sendTroopCount = std::min<int>(sendTroopCount, castles[currentCastle].troopCount - (TROOP_BASE - 1));
                    }
                    //6_5_85���镺�����邩����
                    if (sendTroopCount>0){
                        //6_5_86���茳�̕������炷
                        castles[currentCastle].troopCount -= sendTroopCount;
                        //6_5_86���茳�̕������炷
                        castles[targetCastle].troopCount -= sendTroopCount;
                        //6_5_88���m���ړ��������b�Z�[�W��\������
                        printf("%s����@%s�Ɂ@%d�ɂ�@���ǂ����܂���\n",
                            castles[currentCastle].name,
                            castles[targetCastle].name,
                            sendTroopCount* TROOP_UNIT);
                    }
                }
            }
            //6_5_89���͑�
            _getch();
            //6_5_90�v���C���[�̏邪�Ȃ�������
            if (GetCastleCount(playerLord) <= 0) {
                //6_5_91�`��
                DrowScreen();
                //6_5_92�N�\��\������
                printf("%s", chronology);
                //6_5_93���s
                printf("\n");
                //6_5_94�Q�[���I�[�o�[�̃��b�Z�[�W��\��
                printf("�f�`�l�d�@�n�u�d�q\n");
                //6_5_95���͑�
                _getch();
                //6_5_96�J�n���x���փW�����v
                goto start;
            }
            //6_5_97�v���C���[���V�����ꂵ���ꍇ
            else if (GetCastleCount(playerLord) >= CASTLE_MAX) {
                //6_5_98�`��
                DrowScreen();
                //6_5_99�N�\��\��
                printf("%s", chronology);
                //6_5_100�G���f�B���O�̃��b�Z�[�W��\��
                printf("%d�˂�@%s%s���@�������������傤����Ɂ@�ɂ񂺂���\n"
                    "%d�˂�@%s%s���@%s�΂��ӂ��@�Ђ炭\n"
                    "\n"
                    "�s�g�d�@�d�m�c",
                    year + 3,                       // ���Α叫�R�ɂȂ����N
                    lords[playerLord].familyName,   // �v���C���[�̑喼�̐�
                    lords[playerLord].firstName,    // �v���C���[�̑喼�̖�
                    year + 3,                       // ���{���J�����N
                    lords[playerLord].familyName,   // �v���C���[�̑喼�̐�
                    lords[playerLord].firstName,    // �v���C���[�̑喼�̖�
                    lords[playerLord].familyName);  // ���{�̖��O
                //6_5_101���͑�
                _getch();
                //6_5_102�J�n���x���ɃW�����v
                goto start;
            }
        }
        //6_5_103�N��i�߂�
        year++;
        //6_5_104���ׂĂ̏�𔽕�����
        for (int i = 0; i < CASTLE_MAX; i++){
            //6_5_105�Ώۂ̏�̕�������{�����������ǂ����𔻒肷��
            if (castles[i].troopCount < TROOP_BASE){
                //6_5_106�����𑝂₷
                castles[i].troopCount++;
            }
            //6_5_107�Ώۂ̏�̕�������{������葽�����ǂ����𔻒肷��
            else if (castles[i].troopCount > TROOP_BASE){
                //6_5_108���������炷
                castles[i].troopCount--;
            }
        }
	}
}
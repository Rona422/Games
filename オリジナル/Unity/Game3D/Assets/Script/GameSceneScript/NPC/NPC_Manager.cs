using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class NPC_Manager : MonoBehaviour
{
    //　TODO: クラス化(優先度低
    //NPCに参照させるデータ群
    private List<Vector3> _npcPosList = new List<Vector3>();
    public List<Vector3> npcPosList
    {
        get
        {
            if (_npcPosList == null)
            {
                _npcPosList = new List<Vector3>();
            }
            return _npcPosList;
        }
    }
    private List<Vector3> _npcRotList = new List<Vector3>();
    public List<Vector3> npcRotList
    {
        get
        {
            if (_npcRotList == null)
            {
                _npcRotList = new List<Vector3>();
            }
            return _npcRotList;
        }
    }
    private bool[][] _npcSelectAction;
    public bool[][] npcSelectAction
    {
        get
        {
            return _npcSelectAction;
        }
    }
    private int _npcListNum = 0;
    public int npcListNum
    {
        get
        {
            return _npcListNum;
        }
    }
    //[HideInInspector]
    public GameObject npc;
    void Awake()
    {
        //NPCデータ初期化
        {
            //座標リストの初期化
            {
                Vector3[] a = {
                //本棚前
                new Vector3(-1.58f,9.82f,49.285f),
                new Vector3(-1.58f,9.82f,45.0f),
                new Vector3(-1.58f,9.82f,41.5f),
                new Vector3(-1.58f,9.82f,35.0f),
                new Vector3(6.3f,9.92f,48.34f),
                new Vector3(6.3f,9.92f,44.8f),
                new Vector3(6.3f,9.92f,42.0f),
                new Vector3(6.3f,9.92f,38.17f),
                new Vector3(4.0f,5.0f,23.48f),
                new Vector3(11.94f,5.0f,16.33f),

                new Vector3(11.94f,5.0f,13.67f),
                new Vector3(8.5f,5.0f,19.7f),
                new Vector3(2.24f,5.0f,16.9f),
                new Vector3(2.5f,5.0f,6.77f),
                new Vector3(2.24f,5.0f,-5.0f),
                new Vector3(14.0f,0.0f,1.6f),
                new Vector3(29.7f,0.0f,4.9f),
                new Vector3(18.0f,0.0f,8.59f),
                new Vector3(20.0f,0.0f,8.59f),
                new Vector3(22.0f,0.0f,8.59f),

                new Vector3(15.721f,0.0f,-3.77f),
                new Vector3(32.9f,0.0f,-10.2f),
                new Vector3(7.56f,0.0f,10.28f),
                new Vector3(6.0f,0.0f,-14.6f),
                new Vector3(37.17f,5.0f,-25.0f),
                new Vector3(38.7f,5.0f,-5.0f),
                new Vector3(35.73f,5.0f,-15.0f),
                new Vector3(26.79f,5.0f,-23.0f),
                new Vector3(32.39f,5.0f,-27.44f),
                new Vector3(40.9f,5.0f,-39.31f),

                new Vector3(43.3f,5.0f,2.45f),
                new Vector3(43.3f,5.0f,10.04f),
                new Vector3(42.0f,5.0f,16.35f),
                new Vector3(38.32f,5.0f,17.51f),
                new Vector3(35.92f,5.0f,13.73f),
                new Vector3(35.92f,5.0f,6.33f),
                new Vector3(40.27f,10.0f,-46.93f),
                new Vector3(40.0f,10.0f,-53.35f),
                new Vector3(34.0f,10.0f,-43.0f),
                new Vector3(34.0f,10.0f,-46.69f),

                new Vector3(34.0f,10f,-50.88f),
                new Vector3(34.0f,9.82f,-56.5f),
                new Vector3(-23.0f,0.0f,-8.5f),
                new Vector3(-23.0f,0.0f,-13.41f),
                new Vector3(-8.14f,0.0f,-16.73f),
                new Vector3(5.84f,5.0f,31.32f),
                new Vector3(-14.39f,0.0f,-13.57f),
                new Vector3(-34.68f,0.0f,-14.42f),
                new Vector3(-29.4f,0.0f,-8.93f),
                new Vector3(-29.4f,0.0f,-3.95f),

                new Vector3(-29.4f,0.0f,1.03f),
                new Vector3(-31.37f,0.0f,4.9f),
                new Vector3(-35.8f,0.0f,3.59f),
                new Vector3(-37.0f,0.0f,1.43f),
                new Vector3(-37.0f,0.0f,-1.6f),
                new Vector3(-37.0f,0.0f,-6.58f),
                new Vector3(-15.4f,0.0f,4.78f),
                new Vector3(-11.22f,0.0f,5.44f),
                new Vector3(-16.6f,0.0f,0.16f),
                new Vector3(-16.6f,0.0f,-5.1f),

                new Vector3(-9.2f,0.0f,2.23f),
                new Vector3(-9.2f,0.0f,-2.78f),
                new Vector3(-9.2f,0.0f,-7.83f),
                new Vector3(-40.0f,0.0f,6.8f),
                new Vector3(-23f,0.0f,-24.73f),
                new Vector3(-3.83f,0.0f,-24.0f),
                new Vector3(-7.34f,0.0f,-23.02f),
                new Vector3(-17.16f,0.0f,-23.0f),
                new Vector3(-17.16f,0.0f,-53.64f),
                new Vector3(-17.93f,0.0f,-51.1f),

                new Vector3(-19.59f,0.0f,-49.0f),
                new Vector3(-14.58f,0.0f,-47.81f),
                new Vector3(-35.1f,0.0f,-28.35f),
                new Vector3(-33.18f,0.0f,-30.16f),
                new Vector3(-31.23f,0.0f,-27.83f),
                new Vector3(-38.15f,0.0f,-47.58f),
                new Vector3(-35.15f,0.0f,-45.85f),
                new Vector3(-37.79f,0.0f,-50.95f),
                new Vector3(-18.62f,0.0f,10.27f),
                new Vector3(10.4f,5.15f,-6.0f),

                new Vector3(25.0f,5.15f,-6.0f),
            };
                _npcPosList.AddRange(a);
            }
            //座標別向きリストの初期化
            {
                Vector3[] a =
                {
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,0.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,0.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,245.0f,0.0f),
                new Vector3(0.0f,245.0f,0.0f),
                new Vector3(0.0f,0.0f,0.0f),
                new Vector3(0.0f,-70.0f,0.0f),
                new Vector3(0.0f,160.0f,0.0f),

                new Vector3(0.0f,50.0f,0.0f),
                new Vector3(0.0f,140.0f,0.0f),
                new Vector3(0.0f,90.0f,0.0f),
                new Vector3(0.0f,90.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,70.0f,0.0f),
                new Vector3(0.0f,-70.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),

                new Vector3(0.0f,120.0f,0.0f),
                new Vector3(0.0f,300.0f,0.0f),
                new Vector3(0.0f,110.0f,0.0f),
                new Vector3(0.0f,100.0f,0.0f),
                new Vector3(0.0f,280.0f,0.0f),
                new Vector3(0.0f,270.0f,0.0f),
                new Vector3(0.0f,270.0f,0.0f),
                new Vector3(0.0f,270.0f,0.0f),
                new Vector3(0.0f,300.0f,0.0f),
                new Vector3(0.0f,320.0f,0.0f),

                new Vector3(0.0f,290.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,225.0f,0.0f),
                new Vector3(0.0f,350.0f,0.0f),
                new Vector3(0.0f,90.0f,0.0f),
                new Vector3(0.0f,90.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,0.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,48.0f,0.0f),

                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,0.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),
                new Vector3(0.0f,0.0f,0.0f),
                new Vector3(0.0f,-14.15f,0.0f),
                new Vector3(0.0f,220.0f,0.0f),
                new Vector3(0.0f,50.0f,0.0f),
                new Vector3(0.0f,50.0f,0.0f),
                new Vector3(0.0f,300.0f,0.0f),
                new Vector3(0.0f,240.0f,0.0f),

                new Vector3(0.0f,300.0f,0.0f),
                new Vector3(0.0f,310.0f,0.0f),
                new Vector3(0.0f,60.0f,0.0f),
                new Vector3(0.0f,110.0f,0.0f),
                new Vector3(0.0f,70.0f,0.0f),
                new Vector3(0.0f,90.0f,0.0f),
                new Vector3(0.0f,50.0f,0.0f),
                new Vector3(0.0f,320.0f,0.0f),
                new Vector3(0.0f,100.0f,0.0f),
                new Vector3(0.0f,80.0f,0.0f),

                new Vector3(0.0f,260.0f,0.0f),
                new Vector3(0.0f,280.0f,0.0f),
                new Vector3(0.0f,320.0f,0.0f),
                new Vector3(0.0f,150.0f,0.0f),
                new Vector3(0.0f,150.0f,0.0f),
                new Vector3(0.0f,240.0f,0.0f),
                new Vector3(0.0f,300.0f,0.0f),
                new Vector3(0.0f,210.0f,0.0f),
                new Vector3(0.0f,30.0f,0.0f),
                new Vector3(0.0f,45.0f,0.0f),

                new Vector3(0.0f,60.0f,0.0f),
                new Vector3(0.0f,350.0f,0.0f),
                new Vector3(0.0f,280.0f,0.0f),
                new Vector3(0.0f,100.0f,0.0f),
                new Vector3(0.0f,60.0f,0.0f),
                new Vector3(0.0f,-130.0f,0.0f),
                new Vector3(0.0f,-130.0f,0.0f),
                new Vector3(0.0f,-110.0f,0.0f),
                new Vector3(0.0f,205.0f,0.0f),
                new Vector3(0.0f,180.0f,0.0f),

                new Vector3(0.0f,180.0f,0.0f),
            };
                _npcRotList.AddRange(a);
            }
            _npcListNum = _npcPosList.Count;
            //アニメーション選択肢の初期化
            {
                //読書,睡眠,食事,騒ぎ,傍観
                _npcSelectAction = new bool[_npcListNum][];
                {
                    //0~9
                    {
                        npcSelectAction[0] = new bool[] { true, true, false, false, true };
                        npcSelectAction[1] = new bool[] { true, true, false, false, true };
                        npcSelectAction[2] = new bool[] { true, true, false, false, true };
                        npcSelectAction[3] = new bool[] { false, true, false, false, true };
                        npcSelectAction[4] = new bool[] { false, true, false, false, true };
                        npcSelectAction[5] = new bool[] { true, true, false, false, true };
                        npcSelectAction[6] = new bool[] { true, true, false, false, true };
                        npcSelectAction[7] = new bool[] { true, true, false, false, true };
                        npcSelectAction[8] = new bool[] { false, false, false, true, true };
                        npcSelectAction[9] = new bool[] { true, true, true, true, true };
                    }
                    //10~19
                    {
                        npcSelectAction[10] = new bool[] { true, true, true, true, true };
                        npcSelectAction[11] = new bool[] { true, true, false, true, true };
                        npcSelectAction[12] = new bool[] { false, false, false, true, true };
                        npcSelectAction[13] = new bool[] { false, false, false, false, true };
                        npcSelectAction[14] = new bool[] { true, false, false, true, true };
                        npcSelectAction[15] = new bool[] { true, false, false, true, true };
                        npcSelectAction[16] = new bool[] { true, false, false, true, true };
                        npcSelectAction[17] = new bool[] { true, true, false, true, true };
                        npcSelectAction[18] = new bool[] { true, true, false, true, true };
                        npcSelectAction[19] = new bool[] { true, true, false, true, true };
                    }
                    //20~29
                    {
                        npcSelectAction[20] = new bool[] { true, true, false, false, false };
                        npcSelectAction[21] = new bool[] { true, true, false, false, false };
                        npcSelectAction[22] = new bool[] { true, true, true, false, false };
                        npcSelectAction[23] = new bool[] { true, true, true, true, false };
                        npcSelectAction[24] = new bool[] { false, false, false, true, true };
                        npcSelectAction[25] = new bool[] { false, true, false, false, true };
                        npcSelectAction[26] = new bool[] { false, false, false, false, true };
                        npcSelectAction[27] = new bool[] { true, true, true, false, true };
                        npcSelectAction[28] = new bool[] { false, true, false, false, true };
                        npcSelectAction[29] = new bool[] { true, true, false, false, true };
                    }
                    //3false~39
                    {
                        npcSelectAction[30] = new bool[] { false, false, true, true, true };
                        npcSelectAction[31] = new bool[] { false, false, true, true, true };
                        npcSelectAction[32] = new bool[] { false, false, true, true, true };
                        npcSelectAction[33] = new bool[] { false, true, true, true, true };
                        npcSelectAction[34] = new bool[] { false, false, true, true, true };
                        npcSelectAction[35] = new bool[] { false, false, true, true, true };
                        npcSelectAction[36] = new bool[] { true, true, false, false, true };
                        npcSelectAction[37] = new bool[] { true, true, false, false, true };
                        npcSelectAction[38] = new bool[] { true, false, false, false, true };
                        npcSelectAction[39] = new bool[] { true, true, false, false, true };
                    }
                    //4false~49
                    {
                        npcSelectAction[40] = new bool[] { true, true, false, false, true };
                        npcSelectAction[41] = new bool[] { true, true, false, false, true };
                        npcSelectAction[42] = new bool[] { true, false, false, false, false };
                        npcSelectAction[43] = new bool[] { false, false, false, false, true };
                        npcSelectAction[44] = new bool[] { true, false, false, true, true };
                        npcSelectAction[45] = new bool[] { true, true, false, false, false };
                        npcSelectAction[46] = new bool[] { true, false, false, true, true };
                        npcSelectAction[47] = new bool[] { true, false, false, true, true };
                        npcSelectAction[48] = new bool[] { false, false, true, true, false };
                        npcSelectAction[49] = new bool[] { false, false, true, true, false };
                    }
                    //5false~59
                    {
                        npcSelectAction[50] = new bool[] { false, false, true, true, false };
                        npcSelectAction[51] = new bool[] { true, false, true, false, false };
                        npcSelectAction[52] = new bool[] { false, false, true, true, true };
                        npcSelectAction[53] = new bool[] { false, false, true, true, false };
                        npcSelectAction[54] = new bool[] { false, false, true, true, false };
                        npcSelectAction[55] = new bool[] { false, false, true, true, false };
                        npcSelectAction[56] = new bool[] { false, false, true, true, true };
                        npcSelectAction[57] = new bool[] { false, false, true, true, true };
                        npcSelectAction[58] = new bool[] { false, false, true, true, false };
                        npcSelectAction[59] = new bool[] { false, false, true, true, false };
                    }
                    //6false~69
                    {
                        npcSelectAction[60] = new bool[] { false, false, true, true, false };
                        npcSelectAction[61] = new bool[] { false, false, true, true, false };
                        npcSelectAction[62] = new bool[] { false, false, true, true, false };
                        npcSelectAction[63] = new bool[] { false, false, false, false, true };
                        npcSelectAction[64] = new bool[] { true, true, false, true, true };
                        npcSelectAction[65] = new bool[] { true, true, false, false, false };
                        npcSelectAction[66] = new bool[] { true, true, false, false, false };
                        npcSelectAction[67] = new bool[] { true, true, false, true, true };
                        npcSelectAction[68] = new bool[] { false, true, false, false, false };
                        npcSelectAction[69] = new bool[] { false, true, false, false, false };
                    }
                    //7false~79
                    {
                        npcSelectAction[70] = new bool[] { false, true, false, false, false };
                        npcSelectAction[71] = new bool[] { true, true, false, false, true };
                        npcSelectAction[72] = new bool[] { true, true, true, false, true };
                        npcSelectAction[73] = new bool[] { false, false, true, true, true };
                        npcSelectAction[74] = new bool[] { true, true, false, true, true };
                        npcSelectAction[75] = new bool[] { true, true, false, false, true };
                        npcSelectAction[76] = new bool[] { true, true, false, false, true };
                        npcSelectAction[77] = new bool[] { false, false, false, false, true };
                        npcSelectAction[78] = new bool[] { true, true, false, false, true };
                        npcSelectAction[79] = new bool[] { false, true, true, false, true };
                    }
                    //8false~
                    {
                        npcSelectAction[80] = new bool[] { false, true, true, false, true };
                    }
                }
            }
        }
    }
    //　TODO: カメラを発見したNPCに注目
    void Start()
    {
        //　TODO:NPCの生成数の設定
        //～500
        for (int i = 0; i <50; i++)
        {
            Instantiate(npc);
        }
    }
}

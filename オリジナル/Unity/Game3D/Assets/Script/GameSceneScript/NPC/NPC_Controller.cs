using Cinemachine;
using NUnit.Framework;

using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UIElements;
using static TMPro.SpriteAssetUtilities.TexturePacker_JsonArray;
public class NPC_Controller : MonoBehaviour
{
    private NPC_Manager NPCM;
    //追いかける自身
    [HideInInspector]
    public NavMeshAgent _navMeshAgent;
    //自身の死体
    [HideInInspector]
    public GameObject _deadNPC;
    //アクションで使う小道具
    [HideInInspector]
    public GameObject books;
    [HideInInspector]
    public GameObject sleeps;
    [HideInInspector]
    public SleepUpdate sleep;
    //[HideInInspector]
    public GameObject meats;
    [HideInInspector]
    public GameObject talks;
    //[HideInInspector]
    public GameObject waits;
    //攻撃用武器
    [HideInInspector]
    public GameObject ax;
    //発見時リアクション
    [HideInInspector]
    public GameObject Call;
    //現在使用可能なアクションリスト
    private List<int> boolNum = new List<int>();
    //目的地到達からの待機時間
    private float waitTime;
    //目的地到達からの待機時間計測
    private float waitTimeCount;
    //追いかける対象座標
    private int targetPos;
    //プレイヤー
    private GameObject _player;
    // Start is called before the first frame update
    void Start()
    {
        GameObject obj = GameObject.Find("NPC_Manager");
        NPCM = obj.GetComponent<NPC_Manager>();
        _player = GameObject.Find("Player");
        //座標リストの添え字の初期値
        targetPos = Random.Range(0, NPCM.npcListNum -1);
        //待機時間計測用変数初期化
        waitTimeCount = .0f;
        waitTime = 5.0f;
        //初期位置はランダム
        this.transform.position = NPCM.npcPosList[targetPos];
    }
    void Update()
    {
        //プレイヤーが指名手配中なら
        if (_player.GetComponent<Player_Controller>().lynch)
        {
            //プレイヤー追いかけ行動規則
            NpcAlgorithmAttack();
        }
        else
        {
            //プレイヤーが罪を犯していたら...
            if (_player.GetComponent<Player_Controller>().sinGuilty)
            {
                RaycastHit hit;
                Physics.Raycast(this.transform.position, (_player.transform.position + _player.transform.up * 0.9f) - this.transform.position, out hit);
                //プレイヤーに視線が通っていたら...
                if (hit.collider.gameObject.tag == "Player")
                {
                    //プレイヤーとの距離で警戒度を上げる
                    float distance = Vector3.Distance(_player.transform.position, this.transform.position);
                    if (_player.GetComponent<Player_Controller>().SetWarning(distance))
                    {
                        Call.SetActive(true);
                    }
                    //一度警戒度を上げたらプレイヤーの罪の清算終了
                    _player.GetComponent<Player_Controller>().SetGuilty(false);
                }
            }
            //通常行動規則
            NpcAlgorithm();

        }
    }
    private void NpcAlgorithmAttack()
    {
        //アニメーション停止
        stopAnim();
        //プレイヤーの方へ移動
        _navMeshAgent.SetDestination(_player.transform.position);
        //一定の距離内にプレイヤーがいたら攻撃
        if (Vector3.Distance(this.transform.position,_player.transform.position) <= 5.0f)
        {
            //超斧斬
            if (!ax.activeInHierarchy)
            {
                //斧の初期位置をリセット
                ax.transform.position = transform.position + transform.right * -0.35f + transform.up * 1.4f + transform.forward * 0.45f;
                ax.transform.localEulerAngles = new Vector3(-40.0f, -22.0f, 8.1f);
                ax.SetActive(true);
            }
        }
    }
    private void NpcAlgorithm()
    {
        //目的地へ移動
        _navMeshAgent.SetDestination(NPCM.npcPosList[targetPos]);
        //目的地に近づいたら…
        if (Vector3.Distance(this.transform.position, NPCM.npcPosList[targetPos]) <= 2.0f)
        {
            //　TODO: 向きを滑らかに更新
            this.transform.localEulerAngles = NPCM.npcRotList[targetPos];
            //待機モーション開始
            if (waitTimeCount == .0f)
            {
                //アクションリストのtrueの添え字を保存
                for (int i = 0; i < 5; i++)
                {
                    if (NPCM.npcSelectAction[targetPos][i])
                    {
                        boolNum.Add(i);
                    }
                }
                //使用可能アクションリストからランダムで実行
                switch (boolNum[Random.Range(0, boolNum.Count)])
                {
                    case 0://読書
                        books.SetActive(true);
                        waitTime = 15.0f;
                        break;
                    case 1://睡眠
                        sleep.SleepTimeTime = 0.0f;
                        sleeps.SetActive(true);
                        waitTime = 12.0f;
                        break;
                    //　TODO: NPCの食事アクション
                    case 2://食事
                        meats.SetActive(true);
                        waitTime = 8.0f;
                        break;
                    case 3://騒ぎ
                        talks.SetActive(true);
                        waitTime = 9.0f;
                        break;
                    //　TODO: NPCの傍観アクション
                    case 4://傍観
                        waits.SetActive(true);
                        waitTime = 5.0f;
                        break;
                }
            }
            //待機時間計測更新
            waitTimeCount += Time.deltaTime;
            //待機時間が終わっていれば
            if (waitTimeCount >= waitTime)
            {
                //目的地の更新
                targetPos = Random.Range(0, NPCM.npcListNum - 1);
                //アニメーション停止
                stopAnim();
                //諸々初期化
                waitTimeCount = 0;
                boolNum.Clear();
            }
        }
    }
    public void stopAnim()
    {
        //アニメーション停止
        books.SetActive(false);
        sleeps.SetActive(false);
        meats.SetActive(false);
        talks.SetActive(false);
        waits.SetActive(false);
    }
    public void deadNPC()
    {
        Destroy(this.gameObject);
        _deadNPC.transform.position = this.transform.position;
        Instantiate(_deadNPC);
    }
}
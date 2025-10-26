using Cinemachine;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
public class Player_Controller : MonoBehaviour
{
    //自身のRigidbody
    private Rigidbody _rb;
    public Rigidbody rb
    {
        get
        {
            if (_rb == null)
            {
                _rb = GetComponent<Rigidbody>();
            }
            return _rb;
        }
    }
    //通常フォルム
    [HideInInspector]
    public GameObject defaultBody;
    //殺戮フォルム
    [HideInInspector]
    public GameObject killerBody;
    //燃え尽きフォルム
    [HideInInspector]
    public GameObject deadBody;
    //終了時のカメラ
    [HideInInspector]
    public GameObject endAngle;
    //メインで使うカメラについているUI
    [HideInInspector]
    public GameObject mainUI;
    //視点軸用
    [HideInInspector]
    public GameObject playerAnglePoint;
    private Player_Angle _playerAnglePoint;
    //移動用
    private Player_Move _playerMove;
    //アクション選択ウィンドウ
    [HideInInspector]
    public GameObject ActionChoice;
    //今選択中のアクションを表示
    [HideInInspector]
    public List<GameObject> nowAction = new List<GameObject>(4);
    //アクションで使う小道具
    [HideInInspector]
    public GameObject actionAx;
    //選択中のアクション
    private int nowActionNum;
    //プレイヤーが罪を犯したかどうか
    private bool _sinGuilty;
    public bool sinGuilty
    {
        get { return _sinGuilty; }
    }
    //プレイヤーが指名手配されているかどうか
    private bool _lynch;
    public bool lynch
    {
        get { return _lynch; }
    }
    //プレイヤーが指名手配されるまでの警戒度(100で指名手配
    private int _warningCount;
    public int warningCount
    {
        get { return _warningCount; }
    }
    private void Start()
    {
        //操作系
        {
            _rb = GetComponent<Rigidbody>();
            _playerAnglePoint = playerAnglePoint.GetComponent<Player_Angle>();
            _playerMove = GetComponent<Player_Move>();
            endAngle.GetComponent<CinemachineVirtualCamera>().Priority = 0;
        }
        //罪系
        {
            _sinGuilty = false;
            _lynch = false;
            _warningCount = 0;
        }
        nowActionNum = 0;
    }
    private void Update()
    {
        //座標操作
        _playerMove.PlayerMoveUpdate();
        //視点操作
        PlayerAngleUpdate();
        //アクション操作
        PlayerAction();
    }
    private void PlayerAngleUpdate()
    {
        if (Input.GetMouseButton(1))
        {
            float y = Input.GetAxis("Mouse X");
            this.transform.localEulerAngles += new Vector3(0.0f, y * 2.0f, 0.0f);
            _playerAnglePoint.PlayerAngleUpdateX(Input.GetAxis("Mouse Y"));
        }
    }
    private void PlayerActionChoice()
    {
        //Eで選択ウィンドウ表示
        if (Input.GetKeyDown(KeyCode.E))
        {
            ActionChoice.SetActive(true);
        }
        //離したら非表示
        if (Input.GetKeyUp(KeyCode.E))
        {
            nowAction[nowActionNum].SetActive(false);
            nowActionNum = ActionChoice.GetComponent<ActionChoice>().GetNowAction();
            nowAction[nowActionNum].SetActive(true);
            ActionChoice.SetActive(false);
        }
    }
    private void PlayerAction()
    {
        //アクション選択
        PlayerActionChoice();
        //　TODO: アクションの作りこみ
        //アクション開始
        if (Input.GetMouseButton(0))
        {
            //選択中のアクションで分岐
            switch (nowActionNum)
            {
                //斧
                case 0:
                    _sinGuilty = false;
                    if (Input.GetMouseButtonDown(0))
                    {
                        //斧を取り出す
                        actionAx.SetActive(true);
                        //斧の初期位置をリセット
                        actionAx.transform.position = transform.position + transform.right * -0.35f + transform.up * 1.4f + transform.forward * 0.45f;
                        actionAx.transform.localEulerAngles = new Vector3(-40.0f, -22.0f, 8.1f);
                        _sinGuilty = true;
                    }
                    break;
                //食事
                case 1:
                    break;
                //魔法(優先度低
                case 2:
                    break;
                //呼寄(優先度低
                case 3:
                    break;
                default:
                    break;
            }
        }
    }
    //死んだときの処理
    public void deadPlayer()
    {
        //死体化
        defaultBody.SetActive(false);
        killerBody.SetActive(false);
        deadBody.SetActive(true);
        _rb.constraints= RigidbodyConstraints.None;
        //死亡カメラに切り替え
        mainUI.SetActive(false);
        endAngle.GetComponent<CinemachineVirtualCamera>().Priority = 99;
    }
    //有罪判決
    public void SetGuilty(bool b)
    {
        _sinGuilty = b;
    }
    //警戒度設定
    public bool SetWarning(float distans)
    {
        //warningCount更新
        if ((int)distans < 10)
        {
            _warningCount += 100;
        }
        else
        {
            _warningCount += 100 - (int)distans;
        }
        //_lynch判定&_warningCount上限
        if (_warningCount >= 100)
        {
            _warningCount = 100;
            return true;
        }
        return false;
    }
    //リンチ確定
    public void LetGoLynch()
    {
        _lynch = true;
    }
}

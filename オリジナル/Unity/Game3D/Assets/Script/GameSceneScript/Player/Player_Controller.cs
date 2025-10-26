using Cinemachine;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
public class Player_Controller : MonoBehaviour
{
    //���g��Rigidbody
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
    //�ʏ�t�H����
    [HideInInspector]
    public GameObject defaultBody;
    //�E�C�t�H����
    [HideInInspector]
    public GameObject killerBody;
    //�R���s���t�H����
    [HideInInspector]
    public GameObject deadBody;
    //�I�����̃J����
    [HideInInspector]
    public GameObject endAngle;
    //���C���Ŏg���J�����ɂ��Ă���UI
    [HideInInspector]
    public GameObject mainUI;
    //���_���p
    [HideInInspector]
    public GameObject playerAnglePoint;
    private Player_Angle _playerAnglePoint;
    //�ړ��p
    private Player_Move _playerMove;
    //�A�N�V�����I���E�B���h�E
    [HideInInspector]
    public GameObject ActionChoice;
    //���I�𒆂̃A�N�V������\��
    [HideInInspector]
    public List<GameObject> nowAction = new List<GameObject>(4);
    //�A�N�V�����Ŏg��������
    [HideInInspector]
    public GameObject actionAx;
    //�I�𒆂̃A�N�V����
    private int nowActionNum;
    //�v���C���[���߂�Ƃ������ǂ���
    private bool _sinGuilty;
    public bool sinGuilty
    {
        get { return _sinGuilty; }
    }
    //�v���C���[���w����z����Ă��邩�ǂ���
    private bool _lynch;
    public bool lynch
    {
        get { return _lynch; }
    }
    //�v���C���[���w����z�����܂ł̌x���x(100�Ŏw����z
    private int _warningCount;
    public int warningCount
    {
        get { return _warningCount; }
    }
    private void Start()
    {
        //����n
        {
            _rb = GetComponent<Rigidbody>();
            _playerAnglePoint = playerAnglePoint.GetComponent<Player_Angle>();
            _playerMove = GetComponent<Player_Move>();
            endAngle.GetComponent<CinemachineVirtualCamera>().Priority = 0;
        }
        //�ߌn
        {
            _sinGuilty = false;
            _lynch = false;
            _warningCount = 0;
        }
        nowActionNum = 0;
    }
    private void Update()
    {
        //���W����
        _playerMove.PlayerMoveUpdate();
        //���_����
        PlayerAngleUpdate();
        //�A�N�V��������
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
        //E�őI���E�B���h�E�\��
        if (Input.GetKeyDown(KeyCode.E))
        {
            ActionChoice.SetActive(true);
        }
        //���������\��
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
        //�A�N�V�����I��
        PlayerActionChoice();
        //�@TODO: �A�N�V�����̍�肱��
        //�A�N�V�����J�n
        if (Input.GetMouseButton(0))
        {
            //�I�𒆂̃A�N�V�����ŕ���
            switch (nowActionNum)
            {
                //��
                case 0:
                    _sinGuilty = false;
                    if (Input.GetMouseButtonDown(0))
                    {
                        //�������o��
                        actionAx.SetActive(true);
                        //���̏����ʒu�����Z�b�g
                        actionAx.transform.position = transform.position + transform.right * -0.35f + transform.up * 1.4f + transform.forward * 0.45f;
                        actionAx.transform.localEulerAngles = new Vector3(-40.0f, -22.0f, 8.1f);
                        _sinGuilty = true;
                    }
                    break;
                //�H��
                case 1:
                    break;
                //���@(�D��x��
                case 2:
                    break;
                //�Ċ�(�D��x��
                case 3:
                    break;
                default:
                    break;
            }
        }
    }
    //���񂾂Ƃ��̏���
    public void deadPlayer()
    {
        //���̉�
        defaultBody.SetActive(false);
        killerBody.SetActive(false);
        deadBody.SetActive(true);
        _rb.constraints= RigidbodyConstraints.None;
        //���S�J�����ɐ؂�ւ�
        mainUI.SetActive(false);
        endAngle.GetComponent<CinemachineVirtualCamera>().Priority = 99;
    }
    //�L�ߔ���
    public void SetGuilty(bool b)
    {
        _sinGuilty = b;
    }
    //�x���x�ݒ�
    public bool SetWarning(float distans)
    {
        //warningCount�X�V
        if ((int)distans < 10)
        {
            _warningCount += 100;
        }
        else
        {
            _warningCount += 100 - (int)distans;
        }
        //_lynch����&_warningCount���
        if (_warningCount >= 100)
        {
            _warningCount = 100;
            return true;
        }
        return false;
    }
    //�����`�m��
    public void LetGoLynch()
    {
        _lynch = true;
    }
}

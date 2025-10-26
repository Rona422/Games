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
    //�ǂ������鎩�g
    [HideInInspector]
    public NavMeshAgent _navMeshAgent;
    //���g�̎���
    [HideInInspector]
    public GameObject _deadNPC;
    //�A�N�V�����Ŏg��������
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
    //�U���p����
    [HideInInspector]
    public GameObject ax;
    //���������A�N�V����
    [HideInInspector]
    public GameObject Call;
    //���ݎg�p�\�ȃA�N�V�������X�g
    private List<int> boolNum = new List<int>();
    //�ړI�n���B����̑ҋ@����
    private float waitTime;
    //�ړI�n���B����̑ҋ@���Ԍv��
    private float waitTimeCount;
    //�ǂ�������Ώۍ��W
    private int targetPos;
    //�v���C���[
    private GameObject _player;
    // Start is called before the first frame update
    void Start()
    {
        GameObject obj = GameObject.Find("NPC_Manager");
        NPCM = obj.GetComponent<NPC_Manager>();
        _player = GameObject.Find("Player");
        //���W���X�g�̓Y�����̏����l
        targetPos = Random.Range(0, NPCM.npcListNum -1);
        //�ҋ@���Ԍv���p�ϐ�������
        waitTimeCount = .0f;
        waitTime = 5.0f;
        //�����ʒu�̓����_��
        this.transform.position = NPCM.npcPosList[targetPos];
    }
    void Update()
    {
        //�v���C���[���w����z���Ȃ�
        if (_player.GetComponent<Player_Controller>().lynch)
        {
            //�v���C���[�ǂ������s���K��
            NpcAlgorithmAttack();
        }
        else
        {
            //�v���C���[���߂�Ƃ��Ă�����...
            if (_player.GetComponent<Player_Controller>().sinGuilty)
            {
                RaycastHit hit;
                Physics.Raycast(this.transform.position, (_player.transform.position + _player.transform.up * 0.9f) - this.transform.position, out hit);
                //�v���C���[�Ɏ������ʂ��Ă�����...
                if (hit.collider.gameObject.tag == "Player")
                {
                    //�v���C���[�Ƃ̋����Ōx���x���グ��
                    float distance = Vector3.Distance(_player.transform.position, this.transform.position);
                    if (_player.GetComponent<Player_Controller>().SetWarning(distance))
                    {
                        Call.SetActive(true);
                    }
                    //��x�x���x���グ����v���C���[�̍߂̐��Z�I��
                    _player.GetComponent<Player_Controller>().SetGuilty(false);
                }
            }
            //�ʏ�s���K��
            NpcAlgorithm();

        }
    }
    private void NpcAlgorithmAttack()
    {
        //�A�j���[�V������~
        stopAnim();
        //�v���C���[�̕��ֈړ�
        _navMeshAgent.SetDestination(_player.transform.position);
        //���̋������Ƀv���C���[��������U��
        if (Vector3.Distance(this.transform.position,_player.transform.position) <= 5.0f)
        {
            //�����a
            if (!ax.activeInHierarchy)
            {
                //���̏����ʒu�����Z�b�g
                ax.transform.position = transform.position + transform.right * -0.35f + transform.up * 1.4f + transform.forward * 0.45f;
                ax.transform.localEulerAngles = new Vector3(-40.0f, -22.0f, 8.1f);
                ax.SetActive(true);
            }
        }
    }
    private void NpcAlgorithm()
    {
        //�ړI�n�ֈړ�
        _navMeshAgent.SetDestination(NPCM.npcPosList[targetPos]);
        //�ړI�n�ɋ߂Â�����c
        if (Vector3.Distance(this.transform.position, NPCM.npcPosList[targetPos]) <= 2.0f)
        {
            //�@TODO: ���������炩�ɍX�V
            this.transform.localEulerAngles = NPCM.npcRotList[targetPos];
            //�ҋ@���[�V�����J�n
            if (waitTimeCount == .0f)
            {
                //�A�N�V�������X�g��true�̓Y������ۑ�
                for (int i = 0; i < 5; i++)
                {
                    if (NPCM.npcSelectAction[targetPos][i])
                    {
                        boolNum.Add(i);
                    }
                }
                //�g�p�\�A�N�V�������X�g���烉���_���Ŏ��s
                switch (boolNum[Random.Range(0, boolNum.Count)])
                {
                    case 0://�Ǐ�
                        books.SetActive(true);
                        waitTime = 15.0f;
                        break;
                    case 1://����
                        sleep.SleepTimeTime = 0.0f;
                        sleeps.SetActive(true);
                        waitTime = 12.0f;
                        break;
                    //�@TODO: NPC�̐H���A�N�V����
                    case 2://�H��
                        meats.SetActive(true);
                        waitTime = 8.0f;
                        break;
                    case 3://����
                        talks.SetActive(true);
                        waitTime = 9.0f;
                        break;
                    //�@TODO: NPC�̖T�σA�N�V����
                    case 4://�T��
                        waits.SetActive(true);
                        waitTime = 5.0f;
                        break;
                }
            }
            //�ҋ@���Ԍv���X�V
            waitTimeCount += Time.deltaTime;
            //�ҋ@���Ԃ��I����Ă����
            if (waitTimeCount >= waitTime)
            {
                //�ړI�n�̍X�V
                targetPos = Random.Range(0, NPCM.npcListNum - 1);
                //�A�j���[�V������~
                stopAnim();
                //���X������
                waitTimeCount = 0;
                boolNum.Clear();
            }
        }
    }
    public void stopAnim()
    {
        //�A�j���[�V������~
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
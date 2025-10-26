using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static UnityEditor.Experimental.GraphView.GraphView;

public class NPC_LookKill : MonoBehaviour
{
    //�v���C���[
    private GameObject _player;
    //BGM�������Ă�I�u�W�F�N�g
    private GameObject BgmObj;
    //���L����
    [HideInInspector]
    public GameObject _npc;
    //���ꔭ�����̃J����
    [HideInInspector]
    public GameObject killLookCamera;
    //�ߖ̉�
    [HideInInspector]
    public AudioClip scream;
    [HideInInspector]
    public AudioClip scream2;
    //����BGM
    public AudioClip Bgm2;
    //���C���̃J�����ł����g��Ȃ�UI
    private GameObject mainUI;
    //�E�Q����
    private float killTime;
    //����
    private bool screamT;
    void Start()
    {
        _player = GameObject.Find("Player");
        BgmObj = GameObject.Find("MainCamera");
        mainUI = GameObject.Find("MainCameraImage");
        killTime = 0.0f;
        screamT = true;
    }
    void Update()
    {
        if (killTime == 0.0f)
        {
            _npc.GetComponent<NPC_Controller>().stopAnim();
            BgmObj.GetComponent<AudioSource>().Stop();
            mainUI.SetActive(false);
            killLookCamera.SetActive(true);
            screamT = true;
            killTime = Time.time;
        }
        else if (Time.time > killTime + 4.0f)
        {
            //���Ԍo�߂Ŏ��_��߂��ă����`�J�n
            killTime = 0.0f;
            _player.GetComponent<Player_Controller>().LetGoLynch();
            BgmObj.GetComponent <AudioSource>().PlayOneShot(Bgm2);
            BgmObj.GetComponent<AudioSource>().Play();
            this.gameObject.SetActive(false);
        }
        else if (Time.time > killTime + 3.0f)
        {
            killLookCamera.SetActive(false);
            mainUI.SetActive(true);
        }
        else if (screamT&&Time.time > killTime + 0.8f)
        {
            //�ߖ�
            GetComponent<AudioSource>().PlayOneShot(Random.Range(0,1) == 0 ? scream : scream2);
            screamT = false;
        }
    }
}
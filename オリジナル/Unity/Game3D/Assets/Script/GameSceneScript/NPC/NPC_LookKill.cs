using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static UnityEditor.Experimental.GraphView.GraphView;

public class NPC_LookKill : MonoBehaviour
{
    //プレイヤー
    private GameObject _player;
    //BGMを持ってるオブジェクト
    private GameObject BgmObj;
    //自キャラ
    [HideInInspector]
    public GameObject _npc;
    //現場発見時のカメラ
    [HideInInspector]
    public GameObject killLookCamera;
    //悲鳴の音
    [HideInInspector]
    public AudioClip scream;
    [HideInInspector]
    public AudioClip scream2;
    //第二のBGM
    public AudioClip Bgm2;
    //メインのカメラでしか使わないUI
    private GameObject mainUI;
    //殺害時刻
    private float killTime;
    //叫び
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
            //時間経過で視点を戻してリンチ開始
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
            //悲鳴
            GetComponent<AudioSource>().PlayOneShot(Random.Range(0,1) == 0 ? scream : scream2);
            screamT = false;
        }
    }
}
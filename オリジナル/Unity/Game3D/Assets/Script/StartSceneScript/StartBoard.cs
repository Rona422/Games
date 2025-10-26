using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
public class StartBoard : BaseScene
{
    //StartBoardに移されるアイコン
    [HideInInspector]
    public GameObject Text;
    //ゲームスタートの音
    [HideInInspector]
    public AudioClip startSound;
    //カメラ
    [HideInInspector]
    public GameObject mainCamera;
    AudioSource audioSource;
    //Helpを一度でも見たかどうか
    private bool helpEnd;
    //スタートが有効化されてからの時間計測
    private float flashTime;
    //スタートが押された時間
    private float clickTime;
    void Start()
    {
        helpEnd = false;
        flashTime = 0.0f;
        clickTime = 0.0f;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        //ヘルプが押されていたら
        if (helpEnd)
        {
            //ヘルプが押されてからの時間を計測
            flashTime += Time.deltaTime;
            //ヘルプが押されて3秒経っていたら
            if (flashTime>=3.0f)
            {
                //スタートボード上のものを一秒間隔で点滅
                if ((int)flashTime % 2 == 0)
                {
                    Text.SetActive(false);
                }
                else if ((int)flashTime % 2 == 1)
                {
                    Text.SetActive(true);
                }
            }
            //スタートボードを押されていたら
            if (clickTime != 0.0f)
            {
                //シーンが切り替わるまでカメラを動かす
                mainCamera.transform.position += new Vector3(-0.04f,0,0);
                mainCamera.transform.localEulerAngles += new Vector3(0,0,2.6f);
                //スタートボードを押された3秒後にシーンの切り替え
                if (flashTime - clickTime >= 2.5f)
                {
                    SceneManager.LoadScene("GameScene");
                }
            }
        }
    }
    void OnMouseOver()
    {
        //ヘルプを見て3秒以上立っていたら
        if (flashTime >= 3.0f)
        {
            //一度目のクリックである時
            if (clickTime == 0.0f)
            {
                //左クリックを押したら
                if (Input.GetMouseButtonDown(0))
                {

                    //シーン推移の準備
                    audioSource.PlayOneShot(startSound);
                    clickTime = flashTime;
                }
            }
        }
    }
    public void SetStartTrue()
    {
        helpEnd = true;
    }
}
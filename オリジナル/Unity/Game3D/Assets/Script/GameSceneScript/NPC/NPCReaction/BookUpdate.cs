using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class BookUpdate : MonoBehaviour
{
    //上下運動のスピード(始めは上向きに動く
    private float bookY = 0.01f;
    //上下の切り替えしタイミング観測用変数
    private float waitTimeCount = 0.0f;
    // Update is called once per frame
    void Update()
    {
        //本をふわふわさせる
        this.transform.position += new Vector3(0,bookY,0);
        //待機時間計測更新
        waitTimeCount += Time.deltaTime;
        //待機時間が終わっていれば
        if (waitTimeCount >= 0.5f)
        {
            //上下運動を反転
            bookY *= -1;
            //waitTimeCountを初期化
            waitTimeCount -= 0.5f;
        }
    }
}

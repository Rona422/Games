using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class SleepUpdate : MonoBehaviour
{
    [HideInInspector]
    public List<GameObject> sleeps = new List<GameObject>();
    [HideInInspector]
    public float SleepTimeTime = 0.0f;
    // Update is called once per frame
    void Update()
    {
        if (SleepTimeTime == 0.0f)foreach (var sleep in sleeps)sleep.SetActive(false);
        //(int)のキャストで切り捨て
        //一秒ごとに段階的に表示
        sleeps[(int)SleepTimeTime % 3].SetActive(true);
        //時間の更新
        SleepTimeTime += Time.deltaTime;
        //3秒間をループ
        if (SleepTimeTime > 3.0f)
        {
            SleepTimeTime = 0.0f;
        }
    }
}

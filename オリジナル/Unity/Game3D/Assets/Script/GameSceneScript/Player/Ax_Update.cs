using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_Ax : MonoBehaviour
{
    float deleteTime;
    void Start()
    {
        deleteTime=0.0f;
    }
    void Update()
    {
        this.transform.localEulerAngles += new Vector3(4.0f,2.1f,0.1f);
        deleteTime += Time.deltaTime;
        if (deleteTime > 0.5f)
        {
            deleteTime = 0.0f;
            this.gameObject.SetActive(false);
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NPCtxetUpdate : MonoBehaviour
{
    private GameObject GameCamera;
    private void Start()
    {
        GameCamera = GameObject.Find("MainCamera");
    }
    // Update is called once per frame
    void Update()
    {
        //吹き出しからメインカメラ方向のベクトルを取得する
        Vector3 direction = GameCamera.transform.position - this.transform.position;
        
        //吹き出しをベクトル方向に従って回転させる
        transform.rotation = Quaternion.LookRotation(direction);
    }
}

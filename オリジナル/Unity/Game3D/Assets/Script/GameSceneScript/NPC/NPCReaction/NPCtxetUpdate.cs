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
        //�����o�����烁�C���J���������̃x�N�g�����擾����
        Vector3 direction = GameCamera.transform.position - this.transform.position;
        
        //�����o�����x�N�g�������ɏ]���ĉ�]������
        transform.rotation = Quaternion.LookRotation(direction);
    }
}

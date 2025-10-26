using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class CameraCon : MonoBehaviour
{
    public character character;
    public float distans = 2.5f;
    private Vector3 mousePos;
    private float CamX;
    private void Start()
    {
        CamX = character.transform.localEulerAngles.x + 10;
    }
    // Update is called once per frame
    void Update()
    {
        transform.localEulerAngles =
            new Vector3(CamX, character.transform.localEulerAngles.y, 0f);
        Vector3 PlayerP = character.transform.position;
        Vector3 PlayerRP = new Vector3(0f, 1.5f, 0f) + -transform.forward * 7f;
        transform.position = PlayerP + PlayerRP;

    }
    private void FixedUpdate()
    {
        //éãì_ëÄçÏ
        if (Input.GetMouseButtonDown(1))
        {
            this.mousePos = Input.mousePosition;
        }
        //éãì_ëÄçÏ
        if (Input.GetMouseButton(1))
        {
            CamX += ((this.mousePos - Input.mousePosition).y) * GameManager.instance.LolLevel;
            this.mousePos = Input.mousePosition;
        }
    }
}

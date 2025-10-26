using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HelpButton : MonoBehaviour
{
    [HideInInspector]
    public GameObject HelpBoard;
    [HideInInspector]
    public GameObject StartBoard;
    private bool onButton;
    private bool isBoard;
    void Start()
    {
        onButton = false;
        isBoard = false;
    }
    void Update()
    {
        //Boardの表示or非表示
        if (isBoard)
        {
            if (HelpBoard.transform.position.z>=0f)
            {
                HelpBoard.transform.position += new Vector3(0.0f, 0.0f, -0.1f);
            }
        }
        else
        {
            if (HelpBoard.transform.position.z <= 12.0f) {
                HelpBoard.transform.position += new Vector3(0.0f, 0.0f, 0.1f);
            }
        }
        //ボタンかそれ以外か
        if (Input.GetMouseButtonDown(0))
        {
            if (onButton)
            {
                isBoard = true;
                StartBoard.GetComponent<StartBoard>().SetStartTrue();
            }
            else
            {
                isBoard = false;
            }
        }
    }
    //ボタンの上にカーソルがあるかどうかをboolに保存
    void OnMouseEnter()
    {
        onButton = true;
    }
    void OnMouseExit()
    {
        onButton = false;
    }
}

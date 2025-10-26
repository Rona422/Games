using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class ActionChoice : MonoBehaviour
{
    [HideInInspector]
    public GameObject point;
    [HideInInspector]
    public List<GameObject> actionChoiceIs = new List<GameObject>(4);
    private int nowActionNum;
    void Update()
    {
        Vector3 _point = point.transform.position;
        Vector3 mouse = Input.mousePosition;
        actionChoiceIs[0].SetActive(false);
        actionChoiceIs[1].SetActive(false);
        actionChoiceIs[2].SetActive(false);
        actionChoiceIs[3].SetActive(false);
        //ëIëíÜÇÃóìÇñæÇÈÇ≠
        //è„Ç©â∫Ç©
        if (_point.y < mouse.y)
        {
            //âEÇ©ç∂Ç©
            if (_point.x < mouse.x)
            {
                actionChoiceIs[0].SetActive(true);
                nowActionNum = 0;
            }
            else
            {
                actionChoiceIs[1].SetActive(true);
                nowActionNum = 1;
            }
        }
        else
        {
            //âEÇ©ç∂Ç©
            if (_point.x < mouse.x)
            {
                actionChoiceIs[2].SetActive(true);
                nowActionNum = 2;
            }
            else
            {
                actionChoiceIs[3].SetActive(true);
                nowActionNum = 3;
            }
        }
        
    }
    public int GetNowAction()
    {
        return nowActionNum;
    }
}

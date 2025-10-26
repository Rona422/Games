using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor.PackageManager;
using UnityEngine;
using UnityEngine.AI;
public class GameScene : BaseScene
{
    public UiCon UICon;
    public GameObject ballBase;
    [HideInInspector]
    public List<GameObject> balls;
    private float ballPutTime;
    private float ballSpan = 5f;
    private void Update()
    {
        ballPutTime += Time.deltaTime;
        if (ballPutTime >= ballSpan)
        {
            GameObject ball = Instantiate(ballBase);
            ball.gameObject.SetActive(true);
            ball.transform.position = new Vector3(Random.Range(-15f,15f),0, Random.Range(-15f, 15f));
            balls.Add(ball);
            ballPutTime -= ballSpan;
        }
    }
}
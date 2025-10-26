using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class GameManager : SingletonMonoBehaviour<GameManager>
{
    public float time = 0.00f;
    public int characterBall;
    public int enemyBall;
    public float LolLevel = 0.5f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
    }
}

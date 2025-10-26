using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UiController : MonoBehaviour
{
    private GameObject karmaGauge;
    private GameObject player;
    void Start()
    {
        player = GameObject.Find("Player");
        karmaGauge = GameObject.Find("KarmaGauge");
    }
    void Update()
    {
        karmaGauge.GetComponent<Image>().fillAmount = (float)player.GetComponent<Player_Controller>().warningCount/100.0f;
    }
}

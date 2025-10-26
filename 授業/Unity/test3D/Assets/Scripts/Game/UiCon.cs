using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class UiCon : MonoBehaviour
{
    public Text timerText;
    public Text snowText;
    public Image messageFrame;
    public Text resultText;
    public Image resultFrame;
    private CanvasGroup _resultFrameCG;
    public CanvasGroup resultFrameCG
    {
        get
        {
            if (_resultFrameCG == null)
            {
                _resultFrameCG = GetComponent<CanvasGroup>();
            }
            return _resultFrameCG;
        }
    }
    public Text messageText;
    private GameObject ball;
    private const string SELECT_YES = "->　はい\n　 いいえ";
    private const string SELECT_NO = "　　はい\n-> いいえ";
    private int selectMum = 0;
    private int selectMax = 2;
    // Update is called once per frame
    void Update()
    {
        this.timerText.text = GameManager.instance.time.ToString("f2");
        this.snowText.text = GameManager.instance.characterBall.ToString("f0");
        if (messageFrame.gameObject.activeInHierarchy)
        {
            switch (selectMum)
            {
                case 0:
                    this.messageText.text = SELECT_YES;
                    break;
                case 1:
                    this.messageText.text = SELECT_NO;
                    break;
            }
            if (Input.GetKeyDown(KeyCode.UpArrow))
            {
                selectMum--;
                selectMum %= selectMax;
            }
            else if (Input.GetKeyDown(KeyCode.DownArrow))
            {
                selectMum++;
                selectMum %= selectMax;
            }
            else if (Input.GetKeyDown(KeyCode.Return))
            {
                if (selectMum == 0)
                {
                    GameManager.instance.characterBall++;
                    Destroy(ball);
                }
                messageFrame.gameObject.SetActive(false);
            }
        }
    }
    public void getBall(GameObject _ball)
    {
        ball = _ball;
        messageFrame.gameObject.SetActive(true);
    }
    public void resultFramePlay()
    {
        if (!resultFrame.gameObject.activeInHierarchy)
        {
            resultFrame.gameObject.SetActive(true);
            resultFrameCG.alpha = 0f;
            StartCoroutine(resultFrameFadeInCoroutine());
            resultText.text = "タイム：\""+GameManager.instance.time;
        }
    }
    private IEnumerator resultFrameFadeInCoroutine()
    {

        while (resultFrameCG.alpha < 1f)
        {
            resultFrameCG.alpha += Time.deltaTime ;
            yield return null;
        }
    }
}

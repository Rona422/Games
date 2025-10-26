using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class GameDir : MonoBehaviour
{
    public ItemGene generator;
    public TextMeshProUGUI timerText;
    public TextMeshProUGUI pointText;
    private float time = 30.0f;
    private int point = 0;
    // Update is called once per frame
    void Update()
    {
        //�^�C���l�̍X�V
        this.time-=Time.deltaTime;
        //��Փx�X�V
        if(this.time < 0)
        {
            this.time = 0;
            this.generator.SetParameter(10000.0f, 0, 0);
        }
        else if (0<=this.time&&this.time<5)
        {
            this.generator.SetParameter(0.9f, -0.04f, 3);
        }
        else if (5 <= this.time && this.time < 10)
        {
            this.generator.SetParameter(0.1f, -0.04f, 2);
        }
        else if (10 <= this.time && this.time < 15)
        {
            this.generator.SetParameter(0.2f, -0.07f, 7);
        }
        else if (15 <= this.time && this.time < 22)
        {
            this.generator.SetParameter(0.6f, -0.05f, 5);
        }
        else if (22 <= this.time && this.time < 30)
        {
            this.generator.SetParameter(1.0f, -0.03f, 2);
        }
        //�^�C���e�L�X�g�X�V
        this.timerText.text=time.ToString("f1");
        //�|�C���g�e�L�X�g�X�V
        this.pointText.text = point+" point";
    }
    public void GetApple()
    {
        this.point += 100;
    }
    public void GetBomb()
    {
        this.point /= 2;
    }
}

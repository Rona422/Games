using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class Player_Angle : MonoBehaviour
{
    public void PlayerAngleUpdateX(float x)
    {
        this.transform.localEulerAngles += new Vector3(x * -2.0f, 0.0f, 0.0f);
        //-20~30‚ªãŒÀ(localEulerAngles‚Í0~360‚È‚Ì‚Å‚»‚ê‚É‡‚í‚¹‚é
        if (transform.localEulerAngles.x > 30.0f && transform.localEulerAngles.x <= 185.0f)
        {
            this.transform.localEulerAngles = new Vector3(30.0f, this.transform.localEulerAngles.y, this.transform.localEulerAngles.z);
        }
        else if (transform.localEulerAngles.x < 340.0f && transform.localEulerAngles.x > 185.0f)
        {
            this.transform.localEulerAngles = new Vector3(340.0f, this.transform.localEulerAngles.y, this.transform.localEulerAngles.z);
        }
    }
}

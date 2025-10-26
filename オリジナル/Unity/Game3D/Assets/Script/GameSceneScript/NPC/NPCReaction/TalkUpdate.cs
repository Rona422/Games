using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class TalkUpdate : MonoBehaviour
{
    [HideInInspector]
    public List<GameObject> talks = new List<GameObject>();
    private float talkTimeTime = 0;
    private float waitTime = 0.5f;
    // Update is called once per frame
    void Update()
    {
        if (talkTimeTime> waitTime*2.0f)
        {
            talkTimeTime -= waitTime * 2.0f;
        }
        if (talkTimeTime <= waitTime)
        {
            talks[0].transform.localEulerAngles = new Vector3(0, 0, 310.0f);
            talks[1].transform.localEulerAngles = new Vector3(0, 0, 100.0f);
        }
        else if (talkTimeTime <= waitTime*2.0f)
        {
            talks[0].transform.localEulerAngles = new Vector3(0, 0, 350.0f);
            talks[1].transform.localEulerAngles = new Vector3(0, 0, 130.0f);
        }
        talkTimeTime += Time.deltaTime;
    }
}
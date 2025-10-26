using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class SleepUpdate : MonoBehaviour
{
    [HideInInspector]
    public List<GameObject> sleeps = new List<GameObject>();
    [HideInInspector]
    public float SleepTimeTime = 0.0f;
    // Update is called once per frame
    void Update()
    {
        if (SleepTimeTime == 0.0f)foreach (var sleep in sleeps)sleep.SetActive(false);
        //(int)�̃L���X�g�Ő؂�̂�
        //��b���Ƃɒi�K�I�ɕ\��
        sleeps[(int)SleepTimeTime % 3].SetActive(true);
        //���Ԃ̍X�V
        SleepTimeTime += Time.deltaTime;
        //3�b�Ԃ����[�v
        if (SleepTimeTime > 3.0f)
        {
            SleepTimeTime = 0.0f;
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class BookUpdate : MonoBehaviour
{
    //�㉺�^���̃X�s�[�h(�n�߂͏�����ɓ���
    private float bookY = 0.01f;
    //�㉺�̐؂�ւ����^�C�~���O�ϑ��p�ϐ�
    private float waitTimeCount = 0.0f;
    // Update is called once per frame
    void Update()
    {
        //�{���ӂ�ӂ킳����
        this.transform.position += new Vector3(0,bookY,0);
        //�ҋ@���Ԍv���X�V
        waitTimeCount += Time.deltaTime;
        //�ҋ@���Ԃ��I����Ă����
        if (waitTimeCount >= 0.5f)
        {
            //�㉺�^���𔽓]
            bookY *= -1;
            //waitTimeCount��������
            waitTimeCount -= 0.5f;
        }
    }
}

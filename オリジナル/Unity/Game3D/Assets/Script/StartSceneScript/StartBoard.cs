using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
public class StartBoard : BaseScene
{
    //StartBoard�Ɉڂ����A�C�R��
    [HideInInspector]
    public GameObject Text;
    //�Q�[���X�^�[�g�̉�
    [HideInInspector]
    public AudioClip startSound;
    //�J����
    [HideInInspector]
    public GameObject mainCamera;
    AudioSource audioSource;
    //Help����x�ł��������ǂ���
    private bool helpEnd;
    //�X�^�[�g���L��������Ă���̎��Ԍv��
    private float flashTime;
    //�X�^�[�g�������ꂽ����
    private float clickTime;
    void Start()
    {
        helpEnd = false;
        flashTime = 0.0f;
        clickTime = 0.0f;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        //�w���v��������Ă�����
        if (helpEnd)
        {
            //�w���v��������Ă���̎��Ԃ��v��
            flashTime += Time.deltaTime;
            //�w���v���������3�b�o���Ă�����
            if (flashTime>=3.0f)
            {
                //�X�^�[�g�{�[�h��̂��̂���b�Ԋu�œ_��
                if ((int)flashTime % 2 == 0)
                {
                    Text.SetActive(false);
                }
                else if ((int)flashTime % 2 == 1)
                {
                    Text.SetActive(true);
                }
            }
            //�X�^�[�g�{�[�h��������Ă�����
            if (clickTime != 0.0f)
            {
                //�V�[�����؂�ւ��܂ŃJ�����𓮂���
                mainCamera.transform.position += new Vector3(-0.04f,0,0);
                mainCamera.transform.localEulerAngles += new Vector3(0,0,2.6f);
                //�X�^�[�g�{�[�h�������ꂽ3�b��ɃV�[���̐؂�ւ�
                if (flashTime - clickTime >= 2.5f)
                {
                    SceneManager.LoadScene("GameScene");
                }
            }
        }
    }
    void OnMouseOver()
    {
        //�w���v������3�b�ȏ㗧���Ă�����
        if (flashTime >= 3.0f)
        {
            //��x�ڂ̃N���b�N�ł��鎞
            if (clickTime == 0.0f)
            {
                //���N���b�N����������
                if (Input.GetMouseButtonDown(0))
                {

                    //�V�[�����ڂ̏���
                    audioSource.PlayOneShot(startSound);
                    clickTime = flashTime;
                }
            }
        }
    }
    public void SetStartTrue()
    {
        helpEnd = true;
    }
}
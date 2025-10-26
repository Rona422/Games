using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_Move : MonoBehaviour
{
    //���g��Rigidbody
    private Rigidbody _rb;
    public Rigidbody rb
    {
        get
        {
            if (_rb == null)
            {
                _rb = GetComponent<Rigidbody>();
            }
            return _rb;
        }
    }
    //�ʏ���s���̑��x
    private float speed;
    //�_�b�V�����̑��x
    private float runSpeed;
    //�������Ă��邩��Flag
    private bool IsRunning;
    void Start()
    {
        _rb = GetComponent<Rigidbody>();
        speed = 3.7f;
        runSpeed = 7.0f;
        IsRunning = false;
    }
    //�@TODO: �K�^�K�^�ړ�����
    //�@TODO: �m�[�}���C�Y
    public void PlayerMoveUpdate()
    {
        //���_�b�V�����Ă��邩
        IsRunning = false;
        if (Input.GetKey(KeyCode.LeftShift) || Input.GetKey(KeyCode.RightShift))
        {
            IsRunning = true;
        }
        //�����Ă��邩�ǂ������肵�đ��x����
        float targetMovingSpeed = IsRunning ? runSpeed : speed;
        _rb.velocity = new Vector3(0f, _rb.velocity.y + 0.0f, 0f);
        //wasd�l�����L�[�ŕ��ʈړ��ړ���������
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))
        {
            _rb.velocity += this.transform.forward * targetMovingSpeed;
        }
        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))
        {
            _rb.velocity += -this.transform.forward * targetMovingSpeed;
        }
        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
        {
            _rb.velocity += this.transform.right * targetMovingSpeed;
        }
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
        {
            _rb.velocity += -this.transform.right * targetMovingSpeed;
        }
        //space�ŃW�����v
        if (Input.GetKeyDown(KeyCode.Space))
        {
            _rb.velocity += this.transform.up * 6.0f;
        }

    }
}

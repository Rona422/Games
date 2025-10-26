using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_Move : MonoBehaviour
{
    //自身のRigidbody
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
    //通常歩行時の速度
    private float speed;
    //ダッシュ時の速度
    private float runSpeed;
    //今走っているかのFlag
    private bool IsRunning;
    void Start()
    {
        _rb = GetComponent<Rigidbody>();
        speed = 3.7f;
        runSpeed = 7.0f;
        IsRunning = false;
    }
    //　TODO: ガタガタ移動解消
    //　TODO: ノーマライズ
    public void PlayerMoveUpdate()
    {
        //今ダッシュしているか
        IsRunning = false;
        if (Input.GetKey(KeyCode.LeftShift) || Input.GetKey(KeyCode.RightShift))
        {
            IsRunning = true;
        }
        //走っているかどうか判定して速度を代入
        float targetMovingSpeed = IsRunning ? runSpeed : speed;
        _rb.velocity = new Vector3(0f, _rb.velocity.y + 0.0f, 0f);
        //wasd四方矢印キーで平面移動移動方向決定
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
        //spaceでジャンプ
        if (Input.GetKeyDown(KeyCode.Space))
        {
            _rb.velocity += this.transform.up * 6.0f;
        }

    }
}

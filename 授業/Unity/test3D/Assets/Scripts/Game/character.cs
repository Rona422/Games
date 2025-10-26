using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using Unity.VisualScripting;
using UnityEditor.Rendering;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UIElements;

public class character : MonoBehaviour
{
    public Bullet bulletPrefab;
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
    private Animator _animator;
    public Animator animator
    {
        get
        {
            if (_animator == null)
            {
                _animator = GetComponent<Animator>();
            }
            return _animator;
        }
    }
    private GameScene gameScene
    {
        get { return (GameScene)SceneController.instance.currentScene; }
    }
    private float Speed = 5.0f;
    private float RotationSp = 1.0f;
    private Vector3 mousePos;
    private bool[] moveFlg;

    private void Awake()
    {
        moveFlg = new bool[4];
    }
    private void FixedUpdate()
    {
        {
            int _length = animator.parameters.Length;
            for (int i = 0; i < _length; i++)
            {
                animator.SetBool(animator.parameters[i].name, false);
            }
        }
        animator.SetBool("Wait", true);
        if (!gameScene.UICon.messageFrame.gameObject.activeInHierarchy){
           
            //前へ移動
            if (Input.GetKey(KeyCode.W))
            {
                rb.velocity = transform.forward * Speed;
                animator.SetBool("Run", true);
            }
            //後ろに移動
            if (Input.GetKey(KeyCode.S))
            {
                rb.velocity = -transform.forward * (Speed / 1.5f);
                animator.SetBool("Run", true);
            }
            //右に移動
            if (Input.GetKey(KeyCode.D))
            {
                rb.velocity = transform.right * (Speed / 1.3f);
                animator.SetBool("Run", true);
            }
            //左に移動
            if (Input.GetKey(KeyCode.A))
            {
                rb.velocity = -transform.right * (Speed / 1.3f);
                animator.SetBool("Run", true);
            }
            //視点操作
            if (Input.GetMouseButtonDown(1))
            {
                this.mousePos = Input.mousePosition;
            }
            //視点操作
            if (Input.GetMouseButton(1))
            {
                this.transform.localEulerAngles =
                    new Vector3(transform.eulerAngles.x,
                    transform.eulerAngles.y - ((this.mousePos - Input.mousePosition).x) * GameManager.instance.LolLevel,
                    transform.eulerAngles.z);
                this.mousePos = Input.mousePosition;
            }
            //弾の発射
            if (Input.GetMouseButtonDown(0) && GameManager.instance.characterBall > 0)
            {
                Bullet bullet = Instantiate(bulletPrefab);
                bullet.transform.position =
                    transform.position + transform.up * 1.5f + transform.forward * 1.0f;
                bullet.transform.localEulerAngles = transform.localEulerAngles;
                bullet.Shot();
                GameManager.instance.characterBall -= 1;
            }
        }
    }
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name.Contains("Ball"))
        {
            gameScene.UICon.getBall(collision.gameObject);
        }
    }
    private void OnCollisionStay(Collision collision)
    {
        if (collision.gameObject.name.Contains("Ball"))
        {

        }
        if (collision.gameObject.name == "Cube"|| collision.gameObject.name.Contains("wall"))
        {
            //if (!NavMeshAgent.enabled)
            //{
            //    stageCollisionStayTime += Time.deltaTime;
            //    if (stageCollisionStayTime>=1f)
            //    {
            //        NavMeshAgent.enavled = true;
            //        stageCollisionStayTime = 0f;
            //    }
            //}
        }
        if (collision.gameObject.tag == "enemy")
        {
            Time.timeScale = 0f;
        }
    }
}

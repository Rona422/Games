using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.PlayerLoop;
using static UnityEngine.UI.Image;
public class Enemy : MonoBehaviour
{
    private GameScene gameScene;
    public character character;
    public Bullet bullet;
    private NavMeshAgent _navMeshAgent;
    public NavMeshAgent navMeshAgent
    {
        get
        {
            if (_navMeshAgent == null)
            {
                _navMeshAgent = GetComponent<NavMeshAgent>();
            }
            return _navMeshAgent;
        }
    }
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
    private float bulletShotTime;
    private float Stime;
    private void Start()
    {
        gameScene = (GameScene)SceneController.instance.currentScene;
    }
    private void Update()
    {
        int minDistansBall = -1;
        {
            float minDistans = float.MaxValue;
            int _length = gameScene.balls.Count;
            for (int i = 0; i < _length; i++)
            {
                GameObject currentBall = gameScene.balls[i];


                if (currentBall != null)
                {
                    float distance = Vector3.Distance(this.transform.position, currentBall.transform.position);
                    if (minDistans > distance)
                    {
                        minDistansBall = i;
                        minDistans = distance;
                    }
                }
            }
        }
        RaycastHit raycastHit;
        if (navMeshAgent.enabled)
        {
            if (Physics.SphereCast(transform.position,0.3f,character.transform.position-transform.position,out raycastHit))
            {
                if(raycastHit.collider.name=="character"&&GameManager.instance.enemyBall>0)
                {
                    navMeshAgent.SetDestination(character.transform.position);
                }
                else
                {
                    navMeshAgent.SetDestination(gameScene.balls[minDistansBall].transform.position);
                }
            }
            navMeshAgent.SetDestination(gameScene.balls[minDistansBall].transform.position);
        }
        bulletShotTime += Time.deltaTime;
        if (bulletShotTime >= 1f)
        {
            bulletShotTime = 1f;
        }
        RaycastHit hitInfo;
        if (Physics.SphereCast(transform.position, 0.5f, character.transform.position - transform.position, out hitInfo))
        {
            if (hitInfo.collider.name == "character")
            {
                if (GameManager.instance.enemyBall >0)
                {
                    Bullet crrentBullet = Instantiate(bullet);
                    bullet.transform.position =
                        transform.position + transform.up * 1.5f + transform.forward * 1.0f;
                    bullet.transform.localEulerAngles = transform.localEulerAngles;
                    bullet.Shot();
                    bulletShotTime = 0f;
                }
            }
        }
    }
    //ƒ{[ƒ‹‚ÉG‚ê‚½‚çŽæ“¾
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name.Contains("Ball"))
        {
            GameManager.instance.enemyBall ++;
            Destroy(collision.gameObject);
        }
    }
    //‰½‚©‚ÉG‚ê‚½‚çnavMeshAgent‚ðŒ³‚É–ß‚·
    private void OnCollisionStay(Collision collision)
    {
        if (this.navMeshAgent.enabled)
        {
            return;
        }
        Stime += Time.deltaTime;
        if (Stime > 0.2f)
        {
            this.navMeshAgent.enabled = true;
            Stime -= 0.2f;
        }
    }
}
//    private float Speed = 2.0f;
//    void FixedUpdate()
//    {
//        RaycastHit hitInfo;
//        if (Physics.SphereCast(transform.position, 0.5f, character.transform.position - transform.position, out hitInfo))
//        {
//            if (hitInfo.collider.name == "character")
//            {
//                this.transform.rotation =
//                    Quaternion.LookRotation(character.transform.position - this.transform.position, Vector3.up);
//            }
//            else
//            {
//                RaycastHit hitInfo2;
//                if (Physics.Raycast(transform.position, transform.forward, out hitInfo2, 2f))
//                {

//                    if (hitInfo2.collider.name.Contains("wall"))
//                    {
//                        this.transform.localEulerAngles =
//                            new Vector3(transform.localEulerAngles.x, transform.localEulerAngles.y + 5.0f, transform.localEulerAngles.z);
//                    }
//                }
//            }
//        }
//        rb.velocity = this.transform.forward * Speed;
//    }
//    private void OnCollisionEnter(Collision collision)
//    {
//        if (collision.gameObject.name == "wall")
//        {
//            transform.localEulerAngles =
//                new Vector3(transform.localEulerAngles.x, transform.localEulerAngles.y + 4f, transform.localEulerAngles.z);
//        }
//    }
//    private void OnCollisionStay(Collision collision)
//    {
//        if (collision.gameObject.name == "wall")
//        {
//            transform.localEulerAngles =
//                new Vector3(transform.localEulerAngles.x, transform.localEulerAngles.y + 4f, transform.localEulerAngles.z);
//        }
//        else
//        {
//            //transform.rotation = Quaternion.LookRotation(character.transform.position - this.transform.position, Vector3.up);
//        }
//    }
//}

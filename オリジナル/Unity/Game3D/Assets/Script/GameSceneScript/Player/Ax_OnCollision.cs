using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ax_OnCollision : MonoBehaviour
{
    private void OnCollisionEnter(Collision collision)
    {
        //���͐G�ꂽ�瑦��
        if (collision.gameObject.tag == "NPC")
        {
            collision.gameObject.GetComponent<NPC_Controller>().deadNPC();
        }
        if (collision.gameObject.tag == "Player")
        {
            collision.gameObject.GetComponent<Player_Controller>().deadPlayer();
        }
    }
}

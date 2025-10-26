using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class Bullet : MonoBehaviour
{
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
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    private void FixedUpdate()
    {

    }
    public void Shot()
    {
        rb.AddForce(transform.forward*30f, ForceMode.Impulse);
    }
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "Enemy")
        {
            Enemy currentEnemy = collision.gameObject.GetComponent<Enemy>();
            currentEnemy.navMeshAgent.enabled = false;

            Vector3 addForceXZ = (currentEnemy.transform.position - this.transform.position).normalized;
            currentEnemy.rb.AddForce(new Vector3(addForceXZ.x, 0f, addForceXZ.z) * 10f + Vector3.up * 5f, ForceMode.Impulse);
        }
        if (collision.gameObject.name == "character")
        {
            character currentCharacter = collision.gameObject.GetComponent<character>();
            //currentCharacter.navMeshAgent.enabled = false;

            Vector3 addForceXZ = (currentCharacter.transform.position - this.transform.position).normalized;
            currentCharacter.rb.AddForce(new Vector3(addForceXZ.x, 0f, addForceXZ.z) * 10f + Vector3.up * 5f, ForceMode.Impulse);
        }
        Destroy(this.gameObject);
    }
}

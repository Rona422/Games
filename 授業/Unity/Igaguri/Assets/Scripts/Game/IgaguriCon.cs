using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class IgaguriCon : MonoBehaviour
{
    private Rigidbody _rb;
    public Rigidbody rb
    {
        get
        {
            if (_rb == null)
            {
                _rb = this.GetComponent<Rigidbody>();
            }
            return _rb;
        }
    }
    // Start is called before the first frame update
    public void shot(Vector3 pos)
    {
        rb.AddForce(pos);
    }
    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.tag == "target")
        {
            GetComponent<Rigidbody>().isKinematic = true;
            GetComponent<ParticleSystem>().Play();
        }
    }
}

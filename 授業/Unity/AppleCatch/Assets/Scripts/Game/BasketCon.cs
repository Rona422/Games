using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasketCon : MonoBehaviour
{
    public GameDir director;
    public AudioClip appleSE;
    public AudioClip bombSE;
    private AudioSource aud;
    private void Start()
    {
        Application.targetFrameRate = 60;
        this.aud=GetComponent<AudioSource>();
    }
    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButton(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                float x = hit.point.x;
                float z = hit.point.z;
                if (x<-1.5f)
                {
                    x= -1.5f;
                }
                else if (x>1.5f)
                {
                    x = 1.5f;
                }
                if (z < -1.5f)
                {
                    z = -1.5f;
                }
                else if (z > 1.5f)
                {
                    z = 1.5f;
                }
                this.transform.position=new Vector3(x, 0,z);
            }
        }
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Apple")
        {
            aud.PlayOneShot(appleSE);
            this.director.GetApple();
        }
        if (other.tag == "Bomb")
        {
            aud.PlayOneShot(bombSE);
            this.director.GetBomb();
        }
        Destroy(other.gameObject);
    }
}

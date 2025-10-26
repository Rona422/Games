using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemCon : MonoBehaviour
{
    public float dropSpeed;
    // Update is called once per frame
    void Update()
    {
        this.transform.Translate(0, this.dropSpeed, 0);
        if (this.transform.position.y < -1.0f)
        {
            Destroy(this.gameObject);
        }
    }
}

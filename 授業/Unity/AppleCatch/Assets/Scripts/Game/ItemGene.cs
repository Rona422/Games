using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class ItemGene : MonoBehaviour
{
    public ItemCon applePrefab;
    public ItemCon bombPrefab;
    public float span;
    private float delta;
    private int ratio = 2;
    private float speed = -0.03f;
    // Update is called once per frame
    void Update()
    {
        this.delta += Time.deltaTime;
        if (this.delta >= this.span)
        {
            this.delta -= this.span;
            ItemCon item;
            int dice = Random.Range(0, 10);
            if (dice <= this.ratio)
            {
                item = Instantiate(this.bombPrefab);
            }
            else
            {
                item = Instantiate(this.applePrefab);
            }
            float x = Random.Range(-1f, 1f);
            float z = Random.Range(-1f, 1f);
            item.transform.position = new Vector3(x, 4, z);
            item.dropSpeed = speed;
        }
    }
    public void SetParameter(float span, float speed, int ratio)
    {
        this.span = span;
        this.speed = speed;
        this.ratio = ratio;
    }
}

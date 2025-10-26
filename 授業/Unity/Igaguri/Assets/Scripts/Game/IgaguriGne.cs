using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IgaguriGne : MonoBehaviour
{
    public IgaguriCon igaguriPrefab;
    // Start is called before the first frame update
    void Start()
    {
        
    }
    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            IgaguriCon igaguri = Instantiate(igaguriPrefab);
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            igaguri.shot(ray.direction.normalized*2000f);
        }
    }
}

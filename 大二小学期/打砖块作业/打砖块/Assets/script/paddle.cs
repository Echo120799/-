using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class paddle : MonoBehaviour
{
    public float speed;//滑块移动速度
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float x = Input.GetAxis("Horizontal");//获取横向位移
        if(x!=0)//滑块移动
        {
            Vector3 pos = transform.position;
            pos.x += x * Time.deltaTime * speed;
            transform.position = pos;
        }
    }
}

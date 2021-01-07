using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class brick: MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
     
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    void OnCollisionEnter(Collision other)//发生碰撞时，砖块销毁，检验游戏是否结束
    {
        Destroy(gameObject);
        GM.instance.check();
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ball : MonoBehaviour
{
    private Rigidbody rigidball;
    public float speed;//速度
    public Transform paddle;//滑块
    private const float Y = -6.75f;//球初始y坐标
    // Start is called before the first frame update
    void Start()
    {
        rigidball = GetComponent<Rigidbody>();
    }
    // Update is called once per frame
    void Update()
    {
       if (Input.GetMouseButtonDown(0)&& !GM.instance.isPlaying)//鼠标按下且游戏开始
        {
            Vector3 speedNormalized = new Vector3(1f, 1f, 0).normalized;//标准速度为（1,1,0）
            rigidball.velocity = speedNormalized * speed;//设定速度
            GM.instance.isPlaying = true;
        }
        if (!GM.instance.isPlaying)//游戏停止，球和滑块一起移动，y坐标为定值（滑块上方），x坐标=滑块x坐标
        {
            Vector3 pos = transform.position;
            pos.x = paddle.position.x;
            pos.y = Y;
            transform.position = pos;
        }
       

    }
   
}

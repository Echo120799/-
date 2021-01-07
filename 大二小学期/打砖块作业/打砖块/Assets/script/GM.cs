using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GM : MonoBehaviour
{
    public static GM instance;
    public bool isPlaying = false;//游戏是否开始
    public Text livetext;//生命数文字
    public int lives = 3;//生命数
    public Text congradulations;//游戏通关文字
    public Text GameOvert;//游戏失败文字
    void Awake()
    {
        instance = this;
    }
    // Start is called before the first frame update
    void Start()
    {

    }
    public void GameOver()//游戏结束
    {
        isPlaying = false;//游戏停止
        if (lives > 1)
        {
            lives = lives - 1;//剩余命数
            livetext.text = "Life:" + lives;
        }
        else
        {
            GameOvert.text = "Game Over";//三条命用完，游戏结束
            livetext.text = "Life:0";
        }
    }
    public void check()//判断通关
    {
       if(GameObject.FindObjectsOfType<brick>().Length==0)//剩余砖块数为0
        {
            congradulations.text = "Congratulations!";
        }
    }
    // Update is called once per frame
    void Update()
    {

    }

}

    


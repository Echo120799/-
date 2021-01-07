using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class menu : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {

    }
    public void Onclick()//点击按钮切换场景
    {
        SceneManager.LoadScene("game");
    }
    // Update is called once per frame
    void Update()
    {

    }

}
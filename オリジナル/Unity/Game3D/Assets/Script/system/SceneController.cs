using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneController : SingletonMonoBehaviour<SceneController>
{
    public BaseScene currentScene;

    private void Awake()
    {
        Application.targetFrameRate = 60;
    }

    public void sceneChange(string _SceneName)
    {
        SceneManager.LoadScene(_SceneName);
    }
}

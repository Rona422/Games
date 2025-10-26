using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class SingletonMonoBehaviour<T> : MonoBehaviour where T : SingletonMonoBehaviour<T>
{
    protected static T _instance;
    public static T instance
    {
        get
        {
            if (_instance == null)
            {
                GameObject thisGameObject = new GameObject();

                _instance = thisGameObject.AddComponent<T>();

                thisGameObject.name = "[" + typeof(T) + "]";

                DontDestroyOnLoad(thisGameObject);
            }

            return _instance;
        }
    }
}

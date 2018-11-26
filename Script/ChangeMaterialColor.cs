using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeMaterialColor : MonoBehaviour
{
    public Material m_Material;
    public GameObject ball;
    bool isChange = false;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void ChangeColor()
    {
        print("Change Material");
        if (isChange == false)
        {
            m_Material.color = new Color32(255, 165, 209, 255);
            isChange = true;
        }
        else
        {
            m_Material.color = new Color32(180, 255, 255, 255);
            isChange = false;
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyEvent : MonoBehaviour {

    private ChangeMaterialColor changeMaterial;

	// Use this for initialization
	void Start () {
        changeMaterial = this.GetComponent<ChangeMaterialColor>();
    }
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKeyDown(KeyCode.Space)) {
            print("change color.");
            changeMaterial.ChangeColor();
        }
	}
}

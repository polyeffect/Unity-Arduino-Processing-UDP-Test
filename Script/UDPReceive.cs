using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

public class UDPReceive : MonoBehaviour {
    private ChangeMaterialColor changeMaterial;

    // receiving Thread
    Thread thread;

    // UDP client Object
    UdpClient udp;

    //public string IP = "127.0.0.1";
    public int port;

    static readonly object lockObject = new object();
    string returnData = "";
    bool precessData = false;

	// Use this for initialization
	void Start () {
        changeMaterial = this.GetComponent<ChangeMaterialColor>();

        print("UDPRecceive Start.");
        thread = new Thread(new ThreadStart(ThreadMethod));
        thread.Start();
	}
	
	// Update is called once per frame
	void Update () {
        if (precessData) {
            lock (lockObject)
            {
                precessData = false;
                changeMaterial.ChangeColor();
                returnData = "";
            }
        }
	}

    private void ThreadMethod() {
        udp = new UdpClient(port);
        while(true) {
            IPEndPoint RemoteIPEndPoint = new IPEndPoint(IPAddress.Any, port);

            print(RemoteIPEndPoint);

            byte[] receiveBytes = udp.Receive(ref RemoteIPEndPoint);

            lock (lockObject) {
                returnData = Encoding.ASCII.GetString(receiveBytes);

                print(returnData);

                if (returnData == "acknowledged") {
                    precessData = true;
                }
            }
        }
    }

    private void OnApplicationQuit()
    {
        udp.Close();
        thread.Abort();
    }
}

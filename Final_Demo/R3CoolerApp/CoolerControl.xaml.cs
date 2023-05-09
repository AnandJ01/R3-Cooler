using System;
using System.Net.Http;
using System.Xml.Linq;

namespace R3CoolerApp;

public partial class CoolerControl : ContentPage
{
    int count = 0;

    private HttpClient service = new HttpClient();

    public CoolerControl()
	{
		InitializeComponent();
	}

    private async void Forward(object sender, EventArgs e)
    {
        await service.GetStringAsync(new Uri("http://172.20.10.7/forward"));


    }

    private async void TurnLeft(object sender, EventArgs e)
    {
        var fromServer= await service.GetStringAsync(new Uri("http://172.20.10.7/turnLeft"));
    }

    private async void StopWheels(object sender, EventArgs e)
    {
        var fromServer = await service.GetStringAsync(new Uri("http://172.20.10.7/stop"));
    }

    private async void TurnRight(object sender, EventArgs e)
    {
        var fromServer = await service.GetStringAsync(new Uri("http://172.20.10.7/turnRight"));

    }
    private async void Reverse(object sender, EventArgs e)
    {
        var fromServer = await service.GetStringAsync(new Uri("http://172.20.10.7/backward"));

    }

    private async void Open_Cooler_Door(object sender, EventArgs e)
    {
        var fromServer = await service.GetStringAsync(new Uri("http://4.tcp.ngrok.io:16420/unlock"));
        await service.GetStringAsync(new Uri("http://2.tcp.ngrok.io:16326")); 
        //await service.GetStringAsync(new Uri("http://0.tcp.ngrok.io:13957")); 
    }
}
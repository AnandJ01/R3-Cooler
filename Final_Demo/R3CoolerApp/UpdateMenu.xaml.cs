namespace R3CoolerApp;

public partial class UpdateMenu : ContentPage
{
	public UpdateMenu()
	{
        NavigationPage.SetHasBackButton(this, true);
        InitializeComponent();
    }


    private HttpClient service = new HttpClient();

    public async void cokeCheckBox(object sender, CheckedChangedEventArgs e)
    {
        if(cokeCheck.IsChecked == true)
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/cokeTrue"));
        }
        else
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/cokeFalse"));
        }
    }

    public async void drPepperCheckBox(object sender, CheckedChangedEventArgs e)
    {
        if (drPepperCheck.IsChecked == true)
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/drpepperTrue"));
        }
        else
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/drpepperFalse"));
        }
    }

    public async void mountainDewCheckBox(object sender, CheckedChangedEventArgs e)
    {
        if (mountainDewCheck.IsChecked == true)
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/mountaindewTrue"));
        }
        else
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/mountaindewFalse"));
        }
    }

    public async void pepsiCheckBox(object sender, CheckedChangedEventArgs e)
    {
        if (pepsiCheck.IsChecked == true)
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/pepsiTrue"));
        }
        else
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/pepsiFalse"));

        }
    }

    public async void rootBeerCheckBox(object sender, CheckedChangedEventArgs e)
    {
        if (rootBeerCheck.IsChecked == true)
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/rootbeerTrue"));
        }
        else
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/rootbeerFalse"));
        }
    }

    public async void spriteCheckBox(object sender, CheckedChangedEventArgs e)
    {
        if (spriteCheck.IsChecked == true)
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/spriteTrue"));
        }
        else
        {
            await service.GetStringAsync(new Uri("http://172.20.10.2/spriteFalse"));
        }
    }
}
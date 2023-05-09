namespace R3CoolerApp;

using Microsoft.Maui.Controls;

public class MainPage : ContentPage
{
    private HttpClient service = new HttpClient();

    private string tempTemperature;
    private string tempDrinksLeft;
    private string tempBattery;

    static UpdateMenu updatemenu = new UpdateMenu();

    public MainPage()
    {
        var updateMenuButton = new Button
        {
            Text = "Update Menu",
            HorizontalOptions = LayoutOptions.Center,
            VerticalOptions = LayoutOptions.Center
        };
        updateMenuButton.Clicked += Update_Menu;

        var createQRCodeButton = new Button
        {
            Text = "Create QR Code",
            HorizontalOptions = LayoutOptions.Center,
            VerticalOptions = LayoutOptions.Center
        };
        createQRCodeButton.Clicked += Create_QR_Code;

        var refreshButton = new Button
        {
            Text = "Refresh",
            ImageSource = "refreshicon.png",
            FontSize = 20,
            HorizontalOptions = LayoutOptions.Start
        };
        refreshButton.Clicked += refreshButtonClicked;

        var horizontalStackLayout = new StackLayout
        {
            Orientation = StackOrientation.Horizontal,
            Spacing = 98,
            Children =
            {
                updateMenuButton,
                createQRCodeButton
            }
        };

        var temperatureFrame = new Frame
        {
            WidthRequest = 100,
            BackgroundColor = Color.FromArgb("#9cc2e5"),
            BorderColor = Color.FromArgb("#808080"),
            Content = new StackLayout
            {
                Children =
                {
                    new Label
                    {
                        Text = tempTemperature + "°F",
                        FontSize = 29,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.Center,
                        HorizontalOptions = LayoutOptions.Center
                    },
                    new Label
                    {
                        Text = "Temperature",
                        FontSize = 10,
                        FontAttributes = FontAttributes.Bold,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.End,
                        HorizontalOptions = LayoutOptions.Center
                    }
                }
            }
        };

        var drinksLeftFrame = new Frame
        {
            WidthRequest = 100,
            BackgroundColor = Color.FromArgb("#9cc2e5"),
            BorderColor = Color.FromArgb("#808080"),
            Content = new StackLayout
            {
                Children =
                {
                    new Label
                    {
                        Text = tempDrinksLeft,
                        FontSize = 29,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.Center,
                        HorizontalOptions = LayoutOptions.Center
                    },
                    new Label
                    {
                        Text = "Drinks Left",
                        FontSize = 10,
                        FontAttributes = FontAttributes.Bold,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.End,
                        HorizontalOptions = LayoutOptions.Center
                    }
                }
            }
        };

        var batteryFrame = new Frame
        {
            WidthRequest = 100,
            BackgroundColor = Color.FromArgb("#9cc2e5"),
            BorderColor = Color.FromArgb("#808080"),
            Content = new StackLayout
            {
                Children =
                {
                    new Label
                    {
                        Text = tempBattery + "%",
                        FontSize = 29,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.Center,
                        HorizontalOptions = LayoutOptions.Center
                    },
                    new Label
                    {
                        Text = "Battery",
                        FontSize = 10,
                        FontAttributes = FontAttributes.Bold,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.End,
                        HorizontalOptions = LayoutOptions.Center
                    }
                }
            }
        };


        var hstact = new HorizontalStackLayout
        {
            Padding = new Thickness(35,0,0,0),
            Spacing = 50,
            Children =
            {
                temperatureFrame,
                drinksLeftFrame
                //batteryFrame
            }
        };

        var grid = new Grid
        {
            Margin = new Thickness(0, 0, 10, 0),
            ColumnDefinitions =
            {
                new ColumnDefinition { Width = new GridLength(100, GridUnitType.Absolute) }
            },
            RowDefinitions =
            {
                new RowDefinition { Height = new GridLength(100, GridUnitType.Absolute) }
            }
            
        };

        grid.Children.Add(hstact);

        var image = new Image
        {
            Margin = 0,
            HeightRequest = 400,
            WidthRequest = 400,
            HorizontalOptions = LayoutOptions.Center,
            Source = ImageSource.FromFile("splash.png")
        };

        var stack = new VerticalStackLayout
        {
            Spacing = 25,
            Padding = 30,
            VerticalOptions = LayoutOptions.Center,
            Children =
            {
                horizontalStackLayout,
                grid,
                refreshButton,
                image
            }
        };

        Content = new ScrollView { Content = stack };
    }



    private async void refreshButtonClicked(object sender, EventArgs e)
    {
        //tempTemperature = await service.GetStringAsync(new Uri("http://172.20.10.5/coolerTemperature"));
        tempDrinksLeft = await service.GetStringAsync(new Uri("http://8.tcp.ngrok.io:19455/drinksLeft")); 
        //tempBattery = await service.GetStringAsync(new Uri("http://ip/battery"));

        //tempTemperature = "42";
        //tempDrinksLeft = "12";
        tempBattery = "99";

        var updateMenuButton = new Button
        {
            Text = "Update Menu",
            HorizontalOptions = LayoutOptions.Center,
            VerticalOptions = LayoutOptions.Center
        };
        updateMenuButton.Clicked += Update_Menu;

        var createQRCodeButton = new Button
        {
            Text = "Create QR Code",
            HorizontalOptions = LayoutOptions.Center,
            VerticalOptions = LayoutOptions.Center
        };
        createQRCodeButton.Clicked += Create_QR_Code;

        var refreshButton = new Button
        {
            Text = "Refresh",
            ImageSource = "refreshicon.png",
            FontSize = 20,
            HorizontalOptions = LayoutOptions.Start
        };
        refreshButton.Clicked += refreshButtonClicked;

        var horizontalStackLayout = new StackLayout
        {
            Orientation = StackOrientation.Horizontal,
            Spacing = 98,
            Children =
            {
                updateMenuButton,
                createQRCodeButton
            }
        };

        var temperatureFrame = new Frame
        {
            WidthRequest = 100,
            BackgroundColor = Color.FromArgb("#9cc2e5"),
            BorderColor = Color.FromArgb("#808080"),
            Content = new StackLayout
            {
                Children =
                {
                    new Label
                    {
                        Text = tempTemperature + "°F",
                        FontSize = 29,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.Center,
                        HorizontalOptions = LayoutOptions.Center
                    },
                    new Label
                    {
                        Text = "Temperature",
                        FontSize = 10,
                        FontAttributes = FontAttributes.Bold,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.End,
                        HorizontalOptions = LayoutOptions.Center
                    }
                }
            }
        };

        var drinksLeftFrame = new Frame
        {
            WidthRequest = 100,
            BackgroundColor = Color.FromArgb("#9cc2e5"),
            BorderColor = Color.FromArgb("#808080"),
            Content = new StackLayout
            {
                Children =
                {
                    new Label
                    {
                        Text = tempDrinksLeft,
                        FontSize = 29,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.Center,
                        HorizontalOptions = LayoutOptions.Center
                    },
                    new Label
                    {
                        Text = "Drinks Left",
                        FontSize = 10,
                        FontAttributes = FontAttributes.Bold,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.End,
                        HorizontalOptions = LayoutOptions.Center
                    }
                }
            }
        };

        var batteryFrame = new Frame
        {
            WidthRequest = 100,
            BackgroundColor = Color.FromArgb("#9cc2e5"),
            BorderColor = Color.FromArgb("#808080"),
            Content = new StackLayout
            {
                Children =
                {
                    new Label
                    {
                        Text = tempBattery + "%",
                        FontSize = 29,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.Center,
                        HorizontalOptions = LayoutOptions.Center
                    },
                    new Label
                    {
                        Text = "Battery",
                        FontSize = 10,
                        FontAttributes = FontAttributes.Bold,
                        TextColor = Color.FromArgb("#FFFFFF"),
                        VerticalOptions = LayoutOptions.End,
                        HorizontalOptions = LayoutOptions.Center
                    }
                }
            }
        };


        var hstact = new HorizontalStackLayout
        {
            Padding = new Thickness(35, 0, 0, 0),
            Spacing = 50,
            Children =
            {
                temperatureFrame,
                drinksLeftFrame
                //batteryFrame
            }
        };

        var grid = new Grid
        {
            Margin = new Thickness(0, 0, 10, 0),
            ColumnDefinitions =
            {
                new ColumnDefinition { Width = new GridLength(100, GridUnitType.Absolute) }
            },
            RowDefinitions =
            {
                new RowDefinition { Height = new GridLength(100, GridUnitType.Absolute) }
            }

        };

        grid.Children.Add(hstact);

        var image = new Image
        {
            Margin = 0,
            HeightRequest = 400,
            WidthRequest = 400,
            HorizontalOptions = LayoutOptions.Center,
            Source = ImageSource.FromFile("splash.png")
        };

        var stack = new VerticalStackLayout
        {
            Spacing = 25,
            Padding = 30,
            VerticalOptions = LayoutOptions.Center,
            Children =
            {
                horizontalStackLayout,
                grid,
                refreshButton,
                image
            }
        };

        Content = new ScrollView { Content = stack };
    }

    private async void Update_Menu(object sender, EventArgs e)
    {
        await Navigation.PushAsync(updatemenu);
    }

    private async void Create_QR_Code(object sender, EventArgs e)
    {
        await Navigation.PushAsync(new QRCodeGeneration());
    }
}

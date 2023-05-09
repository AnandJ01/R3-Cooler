namespace R3CoolerApp;

public class DrinkConsumption : ContentPage
{
    private HttpClient service = new HttpClient();

    private string tempName1;
    private string tempName2;
    private string tempName3;
    private string tempName4;
    private string tempName5;
    private string tempName6;
    private string tempName7;
    private string tempName8;
    private string tempName9;
    private string tempName10;
    private string tempName11;
    private string tempName12;
    private string tempName13;
    private string tempName14;
    private string tempName15;

    private string tempDrink1;
    private string tempDrink2;
    private string tempDrink3;
    private string tempDrink4;
    private string tempDrink5;
    private string tempDrink6;
    private string tempDrink7;
    private string tempDrink8;
    private string tempDrink9;
    private string tempDrink10;
    private string tempDrink11;
    private string tempDrink12;
    private string tempDrink13;
    private string tempDrink14;
    private string tempDrink15;

    string ip = "2.tcp.ngrok.io:16326";


    public DrinkConsumption()
	{
        var refreshButton = new Button {Text = "Refresh", ImageSource = "refreshicon.png",FontSize=20, HorizontalOptions = LayoutOptions.Start};
        refreshButton.Clicked += refreshButton_Clicked;

        var stack = new VerticalStackLayout
        {
            Spacing = 10,
            Padding = 30,
            Children = {
                new Label { Text = "Beverage Consumption", FontSize = 50
                },

                refreshButton,

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Padding = 10,
                    Children =
                    {
                        new Label { Text = "Name", FontSize = 25 },
                        new Label { Text = "# Of Drinks", FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "1. " + tempName1, FontSize = 25 },
                        new Label { Text = tempDrink1, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "2. " + tempName2, FontSize = 25 },
                        new Label { Text = tempDrink2, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "3. " + tempName3, FontSize = 25 },
                        new Label { Text = tempDrink3, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "4. " + tempName4, FontSize = 25 },
                        new Label { Text = tempDrink4, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "5. " + tempName5, FontSize = 25 },
                        new Label { Text = tempDrink5, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "6. " + tempName6, FontSize = 25 },
                        new Label { Text = tempDrink6, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "7. " + tempName7, FontSize = 25 },
                        new Label { Text = tempDrink7, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "8. " + tempName8, FontSize = 25 },
                        new Label { Text = tempDrink8, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "9. " + tempName9, FontSize = 25 },
                        new Label { Text = tempDrink9, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "10. " + tempName10, FontSize = 25 },
                        new Label { Text = tempDrink10, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "11. " + tempName11, FontSize = 25 },
                        new Label { Text = tempDrink11, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "12. " + tempName12, FontSize = 25 },
                        new Label { Text = tempDrink12, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "13. " + tempName13, FontSize = 25 },
                        new Label { Text = tempDrink13, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "14. " + tempName14, FontSize = 25 },
                        new Label { Text = tempDrink14, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "15. " + tempName15, FontSize = 25 },
                        new Label { Text = tempDrink15, FontSize = 25 } }
                }

            }

        };

        Content = new ScrollView { Content = stack };
    }

    private async void refreshButton_Clicked(object sender, EventArgs e)
    {
        tempName1 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/1")); 
        if (tempName1 == "-1") {
            tempName1 = "";
            tempDrink1 = "";
        }
        else
        {
            tempDrink1 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/1"));
            if(tempDrink1 == "-1")
            {
                tempDrink1 = "0";
            }
        }

        tempName2 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/2"));
        if (tempName2 == "-1")
        {
            tempName2 = "";
            tempDrink2 = "";
        }
        else
        {
            tempDrink2 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/2"));
            if (tempDrink2 == "-1")
            {
                tempDrink2 = "0";
            }
        }


        tempName3 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/3"));
        if (tempName3 == "-1")
        {
            tempName3 = "";
            tempDrink3 = "";
        }
        else
        {
            tempDrink3 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/3"));
            if (tempDrink3 == "-1")
            {
                tempDrink3 = "0";
            }
        }


        tempName4 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/4"));
        if (tempName4 == "-1")
        {
            tempName4 = "";
            tempDrink4 = "";
        }
        else
        {
            tempDrink4 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/4"));
            if (tempDrink4 == "-1")
            {
                tempDrink4 = "0";
            }
        }


        tempName5 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/5"));
        if (tempName5 == "-1")
        {
            tempName5 = "";
            tempDrink5 = "";
        }
        else
        {
            tempDrink5 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/5"));
            if (tempDrink5 == "-1")
            {
                tempDrink5 = "0";
            }
        }


        tempName6 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/6"));
        if (tempName6 == "-1")
        {
            tempName6 = "";
            tempDrink6 = "";
        }
        else
        {
            tempDrink6 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/6"));
            if (tempDrink6 == "-1")
            {
                tempDrink6 = "0";
            }
        }


        tempName7 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/7"));
        if (tempName7 == "-1")
        {
            tempName7 = "";
            tempDrink7 = "";
        }
        else
        {
            tempDrink7 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/7"));
            if (tempDrink7 == "-1")
            {
                tempDrink7 = "0";
            }
        }


        tempName8 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/8"));
        if (tempName8 == "-1")
        {
            tempName8 = "";
            tempDrink8 = "";
        }
        else
        {
            tempDrink8 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/8"));
            if (tempDrink8 == "-1")
            {
                tempDrink8 = "0";
            }
        }


        tempName9 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/9"));
        if (tempName9 == "-1")
        {
            tempName9 = "";
            tempDrink9 = "";
        }
        else
        {
            tempDrink9 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/9"));
            if (tempDrink9 == "-1")
            {
                tempDrink9 = "0";
            }
        }


        tempName10 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/10"));
        if (tempName10 == "-1")
        {
            tempName10 = "";
            tempDrink10 = "";
        }
        else
        {
            tempDrink10 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/10"));
            if (tempDrink10 == "-1")
            {
                tempDrink10 = "0";
            }
        }


        tempName11 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/11"));
        if (tempName11 == "-1")
        {
            tempName11 = "";
            tempDrink11 = "";
        }
        else
        {
            tempDrink11 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/11"));
            if (tempDrink11 == "-1")
            {
                tempDrink11 = "0";
            }
        }


        tempName12 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/12"));
        if (tempName12 == "-1")
        {
            tempName12 = "";
            tempDrink12 = "";
        }
        else
        {
            tempDrink12 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/12"));
            if (tempDrink12 == "-1")
            {
                tempDrink12 = "0";
            }
        }


        tempName13 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/13"));
        if (tempName13 == "-1")
        {
            tempName13 = "";
            tempDrink13 = "";
        }
        else
        {
            tempDrink13 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/13"));
            if (tempDrink13 == "-1")
            {
                tempDrink13 = "0";
            }
        }


        tempName14 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/14"));
        if (tempName14 == "-1")
        {
            tempName14 = "";
            tempDrink14 = "";
        }
        else
        {
            tempDrink14 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/14"));
            if (tempDrink14 == "-1")
            {
                tempDrink14 = "0";
            }
        }


        tempName15 = await service.GetStringAsync(new Uri("http://" + ip + "/Customer/15"));
        if (tempName15 == "-1")
        {
            tempName15 = "";
            tempDrink15 = "";
        }
        else
        {
            tempDrink15 = await service.GetStringAsync(new Uri("http://" + ip + "/DrinksConsumed/15"));
            if (tempDrink15 == "-1")
            {
                tempDrink15 = "0";
            }
        }




        var refreshButton = new Button { Text = "Refresh", ImageSource = "refreshicon.png", FontSize = 20, HorizontalOptions = LayoutOptions.Start };
        refreshButton.Clicked += refreshButton_Clicked;

        var stack = new VerticalStackLayout
        {
            Spacing = 10,
            Padding = 30,
            Children = {
                new Label { Text = "Beverage Consumption", FontSize = 50
                },

                refreshButton,

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Padding = 10,
                    Children =
                    {
                        new Label { Text = "Name", FontSize = 25 },
                        new Label { Text = "# Of Drinks", FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "1. " + tempName1, FontSize = 25 },
                        new Label { Text = tempDrink1, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "2. " + tempName2, FontSize = 25 },
                        new Label { Text = tempDrink2, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "3. " + tempName3, FontSize = 25 },
                        new Label { Text = tempDrink3, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "4. " + tempName4, FontSize = 25 },
                        new Label { Text = tempDrink4, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "5. " + tempName5, FontSize = 25 },
                        new Label { Text = tempDrink5, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "6. " + tempName6, FontSize = 25 },
                        new Label { Text = tempDrink6, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "7. " + tempName7, FontSize = 25 },
                        new Label { Text = tempDrink7, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "8. " + tempName8, FontSize = 25 },
                        new Label { Text = tempDrink8, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "9. " + tempName9, FontSize = 25 },
                        new Label { Text = tempDrink9, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "10. " + tempName10, FontSize = 25 },
                        new Label { Text = tempDrink10, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "11. " + tempName11, FontSize = 25 },
                        new Label { Text = tempDrink11, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "12. " + tempName12, FontSize = 25 },
                        new Label { Text = tempDrink12, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "13. " + tempName13, FontSize = 25 },
                        new Label { Text = tempDrink13, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "14. " + tempName14, FontSize = 25 },
                        new Label { Text = tempDrink14, FontSize = 25 }
                    }
                },

                new HorizontalStackLayout
                {
                    Spacing = 80,
                    Children =
                    {
                        new Label { Text = "15. " + tempName15, FontSize = 25 },
                        new Label { Text = tempDrink15, FontSize = 25 } }
                }

            }

        };

        Content = new ScrollView { Content = stack };
    }
}
using QRCoder;
namespace R3CoolerApp;

public partial class QRCodeGeneration : ContentPage
{
	public QRCodeGeneration()
	{
        NavigationPage.SetHasBackButton(this, true);
		InitializeComponent();
	}

    //private string folderPath;
    private string filePath;
    private string password;

    private void OnGenerateClicked(object sender, EventArgs e)
    {
        //password = await service.GetStringAsync(new Uri("http://172.20.10.2/ledOn"));
        password = "Obama";
        QRCodeGenerator qrGenerator = new QRCodeGenerator();
        QRCodeData qrCodeData = qrGenerator.CreateQrCode(InputText.Text+","+password, QRCodeGenerator.ECCLevel.L);
        PngByteQRCode qRCode = new PngByteQRCode(qrCodeData);
        byte[] qrCodeBytes = qRCode.GetGraphic(20);

        var ims = ImageSource.FromStream(() => new MemoryStream(qrCodeBytes));

        filePath = Path.Combine(FileSystem.CacheDirectory, InputText.Text+".png");
        File.WriteAllBytes(filePath, qrCodeBytes);

        QrCodeImage.Source = ims;

    }

    private async void ShareBtn_Clicked(object sender, EventArgs e)
    {
        if (File.Exists(filePath))
        {
            await Share.Default.RequestAsync(new ShareFileRequest
            {
                Title = "Share QR Code",
                File = new ShareFile(filePath)
            });
        }
    }
}
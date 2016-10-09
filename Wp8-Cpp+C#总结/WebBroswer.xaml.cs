using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using PhoneDirect3DXamlAppComponent;

namespace PhoneDirect3DXamlAppInterop
{
    public partial class WebBroswer : PhoneApplicationPage
    {
        public WebBroswer()
        {
            InitializeComponent();
            string _URL = (Application.Current as App).BuyURL;
            m_WebBroswer.Navigate(new Uri(_URL, UriKind.Absolute));
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            string _szNull = "";
            (Application.Current as App).m_d3dInterop.onCocos2dPurchaseDone(Cocos2dKeyEvent.PurchaseDone, _szNull);
            this.NavigationService.GoBack();
        }

    }
}
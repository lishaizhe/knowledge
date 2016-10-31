using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Diagnostics;

namespace PhoneDirect3DXamlAppInterop
{
    public partial class InputPage : PhoneApplicationPage
    {
        public InputPage()
        {
            InitializeComponent();
        }


        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            string szTextBox = m_TextBox.Text;
            (Application.Current as App).m_d3dInterop.onCocos2dPostInputData(PhoneDirect3DXamlAppComponent.Cocos2dKeyEvent.Individual, szTextBox);
            this.NavigationService.GoBack();
        }
    }
}
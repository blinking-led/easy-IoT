import urllib.request

thing_val = '52M27PBHJ3LPSH4XEEES'
thing_sw = '52M27PBHJ3LPSH4XEEED'

get_url= urllib.request.urlopen('https://dweet.io/dweet/for/' + thing_val + '?temp=22&hum=45&light=250')
print("Response Status: "+ str(get_url.getcode()) )

get_url= urllib.request.urlopen('https://dweet.io/dweet/for/' + thing_sw + '?mode=1&lamp_sw=1&heat_sw=1&cool_sw=1&hum_sw=1')
print("Response Status: "+ str(get_url.getcode()) )
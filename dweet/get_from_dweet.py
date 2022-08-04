import urllib.request

thing_val = '52M27PBHJ3LPSH4XEEES'
thing_sw = '52M27PBHJ3LPSH4XEEED'

print("Values")
with urllib.request.urlopen('https://dweet.io/get/latest/dweet/for/'+thing_val) as response:
    get_url = response.read().decode('utf-8')
dwData = get_url[(get_url.find('content') + 9):]
symb = '{}[]"'
for i in symb:
    dwData = dwData.replace(i, '')
dwData = dwData.split(',')
for i in dwData:
    print(*i.split(':'),sep='\t')
    
print("Switches")
with urllib.request.urlopen('https://dweet.io/get/latest/dweet/for/'+thing_sw) as response:
    get_url = response.read().decode('utf-8')
dwData = get_url[(get_url.find('content') + 9):]
symb = '{}[]"'
for i in symb:
    dwData = dwData.replace(i, '')
dwData = dwData.split(',')
for i in dwData:
    print(*i.split(':'),sep='\t')
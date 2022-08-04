import urllib.request
thing_val = '52M27PBHJ3LPSH4XEEES'
thing_sw = '52M27PBHJ3LPSH4XEEED'

def get():    
    with urllib.request.urlopen('https://dweet.io/get/latest/dweet/for/' + thing_val) as response:
        get_url = response.read().decode('utf-8')
    dwData = get_url[(get_url.find('content') + 9):]
    symb = '{}[]"'
    for i in symb:
        dwData = dwData.replace(i, '')
    dwData = dwData.split(',')
    for i in dwData:
        print(*i.split(':'), sep = '\t')
    with urllib.request.urlopen('https://dweet.io/get/latest/dweet/for/' + thing_sw) as response:
        get_url = response.read().decode('utf-8')
    dwData = get_url[(get_url.find('content') + 9):]
    symb = '{}[]"'
    for i in symb:
        dwData = dwData.replace(i, '')
    dwData = dwData.split(',')
    for i in dwData:
        print(*i.split(':'), sep = '\t')

def send_val(a):
    get_url = urllib.request.urlopen('https://dweet.io/dweet/for/' + thing_val + '?temp=' + str(a[0])
                                     + '&hum=' + str(a[1]) + '&light=' + str(a[2]))
    print("Response Status: "+ str(get_url.getcode()) )
    
def send_sw(a):
    get_url = urllib.request.urlopen('https://dweet.io/dweet/for/' + thing_sw + '?mode=' + str(a[0])
                                     + '&lamp_sw=' + str(a[1]) + '&heat_sw=' + str(a[2]) + '&cool_sw='
                                     + str(a[3]) + '&hum_sw=' + str(a[4]))
    print("Response Status: "+ str(get_url.getcode()) )

def send_zero():
    get_url = urllib.request.urlopen('https://dweet.io/dweet/for/' + thing_val + '?temp=25&hum=55&light=450&mode=0')
    print("Response Status Val: "+ str(get_url.getcode()) )
    get_url = urllib.request.urlopen('https://dweet.io/dweet/for/' + thing_sw + '?mode=0&lamp_sw=0&heat_sw=0&cool_sw=0&hum_sw=0')
    print("Response Status Sw: "+ str(get_url.getcode()) )
    
play = True
while play:
    print("======")
    print("Система управления умным домом.")
    print("1 - Получить значения")
    print("2 - Передать свои значения датчиков")
    print("3 - Атоматическое и ручное управление")
    print("4 - Передать иницилизационные данные")    
    print("5 - Выход")
    sw = input("Выберите пункт меню: ")
    if sw == '1':
        print("1 - Получить значения")
        get()
    if sw == '2':
        print("2 - Передать свои значения датчиков")
        print("В введите через запятую числовые зачения: temp, hum, light")
        send_val(input().split(","))
    if sw == '3':
        print("3 - Атоматическое и ручное управление")
        print("В введите через запятую числовые зачения: mode, lamp_sw, heat_sw, cool_sw, hum_sw")
        send_sw(input().split(","))
    if sw == '4':
        print("4 - Передать иницилизационные данные")        
        send_zero()
    if sw == '5':
        print("5 - Выход")
        play = False
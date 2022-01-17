# PIC Mikrodenetleyici C-XC8 Tabanlı Keypad-LCD Hesap Makinesi

Hesap makinesi projesi PIC mikrodenetleyici, LCD ekran ve Keypad modülü olmak üzere üç temel elektronik bileşenden oluşmaktadır. Bu projede çeşitli PIC modelleri incelenmiş olup dijial pin sayısı, veri yolu genişliği, hafıza ve fiyat parametreleri göz önüne alınarak PIC16F873A modeli tercih edilmiştir. Sistemin çalışması, görev döngüsünün içerisinde tuş takımından alınan verilerin dört aritmetik işlem (toplama, çıkarma, çarpma, bölme) sonucu LCD ekrana yazdırılması prensibine dayanmaktadır. Oluşturulan elektronik devresinde LCD ekranın tüm pinleri dijital ve output olarak PIC’e bağlanmıştır. Tuş takımı ise satır pinleri dijital-output, sütun pinleri dijital-input olacak şekilde PIC’e bağlantısı yapılmıştır. Keypad’den verilerin alınması, satır pinlerine sırasıyla lojik 1 sinyalinin verilmesi sonucunda sütun değerlerinin okunmasıyla sağlanmıştır. Tuş takımının 4x4 matrisli olması sebebiyle 16 farklı tuş; 4 operatör (+,-,*,/), 1 nokta (.), 1 eşittir (=) ve 10 rakamdan (0,1,2,3,4,5,6,7,8,9) oluşmuştur. Ayrıca eşittir tuşuna 3 saniye boyunca uzun basılması durumunda LCD ekran temizlenmektedir.

![resim](https://github.com/mehmet-engineer/PIC_Keypad_LCD_Hesap_Makinesi/blob/main/proteus.png)

PIC mikrodenetleyici MPLAB ortamında C-XC8 programlama diliyle kodlanmıştır. Yazılan algoritma
aritmetik işlemleri ondalıklı olarak işleyebilme kabiliyetine sahiptir. Yazılımda birden fazla operatörün
kullanılmasına izin verilmemesi, rakamlar girilmediği takdirde değerlerin sıfır olarak ön tanımlı haliyle
işlenmesi ve operatör girilmemesi halinde “Hatalı giriş!” uyarısı gibi önlemler alınmıştır. Program
içerisindeki LCD ve Keypad fonksiyonları dahil olmak üzere tüm kodlar şahsım tarafından yazılmış olup
özgün bir yazılım kullanılmıştır.

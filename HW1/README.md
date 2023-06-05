Konu : Linkli Liste ile Şifreli Kilit Kodu Eşleştirme

Problem: Bir şifreli kasa, 3 adet çark ile kilitlenmektedir. Her bir çarkın üzerinde1-N arasında değer
alan M adet sayı sırasız olarak ve her sayı bir defa geçecek şekilde yer almaktadır. Sadece bir sayı üç
çarkta birden bulunmaktadır. Kasanın açılabilmesi için 3 çarkta da olan bu sayının bulunması ve
çarklardaki sayıların, tüm çarklarda bu sayının aynı hizaya geleceği şekilde dairesel olacak
döndürülmeleri gerekmektedir. Hizalama için birinci çarktaki sayının pozisyonu kullanılmalıdır. Ayrıca,
ikinci ve üçüncü çarklar çevrilirken, saat yönünde veya tersinde, en az hareket hangisi ise o
seçilmelidir. Aksi taktirde kilit açılamamaktadır.

Örnek:
N=15, M=6 olmak üzere, üç çarkın üzerindeki sayılar şu şekildedir:

1.çark: -> 15 -> 4 -> 2  -> 3  -> 1 -> 7  ->

2.çark: -> 3  -> 5 -> 12 -> 15 -> 7 -> 14 ->

3.çark: -> 8  -> 9 -> 6  -> 2  -> 4 -> 3  ->

Ortak sayı: 3

1.çarktaki konumu: 4

2.çarktaki konumu: 1

3.çarktaki konumu: 6


2.çark Saat yönünde 3 adım çevrilmeli (Not: Saatin ters yönünde de 3 adım çevrilebilir.)

3.çark Saatin ters yönünde 2 adım çevrilmeli


Çarkların son hali:
1.çark: -> 15 -> 4 -> 2  -> 3 -> 1 -> 7  ->

2.çark: -> 15 -> 7 -> 14 -> 3 -> 5 -> 12 ->

3.çark: -> 6  -> 2 -> 4  -> 3 -> 8 -> 9  ->

PROGRAM ÇIKTILARIM

1) Programı iki defa M = 3, N = 5 girerek çalıştırdım. 
Çıktılar : 

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/6821c997-555a-4f30-ad7f-7b001ccb7719)


![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/44815e61-6b23-4c0b-831d-756e31a4107b)

2) Programı iki defa M = 3, N = 20 girerek çalıştırdım. 
Çıktılar : 

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/49419fbf-c04d-4ce8-bf06-23181fbe74f2)


![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/99f27f9a-9800-4f5e-8d03-145c825f3a43)

3) Programı iki defa M = 7, N = 30 girerek çalıştırdım. 
Çıktılar : 

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/66b3a74d-7d51-4b6a-b4b1-4d9abe921b38)


![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/27cd0190-bb07-4436-a30a-a5de4141e073)

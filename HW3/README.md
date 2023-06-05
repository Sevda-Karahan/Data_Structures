Konu : Graf Veri Yapısı

Problem: Bilgisayar Mühendisliğinde okuyan öğrencilerin mezun olabilmeleri için N adet ders alması
gerekmektedir. Derslerin ön şartları N düğümlü yönlü bir G grafında tutulmaktadır. Eğer bir v dersi bir
w dersinin ön şartı ise G grafında v düğümünden w düğümüne doğru bir bağlantı vardır. Bir öğrenci bir
dönemde istediği kadar ders alabilmektedir. Her dönem alması mümkün olan bütün derslerS alan bir
öğrencinin aldığı derslerden kalmazsa her dönem hangS derslerS alabSleceğSnS ve bölümü kaç
dönemde bStSreceğSnS hesaplayan algoritmayı tasarlayınız.


İşlem Adımları:

1) N adet ders ve E adet ön şart için G ön şart grafını komşuluk matrisi iadjacency matrix) olarak
okuyunuz.

2) Komşuluk matrisinden komşuluk listesini iadjacency list) elde ediniz ve algoritmanızı graf
işlemlerini komşuluk listesi üzerinde yapacak şekilde tasarlayınız.

3) Her dersin kaç adet ön şartı olduğunu io düğümün indegree değeri) hesaplayınız.

4) İlk dönem derslerinin ön şartı 0’dır. Öğrenci ön şartı 0 olan derslerin hepsini aynı dönemde
alabilir.

5) Ön şartı 0 olan dersler alındığında, bu derslerin ön şart olduğu derslerin indegree değerini 1
azaltabilirsiniz. Bu durumda, bir sonraki dönem alınabilecek ön şartı 0 olan yeni dersler oluşur.

6) Bu işlemi bütün dersler alınana kadar tekrarlayınız.

7) Buna göre her dönem alabileceği bütün dersleri alan ve hepsinden geçen bir öğrencinin, her
dönem hangi dersleri alabileceğini ve bölümü kaç dönemde bitireceğini hesaplayarak yazdırınız.
Örnek: Aşağıdaki 5 ders için örneğin Course-1’in Course-2’nin, Course-3 ve Course-4’ün ise Course5’in ön şartı olduğu görülmektedir. 

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/8a37ff93-2040-4b62-8ea1-0932554a2386)


Bu graf için her dersin ön şart sayısı şöyledir:

Course-1: 0 Course-2: 1 Course-3: 0 Course-4: 1 Course-5: 2

Buna göre ön şartları 0 olduğu için, öğrenci ilk dönemde Course-1 ve Course-3’ü birlikte alabilir. Bu
dersleri alınca, alınmayan derslerin bir sonraki dönem için yeni ön şart sayıları aşağıdaki gibi değişir:

Course-2: 0 Course-4: 1 Course-5: 1

Bu durumda öğrenci ikinci dönemde Course-2’yi alabilir. Bu dersi alınca, alınmayan derslerin bir sonraki
dönem için yeni ön şart sayıları aşağıdaki gibi değişir:

Course-4: 0 Course-5: 1

Bu durumda öğrenci üçüncü dönemde Course-4’ü alabilir. Bu dersi alınca, alınmayan derslerin bir
sonraki dönem için yeni ön şart sayıları aşağıdaki gibi değişir:

Course-5: 0

Öğrenci dördüncü dönemde Course-5’i alır ve mezun olur.

Buna göre öğrenci bölümü 4 dönemde bitirir. Öğrencinin her dönem aldığı dersler:

Dönem-1: Course-1 Course-3

Dönem-2: Course-2

Dönem-3: Course-4

Dönem-4: Course-5

PROGRAM ÇIKTILARIM

1) İlk olarak sorunun verildiği pdf’deki örneğin çıktısını paylaşmak istiyorum. (N=5)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/c83a663e-0dfa-4b01-ace6-c85bbed299f3)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/cb827996-f241-4fe9-b73b-8b58214e03a2)

2) N = 6

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/87764345-ad33-40f7-ae78-003ecdd3f337)

Burada 6 dersin ön koşul durumlarını belirten bri graf için komşuluk matrisi:

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/e7e280fb-32c1-4889-8448-988de546dc9d)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/c3cafa93-f334-408c-956c-6f7e40102dfe)

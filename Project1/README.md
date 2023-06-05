Konu: Trie ve N-ary tree veri yapılarının kullanımı

Problem: Cep telefonlarında keypad’deki sayılar aynı zamanda harfler için de kullanılır. Örneğin 2 sayısı ABC, 3
sayısı DEF harfleri için kullanılır. Aşağıda bir cep telefonu keypad’inde her sayıya karşılık gelen karakterler
verilmiştir. Buna göre örneğin “baza” kelimesinin sayı karşılığı 2292, “gaye” kelimesinin sayı karşılığı 4292’dir.

0 #

1 ÇĞÜŞ

2 ABC

3 DEF

4 GHI

5 JKL

6 MNO

7 PQRS

8 TUV

9 WXYZ


Bu projede, verilen bir sayının sözlükteki kelime karşılıklarını bulmak için trie veri yapısı kullanılacaktır. Trie, bir
sembol diziliminde bulunan her sombolün sıralı olarak bir ağaç düğümü olarak gösterildiği yapıdır. Örneğin
sözlükteki kelimelerin {“az”, “gala”, “hala”, “kar”, “kaz”, “kaya”, “kaza”, “kazı”, “kazan”, “tek”, “tel”, “tela”, “ter”,
“yama”, “yoga”, “zona”} olduğunu varsayalım. Bu sözlüğün trie’si aşağıdaki şekildeki gibidir. Burada örneğin “az”
kelimesinin sayı karşılığı 29’dur. Bu kelime ağaca yerleştirilirken ‘a’ harfini gösteren düğümün değeri 2(2 ABC ), ‘z’
harfini gösteren düğümün değeri ‘9’ (9 WXYZ) olur. Her düğümün o kelimenin son düğümü olup olmadığı bilgisi
de saklanmalıdır. Örneğin “az” kelimesindeki ‘z’ harfine karşılık gelen ve değeri 9 olan düğüm, aynı zamanda
kelime sonu gösteren düğümdür. Örnek ağaçta kelime sonu gösteren düğümler kırmızı ile işaretlenmiştir. Buna
göre örneğin 966 sayısı ağaçta olmasına rağmen sözlükte bir kelime karşılığı yoktur.

Eğer bir sayı sözlükteki birden fazla kelimeye denk düşüyorsa o zaman birinci kelimeden sonraki her kelime için
düğümün değeri ‘#’ olacaktır. Örneğin 5292 sayısı “kaya” ve “kaza” kelimelerine karşılık gelmektedir.

Ağaçta her düğümün bir alt seviyesinde en fazla 0-9 arası 10 düğüm bulunabilir. Örneğin ağaçta root’un ilk alt
seviyesinde 2,4, 5, 8, 9 düğümleri vardır. Bu yapıyı gerçekleştirmek için n-ary tree veri yapısını kullanabilirsiniz.
İkili ağaçta bir düğüme bağlı en fazla iki alt düğüm(child) olabilirken, N-ary ağaçta bir düğümün en fazla N adet alt
düğümü olabilir.

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/6b1ddad5-e7b2-4059-be13-01dfb57de3e4)

İşlem Adımları: Bu projede verilen bir sayıya sözlükte karşılık gelen kelimeleri bulup yazdırmanız istenmektedir.

İşlem adımları aşağıdaki gibidir:

1. Yukarıda tarif edilen ağaç yapısı üzerinde yer ve zamanın en efektif şekilde kullanılabilmesi için uygun
struct’ı oluşturunuz.

2. Sözlüğe ait dosyadan okuyacağınız bir sözlükte bulunan kelimeleri boş trie’ye yerleştiriniz.

3. Sorgu için verilen desimal sayının önce basamaklarını elde ediniz. Daha sonra en yüksek anlamlı
basamaktan başlayarak sayıyı trie üzerinde arayınız, varsa kelime karşılığını yazdırınız. 

PROGRAM ÇIKTILARIM

1)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/ccbf43fe-f079-4e16-8fb0-814490235894)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/1b7c0b18-ed98-4a57-b99e-6967e30e5ea5)

2)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/15331303-edbc-4bac-a6db-754704ae0215)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/3b2c99a6-8ff5-4c38-907d-eaa449dcffb0)

3)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/55c6eb19-6854-4297-898c-58d4a7be3a6a)

![image](https://github.com/Sevda-Karahan/Data_Structures/assets/116480291/2559098c-b5b3-4784-8cfd-cd578da7bc90)

Verilen bir sayı için kelime karşılığını bulma işleminin karmaşıklığı:

Girilen sayının uzunluğu N ise uzunluğunu bulmak (strlen ile) O(N). Kelime karşılığını bulma işlemi de sayının her hanesi için Trie'de ilerlemeyi gerektirir. Sayının uzunluğunu N kabul ettik, sözlükte o sayıya karşılık M adet kelime bulunduğunu varsayarsak, verilen bir sayı için kelime karşılığını bulma işlemi, O(N + M -1) karmaşıklığında gerçekleşir. Burda verilen sayı uzunluğu kadar Trie'de ilerleyip ilk kelime karşılığını elde ettiğimizden N, ilk kelime karşılığı dışındaki her bir kelime için ‘#’ değerindeki her bir düğümü gezdiğimiz için M-1 adım ilerleriz. Toplamda N+M-1 adım ilerleme sağlarız. 

Yani bu işlemi gerçekleştirmenin karmaşıklığına O(N+M) denebilir. 

(N sayı uzunluğu, M sözlükte o sayıya karşılık gelen kelime adedi)

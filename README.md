# Sistem Programlama Ödevleri

Bu depo, sistem programlama dersi için verilen ödevleri içermektedir. Her ödev kendi klasöründe bulunmaktadır. Ödevlerin açıklamaları ve çözümleri bu README dosyasında bulunmaktadır.

## Ödevler

1. **soru1**: Bellek yapısı ve boyutlarına ilişkin bir C programı. Program, global değişkenlerin, heap'in ve stack'in başlangıç adreslerini ve boyutlarını hesaplar.
   
2. **soru2**: Güvensiz C fonksiyonlarını tespit eden bir C programı. Program, verilen bir C dosyasındaki `strcpy()` ve `gets()` gibi güvensiz fonksiyonları bulur ve kullanıcıya uyarı mesajı gösterir.

## Kullanım

Her ödevin kendi klasöründe derlenmiş bir dosyası bulunmaktadır. Derlenmiş dosyayı çalıştırmak için terminalde ilgili klasöre gidin ve aşağıdaki komutu kullanın:

```bash
./soru1

./soru2 dosya.c

make

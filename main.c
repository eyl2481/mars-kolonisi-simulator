#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main() {
    srand(time(NULL));

    int can = 100, enerji = 100, o2 = 100, su = 20;
    int parca = 3, hasar = 0, kilit = 0, gun = 1;
    int firtinaTur = 3, gecerli = 0;
    char zorluk, komut;

    printf("=== MARS KOLONISI YASAM DESTEK SIMULATORU ===\n");

    // Zorluk secimi (do-while ve switch-case)
    do {
        printf("Zorluk Secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        zorluk = toupper(zorluk);

        switch (zorluk) {
            case 'K':
                can = 120; enerji = 120; o2 = 120; su = 30; firtinaTur = 2;
                gecerli = 1;
                break;
            case 'N':
                can = 100; enerji = 100; o2 = 100; su = 20; firtinaTur = 3;
                gecerli = 1;
                break;
            case 'Z':
                can = 80; enerji = 80; o2 = 80; su = 15; firtinaTur = 4;
                gecerli = 1;
                break;
            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    } while (!gecerli);

    // Ana oyun dongusu
    do {
        printf("\n--- GUN %d ---\n", gun);
        printf("Komutlar: [D]urum [G]Kesif [O]ksijen [T]amir [H]ava Kilidi [K]um Firtinasi [U]yu [Q]Cikis\n");
        printf("Seciminiz: ");
        scanf(" %c", &komut);
        komut = toupper(komut);

        int turGecti = 0;

        switch (komut) {
            case 'D':
                printf("\n[DURUM RAPORU]\n");
                printf("Can: %d | Enerji: %d | Oksijen: %d | Su: %d\n", can, enerji, o2, su);
                printf("Yedek Parca: %d | Hasar: %d | Hava Kilidi: %s\n", parca, hasar, kilit ? "MUHURLU" : "ACIK");
                break;

            case 'G': { // Kesfe cikma
                if (enerji < 15) {
                    printf("Yetersiz enerji! (En az 15 gerekli)\n");
                    break;
                }
                enerji -= 15;
                turGecti = 1;

                int zar = rand() % 100;
                int esik = (zorluk == 'K') ? 40 : ((zorluk == 'N') ? 50 : 60);
                printf("Kesif Zari: %d / Esik: %d -> ", zar, esik);

                if (zar >= esik && hasar < 50) {
                    int bulunanSu = (rand() % 5) + 3;
                    int bulunanParca = (rand() % 2) + 1;
                    su += bulunanSu;
                    parca += bulunanParca;
                    printf("BASARILI! +%d Su ve +%d Yedek Parca bulundu.\n", bulunanSu, bulunanParca);
                } else {
                    int kazaHasar = (rand() % 10) + 5;
                    hasar += kazaHasar;
                    can -= 5;
                    printf("BASARISIZ! Firtinaya yakalandiniz. +%d Hasar, -5 Can.\n", kazaHasar);
                }
                break;
            }

            case 'O': { // Oksijen uretimi (mod operatoru)
                if (enerji < 10 || su < 2) {
                    printf("Yetersiz enerji veya su! (En az 10 Enerji ve 2 Su gerekli)\n");
                    break;
                }
                int miktar;
                printf("Kullanilacak su miktari (Mevcut: %d): ", su);
                scanf("%d", &miktar);

                if (miktar < 2 || miktar > su) {
                    printf("Gecersiz su miktari!\n");
                    break;
                }

                enerji -= 10;
                turGecti = 1;

                int kalan = miktar % 2;
                int islenen = miktar - kalan;
                su -= islenen;
                int uretilenO2 = (islenen / 2) * 12;
                o2 += uretilenO2;

                if (kalan == 1) {
                    printf("Tek sayi girildi: %d birim su islendi (+%d O2), 1 birim su depoda kaldi.\n", islenen, uretilenO2);
                } else {
                    printf("%d birim su islendi (+%d O2).\n", islenen, uretilenO2);
                }
                break;
            }

            case 'T': { // Tamir
                if (hasar == 0) {
                    printf("Us hasarsiz, tamire gerek yok.\n");
                    break;
                }
                if (parca < 1 || enerji < 10) {
                    printf("Yetersiz yedek parca veya enerji!\n");
                    break;
                }
                parca -= 1;
                enerji -= 10;
                turGecti = 1;
                hasar -= 20;
                if (hasar < 0) hasar = 0;
                printf("Tamir tamamlandi! Guncel hasar: %d\n", hasar);
                break;
            }

            case 'H': { // Hava kilidi sifresi (do-while 3 hak)
                if (kilit == 1) {
                    printf("Hava kilidi zaten muhurlu.\n");
                    break;
                }
                char ipucu = 'A' + ((gun - 1) % 24);
                char dogruSifre = ipucu + 1;
                char tahmin;
                int hak = 3, basari = 0;

                printf("Hava Kilidi Guvenlik Sistemi (Ipucu: '%c' harfinden sonraki harf)\n", ipucu);
                do {
                    printf("Sifreyi girin (Kalan hak %d): ", hak);
                    scanf(" %c", &tahmin);
                    tahmin = toupper(tahmin);

                    if (tahmin == dogruSifre) {
                        kilit = 1;
                        basari = 1;
                        printf("Sifre dogru! Hava kilidi muhurlendi.\n");
                    } else {
                        hak--;
                        printf("Yanlis sifre!\n");
                    }
                } while (hak > 0 && !basari);

                turGecti = 1;
                break;
            }

            case 'K': { // Kum firtinasi (for, continue, break)
                if (enerji < 10) {
                    printf("Yetersiz enerji!\n");
                    break;
                }
                enerji -= 10;
                turGecti = 1;

                int i, hasarTur = 0, kayipCan = 0, kayipO2 = 0;

                for (i = 1; i <= firtinaTur; i++) {
                    int kat = (i % 2 == 0) ? 2 : 1;
                    int zar = rand() % 100;
                    printf("Firtina Tur %d -> Zar: %d / Esik: 45 -> ", i, zar);

                    if (zar < 45) {
                        printf("ATLATILDI\n");
                        continue;
                    }

                    printf("HASAR ALINDI -> ");
                    hasarTur++;
                    int tip = rand() % 3;

                    if (tip == 0) {
                        if (kilit == 1) {
                            printf("Hava kilidi muhurlu oldugu icin O2 sizintisi engellendi!\n");
                            continue;
                        }
                        int kayip = 6 * kat;
                        o2 -= kayip;
                        kayipO2 += kayip;
                        printf("-%d Oksijen\n", kayip);
                    } else if (tip == 1) {
                        int kayip = 5 * kat;
                        can -= kayip;
                        kayipCan += kayip;
                        printf("-%d Can\n", kayip);
                    } else {
                        int ekHasar = 8 * kat;
                        hasar += ekHasar;
                        printf("+%d Us Hasari\n", ekHasar);
                    }

                    if (hasar >= 80) {
                        printf("KRITIK HASAR! Firtina simulasyonu acil durduruldu.\n");
                        break;
                    }
                }

                printf("Firtina Ozeti: %d tur hasar alindi (Toplam -%d Can, -%d O2)\n", hasarTur, kayipCan, kayipO2);
                kilit = 0; // Firtina sonrasi kilit acilir
                break;
            }

            case 'U': // Dinlenme
                enerji += 25;
                if (enerji > 100) enerji = 100;
                can += 10;
                if (can > 100) can = 100;
                turGecti = 1;
                printf("Dinlenildi. +25 Enerji, +10 Can yenilendi.\n");
                break;

            case 'Q':
                printf("Simulasyondan cikiliyor...\n");
                break;

            default:
                printf("Gecersiz komut!\n");
        }

        // Tur sonu tuketim ve kontrol
        if (turGecti && komut != 'Q') {
            o2 -= 5;
            su -= 1;
            if (hasar >= 50) {
                can -= 5;
                printf("Uyari: Yuksek hasar nedeniyle -5 Can kaybi!\n");
            }
            gun++;
        }

        if (can <= 0 || o2 <= 0 || su <= 0 || enerji <= 0) {
            printf("\nKAYNAKLAR TUKENDI! Koloni hayatta kalamadi.\n");
            break;
        }

        if (gun > 7) {
            printf("\nTEBRIKLER! 7 gun boyunca koloniyi hayatta tuttunuz!\n");
            break;
        }

    } while (komut != 'Q');

    int puan = (can * 2) + (o2 * 2) + (su * 5) + (parca * 10) - hasar;
    if (puan < 0) puan = 0;

    printf("\n=== OYUN SONU RAPORU ===\n");
    printf("Hayatta Kalinan Gun: %d | Kalan Can: %d | Kalan O2: %d | Kalan Su: %d\n", gun - 1, can, o2, su);
    printf("Toplam Hayatta Kalma Puani: %d\n", puan);

    return 0;
}

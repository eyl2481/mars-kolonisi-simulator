#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Rastgele sayi uretimi[span_0](start_span)[span_0](end_span)

    // Temel degiskenler[span_1](start_span)[span_1](end_span)
    int can = 100, enerji = 100, o2 = 100;
    int su = 0, parca = 0, hasar = 0, kilit = 0;
    int gun = 1, tur = 0, firtinaTur = 5, zorlukCarpan = 1;
    char secim;
    int basla = 0;

    printf("--- MARS YASAM DESTEK SIMULATORU ---\n");

    // Zorluk secimi (SWITCH-CASE + DO-WHILE)[span_2](start_span)[span_2](end_span)
    do {
        printf("Zorluk (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &secim);

        switch (secim) {
            case 'k': case 'K':
                su = 30; parca = 10; hasar = 10; firtinaTur = 3; zorlukCarpan = 1; basla = 1;
                break;
            case 'n': case 'N':
                su = 20; parca = 6; hasar = 20; firtinaTur = 5; zorlukCarpan = 2; basla = 1;
                break;
            case 'z': case 'Z':
                su = 10; parca = 3; hasar = 35; firtinaTur = 7; zorlukCarpan = 3; basla = 1;
                break;
            default:
                printf("Hatali secim! Tekrar girin.\n");
        }
    } while (!basla);

    char cmd;
    int oyun = 1;

    // Ana oyun dongusu[span_3](start_span)[span_3](end_span)
    do {
        int turSay = 0;
        printf("\n[Gun:%d Tur:%d] Can:%d Enerji:%d O2:%d Su:%d Parca:%d Hasar:%d\n",
               gun, tur, can, enerji, o2, su, parca, hasar);
        printf("Komut (G, O, T, D, U, K, H, Q): ");
        scanf(" %c", &cmd);

        switch (cmd) {
            case 'g': case 'G': { // Kesif[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span)
                if (enerji < 15) { printf("Yetersiz enerji!\n"); break; }
                enerji -= 15; o2 -= 10; turSay = 1;

                int zar = rand() % 100;
                int esik = (enerji > 40 && o2 > 30) ? 60 : 35;
                printf("Zar: %d / Esik: %d -> ", zar, esik);

                if (zar < esik) { su += 8; printf("BASARILI (+8 Su)\n"); }
                else if (zar < esik + 25) { parca += 2; printf("BASARILI (+2 Parca)\n"); }
                else { printf("BASARISIZ (Bos donuldu)\n"); }

                int kaza = rand() % 100;
                printf("Kaza Zari: %d / Esik: 10 -> ", kaza);
                if (kaza < 10 || hasar > 70) { can -= 12; printf("BASARISIZ (-12 Can)\n"); }
                else { printf("BASARILI (Guvenli)\n"); }
                break;
            }

            case 'o': case 'O': { // Oksijen uretimi[span_6](start_span)[span_6](end_span)[span_7](start_span)[span_7](end_span)
                if (enerji < 10) { printf("Yetersiz enerji!\n"); break; }
                int miktar;
                printf("Kullanilacak su (Mevcut %d): ", su);
                scanf("%d", &miktar);

                if (miktar > su || miktar < 2) { printf("Gecersiz su miktari!\n"); break; }

                int artik = miktar % 2; // Mod ile tek/cift kontrolu[span_8](start_span)[span_8](end_span)
                int islenen = miktar - artik;
                su -= islenen;
                enerji -= 10;
                o2 += (islenen / 2) * 3;
                turSay = 1;

                if (artik == 1) printf("1 birim su artik olarak depoda kaldi.\n");
                printf("+%d O2 uretildi.\n", (islenen / 2) * 3);
                break;
            }

            case 't': case 'T': { // Tamir[span_9](start_span)[span_9](end_span)[span_10](start_span)[span_10](end_span)
                if (enerji < 10 || parca <= 0 || hasar == 0) {
                    printf("Tamir yapilamiyor (Enerji/Parca yetersiz veya hasar yok).\n");
                    break;
                }
                if (hasar <= 30) {
                    parca -= 1; hasar -= 15; enerji -= 10; turSay = 1;
                    printf("Hafif hasar onarildi (-15 Hasar).\n");
                } else if (hasar <= 70 && parca >= 2) {
                    parca -= 2; hasar -= 25; enerji -= 10; turSay = 1;
                    printf("Orta hasar onarildi (-25 Hasar).\n");
                } else if (hasar > 70 && parca >= 3) {
                    parca -= 3; hasar -= 35; enerji -= 10; turSay = 1;
                    printf("Agir hasar onarildi (-35 Hasar).\n");
                } else {
                    printf("Bu hasar seviyesi icin yedek parca yetersiz!\n");
                }
                break;
            }

            case 'd': case 'D': { // Durum raporu (Tur harcamaz)[span_11](start_span)[span_11](end_span)[span_12](start_span)[span_12](end_span)[span_13](start_span)[span_13](end_span)
                printf("Kilit: %s | ", kilit ? "MUHURLU" : "ACIK");
                if (o2 < 25) printf("[KRITIK O2] ");
                if (can < 30) printf("[KRITIK CAN] ");
                if (hasar > 70) printf("[KRITIK HASAR] ");
                if (o2 >= 25 && can >= 30 && hasar <= 70 && enerji >= 20)
                    printf("TUM SISTEMLER NORMAL");
                printf("\n");
                break;
            }

            case 'u': case 'U': { // Dinlen[span_14](start_span)[span_14](end_span)[span_15](start_span)[span_15](end_span)
                enerji += 25; o2 -= 8; turSay = 1;
                if (o2 < 20) {
                    can -= 10;
                    printf("Dusuk O2 nedeniyle uyurken can kaybettin (-10 Can)!\n");
                } else {
                    can += 15;
                    printf("Dinlendin (+25 Enerji, +15 Can).\n");
                }
                break;
            }

            case 'k': case 'K': { // Kum firtinasi (FOR)[span_16](start_span)[span_16](end_span)[span_17](start_span)[span_17](end_span)
                if (enerji < 10) { printf("Yetersiz enerji!\n"); break; }
                enerji -= 10; turSay = 1;
                int hasarTur = 0, kayipCan = 0, kayipO2 = 0;

                for (int i = 1; i <= firtinaTur; i++) {
                    int kat = (i % 2 == 0) ? 2 : 1; // Cift turlarda 2 kat hasar[span_18](start_span)[span_18](end_span)
                    int zar = rand() % 100;
                    printf("Firtina %d -> Zar: %d / Esik: 45 -> ", i, zar);

                    if (zar < 45) { printf("BASARILI\n"); continue; }

                    printf("BASARISIZ -> ");
                    hasarTur++;
                    int tip = rand() % 3;

                    if (tip == 0) {
                        if (kilit == 1) { printf("Kilit muhurlu, O2 sizintisi atlandi.\n"); continue; }
                        int kayip = 5 * kat * zorlukCarpan;
                        o2 -= kayip; kayipO2 += kayip;
                        printf("-%d O2\n", kayip);
                    } else if (tip == 1) {
                        hasar += 6 * kat * zorlukCarpan;
                        printf("+%d Hasar\n", 6 * kat * zorlukCarpan);
                    } else {
                        int kayip = 5 * kat * zorlukCarpan;
                        can -= kayip; kayipCan += kayip;
                        printf("-%d Can\n", kayip);
                    }

                    if (can <= 0 || o2 <= 0) break; // Deger sifirlanirsa cik[span_19](start_span)[span_19](end_span)
                }
                printf("Ozet -> Hasarli Tur:%d | Kayip Can:%d | Kayip O2:%d\n", hasarTur, kayipCan, kayipO2);
                break;
            }

            case 'h': case 'H': { // Hava kilidi (DO-WHILE)[span_20](start_span)[span_20](end_span)[span_21](start_span)[span_21](end_span)[span_22](start_span)[span_22](end_span)
                if (kilit == 1 || enerji < 15) { printf("Kilit zaten kapali veya enerji yetersiz.\n"); break; }
                char sifre = 'A' + (gun % 26); // Gune gore sifre[span_23](start_span)[span_23](end_span)
                char tahmin;
                int hak = 3, bildi = 0;
                turSay = 1;

                printf("Ipucu: A harfinden gun sayisi (%d) kadar ilerideki harf.\n", gun);
                do {
                    printf("Sifre (Hak %d): ", hak);
                    scanf(" %c", &tahmin);
                    if (tahmin >= 'a' && tahmin <= 'z') tahmin -= 32;

                    if (tahmin == sifre) bildi = 1;
                    else {
                        hak--; enerji -= 5;
                        printf(tahmin < sifre ? "Ileri git (-5 Enerji)\n" : "Geri git (-5 Enerji)\n");
                    }
                } while (!bildi && hak > 0); // Tek kosullu kontrol[span_24](start_span)[span_24](end_span)

                if (bildi) { kilit = 1; printf("Kilit muhurlendi!\n"); }
                else { hasar += 20; printf("Basarisiz (+20 Hasar)!\n"); }
                break;
            }

            case 'q': case 'Q': oyun = 0; break;
            default: printf("Tanimsiz komut!\n"); // Tur harcamaz[span_25](start_span)[span_25](end_span)
        }

        // 0-100 Sinirlandirma[span_26](start_span)[span_26](end_span)
        if (can > 100) can = 100; if (can < 0) can = 0;
        if (enerji > 100) enerji = 100; if (enerji < 0) enerji = 0;
        if (o2 > 100) o2 = 100; if (o2 < 0) o2 = 0;
        if (hasar > 100) hasar = 100; if (hasar < 0) hasar = 0;

        // Gun gecisi (Her 3 turda 1 gun)[span_27](start_span)[span_27](end_span)
        if (oyun && turSay) {
            tur++;
            if (tur % 3 == 0) {
                gun++;
                if (gun <= 15) {
                    o2 -= 8;
                    if (hasar > 70) can -= 5;
                    if (o2 < 0) o2 = 0; if (can < 0) can = 0;
                    printf("--- %d. GUNE GECILDI (-8 O2) ---\n", gun);
                }
            }
        }

        // Oyun sonu kontrolu[span_28](start_span)[span_28](end_span)
        if (oyun && (can <= 0 || o2 <= 0)) {
            printf("\nKAYBETTINIZ!\n"); oyun = 0;
        } else if (oyun && gun > 15) {
            gun = 15; printf("\nKAZANDINIZ! Kurtarma ekibi geldi.\n"); oyun = 0;
        }

    } while (oyun);

    // Sonuc raporu[span_29](start_span)[span_29](end_span)
    int puan = (gun * 100) + can + o2 - hasar;
    printf("\n=== SONUC ===\nGun:%d Tur:%d Can:%d O2:%d Hasar:%d | PUAN: %d\n",
           gun, tur, can, o2, hasar, puan);

    return 0;
}

    
            
            

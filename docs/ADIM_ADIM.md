# CMakeLists.txt'dan GitHub CI/CD'ye — Turkce Kilavuz

## 1. Sozluk: hangi kelime sabit, hangisi degisebilir?

| Metin | Tur | Anlam |
|---|---|---|
| `CMakeLists.txt` | CMake tarafindan beklenen ozel dosya adi | Ana CMake dosyasi |
| `cmake_minimum_required` | CMake komutu (sabit) | Minimum CMake surumu |
| `VERSION` | CMake anahtar sozcugu (sabit) | Surum girisi |
| `3.16` | Deger (degisebilir) | Minimum CMake surumu |
| `project` | CMake komutu (sabit) | Projeyi tanimlar |
| `MotorThermalGuard` | Proje adi (degisebilir) | Projeye sen isim verirsin |
| `LANGUAGES` | CMake anahtar sozcugu (sabit) | Kullanilan dil |
| `CXX` | CMake tarafindan tanimlanan dil kodu | C++ icin sabit kod |
| `set` | CMake komutu | Bir degiskene deger atar |
| `CMAKE_CXX_STANDARD` | CMake'in onceden tanimladigi degisken adi | Ismini degistirme, degerini degistirebilirsin |
| `17` | Deger | C++17 standardi; destek varsa 20 yapilabilir |
| `add_library` | CMake komutu | Kutuphane hedefi olusturur |
| `motor_protection` | Senin hedef adin | Diger referanslarla tutarli yeniden adlandirilabilir |
| `src/motor_protection.cpp` | Dosya yolu | Dosyayi tasirsan guncelle |
| `target_include_directories` | CMake komutu | Header arama yolu |
| `PUBLIC` | CMake anahtar sozcugu | Bagimlilara yayinlanan ayar |
| `include` | Klasor yolu | Degisebilir |
| `add_executable` | CMake komutu | Calistirilabilir hedef |
| `motor_monitor` | Senin hedef adin | Uretilecek program adi |
| `target_link_libraries` | CMake komutu | Kutuphaneleri baglar |
| `PRIVATE` | CMake anahtar sozcugu | Hedefe ozel bagimlilik |
| `enable_testing` | CMake komutu | CTest testlerini etkinlestirir |
| `add_test` | CMake komutu | Test kaydi |
| `NAME` / `COMMAND` | CMake anahtar sozcukleri | Test adi ve calistirma komutu |
| `MotorProtectionTests` | Test adi | Serbestce belirlenir |

## 2. C++ tarafindaki sabit ve degiskenler

- `constexpr double kTripTemperatureC = 75.0;`: `constexpr` C++ dilinin **sabit anahtar sozcugu**, `double` tip, `kTripTemperatureC` programcinin sectigi ad, `75.0` degeridir. `constexpr` ile tanimlanmis bu deger calisirken degistirilemez.
- `double temperatureCelsius`: `double` sabit tip adi, `temperatureCelsius` programcinin sectigi degisken adidir. Fonksiyona verilen sicaklik her cagirmada degisebilir.
- `class MotorProtection`: `class` sabit C++ sozcugu; `MotorProtection` bizim sinifimizin adidir.
- `return`, `if`, `else`, `true`, `false`: C++ dilinin sabit anahtar sozcukleri.
- `motor_monitor`: CMake hedef adi; Linux'ta program adi, Windows'ta genellikle `motor_monitor.exe` olur.

## 3. Build nedir?

Kaynak kod (`.cpp`) -> derleyici -> nesne dosyalari (`.o`/`.obj`) -> baglayici (linker) -> `motor_monitor` programi.

CMake `cmake -S . -B build` ile derleme sistemini olusturur. `cmake --build build --config Release` ile derleme baslatilir.

## 4. Testler neden ayri?

`motor_monitor`: Son kullanicinin calistirdigi simulasyon programi.
`motor_tests`: Beklenen sonucu otomatik denetleyen ayri program.
CTest test programini calistirir, `0` cikisi basari, sifir disi cikis basarisizlik demektir.

## 5. Git komutlari

| Komut | Etkisi |
|---|---|
| `git init` | Klasoru Git reposu yapar |
| `git status` | Dosya degisikliklerini gosterir |
| `git add .` | Dosyalari bir sonraki commit icin stage eder |
| `git commit -m "mesaj"` | Yerel surum kaydi olusturur |
| `git branch -M main` | Ana branch adini `main` yapar |
| `git remote add origin URL` | Uzak GitHub deposunu baglar |
| `git push -u origin main` | Commitleri GitHub'a gonderir |
| `git switch -c feature/threshold-80` | Ozellik dali acar ve ona gecer |
| `git pull` | Uzak depodan guncellemeleri alir ve entegre eder |

`git` ve `push` komut sozcukleri sabit; `origin`, `main`, branch adi, commit mesaji, URL degisebilir. `origin` Git'in varsayilan uzak depo takma adi degildir, yaygin konvansiyonudur.

## 6. GitHub Actions dosyasi

`.github/workflows/ci.yml` dosyasini GitHub otomatik okur.

- `on`, `push`, `pull_request`, `jobs`, `runs-on`, `steps`, `uses`, `run`, `needs`: GitHub Actions YAML alanlari; anahtar adlari platform tarafindan belirlenmistir.
- `C++ Motor Guard CI-CD`: bizim workflow adimiz.
- `main`: bizim ana branch adimiz; baska branch adi secersek burada da degistirmeliyiz.
- `ubuntu-24.04`, `windows-2025`: GitHub runner etiketleri; desteklenen bir baskasini kullanabilirsin.
- `ci`, `cd`: kendi secilen job kimliklerimiz (ozel `ci` veya `cd` anahtar sozcukleri degil).
- `actions/checkout@v7`, `actions/upload-artifact@v7`: Gercek GitHub Actions paket ve surum referanslari; keyfi degistirme, guncel desteklenen surumu kullan.
- `cmake -S . -B build`: terminal komutudur; `-S` kaynak, `-B` build klasorunu secer.
- `${{ matrix.os }}`: Github Actions ifadesi; `matrix.os` matris satirindan hesaplanir.
- `if: github.event_name == 'push' && github.ref == 'refs/heads/main'`: CD sadece ana branch'e push olunca calissin.

## 7. GitHub uzerinde adim adim

1. https://github.com/ uzerinden hesap ac; e-postani dogrula.
2. `+` > `New repository` tikla.
3. Repo adi `motor-thermal-guard` yaz, public/private sec.
4. README veya gitignore ekleme, cunku zaten yerel projede mevcut.
5. `Create repository` tikla.
6. Visual Studio'nun terminalini veya Git Bash'i ac; proje klasorune gec.
7. `git init`, `git add .`, `git commit` komutlarini sirasiyla calistir.
8. GitHub'in gosterdigi URL'yi `git remote add origin ...` ile bagla.
9. `git push -u origin main` yap; gerektiginde Git Credential Manager tarayici uzerinden kimlik dogrulama yaptirir.
10. GitHub'da `Actions` sekmesinden `Build and test (ubuntu-24.04)` ve `(windows-2025)` sonuclarini gor.
11. Ana branch'e push sonrasi `Package` isleri de basariliysa workflow sayfasindaki `Artifacts` bolumunden Linux ve Windows program dosyalarini indir.

## 8. Kasitli bug egzersizi

`src/motor_protection.cpp` dosyasindaki `temperatureCelsius >= config_.tripTemperatureC` ifadesini gecici olarak `temperatureCelsius > config_.tripTemperatureC` yap.

Bunun sonucunda 75.0 C sinirinda alarm beklenen sekilde acilmaz. Test programi bunu yakalar. Kodu tekrar `>=` yaparak testleri yesile donustur.

## 9. Yeni gorev: Esik 80 C olacak

1. Yeni branch: `git switch -c feature/threshold-80`
2. `include/motor_protection.h` icindeki `kTripTemperatureC = 80.0` yap.
3. `tests/test_motor_protection.cpp` icindeki varsayilan sistem testlerini yeni gereksinime gore guncelle: 74.9 yerine 79.9, 75.0 yerine 80.0 gibi. Testin **beklenen** sonucunu degistirirken gereksinimlerle uyumunu gozden gecir.
4. `cmake --build build --config Release` ve `ctest --test-dir build -C Release --output-on-failure` calistir.
5. `git add .`, `git commit -m "Raise trip temperature to 80 C"`, `git push -u origin feature/threshold-80`.
6. GitHub'da Pull Request ac, CI sonucunu gor, kodu incele, birlestir.

## 10. Kisa ariza giderme

- `'cmake' is not recognized`: CMake yuklu degil veya dogru gelistirici terminali kullanilmiyor.
- `'git' is not recognized`: Git for Windows kur veya terminali yeniden ac.
- `No CMAKE_CXX_COMPILER could be found`: C++ derleyicisi yok, Visual Studio Installer icinde **Desktop development with C++** sec.
- `not a git repository`: Terminal proje klasorunde degil veya `git init` yapilmamis.
- `Author identity unknown`: `git config --global user.name "Ad Soyad"` ve `git config --global user.email "eposta@adres"` ayarla.
- `remote origin already exists`: `git remote -v` ile bak; tekrar ekleme, gerekirse `git remote set-url origin URL` kullan.
- `non-fast-forward`: Uzak repo ile yerel repo farkli gecmise sahiptir. Gelisiguzel `--force` kullanma; mevcut durumu incele.

## 11. Resmi basvuru kaynaklari

- https://cmake.org/cmake/help/latest/guide/tutorial/index.html
- https://learn.microsoft.com/cpp/build/cmake-projects-in-visual-studio
- https://git-scm.com/install/windows
- https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-new-repository
- https://docs.github.com/en/actions

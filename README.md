# Motor Thermal Guard — C++ / Git / GitHub / CI/CD

Bu proje, C++17, CMake, Git ve GitHub Actions ogrenmek icin gercekten derlenebilen bir egitim uygulamasidir.
Bu bir **simulasyondur**; STM32'ye firmware yuklemez ve gercek bir motoru kontrol etmez.

## Neler yapiyor?

- Motor sicakligi **75 C** oldugunda `ALARM` durumuna gecer.
- Sicaklik **70 C** seviyesine inene kadar alarm acik kalir (histerezis).
- Gecerli sensor araligi -40..150 C; bunun disinda `SENSOR_FAULT` olusur.
- Hata sonrasinda sensor tekrar gecerli olsa bile sicaklik 70 C veya altina inmeden alarm kalkmaz.
- C++ ile yazilmis **19 kontrol** iceren otomatik test programi vardir.
- GitHub Actions, Windows ve Linux uzerinde derler, test eder ve ana branch'e push sonrasi iki platformun calistirilabilir programlarini artifact olarak saklar.

## Dosyalar

```text
motor-thermal-guard/
  CMakeLists.txt
  .gitignore
  .github/workflows/ci.yml
  include/motor_protection.h
  src/motor_protection.cpp
  src/main.cpp
  tests/test_motor_protection.cpp
  docs/ADIM_ADIM.md
  README.md
```

## Windows — Visual Studio Developer PowerShell ile

1. Visual Studio Community 2026 kur, `Desktop development with C++` bileşenini sec.
2. Proje klasorunu ac ve **Developer PowerShell for VS 2026** terminalini baslat.
3. Proje klasorune terminalden gec. Asagidaki komutlar klasorun icindeyken calisir.

```powershell
cmake --version
git --version
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\motor_monitor.exe 25 74.9 75 73 70 180 72 69
```

**Not:** Windows'ta secilen CMake generator'a gore executable yolu degisebilir. Visual Studio generator ile genellikle `build/Release/motor_monitor.exe` olusur. Ninja kullaniyorsan `build/motor_monitor.exe` olabilir.

## macOS ve Linux — Terminal

CMake ve C++ compiler (`clang++` veya `g++`) kurulu olmali. Ardindan:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/motor_monitor 25 75 73 70
```

## Git / GitHub

GitHub'da **bos**, `motor-thermal-guard` adinda yeni repo olustur (README/.gitignore/license ekleme; dosyalar zaten bu klasorde). Sonra klasorde:

```bash
git init
git branch -M main
git add .
git commit -m "Initial C++ motor protection and CI"
git remote add origin https://github.com/KULLANICI_ADIN/motor-thermal-guard.git
git push -u origin main
```

Bu `KULLANICI_ADIN` gercek GitHub kullanici adinla degistirilmelidir. Once `git config --global user.name ...` ve `user.email ...` gerekebilir. HTTPS girisinde Git Credential Manager tarayicida oturum actirabilir. GitHub hesap sifresini terminale normal Git parolasi olarak yazmak artik gecerli yontem degildir.

GitHub'da `Actions` > `C++ Motor Guard CI-CD` altinda otomatik testleri gor.

## Branch ve Pull Request deneyi

```bash
git switch -c feature/threshold-80
```

`include/motor_protection.h` icinde trip degerini 75.0'dan 80.0'a degistir. Var olan testleri de **yeni gereksinime** gore guncelle. Testleri calistir:

```bash
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Windows icin gecerli bu iki komut macOS/Linux'ta da calisir.

```bash
git add .
git commit -m "Raise motor trip threshold to 80 C"
git push -u origin feature/threshold-80
```

GitHub'da `Compare & pull request` ile `main` branch'ine PR ac. PR uzerinde otomatik CI calisir. GitHub'a yuklenince PR ve Actions kontrolu gercekten platform uzerinde gerceklesir.

## Guvenlik

Bu bir egitim projesidir. Gercek motor sistemlerinde ayrica sensor hata politikalari, watchdog, hardware fail-safe, HIL testleri ve guvenlik analizi gereklidir.

Detayli Turkce anlatim: [docs/ADIM_ADIM.md](docs/ADIM_ADIM.md)

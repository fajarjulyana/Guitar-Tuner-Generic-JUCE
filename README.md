# Tuner Gitar Kromatik

Tuner gitar kromatik berbasis JUCE yang menggunakan Fast Fourier Transform (FFT) untuk mendeteksi frekuensi dari input mikrofon.

## Fitur
- Menggunakan JUCE Framework 7.0.9
- Input dari mikrofon
- FFT untuk analisis frekuensi
- Deteksi frekuensi secara real-time
- Output frekuensi yang terdeteksi

## Prerequisites
Pastikan telah menginstal:
- JUCE Framework 7.0.9
- C++ Compiler (GCC/Clang di Linux, MSVC di Windows, Xcode di macOS)
- CMake (opsional untuk build cross-platform)

## Cara Build dan Run
### 1. Clone Repository
```bash
git clone https://github.com/fajarjulyana/Guitar-Tuner-Generic-JUCE.git
cd Guitar-Tuner-Generic-JUCE
```

### 2. Jalankan Projucer
Buka `Projucer` dan load file `.jucer`, lalu generate build files sesuai sistem operasi.

### 3. Build dengan Linux Makefile (Linux)
```bash
cd Builds/LinuxMakefile
make
./build/TunerGitarChromatic
```

### 4. Build dengan Visual Studio (Windows)
- Buka `.sln` di Visual Studio
- Compile dan jalankan proyek

### 5. Build dengan Xcode (macOS)
- Buka `.xcodeproj` di Xcode
- Compile dan jalankan proyek

## Cara Penggunaan
1. Jalankan aplikasi.
2. Pastikan mikrofon terhubung dan aktif.
3. Mainkan sebuah nada pada gitar.
4. Frekuensi akan muncul pada output log atau GUI (jika sudah ditambahkan).
5. Gunakan hasil frekuensi untuk menyetel gitar.

## Kalibrasi
Jika frekuensi tidak akurat:
- Pastikan tidak ada noise yang mengganggu.
- Sesuaikan ukuran FFT untuk akurasi lebih baik.
- Pastikan sample rate sesuai dengan spesifikasi perangkat.

## Lisensi
MIT License.

---
Dibuat dengan ❤️ menggunakan JUCE.



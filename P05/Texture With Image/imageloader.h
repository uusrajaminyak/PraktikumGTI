#include <windows.h>
#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

// Merepresentasikan sebuah gambar
class Image {
public:
    Image(char* ps, int w, int h);
    ~Image();

    /* Array dalam bentuk (R1, G1, B1, R2, G2, B2, ...)
     * yang menunjukkan warna setiap piksel. Komponen warna 0-255.
     * Array dimulai dari piksel kiri-bawah ke kanan, lalu ke atas.
     */
    char* pixels;
    int width;
    int height;
};

// Membaca gambar bitmap dari file
Image* loadBMP(const char* filename);

#endif

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#include <immintrin.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static inline void getRGB(uint8_t *im, int width, int height, int nchannels, int x, int y, int *r, int *g, int *b)
{

    unsigned char *offset = im + (x + width * y) * nchannels;
    *r = offset[0];
    *g = offset[1];
    *b = offset[2];
}

int main(int nargs, char **argv)
{
    int width, height, nchannels;
    struct timeval fin,ini;

    if (nargs < 2)
    {
        printf("Usage: %s <image1> [<image2> ...]\n", argv[0]);
    }
    // For each image
    // Bucle 0
    for (int file_i = 1; file_i < nargs; file_i++)
    {
        printf("[info] Processing %s\n", argv[file_i]);
        /****** Reading file ******/
        uint8_t *rgb_image = stbi_load(argv[file_i], &width, &height, &nchannels, 4);
        if (!rgb_image)
        {
            perror("Image could not be opened");
        }

        /****** Allocating memory ******/
        // - RGB2Grey
        uint8_t *grey_image = malloc(width * height);
        if (!grey_image)
        {
            perror("Could not allocate memory");
        }

        // - Filenames 
        for (int i = strlen(argv[file_i]) - 1; i >= 0; i--)
        {
            if (argv[file_i][i] == '.')
            {
                argv[file_i][i] = 0;
                break;
            }
        }

        char *grey_image_filename = 0;
        asprintf(&grey_image_filename, "%s_grey.jpg", argv[file_i]);
        if (!grey_image_filename)
        {
            perror("Could not allocate memory");
            exit(-1);
        }

        /****** Computations ******/
        printf("[info] %s: width=%d, height=%d, nchannels=%d\n", argv[file_i], width, height, nchannels);

        if (nchannels != 3 && nchannels != 4)
        {
            printf("[error] Num of channels=%d not supported. Only three (RGB), four (RGBA) are supported.\n", nchannels);
            continue;
        }

        gettimeofday(&ini,NULL);

        // RGB to grey scale
        __m256 coefficients = _mm256_set_ps(0.0, 0.1140, 0.5870, 0.2989, 0.0, 0.1140, 0.5870, 0.2989);

        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i += 4) {
                uint8_t *pixel = rgb_image + (j * width + i) * 4;
                
                // Cargamos 8 bytes en dos vectores (low y high)
                __m128i lowData = _mm_loadu_si128((__m128i *)pixel);
                __m128i highData = _mm_loadu_si128((__m128i *)pixel + 16);
                
                // Extender a 32 bits
                __m256i lowInt = _mm256_cvtepu8_epi32(lowData);
                __m256i highInt = _mm256_cvtepu8_epi32(highData);
                
                // Convertir a float
                __m256 lowFloat = _mm256_cvtepi32_ps(lowInt);
                __m256 highFloat = _mm256_cvtepi32_ps(highInt);
                
                // Aplicar coeficientes de escala de grises
                __m256 lowScaled = _mm256_mul_ps(lowFloat, coefficients);
                __m256 highScaled = _mm256_mul_ps(highFloat, coefficients);
                
                // Sumar los valores
                __m256 sum = _mm256_hadd_ps(lowScaled, highScaled);
                sum = _mm256_hadd_ps(sum, sum);
                
                // Reordenar los valores en el orden correcto
                sum = _mm256_permutevar8x32_ps(sum, _mm256_set_epi32(7, 5, 3, 1, 6, 4, 2, 0));
                
                // Convertir en enteros de 32 bits
                __m128i finalInt = _mm_cvtps_epi32(_mm256_extractf128_ps(sum, 0));
                
                // Asignar los valores en escala de grises
                for (int channel = 0; channel < 4; channel++) {
                    grey_image[j * width + i + channel] = (uint8_t)_mm_extract_epi32(finalInt, channel);
                }
            }
        }

        stbi_write_jpg(grey_image_filename, width, height, 1, grey_image, 10);
        free(rgb_image);

        gettimeofday(&fin,NULL);

	printf("Tiempo: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
        free(grey_image_filename);
    }
}

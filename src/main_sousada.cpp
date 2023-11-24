#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>    //a mettre en commentaire pour Sousada
#include <math.h>
#include <corecrt_math_defines.h>   //a mettre en commentaire pour Lison
#include <glm/gtx/matrix_transform_2d.hpp>


void GreenOnly(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}


void ChannelsSwap(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}


void BlackAndWhite(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float gris = (color.r + color.g + color.b)/3;
        color.r = gris;
        color.b = gris;
        color.g = gris;
    }
}


void Negative(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.b = 1.f - color.b;
        color.g = 1.f - color.g;
    }
}


void Gradient(sil::Image& image)
{
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width()-1; x++)
        {
            float px = static_cast<float>(x)/image.width();
            glm::vec3 couleur(px, px, px);
            image.pixel(x, y) = couleur;
        }
    }
}


void Mirror(sil::Image& image)
{
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{1}; x < image.width(); x++)
        {
            int miroir = image.width()-x;
            glm::vec3 couleur = image.pixel(x, y);
            image.pixel(miroir, y) = couleur;
        }
    }
}

void MirrorV2(sil::Image& image)
{
    sil::Image imageInverse(image.width(), image.height());
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{1}; x < image.width(); x++)
        {
            int miroir = image.width()-x;
            imageInverse.pixel(miroir, y) = image.pixel(x, y);
        }
    }
    imageInverse.save("output_s/miroirInverse.png");
}


void Noise(sil::Image& image)
{
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x+=random_int(0, 10))
        {
            float r = random_float(0, 1);
            float g = random_float(0, 1);
            float b = random_float(0, 1);

            glm::vec3 couleur_rdm(r, g, b);
            image.pixel(x, y) = couleur_rdm;
        }
    }
}


void Rotation(sil::Image& image)
{
    sil::Image imageRotation(image.height(), image.width());

    for (int y{1}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            int rotationX = image.height()-y;
            int rotationY = x;
            imageRotation.pixel(rotationX, rotationY) = image.pixel(x,y);
        }
    }
    imageRotation.save("output_s/rotation.png");
}


void RgbSplit(sil::Image& image)
{
    sil::Image RGBsplit(image.width(), image.height());

    int deplacementR{30};
    int deplacementB{-30};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            glm::vec3 originalColor = image.pixel(x, y);

            int redX = x + deplacementR;
            int greenX = x;
            int blueX = x + deplacementB;

            if (redX >= 0 && redX < image.width()) 
            {
                RGBsplit.pixel(redX, y).r = originalColor.r;
            }

            if (greenX >= 0 && greenX < image.width()) 
            {
                RGBsplit.pixel(greenX, y).g = originalColor.g;
            }

            if (blueX >= 0 && blueX < image.width()) 
            {
                RGBsplit.pixel(blueX, y).b = originalColor.b;
            }
        } 
    }
    RGBsplit.save("output_s/RGB_split.png");
}


void LuminosityBrighter(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = pow(color.r,0.5);
        color.g = pow(color.g,0.5);
        color.b = pow(color.b,0.5);
    }
    image.save("output_s/eclaircissement.jpg");
}

void LuminosityDarker(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = pow(color.r,2);
        color.g = pow(color.g,2);
        color.b = pow(color.b,2);
    }
    image.save("output_s/assombrissement.jpg");
}


void Disc(sil::Image& image)
{
    // Paramètres disque
    int centerX = 250;
    int centerY = 250;
    int radius = 100;
    glm::vec3 colorDisc(1.0f, 1.0f, 1.0f);

    // Dessin disque
    for (int y{0}; y < image.height(); y++) 
    {
        for (int x{0}; x < image.width(); x++) 
        {
            if (pow(x - centerX, 2) + pow(y - centerY, 2) <= pow(radius, 2)) 
            {
                image.pixel(x, y) = colorDisc;
            }
        }
    }
}


void Circle(sil::Image& image)
{
    // Paramètres cercle
    int centerX = 250;
    int centerY = 250;
    int radiusExt = 100;
    int radiusInt = 90;
    glm::vec3 colorCircle(1.0f, 1.0f, 1.0f);

    // Dessin cercle
    for (int y{0}; y < image.height(); y++) 
    {
        for (int x{0}; x < image.width(); x++) 
        {
            if (pow(x - centerX, 2) + pow(y - centerY, 2) <= pow(radiusExt, 2)) 
            {
                if (pow(x - centerX, 2) + pow(y - centerY, 2) >= pow(radiusInt, 2)) 
                {
                    image.pixel(x, y) = colorCircle;
                }
            }
        }
    }
}


void Rosace(sil::Image& image, int centerX, int centerY)
{
    int radiusExt = 100;
    int radiusInt = 95;
    glm::vec3 colorCircle(1.0f, 1.0f, 1.0f);

    // Dessin cercle
    for (int y{0}; y < image.height(); y++) 
    {
        for (int x{0}; x < image.width(); x++) 
        {
            if (pow(x - centerX, 2) + pow(y - centerY, 2) <= pow(radiusExt, 2)) 
            {
                if (pow(x - centerX, 2) + pow(y - centerY, 2) >= pow(radiusInt, 2)) 
                {
                    image.pixel(x, y) = colorCircle;
                }
            }
        }
    }
}


void Glitch(sil::Image& image)
{
    int nb_rectangles_a_echanger = 50;

    for (int i{0}; i < nb_rectangles_a_echanger; i++) 
    {
        // Coordonnées rectangle01
        int x1 = random_int(0, image.width() - 1 - 50);
        int y1 = random_int(0, image.height() - 1 - 10);
        int width1 = random_int(10, 50);
        int height1 = random_int(5, 10);

        // Coordonnées rectangle02
        int x2 = random_int(0, image.width() - 1 - 50);
        int y2 = random_int(0, image.height() - 1 - 10);
        int width2 = random_int(10, 50);
        int height2 = random_int(5, 10);

        // Echange rectangles
        for (int dy{0}; dy < height1; dy++) 
        {
            for (int dx{0}; dx < width1; dx++) 
            {
                int rectangle01_X = x1 + dx;
                int rectangle01_Y = y1 + dy;

                int rectangle02_X = x2 + dx;
                int rectangle02_Y = y2 + dy;

                std::swap(image.pixel(rectangle01_X, rectangle01_Y), image.pixel(rectangle02_X, rectangle02_Y));
            }
        }
    }
}


glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void Vortex(sil::Image& image)
{
    // //tentative de vortex
    // float centerX = static_cast<float>(image.width()) / 2.0f;
    // float centerY = static_cast<float>(image.height()) / 2.0f;

    // for (int y{0}; y < image.height(); y++) 
    // {
    //     for (int x{0}; x < image.width(); x++) 
    //     {
            
    //         float distanceX = static_cast<float>(x) - centerX;
    //         float distanceY = static_cast<float>(y) - centerY;

    //         float angle = atan2(distanceY, distanceX);

    //         int rotatedX = static_cast<int>(centerX + cos(angle) * distanceX - sin(angle) * distanceY);
    //         int rotatedY = static_cast<int>(centerY + sin(angle) * distanceX + cos(angle) * distanceY);

    //         rotatedX = std::max(0, std::min(image.width() - 1, rotatedX));
    //         rotatedY = std::max(0, std::min(image.height() - 1, rotatedY));

    //         image.pixel(rotatedX, rotatedY) = image.pixel(x, y);
    //     }
    // }

    
    glm::vec2 center{image.width() / 2.f, image.height() / 2.f};

    float vortexFactor = 0.2f;

    for (int y{0}; y < image.height(); y++) 
    {
        for (int x{0}; x < image.width(); x++) 
        {
            
            glm::vec2 offset{x - center.x, y - center.y};

            float distance = glm::length(offset);
            float angle = distance * vortexFactor;

            glm::vec2 rotatedOffset = rotated(offset, center, angle);

            int rotatedX = static_cast<int>(rotatedOffset.x + center.x);
            int rotatedY = static_cast<int>(rotatedOffset.y + center.y);

            rotatedX = glm::clamp(rotatedX, 0, image.width() - 1);
            rotatedY = glm::clamp(rotatedY, 0, image.height() - 1);

            image.pixel(x, y) = image.pixel(rotatedX, rotatedY);
        }
    }
}



void Dithering(sil::Image& image)
{
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
    {    -0.5,       0,  -0.375,   0.125 },
    {    0.25,   -0.25,   0.375, - 0.125 },
    { -0.3125,  0.1875, -0.4375,  0.0625 },
    {  0.4375, -0.0625,  0.3125, -0.1875 },
    };

    for (int y{0}; y < image.height(); y++) 
    {

        for (int x{0}; x < image.width(); x++) 
        {
            float orig_color = image.pixel(x, y).r;
            float color_result = 0.f;
            float bayer_value = bayer_matrix_4x4[y % bayer_n][x % bayer_n];
            float output_color = orig_color + (2 * bayer_value);

            if (output_color > 0.5) 
            {
                color_result = 1.f;
            }

            glm::vec3 Color(color_result);
            image.pixel(x, y) = Color;
        }
    }
}


void Histogramme(sil::Image& image)
{
    float valeur_minimale_r = 1.f;
    float valeur_maximale_r = 0.f;
    float valeur_minimale_g = 1.f;
    float valeur_maximale_g = 0.f;
    float valeur_minimale_b = 1.f;
    float valeur_maximale_b = 0.f;

    for (int y{0}; y < image.height(); y++) 
    {
        for (int x{0}; x < image.width(); x++) 
        {
            float pixel_original_r = image.pixel(x, y).r;
            float pixel_original_g = image.pixel(x, y).g;
            float pixel_original_b = image.pixel(x, y).b;
            
            valeur_minimale_r = std::min(valeur_minimale_r, pixel_original_r);
            valeur_maximale_r = std::max(valeur_maximale_r, pixel_original_r);

            valeur_minimale_g = std::min(valeur_minimale_g, pixel_original_g);
            valeur_maximale_g = std::max(valeur_maximale_g, pixel_original_g);

            valeur_minimale_b = std::min(valeur_minimale_b, pixel_original_b);
            valeur_maximale_b = std::max(valeur_maximale_b, pixel_original_b);
        }
    }

    for (int y{0}; y < image.height(); y++) 
    {
        for (int x{0}; x < image.width(); x++) 
        {
            float pixel_original_r = image.pixel(x, y).r;
            float pixel_original_g = image.pixel(x, y).g;
            float pixel_original_b = image.pixel(x, y).b;

            float pixel_normalise_r = (pixel_original_r - valeur_minimale_r) / (valeur_maximale_r - valeur_minimale_r);
            float pixel_normalise_g = (pixel_original_g - valeur_minimale_g) / (valeur_maximale_g - valeur_minimale_g);
            float pixel_normalise_b = (pixel_original_b - valeur_minimale_b) / (valeur_maximale_b - valeur_minimale_b);

            glm::vec3 Color(pixel_normalise_r, pixel_normalise_g, pixel_normalise_b);
            image.pixel(x, y) = Color;
        }
    }
}


void PixelsSort(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++) 
    {
        std::vector<glm::vec3> Pixels;
        for (int y{0}; y < image.height(); y++) 
        {
            Pixels.push_back(image.pixel(x, y));
        }

        std::sort(Pixels.begin(), Pixels.end(), [](glm::vec3 const& color1, glm::vec3 const& color2) 
        {
            return color1.r < color2.r;
        });

        for (int y{0}; y < image.height(); y++) 
        {
            image.pixel(x, y) = Pixels[y];
        }
    }
}


void main_sousada()
{
    {
        //EXO: Ne garder que le vert
        sil::Image image{"images/logo.png"};
        GreenOnly(image);
        image.save("output_s/vert.png");
    }

    {
        //EXO: Échanger les canaux
        sil::Image image{"images/logo.png"};
        ChannelsSwap(image);
        image.save("output_s/echange_canaux.png");
    }

    {
        //EXO: Noir et blanc
        sil::Image image{"images/logo.png"};
        BlackAndWhite(image);
        image.save("output_s/noir_et_blanc.png");
    }

    {
        //EXO: Négatif
        sil::Image image{"images/logo.png"};
        Negative(image);
        image.save("output_s/negatif.png");
    }

    {
        //EXO: Dégradé
        sil::Image image{300/*width*/, 200/*height*/};
        Gradient(image);
        image.save("output_s/degrade.png");
    }

    {
        //EXO: Miroir
        sil::Image image{"images/logo.png"};
        Mirror(image);
        image.save("output_s/miroir.png");
    }
    {
        //Image inversée
        sil::Image image{"images/logo.png"};
        MirrorV2(image);
    }

    {
        //EXO : Image bruitée
        sil::Image image{"images/logo.png"};
        Noise(image);
        image.save("output_s/bruit.png");
    }

    {
        //EXO : Rotation 90°
        sil::Image image{"images/logo.png"};
        Rotation(image);
    }

    {
        //EXO : RGB split
        sil::Image image{"images/logo.png"};
        RgbSplit(image);
    }

    {
        //EXO : Luminosité
        sil::Image image{"images/photo.jpg"};
        LuminosityBrighter(image);
        LuminosityDarker(image);
    }

    {
        //EXO : Disque
        sil::Image image{500/*width*/, 500/*height*/};
        Disc(image);
        image.save("output_s/disque.png");
    }

    {
        //EXO : Cercle
        sil::Image image{500/*width*/, 500/*height*/};
        Circle(image);
        image.save("output_s/cercle.png");
    }

    {
        //EXO : Rosace
        sil::Image image{500/*width*/, 500/*height*/};
        Rosace(image, 250, 250);
        Rosace(image, 250 + 100 * cos(2*M_PI/3), 250 + 100 * sin(2*M_PI/3));
        Rosace(image, 250 + 100 * cos(M_PI/3), 250 + 100 * sin(M_PI/3));
        Rosace(image, 250 + 100 * cos(-2*M_PI/3), 250 + 100 * sin(-2*M_PI/3));
        Rosace(image, 250 + 100 * cos(-M_PI/3), 250 + 100 * sin(-M_PI/3));
        Rosace(image, 250 + 100 * cos(M_PI), 250 + 100 * sin(M_PI));
        Rosace(image, 250 + 100 * cos(0), 250 + 100 * sin(0));
        image.save("output_s/rosace.png");
    }

    {
        //EXO : Glitch
        sil::Image image{"images/logo.png"};
        Glitch(image);
        image.save("output_s/glitch.png");
    }

    {
        //EXO : Vortex
        sil::Image image{"images/logo.png"};
        Vortex(image);
        image.save("output_s/vortex.png");
    }

    {
        //EXO : Tramage
        sil::Image image{"images/photo.jpg"};
        Dithering(image);
        image.save("output_s/tramage.jpg");
    }

    {
        //EXO : Normalisation de l'histogramme
        sil::Image image{"images/photo_faible_contraste.jpg"};
        Histogramme(image);
        image.save("output_s/histogramme.jpg");
    }

    {
        //EXO : Tri de pixels
        sil::Image image{"images/logo.png"};
        PixelsSort(image);
        image.save("output_s/tri_pixels.png");
    }
}
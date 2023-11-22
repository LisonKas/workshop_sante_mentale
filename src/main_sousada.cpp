#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>    //a mettre en commentaire pour Sousada
#include <math.h>
#include <corecrt_math_defines.h>   //a mettre en commentaire pour Lison


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
    for (int y = 0; y < image.height(); y++) 
    {
        for (int x = 0; x < image.width(); x++) 
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
    for (int y = 0; y < image.height(); y++) 
    {
        for (int x = 0; x < image.width(); x++) 
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
    for (int y = 0; y < image.height(); y++) 
    {
        for (int x = 0; x < image.width(); x++) 
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

sil::Image copie_image(sil::Image& image, sil::Image const& logo, int debut_i, int debut_j)
{
    for(int i {0}; i<logo.width(); i++)
    {
        for(int j {0}; j<logo.height(); j++)
        {
            image.pixel(i+debut_i, j+debut_j) = logo.pixel(i, j);
        }
    }
    return image;
}

void Mosaique(sil::Image& logo)
{
    // sil::Image imageReduite(image.width()*reduction, image.height()*reduction);

    // for (int y{0}; y < image.height(); y++) 
    // {
    //     for (int x{0}; x < image.width(); x++) 
    //     {
            
    //     }
    // }
    // mosaique.save("output_s/mosaique.png");

    sil::Image image{logo.width()*5, logo.height()*5};
    int i = 0;
    for(int a {0}; a<5; a++){
        int j = 0;
        for(int b {0}; b<5; b++){
            copie_image(image, logo, i, j);
            j += logo.height();
        }
        i += logo.width();
    }
    image.save("output_s/mosaique.png");
}


void Glitch(sil::Image& image)
{
    //
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
        //EXO : Mosaique
        sil::Image logo{"images/logo.png"};
        Mosaique(logo);
    }

    {
        //EXO : Glitch
        sil::Image image{"images/logo.png"};

        image.save("output_s/glitch.png");
    }
}
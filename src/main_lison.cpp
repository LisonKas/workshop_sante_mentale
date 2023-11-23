#include <sil/sil.hpp>
#include "random.hpp"
#include <math.h>
#include <cmath>
#include <complex>
#include <corecrt_math_defines.h> 

sil::Image dessine_cercle(sil::Image& photo, int center_x, int center_y){  //Pour rosace
    int thickness {10};
    for(int i {0}; i<photo.width(); i++){
        for(int j {0}; j<photo.height(); j++){
            float const distance_carre { static_cast<float>(std::pow(i - center_x, 2) + std::pow(j - center_y, 2))};
            if(distance_carre <= std::pow(100, 2)){
                if(distance_carre >= std::pow(100-thickness, 2)){
                    // photo.pixel(i, j).r = 1.f;
                    // photo.pixel(i, j).g = 1.f;
                    // photo.pixel(i, j).b = 1.f;

                    photo.pixel(i, j) = glm::vec3{1};
                }
            }
        }
    }
    return photo;
}

//------------------------------------------------------------------------------

sil::Image image_en_miroir(sil::Image& image){
    for(int i {0}; i<image.width()/2 ; i++){
        for(int y {0}; y<image.height(); y++){
            std::swap(image.pixel(i, y), image.pixel(image.width()-1-i, y));
        }
    }
    return image;
}

sil::Image al_envers(sil::Image& image){
    sil::Image rota{image.height(), image.width()};
    for(int i {0}; i<rota.width(); i++){
        for(int y {0}; y<rota.height(); y++){
            rota.pixel(i, y) = image.pixel(y, image.height()-1-i);
        }
    }
    sil::Image rota_90{rota.height(), rota.width()};
    for(int i {0}; i<image.width(); i++){
        for(int y {0}; y<image.height(); y++){
            image.pixel(i, y) = rota.pixel(y, rota.height()-1-i);
        }
    }
    return image;
}

sil::Image copie_image(sil::Image& image, sil::Image const& logo, int debut_i, int debut_j){   //Pour mosaique
    for(int i {0}; i<logo.width(); i++){
        for(int j {0}; j<logo.height(); j++){
            image.pixel(i+debut_i, j+debut_j) = logo.pixel(i, j);
        }
    }
    return image;
}

//-------------------------------------------------------------------------------

void main_lison()
{

{
    sil::Image image{"images/logo.png"};   //Exo 1 : Niv 1 : Tout en vert !
    for(glm::vec3& color : image.pixels()){  
        color.r = 0.f;
        color.b = 0.f;
    }
    image.save("output_l/tout_en_vert.png");
}

//Exo 2 : Niv 1 : Echanger les canaux
{
    sil::Image image{"images/logo.png"};   
    for(glm::vec3& color : image.pixels()){
        std::swap(color.r, color.b);
    }
    image.save("output_l/canaux_echanges.png");
}

//-----------------------------------------------------------------------------------
{
    sil::Image image{"images/logo.png"};   //Exo 3 : Niv 1 : Noir et blanc
    for(glm::vec3& color : image.pixels()){
        float moyenne = (color.r + color.g + color.b)/3;
        color.r=moyenne;
        color.g=moyenne;
        color.b=moyenne;
        /*if(color.r<=color.g && color.r<=color.b){
            color.g=color.r;
            color.b=color.r;
        }
        else if(color.b<=color.g && color.b<=color.r){
            color.g=color.b;
            color.r=color.b;
        }
        else {
            color.r=color.g;
            color.b=color.g;
        }*/
    }
    image.save("output_l/noir_et_blanc.png");
}
//-----------------------------------------------------------------------------------
{
    sil::Image image{"images/logo.png"}; //Exo 4: Niv 1 : Négatif
    for(glm::vec3& color : image.pixels()){
        // color.r = 1.f - color.r;
        // color.g = 1.f - color.g;
        // color.b = 1.f - color.b;

        color = 1.f - color;
    }
    image.save("output_l/negatif.png");
}
//-------------------------------------------------------------------------------------
{
    sil::Image image{300/*width*/, 200/*height*/};  //Exo 5: Niv 1 : Dégradé
    for(int i {0}; i<=image.width()-1; i++){
        for(int y {0}; y<image.height(); y++){
            float color = static_cast<float>(i) /(image.width()-1);  //
            image.pixel(i, y) += color;
        }
    }
    image.save("output_l/degrade.png");
}
//-----------------------------------------------------------------------------------
{
    sil::Image image{"images/logo.png"};  //Exo 6 : Niv 2 : Miroir
    for(int i {0}; i<image.width()/2 ; i++){
        for(int y {0}; y<image.height(); y++){
            std::swap(image.pixel(i, y), image.pixel(image.width()-1-i, y));
        }
    }
    image.save("output_l/miroir.png");
}
//-------------------------------------------------------------------------------------
{
    sil::Image image{"images/logo.png"};  //Exo 7 : Niv 2 : Bruitée
    for(int i {0}; i<image.width(); i++){
        for(int z {0}; z<image.height()/3; z++){
            int x {random_int(0, image.width()-1)};
            int y {random_int(0, image.height()-1)};
            image.pixel(x, y).r = random_float(0.00f, 1.00f);
            image.pixel(x, y).g = random_float(0.00f, 1.00f);
            image.pixel(x, y).b = random_float(0.00f, 1.00f);
        }
    }
    image.save("output_l/bruitee.png");
}
//--------------------------------------------------------------------------------------

    sil::Image image{"images/logo.png"};  //Exo 8 : Niv 2 : Rotation 90°
    sil::Image rota_90{image.height(), image.width()};
    for(int i {0}; i<rota_90.width(); i++){
        for(int y {0}; y<rota_90.height(); y++){
            rota_90.pixel(i, y) = image.pixel(y, image.height()-1-i);
        }
    }
    rota_90.save("output_l/rotation_90.png");

//------------------------------------------------------------------------------------------

    sil::Image split{image.width(), image.height()};   //Exo 9 : Niv 2 : RGB split
    for(int i {0}; i<split.width(); i++){
        for(int j {0}; j<split.height(); j++){
            if(i<=30){
                split.pixel(i, j).g = image.pixel(i, j).g;
                split.pixel(i, j).b = image.pixel(i+30, j).b;
            }
            else if(i>=split.width()-31){
                split.pixel(i, j).r = image.pixel(i-30, j).r;
                split.pixel(i, j).g = image.pixel(i, j).g;
            }
            else {
                split.pixel(i, j).r = image.pixel(i-30, j).r;
                split.pixel(i, j).g = image.pixel(i, j).g;
                split.pixel(i, j).b = image.pixel(i+30, j).b;
            }
        }
    }
    split.save("output_l/rgb_split.png");

//----------------------------------------------------------------------------------------
{
    sil::Image photo{"images/photo_faible_contraste.jpg"};   //Exo 10 : Niv 2 : Luminosité
    for(glm::vec3& color : photo.pixels()){
        color = glm::pow(color,glm::vec3{ 1.6f}); 
    }
    photo.save("output_l/photo_apres_assombrissement.jpg");
}
{
    sil::Image photo{"images/photo_faible_contraste.jpg"};
    for(glm::vec3& color : photo.pixels()){
        color.r = pow(color.r, 0.8f);   
        color.g = pow(color.g, 0.8f);
        color.b = pow(color.b, 0.8f);
    }
    photo.save("output_l/photo_apres_eclaircissement.jpg");
}
//---------------------------------------------------------------------------------------
{
    sil::Image image{500/*width*/, 500/*height*/};            //Exo 11 : Niv 2 : Disque
    for(int i {image.width()/2 - 100}; i<image.width()/2 +100; i++){
        for(int j {image.height()/2 - 100}; j<image.height()/2 +100; j++){
            if(std::pow(i - image.width()/2, 2) + std::pow(j - image.height()/2, 2) <= std::pow(100, 2)){
                image.pixel(i, j).r = 1.f;
                image.pixel(i, j).g = 1.f;
                image.pixel(i, j).b = 1.f;
            }
        }
    }
    image.save("output_l/disque.png");
}
{
    //Niv 1 : Cercle
    sil::Image image{500/*width*/, 500/*height*/} ;
    int thickness {10};
    for(int i {image.width()/2 - 100}; i<image.width()/2 +100; i++){
        for(int j {image.height()/2 - 100}; j<image.height()/2 +100; j++){
            if(std::pow(i - image.width()/2, 2) + std::pow(j - image.height()/2, 2) <= std::pow(100, 2)){
                if(std::pow(i - image.width()/2, 2) + std::pow(j - image.height()/2, 2) >= std::pow(100-thickness, 2)){
                    image.pixel(i, j).r = 1.f;
                    image.pixel(i, j).g = 1.f;
                    image.pixel(i, j).b = 1.f;
                }
            }
        }
    }
    image.save("output_l/cercle.png");
}
{
    //Niv 3 : Rosace
    sil::Image image{500/*width*/, 500/*height*/} ;
    int x = image.width()/2;
    int y = image.height()/2;
    dessine_cercle(image, x, y);

    dessine_cercle(image, x-95, y);
    dessine_cercle(image, x+95, y);
    int x_trigo {static_cast<int>(95*std::cos(M_PI/3.0))};
    int y_trigo {static_cast<int>(95*std::sin(M_PI/3.0))};
    dessine_cercle(image, x-x_trigo, y+y_trigo);
    dessine_cercle(image, x+x_trigo, y+y_trigo);
    dessine_cercle(image, x-x_trigo, y-y_trigo);
    dessine_cercle(image, x+x_trigo, y-y_trigo);
    image.save("output_l/rosace.png");
}

//-------------------------------------------------------------------------------------
{
    //Exo 12 : Niv 2 : Mosaïque
    sil::Image logo {"images/logo.png"};
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
    image.save("output_l/mosaique.png");
}
{
    //Niv 3 : Mosaique_miroir
    sil::Image logo {"images/logo.png"};
    sil::Image logo_a_miroir {"images/logo.png"};
    sil::Image logo_a_l_envers {"images/logo.png"};
    sil::Image logo_alenvers_miroir {"images/logo.png"};
    al_envers(logo_a_l_envers);
    image_en_miroir(logo_a_miroir);
    al_envers(logo_alenvers_miroir);
    image_en_miroir(logo_alenvers_miroir);
    sil::Image image{logo.width()*5, logo.height()*5};
    int k = 0;
    for(int a {0}; a<5; a++){
        int j = 0;
        if(a%2==0){
            for(int b {0}; b<5; b++){
                if(b%2==0){
                    copie_image(image, logo, k, j);
                }
                else{
                    copie_image(image, logo_a_l_envers, k, j);
                }
                j += logo.height();
            }
        }
        else{
            for(int b {0}; b<5; b++){
                if(b%2==0){
                    copie_image(image, logo_a_miroir, k, j);
                }
                else{
                    copie_image(image, logo_alenvers_miroir, k, j);
                }
                j += logo.height();
            }
        }
        k += logo.width();
    }
    image.save("output_l/mosaique_miroir.png");

    //Niv 3 : Mosaique_miroir, autre type marrant
    /*sil::Image logo2 {"images/logo.png"};
    sil::Image logo_a_miroir {"images/logo.png"};
    sil::Image logo_a_l_envers {"images/logo.png"};
    sil::Image logo_alenvers_miroir {"images/logo.png"};
    al_envers(logo_a_l_envers);
    image_en_miroir(logo_a_miroir);
    al_envers(logo_alenvers_miroir);
    image_en_miroir(logo_alenvers_miroir);
    sil::Image image_mosa2{logo2.width()*5, logo2.height()*5};
    int k = 0;
    for(int a {0}; a<5; a++){
        int j = 0;
        if(a%2==0){
            for(int b {0}; b<5; b++){
                if(b%2==0){
                    copie_image(image_mosa2, logo2, k, j);
                }
                else{
                    copie_image(image_mosa2, logo_a_miroir, k, j);
                }
                j += logo.height();
            }
        }
        else{
            for(int b {0}; b<5; b++){
                if(b%2==0){
                    copie_image(image_mosa2, logo_a_l_envers, k, j);
                }
                else{
                    copie_image(image_mosa2, logo_alenvers_miroir, k, j);
                }
                j += logo2.height();
            }
        }
        k += logo2.width();
    }
    image_mosa2.save("output_l/mosaique_miroir_autre.png");*/
}

//------------------------------------------------------------------------------------
{
    //Exo 13 : Niv 3 : Glitch   eh bah non
    sil::Image image_GLITCH{"images/logo.png"};
    int j {0};
    int f {0};
    for(int i {0}; i<100; i++){
        f = 0;
            int x {random_int(0, image_GLITCH.width()-51)};
            int y {random_int(0, image_GLITCH.height()-11)};
            int x2 {random_int(x, x+50)};
            int y2 {random_int(y, y+10)};
            for(int a {x}; a<=x2; a++){
                j=0;
                for(int b {y}; b<y2; b++){
                    std::swap(image_GLITCH.pixel(f, j), image_GLITCH.pixel(a, b));
                    j++;
                }
                f++;
            }
    }
    image_GLITCH.save("output_l/glitch.png");

    /*sil::Image image_GLITCH{"images/logo.png"};    //glitch fondant
    int j {0};
    for(int i {0}; i<image_GLITCH.width(); i++){
            int x {random_int(0, image_GLITCH.width()-1)};
            int y {random_int(0, image_GLITCH.height()-1)};
            int x2 {random_int(x, image_GLITCH.width()-1)};
            int y2 {random_int(y, image_GLITCH.height()-1)};
            /*if(x<image_GLITCH.width()-11){
                x2 = random_int(x, 10);
            }
            else {
                x2 = random_int(x, image_GLITCH.width()-1);
            }
            if(y<image_GLITCH.height()-11){
                y2 = random_int(y, 10);
            }
            else{
                y2 = random_int(y, image_GLITCH.height()-1);
            }*/
            /*for(int a {x}; a<=x2; a++){
                j=0;
                for(int b {y}; b<y2; b++){
                    std::swap(image_GLITCH.pixel(i, j), image_GLITCH.pixel(a, b));
                    j++;
                }
            }
    }
    image_GLITCH.save("output_l/glitch_2.png");*/
}

//---------------------------------------------------------------------------------------

    //Exo 14 : Niv 3 : Fractale de Mandelbrot
{
    sil::Image image {500, 500};
    int maxIter {50};
    for(int i {0}; i<image.width(); i++){
        for(int j {0}; j<image.height(); j++){
            float x {(i-image.width()/2.0f)*4.0f/image.width()};
            float y {(j-image.height()/2.0f)*4.0f/image.height()};
            std::complex<float> c{x, y};
            std::complex<float> z{0.f, 0.f};
            int iter{0};
            while(std::abs(z)<=2 && iter<maxIter){
                z = z*z + c;
                iter++;
                image.pixel(i, j) = glm::vec3(1.f);
            }
            if(iter>maxIter){
                image.pixel(i, j) = glm::vec3(0.f);
            }
            else {
                image.pixel(i, j) = glm::vec3(0.f + iter*0.02f);
            }

            // if(std::abs(z)>2){
            //     image.pixel(i, j) = glm::vec3(0.f+i*0.02f);
            // }
        }
    }
    image.save("output_l/fractale_mandelbrot.png");
}

//-------------------------------------------------------------------------------------

{
    //Exo 15 : Convolutions
    sil::Image image {"images/logo.png"};
    //float coeff {static_cast<float>(1/9)};
    for(int i {1}; i<image.width()-1; i++){
        for(int j {1}; j<image.height()-1; j++){
            // if(i==0 && j==0){
            //     //float color_px_debordant {coeff*5.f*0.f};
            //     image.pixel(i, j) = coeff*image.pixel(i, j);
            //     image.pixel(i, j) += coeff*image.pixel(i, j+1)+coeff*image.pixel(i+1, j+1)+coeff*image.pixel(i+1, j); //+ (glm::vec3(color_px_debordant));
            // }
            // else if(i==0 && j==image.height()-1){
            //     //float color_px_debordant {coeff*5.f*0.f};
            //     image.pixel(i, j) = coeff*image.pixel(i, j);
            //     image.pixel(i, j) += coeff*image.pixel(i, j-1)+coeff*image.pixel(i+1, j-1)+coeff*image.pixel(i+1, j); //+ (glm::vec3(color_px_debordant));
            // }
            // else if(i==image.width()-1 && j==0){
            //     //float color_px_debordant {coeff*5.f*0.f};
            //     image.pixel(i, j) = coeff*image.pixel(i, j);
            //     image.pixel(i, j) += coeff*image.pixel(i, j+1)+coeff*image.pixel(i-1, j+1)+coeff*image.pixel(i-1, j); //+ (glm::vec3(color_px_debordant));
            // }
            // else if(i==image.width()-1 && j==image.height()-1){
            //     //float color_px_debordant {coeff*5.f*0.f};
            //     image.pixel(i, j) = coeff*image.pixel(i, j);
            //     image.pixel(i, j) += coeff*image.pixel(i, j-1)+coeff*image.pixel(i-1, j-1)+coeff*image.pixel(i-1, j); //+ (glm::vec3(color_px_debordant));
            // }
            // else if((i>=1 && j>=1) && (i<=image.width()-2 && j<=image.height()-2)){
            //     image.pixel(i, j) = coeff*image.pixel(i, j);
            //     image.pixel(i, j) += coeff*image.pixel(i, j-1)+coeff*image.pixel(i-1, j-1)+coeff*image.pixel(i-1, j)+coeff*image.pixel(i-1, j+1)+coeff*image.pixel(i, j+1)+coeff*image.pixel(i+1, j+1)+coeff*image.pixel(i+1, j)+coeff*image.pixel(i+1, j-1);
            // }

            //image.pixel(i, j) = image.pixel(i, j);
            image.pixel(i, j) = (image.pixel(i, j)+image.pixel(i, j-1)+image.pixel(i-1, j-1)+image.pixel(i-1, j)+image.pixel(i-1, j+1)+image.pixel(i, j+1)+image.pixel(i+1, j+1)+image.pixel(i+1, j)+image.pixel(i+1, j-1))/glm::vec3(8);
        }
    }
    image.save("output_l/convolution_petite.png");


    sil::Image image2 {"images/logo.png"};
    for(int i {1}; i<image.width()-1; i++){
        for(int j {1}; j<image.height()-1; j++){
            if((i>=2 && i<image.width()-2) && (j>=2 && j<image.height()-2)){
                glm::vec3 color1 = (image.pixel(i, j)+image.pixel(i, j-1)+image.pixel(i-1, j-1)+image.pixel(i-1, j)+image.pixel(i-1, j+1)+image.pixel(i, j+1)+image.pixel(i+1, j+1)+image.pixel(i+1, j)+image.pixel(i+1, j-1));
                glm::vec3 color2 = image.pixel(i-2, j-2)+image.pixel(i-2, j-1)+image.pixel(i-2, j)+image.pixel(i-2, j+1)+image.pixel(i-2, j+2);
                glm::vec3 color3 = image.pixel(i-1, j-2)+image.pixel(i-1, j+2);
                glm::vec3 color4 = image.pixel(i, j-2)+image.pixel(i, j+2);
                glm::vec3 color5 = image.pixel(i+1, j-2)+image.pixel(i+1, j+2);
                glm::vec3 color6 = image.pixel(i+2, j-2)+image.pixel(i+2, j-1)+image.pixel(i+2, j)+image.pixel(i+2, j+1)+image.pixel(i+2, j+2);
                image.pixel(i, j) = (color1+color2+color3+color4+color5+color6)/glm::vec3(9+5+2+2+2+5);
            }
            else if((i==1)&&(j==1)){
                glm::vec3 color1 = (image.pixel(i, j)+image.pixel(i, j-1)+image.pixel(i-1, j-1)+image.pixel(i-1, j)+image.pixel(i-1, j+1)+image.pixel(i, j+1)+image.pixel(i+1, j+1)+image.pixel(i+1, j)+image.pixel(i+1, j-1));
                glm::vec3 color2 = glm::vec3(5.f*0.f);
                glm::vec3 color3 = glm::vec3(0.f)+image.pixel(i-1, j+2);
                glm::vec3 color4 = glm::vec3(0.f)+image.pixel(i, j+2);
                glm::vec3 color5 = glm::vec3(0.f)+image.pixel(i+1, j+2);
                glm::vec3 color6 = glm::vec3(0.f)+image.pixel(i+2, j-1)+image.pixel(i+2, j)+image.pixel(i+2, j+1)+image.pixel(i+2, j+2);
                image.pixel(i, j) = (color1+color2+color3+color4+color5+color6)/glm::vec3(9+5+2+2+2+5);
            }
            else if(i==1 && j==image.height()-2){
                glm::vec3 color1 = (image.pixel(i, j)+image.pixel(i, j-1)+image.pixel(i-1, j-1)+image.pixel(i-1, j)+image.pixel(i-1, j+1)+image.pixel(i, j+1)+image.pixel(i+1, j+1)+image.pixel(i+1, j)+image.pixel(i+1, j-1));
                glm::vec3 color2 = glm::vec3(5.f*0.f);
                glm::vec3 color3 = image.pixel(i-1, j-2)+glm::vec3(0.f);
                glm::vec3 color4 = image.pixel(i, j-2)+glm::vec3(0.f);
                glm::vec3 color5 = image.pixel(i+1, j-2)+glm::vec3(0.f);
                glm::vec3 color6 = image.pixel(i+2, j-2)+image.pixel(i+2, j-1)+image.pixel(i+2, j)+image.pixel(i+2, j+1)+glm::vec3(0.f);
                image.pixel(i, j) = (color1+color2+color3+color4+color5+color6)/glm::vec3(9+5+2+2+2+5);
            }
            else if(i==image.width()-2 && j==1){
                glm::vec3 color1 = (image.pixel(i, j)+image.pixel(i, j-1)+image.pixel(i-1, j-1)+image.pixel(i-1, j)+image.pixel(i-1, j+1)+image.pixel(i, j+1)+image.pixel(i+1, j+1)+image.pixel(i+1, j)+image.pixel(i+1, j-1));
                glm::vec3 color2 = glm::vec3(0.f)+image.pixel(i-2, j-1)+image.pixel(i-2, j)+image.pixel(i-2, j+1)+image.pixel(i-2, j+2);
                glm::vec3 color3 = glm::vec3(0.f)+image.pixel(i-1, j+2);
                glm::vec3 color4 = glm::vec3(0.f)+image.pixel(i, j+2);
                glm::vec3 color5 = glm::vec3(0.f)+image.pixel(i+1, j+2);
                glm::vec3 color6 = glm::vec3(5.f*0.f);
                image.pixel(i, j) = (color1+color2+color3+color4+color5+color6)/glm::vec3(9+5+2+2+2+5);
            }
            else if(i==image.width()-2 && j==image.height()-2){
                glm::vec3 color1 = (image.pixel(i, j)+image.pixel(i, j-1)+image.pixel(i-1, j-1)+image.pixel(i-1, j)+image.pixel(i-1, j+1)+image.pixel(i, j+1)+image.pixel(i+1, j+1)+image.pixel(i+1, j)+image.pixel(i+1, j-1));
                glm::vec3 color2 = image.pixel(i-2, j-2)+image.pixel(i-2, j-1)+image.pixel(i-2, j)+image.pixel(i-2, j+1)+glm::vec3(0.f);
                glm::vec3 color3 = image.pixel(i-1, j-2)+glm::vec3(0.f);
                glm::vec3 color4 = image.pixel(i, j-2)+glm::vec3(0.f);
                glm::vec3 color5 = image.pixel(i+1, j-2)+glm::vec3(0.f);
                glm::vec3 color6 = glm::vec3(5.f*0.f);
                image.pixel(i, j) = (color1+color2+color3+color4+color5+color6)/glm::vec3(9+5+2+2+2+5);
            }
        }
    }
    image.save("output_l/convolution_moyenne.png");
}

{
    //Avec autres boucles
    sil::Image image {"images/logo.png"};
    for(int x {0}; x<image.width(); x++){
        for(int y {0}; y<image.height(); y++){
            int i {0}, j {0};
            int iter {0};
            if((x>=6 && x<image.width()-6) && (y>=6 && y<image.height()-6)){
                for(i; i<6; i++){
                    for(j; j<6; j++){
                        image.pixel(x, y) += image.pixel(x+i, y+j)+image.pixel(x-i, y-j);
                        iter+=2;
                    }
                }
                image.pixel(x, y) /= glm::vec3(iter);
            }
            
        }
    }
    image.save("output_l/convolution_boucles.png");
}
{
    //Avec matrices -> le vrai, normalement
    sil::Image logo {"images/logo.png"};
    sil::Image image {logo};
    std::vector<std::vector<float>> kernel {
        {1.f, 1.f, 1.f, 1.f},
        {1.f, 1.f, 1.f, 1.f},
        {1.f, 1.f, 1.f, 1.f},
        {1.f, 1.f, 1.f, 1.f}
    };
    float Total{0};
    for (std::vector<float> line : kernel)
    {
        for (float nb : line)
        {
            Total += nb;
        }
    }
    int coordx {0};
    int coordy {0};
    for(int x {0}; x<image.width(); x++){
        for(int y {0}; y<image.height(); y++){
            glm::vec3 couleur {0};
            for(int i {-(static_cast<int>(kernel.size())/2)}; i<(static_cast<int>(kernel.size())); i++){
                for(int j {-(static_cast<int>(kernel.size())/2)}; j<(static_cast<int>(kernel[0].size())); j++){
                    coordx = x+i;
                    coordy = y+i;
                    if(coordx>0 && coordx<image.width() && coordy>0 && coordy<image.height() && j+static_cast<int>(kernel[0].size())/2<kernel[0].size() && i+static_cast<int>(kernel.size())/2<kernel.size()){
                        couleur = image.pixel(coordx, coordy)*kernel.at(i+static_cast<int>(kernel.size())/2).at(j+static_cast<int>(kernel[0].size())/2);
                    }
                    else {
                        image.pixel(x, y) += glm::vec3(0); 
                    }
                }
            }
            if(Total!=0){
                couleur=couleur/Total;
            }
            image.pixel(x, y) = couleur;
        }
    }
    image.save("output_l/convolution.png");
}

}
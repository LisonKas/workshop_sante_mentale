
## Ne garder que le vert
|![image](./images/logo.png) |![image](./output_l/tout_en_vert.png)|
| ------------- |-------------|

---
## Échanger les canaux
|![image](./images/logo.png) |![image](./output_l/canaux_echanges.png)|
| ------------- |-------------|

---
## Noir & Blanc
|![image](./images/logo.png) |![image](./output_l/noir_et_blanc.png)|
| ------------- |-------------|

---
## Négatif
|![image](./images/logo.png) |![image](./output_l/negatif.png)|
| ------------- |-------------|

---
## Dégradé
![image](./output_l/degrade.png)

Le calcul a pris un peu de temps à être trouvé, mais c'est :
```cpp
float color = static_cast<float>(i) /(image.width()-1);
image.pixel(i, y) += color;
```
---

## Miroir
|![image](./images/logo.png) |![image](./output_l/miroir.png)|
| ------------- |-------------|

Nous avons eu deux façons de faire :
```cpp
std::swap(image.pixel(i, y), image.pixel(image.width()-1-i, y));
```
Ou avec une fonction :
```cpp
int miroir = image.width()-x;
imageInverse.pixel(miroir, y) = image.pixel(x, y);
```
---
![image](./output_s/miroir.png)

Autre effet "miroir" découvert avec ce code-ci :

```cpp
int miroir = image.width()-x;
glm::vec3 couleur = image.pixel(x, y);
image.pixel(miroir, y) = couleur;
```
---

## Image bruitée
|![image](./images/logo.png) |![image](./output_l/bruitee.png)|
| ------------- |-------------|

Pour cet effet, nous avons fait en sorte d'avoir des coordonnées de pixels `random`, et ensuite nous avons fait de même pour chaque partie de la couleur du pixel en question.

---
## Rotation 90°
|![image](./images/logo.png) |![image](./output_l/rotation_90.png)|
| ------------- |-------------|

Nous avons créé une nouvelle image en inversant les valeurs de `width` et de `height`. Puis nous avons recopié l'image à partir des bonnes coordonnées.

---
## RGB Split
|![image](./images/logo.png) |![image](./output_l/rgb_split.png)|
| ------------- |-------------|

On ne sait pas trop comment expliquer donc voici le code :
```cpp
sil::Image split{image.width(), image.height()};
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
```

---
## Luminosité

|Image de référence |Après éclaircissement |Après assombrissement |
| ------------- |-------------| -----|
|![image](./images/photo.jpg) |![image](./output_s/eclaircissement.jpg) |![image](./output_l/photo_apres_assombrissement.jpg)|

Pour les deux nous avons utilisé la fonction `pow()`, avec différentes valeurs de puissance.

---
## Disque
![image](./output_l/disque.png)

Dans le `if` pour colorer les bons pixels, nous avons utilisé :
```cpp
std::pow(i - image.width()/2, 2) + std::pow(j - image.height()/2, 2) <= std::pow(100, 2);
```

---
## Cercle
![image](./output_l/cercle.png)

Nous avons utilisé deux fois le même `if` que pour le disque, avec des valeurs différentes.

---
## Rosace
![image](./output_l/rosace.png)

Nous avons recréé une fonction `dessine_cercle`, que l'on a appelé plusieurs fois, pour dessiner les différents cercles de la rosace.

```cpp
sil::Image dessine_cercle(sil::Image& photo, int center_x, int center_y){
    int thickness {10};
    for (int i {0}; i<photo.width(); i++){
        for (int j {0}; j<photo.height(); j++){
            float const distance_carre { static_cast<float>(std::pow(i - center_x, 2) + std::pow(j - center_y, 2))};
            if (distance_carre <= std::pow(100, 2)){
                if (distance_carre >= std::pow(100-thickness, 2)){
                    photo.pixel(i, j) = glm::vec3{1};
                }
            }
        }
    }
    return photo;
}
```

---
## Mosaïque
|![image](./images/logo.png) |![image](./output_l/mosaique.png)|
| ------------- |-------------|

---
## Mosaïque miroir
| ![image](./images/logo.png)      | ![image](./output_l/mosaique_miroir_autre.png)        | ![image](./output_l/mosaique_miroir.png)  |
| ------------- |-------------| -----|

---
## Glitch
|![image](./images/logo.png) |![image](./output_l/glitch_2.png) |![image](./output_l/glitch.png)
| ------------- |-------------| -----|

---
## Fractale de Mandelbrot
![image](./output_l/fractale_mandelbrot.png)

---
## Vortex
|![image](./images/logo.png) |![image](./output_s/vortex.png)
| ------------- |-------------|

---
## Tramage
|![image](./images/photo.jpg) |![image](./output_s/tramage.jpg) |
| ------------- |-------------|

L'effet de tramage a été obtenu en adaptant le code trouvé sur [cet article](https://medium.com/the-bkpt/dithered-shading-tutorial-29f57d06ac39).

Ce qui donne :
```cpp
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
```

---
## Normalisation de l'histogramme
|![image](./images/photo.jpg) |![image](./output_s/histogramme.jpg)|
| ------------- |-------------|

---
## Convolution (et essais de netteté)

---
## Tri de pixels
|![image](./images/logo.png) |![image](./output_s/tri_pixels.png)|
| ------------- |-------------|

##Ne garder que le vert
![image](./images/logo.png)
![image](./output_l/tout_en_vert.png)

##Échanger les canaux
![image](./images/logo.png)
![image](./output_l/canaux_echanges.png)

##Noir & Blanc
![image](./images/logo.png)
![image](./output_l/noir_et_blanc.png)

##Négatif
![image](./images/logo.png)
![image](./output_l/negatif.png)

##Dégradé
![image](./output_l/degrade.png)
Le calcul a pris un peu de temps à être trouvé, mais c'est :
'''cpp
float color = static_cast<float>(i) /(image.width()-1);
image.pixel(i, y) += color;
'''

##Miroir
![image](./images/logo.png)
![image](./output_l/miroir.png)
Nous avons eu deux façon de faire :
'''cpp
std::swap(image.pixel(i, y), image.pixel(image.width()-1-i, y));
'''
ou avec une fonction MiroirV2
'''cpp
int miroir = image.width()-x;
imageInverse.pixel(miroir, y) = image.pixel(x, y);
'''

##Image bruitée
![image](./images/logo.png)
![image](./output_l/bruitee.png)
Pour cet effet là, nous avons fait en sorte d'avoir des coordonnées de pixels random, et ensuite nous avons fait de même pour chaque partie de la couleur du pixel en question.

##Rotation 90°
![image](./images/logo.png)
![image](./output_l/rotation_90.png)
Nous avons créer une nouvelle image en inversant les valeur de width et de height. Puis nous avons recopier l'image à partir des bonnes coordonnées.

##RGB Split
![image](./images/logo.png)
![image](./output_l/rgb_split.png)
Voir le code.

##Luminosité
Pour l'éclaircissement :
![image](./images/photo_faible_contraste.jpg)
![image](./output_l/photo_apres_eclaircissement.jpg)

Pour l'assombrissement :
![image](./output_l/photo_apres_assombrissement.jpg)

Pour les deux nous avons utilisé la fonction pow(), avec différentes valeurs de puissance.

##Disque
![image](./output_l/disque.png)
Dans le if pour colorer les bon pixels, nous avons utilisé :
'''cpp
std::pow(i - image.width()/2, 2) + std::pow(j - image.height()/2, 2) <= std::pow(100, 2);
'''

##Cercle
![image](./output_l/cercle.png)
Nous avons utilisé deux fois le même if que pour le disque, juste avec des valeurs différentes.

##Rosace
![image](./output_l/rosace.png)
Nous avons recréer une fonction dessine_cercle, que l'on a appeler plusieurs fois, pour dessiner les different cercles de la rosace.

##Mosaïque
![image](./images/logo.png)
![image](./output_l/rotation_90.png)

##Mosaïque miroir
![image](./images/logo.png)
![image](./output_l/mosaique_miroir_autre.png)
![image](./output_l/mosaique_miroir.png)

##Glitch
![image](./images/logo.png)
![image](./output_l/glitch_2.png)
![image](./output_l/glitch.png)

##Fractale de Mandelbrot
![image](./output_l/fractale_mandelbrot.png)

##Vortex
##Tramage
##Normalisation de l'histogramme
##Convolution (et essais de netteté)
##Tri de pixels
#include "matrice.h"

int maxPool(Matrice *in_feature_map, // input feature map
  unsigned short kernel_size, // La taille filtre
  unsigned short stride, // La valeur du pas de glissement
  unsigned short padding, // La valeur du padding (lignes et colonnes des zéros)
  double **in_feature_ma // output feature map
);

int minPool(Matrice *in_feature_map, // input feature map
  unsigned short kernel_size, // La taille filtre
  unsigned short stride, // La valeur du pas de glissement
  unsigned short padding, // La valeur du padding (lignes et colonnes des zéros)
  Matrice *in_feature_ma // output feature map
);

int avgPool(Matrice *in_feature_map, // input feature map
  unsigned short kernel_size, // La taille filtre
  unsigned short stride, // La valeur du pas de glissement
  unsigned short padding, // La valeur du padding (lignes et colonnes des zéros)
  Matrice *in_feature_ma // output feature map
);


int maxPool(*in_feature_map, // input feature map
  unsigned short kernel_size, // La taille filtre
  unsigned short stride, // La valeur du pas de glissement
  unsigned short padding, // La valeur du padding (lignes et colonnes des zéros)
  *in_feature_map // output feature map
)

int minPool(*in_feature_map, // input feature map
  *kernel, // Le filtre
  unsigned short stride, // La valeur du pas de glissement
  unsigned short padding, // La valeur du padding (lignes et colonnes des zéros)
  *in_feature_map // output feature map
)

int avgPool(*in_feature_map, // input feature map
  *kernel, // Le filtre
  unsigned short stride, // La valeur du pas de glissement
  unsigned short padding, // La valeur du padding (lignes et colonnes des zéros)
  *in_feature_map // output feature map
)

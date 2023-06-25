/***************************************************/
/* Alunos: Leandro Xavier da Silva e Natanael Nogueira Fernandes */
/* Matrícula: 20222045050255 e 20222045050379 */
/* Avaliação 04: Trabalho Final */
/* 26.06.23 - 2023.1 - Prof. Daniel Ferreira */
/* Compilador : ... ( DevC++ ou gcc ) versão... */
/***************************************************/

#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 

 // Essa estrutura contém informações sobre a largura, altura, valor máximo e matriz de pixels da imagem.
 struct ImagemPGM{ 
     int largura; 
     int altura; 
     int valorMax; 
     unsigned char** pixels; 
 }; 

// Função responsável por ler uma imagem PGM de um arquivo e retornar uma estrutura ImagemPGM preenchida com os dados da imagem
 struct ImagemPGM* lerImagemPGM(const char* nomeArquivo){ 
     FILE* arquivo = fopen(nomeArquivo, "r"); 
  
     if (arquivo == NULL){ 
         printf("Erro ao abrir o arquivo de imagem.\n"); 
         return NULL; 
     } 
  
     // Lendo o cabeçalho da imagem PGM 
     char formato[3]; 
     int largura, altura, valorMax; 
     fscanf(arquivo, "%s\n%d %d\n%d\n", formato, &largura, &altura, &valorMax); 
  
     // Alocando memória para a estrutura da imagem 
     struct ImagemPGM* imagem = (struct ImagemPGM*)malloc(sizeof(struct ImagemPGM)); 
     imagem->largura = largura; 
     imagem->altura = altura; 
     imagem->valorMax = valorMax; 
  
     // Alocando memória para os pixels da imagem 
     imagem->pixels = (unsigned char**)malloc(altura * sizeof(unsigned char*)); 
     for (int i = 0; i < altura; i++){ 
         imagem->pixels[i] = (unsigned char*)malloc(largura * sizeof(unsigned char)); 
     } 
  
     // Lendo os dados dos pixels da imagem 
     for (int i = 0; i < altura; i++){ 
         for (int j = 0; j < largura; j++){ 
             fscanf(arquivo, "%hhu", &imagem->pixels[i][j]); 
         } 
     } 
  
     fclose(arquivo); 
     return imagem; 
 } 

// Função responsável por liberar a memória alocada para a estrutura ImagemPGM e seus pixels
 void liberarImagemPGM(struct ImagemPGM* imagem){ 
     for (int i = 0; i < imagem->altura; i++){ 
         free(imagem->pixels[i]); 
     } 
     free(imagem->pixels); 
     free(imagem); 
 } 

// Função responsável por salvar uma sub-imagem em um arquivo no formato PGM
 void salvarSubImagemPGM(const char* nomeArquivo, struct ImagemPGM* subImagem){ 
     FILE* arquivo = fopen(nomeArquivo, "w"); 
  
     if (arquivo == NULL){ 
         printf("Erro ao criar o arquivo de sub-imagem.\n"); 
         return; 
     } 
  
     // Escrevendo o cabeçalho da sub-imagem PGM 
     fprintf(arquivo, "P2\n# 19b7ae0c1983488b205056be14cb8d3f_ascii.pgm\n%d %d\n%d\n", subImagem->largura, subImagem->altura, subImagem->valorMax); 
  
     // Escrevendo os dados dos pixels da sub-imagem 
     for (int i = 0; i < subImagem->altura; i++){ 
         for (int j = 0; j < subImagem->largura; j++){ 
             fprintf(arquivo, "%hhu ", subImagem->pixels[i][j]); 
         } 
         fprintf(arquivo, "\n"); 
     } 
  
     fclose(arquivo); 
 } 

// Função responsável por aplicar um filtro de média 3x3 na imagem fornecida
 void aplicarFiltroMedia(struct ImagemPGM* imagem){ 
     struct ImagemPGM* copiaImagem = (struct ImagemPGM*)malloc(sizeof(struct ImagemPGM)); 
     copiaImagem->largura = imagem->largura; 
     copiaImagem->altura = imagem->altura; 
     copiaImagem->valorMax = imagem->valorMax; 
     copiaImagem->pixels = (unsigned char**)malloc(imagem->altura * sizeof(unsigned char*)); 
  
     // Copiar a imagem original para a cópia 
     for (int i = 0; i < imagem->altura; i++){ 
         copiaImagem->pixels[i] = (unsigned char*)malloc(imagem->largura * sizeof(unsigned char)); 
         for (int j = 0; j < imagem->largura; j++){ 
             copiaImagem->pixels[i][j] = imagem->pixels[i][j]; 
         } 
     } 
  
     // Aplicar o filtro de média 3x3 
     int kernel[3][3] = { 
         {1, 1, 1}, 
         {1, 1, 1}, 
         {1, 1, 1} 
     }; 
  
     for (int i = 1; i < imagem->altura - 1; i++) { 
         for (int j = 1; j < imagem->largura - 1; j++) { 
             int soma = 0; 
             for (int k = -1; k <= 1; k++) { 
                 for (int l = -1; l <= 1; l++) { 
                     soma += copiaImagem->pixels[i + k][j + l] * kernel[k + 1][l + 1]; 
                 } 
             } 
             imagem->pixels[i][j] = soma / 9; 
         } 
     } 
  
     // Tratamento de bordas com zero 
     for (int i = 0; i < imagem->altura; i++){ 
         imagem->pixels[i][0] = 0;  // Bordas esquerda 
         imagem->pixels[i][imagem->largura - 1] = 0;  // Bordas direita 
     } 
     for (int j = 0; j < imagem->largura; j++){ 
         imagem->pixels[0][j] = 0;  // Bordas superior 
         imagem->pixels[imagem->altura - 1][j] = 0;  // Bordas inferior 
     } 
  
     // Liberar a memória alocada para a cópia da imagem 
     for (int i = 0; i < copiaImagem->altura; i++){ 
         free(copiaImagem->pixels[i]); 
     } 
     free(copiaImagem->pixels); 
     free(copiaImagem); 
 } 
  
 // Função responsável por gerar e salvar sub-imagens aleatórias da imagem fornecida,
 // com base no número de sub-imagens desejado, largura e altura especificadas. 
 void selecionarSubImagensAleatorias(struct ImagemPGM* imagem, int numSubImagens, int larguraSubImagem, int alturaSubImagem){ 
     int limiteHorizontal = imagem->largura - larguraSubImagem; 
     int limiteVertical = imagem->altura - alturaSubImagem; 
  
     for (int i = 0; i < numSubImagens; i++){ 
         // Gerando coordenadas aleatórias para a sub-imagem 
         int posX = rand() % limiteHorizontal; 
         int posY = rand() % limiteVertical; 
  
         // Criando a sub-imagem 
         struct ImagemPGM* subImagem = (struct ImagemPGM*)malloc(sizeof(struct ImagemPGM)); 
         subImagem->largura = larguraSubImagem; 
         subImagem->altura = alturaSubImagem; 
         subImagem->valorMax = imagem->valorMax; 
  
         // Alocando memória para os pixels da sub-imagem 
         subImagem->pixels = (unsigned char**)malloc(alturaSubImagem * sizeof(unsigned char*)); 
         for (int j = 0; j < alturaSubImagem; j++){ 
             subImagem->pixels[j] = (unsigned char*)malloc(larguraSubImagem * sizeof(unsigned char)); 
         } 
  
         // Copiando os pixels da sub-imagem da imagem original 
         for (int y = 0; y < alturaSubImagem; y++){ 
             for (int x = 0; x < larguraSubImagem; x++){ 
                 subImagem->pixels[y][x] = imagem->pixels[posY + y][posX + x]; 
             } 
         } 
  
         // Aplicando o filtro de média na sub-imagem 
         aplicarFiltroMedia(subImagem); 
  
         // Salvando a sub-imagem em um arquivo 
         char nomeArquivo[20]; 
         sprintf(nomeArquivo, "subimagem%d.pgm", i + 1); 
         salvarSubImagemPGM(nomeArquivo, subImagem); 
  
         // Liberando a memória alocada para a sub-imagem 
         for (int j = 0; j < alturaSubImagem; j++){ 
             free(subImagem->pixels[j]); 
         } 
         free(subImagem->pixels); 
         free(subImagem); 
     } 
 } 
  
 int main(){ 
     // Definindo a semente aleatória com base no horário atual
     srand(time(NULL)); 
  
     // Lendo a imagem PGM 
     struct ImagemPGM* imagem = lerImagemPGM("19b7ae0c1983488b205056be14cb8d3f_ascii.pgm"); 
  
     // Solicitando a quantidade e tamanho das sub-imagens ao usuário 
     int quantidadeSubImagens, larguraSubImagem, alturaSubImagem; 
     printf("Digite a quantidade de sub-imagens a serem geradas: "); 
     scanf("%d", &quantidadeSubImagens); 
     printf("Digite a largura das sub-imagens: "); 
     scanf("%d", &larguraSubImagem); 
     printf("Digite a altura das sub-imagens: "); 
     scanf("%d", &alturaSubImagem); 
  
     // Gerando e salvando as sub-imagens aleatórias com filtro de média 
     selecionarSubImagensAleatorias(imagem, quantidadeSubImagens, larguraSubImagem, alturaSubImagem); 
  
     // Liberando a memória alocada para a imagem 
     liberarImagemPGM(imagem); 
  
     return 0; 
 }

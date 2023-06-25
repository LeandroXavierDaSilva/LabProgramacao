/***************************************************/
/* Alunos: Leandro Xavier da Silva e Natanael Nogueira Fernandes */
/* Matrícula: 20222045050255 e 20222045050379 */
/* Avaliação 04: Trabalho Final */
/* 26.06.23 - 2023.1 - Prof. Daniel Ferreira */
/* Compilador : ... ( DevC++ ou gcc ) versão... */
/***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct{
    int largura;
    int altura;
    int *pixels;
} ImagemPGM;

// Função para carregar uma imagem PGM a partir de um arquivo
int carregarImagemPGM(const char *nomeArquivo, ImagemPGM *imagem){
    FILE *arquivo;
    char linha[100];
    int maxValor;
    int i, j;
    
    // Abre o arquivo para leitura
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }
    
    // Lendo o cabeçalho PGM
    fgets(linha, sizeof(linha), arquivo);
    if (strcmp(linha, "P2\n") != 0){
        printf("Formato de arquivo PGM inválido.\n");
        fclose(arquivo);
        return 0;
    }
    
    // Ignorando linhas de comentário
    fgets(linha, sizeof(linha), arquivo);
    while (linha[0] == '#'){
        fgets(linha, sizeof(linha), arquivo);
    }
    
    // Lendo largura e altura da imagem
    sscanf(linha, "%d %d", &imagem->largura, &imagem->altura);
    
    // Lendo o valor máximo dos pixels
    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "%d", &maxValor);
    
    // Alocando memória para os pixels
    imagem->pixels = (int *)malloc(imagem->largura * imagem->altura * sizeof(int));
    if (imagem->pixels == NULL){
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return 0;
    }
    
    // Lendo os pixels da imagem
    for (i = 0; i < imagem->altura; i++){
        for (j = 0; j < imagem->largura; j++){
            fscanf(arquivo, "%d", &imagem->pixels[i * imagem->largura + j]);
        }
    }
    
    fclose(arquivo);
    return 1;
}

// Função para liberar a memória alocada para uma imagem
void liberarImagemPGM(ImagemPGM *imagem){
    if (imagem->pixels != NULL){
        free(imagem->pixels);
        imagem->pixels = NULL;
    }
}

// Função para calcular o erro médio quadrático entre duas imagens
double calcularErroMedioQuadratico(const ImagemPGM *imagem1, const ImagemPGM *imagem2, int x, int y){
    double erro = 0.0;
    int i, j;
    
    // Percorre os pixels da sub-imagem e da região correspondente na imagem original
    for (i = 0; i < imagem2->altura; i++){
        for (j = 0; j < imagem2->largura; j++){
            int pixel1 = imagem1->pixels[(y + i) * imagem1->largura + (x + j)];
            int pixel2 = imagem2->pixels[i * imagem2->largura + j];
            erro += ((pixel1 - pixel2) * (pixel1 - pixel2));
        }
    }
    
    erro /= (imagem2->largura * imagem2->altura);
    return erro;
}

// Função para buscar sub-imagens em uma imagem original
void buscarSubImagens(const char *diretorio, const ImagemPGM *imagemOriginal, int numSubImagens){
    char nomeArquivo[100];
    int i, j, x, y;
    
    FILE *resultado = fopen("resultado.txt", "w");
    if (resultado == NULL){
        printf("Erro ao criar o arquivo de resultado.\n");
        return;
    }
    
    // Itera sobre as sub-imagens
    for (i = 0; i < numSubImagens; i++){
        sprintf(nomeArquivo, "%s/subimagem%d.pgm", diretorio, i + 1);
        
        ImagemPGM subImagem;
        // Carrega a sub-imagem
        if (carregarImagemPGM(nomeArquivo, &subImagem)){
            double menorErro = -1.0;
            int encontrada = 0;
            int coordX = -1;
            int coordY = -1;
            
            // Percorre a imagem original em busca da melhor correspondência
            for (y = 0; y <= imagemOriginal->altura - subImagem.altura; y++){
                for (x = 0; x <= imagemOriginal->largura - subImagem.largura; x++){
                    double erro = calcularErroMedioQuadratico(imagemOriginal, &subImagem, x, y);
                    
                    if (encontrada == 0 || erro < menorErro){
                        menorErro = erro;
                        encontrada = 1;
                        coordX = x;
                        coordY = y;
                    }
                }
            }
            
            // Escreve o resultado da busca no arquivo de resultado
            if (encontrada){
                fprintf(resultado, "Subimagem %d encontrada na posição (%d, %d)\n", i + 1, coordX, coordY);
            }else{
                fprintf(resultado, "Subimagem %d não encontrada\n", i + 1);
            }
            
            liberarImagemPGM(&subImagem);
        }else{
            printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        }
    }
    
    fclose(resultado);
}

int main(){
    char diretorioSubImagens[100];
    char nomeArquivoImagem[100];
    int numSubImagens;
    ImagemPGM imagemOriginal;
    clock_t begin = clock();
    
    // Solicita ao usuário o diretório das sub-imagens, o nome da imagem original e o número de sub-imagens
    printf("Digite o diretório das sub-imagens: ");
    scanf("%s", diretorioSubImagens);
    
    printf("Digite o nome da imagem original: ");
    scanf("%s", nomeArquivoImagem);
    
    printf("Digite o número de sub-imagens: ");
    scanf("%d", &numSubImagens);
    
    // Carrega a imagem original
    if (carregarImagemPGM(nomeArquivoImagem, &imagemOriginal)){
        // Busca as sub-imagens na imagem original
        buscarSubImagens(diretorioSubImagens, &imagemOriginal, numSubImagens);
        // Libera a memória alocada para a imagem original
        liberarImagemPGM(&imagemOriginal);
    }else{
        printf("Erro ao abrir o arquivo %s\n", nomeArquivoImagem);
    }
    
    clock_t end = clock();
    double tempoTotal = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo total de execução: %.2lf segundos (%.2lf minutos)\n", tempoTotal, tempoTotal/60);
    return 0;
}

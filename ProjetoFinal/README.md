<h1 align="center"> Projeto Final: Busca de Regiões em Imagens </h1> 
  
 #Sobre o projeto: 
   Esse projeto é o Trabalho Final desenvolvido pelos alunos *Leandro Xavier da Silva* e *Natanael Nogueira Fernandes*, como avaliação da disciplina de Laboratório de Programação ministrada pelo professor *Daniel Ferreira* no período letivo 2023.1. 
  
 Neste trabalho, nós implementamos em Linguagem C dois algoritmos para resolver o problema a seguir. 
  
 - ## Algoritmo 1: 
  
   O algoritmo lê uma imagem PGM, gera sub-imagens aleatórias com base nos parâmetros especificados, aplica um filtro de média a essas sub-imagens e as salva em arquivos separados. 
  
 - ## Algoritmo 2: 
  
   O algoritmo implementa um sistema de busca de sub-imagens em uma imagem original utilizando o cálculo do erro médio quadrático como critério de similaridade, assim salvando as condenadas de cada sub-imagem. 
  
 # Funcionamento dos Algoritmos: 
  
 - ## Algoritmo 1: 
  
 A estrutura **ImagemPGM** é definida para armazenar informações sobre a imagem, como largura, altura, valor máximo e matriz de pixels. 
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/f2f99854-9ff5-4a45-859a-683f07fce130) 
  
 A função **lerImagemPGM** recebe o nome de um arquivo de imagem PGM como entrada e retorna uma estrutura ImagemPGM preenchida com os dados da imagem. Ela lê o cabeçalho do arquivo PGM (formato, largura, altura e valor máximo) e aloca memória para a estrutura e para a matriz de pixels. Em seguida, lê os valores dos pixels da imagem do arquivo. 
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/bceb296b-abf3-4d73-8d4d-505b2b1421ec) 
  
  
 A função **liberarImagemPGM** é responsável por liberar a memória alocada para a estrutura ImagemPGM e seus pixels. 
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/d8fef485-9f7b-49f2-8f00-042dda32afd8) 
  
  
 A função **salvarSubImagemPGM** recebe o nome de um arquivo e uma estrutura ImagemPGM representando uma sub-imagem. Ela cria um novo arquivo PGM e escreve o cabeçalho e os dados dos pixels da sub-imagem no arquivo. 
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/6fabc1a8-87d2-4555-8f8d-15691f3009c4) 
  
  
 A função **aplicarFiltroMedia** recebe uma estrutura ImagemPGM e aplica um filtro de média 3x3 na imagem. Ela cria uma cópia da imagem original, percorre os pixels da imagem (exceto as bordas) e calcula a média dos pixels vizinhos usando uma máscara de convolução 3x3. O resultado é armazenado na imagem original. 
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/d647c4b3-50ca-4a0b-b70c-f63f864acefc) 
  
 Essa função tambem inclue um tratamento de bordas com 0: 
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/9feb4503-392e-45d9-b252-a5c264af82ef) 
  
 A função **selecionarSubImagensAleatorias** recebe uma estrutura ImagemPGM, o número de sub-imagens desejadas, a largura e a altura das sub-imagens. Ela gera sub-imagens aleatórias com base nas coordenadas especificadas e aplica o filtro de média em cada sub-imagem. Em seguida, salva as sub-imagens em arquivos separados. 
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/68ef2ffb-60ca-4f8f-8208-1e66debd0319) 
 ![image](https://github.com/Neitan0/teste/assets/127685007/c633bd37-92bf-42da-9389-ab96f18f8bf2) 
  
  
  
 A função **main** é a função principal do programa. Ela começa definindo a semente aleatória com base no horário atual. Em seguida, lê a imagem PGM a partir de um arquivo chamado "19b7ae0c1983488b205056be14cb8d3f_ascii.pgm". 
  
 O programa solicita ao usuário a quantidade de sub-imagens a serem geradas, bem como a largura e altura desejadas para cada sub-imagem. 
  
 Em seguida, a função selecionarSubImagensAleatorias é chamada para gerar e salvar as sub-imagens aleatórias com o filtro de média aplicado. 
  
 Finalmente, a memória alocada para a imagem principal é liberada usando a função liberarImagemPGM, e o programa é encerrado. 
  
  
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/81981d15-65af-4952-9603-2d2d50510678) 
  
 - ## Algoritmo 2: 
  
 O código começa com a definição da estrutura **ImagemPGM**, que armazena a largura, altura e os pixels da imagem. 
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/6289669f-9db7-4f6e-bbed-6d61bda9fd17) 
  
 A função **carregarImagemPGM** é responsável por carregar uma imagem PGM a partir de um arquivo. Ela recebe o nome do arquivo e um ponteiro para a estrutura ImagemPGM onde os dados serão armazenados. Essa função lê o cabeçalho do arquivo PGM, obtém as informações de largura, altura e valor máximo dos pixels, aloca a memória necessária para os pixels e lê os valores dos pixels da imagem. 
  
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/3a9b0291-ca4d-491f-bb5c-79fd7f0e2c3d) 
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/8513f7a5-ea5a-48fe-bb26-de2ce22c3a01) 
  
  
 A função **liberarImagemPGM** é utilizada para liberar a memória alocada para uma imagem. 
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/03a69322-11a0-439d-aa5e-38aa0f235f1e) 
  
  
 A função **calcularErroMedioQuadratico** calcula o erro médio quadrático entre duas imagens. Ela recebe dois ponteiros para ImagemPGM, representando a imagem original e uma sub-imagem, além das coordenadas x e y da região correspondente na imagem original. Essa função percorre os pixels da sub-imagem e da região correspondente na imagem original, calculando o erro médio quadrático entre eles. 
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/fa6af1c9-c78d-407a-9a99-52901b590bf7) 
  
  
 A função **buscarSubImagens** realiza a busca das sub-imagens na imagem original. Ela recebe o diretório onde estão armazenadas as sub-imagens, um ponteiro para a imagem original e o número de sub-imagens a serem buscadas. Essa função itera sobre as sub-imagens, carrega cada uma delas e percorre a imagem original em busca da melhor correspondência utilizando a função calcularErroMedioQuadratico. O resultado da busca é armazenado em um arquivo de texto chamado "resultado.txt". 
  
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/4021c83f-6fd3-41f0-8555-59240c65dd0d) 
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/be3ef061-2dcf-48af-a4d5-71b00bd3da58) 
  
  
 A função **main** é a função principal do programa. Ela solicita ao usuário o diretório das sub-imagens, o nome da imagem original e o número de sub-imagens. Em seguida, carrega a imagem original utilizando a função **carregarImagemPGM**, chama a função **buscarSubImagens** e, por fim, libera a memória alocada para a imagem original utilizando **liberarImagemPGM**. O tempo total de execução do programa também é calculado e exibido. 
  
  
  
 ![image](https://github.com/Neitan0/teste/assets/127685007/2c64a4b7-c436-41c3-845d-6a5bc113bb66) 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 

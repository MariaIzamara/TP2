typedef struct {
    GLfloat x, y, z; 
} coordenadas;

//Localização da câmera
coordenadas cameraFixa, cameraOlha, local,  centro, mouse, vetor;

//Localização dos brinquedos
coordenadas rodaGiganteL, torreL, carrosselL;

//Tamanho dos brinquedos
coordenadas rodaGiganteT, torreT, carrosselT;

//Localização dos objetos
coordenadas chaoL, carroBrownL, carroRedL, carroGrayL, carroBlueL, caminhoQL, caminhoCL, caminhoRL, banco4L, bancoPL, poste4L, cemiterioL;
coordenadas cemiterio1L, arvoreL, arvore1L, lixeira1L, lixeira2L;

//Tamanho dos objetos
coordenadas chaoT, carroBrownT, carroRedT, carroGrayT, carroBlueT, caminhoQT, caminhoCT, caminhoRT, banco4T, bancoPT, poste4T, cemiterioT;
coordenadas cemiterio1T, arvoreT, arvore1T, lixeira1T, lixeira2T;

//configura alguns parâmetros do modelo de iluminação
typedef struct {
    //a cor final do vértice pode ser dada pelo somatório dessas 4 primeiros componentes
	GLfloat ambiente[4];    //é indiretamente iluminado pelas “infinitas interações” da luz na cena
	GLfloat difusa[4];  //tem características de objetos foscos (ásperos)
	GLfloat especular[4];   //tem características de objetos polidos e reflete a cor da luz
    GLfloat emissiva[4];    //pode emitir [0, 100%] luz de uma cor 
    GLfloat posicao[4];
    //GLfloat brilhosidade[1];
} iluminacao;


iluminacao luzC = { {0.176, 0.176, 0.176, 1.0},
                    {0.5, 0.5, 0.5, 1.0},
                    {1.0, 1.0, 1.0, 1.0},
                    {0.0, 20.0, 0.0, 1.0} };

typedef struct {
    GLint a;
    GLint b;
    GLint c;
    GLint d;
} telas;

telas park, instructions, credits, exits, back;

//variáveis para verificação
bool luz = true, nevoa = true, som = true;

int modoCamera = 1; //modo padrão
int tela = 0;    //variável que me diz em qual tela estou
int mundoW, mundoH;  //variáveis que guardam a altura e largura do meu mundo
float theta, phi; //tipo no 2D
int brinquedoAtual = 0;

float corNevoa[3] = {0.176, 0.176, 0.176};
float corMaterial[3] = {1, 1, 1};

//brinquedos

//Roda Gigante
float anguloRodaGigante = 0;
//Carrossel
float anguloCarrossel = 0;
//Torre de Queda
int permisaoSubir = 0, permisaoDescer = 0, aguardaEmBaixo = 1, aguardaEmCima = 0;
float alturaTorre = -7.8;
float tempo = 0;

//variáveis de controle da camera no modo 2
int a = 0, d = 0, w = 0, s = 0, q = 0, e = 0;

//variáveis de controle do volume do som
int vA = 0, vD = 0;
float volume;   //controla o volume da música

//imagens
GLuint idTexturaMenu;
GLuint idTexturaParkT;
GLuint idTexturaInstructionsT;
GLuint idTexturaCreditsT;
GLuint idTexturaExitT;
GLuint idTexturaInstructions;
GLuint idTexturaCredits;
GLuint idTexturaBackT;

//objetos
GLMmodel* chaoO = NULL;   
GLMmodel* rodagiganteBaseO = NULL;
GLMmodel* rodagiganteRodaO = NULL;
GLMmodel* rodagiganteCarrinhoO = NULL;
GLMmodel* torreBaseO = NULL;
GLMmodel* torreCarrinhoO = NULL;
GLMmodel* carrosselBaseO = NULL;
GLMmodel* carrosselCorpoO = NULL;
GLMmodel* carroBrownO = NULL;
GLMmodel* carroBlueO = NULL;
GLMmodel* carroRedO = NULL;
GLMmodel* carroGrayO = NULL;
GLMmodel* caminhoQO = NULL;
GLMmodel* caminhoCO = NULL;
GLMmodel* caminhoRO = NULL;
GLMmodel* banco4O = NULL;
GLMmodel* bancoPO = NULL;
GLMmodel* poste4O = NULL;
GLMmodel* cemiterioO = NULL;
GLMmodel* cemiterio1O = NULL;
GLMmodel* arvoreO = NULL;
GLMmodel* arvore1O = NULL;
GLMmodel* lixeira1O = NULL;
GLMmodel* lixeira2O = NULL;



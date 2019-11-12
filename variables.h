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
coordenadas chaoL, terraL, addTorreL, bancoL, caminhoL, carroBrownL, carroRedL, carroGrayL, carroBlueL, paredeArvoreL, paredeArvore2L;

//Tamanho dos objetos
coordenadas chaoT, terraT, addTorreT, entradaT, bancoT, caminhoT, carroBrownT, carroRedT, carroGrayT, carroBlueT, paredeArvoreT, paredeArvore2T;

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


iluminacao luzC = { {0.0, 0.5, 0.0, 1.0},
                    {0.5, 0.5, 0.5, 1.0},
                    {1.0, 1.0, 1.0, 1.0},
                    {0.0, 0.0, 0.0, 1.0} };

/*
iluminacao materialC = { {0.7f, 0.7f, 0.7f, 1},
                         {0.8f, 0.8f, 0.8f, 1},
                         {1.0f, 1.0f, 1.0f, 1.0f} };
                
iluminacao brilhoC = { {}, {}, {}, {}, {}, {100.0f}};
*/


typedef struct {
    GLint a;
    GLint b;
    GLint c;
    GLint d;
} telas;

telas park, instructions, credits, exits, back;

//variáveis para verificação
bool luz = false, nevoa = false, som = true;

int modoCamera = 1; //modo padrão
int tela = 0;    //variável que me diz em qual tela estou
int mundoW, mundoH;  //variáveis que guardam a altura e largura do meu mundo
float theta, phi; //tipo no 2D
float volume;   //controla o volume da música

float corNevoa[3] = {0.176, 0.176, 0.176};
float corMaterial[3] = {1, 1, 1};

//brinquedos

//Roda Gigante
float anguloRodaGigante = 0;
float anguloCarrossel = 0;
//Torre de Queda
int permisaoSubir = 0, permisaoDescer = 0, aguardaEmBaixo = 1, aguardaEmCima = 0;
float alturaTorre = -7.8;
float tempo = 0;

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
GLMmodel* pedraTorreO = NULL;  
GLMmodel* entradaO = NULL;
GLMmodel* caminhoO = NULL;
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
GLMmodel* paredeArvoreO = NULL;
GLMmodel* paredeArvore2O = NULL;

#define AumentoAngulo_RodaGigante 1
#define AumentoAngulo_Carrossel 0,05
#define AnguloEntreCarrinhos M_PI/4



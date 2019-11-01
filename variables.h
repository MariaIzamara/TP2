typedef struct {
    GLfloat x, y, z; 
} coordenadas;

//Localização de objetos
coordenadas chaoL, terraL, arvoreL;

//Localização da câmera
coordenadas cameraFixa, local,  centro, mouse, vetor;

//Tamanho dos objetos
coordenadas chaoT, terraT, arvoreT;

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

iluminacao luzC = { {1.0, 1.0, 1.0, 1.0},
                    {1.0, 1.0, 1.0, 1.0},
                    {0.5, 0.5, 0.5, 0.5},
                    {1.0, 1.0, 1.0, 1.0} 
                    {cameraFixa.x, cameraFixa.y, cameraFixa.z, 0}};

/*
iluminacao materialC = { {0.7f, 0.7f, 0.7f, 1.0f},
                         {0.8f, 0.8f, 0.8f, 1.0f},
                         {1.0f, 1.0f, 1.0f, 1.0f} };
                
iluminacao brilhoC = { {}, {}, {}, {}, {}, {100.0f}};
*/

int modoCamera = 1; //modo padrão
float theta = 0, phi = 90; //tipo no 2D

//verifica se a luz está ou não acessa
bool luz = true;

//GLuint idTexturaGrama; // imagem da grama

//objetos
GLMmodel* chaoO = NULL;   
GLMmodel* arvoreO = NULL;  
GLMmodel* terraO = NULL;






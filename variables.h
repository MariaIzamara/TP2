typedef struct {
    float x, y, z; 
} coordenadas;

//Localização de objetos
coordenadas chaoL, terraL, arvoreL;

//Localização da câmera
coordenadas cameraFixa, local, mouse, vetor, centro;

//Tamanho dos objetos
coordenadas chaoT, terraT, arvoreT;


int modoCamera = 1; //modo padrão
int teta = 0, phi = 90; //tipo no 2D

GLuint idTexturaGrama; // imagem da grama

//objetos
GLMmodel* chaoO = NULL;   
GLMmodel* arvoreO = NULL;  
GLMmodel* terraO = NULL;






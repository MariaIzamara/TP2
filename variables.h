typedef struct {
    GLfloat x, y, z; 
} coordenadas;

coordenadas cameraFixa, local, roda, mouse, vetor, centro;


int modoCamera = 1; //modo padrão
int teta = 0, phi = 90; //tipo no 2D

GLuint idTexturaGrama; // imagem da grama

GLMmodel* rodaM = NULL;   //objeto





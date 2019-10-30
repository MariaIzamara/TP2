#include "libraries.h"
#include "variables.h"


GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}


void desenhaObjeto(GLMmodel* objeto, char* string, coordenadas coordenada){
    if(objeto == NULL){
            objeto = glmReadOBJ(string);    //manda pro objeto sua localização
            if(!objeto)
                exit(0);
            glmScale(objeto, 90.0); //o último parâmetro muda o que?
            glmUnitize(objeto);
            glmFacetNormals(objeto);
            glmVertexNormals(objeto, 90.0, 1);  //o que esses parârametros mudam?
        }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glPopMatrix();
    glmDraw(objeto, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

void desenhaCena(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a tela com a cor definida e limpa o mapa de profundidade
    glLoadIdentity();  //carrega a matriz identidade do modelo de visualização, sempre utilize antes de usar LookAt
    
    gluLookAt(local.x, local.y, local.z,   //onde a câmera  está
              0, 0, 0,                     //pra onde a câmera tá olhando
              0, 1, 0);                    //coordenada que ela gira
    
    desenhaObjeto(rodaM, "objetos/rodax.obj", roda);
    
    glutSwapBuffers();     //SwapBuffers funciona como o Flush, mas para o modo de buffer duplo
}

void inicializa() {
    
    srand(time(0));
    glClearColor(0, 0, 0, 0);   //cor de fundo preto
    // habilita mesclagem de cores, para termos suporte a texturas com transparência
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //para poder criar objetos transparentes

    local.x = 0;
    local.y = 0;
    local.z = 20;

    roda.x = 5;
    roda.y = 5;
    roda.z = 0;

    keyStates[1] = true;
}

void redimensiona(int width, int height) {

    glEnable(GL_DEPTH_TEST);             //ativa o Z buffer
    glViewport (0, 0, width, height);    //define a proporção da janela de visualização
    glMatrixMode (GL_PROJECTION);        //define o tipo de matriz de transformação que será utilizada
    glLoadIdentity();                    //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente
    gluPerspective(90, (float)width/(float)height, 0.5, 200.0);   //funciona como se fosse o glOrtho, mas para o espaço 3D
    glMatrixMode(GL_MODELVIEW);                                   //ativa o modo de matriz de visualização para utilizar o LookAt
}

void teclado(unsigned char key, int x, int y) {
    switch (key){
        case 27:    //esc
            exit(0);
            break;
        case 1:     //câmera que tem visão de cima/diagonal
            local.x = 0;
            local.y = 0;
            local.z = 20;
            break;
        //câmera que tem visão de cada brinquedo
        case 'r':   //roller coaster (montanha-russa)
            local.x = 5;
            local.y = 5;
            local.z = 0;
            break;
    }
}

void atualizaCena(int periodo) {

    //pede ao GLUT para redesenhar a tela assim que possível
    glutPostRedisplay();
    //se registra novamente, para que fique sempre sendo chamada
    glutTimerFunc(periodo, atualizaCena, periodo);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);

    //glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   //para o que serve?

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(170, 70);
    glutCreateWindow("Haunted Park");
    

    glutDisplayFunc(desenhaCena);    
    glutReshapeFunc(redimensiona);

    glutKeyboardFunc(teclado);
  //glutKeyboardUpFunc(teclaLiberada);      //caso eu queira mudar tal estado assim que a pessoa soltar a tecla (keyboard[key] = false;)

    glutTimerFunc(0, atualizaCena, 33);

    inicializa();

    glutMainLoop();

    return 0;
}



   
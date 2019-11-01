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


void desenhaObjeto(GLMmodel* objeto, char* string, coordenadas coordenada, coordenadas tamanho){
    if(objeto == NULL){
            objeto = glmReadOBJ(string);    //manda pro objeto sua localização
            if(!objeto)
                exit(0);           
            glmScale(objeto, 90.0); //escala padrão, dentro de um obj
            glmUnitize(objeto);
            glmFacetNormals(objeto);
            glmVertexNormals(objeto, 90.0, 1);  //serviria se eu tivesse texturas diferentes, mas tem que ter por padrão
        }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glScalef(tamanho.x, tamanho.y, tamanho.z); //escala dentro de uma matriz
    glmDraw(objeto, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
    glPopMatrix();    
}

void posicionaCamera(int x, int y){ 
    vetor.x = (GLfloat)x - mouse.x; //vetor é o Pfinal - Pinicial;
    vetor.y = (GLfloat)y - mouse.y;

    mouse.x = x;
    mouse.y = y;

    if(phi>=180)
        phi=180;

    //printf("deltaX = %f deltaY = %f \n", vetor.x, vetor.y);

    teta += vetor.x/40.0;
    phi -= vetor.y/40.0;

    //printf("phi %f, teta %f\n", phi, teta);

    //aqui eu guardo a posição anterior do meu mouse
    
    //glutPostRedisplay(); //manda redesenhar a cena pra evitar lag (aquelas travadinhas)
}

void desenhaCena(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a tela com a cor definida e limpa o mapa de profundidade
    glLoadIdentity();  //carrega a matriz identidade do modelo de visualização, sempre utilize antes de usar LookAt
    
    //mudança de coordenadas retângular(a mais comum) para esféricas
    local.x = 50 * sin(phi) * cos(teta);
    local.z = 50 * sin(phi) * sin(teta);
    local.y = 50 * cos(phi);

    //printf("x=%f y=%f z=%f\n", local.x, local.y, local.z);

    switch(modoCamera){
        case 2:
            gluLookAt(centro.x, centro.y, centro.z,
                      local.x+centro.x, local.y, local.z+centro.z,
                      0, 1, 0);
            break;
        case 3:
            gluLookAt(local.x+centro.x, local.y, local.z+centro.z,
                      centro.x, centro.y, centro.z,
                      0, 1, 0);
            break;
        default:    //modoCamera = 1;
            gluLookAt(cameraFixa.x, cameraFixa.y, cameraFixa.z,   //onde a câmera  está
                      0, 0, 0,                     //pra onde a câmera tá olhando
                      0, 1, 0);                    //coordenada que ela gira
    }

    desenhaObjeto(chaoO, "objetos/floor.obj", chaoL, chaoT);
    desenhaObjeto(terraO, "objetos/tree.obj", terraL, terraT);
    //desenhaObjeto(arvoreO, "objetos/tree.obj", arvoreL, arvoreT);
    
    glutSwapBuffers();     //SwapBuffers funciona como o Flush, mas para o modo de buffer duplo
}


void inicializa() {
    
    srand(time(0));
    glClearColor(0.176, 0.176, 0.176, 0);   //cor de fundo preto
    // habilita mesclagem de cores, para termos suporte a texturas com transparência
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //para poder criar objetos transparentes

    centro.x = centro.y = centro.z = 0;
    mouse.x = mouse.y = mouse.z = 0;
    phi = 90;
    teta = 0;

    cameraFixa.x = 0;
    cameraFixa.y = 60;
    cameraFixa.z = 100;  //maior que o raio da minha esfera

    chaoL.x = 0;
    chaoL.y = 0;
    chaoL.z = 2;

    chaoT.x = chaoT.y = chaoT.z = 60;
    
    terraL.x = 0;
    terraL.y = 0.1;
    terraL.z = 2;

    terraT.x = terraT.y = terraT.z = 5;

    arvoreL.x = 0;
    arvoreL.y = 0;
    arvoreL.z = 2;

    arvoreT.x = arvoreT.y = arvoreT.z = 10;
}

void redimensiona(int width, int height) {

    glEnable(GL_DEPTH_TEST);             //ativa o Z buffer
    glViewport (0, 0, width, height);    //define a proporção da janela de visualização
    glMatrixMode (GL_PROJECTION);        //define o tipo de matriz de transformação que será utilizada
    glLoadIdentity();                    //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente
    gluPerspective(90, (float)width/(float)height, 0.2, 200.0);   //funciona como se fosse o glOrtho, mas para o espaço 3D
    glMatrixMode(GL_MODELVIEW);                                   //ativa o modo de matriz de visualização para utilizar o LookAt
}

void teclado(unsigned char key, int x, int y) {
    switch (key){
        case 27:    //esc
            exit(0);
            break;
        case '1':     //câmera que tem visão de cima/diagonal
            modoCamera = 1;
            cameraFixa.x = -10;
            cameraFixa.y = 60;
            cameraFixa.z = 100;
            break;
        case '2':   //camêra em primeira pessoa
            modoCamera = 2;
            break;
        case '3':   //camêra em terceira pessoa
            modoCamera = 3;
            break;
        //câmera que tem visão de cada brinquedo
        case 'r':   //roller coaster (montanha-russa)
            modoCamera = 1;
            arvoreL.x = 0;
            arvoreL.y = 0;
            arvoreL.z = 2;
            break;
        case 'w':
            centro.x ++;
            break;
        case 's':
            centro.x --;
            break;
        case 'a':
            centro.z ++;
            break;
        case 'd':
            centro.z --;
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

    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   //configuração interna do opengl relativa à versões

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(170, 70);
    glutCreateWindow("Haunted Park");
    

    glutDisplayFunc(desenhaCena);    
    glutReshapeFunc(redimensiona);

    glutKeyboardFunc(teclado);
  //glutKeyboardUpFunc(teclaLiberada);      //caso eu queira mudar tal estado assim que a pessoa soltar a tecla (keyboard[key] = false;)

    glutTimerFunc(0, atualizaCena, 10);
    glutPassiveMotionFunc(posicionaCamera);

    inicializa();

    glutMainLoop();

    return 0;
}



   
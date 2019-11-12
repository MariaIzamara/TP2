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

void desenhaTextura(GLuint id, int mundoW, int mundoH) {
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0, 0, 0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, id);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
            glTexCoord2f(1, 0); glVertex3f(mundoW, 0, 0);
            glTexCoord2f(1, 1); glVertex3f(mundoW, mundoH, 0);
            glTexCoord2f(0, 1); glVertex3f(0, mundoH, 0);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void desenhaPalavra(GLuint id, int a, int b, int c, int d) {
    glEnable(GL_TEXTURE_2D); 
    glPushMatrix();
    //glTranslatef(a, c, 0);
    glBindTexture(GL_TEXTURE_2D, id);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex3f(a, c, 0);
            glTexCoord2f(0, 1); glVertex3f(a, d, 0);
            glTexCoord2f(1, 1); glVertex3f(b, d, 0);
            glTexCoord2f(1, 0); glVertex3f(b, c, 0);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void desenhaObjeto(GLMmodel* objeto, char* string, coordenadas coordenada, coordenadas tamanho) {
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
    glScalef(tamanho.x, tamanho.y, tamanho.z); //escala dentro de uma matriz de transformação
    glmDraw(objeto, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
    glPopMatrix();    
}

void acrescentarAngulos(){
    //arruma o ângulo da roda gigante
    if(anguloRodaGigante >= 360)
        anguloRodaGigante = 0;
    else
        anguloRodaGigante += 0.5;
}

void desenhaRodaGigante(GLMmodel* objeto1, GLMmodel* objeto2, GLMmodel* objeto3, char* string1, char* string2, char* string3, coordenadas coordenada, coordenadas tamanho){
    if(objeto1 == NULL){
        objeto1 = glmReadOBJ(string1);    
        if(!objeto1)
            exit(0);
        glmScale(objeto1, 90.0); 
        glmUnitize(objeto1);
        glmFacetNormals(objeto1);
        glmVertexNormals(objeto1, 90.0, 1); 
    }
    if(objeto2 == NULL){
        objeto2 = glmReadOBJ(string2);    
        if(!objeto2)
            exit(0);
        glmScale(objeto2, 90.0); 
        glmUnitize(objeto2);
        glmFacetNormals(objeto2);
        glmVertexNormals(objeto2, 90.0, 1);  
    }
    if(objeto3 == NULL){
        objeto3 = glmReadOBJ(string3);    
        if(!objeto3)
            exit(0);
        glmScale(objeto3, 90.0); 
        glmUnitize(objeto3);
        glmFacetNormals(objeto3);
        glmVertexNormals(objeto3, 90.0, 1); 
    }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glScalef(tamanho.x, tamanho.y, tamanho.z);
    glmDraw(objeto1, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
        //como os outros dois obj vão estar dentro do primeiro push, meus translate e rotate estarão de acordo com o do obj1
        glPushMatrix();
        glScalef(1.3, 1.3, 1);
        glTranslatef(0, 0.5, 0);    //aqui tá desenhado quase no centro do objeto1
        glRotatef(anguloRodaGigante, 0, 0, 1);   // [anguloRotacao, x, y, z] no caso eu giro tantos graus no eixo z.
        glmDraw(objeto2, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
        glRotatef(-anguloRodaGigante, 0, 0, 1); 
            for(int t=0; t<8; t++) {
                glPushMatrix();
                glScalef(0.2, 0.2, 0.2); //proporcional a escala do objeto1
                glTranslatef(4 * cos(anguloRodaGigante*M_PI/180 + t*M_PI/4), -4 * sin(anguloRodaGigante*M_PI/180 + t*M_PI/4), 0);
                glmDraw(objeto3, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
                glPopMatrix();
            }
        glPopMatrix();
    glPopMatrix();
}

void acrescentarAltura(){
    if(aguardaEmBaixo) {
        if(tempo < 80)
            tempo ++;
        else {
            tempo = 0;
            aguardaEmBaixo = 0;
            permisaoSubir = 1;
        }
    }
    if(permisaoSubir) {
        if(alturaTorre < 5.5)
            alturaTorre += 0.05;
        else {
            aguardaEmCima = 1;
            permisaoSubir = 0;
        }
    }
    if(aguardaEmCima) {
        if(tempo < 100)
            tempo ++;
        else {
            tempo = 0;
            aguardaEmCima = 0;
            permisaoDescer =  1;
        }
    }
    if(permisaoDescer) {
        if(alturaTorre > -7.3)
            alturaTorre -= 0.4;
        else {
            aguardaEmBaixo = 1;
            permisaoDescer = 0;
        }
    }
}

void desenhaTorre(GLMmodel* objeto1, GLMmodel* objeto2, char* string1, char* string2, coordenadas coordenada, coordenadas tamanho){
    if(objeto1 == NULL){
        objeto1 = glmReadOBJ(string1);    
        if(!objeto1)
            exit(0);
        glmScale(objeto1, 100.0); 
        glmUnitize(objeto1);
        glmFacetNormals(objeto1);
        glmVertexNormals(objeto1, 90.0, 1); 
    }
    if(objeto2 == NULL){
        objeto2 = glmReadOBJ(string2);    
        if(!objeto2)
            exit(0);
        glmScale(objeto2, 100.0); 
        glmUnitize(objeto2);
        glmFacetNormals(objeto2);
        glmVertexNormals(objeto2, 90.0, 1);  
    }
    glPushMatrix();
    glTranslatef(coordenada.x, coordenada.y, coordenada.z);
    glScalef(tamanho.x, tamanho.y, tamanho.z);
    glmDraw(objeto1, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
        //como esse próximo objeto esta dentro do primeiro push, tudo vai estar proporcional ao primeiro
        glPushMatrix();
        glScalef(0.12, 0.12, 0.12);
        glTranslatef(0, alturaTorre, 0);
        glmDraw(objeto2, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
        glPopMatrix();
    glPopMatrix();
}

void desenhaCena(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a tela com a cor definida e limpa o mapa de profundidade
    glLoadIdentity();  //carrega a matriz identidade do modelo de visualização, sempre utilize antes de usar LookAt
    
    if(tela == 0) {
        desenhaTextura(idTexturaMenu, mundoW, mundoH);
        desenhaPalavra(idTexturaParkT, park.a, park.b, park.c, park.d);
        desenhaPalavra(idTexturaInstructionsT, instructions.a, instructions.b, instructions.c, instructions.d);
        desenhaPalavra(idTexturaCreditsT, credits.a, credits.b, credits.c, credits.d);
        desenhaPalavra(idTexturaExitT, exits.a, exits.b, exits.c, exits.d);
    }
    else if(tela == 2) {
        desenhaTextura(idTexturaInstructions, mundoW, mundoH);
        desenhaPalavra(idTexturaBackT, back.a, back.b, back.c, back.d);
    }
    else if(tela == 3) {
        desenhaTextura(idTexturaCredits, mundoW, mundoH);
        desenhaPalavra(idTexturaBackT, back.a, back.b, back.c, back.d);
    }
    else if(tela == 1) {

        //mudança de coordenadas retangular(a mais comum) para esféricas, com raio = 100
        local.x = 100 * sin(phi) * cos(theta);
        local.z = 100 * sin(phi) * sin(theta);
        local.y = 100 * cos(phi);


        switch(modoCamera){
            case 2: //câmera em primeira pessoa que mexe as teclas (o mouse interferindo não ficou legal)
                gluLookAt(cameraFixa.x, 15, cameraFixa.z+20,
                          0, 0, 0,
                          0, 1, 0);
                break;
            case 3: //usa o mouse ou as teclas
                gluLookAt(local.x+centro.x, local.y, local.z+centro.z,
                        centro.x, centro.y, centro.z,
                        0, 1, 0);
                break;
            default:    //modoCamera = 1;
                gluLookAt(cameraFixa.x, cameraFixa.y, cameraFixa.z,   //onde a câmera  está
                        cameraOlha.x, cameraOlha.y, cameraOlha.z,                     //pra onde a câmera tá olhando
                        0, 1, 0);                    //coordenada que ela gira
        }

        //começo meu jogo com iluminação
        if(!luz) {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT_MODEL_AMBIENT);
        }
        else {
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT_MODEL_AMBIENT);
        }

        //começo meu jogo com névoa
        if(!nevoa)
            glDisable(GL_FOG);
        else
            glEnable(GL_FOG);

        desenhaObjeto(chaoO, "objects/floor/floor.obj", chaoL, chaoT);
        //carros
        desenhaObjeto(carroBrownO, "objects/car/carBrown.obj", carroBrownL, carroBrownT);
        desenhaObjeto(carroBlueO, "objects/car/carBlue.obj", carroBlueL, carroBlueT);
        desenhaObjeto(carroRedO, "objects/car/carRed.obj", carroRedL, carroRedT);
        desenhaObjeto(carroGrayO, "objects/car/carGray.obj", carroGrayL, carroGrayT);

        //caminhos de terra
        //desenhaObjeto(caminhoO, "objects/tree/paredeArvore.obj", caminhoL, caminhoT);
        //desenhaObjeto(caminhoO, "objects/spinner/spinner.obj", caminhoL, caminhoT);

        //arvores
        desenhaObjeto(paredeArvoreO, "objects/tree/paredeArvore.obj", paredeArvoreL, paredeArvoreT);

        glRotatef(90, 0, 1, 0);   // [anguloRotacao, x, y, z] no caso eu giro tantos graus no eixo z.
        desenhaObjeto(paredeArvoreO, "objects/tree/natureza.obj", paredeArvore2L, paredeArvore2T);
        glRotatef(-90, 0, 1, 0);   // [anguloRotacao, x, y, z] no caso eu giro tantos graus no eixo z.
        //pedras perto da torre   
        //desenhaObjeto(pedraTorreO, "objects/lixeira/lixeira.obj", addTorreL, addTorreT);

        //Roda Gigante
        desenhaRodaGigante(rodagiganteBaseO, rodagiganteRodaO,rodagiganteCarrinhoO,"objects/rodaGigante/base.obj", "objects/rodaGigante/roda.obj", 
                            "objects/rodaGigante/carrinho.obj", rodaGiganteL, rodaGiganteT);
        //Torre de Queda
        desenhaTorre(torreBaseO, torreCarrinhoO, "objects/torre/torre.obj", "objects/torre/carrinho.obj", torreL, torreT);
        //Spinner
        //desenhaObjeto(spinnerO, "objects/arvores/arvoreMortaPedras.obj", spinnerL, spinnerT);
    }
    
    glutSwapBuffers();     //SwapBuffers funciona como o Flush, mas para o modo de buffer duplo
}

void inicializa() {
    
    srand(time(0));
    glClearColor(0.176, 0.176, 0.176, 0);   //cor de fundo preto

    // habilita mesclagem de cores, para termos suporte a texturas com transparência
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //para poder criar objetos transparentes

    //inicializa a musica --> por algum motivo eu não preciso disso
    //Mix_ResumeMusic()

    //luz ambiente global que é usada para iluminar uniformemente todos os objetos da cena
    glMaterialfv (GL_FRONT, GL_LIGHT_MODEL_AMBIENT, corMaterial);  
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, corMaterial);

    //iluminação
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzC.ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzC.difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzC.especular);
    glLightfv(GL_LIGHT0, GL_POSITION, luzC.posicao);
    
    //névoa
    glFogi(GL_FOG_MODE, GL_EXP); //modo de decaimento da névoa
    glFogf(GL_FOG_DENSITY, 0.02);    //densidade da névoa
    glFogfv(GL_FOG_COLOR, corNevoa);    //cor da névoa

    //mundoW = 1000 e mundoH = 600
    park.a = 108;
    park.b = 373;
    park.c = 292;
    park.d = 331;

    instructions.a = 108;
    instructions.b = 310;
    instructions.c = 347;
    instructions.d = 394;

    credits.a = 108;
    credits.b = 246;
    credits.c = 416;
    credits.d = 467;

    exits.a = 108;
    exits.b = 190;
    exits.c = 481;
    exits.d = 527;

    back.a = 860;
    back.b = 960;
    back.c = 492;
    back.d = 522;

    idTexturaMenu = carregaTextura("images/menu.png");
    idTexturaParkT = carregaTextura("images/park1.png");
    idTexturaInstructionsT = carregaTextura("images/instructions.png");
    idTexturaCreditsT = carregaTextura("images/credits.png");
    idTexturaExitT = carregaTextura("images/exits.png");
    idTexturaBackT = carregaTextura("images/back.png");
    idTexturaInstructions = carregaTextura("images/Instructions.png");
    idTexturaCredits = carregaTextura("images/Credits.png");

    centro.x = centro.y = centro.z = 0;
    mouse.x = mouse.y = mouse.z = 0;

    modoCamera = 1;
    phi = 90;
    theta = 0;

    cameraFixa.x = 0;
    cameraFixa.y = 50;
    cameraFixa.z = 75;  //maior que o raio da minha esfera
    cameraOlha.x = cameraOlha.y = cameraOlha.z = 0;

    chaoL.x = chaoL.y = chaoL.z = 0;
    chaoT.x = chaoT.z = 60;
    chaoT.y = 20;
    
    caminhoL.x = -25;
    caminhoL.y = 2.5;
    caminhoL.z = -45;

    caminhoT.x = 100;
    caminhoT.y = 100;
    caminhoT.z = 100;

    paredeArvoreL.x = 52;
    paredeArvoreL.y = 9;
    paredeArvoreL.z = 20;

    paredeArvoreT.x = paredeArvoreT.y = paredeArvoreT.z = 40; 

    paredeArvore2L.x = -10;
    paredeArvore2L.y = 15;
    paredeArvore2L.z = 0;

    paredeArvore2T.x = paredeArvore2T.y = paredeArvore2T.z = 40; 


    bancoL.x = 40;
    bancoL.y = 0.3;
    bancoL.z = 44;

    bancoT.x = bancoT.y = bancoT.z = 20;

    carroBrownL.x = 50; 
    carroBrownL.y = 3;
    carroBrownL.z = -55;

    carroBrownT.x = carroBrownT.y = carroBrownT.z = 7;

    carroBlueL.x = 50; 
    carroBlueL.y = 3;
    carroBlueL.z = -30.5;

    carroBlueT.x = carroBlueT.y = carroBlueT.z = 8;

    carroRedL.x = 23.7; 
    carroRedL.y = 3;
    carroRedL.z = -38.9;

    carroRedT.x = carroRedT.y = carroRedT.z = 8;

    carroGrayL.x = 23.7; 
    carroGrayL.y = 3;
    carroGrayL.z = -55;

    carroGrayT.x = carroGrayT.y = carroGrayT.z = 8;

    //Pedras
    addTorreL.x = -32;
    addTorreL.y = 8.5;
    addTorreL.z = -58;
    addTorreT.x = addTorreT.y = addTorreT.z = 7;

    //Roda Gigante
    rodaGiganteL.x = 0;
    rodaGiganteL.y = 15;
    rodaGiganteL.z = 10;
    rodaGiganteT.x = rodaGiganteT.y = 15;
    rodaGiganteT.z = 10;

    //Torre de Queda
    torreL.x = -35;
    torreL.y = 27;
    torreL.z = 10;
    torreT.x = torreT.z = 40;
    torreT.y = 25;

    //Spinner
    spinnerL.x = -20;
    spinnerL.y = 17;
    spinnerL.z = -20;
    spinnerT.x = spinnerT.y = spinnerT.z = 20;
}

void detectaMouse(int x, int y){ 

    //(x - mouse.x) e (y - mouse.y) são os vetores formados pelo ponto onde eu estava com o mouse e o novo local.
    theta += (x - mouse.x)/40.0;
    phi -= (y - mouse.y)/40.0;

    if(phi>=180)
        phi=180;

    //printf("x: %d y: %d\n", x, y);

    //aqui eu guardo a posição anterior do meu mouse
    mouse.x = x;
    mouse.y = y;
/*
    // Realizando o efeito hover no menu
    if(tela == 0) {
		if(mouse.x >= park.a && mouse.x <= park.b && mouse.y >= park.c && mouse.y <= park.d)
            idTexturaParkT = carregaTextura("images/parkB.png");
        else
            idTexturaParkT = carregaTextura("images/park1.png");
        if(mouse.x >= instructions.a && mouse.x <= instructions.b && mouse.y >= instructions.c && mouse.y <= instructions.d)
            idTexturaInstructionsT = carregaTextura("images/instructionsB.png");
        else
            idTexturaInstructionsT = carregaTextura("images/instructions.png");
        if(mouse.x >= credits.a && mouse.x <= credits.b && mouse.y >= credits.c && mouse.y <= credits.d)
            idTexturaCreditsT = carregaTextura("images/creditsB.png");
        else
            idTexturaCreditsT = carregaTextura("images/credits.png");
        if(mouse.x >= exits.a && mouse.x <= exits.b && mouse.y >= exits.c && mouse.y <= exits.d)
            idTexturaExitT = carregaTextura("images/exitsB.png");
        else 
            idTexturaExitT = carregaTextura("images/exits.png");
    }   
*/
    glutPostRedisplay(); //manda redesenhar a cena pra evitar lag (aquelas travadinhas)
}
/*
void detectaClique(int botao, int estado, int x, int y)
{
	switch(botao)
    {

		case GLUT_LEFT_BUTTON:  //se o botão esquerdo do mouse tiver sido pressionado

			//menu
			if(tela == 0) {
				//clicando "Go to the park"
				if(mouse.x >= park.a && mouse.x <= park.b && mouse.y >= park.c && mouse.y <= park.d) {
					tela = 1;
					glutReshapeWindow(mundoW, mundoH);  //chama a função que eu coloquei por padrão pra redimensionar
                }
                //clicando "Instructions"
                else if(mouse.x >= instructions.a && mouse.x <= instructions.b && mouse.y >= instructions.c && mouse.y <= instructions.d)
                    tela = 2;
                //clicando "Credits"
                else if(mouse.x >= credits.a && mouse.x <= credits.b && mouse.y >= credits.c && mouse.y <= credits.d)
                    tela = 3;
                //clicando "Exit"
                else if(mouse.x >= exits.a && mouse.x <= exits.b && mouse.y >= exits.c && mouse.y <= exits.d)
                    exit(0);
            }
            //instructions
            if(tela == 2) {
                if(mouse.x >= back.a && mouse.x <= back.b && mouse.y >= back.c && mouse.y <= back.d)
                    tela = 0;
            }
            //credits
            if(tela == 3) {
                if(mouse.x >= back.a && mouse.x <= back.b && mouse.y >= back.c && mouse.y <= back.d)
                    tela = 0;
            }
    }
}
*/

void redimensiona(int width, int height) {
    mundoW = width;     //1000
    mundoH = height;    //600

    switch(tela) {
        case 0:           
        case 2:
        case 3: 
            glDisable(GL_DEPTH_TEST);
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, width, 0, height, -1, 1);
            glMatrixMode(GL_MODELVIEW); //ativa o modo de matriz de visualização para utilizar o LookAt
            glLoadIdentity();
            break;
        case 1:
            Mix_PlayChannel(-1, Mix_LoadWAV("sounds/teremim.wav"), 1);
                            //(canal, carrega formatos WAV, loop)
            glEnable(GL_DEPTH_TEST);             //ativa o Z buffer
            glViewport (0, 0, width, height);    //define a proporção da janela de visualização
            glMatrixMode (GL_PROJECTION);        //define o tipo de matriz de transformação que será utilizada
            glLoadIdentity();                    //carrega a matriz identidade do tipo GL_PROJECTION configurado anteriormente
            gluPerspective(90, (float)width/(float)height, 0.2, 400.0);   //funciona como se fosse o glOrtho, mas para o espaço 3D
            glMatrixMode(GL_MODELVIEW);                                   //ativa o modo de matriz de visualização para utilizar o LookAt
            glLoadIdentity(); 
            break;
    }
}

void teclasEspecias(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            modoCamera = 1;
            cameraFixa.x = -37;
            cameraFixa.y = 10;
            cameraFixa.z = -20;
            cameraOlha.x = -37;
            cameraOlha.y = 17;
            cameraOlha.z = -50;
            break;
        case GLUT_KEY_RIGHT:
            modoCamera = 1;
            cameraFixa.x = 0;
            cameraFixa.y = 50;
            cameraFixa.z = 75;
            cameraOlha.x = cameraOlha.y = cameraOlha.z = 0;
            break;
        default:
            break;
    }
}

void teclado(unsigned char key, int x, int y) {
    switch (key){
        case 27:    //esc
            exit(0);
            //Mix_HaltChannel(-1);    //pausa música
            //glutReshapeWindow(mundoW, mundoH);  //chama a função que eu coloquei por padrão pra redimensionar
            break;
        //câmera que tem visão de cima/diagonal
        case '1':     
            modoCamera = 1;
            cameraFixa.x = 0;
            cameraFixa.y = 50;
            cameraFixa.z = 75;
            cameraOlha.x = cameraOlha.y = cameraOlha.z = 0;
            break;
        //camêra em primeira pessoa que utiliza as teclas A D W S Q E para se mover
        case '2':   
            modoCamera = 2;
            break;
        //alguns sinais estão ao contrário do costume justamente pra ter o efeito desejado
        case 'W':
        case 'w':
            if(modoCamera == 2)
                cameraFixa.z -= 0.5;
            break;
        case 'S':
        case 's':
            if(modoCamera == 2)
                cameraFixa.z += 0.5;
            break;
        case 'A':
        case 'a':
            if(modoCamera == 2)
                cameraFixa.x -= 0.5;
            break;
        case 'D':
        case 'd':
            if(modoCamera == 2)
                cameraFixa.x += 0.5;
            break;
        case 'Q':
        case 'q':   //deu ruim aqui
            if(modoCamera == 2)
                cameraFixa.y += 0.5;
            break;
        case 'E':
        case 'e':
            if(modoCamera == 2)
                cameraFixa.y -= 0.5;
            break;
        //camêra em terceira pessoa que utiliza o mouse pra mover
        case '3':  
            modoCamera = 3;
            break;
        //câmera que tem visão de cada brinquedo
        case 'T':
        case 't':   //tower (torre de queda)
            modoCamera = 1;
            cameraFixa.x = -37;
            cameraFixa.y = 10;
            cameraFixa.z = -20;
            cameraOlha.x = -37;
            cameraOlha.y = 17;
            cameraOlha.z = -50;
            break;
        //pausar ou retomar música
        case 'M':    //space     --> não acredito que foi o melhor jeito de fazer
        case 'm':
            if(!som){
                Mix_PlayChannel(-1, Mix_LoadWAV("sounds/teremim.wav"), 1);     //toca a música
                som = true;
            }
            else {
                Mix_HaltChannel(-1);    //pausa música
                som = false;
            }
            break;
        //habilita ou desabilita a iluminação
        case 'L':
        case 'l':
            if(luz)
                luz = false;
            else
                luz = true;
            break;
        //habilita ou desabilita a névoa
        case 'N':
        case 'n':
            if(nevoa) 
                nevoa = false;
            else
                nevoa = true;
            break;
        default:
            break;
    }
}

void atualizaCena(int periodo) {

    //pede ao GLUT para redesenhar a tela assim que possível
    glutPostRedisplay();
    acrescentarAngulos();
    acrescentarAltura();
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

    //configurações para colocar música
    Mix_OpenAudio(35000, MIX_DEFAULT_FORMAT, 2, 2000);
                //(frequencia, formato, canal, tamanho)
    //Mix_PlayChannel(-1, Mix_LoadWAV("sounds/teremim.wav"), 1); 
    Mix_Volume(-1, MIX_MAX_VOLUME);
            //(canal, volume) - se eu dividir o MIX_MAX_VOLUME eu vou diminuindo o som

    glutDisplayFunc(desenhaCena);    
    glutReshapeFunc(redimensiona);  //guarda qual é a função que redimensiona "callback"

    glutKeyboardFunc(teclado);
  //glutKeyboardUpFunc(teclaLiberada);      //caso eu queira mudar tal estado assim que a pessoa soltar a tecla (keyboard[key] = false;)

    glutTimerFunc(0, atualizaCena, 10);
    glutPassiveMotionFunc(detectaMouse);
//    glutMouseFunc(detectaClique);

    inicializa();

    glutMainLoop();

    return 0;
}
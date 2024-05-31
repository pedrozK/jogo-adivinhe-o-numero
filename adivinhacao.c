/*recriando um jogo de adivinhacao de numero que foi
criado em java script, html e css.Porem agora sera utilizado
C e a biblioteca de desenvolvimento visual para jogos RAYLIB*/
#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// variaveis globais
const int screenWidth = 1200;
const int screenHeight = 600;
int new_width=screenWidth - 250;
int new_height=screenHeight - 125;
int num_secret;
int tentativa = 0;
int acertou = 0;
int eh_maior = 0;
int par_impar = 0;

void titulo() {
    Font customFont = LoadFont("C:\\raylib\\projeto_inicial\\fonts\\ChakraPetch.OTF");
    Color text_color = WHITE;
    const char *title = "Jogo do numero \n\n\n\nsecreto";
    Vector2 text_position = { new_width / 2 - 80 / 2 - 260, new_height / 2 - 80 / 2 -90};
    DrawTextEx(customFont, title, text_position, 60, 2, text_color);
    UnloadFont(customFont);
}
void message_um() {
    Color message_color = WHITE;
    const char *message = "Escolha um numero entre 1 e 100";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_dois_um() {
    Color message_color = WHITE;
    const char *message = "Numero secreto eh menor";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_dois_dois() {
    Color message_color = WHITE;
    const char *message = "Numero secreto eh maior";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_tres_um() {
    Color message_color = WHITE;
    const char *message = "Numero secreto eh menor e par";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_tres_dois() {
    Color message_color = WHITE;
    const char *message = "Numero secreto eh menor e impar";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_tres_tres() {
    Color message_color = WHITE;
    const char *message = "Numero secreto eh maior e par";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_tres_quatro() {
    Color message_color = WHITE;
    const char *message = "Numero secreto eh maior e impar";
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
void message_win(int tentativa) {
    Color message_color = WHITE;
    char message[100];
    sprintf(message, "Voce acertou com %d tentativas", tentativa);
    Vector2 message_position = { new_width / 2 - 30 / 2 - 284, new_height / 2 - 30 / 2 +90};
    DrawTextEx(GetFontDefault(), message, message_position, 30, 2, message_color);
}
int espace_type(bool *isInputActive, bool *buttonClicked) {
    // Buffer para armazenar o texto digitado
    static char inputText[4] = "\0";
    static int letterCount = 0;
    static int userNumber = 0;

    // Definindo retângulo e botăo de chutar
    int space_width = 480;
    int space_height = 60;
    Rectangle ret_space = {(new_width - space_width)/2 - 60, (new_height - space_height)/2 + 150, space_width, space_height};
    Color ret_space_color = WHITE;
    float roundness = 0.2;
    float lineThick = 3.0;

    int botton_width = space_width/2 - 20;
    int botton_height = space_height - 10;
    Rectangle botton_guess = {(new_width - space_width)/2 - 60, (new_height - botton_height)/2 + 227, botton_width, botton_height};
    const char *message = "Chutar";
    int fontSize = 25;
    Vector2 message_size = MeasureTextEx(GetFontDefault(), message, fontSize, 5);
    Vector2 message_position = {
        botton_guess.x + (botton_guess.width - message_size.x) / 2,
        botton_guess.y + (botton_guess.height - message_size.y) / 2
    };
    // Desenhando retângulo branco e botăo de chutar e novo jogo
    DrawRectangleRounded(ret_space, roundness, 0, ret_space_color);
    DrawRectangleRounded(botton_guess, roundness, 0, BLUE);
    DrawTextEx(GetFontDefault(), message, message_position, fontSize, 5, WHITE);

    // Verifica se o mouse foi clicado dentro do retângulo
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mousePoint = GetMousePosition();
        if(CheckCollisionPointRec(mousePoint, ret_space)){
            *isInputActive = true;
        }
        else if(CheckCollisionPointRec(mousePoint, botton_guess)){
            *buttonClicked = true;
        }
        else{
            *isInputActive = false;
        }
    }
    if(*isInputActive == true){
        DrawRectangleRoundedLines(ret_space, roundness, 0, lineThick, BLUE);
        int key = GetCharPressed();// Verifica se uma tecla foi pressionada

        // Adiciona o caractere ao buffer se for um número
        while(key > 0){
            if((key >= '0' && key <= '9') && (letterCount < 3)){
                inputText[letterCount] = (char)key;
                letterCount++;
                inputText[letterCount] = '\0'; // Adiciona o caractere nulo ao final da string
                userNumber = atoi(inputText);// Atualiza o número do usuário
            }
            key = GetCharPressed(); // Captura a próxima tecla pressionada
        }

        // Remove o último caractere com o Backspace
        if(IsKeyPressed(KEY_BACKSPACE)){
            if(letterCount > 0){
                letterCount--;
                inputText[letterCount] = '\0';
            }
            // Atualiza o número do usuário
            if(letterCount == 0){
                userNumber = 0;
            }
            else{
                userNumber = atoi(inputText);
            }
        }
    }

    // Desenha o texto digitado
    DrawText(inputText, ret_space.x + 10, ret_space.y + 20, 20, BLUE);

    // Retorna o número do usuário se o botăo for clicado
    if(*buttonClicked){
        *buttonClicked = false; // Reseta o clique do botăo
        letterCount = 0; // Reseta o contador de letras para nova entrada
        inputText[0] = '\0'; // Limpa o texto digitado
        return userNumber;
    }

    return -1; // Retorna -1 se o botăo năo foi clicado
}

//botao de reset game separado da função space_type
void reset_button_off(){
    int buttonWidth = 220;
    int buttonHeight = 50;
    Rectangle resetButton = {(new_width - buttonWidth) / 2 + 71, (new_height - buttonHeight) / 2 + 227, buttonWidth, buttonHeight};

    const char *message = "Reiniciar";
    int fontSize = 25;
    Vector2 messageSize = MeasureTextEx(GetFontDefault(), message, fontSize, 5);
    Vector2 messagePosition = {
        resetButton.x + (resetButton.width - messageSize.x) / 2,
        resetButton.y + (resetButton.height - messageSize.y) / 2
    };
    DrawRectangleRounded(resetButton, 0.2, 0, GRAY);
    DrawTextEx(GetFontDefault(), message, messagePosition, fontSize, 5, WHITE);
}
void reset_button_on(bool *resetButtonClicked){
    int buttonWidth = 220;
    int buttonHeight = 50;
    Rectangle resetButton = {(new_width - buttonWidth) / 2 + 71, (new_height - buttonHeight) / 2 + 227, buttonWidth, buttonHeight};

    const char *message = "Reiniciar";
    int fontSize = 25;
    Vector2 messageSize = MeasureTextEx(GetFontDefault(), message, fontSize, 5);
    Vector2 messagePosition = {
        resetButton.x + (resetButton.width - messageSize.x) / 2,
        resetButton.y + (resetButton.height - messageSize.y) / 2
    };
    DrawRectangleRounded(resetButton, 0.2, 0, BLUE);
    DrawTextEx(GetFontDefault(), message, messagePosition, fontSize, 5, WHITE);

    //verificando se botao foi clicado
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mousePoint = GetMousePosition();
        if(CheckCollisionPointRec(mousePoint, resetButton)){
            *resetButtonClicked = true;
        }
    }
}
void game(bool *isInputActive, bool *buttonClicked){
    int user_number;
    titulo();

    if(tentativa == 0 && acertou==0){
        message_um();
    }
    else if(tentativa > 0 && tentativa <= 10 && acertou==0){
        if(eh_maior == 0){
            message_dois_um();
        }
        else{
            message_dois_dois();
        }
    }
    else if(tentativa>10 && acertou==0){
        if(eh_maior == 0 && par_impar == 0){
            message_tres_um();
        }
        else if(eh_maior == 0 && par_impar != 0){
            message_tres_dois();
        }
        else if(eh_maior == 1 && par_impar == 0){
            message_tres_tres();
        }
        else if (eh_maior == 1 && par_impar != 1){
            message_tres_quatro();
        }
    }
    else if(acertou==1){
        message_win(tentativa);
    }

    user_number = espace_type(isInputActive, buttonClicked);

    if(user_number != -1){
        tentativa++;
        // Verifica se o número é maior, menor ou se acertou
        if(user_number > num_secret){
            eh_maior = 0;
        }
        else if(user_number < num_secret){
            eh_maior = 1;
        }
        else{
            acertou = 1;
        }
    }
}
void reset_game() {
    num_secret = (1 + rand() % 100);
    tentativa = 0;
    acertou = 0;
    eh_maior = 0;
    par_impar = 0;
}

int main() {
    // Inicializa a janela
    int new_width=screenWidth - 250;
    int new_height=screenHeight - 125;
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "ADIVINHE O NUMERO");

    // Define uma nova cor
    Color novaCor = (Color){ 4, 47, 98, 255 }; // Cor personalizada (Medium Slate Blue)

    // Desenhando um container
    Rectangle container_Rect = {(screenWidth - new_width)/2, (screenHeight - new_height)/2, new_width, new_height};
    Color container_color = WHITE;
    Color border_color = BLUE;
    float roundness = 0.1;
    int borderWidth = 2;

    // Carrega a imagem e converte para textura
    Image ruido = LoadImage("C:\\raylib\\projeto_inicial\\images\\Ruido.png");
    ImageResize(&ruido, new_width, new_height);
    Texture2D texture_ruido = LoadTextureFromImage(ruido);
    Image code = LoadImage("C:\\raylib\\projeto_inicial\\images\\code.png");
    Texture2D texture_code = LoadTextureFromImage(code);
    Image ia = LoadImage("C:\\raylib\\projeto_inicial\\images\\ia.png");
    Image icon = LoadImage("C:\\raylib\\projeto_inicial\\images\\icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    int new_width_ia = new_width / 2;
    int new_height_ia = new_height + 50;
    ImageResize(&ia, new_width_ia, new_height_ia);
    Texture2D texture_ia = LoadTextureFromImage(ia);

    // Descarrega a imagem da memória, pois já temos a textura
    UnloadImage(ruido);
    UnloadImage(code);
    UnloadImage(ia);

    bool isInputActive = false;
    bool buttonClicked = false;
    bool resetButtonClicked = false;
    // Gera o número secreto
    num_secret = (1 + rand() % 100);

    // Configura a taxa de quadros por segundo
    SetTargetFPS(60);

    // Loop principal do jogo
    while(!WindowShouldClose()){// Detecta se a janela deve fechar
        // Início do desenho
        BeginDrawing();

        // Limpa a tela com a cor de fundo
        ClearBackground(novaCor);

        // Desenha a textura (imagem) e o bottao de reiniciar
        DrawTexture(texture_code, screenWidth/2 - texture_code.width/2 + 350, screenHeight/2 - texture_code.height/2, WHITE);
        DrawRectangleRoundedLines(container_Rect, roundness, 0, borderWidth, border_color);
        DrawTexture(texture_ruido, screenWidth/2 - texture_ruido.width/2, screenHeight/2 - texture_ruido.height/2, WHITE);
        DrawTexture(texture_ia, new_width/2 - texture_ia.width/2 + 356, new_height/2 - texture_ia.height/2 + 37, WHITE);

        // Jogo com textos e botőes
        if(acertou == 0){
            game(&isInputActive, &buttonClicked);
            reset_button_off();
        }
        else{
            game(&isInputActive, &buttonClicked);
            reset_button_on(&resetButtonClicked);
            if(resetButtonClicked){
                reset_game();
                resetButtonClicked=false;
            }
        }
        // Fim do desenho
        EndDrawing();
    }
    // Fecha a janela e limpa os recursos
    CloseWindow();
    return 0;
}

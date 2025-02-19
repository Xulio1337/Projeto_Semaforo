//Don't Fear The Reaper

/*Usei a Struct para facilitar o uso dos semaforos,
ao invés de criar uma enorme quantidade de "INT", criei uma
Struct, assim mantenho meu codigo mais estruturado, além de que
com ela consigo englobalizar minhas voids"*/

  struct Semaforo {
  int verde; //Aberto
  int amarelo; //Atenção
  int vermelho; // Fechado
};

Semaforo semaforoCarro1 = {11, 12, 13}; 
Semaforo semaforoCarro2 = {8, 9, 10};   
Semaforo semaforoPedestre1 = {6, NULL, 7}; 
Semaforo semaforoPedestre2 = {4, NULL, 5}; 

/////////////////////////////////////////////////////
/* No começo eu não queria usar tantas vois, mas após muito
suor e complexidade eu desisti e crei essas*/

// Void's Principais
void SC_1(Semaforo &semaforo);
void SC_2(Semaforo &semaforo);
void fecharSemaforos() ;

// Void's de apoio
void detectarBotao();
void identificarBotao(); 
void SP_Pisca(Semaforo &semaforo); 
  
/////////////////////////////////////////////////////
/*O sistema que usei para criar meu botão, armazenando 
uma flag é simples e não necessita de uma explicação gritante*/

int botao = 2;
bool botaoPressionado = false;
volatile byte flag = 0;


void setup() {
  
  pinMode(botao, INPUT_PULLUP);
  
  pinMode(semaforoCarro1.verde, OUTPUT);
  pinMode(semaforoCarro1.amarelo, OUTPUT);
  pinMode(semaforoCarro1.vermelho, OUTPUT);

  pinMode(semaforoCarro2.verde, OUTPUT);
  pinMode(semaforoCarro2.amarelo, OUTPUT);
  pinMode(semaforoCarro2.vermelho, OUTPUT);

  pinMode(semaforoPedestre1.verde, OUTPUT);
  pinMode(semaforoPedestre1.vermelho, OUTPUT);

  pinMode(semaforoPedestre2.verde, OUTPUT);
  pinMode(semaforoPedestre2.vermelho, OUTPUT);

attachInterrupt(digitalPinToInterrupt(botao), detectarBotao, FALLING);
//Interrompe os semaforos e executa detectarBotao
}

void detectarBotao() {
  // Quando o botão for pressionado, a flag é ativada
  flag = 1;
}

void identificarBotao() {
  
  if (flag == 1) {
    // Chama a função para fechar os semáforos e abrir os de pedestre
    fecharSemaforos();
    flag = 0;  // Reseta a flag após a execução
    
  }
}
void fecharSemaforos(){
//Estado base dos Semaforos dentro dessa função (Fecha SC_1 e 2)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
  digitalWrite(semaforoCarro1.verde, LOW);
  digitalWrite(semaforoCarro1.amarelo, LOW);
  digitalWrite(semaforoCarro1.vermelho, HIGH);
  digitalWrite(semaforoCarro2.verde, LOW);
  digitalWrite(semaforoCarro2.amarelo, LOW);
  digitalWrite(semaforoCarro2.vermelho, HIGH);
  digitalWrite(semaforoPedestre1.verde, HIGH);
  digitalWrite(semaforoPedestre1.vermelho, LOW);
  digitalWrite(semaforoPedestre2.verde, HIGH);
  digitalWrite(semaforoPedestre2.vermelho, LOW);
  delay(3000);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   for (int i = 0; i < 3; i++) {    
  digitalWrite(semaforoPedestre1.verde, LOW);
  digitalWrite(semaforoPedestre1.vermelho, LOW);
  digitalWrite(semaforoPedestre2.verde, LOW);
  digitalWrite(semaforoPedestre2.vermelho, LOW);
  delay(500);
  digitalWrite(semaforoPedestre1.verde, LOW);
  digitalWrite(semaforoPedestre1.vermelho, HIGH);
  digitalWrite(semaforoPedestre2.verde, LOW);
  digitalWrite(semaforoPedestre2.vermelho, HIGH);
  delay(500);
   }
  }
/*Acima, pisca os semaforos de pedestres sincronizadamente.
Por quê usei ela e não a void Pisca? Isso se deve ao fato de
que o arduino executa um proceso por vez, fazendo executar uma
"void pisca" por vez.*/
  

void SC_1(Semaforo &semaforo) {  
 // No final do codigo coloquei uma explicação dessa void
  
  digitalWrite(semaforoPedestre1.verde, HIGH);
  digitalWrite(semaforoPedestre1.vermelho, LOW);
  
  //Aberto
  digitalWrite(semaforo.vermelho, LOW);
  digitalWrite(semaforo.verde, HIGH);    
  delay(3000);                         
  
  // Atenção
  digitalWrite(semaforo.verde, LOW);    
  digitalWrite(semaforo.amarelo, HIGH);
  SP_Pisca(semaforoPedestre1);
  delay(500);                          
  
  // Fechado
  digitalWrite(semaforoPedestre1.verde, LOW);
  digitalWrite(semaforoPedestre1.vermelho, HIGH);
  digitalWrite(semaforo.amarelo, LOW);  
  digitalWrite(semaforo.vermelho, HIGH);
  delay(500);
}


void SC_2(Semaforo &semaforo) {
  
  digitalWrite(semaforoPedestre2.verde, HIGH);
  digitalWrite(semaforoPedestre2.vermelho, LOW);
  digitalWrite(semaforo.vermelho, LOW);
  digitalWrite(semaforo.verde, HIGH);    
  delay(2500);                 
  
  digitalWrite(semaforo.verde, LOW);    
  digitalWrite(semaforo.amarelo, HIGH); 
  SP_Pisca(semaforoPedestre2);
  delay(1000);                          
  
  digitalWrite(semaforoPedestre2.verde, LOW);
  digitalWrite(semaforoPedestre2.vermelho, HIGH);
  digitalWrite(semaforo.amarelo, LOW);  
  digitalWrite(semaforo.vermelho, HIGH);
}


void SP_Pisca(Semaforo &semaforo) {

  //Sistema para piscar o led do semaforo de pedestre
  digitalWrite(semaforo.verde, LOW);    
  for (int i = 0; i < 3; i++) {         
    digitalWrite(semaforo.vermelho, LOW); 
    delay(250);
    digitalWrite(semaforo.vermelho, HIGH); 
    delay(250);
  }
  digitalWrite(semaforo.vermelho, HIGH); 
}




void loop() {
//Estado base dos Semaforos (para ambos não iniciarem desligados)
 /////////////////////////////////////////////////     
  digitalWrite(semaforoCarro1.verde, LOW);
  digitalWrite(semaforoCarro1.amarelo, LOW);
  digitalWrite(semaforoCarro1.vermelho, HIGH);

  digitalWrite(semaforoCarro2.verde, LOW);
  digitalWrite(semaforoCarro2.amarelo, LOW);
  digitalWrite(semaforoCarro2.vermelho, HIGH);

  digitalWrite(semaforoPedestre1.verde, LOW);
  digitalWrite(semaforoPedestre1.vermelho, HIGH);

  digitalWrite(semaforoPedestre2.verde, LOW);
  digitalWrite(semaforoPedestre2.vermelho, HIGH);
 //////////////////////////////////////////////////
  delay(500);
  SC_1(semaforoCarro1);
  identificarBotao();
  delay(500);
  SC_2(semaforoCarro2);
  identificarBotao();
  delay(500);
 //////////////////////////////////////////////////
}

/* Exemplo Void que eu estava usando com a Struct
para faclitar as funções.

  void Semaforo_abre(Semaforo &semaforo) {  
 
  digitalWrite(semaforo.vermelho, LOW);
  digitalWrite(semaforo.verde, HIGH);    
  delay(2500);                         
  
  digitalWrite(semaforo.verde, LOW);    
  digitalWrite(semaforo.amarelo, HIGH); 
  delay(1000);                          
  
  digitalWrite(semaforo.amarelo, LOW);  
  digitalWrite(semaforo.vermelho, HIGH);
} 

 Eu troquei por aquela feiura pelo fato de que o arduino
 possui apenas um unico nucleo de processamento, entao cada void
 iria executar em uma ordem somando assim o delay ou millis.
 Então para que eu pudesse fazer os semaforos tanto de
 pedestres como de carro de uma maneira "sincronizada" uni
 todas em apenas uma void
 
 Também criei duas void "SC_1 e SC_2" para que pudesse sincronizar
 com os semaforos. Não usei uma void só para semaforo pois
 ocorreria o erro do semaforo não sincronizar, além que eu teria
 que criar uma segunda struct somente para aplicar e diferenciar
 dentro da void os semaforos de carro e de pedestres.
*/
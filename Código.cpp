//------------------------------------------//
//       CÓDIGO TRANCA NERO 13/11/2020      //
//   MÓDULO RC 522 / CARTAO RFID 13,5 KHz   //
//                                          //
//          By Celso Barcelos               //
//------------------------------------------//

//  CARTAOES QUE EU TENHO NO CADASTRO:
// "CB CE 31 01" => Celso antigo
// "79 30 58 8D" => Celso novo
// "06 72 BA 1B" => Brandão
// "C6 BA 3C 1A" => Hiago
// "D6 57 29 1A" => Werikson
// "51 BC EB 20" => Guilherme
// "2B 2F 33 0D" => Kevin
// "06 AB E3 1B" => Gladson
// "CB 94 45 0D" => Caldeira
// "1B DA 44 0D" => Daniel
// "6B 79 15 0F" => Iure
// "D6 44 36 1A" => Ridogério
// "F6 FB 4D 1A" => Mateus
// "D6 0E 7C 1A" => Sacola
// "C6 FF 2D 1A" => Paulo ?
// "7B 3C 3A 0D" => Ritti
// "69 3E 4F 8C" => Jhenifer
// "06 5F 7B 1B" => Leo
// "D1 A5 8F C9" => Heitor
// "1B 83 45 0D" => Heitor
// "41 33 3D 20" => Kevin
// "E9 AF 28 8C" => João Vitor
// "D6 31 1C 1A" => Paula Gibrim
// "C6 EE 1F 1A" => Valentim
// "8B D2 46 0D" => Luiza
// "06 3C FC 1B" => Jéssica
// "42 16 9B 1E" => Francisco
// "31 1C 16 20" => Pablo
// "41 97 72 20" => Rafael

/*
  /* Definição das portas utilizadas
   Sensor RFID
     RST => D9
     SDA => D10
     MOSI => D11
     MISO => D12
     SCK => D13
*/

#include <SPI.h>

//RFID:
//VERIFICAR SAIDAS ICSP (11 12 13)
#include <MFRC522.h> //LEetor RFID
#include <avr/wdt.h>  // chama a biblioteca Watchdog

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Definição das variaveis
int rele = 2;// PINO QUE CONTROLA O RELÉ
int ledverde = 3; //  PINO QUE CONTROLA O LED
int ledvermelho = 4; //  PINO QUE CONTROLA O LED
int sist_ligado = 5; //  sinaliza que o sistema está ligado (stand by)
int tempoled = 1000; // TEMPO DE CONTROLE DO LED
int pulso = 250; // TEMPO DE PULSO
int pwm_led = 5; // Controla intensidade do brilho do led que indica que o sistema está operante

void setup() {
  wdt_enable(WDTO_2S); // habilita o watchdog para acionar após 2 seg
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();    // Init MFRC522 card
  Serial.println("iniciou o teste");

  // Definiçao do Estado das portas
  pinMode(rele, OUTPUT);
  pinMode(ledverde, OUTPUT);
  pinMode(ledvermelho, OUTPUT);
  pinMode(sist_ligado, OUTPUT);

  analogWrite(sist_ligado, pwm_led); // Indicar que o sistema está ligado
}

void loop() {
  wdt_reset(); // reseta arduino
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Identificação do cartao:");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  //Serial.println(conteudo.substring(1));

  //Executa as ações a partir deste ponto
  if (   (conteudo.substring(1) == "CB CE 31 01") || (conteudo.substring(1) == "06 72 BA 1B")
      || (conteudo.substring(1) == "C6 BA 3C 1A") || (conteudo.substring(1) == "D6 57 29 1A")
      || (conteudo.substring(1) == "51 BC EB 20") || (conteudo.substring(1) == "2B 2F 33 0D")
      || (conteudo.substring(1) == "06 AB E3 1B") || (conteudo.substring(1) == "CB 94 45 0D")
      || (conteudo.substring(1) == "31 1C 16 20") || (conteudo.substring(1) == "1B DA 44 0D")
      || (conteudo.substring(1) == "6B 79 15 0F") || (conteudo.substring(1) == "D6 44 36 1A")
      || (conteudo.substring(1) == "F6 FB 4D 1A") || (conteudo.substring(1) == "D6 0E 7C 1A")
      || (conteudo.substring(1) == "C6 EB 53 1A") || (conteudo.substring(1) == "C6 FF 2D 1A")
      || (conteudo.substring(1) == "D1 A5 8F C9") || (conteudo.substring(1) == "1B 83 45 0D")
      || (conteudo.substring(1) == "06 5F 7B 1B") || (conteudo.substring(1) == "7B 3C 3A 0D") 
      || (conteudo.substring(1) == "69 3E 4F 8C") || (conteudo.substring(1) == "41 33 3D 20")
      || (conteudo.substring(1) == "E9 AF 28 8C") || (conteudo.substring(1) == "D6 31 1C 1A")
      || (conteudo.substring(1) == "C6 EE 1F 1A") || (conteudo.substring(1) == "8B D2 46 0D")
      || (conteudo.substring(1) == "06 3C FC 1B") || (conteudo.substring(1) == "42 16 9B 1E")
      || (conteudo.substring(1) == "31 1C 16 20") || (conteudo.substring(1) == "41 97 72 20")
      || (conteudo.substring(1) == "79 30 58 8D")){

    //Serial.print("LIBERADO !!! PODE PASSAR !!!");
    //Serial.println();

    Serial.println("Cartão Aceito");
    Serial.println(" ");
    digitalWrite(ledverde, HIGH);
    digitalWrite(rele, HIGH);
    delay(pulso);
    digitalWrite(rele, LOW);
    delay(tempoled);
    digitalWrite(ledverde, LOW);

    delay(pulso);
  }

  else {
    Serial.println("Cartão Recusado");
    Serial.println(" ");
    digitalWrite(rele, LOW);
    digitalWrite(ledvermelho, HIGH);
    delay(tempoled);
    digitalWrite(ledvermelho, LOW);
  }
}

/*
 * Robô Bluetooth Arduino para Disciplina de Experimentação Orientada
 * Daniel Almeida Chagas - daniel.chagas@unifor.br
 *
 * Este robô tem como objetivo demonstrar um protocolo de comunicação
 * entre um dispositivo bluetooth e um Arduino UNO com módulo bluetooth. 
 * 
 * Os motores estão conectados ao Arduino por um módulo Driver Ponte H
 * Duplo HG7881, com os pinos definidos pelas variáveis motor1 e motor2,
 * (são dois pinos por motor, para sentido horário e anti-horário).
 *
 * O protocolo de comunicação inventado é feito de um padrão de letras
 * e números, no formato LNNN, para formar comandos como f100 (ir para
 * frente a 100% da potência). A exceção são os comandos 'oi' (que 
 * retorna 'ola' do robô, para testes de comunicação) e o comando 'help'
 * (que retorna uma lista de comandos e variáveis do robô).
 */

//pinos que ligam os motores
int motor1_hora = 6;
int motor1_anti = 5;
int motor2_hora = 10;
int motor2_anti = 9;

//variáveis de calibração dos motores
int potMinEsq = 80;
int potMaxEsq = 180;
int potMinDir = 80;
int potMaxDir = 180;

String textoRecebido = "";
char byteRecebido;

void setup() {
  pinMode(motor1_hora, OUTPUT);
  pinMode(motor1_anti, OUTPUT);
  pinMode(motor2_hora, OUTPUT);
  pinMode(motor2_anti, OUTPUT);
  Serial.begin(9600);  
  Serial.println(F(""));
  Serial.println(F("Robô ligado!"));
}

void loop() {
  if(Serial.available()){
    byteRecebido = Serial.read(); //lê o valor do caractere que chegou via serial
    if(byteRecebido=='\n'){
      //manda o comando para os motores
      Serial.print(F("Você mandou o comando "));
      Serial.print(textoRecebido);
      Serial.print(F(" (tamanho "));
      Serial.print(textoRecebido.length());
      Serial.println(F(")"));
      maquinaDeEstado(textoRecebido);
      textoRecebido = "";
    } else {
      textoRecebido = textoRecebido + byteRecebido;
    }
  }
}

void maquinaDeEstado(String comando){
  //recebe e processa comandos!

  if(comando == "oi"){
    Serial.println(F("Ola!"));
  } else if(comando == "help"){
    Serial.println(F("Comandos:"));
    Serial.println(F("e100 - Gira pra esquerda"));
    Serial.println(F("d100 - Gira pra direita"));
    Serial.println(F("f100 - Anda para frente"));
    Serial.println(F("t100 - Anda para tras"));
    Serial.println(F("p    - Para motores"));
    Serial.println(F("DD100 - Liga motor direito horario a 100 (valor entre 0 e 100)"));
    Serial.println(F("DE100 - Liga motor direito antihorario a 100 (valor entre 0 e 100)"));
    Serial.println(F("ED100 - Liga motor esquerdo horario a 100 (valor entre 0 e 100)"));
    Serial.println(F("EE100 - Liga motor esquerdo antihorario a 100 (valor entre 0 e 100)"));
    Serial.print(F("me100 - Torque minimo do motor esquerdo (valor entre 0 e 255). Atual "));
    Serial.println(potMinEsq);
    Serial.print(F("md100 - Torque minimo do motor direito (valor entre 0 e 255). Atual "));
    Serial.println(potMinDir);
    Serial.print(F("xe100 - Torque maximo do motor esquerdo (valor entre 0 e 255). Atual "));
    Serial.println(potMaxEsq);
    Serial.print(F("xd100 - Torque maximo do motor direito (valor entre 0 e 255). Atual "));
    Serial.println(potMaxDir);
    Serial.print(F("id - Inverte rotação motor direito. Pinos atuais "));
    Serial.print(motor2_hora);
    Serial.print(F(" "));
    Serial.println(motor2_anti);
    Serial.print(F("ie - Inverte rotação motor esquerdo. Pinos atuais "));
    Serial.print(motor1_hora);
    Serial.print(F(" "));
    Serial.println(motor1_anti);
    Serial.println(F("im - Inverte motor esquerdo e direito"));
    
  } else if(comando.substring(0,1)=="e"){
    String vel = comando.substring(1,comando.length());
    Serial.println("mandando comando " + vel + " para o motor esquerdo");
    motorEsq(vel.toInt(), true);
    motorDir(vel.toInt(), false);
  } else if(comando.substring(0,2)=="ED"){
    String vel = comando.substring(2,comando.length());
    Serial.println("Liga motor esquerdo rotacao horaria a " + vel);
    analogWrite(motor1_hora,map(vel.toInt(),0,100,potMinEsq,potMaxEsq));
  } else if(comando == "dir"){
    Serial.println(F("Prime Directives:"));
    Serial.println(F("1. Serve the public trust"));
    Serial.println(F("2. Protect the innocent"));
    Serial.println(F("3. Uphold the law"));
    Serial.println(F("4. [CLASSIFIED]"));
  } else if(comando == "laws"){
    Serial.println(F("A robot may not injure a human being or, through inaction, allow a human being to come to harm."));
    Serial.println(F("A robot must obey the orders given it by human beings except where such orders would conflict with the First Law."));
    Serial.println(F("A robot must protect its own existence as long as such protection does not conflict with the First or Second Law."));
  } else if(comando.substring(0,2)=="EE"){
    String vel = comando.substring(2,comando.length());
    Serial.println("Liga motor esquerdo rotacao antihoraria a " + vel);
    analogWrite(motor1_anti,map(vel.toInt(),0,100,potMinEsq,potMaxEsq));
  } else if(comando.substring(0,1)=="d"){
    String vel = comando.substring(1,comando.length());
    Serial.println("mandando comando " + vel + " para o motor esquerdo");
    motorEsq(vel.toInt(), false);
    motorDir(vel.toInt(), true);
  } else if(comando.substring(0,2)=="DD"){
    String vel = comando.substring(2,comando.length());
    Serial.println("Liga motor direito rotacao horaria a " + vel);
    analogWrite(motor2_hora,map(vel.toInt(),0,100,potMinDir,potMaxDir));
  } else if(comando.substring(0,2)=="DE"){
    String vel = comando.substring(2,comando.length());
    Serial.println("Liga motor direito rotacao antihoraria a " + vel);
    analogWrite(motor2_anti,map(vel.toInt(),0,100,potMinDir,potMaxDir));
  } else if(comando.substring(0,1)=="f"){
    String vel = comando.substring(1,comando.length());
    Serial.println("mandando comando Pra Frente na potencia " + vel);
    praFrente(vel.toInt());
  } else if(comando.substring(0,1)=="t"){
    String vel = comando.substring(1,comando.length());
    Serial.println("mandando comando Pra Frente na potencia " + vel);
    praTras(vel.toInt());
  } else if(comando.substring(0,1)=="p"){
    Serial.println(F("mandando comando parar"));
    parar();
  } else if(comando.substring(0,2)=="me"){
    String param = comando.substring(2,comando.length());
    int paramNum = param.toInt();
    if(paramNum>0&&paramNum<=255){
      Serial.println("Mudando potencia minima esquerda para " + param);
      potMinEsq = paramNum;
    } else {
      Serial.println("Valor de potencia minimo invalido: " + param);
    }
  } else if(comando.substring(0,2)=="md"){
    String param = comando.substring(2,comando.length());
    int paramNum = param.toInt();
    if(paramNum>0&&paramNum<=255){
      Serial.println("Mudando potencia minima direita para " + param);
      potMinDir = paramNum;
    } else {
      Serial.println("Valor de potencia minimo invalido: " + param);
    }
  } else if(comando.substring(0,2)=="xe"){
    String param = comando.substring(2,comando.length());
    int paramNum = param.toInt();
    if(paramNum>0&&paramNum<=255){
      Serial.println("Mudando potencia maxima esquerda para " + param);
      potMaxEsq = paramNum;
    } else {
      Serial.println("Valor de potencia maximo invalido: " + param);
    }
  } else if(comando.substring(0,2)=="xd"){
    String param = comando.substring(2,comando.length());
    int paramNum = param.toInt();
    if(paramNum>0&&paramNum<=255){
      Serial.println("Mudando potencia maxima direita para " + param);
      potMaxDir = paramNum;
    } else {
      Serial.println("Valor de potencia maximo invalido: " + param);
    }
  } else if(comando.substring(0,2)=="im"){
    Serial.println(F("Inverntendo motores direito e esquerdo"));
    int temp = motor1_hora;
    motor1_hora = motor2_hora;
    motor2_hora = temp;
    temp = motor1_anti;
    motor1_anti = motor2_anti;
    motor2_anti = temp;
  } else if(comando.substring(0,2)=="ie"){
    Serial.println(F("Inverntendo rotacao do motor esquerdo"));
    int temp = motor1_hora;
    motor1_hora = motor1_anti;
    motor1_anti = temp;
  } else if(comando.substring(0,2)=="id"){
    Serial.println(F("Inverntendo rotacao do motor direito"));
    int temp = motor2_hora;
    motor2_hora = motor2_anti;
    motor2_anti = temp;
  } else {
    Serial.println(F("Comando invalido!"));
  }
}

void motorEsq(int potencia, bool dir){
  int vel = map(potencia,0,100,potMinEsq,potMaxEsq);
  if(dir){
    analogWrite(motor1_hora,vel);  
  } else {
    analogWrite(motor1_anti,vel);
  }
}

void motorDir(int potencia, bool dir){
  int vel = map(potencia,0,100,potMinDir,potMaxDir);
  if(dir){
    analogWrite(motor2_hora,vel);  
  } else {
    analogWrite(motor2_anti,vel);
  }
}

void praFrente(int potencia){
  motorEsq(potencia,true);
  motorDir(potencia,true);
}

void praTras(int potencia){
  motorEsq(potencia,false);
  motorDir(potencia,false);
}

void parar(){
  analogWrite(motor1_hora,0);
  analogWrite(motor1_anti,0);
  analogWrite(motor2_hora,0);
  analogWrite(motor2_anti,0); 
}


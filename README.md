# roboExperimentacaoOrientada
Robô didático com Arduino e Bluetooth para uso na disciplina de experimentação orientada. Este robô tem como objetivo demonstrar um protocolo de comunicação entre um dispositivo bluetooth e um Arduino UNO com módulo bluetooth. 

# Hardware
O código funciona com qualquer robô que use a plataforma IDE Arduino, e se comunique via serial para receber comandos. No robô de testes um módulo bluetooth HC-05 foi conectado aos pinos RX e TX do Arduino para a comunicação serial. A comunicação serial pode ser simulada via conexão serial da IDE do Arduino. 

Os motores estão conectados ao Arduino por um módulo Driver Ponte H Duplo HG7881, com os pinos definidos pelas variáveis motor1 e motor2, (são dois pinos por motor, para sentido horário e anti-horário).

O protocolo de comunicação inventado é feito de um padrão de letras e números, no formato LNNN, para formar comandos como f100 (ir para frente a 100% da potência). A exceção são os comandos 'oi' (que  retorna 'ola' do robô, para testes de comunicação) e o comando 'help' (que retorna uma lista de comandos e variáveis do robô).

#Exemplo de uso
1. Conecte um Arduino UNO via porta USB e faça a gravação do código .ino desse repositório.
2. Abra a porta serial e digite o comando `oi` e o robô deve responder `ola`.
3. Para ver os possíveis comandos que pode mandar, digite na porta serial `help`
4. Para testar a movimentação, use o comando `f100` que irá fazer o robô ir para frente a 100% de velocidade.

# Calibração dos motores
Os motores DC são bem diferentes entre si, e fazer o robô simplesmente seguir reto necessita calibrar, pois a velocidade máxima de um motor pode não ser a mesma de outro. 

Para calibrar a potência máxima, siga os passos:
1. Com o robô montado e funcionando a baterias, powerbank ou pilhas, digite o comando `f50` para ele ir para frente a 50% de potência. Verifique para que lado ele dobra mais.
2. Caso o robô esteja virando para a esquerda, significa que é necessário diminuir a potência do motor esquerdo. Para isso use o comando `xe` seguido de um valor entre 0 e 255. A configuração padrão está definida para 180. Se precisa que ele vá mais lento, tente um numero menor, como `xe160`.
3. Repita a operação de fazer o robô ir para frente `f50` e veja se ele ainda vira para um dos lados.
4. Siga corrigindo, aumentando e diminuindo as potências máximas dos motores direito e esquerdo, até que ele ande em linha reta quando comandado. 

Os motores podem também ter problemas para se mover com potências muito baixas. Na configuração padrão a potência 1% equivale ao valor 80 no motor. Valores menores podem fazer com que o motor não tenha potência suficiente para andar, então é necessário calibrar a potência mínima para o motor mover-se. Para Calibrar a potência mínima siga os passos:
1. Com o robô montado e funcionando, faça o robô andar pra frente na potência mínima com o comando `f1` (pra frente a 1%);
2. Se alguma roda não rodar, por exemplo o motor esquerdo, aumente a potência mínima através do comando `me90` (aqui nesse caso definindo a potência mínima para o motor esquerdo em 90).
3. Siga ajustando a potência de cada motor para que eles rodem com o comando mínimo. 

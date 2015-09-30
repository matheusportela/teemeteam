# teemeteam
Código desenvolvido durante o hackathon Se Vira II, realizado na Universidade de Brasília.

O código implementa um algoritmo distribuído de cálculo de mínimos e máximos utilizando 3 Intel Galileo, os quais se comunicam pela rede utilizando cabos Ethernet.

Utilizando o script `message.py`, envia-se uma lista de números para qualquer Intel Galileo conectado à rede e identificado pelo seu endereço de IP. O dispositivo então divide a lista em 3 partes, armazena uma para cálculo próprio e envia as restantes para os outros Intel Galileo da rede. Cada hardware calcula o mínimo (ou máximo) da lista recebida e retorna o seu resultado para o dispositivo inicial, o qual reúne os resultados parciais e calcula o resultado final. Por fim, o resultado da computação é retornado para o computador que enviou a mensagem, sendo visualizado ao executar o script `server.py`.

É importante ressaltar que todos os dispositivos possuem o mesmo programa executando, portanto, todos podem receber mensagens e coordenar a computação ou apenas obedecer ordens de um outro dispositivo.

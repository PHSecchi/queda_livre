# Queda Livre

Este projeto de queda livre foi desenvolvido na disciplina de Sistemas Microcontrolados do curso de Tecnologia em Mecatrônica Industrial, do Instituto Federal de São Paulo, campus Catanduva.

O objetivo do projeto foi criar uma experiência prática para ilustrar conceitos de física. Ele consiste em um eletroímã que segura uma esfera metálica. Quando um botão é pressionado, a esfera é liberada e atravessa dois conjuntos de sensores infravermelhos, que formam barreiras. Ao passar pelo primeiro sensor, um cronômetro é ativado, sendo pausado assim que a esfera atravessa o segundo sensor.

O código foi escrito em linguagem C e utiliza o microcontrolador ATmega328P, o mesmo utilizado no Arduino Uno. No entanto, ao contrário do ambiente Arduino IDE, onde a programação é mais simplificada, aqui foi feita diretamente no microcontrolador utilizando registradores para configurar saídas e entradas, temporizadores (timers), prescalers, além de leituras para diagnóstico e aferição de eventuais problemas.

Para mais detalhes e dúvidas, verificar o relatório presente no repositório
# Mouse-de-sopro
VERSÃO do Mouse de Sopro com MAIS de um sensor BMP280. 

LISTA DE MATERIAIS:

Arduino Leonardo
Sensores BMP280
Multiplexer ....
LevelShifter ....
Fonte Externa
Conversor USB-Serial para depuração
Joystick 

Considerações: 

O Sensor BMP280 é sensor de umidade e pressão que trabalha com 3,3 Volts. 
Quando se usa o Arduino 5V: 
Nas versões que experimentamos não tinha level-shift integrado, sendo necessário a utilização de
um módulo à parte.

Para o uso de mais de mais de dois sensores é necessario o uso de um Multiplexer I2C.

Para o uso de todos esses módulos é necessário que o Arduino seja alimentado por uma fonte externa. 

ERROS:
Travamentos de leitura I2C/BMP280: 
Problema nos níveis digitais. Solucionado com o Level-Shift

Leitura errada muito abaixo da média:
Alimentação pela USB não fornece corrente necessária. Solucionado com o uso de uma fonte externa.

TODO:
Na matriz de contatos: Problema  com I2C quanto a aproximação das mãos nos fios, alterando o valor da leitura dos sensores 

Verificar circuitos dos módulos/Datasheets para ver se cabe o uso de resistores de pullups
nas linhas I2C e onde colocálos. 

Quando se usa Mouse.begin() no setup do sketch, a conexão da serial-usb com o windows fica instável. 
Deveríamos saber o porquê. 

Demais formas de interferência elêtricas/magnéticas que ocasionam falha na comunicação i2c. 

DEBUG:
A forma de debug utilizada é pela segunda porta serial com módulo externo.



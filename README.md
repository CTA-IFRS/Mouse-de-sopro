Versão do Mouse de Sopro com MAIS de um sensor BMP280.

LISTA DE MATERIAIS:

Arduino Leonardo, 
Sensores BMP280, 
Multiplexer I2C, 
Level Shifter,
Fonte Externa, 
Conversor USB-Serial para depuração,
Joystick.

Considerações:
Sensor BMP280:
Nas versões que experimentamos não tinha level-shift integrado, sendo necessário a utilização de um módulo à parte.
Para o uso de mais de dois sensores é necessário o uso de um Multiplexer I2C.
Para o funcionamento de todos esses módulos é necessário que o Arduino seja alimentado por uma fonte externa.

ERROS: 
-Travamentos de leitura I2C/BMP280: 
Problema nos níveis digitais. Solucionado com o Level-Shift

-Leitura errada muito abaixo da média: 
Alimentação pela USB não fornece corrente necessária. Solucionado com o uso de uma fonte externa.

TODO:
*Na matriz de contatos: Problema com I2C quanto a aproximação das mãos nos fios, alterando o valor da leitura dos sensores ou travando o sensor

*Verificar circuitos dos módulos/Datasheets para ver se cabe o uso de resistores de pullups nas linhas I2C e onde colocá-los. 

*Quando se usa Mouse.begin() no setup do sketch, a conexão da serial-usb com o windows fica instável. Deveríamos saber o porquê.

*Demais formas de interferência elétricas/magnéticas que ocasionam falha na comunicação i2c.

*Testar uma versão do hardware com todas as ligações soldadas. 

DEBUG:
A forma de debug utilizada é pela segunda porta serial com uso de um módulo USB-Serial externo.

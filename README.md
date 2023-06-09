# Mouse de Sopro com mais de um sensor BMP280.
## 
##

## LISTA DE MATERIAIS:

- 1 - Arduino Leonardo 
- 3 - Sensores BMP280 
- 1 - Multiplexer I2C 
- 1 - Level Shifter
- 1 - Fonte Externa 
- 1 - Conversor USB-Serial para depuração
- 1 - Joystick

## Considerações:
* Level Shifter:
- Os BMP280 nas versões que experimentamos não tinham level shifter  integrado, sendo necessário a utilização de um módulo à parte.  

* Mux I2C:

    - Para o uso de mais de dois sensores é necessário o uso de um Multiplexer I2C.

* Fonte Externa:

    - Para o funcionamento de todos esses módulos é necessário que o Arduino seja alimentado por uma fonte externa.


## Erros corrigidos: 
* Travamentos de leitura I2C/BMP280: 

Problema nos níveis digitais. Solucionado com emprego do level shifter 

* Leitura muito abaixo da média calculada: 

Alimentação pela USB não fornecia corrente necessária. Solucionado com o uso de uma fonte externa.
Usamos a fonte de bancada, será substituido por baterias recarregáveis padrão 16850

## Tarefas:
* Quando os fios da saída do mux são tocados pelas mãos, os valores lidos dos sensores mudam.

* Pesquisar se é necessário o uso de resistores de pullups nas linhas I2C e onde colocá-los. 

* Quando se usa Mouse.begin() no setup, a conexão da serial-usb com o windows fica instável e as vezes não reconhecendo o mouse. Deveríamos saber o porquê.

* Demais formas de interferência elétricas/magnéticas que ocasionam falha na comunicação i2c.

* Testar uma versão do hardware com todas as ligações soldadas, ao invés do uso de cabos jumper. 

* Verificar se a frequência do I2C é compatível com os modulos conectados à ela.

## Debug:
Foi usada a segunda porta serial para fazer a leitura dos dados dos sensores. Usamos um módulo USB-Serial padrão e ligamos aos pinos TX, RX. Desta forma utilizamos algo do tipo:  "Serial1.println". 
#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <linux/ioctl.h>

#define UTS_RELEASE "3.3.0-xxx+"

#define MAJOR_NUM 100

#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
/*
  * _IOR significa que estamos criando um comando ioctl
  * para passar informações de um processo do usuário
  * para o módulo do kernel.
  *
  * O primeirio argumento, MAJOR_NUM, é número do principal 
  * dispositivo que estamos usando.
  *
  * O segundo argumento é o número do comando
  *
  * O terceiro argumento é o tipo que queremos obter do processo para o kernel.
 */

#define IOCTL_GET_MSG _IOW(MAJOR_NUM, 1, char *)
/* 
  * Este IOCTL é usado para saída, para obter a mensagem
  * do driver do dispositivo. No entanto, ainda precisamos do
  * buffer para colocar a mensagem a ser a entrada  é alocado pelo processo.
 */

#endif
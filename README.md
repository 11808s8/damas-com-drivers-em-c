# Aplicação de um Jogo de Damas com a utilização de Drivers no Kernel do Linux

Projeto para disciplina de Fundamentos de Sistemas Operacionais da Universidade de Caxias do Sul (UCS).

### Configuração do ambiente

Primeiramente deve-se abrir o log do sistema para visualização da comunicação com o kernel.
```sh
    $ sudo tail -f /var/log/syslog
```
Deve-se realizar a criação do arquivo (necessita ser feita somente uma vez).
```sh
    $ sudo mknod /dev/so c 60 0
    $ sudo chmod 666 /dev/so
```
Necessita-se compilar e carregar o driver na pasta da aplicação.
```sh
    $ make
    $ sudo insmod driver.ko
```
Caso o driver sofra alteração, deve-se compilar ele novamente, remover o driver e carregar novamente.
```sh
    $ make
    $ sudo rmmod driver.ko
    $ sudo insmod driver.ko
```
##
Desenvolvido por [Adriano Gomes](https://github.com/11808s8) e [Bruno Caregnato](https://github.com/brunocaregnato).

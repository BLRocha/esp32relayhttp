# Servidor para controlar Relay com ESP32.

### Sobre.

Recentemente adquirir alguns Arduinos Nano, UNO e ESP32.
Com intuito de aprender um pouco sobre estas magníficas ferramentas de prototipação,
Criei um pequeno server http com ESP32 Wroom 32.

## Config Default
`Arquivo main.cpp`
```py

int R12 = 12;
int R27 = 27;

int r12s = 0;
int r27s = 0;

IPAddress ip(192,168,2,15);
IPAddress sub(255,255,255,0);
IPAddress gat(192,168,2,1);
IPAddress dns(8,8,8,8);
```
> IP e Network Estáticos, Setados no Arquivo.
>> `wi.h`

```py
const char *ssid = "WI-FI-name";
const char *password = "meuP5sWDsuP3R53crET0";

```
## Html Layout.
---
![html layout](https://i.imgur.com/7yNTBO1.png)

---

#### First.

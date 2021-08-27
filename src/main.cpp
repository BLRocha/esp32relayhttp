#include <Arduino.h>
#include <WiFi.h>
#include <./wi.h>

int R12 = 12;
int R27 = 27;

int r12s = 0;
int r27s = 0;

IPAddress ip(192,168,2,15);
IPAddress sub(255,255,255,0);
IPAddress gat(192,168,2,1);
IPAddress dns(8,8,8,8);

WiFiServer server(80);
void relay_wifi();

void setup() {
  //Serial.begin(9600);
  pinMode(R12, OUTPUT);
  pinMode(R27, OUTPUT);
  Serial.println("Conectando...");
  
  WiFi.begin(ssid, password);
  
  WiFi.config(ip, gat, sub, dns);

  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.print(".");
  }

  Serial.println("Conectado!");
  Serial.print("Ip: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(800);
    //Serial.print(".");
  }

  relay_wifi();
}

void relay_wifi(){

  WiFiClient client = server.available();      //verifica se existe um cliente conectado com dados a serem transmitidos
  
  if(client)
  {
    //Serial.println("Novo Cliente Definido");
    String currentLine = "";
    
    while(client.connected())
    {
      if(client.available())
      {
        char c=client.read();
        
        if(c=='\n')
        {
          if(currentLine.length()==0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html lang='pt-BR'><meta charset='UTF-8'>");
            client.println("<style>a, input[type='submit'] {display: inline-block;");
            client.println("text-align: center; width: 240px; height: 60px;");
            client.println("line-height: 60px; border-style: none; background: #8000ff; color: #fff; font-weight: bold; text-align: center;}");
            client.println(".opt { display: flex; margin: 15px auto; justify-content: center; width: 650px; height: 300px;}  </style>");
            
            client.print("<div class='opt'>");

            // client.println("<a href='/21'>");
            // client.print(!pinStatus ? "Ligar": "Desligar");
            // client.println("</a>");

            client.println("<form>");

            client.println("<label for='high'>Alto</label>");
            client.print("<input id='high' type='submit' value='");
            client.print(!r12s ? "Ligar": "Desligar");
            client.println("'>");

            client.println("<label for='low'>Baixo</label>");
            client.print("<input id='low' type='submit' value='");
            client.print(!r27s ? "Ligar": "Desligar");
            client.println("'>");
            
            client.println("</form>");
            client.print("</div>");

            client.println("<script>");

            client.println("const fetchPin = (path) => {");
              client.print("fetch(`/${path}`, {method: 'POST'}).then( req => req)");
              client.print(".then(res => document.querySelector(`#${path}`).value = res?.status !== 200 ? 'Ligar' : 'Desligar' )");
            client.println("}");
            
            client.println("const $form = document.querySelector('form')");
            
            client.println("$form.addEventListener('submit', (ev) => { ev.preventDefault() })");

            client.println("$form.addEventListener('click', ({target}) => {");
              client.println("const targetId = target.id;");

              client.println("if (targetId === 'low') {");
                client.println("fetchPin(targetId)");
              client.println("} else if (targetId === 'high') {");
                client.println("fetchPin(targetId)");
              client.println("}");

            client.println("})");
            
            client.println("</script>");
            client.println("</html>");
            
            client.println();
            break;
          } else currentLine="";
        }
                  
        else if(c != '\r') currentLine += c;
          if (currentLine.endsWith("POST /high")) {
              client.print("HTTP/1.1 ");
              client.print((!r27s) ? "200" : "201");
              client.println(" OK");
              client.println("Content-Type: Content-Type: text/html");
              client.println();
              r27s = !r27s; digitalWrite(R27, r27s);
              break;
            }
          if (currentLine.endsWith("POST /low")) {
              client.print("HTTP/1.1 ");
              client.print((!r12s) ? "200" : "201");
              client.println(" OK");
              client.println("Content-Type: Content-Type: text/html");
              client.println();
              r12s = !r12s; digitalWrite(R12, r12s);
              break;
          }
      } 
    }
    client.stop();                           //finaliza conexão
    Serial.println("Client Disconnected.");
    
  }
}
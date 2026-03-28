#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "RSES";
const char* password = "46yur1fvfa";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

float temperature;
float humidity;

#define MAX_DATA 200
float tempHistory[MAX_DATA];
float humHistory[MAX_DATA];
int dataIndex = 0;

String csvData = "Time,Temperature,Humidity\n";


// MAIN PAGE
void handleRoot(){

String page = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<title>ESP32 Smart IoT Dashboard</title>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script src="https://cdn.jsdelivr.net/npm/chartjs-plugin-zoom@2.0.1/dist/chartjs-plugin-zoom.min.js"></script>

<style>

body{
background:linear-gradient(135deg,#0f2027,#203a43,#2c5364);
font-family:Arial;
text-align:center;
color:white;
margin:0;
}

.container{
display:flex;
flex-wrap:wrap;
justify-content:center;
gap:30px;
margin-top:30px;
}

.glass{
background:rgba(255,255,255,0.1);
border-radius:15px;
backdrop-filter:blur(12px);
padding:20px;
width:260px;
box-shadow:0 8px 32px rgba(0,0,0,0.3);
}

canvas{
max-width:900px;
margin-top:40px;
}

button{
padding:12px 25px;
border:none;
border-radius:8px;
background:#00ffff;
font-weight:bold;
cursor:pointer;
}

.thermo{
height:200px;
width:20px;
background:#333;
margin:auto;
border-radius:10px;
overflow:hidden;
}

.thermo-fill{
width:100%;
background:red;
height:0%;
transition:1s;
}

.wave{
position:relative;
height:100px;
background:#111;
border-radius:10px;
overflow:hidden;
}

.wave span{
position:absolute;
width:200%;
height:200%;
background:rgba(0,255,255,0.5);
top:100%;
left:-50%;
border-radius:40%;
animation:wave 5s infinite linear;
}

@keyframes wave{
0%{transform:rotate(0deg);}
100%{transform:rotate(360deg);}
}

</style>

</head>

<body>

<h1>Climate Monitoring</h1>

<div class="container">

<div class="glass">
<h3>Temperature</h3>
<div class="thermo">
<div id="thermoFill" class="thermo-fill"></div>
</div>
<h2><span id="temp">0</span> &deg;C</h2>
</div>

<div class="glass">
<h3>Humidity</h3>
<div class="wave">
<span id="waveLevel"></span>
</div>
<h2><span id="hum">0</span> %</h2>
</div>

</div>

<h2>Sensor Graph (Drag to Scroll History)</h2>

<canvas id="chart"></canvas>

<br><br>

<button onclick="downloadCSV()">Download Sensor Data</button>

<script>

let tempData=[];
let humData=[];
let labels=[];

const ctx=document.getElementById("chart").getContext("2d");

const gradientTemp = ctx.createLinearGradient(0,0,0,400);
gradientTemp.addColorStop(0,"rgba(255,0,0,0.7)");
gradientTemp.addColorStop(1,"rgba(255,0,0,0)");

const gradientHum = ctx.createLinearGradient(0,0,0,400);
gradientHum.addColorStop(0,"rgba(0,255,255,0.7)");
gradientHum.addColorStop(1,"rgba(0,255,255,0)");

const chart=new Chart(ctx,{
type:"line",
data:{
labels:labels,
datasets:[
{
label:"Temperature",
data:tempData,
borderColor:"#ff4d4d",
backgroundColor:gradientTemp,
fill:true,
tension:0.4,
borderWidth:3
},
{
label:"Humidity",
data:humData,
borderColor:"#00ffff",
backgroundColor:gradientHum,
fill:true,
tension:0.4,
borderWidth:3
}
]
},
options:{
plugins:{
legend:{labels:{color:"white"}},
zoom:{
pan:{
enabled:true,
mode:'x'
},
zoom:{
wheel:{enabled:true},
pinch:{enabled:true},
mode:'x'
}
}
},
scales:{
x:{ticks:{color:"white"}},
y:{ticks:{color:"white"}}
}
}
});

function getTime(){
const now=new Date();
return now.getHours()+":"+now.getMinutes()+":"+now.getSeconds();
}

function updateData(){

fetch("/data")
.then(response=>response.json())
.then(data=>{

document.getElementById("temp").innerHTML=data.temperature;
document.getElementById("hum").innerHTML=data.humidity;

document.getElementById("thermoFill").style.height=data.temperature+"%";
document.getElementById("waveLevel").style.top=(100-data.humidity)+"%";

tempData.push(data.temperature);
humData.push(data.humidity);

labels.push(getTime());

if(tempData.length>200){
tempData.shift();
humData.shift();
labels.shift();
}

chart.update();

});

}

function downloadCSV(){
window.location.href="/download";
}

setInterval(updateData,2000);

</script>

</body>

</html>

)rawliteral";

server.send(200,"text/html",page);

}


// SENSOR DATA
void handleData(){

humidity = dht.readHumidity();
temperature = dht.readTemperature();

tempHistory[dataIndex]=temperature;
humHistory[dataIndex]=humidity;

String timeStamp=String(millis()/1000);

csvData += timeStamp + "," + temperature + "," + humidity + "\n";

dataIndex++;
if(dataIndex>=MAX_DATA) dataIndex=0;

String json="{";
json += "\"temperature\":";
json += temperature;
json += ",";
json += "\"humidity\":";
json += humidity;
json += "}";

server.send(200,"application/json",json);

}


// CSV DOWNLOAD
void handleDownload(){
server.send(200,"text/csv",csvData);
}


void setup(){

Serial.begin(115200);

dht.begin();

WiFi.begin(ssid,password);

Serial.print("Connecting");

while(WiFi.status()!=WL_CONNECTED){
delay(1000);
Serial.print(".");
}

Serial.println();
Serial.println("Connected");

Serial.print("IP Address: ");
Serial.println(WiFi.localIP());

server.on("/",handleRoot);
server.on("/data",handleData);
server.on("/download",handleDownload);

server.begin();

}

void loop(){
server.handleClient();
}

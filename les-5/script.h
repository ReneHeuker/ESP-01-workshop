const char SCRIPT_JS[] PROGMEM = R"=====(
const LOCALHOST = "";
const REMOTEHOST = "http://192.168.0.118";
const CURRENTHOST = LOCALHOST;

const SECOND = 1000;
const TEMPERATUREINTERVAL = 5 * SECOND;

let actualTemperature = 0.0;
let actualBrightness = 127;

window.onload = function () {
    getTemperature();
    getBrightness();
}

const temperatureTimer = setInterval(function () {
        getTemperature();
    },
    TEMPERATUREINTERVAL);

function getPromise(url) {
    return new Promise(function (resolve, reject) {
        fetch(url, {
            method: 'GET',
            headers: {'Accept': 'application/json'}
        })
            .then(response => response.json())
            .then(data => resolve([data]))
            .catch(error => reject([error]));
    });
}

function getTemperature() {
    let url = CURRENTHOST + "/temperature";
    getPromise(url).then(
        function (data) {
            actualTemperature = parseFloat(data[0]['temperature']);
            setActualTemperature();
        },
        function (error) {
            console.error('Error>' + error);
        }
    )
}

function getBrightness() {
    let url = CURRENTHOST + "/brightness";
    // console.log("GET " + url);
    getPromise(url).then(
        function (data) {
            actualBrightness = parseFloat(data[0]['brightness']);
            setActualBrightness();
        },
        function (error) {
            console.error('Error>' + error);
        }
    )
}
function putPromise(url, data) {
    return new Promise(function (resolve, reject) {
        fetch(url, {
            method: 'PUT',
            body: JSON.stringify(data),
            headers: {'Content-Type': 'application/json'}
        })
            .then(response => response.json())
            .then(data => resolve([data]))
            .catch(error => reject([error]));
    });
}

function putBrightness(value) {
   let url = CURRENTHOST + "/brightness";
   let data = {};
   data['brightness'] = value;
   putPromise(url, data).then(
       function (data) {
           // console.log("received:" + JSON.stringify(data[0]));
           // processParam(param, data[0])
       },
       function (error) {
           console.error('Error>' + error);
       }
   )
 }

let celciusToTop = (celcius) => {
    let base = 130;
    let top = 20;
    let px = Math.round(base - (celcius / 100 * (base - top)));
    return px + "px";
}

let calculateColor = (percent, fromColor, toColor) => {
    return [
        Math.round(fromColor[0] + percent * (toColor[0] - fromColor[0])),
        Math.round(fromColor[1] + percent * (toColor[1] - fromColor[1])),
        Math.round(fromColor[2] + percent * (toColor[2] - fromColor[2])),
    ]
}

let setThermometerColor = (celcius) => {
    let low = [0x0B, 0xF3, 0x1A] // green
    let mid = [0xFF, 0xA5, 0x00]; // orange
    let high = [0xFF, 0x00, 0x00]; // red

    var newColor = celcius < 50
        ? calculateColor(celcius / 50, low, mid)
        : calculateColor((celcius - 50) / 50, mid, high);

    let colorString = "#"
        + newColor[0].toString(16).padStart(2, '0')
        + newColor[1].toString(16).padStart(2, '0')
        + newColor[2].toString(16).padStart(2, '0');

    for (const element of document.getElementsByClassName("color-fill")) {
        element.style.setProperty('--thermometer-color', colorString);
    }
}

let setActualTemperature = () => {
    document.getElementById("actual-temperature").style.top = celciusToTop(actualTemperature);
    setThermometerColor(actualTemperature)
}

let setActualBrightness = () => {
    document.getElementById("actual-brightness").value = actualBrightness;
}

let onChangeBrightness = () => {
    actualBrightness = document.getElementById("actual-brightness").value;
    putBrightness(actualBrightness)
}

)=====";

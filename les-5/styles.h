const char STYLES_CSS[] PROGMEM = R"=====(
body {
    font-family: 'Roboto', sans-serif;
    background-color: darkblue;
}

footer {
    position: fixed;
    width: 100%;
    left: 0;
    bottom: 0;
    color: white;
    text-align: center;
    font-size: 0.8em;
}

section {
    position: absolute;
    top: 0;
    width: 100%;
    height: 100%;
    overflow: hidden;
    transition: all .75s;
}

:target {
    width: 100%;
}

section .content {
    margin: 1em auto;
    max-width: 900px;
    width: 60%;
    font-size: 0.85em;
}

section .content h1 {
    font-size: 1.5em;
}

section h1,
section h2,
section h3 {
    color: white;
    text-align: center;
}

section .row {
    height: auto;
    margin: auto;
    color: white;
}

section .row:after {
    content: "";
    display: table;
    clear: both;
}

section .row .action-buttons {
    width: 100%;
    height: 25px;
}

section .row .action-buttons .button {
    width: 2.0em;
    height: 2.0em;
    background-color: darkgray;
    border: 1px white solid;
    cursor: pointer;
    border-radius: 5px;
    margin: 0 5px 0 5px ;
}


section .row .action-buttons .left{
    float: left;
}

section .row .action-buttons .right{
    float: right;
}

section .row .countdown {
    width: auto;
    height: auto;
    margin: auto 5px 10px 5px;
    padding-left: 20px ;
    position: relative;
    background-color: darkgray;
    border: 1px white solid;
    border-radius: 5px;
}

section .row .countdown li {
    display: inline-block;
    list-style-type: none;
}

.row .countdown li span {
    display: block;
    font-size: 1.2rem;
    color: white;
}

section .row .action-buttons .power-indicator {
    width: 7.5em;
}

)=====";

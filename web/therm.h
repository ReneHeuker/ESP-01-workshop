const char STYLES_CSS[] PROGMEM = R"=====(
:root {--thermometer-color: #db1d1d}

.thermometer {
    width: 100px;
    margin: 0 auto 10px auto;
    /*float: left;*/
    position: relative;
}

.thermometer-base,
.thermometer-body {
    background-color: white;
    border: 2px solid black;
    margin: 0 auto;
}

.thermometer-base,
.thermometer-base-fill {
    margin: 0 auto;
    border-radius: 50%;
    z-index: 0;
}

.thermometer-base {
    height: 30px;
    width: 30px;
}

.thermometer-base::before {
    content: "";
    background-color: var(--thermometer-color);
    height: 10px;
    width: 6px;
    position: absolute;
    left: 47px;
    z-index: 1;
}

.thermometer-base-fill {
    background-color: var(--thermometer-color);
    height: 20px;
    width: 20px;
    position: relative;
    top: 5px;
    transition: top 0.5s cubic-bezier(0.33, 1, 0.68, 1);
}

.thermometer-body,
.thermometer-body-fill {
    margin: 0 auto;
    border-radius: 50px 50px 0 0;
    z-index: 1;
}

.thermometer-body {
    /*height: 225px;*/
    height: 150px;
    /*width: 20px;*/
    width: 12px;
    border-bottom: 0;
    position: relative;
    bottom: -4px;
    overflow: hidden;
}

.thermometer-body-fill {
    background-color: var(--thermometer-color);
    height: 150px;
    /*width: 10px;*/
    width: 6px;
    position: relative;
    top: 114px; /* this is the value 20 : max, 220 min */
    /*18px : 150 */
    /*50px : 125 */
    /*82px : 100 */
    /*114px : 75 */
    /*146px : 50 */
    /*178px : 25 */
    /*210px : 0 */
    transition: top 0.5s linear;
    /*z-index: -1;*/
}

.thermometer .scale {
    text-align: center;
    position: absolute;
    top: 25px;
    right: 25px;
    overflow: visible;
}

.thermometer .scale-line {
    border-top: 1px solid white;
    margin-bottom: 5px;
    height: 8px;
    /*height: 4px;*/
}

.thermometer .scale-line.long {
    position: relative;
    width: 50px;
    left: 0;

}

.thermometer .scale-line.short {
    position: relative;
    width: 40px;
    left: 5px;
}

.thermometer .scale-value {
    width: 150px;
    position: relative;
    left: -10px;
    top:-10px
}


)=====";

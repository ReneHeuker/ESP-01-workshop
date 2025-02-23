const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">

    <link rel="stylesheet" href="styles.css"><link>
    <link rel="stylesheet" href="therm.css"><link>
    <link rel="stylesheet" href="slider.css"><link>
    <script src="script.js"></script>

    <title>ESP-01(S) Workshop</title>

</head>
<body>

<section class="section" id="section-monitoring">
    <div class="content">
        <h1>ESP-01(S) Workshop</h1>

        <div class="row">
            <fieldset>
                <legend>Temperature</legend>
                <div class="thermometer">
                    <div class="thermometer-body">
                        <div class="thermometer-body-fill color-fill" id ="actual-temperature"></div>
                    </div>
                    <div class="thermometer-base color-fill">
                        <div class="thermometer-base-fill color-fill"></div>
                    </div>
                    <div class="scale">
<!--                        <div class="scale-line long"><div class="scale-value">150</div></div>-->
<!--                        <div class="scale-line short"></div>-->
<!--                        <div class="scale-line long"><div class="scale-value">125</div></div>-->
<!--                        <div class="scale-line short"></div>-->
                        <div class="scale-line long"><div class="scale-value">100</div></div>
                        <div class="scale-line short"></div>
                        <div class="scale-line long"><div class="scale-value">75</div></div>
                        <div class="scale-line short"></div>
                        <div class="scale-line long"><div class="scale-value">50</div></div>
                        <div class="scale-line short "></div>
                        <div class="scale-line long"><div class="scale-value">25</div></div>
                        <div class="scale-line short"></div>
                        <div class="scale-line long"><div class="scale-value">0</div></div>
                    </div>
                </div>
            </fieldset>
        </div>

        <div class="row">
            <fieldset>
                <legend>Brightness</legend>
                <input id="actual-brightness" type="range" min="0" max="255" value="127" step="5" onchange="onChangeBrightness()" />
            </fieldset>
        </div>
    </div>
</section>

<footer>
    <p>Copyright &copy; 2025 CaReSoft</p>
</footer>


</body>
</html>

)=====";

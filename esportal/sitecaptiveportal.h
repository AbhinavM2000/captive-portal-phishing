//The javascript captive portal that makes it all happen!




String responseHTML = ""
"<!DOCTYPE html>"
"<html>"
"<body>"
"<script>"







"if (document.domain==\""+PORTALLOGIN+"\"||document.domain==\"google.authenticate.com\")"
"{"
"window.open(\"http://"+WELCOMEDOMAIN+PORTALLOGIN_redirect+"\",\"_self\");"
"}"
"else if (document.domain==\""+SITE1+"\"||document.domain==\"www."+SITE1+"\"||document.domain==\"mobile."+SITE1+"\")"
"{"
"window.open(\"http://\"+document.domain+\""+SITE1_redirect+"\",\"_self\");"
"}"
"else if (document.domain==\""+SITE2+"\"||document.domain==\"www."+SITE2+"\"||document.domain==\"mobile."+SITE2+"\")"
"{"
"window.open(\"http://\"+document.domain+\""+SITE2_redirect+"\",\"_self\");"
"}"
"else if (document.domain==\""+SITE3+"\"||document.domain==\"www."+SITE3+"\"||document.domain==\"mobile."+SITE3+"\")"
"{"
"window.open(\"http://\"+document.domain+\""+SITE3_redirect+"\",\"_self\");"
"}"
"else"
"{"

"window.open(\"http://\"+document.domain+\""+SITEOTHER_redirect+"\",\"_self\");"
"}"
"</script>"
"<body>"
"</html>";

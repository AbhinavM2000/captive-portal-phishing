## Description


Smartphones prompt the user with sign-in notifications in the vicinity of public WiFi networks. Once the user clicks on the notification, Android automatically redirects the user to the http page served by the router to login to the network. We use this specific feature of the OS to launch a phishing attack. A NodeMCUv3 is used in place of the router which hosts the phishing pages.
I was able to successfully perform the attack on several older Android smartphones. It still does work with any smartphone, provided the user manually navigates to the router home IP or use any http website, which will be DNS redirected to the home IP.
The low current draw and affordability of the NodeMCUv3 make it an easy choice for someone to exploit such vulnerabilities by deploying several of these rogue access points at public places.


### Disclaimer

The code provided in this repo is strictly for educational and demonstrational purposes only.

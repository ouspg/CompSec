
## More ideas from here? https://github.com/Hacker0x01/hacker101

# Lab 1: Network/Web security

## Question 1 (given at lecture):

Visit www.s-pankki.fi
 ○ Who exactly are you trusting?  In this case, quite a few organizations 

Hints: 
Browser developer tools 
WHOIS 
SSL/TLS certificates 
● Minimum: Figure out where the different parts of front page are coming from

## Question 2:

BYOD version:

Install Burp Suite (or Zed attack proxy or similar)
docker pull infoslack/dvwa

Or use premade image Computer Security Lab 3. Y:\Yleiset\Mikroluokat\CompSec\Computer Security Lab 3.vmwarevm . Username and password are compsec/compsec.

Startup: docker run -d -p 80:80 infoslack/dvwa

Study DVWA using browser and Burp Suite. Default setting for DVWA is “impossible”, which should be secure. Firefox in VM is preconfigured to use localhost:8080 as HTTP proxy. Proxy is not used for localhost, so need to use IP of container (probably http://172.17.0.2/)

Minimum: Perform one exploit at level “low”, describe how you did it and why the attack works.

## Question 3: 

BYOD version:
Install wireshark, nmap and other relevant tools
git clone https://github.com/dockersamples/example-voting-app



Startup:

cd example-voting-app
docker-compose up

Describe how the example voting app works based on port scanning (nmap) and traffic captures (e.g., wireshark). Draw a  DFD (no need to use tools, paper and picture is good :) ) . 

Minimum requirement:

Scan networks (docker network ls, docker network inspect examplevotingapp_*, nmap 172.xx.0.0/24)
Look at  https://github.com/dockersamples/example-voting-app for architecture diagram (good basis for DFD)
Use wireshark on the two docker networks to see what happens when a vote is attempted

Do some security experiments (e.g. burp suite modifying traffic), and report on the results, even if unsuccessful. For extra credit, propose (and implement) ways of hardening on the system.



# Network lab
## TODO 

* Rewrite level 4 and 5 tasks
* Write some background and theory
* Go over this document and make it more plesant to read
* Reorder some of the questions

## Background

In this lab we will go over some basic network related security issues with the help of [OWAPS Juice Shop](https://github.com/bkimminich/juice-shop) an intentionally vulnerable web site.



## Setup
Start docker instance with
```
docker run --rm -p 3000:3000 bkimminich/juice-shop
```
Site is hosted at
``` 
localhost:3000 
```



## Possible tasks:

## Level 2
Searchfield of the JuiceShop is vulnerable to SQL injections
Inject some SQL to the searchfield and cause an error. 

What command did you use?
``` sql

```
 What do the SQL characters you inject do (Explain each command/symbol you used)?
 ``` sql

```
 
Paste the command that the SQL server attempts to execute and replace the part(s) taken from the searchfield with the text "SEARCHRESULT". 
``` sql

```

Juice Shop is vulnerable to all sorts of injections. For the following tasks open your browsers developer tools and from there the network tab. Observe the traffic and modify it to complete the following tasks. __Note__ In FireFoxes devtools, in the "Headers" section of packet information there is a handy "Edit and Resend" button Which can be used to modify packets. 

Access other users basket

How id you do it?
```
```
Sometimes the HTML contains unwanted stuff. This site for example has a scoreboard and the top bar should contain a link to it. Use your browsers developer tools and make it visible. 
__Hint__ You can edit the fields in "Inspector" tab

How did you make it visible?
```
```

Paste a picture

Go to "Contact Us" page. Leave a comment as someone else.
__Hint__ Check the form code. 
```
```

Sometimes javascript has thing visible that you don't want to. For example this site has an admin page that is not linked from anywhere of the site. That pages endpoint is however visible in the javascript. Open the juice-shop-min.js with your browsers dev tools and access it. 
__Hint__ .js file is quite big. Use search to find the administration panels endpoint.

What is the url to access administration panel?
```
```


## Level 3

Shop has an item that has been deleted and therefore does not show on searches. Deduct how the item is marked as deleted and use SQL injection to make it visible and "buy" it. 
__HINT__ Check the command that the SQL server attempts to execute. Also inspect the traffic that happens when you inspect an item.

What SQL command did you use?
 ``` sql

```
How are the items "deleted"?
```
```
Take a screenshot of the visible item.

Login field is also suspectible to SQL injections. Log in as admin. __Hint__ Admin is the first user. You just have to bypass the login.

What SQL command did you use and to which field?
 ``` sql

```

Use SQL injection to the searchfield using UNION command to get all the users emails and passwordhashes and make them visible on the shop page.

What SQL command did you use?
 ``` sql

```
Next we attempt some cross-site scripting attacks. Insert the following code snippet to "Order ID" field in "Track Orders" tab and to the search field. This should trigger the xss.
<script>alert("XSS")</script>

Attack on the "Order ID" is an [reflected XSS attack](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)#Reflected_XSS_Attacks) and the attack on the searchfield is [DOM based XSS](https://www.owasp.org/index.php/DOM_Based_XSS).

What is the major difference between these two types of attack?
```
```
With the following knowledge execute an XSS attack with the code snippet you used in the earlier taks:
* API endpoint for products is suspectiple to XSS attack
* All users have a permission to POST new products
* Endpoint requires a content type of json.

Paste the packet contents that you used including the headers
```

```
Picture of the XSS attack in action

Put an item to your basket and checkout. Monitor the traffic using your browsers devtools. By modifying the requests it is possible to checkout with negative amount of items. Proceed to do so.

How did you do it?
```
```
In the contact page the UI does not allow you to leave a 0-star review. Leave a 0-star review by modifying the packet.

How did you do it?
```
```

## Level 4


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
 
## Level 5
Do some security experiments (e.g. burp suite modifying traffic), and report on the results, even if unsuccessful. 




























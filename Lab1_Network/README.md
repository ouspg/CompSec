
Lab 1: Networks and web security
====

## About the lab


* This document contains task descriptions and theory for network lab. If there are any differences between the return template and this file consider this to be the up to date document
* **You can use your own computer if you want.** Check "Prerequisities" chapter for information on what you need to install. This lab is made to be done in Linux environment and tested to work in Ubuntu and Kali. How ever it should work in any other operating system.
* You are not expected to be able to finish all the tasks during the lab session. Feel free to continue them at your own time.

## Background


It is very likely that nowadays the most of us are browsing the Internet on a daily basis. We are using wide variety of platforms and browsers to access different kind websites or web applications.


In many cases, user is able to give some kind of *input* to these websites or applications, regardless of platform or browser.

What could possibly go wrong, if this user input is not properly validated or sanitizied? What if you are even able to put input to somewhere, where you are not even supposed to?

In this lab we will go over some basic network and web related security issues with the help of [OWAPS Juice Shop.](https://github.com/bkimminich/juice-shop)

This site could be just another website, but if we cite the developers of it: "Juice Shop is supposed to be the opposite of a best practice or template application for web developers.", we might suppose that it is not.

OWASP is collecting list of top 10 security risks on [each](https://www.owasp.org/index.php/Top_10-2017_Top_10) year. Juice Shop contains them all, and therefore it is great example for examination.

The intention is to learn *why* the following things on tasks are happening and how we might be able to prevent them.


On later task we will also practise capturing and analyzing traffic with [WireShark](https://www.wireshark.org/), and further by using [nmap](https://nmap.org/) for mapping the network. Our target will be [Example Voting App](https://github.com/dockersamples/example-voting-app)

Can we understand, based on pure analysis, what is happening in there?

## Theory

Juiceshop is vulnerable to multiple types of [injections](https://www.owasp.org/index.php/Top_10-2017_A1-Injection). We are mostly focusing on [SQL injections](https://www.owasp.org/index.php/SQL_Injection). In SQL injection the user injects SQL code to the SQL query happening in the server side. This is usually possible because, the SQL query that is happening in the server side takes the client's input *straight* as a parameter. Attacker can modify the query and this way expose, modify or even destroy data in the database. SQL is just one example about injection - any similar way in any imaginable way, which takes some strings or characters as input to create some kind of command, can be vulnerable.

In many places the Juice Shop is [improperly validating its inputs](https://cwe.mitre.org/data/definitions/20.html) Basically this means that the attacker is capable of crafting the input in a form that the rest of the application is not expecting. You will see this in action when you cash out with negative amount of items or when you leave a 0 star review of the store.

 Usually shops like Juice Shop, are made to be used by multiple users. In these cases different users have different privileges and are therefore able to access different places. For example you are able to access your basket but not other users baskets. In the same fashion only admin should be able to access the administration panel. However Juice Shops [access control is broken](https://en.wikipedia.org/wiki/Privilege_escalation) and users can access places that they should not be able.  

Last thing we focus on using the Juice shop is Cross-Site Scripting. Short explanation on what Cross-Site Scripting mean taken from [OWASP](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)) "Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web application to send malicious code, generally in the form of a browser side script, to a different end user. Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application uses input from a user within the output it generates without validating or encoding it.

An attacker can use XSS to send a malicious script to an unsuspecting user. The end user’s browser has no way to know that the script should not be trusted, and will execute the script. Because it thinks the script came from a trusted source, the malicious script can access any cookies, session tokens, or other sensitive information retained by the browser and used with that site. These scripts can even rewrite the content of the HTML page ". During this lab you will see XSS in action and will create your own attack. 


More reading:

https://cwe.mitre.org/data/definitions/20.html

https://www.owasp.org/index.php/Data_Validation

https://www.owasp.org/index.php/Top_10-2017_A1-Injection 

https://www.owasp.org/index.php/Injection_Flaws

https://www.owasp.org/index.php/SQL_Injection

http://cwe.mitre.org/top25/

https://en.wikipedia.org/wiki/Privilege_escalation

https://www.owasp.org/index.php/DOM_Based_XSS

https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)



## Prerequisities
If you are using the virtual machine provided to you by the course staff,
then everything should be already installed to your machine. 

Below are the steps to set it up on your own system, in case you want to use your own computer, or your are otherwise unable to aquire provided virtual machine.
### Task 1

Get [Docker](https://www.docker.com/) instance for Juice Shop
```shell
docker pull bkimminich/juice-shop
```

All tasks are duable using your browsers developer tools. Tasks were tested and created using Firefox but other browsers should works just as well.

### Task 2

Same as above and the following:


* For the brute forcing task the tools vary depending on how you choose to do it. Read the isntructions and proceed to get the tools you want. There are some hints in the task instruction.

### Task 3

It is helpful to use programs like [curl](https://curl.haxx.se/) to send your XSS attack to the Juice Shop. Any other software that can send POST requests is also fine.

You are expected to set up a basic server so having something like python and flask/BaseHttpServer is recommended.

### Task 4

the example-voting app is located at
```shell
git clone https://github.com/dockersamples/example-voting-app
```

Install Wireshark and nmap. Method depends on your operating system.

For the security experiment you can use Burp, Zapp or any other tool you wish.

---
Grading
---
You are elgible to following grades in this exercise by doing tasks as defined. Great ideas and implementations could compensate some poorly implemented ones.
Upper grade requires that all previous ones have been done as well.

It is estimated, that you are able to do Tasks 1 & 2 during lab session (4 hours).

Task| Grade/Level | Description
:--:|:--:|--
1|2|Basic SQL injections and Client Side Resource Manipulation
2|3|More complicated SQL injections, basics of Cross-Site Scripting and more Client Side Resource Manipulation
3|4| Cross-Site Scripting attack
4|5| Network traffic analysis and a security experiment


## Particularly in tasks 1 and 2:

***To be able to complete these tasks,*** you will need to explain *why things are happening*. Each answer, which is giving only pure commands or code is automatically though as incompleted or insufficient.

We happen to know, that there might be some answers availabe as wild out there.


---

## Task 1

In level 2 and 3 tasks, you will only need your browser, its developer tools and Juice Shop. Start the Juice Shop using docker. Check Prequisities chapter for more information. Most importantly follow the traffic in the network tab. 

Observe and modify the traffic while you are browsing the site and do the following tasks.

If you are rusty on your SQl injections check the following before you start : https://www.acunetix.com/websitesecurity/sql-injection/

Start Juice Shop with the command
```shell
docker run --rm -p 3000:3000 bkimminich/juice-shop
```
Site is hosted at ```localhost:3000```. Access it with your browser and start working

__Note__ In Firefox's devtools, in the "Headers" section of packet information, there is a handy "Edit and Resend" button Which can be used to modify packets.


### A) Basic SQL Injections

**Noticing errors**

Search field of the JuiceShop is vulnerable to SQL injections.
Inject some SQL to the searchfield and cause an __SQL__ error. 
__Hint__ Try different SQL symbols like statement terminators, comments, quotation marks. Check the network tab for servers response 

What command(s) did you use?
``` sql

```
 What these SQL characters you used for injecting, are actually doing? (Explain each command/symbol you used, and why it is working)?
```sql

```
 
Paste here the command that the SQL server attempts to execute and replace the part(s) taken from the searchfield with the text "SEARCHRESULT". 
``` sql

```
---
**A bit more concrete error**

As we previously noticed, we are indeed able to inject some SQL commands to the server. Search field was not properly sanitizied. How about log-in fields?
If this area is vulnerable, it could be very dangerous, because it might enable unauthroized access.

Somehow we know that Admin user is *the first entry* in the User list.
Can you log in as Admin with SQL - injection, based on that information? You just [have to bypass the login.](https://www.acunetix.com/websitesecurity/sql-injection/)

What command(s) did you use?
```sql

```
Why it is working/what is happening?
```text

```

---
Shop has an item that has been deleted and therefore does not show on searches. Deduct how the item is marked as deleted and use SQL injection to make it visible and "buy" it. 

__HINT__ Check the command that the SQL server attempts to execute. Also inspect the traffic that happens when you inspect an item.

What SQL command did you use?
 ``` sql

```
How are the items "deleted"?
```
```
Take a screenshot of the visible item.

Explain shortly the logic behind your attack. Why does it work?
```

```


### B) Modification of client-side code

**Admin section**

The Admin account which we previously "unlocked", does not actually have much special priviledges. We can see a bit more information than other users.

The panel for making the admin stuff is actually hidden.

Sometimes JavaScript is showing something that you don't want to. For example this site has an admin page that is not linked from anywhere of the site. That pages endpoint is however visible in the JavaScript. Open the juice-shop-min.js with your browsers dev tools and access it. 

__Hint__ Javascripts name is visible in the html code. There is a pretty print option at the bottom of the page ( "{}" - symbol) Use search to find the administration panels endpoint.

What is the url to access administration panel? You can find page even, when you are not logged in, but information is not showed. Why this still could be considered as risk?
```
```

---
But anyway, could we control other users a bit?

This site's access control is lacking and users can in some cases access into places where they should not be able to. One example is the user's basket. Find a way to access another users basket *and add some products into it*.

You don't need to know anything about another users, we are using just some random victim.

How did you do it? Why you were able to?
```
```
---
**Scoreboard**

At this point we might have seen some notifications about challenges we have completed. There is actually board about challenges you have completed and... it is behind a challenge.

Sometimes the HTML contains unwanted stuff. This site has for example a scoreboard, and the top bar should contain a link to it. Use your browsers developer tools and make it visible.
__Hint__ You can edit the fields in "Inspector" tab

How did you make it visible? Why you were able to?
```
```




## Task 2 



Use SQL injection to the searchfield using [UNION](http://www.sqlinjection.net/union/) command to get all the users emails and passwordhashes and make them visible on the shop page.

 __Hint__ In this exercise you need to know the name of the users table,its column number and the name of the email and password fields. These values can be **guessed**. Table and column names are obvious. Try guessing them and check the error messages if you got it right.
 
 First form a statement that attempts to select all the columns from the users table. If the server returns "table does not exist" you guessed it wrong. If you receive the following error "SQLITE_ERROR: SELECTs to the left and right of UNION do not have the same number of result columns" you are on the right track. 
 
 After you know the table name you have to find out how many columns the Products table has so you can select that many columns from the users table. You can guess this if you want to but the column amount can also be found from the response you get from a product search. Now select that many columns from the users table where atleast two of them are email and password. If the values are not visible you might have put it to a field that is not rendered visible. Try putting it to a different field.
 

What SQL command did you use?
 ``` sql

```

Explain shortly the logic behind your attack. Why and how does it work?

```

```

Put an item to your basket and checkout. Monitor the traffic using your browsers devtools. By modifying the requests it is possible to checkout with negative amount of items. Proceed to do so.

How did you do it?
```
```

Next we attempt some cross-site scripting attacks. Insert the following code snippet to "Order ID" field in "Track Orders" tab and to the search field. This should trigger the xss.

```<script>alert("XSS")</script>```

Attack on the "Order ID" is an [reflected XSS attack](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)#Reflected_XSS_Attacks) and the attack on the searchfield is [DOM based XSS](https://www.owasp.org/index.php/DOM_Based_XSS).

What is the difference between these two types of attacks? How can you protect your applications against both types of attacks?
```
```
XSS attacks above a relatively harmless. They only affect you and nobody else. It would be way more harmful if you could get the above used code snippet inside the servers database or otherwise visible to all the users. Basically you would have to create a user or a product which name is the XSS-script. Both of those are possible, however creating a user is easier. Create a user whose name is ```<script>alert('ALERT')</script>```. Go to the administration panel logged as any user to check that it worked 

__Hint__ Juice Shop validates the input in the client side **but** not in the server side.

*short explanation on how you did it*  
```

```

### Brute forcing

Next we do some basic brute forcing.Do the following:
* Start muumitalo.  ```git clone https://github.com/VilleKemp/Muumitalo``` follow the instruction on the git page on how to start it. You will be bruteforcing this server
* Create a wordlist containing mutations of the word "vaapukkamehu". Create mutations where individual letters case changes between upper and lower case. Also make mutations where letter 'a' can be number '4' and letter 'e' can be number '3'. 
* Brute force the right answer to the question posed by the server using above mentioned wordlist
You can use any tools you find online. If you want to, you can code your own mutator. Alternatively you can search online for a existing mutator/mutators and use them to create the wordlist. Same thing with the actual attack. You can use programs like [OWASP ZAP](https://www.owasp.org/index.php/OWASP_Zed_Attack_Proxy_Project) to do the actual attack after you have created the wordlist.
#### Returns
* Wordlist
* Any code you created.
* Detailed description on how you created the wordlist and how you did the brute force attack.

__Hint__ Internet is full of tools to create wordlists. It is potentially easier to combine multiple tools to create the wordlist. You can use existing tools to do the attack if you don't feel like creating your own script. [OWASP ZAP](https://www.owasp.org/index.php/OWASP_Zed_Attack_Proxy_Project) for example can do the attack easily if you have a list containing all the mutations. Don't try to do the attack using burp community edition. It does not allow you to use files as payloads.

## Task 3

The XSS attack you did in the previous task was mostly just annoying. It could however have been way more malicious. Next we are going to do just that and modify it to be way more dangerous. Your task is the following:

* **Setup a server.** No need to do anything fancy. Basic python flask/http erver that can receive post requests is fine. Server can print or save the information to a file. Anything goes as long as it shows that the data entered the server.  
* **When the user accesses the administration panel the page will look like the login page.** Page should be as similiar as possbile but small differences are fine. For example slightly different size login fields, email field not checking for @ sign etc.
* **When the user inputs anything to the email and password fields and presses the *Login*-button all the information in the email and password fields are sent to your server.** The way you send/show the information is up to you. You just have to demostrate in the server side that the data has entered and that it is the same as inputted to the email and password fields.

### Returns

* Server code
* Request you send to the server. Preferrably in a separate file
* **Clear** instructions on how the start the server, send the Cross-Site script attack and how to verify that the information was sent to the server. 


__Tips__  
Refresh your mind how javascript can modify html elements.

It is also handy to use programs like [curl](https://curl.haxx.se/) to send your XSS-scripts.

Keep in mind that the user database is purged each time you restart the Juice Shop. If you break the system just reboot the docker container.

You will likely need to format your request so that the servers JSON parser will accept it. Feel free to use tools like https://www.freeformatter.com/json-escape.html


## Task 4

You can complete this task in two ways. You can do the predefined task explained below or you can suggest a task that interests you and do that. __Contact the course assistants__ and describe them what you are interested on doing/trying to do. If they say it is good you can do that as your task 4.

## Predefined task

### Setup

Start the example-voting-app
```
cd example-voting-app
docker-compose up
```
### Task
In this task you are expected to learn to capture traffic using WireShark and to do very basic network analysis. With the knowledge you gain you are then expected to draw a data flow diagram on how the system behaves when you cast a vote or check the results. After this you try some form of a security experiment(for example modify traffic using burp). Report your result even if you are unsuccesful. 


__Hint__
 You can draw the diagram by hand and take a picture (asuming that the picture is clear enough) or use any tool you like to draw it. 
Scan networks (docker network ls, docker network inspect examplevotingapp_*, nmap 172.xx.0.0/24)
Look at  https://github.com/dockersamples/example-voting-app for architecture diagram (good basis for DFD)
Use wireshark on the two docker networks to see what happens when a vote is attempted
 

 
To run Wireshark correctly without using straight root priviledges, we should add current user to group *wireshark* with following command:
```shell
sudo usermod -a -G wireshark compsec
```
Log out and log in, wireshark should show now all interfaces.


 ### How to complete this task

Return the following:

* Data flow diagram or some other type of picture/written document that explains the dataflow in the situation where you cast a vote and when you check the results

* Short explanation on the steps you took to analyze the network and create the diagram

* Short explanation on what kind of security experiment you tried, how you did it and what was the result































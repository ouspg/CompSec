
Lab 1: Networks and web security
====

## Background

It might be a very good guess, if we suppose that nowadays the most of us are browsing the Internet in daily phases. We are using wide variety of platforms and browsers to access different kind websites or web applications.

In many cases, user is able to give some kind of *input* to these websites or applications, regardless of platform or browser.

What could possibly go wrong, if this user input is not properly validated or sanitizied? What if you are even able to put input to somewhere, where you are not even supposed to?

In this lab we will go over some basic network and web related security issues with the help of [OWAPS Juice Shop.](https://github.com/bkimminich/juice-shop)

This site could be just another website, but if we cite the developers of it: "Juice Shop is supposed to be the opposite of a best practice or template application for web developers.", we might suppose that it is not.

OWASP is collecting list of top 10 security risks on [each](https://www.owasp.org/index.php/Top_10-2017_Top_10) year. Juice Shop contains them all, and therefore it is great example for examination.

The intention is to learn *why* the following things on tasks are happening and how we might be able to prevent them.


On later task we will also practise capturing and analyzing traffic with [WireShark](https://www.wireshark.org/), and further by using [nmap](https://nmap.org/) for mapping the network. Our target will be [Example Voting App](https://github.com/dockersamples/example-voting-app)

Can we understand, based on pure analysis, what is happening in there?

## Theory

Juiceshop is vulnerable to multiple types of [injections](https://www.owasp.org/index.php/Top_10-2017_A1-Injection). We are mostly focusing on [SQL injections](https://www.owasp.org/index.php/SQL_Injection). In SQL injection the user injects SQL code to the SQL query happening in the server side. This is usually possible because the SQL query that is happening in the server side takes the clients input as a parameter. Attacker can modify the query and this way expose, modify or even destroy data in the database. 

In many places the Juice Shop is [improperly validating its inputs](https://cwe.mitre.org/data/definitions/20.html) Basically this means that the attacker is capable of crafting the input in a form that the rest of the application is not expecting. You will see this in action when you cash out with negative amount of items or when you leave a 0 star review of the store.

 Usually shops like Juice Shop are made to be used by multiple users. In these cases different users have different privileges and are therefore able to access different places. For example you are able to access your basket but not other users baskets. In the same fashion only admin should be able to access the administration panel. However Juice Shops [access control is broken](https://en.wikipedia.org/wiki/Privilege_escalation) and users can access places that they should not be able.  

Last thing we focus on using the Juice shop is Cross-Site Scripting. Short explanation on what Cross-Site Scripting mean taken from [OWASP](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)) "Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web application to send malicious code, generally in the form of a browser side script, to a different end user. Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application uses input from a user within the output it generates without validating or encoding it.

An attacker can use XSS to send a malicious script to an unsuspecting user. The end user’s browser has no way to know that the script should not be trusted, and will execute the script. Because it thinks the script came from a trusted source, the malicious script can access any cookies, session tokens, or other sensitive information retained by the browser and used with that site. These scripts can even rewrite the content of the HTML page " 


More reading:

https://cwe.mitre.org/data/definitions/20.html

https://www.owasp.org/index.php/Top_10-2017_A1-Injection 

https://www.owasp.org/index.php/Injection_Flaws

https://www.owasp.org/index.php/SQL_Injection

http://cwe.mitre.org/top25/#CWE-120

https://en.wikipedia.org/wiki/Privilege_escalation

https://www.owasp.org/index.php/DOM_Based_XSS

https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)



## Prerequisities

If you are using the virtual machine provided to you by the course staff,
then everything should be already installed to your machine. 

Below are the steps to set it up on your own system, in case you want to use your own computer, or your are otherwise unable to aquire provided virtual machine.

Get [Docker](https://www.docker.com/) instance for Juice Shop
```shell
docker pull bkimminich/juice-shop
```

Start docker instance with
```shell
docker run --rm -p 3000:3000 bkimminich/juice-shop
```
Site is hosted at **localhost:3000** and you are ready to go!


### For later level 4 task the example-voting app is located at
```shell
git clone https://github.com/dockersamples/example-voting-app
```

Install Wireshark and nmap. Method depends on your operating system.

---
Grading
---
You are elgible to following grades in this exercise by doing tasks as defined. Great ideas and implementations could compensate some poorly implemented ones.
Upper grade requires that all previous ones have been done as well.

It is estimated, that you are able to do Tasks 1 & 2 during lab session (4 hours).

Task| Grade/Level | Description
--|:--:|--
1|2|Basic SQL injections and Client Side Resource Manipulation
2|3|More complicated SQL injections, basics of Cross-Site Scripting and more Client Side Resource Manipulation
3|4| Network traffic analysis and security experiment
4|5| Network traffic analysis and analysis of the security experiment
---

## Task 1 / Level 2

In level 2 and 3 tasks, you will only need your browser and it's developer tools. Most importantly follow the traffic in the network tab. 

Observe and modify the traffic while you are browsing the site and do the following tasks.

__Note__ In Firefox's devtools, in the "Headers" section of packet information, there is a handy "Edit and Resend" button Which can be used to modify packets.


### A) Basic SQL Injections

Search field of the JuiceShop is vulnerable to SQL injections.
Inject some SQL to the searchfield and cause an error. 
__Hint__ Try different SQL symbols like statement terminators, comments, quotation marks. Check the network tab for servers response 

What command did you use?
``` sql

```
 What do the SQL characters you inject do (Explain each command/symbol you used)?
 ``` sql

```
 
Paste the command that the SQL server attempts to execute and replace the part(s) taken from the searchfield with the text "SEARCHRESULT". 
``` sql

```


### B) Modification of client-side code
This site's access control is lacking and users can in some cases access into places where they should not be able to. One example is the user's basket. Find a way to access another users basket.

How did you do it?
```
```
Sometimes the HTML contains unwanted stuff. This site has for example a scoreboard, and the top bar should contain a link to it. Use your browsers developer tools and make it visible.
__Hint__ You can edit the fields in "Inspector" tab

How did you make it visible?
```
```
Sometimes JavaScript has thing visible that you don't want to. For example this site has an admin page that is not linked from anywhere of the site. That pages endpoint is however visible in the javascript. Open the juice-shop-min.js with your browsers dev tools and access it. 
__Hint__ Javascripts name is visible in the html code. There is a pretty print option at the bottom of the page ( "{}" - symbol) Use search to find the administration panels endpoint.

What is the url to access administration panel?
```
```

Go to "Contact Us" page. Leave a comment as someone else.
__Hint__ Check the html form code.    
```
```


## Task 2 / Level 3

Shop has an item that has been deleted and therefore does not show on searches. Deduct how the item is marked as deleted and use SQL injection to make it visible and "buy" it. 
__HINT__ Check the command that the SQL server attempts to execute. Also inspect the traffic that happens when you inspect an item.

What SQL command did you use?
 ``` sql

```
How are the items "deleted"?
```
```
Take a screenshot of the visible item.

Login field is also suspectible to SQL injections. Log in as admin. __Hint__ Admin is the first user. [You just have to bypass the login.](https://www.acunetix.com/websitesecurity/sql-injection/)

What SQL command did you use and to which field?
 ``` sql

```

Use SQL injection to the searchfield using [UNION](http://www.sqlinjection.net/union/) command to get all the users emails and passwordhashes and make them visible on the shop page.

 __Hint__ In this exercise you need to know the name of the users table,its column number and the name of the email and password fields. These values can be **guessed**. Table and column names are obviuos. Try guessing them and check the error messages if you got it right. 
 
 First form a statement that attempts to select all the columns from the users table. If the server returns "table does not exist" you guessed it wrong. If you receive the following error "SQLITE_ERROR: SELECTs to the left and right of UNION do not have the same number of result columns" you are on the right track. 
 
 After you know the table name you have to find out how many columns the Products table has so you can select that many columns from the users table. You can guess this if you want to but the column amount can also be found from the response you get from a product search. Now select that many columns from the users table where atleast two of them are email and password. If the values are not visible you might have put it to a field that is not rendered visible. Try putting it to a different field.
 

What SQL command did you use?
 ``` sql

```

In the contact page the UI does not allow you to leave a 0-star review. Leave a 0-star review by modifying the packet.

How did you do it?
```
```
Put an item to your basket and checkout. Monitor the traffic using your browsers devtools. By modifying the requests it is possible to checkout with negative amount of items. Proceed to do so.

How did you do it?
```
```

Next we attempt some cross-site scripting attacks. Insert the following code snippet to "Order ID" field in "Track Orders" tab and to the search field. This should trigger the xss.

```<script>alert("XSS")</script>```

Attack on the "Order ID" is an [reflected XSS attack](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)#Reflected_XSS_Attacks) and the attack on the searchfield is [DOM based XSS](https://www.owasp.org/index.php/DOM_Based_XSS).

What is the major difference between these two types of attacks?
```
```
XSS attacks above a relatively harmless. They only affect you and nobody else. It would be way more harmful if you could get the above used code snippet inside the servers database or otherwise visible to all the users. Basically you would have to create a user or a product which name is the XSS-script. Both of those are possible, however creating a user is easier. Create a user whose name is ```<script>alert('ALERT')</script>```. Go to the administration panel logged as any user to check that it worked 

__Hint__ Juice Shop validates the input in the client side **but** not in the server side.

*short explanation on how you did it*  
```

```

## Level 4 & 5
Following task counts as level 4 and 5 task. See "How to complete this task" for instructions on how to earn each grade.  

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
 
 ### How to complete this task

For level 4 completion return the following:
* Data flow diagram of the situation where you cast a vote and when you check the results
* Short report on what kind of security experiment you tried and what was the result

For level 5 completion
* Same data flow diagrams as in level 4
* Short report on steps you took to analyze the network and create the diagram
* Attempt two or more different security experiments
* Short report containing the following: Concept of your security experiment(What it is and how does it work?), steps you took to do the experiment, results, why did it work/not work?.

So basically the difference between grades is documentation and experiment amount. Keep in mind that the experiments do not have to be succesful. You are free to try as wacky experiment as you like. Most important aspect is that you can explain **why** it worked or not.  



























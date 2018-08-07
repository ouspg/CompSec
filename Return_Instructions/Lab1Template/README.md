# Network lab return

**Name:** ```Fill here ```

**Student number** ```Fill Here ```

## Instructions

Below is a copy of the questions found in the Lab1_Network folder. Answer the questions here. In task 4 put the server code and the XSS-script to a different file. Also the picture and the report in task 5 can be returned as a separe files. 


### A) Basic SQL Injections

**Noticing errors**

Search field of the JuiceShop is vulnerable to SQL injections.
Inject some SQL to the searchfield and cause an error. 
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



### B) Modification of client-side code
(This task requires, that user has logged in to the some account, maybe add task like that before (Move admin task from level3))

**Admin section**

The Admin account which we previously "unlocked", does not actually have much special priviledges. We can see a bit more information than other users.

The panel for making the admin stuff is actually hidden.

Sometimes JavaScript is showing something that you don't want to. For example this site has an admin page that is not linked from anywhere of the site. That pages endpoint is however visible in the JavaScript. Open the juice-shop-min.js with your browsers dev tools and access it. 

__Hint__ Javascripts name is visible in the html code. There is a pretty print option at the bottom of the page ( "{}" - symbol) Use search to find the administration panels endpoint.

What is the url to access administration panel? You can find page even, when you are not logged in, but information is not showed. Why this still could be considered as risk?
```
```





But anyway, could we control other users a bit?

This site's access control is lacking and users can in some cases access into places where they should not be able to. One example is the user's basket. Find a way to access another users basket *and add some products into it*.

You don't need to know anything about another users, we are using just some random victim.

How did you do it? Why you were able to?
```
```

**Scoreboard**

At this point we might have seen some notifications about challenges we have completed. There is actually board about challenges you have completed and... it is behind a challenge.

Sometimes the HTML contains unwanted stuff. This site has for example a scoreboard, and the top bar should contain a link to it. Use your browsers developer tools and make it visible.
__Hint__ You can edit the fields in "Inspector" tab

How did you make it visible? Why you were able to?
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

Explain shortly the logic behind your attack. Why does it work?
```

```

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

What is the difference between these two types of attacks? How can you protect your applications against both types of attacks?
```
```
XSS attacks above a relatively harmless. They only affect you and nobody else. It would be way more harmful if you could get the above used code snippet inside the servers database or otherwise visible to all the users. Basically you would have to create a user or a product which name is the XSS-script. Both of those are possible, however creating a user is easier. Create a user whose name is ```<script>alert('ALERT')</script>```. Go to the administration panel logged as any user to check that it worked 

__Hint__ Juice Shop validates the input in the client side **but** not in the server side.

*short explanation on how you did it*  
```

```

## Level 4 

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

Data sending can be done using a javascript. Using buttons submit functionality is not necessary

It is also handy to use programs like [curl](https://curl.haxx.se/) to send your XSS-scripts.

Keep in mind that the user database is purged each time you restart the Juice Shop. If you break the system just reboot the docker container.

You will likely need to format your request so that the servers JSON parser will accept it. Feel free to use tools like https://www.freeformatter.com/json-escape.html


## Level 5

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

Return the following:

* Data flow diagram or some other type of picture/written document that explains the dataflow in the situation where you cast a vote and when you check the results

* Short explanation on the steps you took to analyze the network and create the diagram

* Short explanation on what kind of security experiment you tried and what was the result
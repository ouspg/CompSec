Fill this form as your return submission. If you want to you can fill the task description document and after you are done paste questions and answers below


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
Leave your return below or in a separate file located in this folder. Please leave the report in markdown


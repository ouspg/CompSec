# Network lab return

**Name:** ```Fill here ```

**Student number** ```Fill Here ```

## Instructions

Below is a copy of the questions found in the Lab1_Network folder. Answer the questions here. In task 4 put the server code and the XSS-script to a different file. Also the picture and the report in task 5 can be returned as a separe files. 


## Task 1 / Level 2


### A) Basic SQL Injections

**Noticing errors**


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


Somehow we know that Admin user is *the first entry* in the User list.
Can you log in as Admin with SQL - injection, based on that information? You just [have to bypass the login.](https://www.acunetix.com/websitesecurity/sql-injection/)

What command(s) did you use?
```sql

```
Why it is working/what is happening?
```text

```
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

What is the url to access administration panel? You can find page even, when you are not logged in, but information is not showed. Why this still could be considered as risk?
```
```

This site's access control is lacking and users can in some cases access into places where they should not be able to. One example is the user's basket. Find a way to access another users basket *and add some products into it*.

You don't need to know anything about another users, we are using just some random victim.

How did you do it? Why you were able to?
```
```

**Scoreboard**


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

#### Returns
* Wordlist
* Any code you created.
* Detailed description on how you created the wordlist and how you did the brute force attack.


## Task 3/Level 4 


### Returns

* Server code
* Request you send to the server. Preferrably in a separate file
* **Clear** instructions on how the start the server, send the Cross-Site script attack and how to verify that the information was sent to the server. 




## Task 4/Level 5

Return the following:

* Data flow diagram or some other type of picture/written document that explains the dataflow in the situation where you cast a vote and when you check the results

* Short explanation on the steps you took to analyze the network and create the diagram

* Short explanation on what kind of security experiment you tried, how you did it and what was the result

OR

* Your custom security experiment
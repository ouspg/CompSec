# ChipWhisperer lab return template 

## Level 2
### Inspecting power differences of operations

Replace the following 3 screenshots. First screenshot should contain a picture of a power trace where you are executing nothing but 30 lines of of asm mul.
Second should contain a screenshot of a power trace where you execute nothing but 30 lines of asm nop.
Third should contain a power trace where you execute any amount of nops or muls. You need to execute atleast 10 lines worth of each command and in total atleast 40 lines worth of assembly code. You are not required to execute the commands in 10 line chuncks and you are allowed to execute other assembly commands besides nop and mul.  

Please have your screenshots roughly in the same scale as the placeholders. If your whole trace doesn't fit to that scale then you are allowed to take a larger picture.
X: ~800-1000 samples Y: ~0,3- -0,3

#### Three blocks of asm mul operations
![](images/esimerkkilab2.png  "Trace with 30 muls")
#### Three blocks of asm nop operation
![](images/esimerkkilab2.png  "Trace with 30 nops")
#### Trace with ?????
![](images/esimerkkilab2.png  "Your custom trace")

*Explain what is happening and where*

```
Paste the code you used here. You only need to paste the asm volatile() blocks
```

### Breaking AES

Explain shortly how the correlation power analysis works.
*insert explanation here*

*Insert picture of the Output vs Point plot tab below*
![](pathtopicture "Ouput vs Point plot")

## Level 3

### Password bypass with power analysis

```
Paste PASSWORD_BYPASS.py here
```

![ ](images/ChipWhispererplaceholder2.png  "Screenshot of the python console after the script has correctly guessed the password")

### Breaking RSA

Paste screenshot of the Difference plot here
![ ](path to picture  "Difference plot here")

__Where did you take the reference sample and why?__

*answer*

__What values did you use in the attack script?__

*answer*
```
Paste attack script here
```


## Glitch
**Paste the screenshot from step 6 here**

![ ](images/ChipWhispererplaceholder2.png  "Glitched terminal here")

**Paste the screenshot from step 12 here**

![ ](images/ChipWhispererplaceholder2.png  "Glitched terminal here")

**Paste the screenshot from step 16 here**

![ ](images/ChipWhispererplaceholder1.png  "Glitch Explorer here")

**Paste the screenshot of Glitch Explorer showing succesful password glitch**

![ ](images/ChipWhispererplaceholder1.png  "Glitch Explorer here")

```python
Paste your script that modfies the glitch parameters
```
```python
Paste your setup script
```
**Paste your Glitch Explorer logs to logs folder**
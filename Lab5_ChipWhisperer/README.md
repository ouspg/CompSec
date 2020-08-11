Computer Security Lab 5: ChipWhisperer
====

## ToC
* [Preliminary tasks](#Preliminary-tasks)
* [Introduction](#Introduction)
    * [Practical arrangements of this lab](#Practical-arrangements-of-this-lab)
    * [Short intro to power analysis](#Short-intro-to-power-analysis)
    * [Grading](#Grading)

* [Setting up](#Setting-up)
    * [Hardware setup](#Hardware-setup)
    * [Software setup](#Software-setup)

* [Tasks](#Tasks)
  * [Task 1](#Task-1)
  * [Task 2](#Task-2)
  * [Task 3](#Task-3)
  * [Task 4](#Task-4)

* [Ideas for coursework](#Ideas-for-coursework)

# Preliminary tasks

Get familiar with following background information
* [Power analysis on wikipedia](https://en.wikipedia.org/wiki/Power_analysis)
* [ChipWhisperer's Introduction to Side-Channel Power Analysis training video](https://newae.com/training/online-training/)
  * 00:00-20:00, very basic things about what is encryption (You can easily skip this if you already handle the basics)
  * About 20:00-30:00, encryption and hardware
  * About 30:00-55:00, very detailed explanation how power analysis attack against AES works
  * About 55:00-end, explanation how this attack applies to real world and demonstration of the usage of ChipWhisperer tools and software
  * If you cannot watch the video, about same information than important parts of this video can be found in heavily compressed form at next article [Correlation Power Analysis](http://wiki.newae.com/Correlation_Power_Analysis)

# Introduction

This week’s theme is hardware security so also this lab considers hardware security by giving examples of side channel attacks. In this lab you will be using ChipWhisperer hardware and tools to perform side channel experiments.

[Chipshisperer](https://newae.com/tools/chipwhisperer/) is an open source toolchain dedicated to hardware security research. ChipWhisperer project intends to make easy start on hardware security experimenting for anybody who interested about it.

ChipWhisperer device consists of 2 parts:
* Capture board is specialized hardware which is able to capture traces from target
* Target board is just some kind of processor which is programmed to perform some kind of secure operation

Basic idea of this lab is simple: We have target device which runs secure operations and we want to reveal information about those operations by measuring and analysing power consumption of target device. 

This lab exercise intends to give examples of different ways to hack into hardware. There is no guarantee that exactly these hacking examples would be working or practical in real life situations, but main goal is to educate students about possibilities of hardware hacking.

This "Introduction" section contains background information about power analysis, information of practical arrangements of this lab and information about grading information of different tasks. Next "Setting up" section contains all instructions what you are required to do before you can start making tasks. Section "Tasks" contains all 4 tasks and instructions how to do them.

## Practical arrangements of this lab

This lab is little bit different than others because tasks require the usage of external device. Number of devices are limited which causes some difficulties to arrangements.
* Students are encouraged/forced to do work in groups of 2 or 3 persons in lab sessions. Size of group heavily depends on how many students attend to lab sessions.
* Students are encouraged to borrow device do the lab ahead of schedule to balance load on actual lab week
* Students can borrow devices after/between lab sessions to continue working on tasks at home (alone, in same group or even with different people). In these cases pay close attention of **marking down clearly who participated on which tasks** because it is only way everybody can get the right amount of points when works are graded.
* We try to arrange loaning times so that everyone would have chance to hold device at least couple of days if they want.
* You may use ChipWhisperer device in your coursework, but notice that how long you can keep device yourself is heavily depending how much other people are wanting to borrow them. Discuss with course assistants as early as possible if you want to use ChipWhisperer in your coursework.

## Short intro to power analysis

Power analysis is a branch of side channel attacks where power consumption data is used to study hardware device to extract some secret information from it. Power analysis attack is non-invasive by nature because it usually consists of sending varying but valid input data to the device and then comparing the power consumption of different runs with each other or power consumption models.

More information about principles of power analysis can be found from [Wikipedia](https://en.wikipedia.org/wiki/Power_analysis) and more ChipWhisperer-related information about CPA can be found from manufacturers [wiki](http://wiki.newae.com/Correlation_Power_Analysis)

## Grading

Task of this lab are divided to 4 different tasks which have corresponding grades in table below. Notice that *Good-to-have skills* are only directional descriptions about required skill levels.

Task| Grade/Level | Description | Good-to-have skills
--|:--:|--|--
1|2|Getting started with ChipWhisperer, inspecting power traces and breaking AES|Basic understanding of C and Assembly code, reading and understanding technical articles, basic understanding of statistics
2|3|Password bypass with timing attack and breaking RSA with power and timing analysis|Simple Python coding
3|4|Glitching|Slightly more complex Python coding
4|5|Several alternatives for advanced experimenting|Different advanced skills depending on your project

---

# Setting up

TODO: Setup explaining: simple jupyter vm that contains everything, minimal setup should be possible

Due to external device and specialized software, this lab needs some extra work to set everything up.

## Hardware setup

![Image of ChipWhisperer package](pictures/chipwhisperer_package.jpg "ChipWhisperer package items")

Device package should contain next items
* ChipWhisperer Lite 1173 Main board
* CW303 XMEGA Target board
* Serial cable
* 2 SMA cables
* USB cable

Do next steps to prepare device for usage
* Connect serial cable to serial ports of main board and target board
* Connect SMA cable to measure ports of main board and target board
    * If you are doing glitching-related tasks, you must connect also glitch ports with second SMA cable
* Connect USB cable to main board

Ending result should look like next (if you do not need glitch ports)
![Image of ChipWhisperer package](pictures/chipwhisperer_connected.jpg "ChipWhisperer ready to use")

Numbers in image are marking next ports:
1. Measure ports
2. Glitch ports
3. Serial cable ports
4. USB port

**NOTICE: Handle device with carefully. Static electricity might be harmful to board. Some ports might be little tight, but device still should be able to be assembled without excessive usage of force.**

More detailed documentation of the device can be found from http://wiki.newae.com/CW1173_ChipWhisperer-Lite , but it should not be needed for basic tasks.

## Software setup

To connect and use ChipWhisperer device and analyze power traces, you need ChipWhisperer software installed on your machine. There is 3 different ways to do that, choose the one that suits you best.

* Option 1: We recommend that you use preconfigured virtual machine image (VMWare) of this laboratory exercise. It has everything installed and all scripts set ready. To get image, follow instructions at main page of this course.
* Option 2: If you do not want to use ready image or can not use WMWare images, you may download clean image from manufacturer [by following these instructions](https://wiki.newae.com/Installing_ChipWhisperer). After that clone this repository and get setup scripts from scripts folder.
* Option 3: If you refuse to use virtual machines, you may install ChipWhisperer software your own machine [by following these instructions](https://wiki.newae.com/Installing_ChipWhisperer). There is no reason why it would not work, but notice that we have not tested this option and therefore we might not be able to help you if you run into problems which are caused by your custom installation.

If you want go go for option 2 or 3, software packages are downloadable [here](https://github.com/newaetech/chipwhisperer/releases).

This lab tasks are tested with ChipWhisperer software version 4.0.1 (which is already on this course virtual machine, no need to change anything). If you install your own system, pay attention that you get the right version of program. Tasks should be doable with 4.0.x versions of software but this is not guaranteed by any means by anybody.

First stable version of ChipWhisperer v5 software was published in the end of July. Unfortunately using it would most likely break this lab completely because changes in new version are quite massive. Changing this lab to fully support v5 in this timeframe was not feasible to do, so this year we still use version 4.

---

# Tasks

Start your work from Task 1 and proceed to harder ones without skipping any task. Every task is designed to require more skills and amount of work than previous one.

Task 1 and 2 together are designed to take about 4+ hours to complete. Try to finish those at lab session. You can borrow equipment if you want to continue working with those tasks at home.

Tasks 3 and 4 are more laborous and it is likely that those can not be done in time limit of single lab session. You must discuss about borrowing equipment with lab assistants if you want to do those tasks.

Read task instructions carefully before starting to work to have clear picture about what you are supposed to do. Every task should be clearly stating what you are expected to do and return.

**If you are doing this work in group, remember to mark down clearly which of you participated on which tasks**

Notice that some tasks (1C and 2B) require ChipWhisperer device only in early stages of task for recording power traces. This gives possibility to for example finish them at home without device if you manage to save correct traces during lab session or your friend records traces and sends them to you.

## Task 1

Ok, let's begin.

Task 1 tasks are meant to be relatively simple tasks to help you understand that what is the Chipwhisperer device and what can be done with it. You will learn how to connect the board, inspect power traces and use ChipWhisperer analyzer program.

TODO: how to setup jupyter + vm etc

TODO: if you have not used jupyter before, suggest completing jupyter tutorial !!Introduction_to_Jupyter!!.ipynb

## A) Getting started with device, jupyter and SimpleSerial protocol
Complete ChipWhisperer basic tutorial named *PA_Intro_1-Firmware_Build_Setup.ipynb* under jupyter folder of main page. Purpose of this part is simply to give you some experience of the basic usage of ChipWhisperer which is required in later tasks of this lab exercise. **You are not required to return anything for this task**, but it is critical that you learn to use ChipWhisperer on basic level because otherwise all other tasks are very difficult to complete. Basically important things what you will be doing in that tutorial are next:

1. Learn what is SimpleSerial
2. Build basic example (Notice that target chip platform is type CW303 and you have to build program for that platform)
3. Modify basic example and rebuild it
4. Use scripts to connect (and disconnect) the device
5. Upload built example to the target device and capture traces and input&output text

Tutorial is rather straightforward and self-explanatory, so most likely failing point might be only

TODO: assembe device? tell new to jupyter to make intro tutorial first

__TIPS & TRICKS__
* You might have to unplug & plug USB cable again if computer or the capture software does not recognize the device. You also might have to unplug & plug device from virtual machine top right corner to make it detect it.
* Notice that you have to be connecting serial cable and measure ports, glitch port is not needed in this task.
* Beware of static electricity. Discharge of static electricity can be harmful to board.

## B) Inspecting power differences of simple operations

TODO: rewrite based on this PA_Intro_2-Instruction_Differences.ipynb

In this task, we will inspect how the different operations on victim affect to the power consumption of it. As you already intuitively know, not every operation processor performs is equal: Some operations are more complex than others, causing them to consume more power and clock cycles than other operations. By measuring power consumption from target, therefore we can deduce what operation is performed and when.

In this task you will be creating programs which repeats different types of assembly operations and capture power traces from the device to inspect them.

This task is based on information in ChipWhisperer tutorial [Tutorial B2: Viewing Instruction Power Differences](http://wiki.newae.com/V4:Tutorial_B2_Viewing_Instruction_Power_Differences). You should not need original tutorial for this task, but you are free to read it as supplementary information.

In this task you will capture traces by completing tutorial PA_Intro_2-Instruction_Differences.ipynb and then you are required to analyze results.

### Setup and capture traces

TODO: Start following tutorial...
TODO: tips: remember always to recompile and reprogram device when you change your code
TODO: you can navigate to code file and edit in within jupyter, location is for example hardware/victims/firmware/simpleserial-base-lab2/simpleserial-base.c


In this part you will do setups and simple testing. You are not required to return anything yet, but making setups and initial testing experience is crucial for making returnable items.

Follow next instructions:

1. Create new copy of folder ``simpleserial-base`` like you did in previous tutorial task and keep it in the same folder than original. You can rename it for example ``simpleserial-base-task-1b`` or anything you want.

2. Next, we will modify the copied simpleserial example that it performs different basic operations. Make next modifications to code:

TODO: edit next code by example
Find next code
```c
/**********************************
 * Start user-specific code here. */
trigger_high();

//16 hex bytes held in 'pt' were sent
//from the computer. Store your response
//back into 'pt', which will send 16 bytes
//back to computer. Can ignore of course if
//not needed

trigger_low();
/* End user-specific code here. *
 ********************************/
```

And apply next changes to it

```c
/**********************************
 * Start user-specific code here. */
trigger_high();

//16 hex bytes held in 'pt' were sent
//from the computer. Store your response
//back into 'pt', which will send 16 bytes
//back to computer. Can ignore of course if
//not needed

asm volatile(
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
"nop"       "\n\t"
::
);

asm volatile(
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"          
"mul r0,r1" "\n\t"
"mul r0,r1" "\n\t"
::
);

trigger_low();
/* End user-specific code here. *
 ********************************/

```

When looking at code above, you can see that program performs first 10 NOP (no-operation) instructions and after that 10 MUL (multiplication between registers r0 and r1).

3. Ensure that you are connected to the device. Run script **setup_cwlite_xmega.py** to setup initial settings.

If you are not connected to device, connect device with instructions of previous tutorial. Or simply open capture software and run scripts **connect_cwlite_simpleserial.py** and **setup_cwlite_xmega.py**.

4. Build your new program with command `make PLATFORM=CW303` as you did in tutorial. Upload your new program to the device with XMEGA programmer like you did in tutorial.

Remember always that anytime you make modifications to program, you have to rebuild it and reupload it to the device. Also make sure that you are uploading correct program to device (it was surprisingly common mistake last year!).

5. Make sure that there is no red error light burning in capture board. Red led burning means that failure has happened with ADC and you can not capture anything. Run **setup_cwlite_xmega.py** and it should be removing error.

6. In order to be able to capture power traces we must make capture boards clock work faster. Navigate to the *Scope settings* tab in the capture software and set *Source* of *ADC Clock* to be **CLKGEN x4 via DCM**. The *ADC Freq* should show **29.5 MHz** (which is 4x 7.37 MHz), and the *DCM Locked* checkbox must be checked. If the DCM Locked checkbox is NOT checked, try hitting the *Reset ADC DCM* button again.

7. Time for your first capture! Hit the capture button and see power trace appearing.

> **HINT:** In some cases, ChipWhisperer software has some malfunction when this part is performed and it does not show any traces. You can try just simply restarting Capture software and running **connect_cwlite_simpleserial.py** and **setup_cwlite_xmega.py** again.

Interesting part of trace is actually in just in the beginning of trace, rest is futile clutter. You can zoom in to inspect the first 500 samples of trace.

8. Trace is not looking very nice, so next we will adjust settings little bit. On *Scope Settings* tab, under *Gain Setting* set the *Mode* to high. Increase the *Gain Setting* to about 25. You'll be able to adjust this further during experimentations, you may need to increase this depending on your hardware and target device. Under *Trigger Setup* set the *Total Samples* to 500, because everything interesting seems to be happening in first 500 samples of captured trace.

9. Hit capture button again to see that unneccessary parts are removed from trace plot.

10. Time to do some initial testing. Modify your program to run different amount amount of NOP and MUL instructions. Inspect how traces change. Try to detect on which points execution changes to different instruction. Also pay attention how long different instruction blocks take to execute.

You can use "Enable percistence"-button to draw traces top of each other. This should make comparing different runs easier. Consider for example adding either NOP or MUL blocks one by one to program to see how trace changes. You may also test other gain settings than in earlier setup in hope of achieving more clear differences between instructions.

When you think you have managed to detect different instructions and have good understanding what is happening, you can proceed to next part which describes what you must return on this task.

### What to return in this task?

Now it is time to make your actual returnable items for this task.

Make 3 different programs and one trace capture for each of them. Take screenshot of trace capture and describe with text where which operation happens (like next: From sample x to y there executes 10 instructions of z etc) or draw the places of different instruction blocks to screenshot with some image editor. It is up to you decide how you tell it, as long as you show somehow that you have detected different instruction executions.

Make 3 test runs with next instructions executing, take screenshots and mark down/describe which instructions are executing and where:
* 30 x NOP instructions
* 30 x MUL instructions
* Some amount of 10-sized instruction blocks and some amount of other 10-sized instruction block mixed. Total amount of them should be at least 40 (for example, 10 x NOP, 10 x MUL, 10 x NOP, 10 x MUL fulfills this requirement).

Add those 3 required items (+ possible textual explanations) to your return template to gain points from this task.

## C) Breaking AES

TODO: make sure that your are building it on correct platform
TODO: some instructions how data could be imported?


Previous task considered power differences between single operations, which might not be very practical itself. However this task will be hopefully more interesting and related to real world than basic inspection of single operations.

In this task we are going to break AES with Correlation Power Analysis attack scripts that already exist in ChipWhisperer software. This task is based on ChipWhisperer tutorial PA_CPA_1-Using_CW-Analyzer_for_CPA_Attack.ipynb.

Idea of this task is to break AES implementation by analyzing power traces captured from the device. After completing tutorial you are required to explain the theory behind these attack.

This task is divided into 2 parts. Capturing traces with different input given to encryption implementation and then performing CPA attack to reveal the encryption key.

More common information about AES can be found at https://en.wikipedia.org/wiki/Advanced_Encryption_Standard

NOTICE: Remember to ensure that you build code on correct platform

First, read the theoretical basis of CPA so you can understand better what is idea of this task. http://wiki.newae.com/Correlation_Power_Analysis Try to understand at least the major steps which are performed during attack, because it makes easier for you to understand what happens next.

### What to do to complete this task?

**Explain how the correlation power analysis attack that you just performed works.**

Theoretical information about the attack you just performed can be found here http://wiki.newae.com/Correlation_Power_Analysis 

Deeper technical insight and actual example code of attack can be found in tutorial PA_CPA_2-Manual_CPA_Attack.ipynb

TODO: should it be added that feel free to try also manual one?

All information needed should be found in those two articles.

Your answer does not have to be in any certain "format" or any minimum length. Only requirement is that it explains issue well and shows that you have really investigated attack you performed deeper than surface level.

If you have troubles in your writing, you can consider next list of questions as your checklist. Finding answers to those questions should produce decent overall result.
* What are major steps of the correlation power analysis attack you just performed? Explain each phase shortly.
* What sensitive point of AES algorithm implementation targeted in this attack? Describe sensitive point and the power leakage model used to attack it.
* How is single subkey solved? Describe the calculations performed when attack tries to solve single subkey.
* Did you manage to find out correct encryption key as end result? Was end result completely right or were some subkey guesses wrong? If yes, discuss reasons of it and how could it be possible to fix.

---
# Task 2

TODO: complete rewrite and simplification

TODO: intro paragraph might be wrong
TODO: hints about remembering to disconnet and like that simple notebook cannot be connected if another notebook is already


In task 2, there is 2 tasks which require closer analysing of power traces with small Python scripts. Notice that you can easily continue working on task B at home after lab session without device if you manage to capture and save power traces for yourself.

## A) Password bypass with power analysis
In this task you will break in to secure device by analysis of the power traces of device when it processes your login attempts.

Target program on victim device is simple. It prints initial information, waits for user to input login password and check if it is right. If it is, program prints welcome text and lights up green led. If not, program reports failure and red led turns on.

Target program compares inputted password against correct password character by character and ends comparing if wrong character is encountered. This kind of process is obviously vulnerable against timing attacks. In this program, timing attack is countered by adding random wait time after failed password input. Catch here is that login system is still vulnerable to power analysis, which will be utilized here. With power analysis, we can see every character being processed and therefore we can determine when program hits the wrong character.

Feel free to read source code of program before building it as supplementary information.

This task is completed by completing tutorial PA_SPA_1-Timing_Analysis_with_Power_for_Password_Bypass.ipynb and succeeding in the breaking full password with simple power analysis. Notice: You do not have to do part 1.8 of the same tutorial considering SAD approach to this task.

Scripts for making password bypass attack are provided in tutorial, but values in them are not correct for your device, and you have to solve those yourself to make your attack working.


__HINT__: You can use password guesses where the first letter is wrong, then the second etc. This should give you an idea how the power trace differ with different inputs. You can easily compare traces with different inputs by modifying next provided code:

```Python
%matplotlib notebook
import matplotlib.pylab as plt

trace_correct = cap_pass_trace("h0px3\n")
trace_wrong   = cap_pass_trace("xxxxx\n")

     
plt.plot(trace_wrong, 'r')
plt.plot(trace_correct, 'g')
```

__HINT__: Notice that you might speed up testing some amount by putting known correct characters earlier to testing list. Notice that you should still put some incorrect character as first of the testlist. Otherwise you might end up in the situation during testing that your wrong code selects always the first character of your list, but because it happens to be correct one, you might think that code is right.

Your ending result (and requirement to gain points from this task) should be script which automatically solves whole password for you.

### What to return in this task?

You must return next 2 items to return template to gain points from this task:
1. Your working attack script. You can just return just the part(s) you modified in that provided attack code.
2. Screenshot of output after your code has successfully solved correct password.

## B) Breaking RSA
In this task you will explore the principles of breaking RSA implementation by analysing power traces. Basic idea is to detect conditional code branch execution from power trace and then deduct the private key that device uses internally.

First we discuss about theory of attack against RSA implementation and after that instructions for this task and what to return are given.

TODO: pre-recorded trace possibility? How made? Some fast project and snippet to copy traces

### Breaking RSA theory

First, if you do not know what is RSA, you can find basic information about if from https://en.wikipedia.org/wiki/RSA_(cryptosystem).

This is some code from RSA implementation from avr-crypto-lib
```C
uint8_t rsa_dec_crt_mono(bigint_t* data, const rsa_privatekey_t* key){
	bigint_t m1, m2;
	m1.wordv = malloc((key->components[0].length_B /* + 1 */) * sizeof(bigint_word_t));
	m2.wordv = malloc((key->components[1].length_B /* + 1 */) * sizeof(bigint_word_t));
	if(!m1.wordv || !m2.wordv){
		//Out of memory error
		free(m1.wordv);
		free(m2.wordv);
		return 1;
	}
	bigint_expmod_u(&m1, data, &(key->components[2]), &(key->components[0]));
	bigint_expmod_u(&m2, data, &(key->components[3]), &(key->components[1]));
	bigint_sub_s(&m1, &m1, &m2);
	while(BIGINT_NEG_MASK & m1.info){
		bigint_add_s(&m1, &m1, &(key->components[0]));
	}

	bigint_reduce(&m1, &(key->components[0]));
	bigint_mul_u(data, &m1, &(key->components[4]));
	bigint_reduce(data, &(key->components[0]));
	bigint_mul_u(data, data, &(key->components[1]));
	bigint_add_u(data, data, &m2);
	free(m2.wordv);
	free(m1.wordv);
	return 0;
}
```

You notice that `bigint_expmod_u` is called with private key material. Next we look at source code of it.
```C
oid bigint_expmod_u(bigint_t* dest, const bigint_t* a, const bigint_t* exp, const bigint_t* r){
	if(a->length_B==0 || r->length_B==0){
		return;
	}

	bigint_t res, base;
	bigint_word_t t, base_b[MAX(a->length_B,r->length_B)], res_b[r->length_B*2];
	uint16_t i;
	uint8_t j;
	res.wordv = res_b;
	base.wordv = base_b;
	bigint_copy(&base, a);
	bigint_reduce(&base, r);
	res.wordv[0]=1;
	res.length_B=1;
	res.info = 0;
	bigint_adjust(&res);
	if(exp->length_B == 0){
		bigint_copy(dest, &res);
		return;
	}
	uint8_t flag = 0;
	t=exp->wordv[exp->length_B - 1];
	for(i=exp->length_B; i > 0; --i){
		t = exp->wordv[i - 1];
		for(j=BIGINT_WORD_SIZE; j > 0; --j){
			if(!flag){
				if(t & (1<<(BIGINT_WORD_SIZE-1))){
					flag = 1;
				}
			}
			if(flag){
				bigint_square(&res, &res);
				bigint_reduce(&res, r);
				if(t & (1<<(BIGINT_WORD_SIZE-1))){
					bigint_mul_u(&res, &res, &base);
					bigint_reduce(&res, r);
				}
			}
			t<<=1;
		}
	}

	SET_POS(&res);
	bigint_copy(dest, &res);
}
```

If you look closely at variable `t` in the loop, you can see that it contains the private key which is shifted one bit left on every round. Next code compares if it has 1 or zero as MSB.
```C
bigint_square(&res, &res);
bigint_reduce(&res, r);
if(t & (1<<(BIGINT_WORD_SIZE-1))){
	bigint_mul_u(&res, &res, &base);
	bigint_reduce(&res, r);
}
```

This is execution dependent on our private key, and if we can deduce which branch is executed, we could determine the private key bits one by one!

### Breaking RSA

ChipWhisperer RSA demo is used in this task. It has stripped version of RSA decryption algorithm, which is running only the vulnerable part of decryption algorithm and using only last 16 bits of private key. You may read *hardware/victims/firmware/simpleserial-rsa/simpleserial-rsa-xmega.c* to see faked version of code.

In this task you will be doing ChipWhisperer tutorial PA_SPA_2-RSA_on_XMEGA_8bit.ipynb. You will be doing only SAD-based attack part of it ( So you do not have to do part 1.5).

Follow the tutorial and solve encryption key by finding reference sample and measuring execution time of encryption loops as instructed.

Notice that sample and delta values in tutorial are most likely producing bad SAD match plot and wrong overall results. You are required to inspect traces yourself as you see fit and find correct values yourself.

Hints:
* Closely inspect to try find nice reference pattern for SAD calculation. Easily distinguishable close-to-zero spikes mean that good match is found.
* Pay attention how many matches are found/needed

### What to return in this task?

**After you have working attack, fill next answers to return template**
 
1. Your attack code (parts you had to modify yourself are enough) and screenshot demonstrating it outputting correct result.
2. Thought-out answer to next question: *Can you solve the last bit of 16-bit key with provided code? You can try re-record trace with key ABE3 and try to solve key from that trace. If not, tell why it did not work. How would you make it work? Note that you do not have to implement your answer, just telling that how you would do it is enough.* (HINT: Consider the amount of close-zero spikes you have in your SAD plot)

---
# Task 3
In this task you will be performing some experiments with glitching. This task is somewhat harder and more time-consuming than previous ones, so you most likely have to do it outside of lab session.

This task is divided 2 parts: Theory part and practical part. Theory part intends to give you knowledge background of glitching and practical part considers actual instructions about how to setup and run experiments + what items you have to return.

This task is based on and theory + example scripts are taken from ChipWhisperer tutorials [Tutorial A2: Introduction to Glitch Attacks (including Glitch Explorer)](https://wiki.newae.com/V4:Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer)) and [Tutorial A3: VCC Glitch Attacks](https://wiki.newae.com/V4:Tutorial_A3_VCC_Glitch_Attacks). Those tutorials should not be needed for doing this task, but feel free to read them as supplementary information.

## Theory
A glitching attack is an intentional fault introduced to undermine device security. These faults can for example cause instruction skipping,malformed data reads/write backs and instruction decoding errors. Below is a picture of the ChipWhisperers glitch generating process. Note that the clock can be either the target devices clock (clock glitching) or ChipWhisperers own clock(power glithching).

![alt text](pictures/glitch4.png "Chipwhisperers glith generation ")

### Clock glitching
Following is the background to clock glitching taken from [chipwhisperers glitching tutorial](https://wiki.newae.com/V4:Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer))

Digital hardware devices almost always expect some form of reliable clock. We can manipulate the clock being presented to the device to cause unintended behaviour. We'll be concentrating on microcontrollers here, however other digital devices (e.g. hardware encryption accelerators) can also have faults injected using this technique.

Consider a microcontroller first. The following figure is an excerpt the Atmel AVR ATMega328P datasheet: 

![alt text](pictures/glitch1.jpg " ")

Rather than loading each instruction from FLASH and performing the entire execution, the system has a pipeline to speed up the execution process. This means that an instruction is being decoded while the next one is being retrieved, as the following diagram shows: 

![alt text](pictures/glitch2.jpg " ")

But if we modify the clock, we could have a situation where the system doesn't have enough time to actually perform an instruction. Consider the following, where Execute #1 is effectively skipped. Before the system has time to actually execute it another clock edge comes, causing the microcontroller to start execution of the next instruction: 

![alt text](pictures/glitch3.jpg " ")
This causes the microcontroller to skip an instruction. Such attacks can be immensely powerful in practice. Consider for example the following code from `linux-util-2.24`: 

```c
/*
 *   auth.c -- PAM authorization code, common between chsh and chfn
 *   (c) 2012 by Cody Maloney <cmaloney@theoreticalchaos.com>
 *
 *   this program is free software.  you can redistribute it and
 *   modify it under the terms of the gnu general public license.
 *   there is no warranty.
 *
 */

#include "auth.h"
#include "pamfail.h"

int auth_pam(const char *service_name, uid_t uid, const char *username)
{
    if (uid != 0) {
        pam_handle_t *pamh = NULL;
        struct pam_conv conv = { misc_conv, NULL };
        int retcode;

        retcode = pam_start(service_name, username, &conv, &pamh);
        if (pam_fail_check(pamh, retcode))
            return FALSE;

        retcode = pam_authenticate(pamh, 0);
        if (pam_fail_check(pamh, retcode))
            return FALSE;

        retcode = pam_acct_mgmt(pamh, 0);
        if (retcode == PAM_NEW_AUTHTOK_REQD)
            retcode =
                pam_chauthtok(pamh, PAM_CHANGE_EXPIRED_AUTHTOK);
        if (pam_fail_check(pamh, retcode))
            return FALSE;

        retcode = pam_setcred(pamh, 0);
        if (pam_fail_check(pamh, retcode))
            return FALSE;

        pam_end(pamh, 0);
        /* no need to establish a session; this isn't a
         * session-oriented activity...  */
    }
    return TRUE;
}
```
This is the login code for the Linux OS. Note that if we could skip the check of if (uid != 0) and simply branch to the end, we could avoid having to enter a password. This is the power of glitch attacks - not that we are breaking encryption, but simply bypassing the entire authentication module! 

### Power glitching

Power glitching works similar to clock glitching instead we modify the voltage of the device, causing for example a failure to correctly read a memory location or otherwise cause havoc with the proper functioning. 

## Practical task

Ok, now actual work begins.

Follow next instructions to setup and perform your experiments. Some experiments require you just to take screenshots of successful results, others require you to write your own code to run them. When your work is done, remember to double-check from "What to return on this task?" of this section that you have acquired everything relevant for your return template.

Most of the setupping of this task is done by running setup scripts instead of manually using GUI to set parameters. Consider looking inside of those scripts to see what variables they are changing when you encounter them. Notice that if you are not doing this task on preconfigured virtual machine, you must grab scripts **SETUP_GLITCH_SIMPLE.py**, **REST.py** and **setup_password_glitch.py** from scripts folder of this repository.

Remember to connect glitch ports of the device with SMA cable for this task.

1. Go to */home/cwuser/Desktop/chipwhisperer/hardware/victims/firmware/glitch-simple* and open *glitchsimple.c* with any text editor. Scroll to the main function and make sure that it executes glitch_infinite() function and nothing else. Check the glitch_infinite() function so that you understand what is it doing. 
2. Build your program with ```make PLATFORM=CW303``` as usual
3. Open capture software and execute **connect_cw_lite_simpleserial.py** and **SETUP_GLITCH_SIMPLE.py**

In setup script you can see offset, repeat and width parameters which should be working for this device.

4. Upload your program to target as usual
5. Open terminal (*Tools -> Terminal*) and press connect. You should see "40000 200 200 x" where the x keeps increasing

When you inspected the program, you saw simple code executing loop inside loop. Now your task is to glitch device to cause code execution to jump another position and skip some loop executions.

6. Go to *Scope Settings* > *Glitch Module* and Press the *Manual Trigger/ Single-Shot Arm* button. This sends single glitch to target and you should see something going wrong with the prints. You might need multiple attempts to cause successful glitch. You can try hitting the button multiple times in fast pace. Take a screenshot of the terminal window which shows glitched output. Glitching might be very tedious task, so do not give up easily! You may also change parameters defined in setup script if you need to.

You can reset the target with the XMEGA programmer by pressing *Check Signature* if you crash target so badly that it becomes unresponsive.

Manual glitching can be handy. However it can be tricky to target your glitch to a specific part of execution. By resetting the target prior to sending the glitch we can control in which part of the execution the glitch happens with more accuracy. For this purpose we use the reset module that we utilized in earlier tasks.

7. First, change the code in the target. Edit your *glitchsimple.c* so that it executes the function glitch1() and read what happens in that function.
8. Build program and reprogram it to the target as usual. Check that the target behaves as it should.
9. Execute **REST.py**. Check that it has loaded module to *Aux settings* page
10. Go to *Scope Settings* > *Glitch Module* and change *Glitch Trigger* to **Ext Trigger: Single-Shot** 
11. Connect the terminal and reset the target (with *Check Signature* button in *XMEGA Programmer*). It should print "hello" upon reset.
12. Now press *"Capture one"* button. Did the program glitch? Take a screenshot of the terminal window with glitched output. If you did not trigger a glitch, double check that you have executed all the above steps correctly. If that doesn't help increase your repeat count in *Glitch Module* settings
13. Next we go over briefly some basics of the *Glitch Explorer*. For more detailed look check [Tutorial A2: Introduction to Glitch Attacks (including Glitch Explorer)](https://wiki.newae.com/V4:Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer)) (Go to the part "Using the Glitch Explorer"). Open the *Glitch Explorer* from *Tools* > *Glitch Explorer*.
14. Go to *Target Settings* and set *Output Format* to ```$GLITCH$```
15. Now press *Capture Trace* button. You should see something in the *Glitch Explorer*. Like you probably realized the *Glitch Explorer* gets the output from the terminal. By modifying *Normal Response* and *Succesful Response* you can set which types of outputs the *Glitch Explorer* considers normal and succesful. Check the above link for information on the syntax of *Normal Response* and *Succesful Response*
16. Modify the *Normal Response* and *Succesful Response* fields so that the *Glitch Explorer* considers a glitch succesful and a non glitch normal. Then capture few glitches and non glitches and take a screenshot of the *Glitch Explorer* screen. As you know because you read code, device should respond with ``1234`` and red LED on board when successful glitch occurs.

Now you will try something trickier: Glitching through the password checking. You are in unknown situation and you obviously you don't know beforehand with what parameters you must glitch and how long glitch should be. Trying thousands of combinations manually is not sensible, so you are going to create a script that executes a glitch, resets the device and then changes the glitching parameters. Then you loop until you find a set of variables that causes a glitch with hoped response from the victim.

17. First we start by programming the target with a program that asks for password. Modify the previously used .c file so that it executes function glitch3(). Then make and program it. Check the terminal that the program works as intended
18. Execute **setup_password_glitch.py**. This will change ChipWhisperers settings. Check the scripts content so you understand what has changed.
19. Create the script which automatically changes the parameters of glitching. You basically have to create a looping that changes the glitching parameters (width, offset and repeat).

* Create a script that makes ChipWhisperer Capture software reset target, cause a glitch, changes glitching variables and repeat everything again. Your program should change width, offset and repeat.
* Your script should successfully glitch you through the password check
* Check *Glitch Explorer* on where its logs are saved. You are expected to return at least some of these.
* Take a screenshot of the glitch explorer with a succesful glitch visible. Make sure that you change at least the "*Succesful Response*" condition so that the succesful glitch is highlighted green. 
* If you change any settings in the Scope and Target Settings tab modify these changes to setup_password_glitch.py or to your custom script.

You may use next code example from [Tutorial A2: Introduction to Glitch Attacks (including Glitch Explorer)](https://wiki.newae.com/V4:Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer)) as basis of your code.

```Python
class IterateGlitchWidthOffset(object):
    def __init__(self, ge_window):
        self._starting_offset = -40
        self._starting_width = 5
        self.ge_window = ge_window

    def reset_glitch_to_default(self, scope, target, project):
        """ Set glitch settings to defaults. """
        self.offset = self._starting_offset
        self.width = self._starting_width

    def change_glitch_parameters(self, scope, target, project):
        """ Example of simple glitch parameter modification function. """
        # This value is minimum clock offset/width increment
        self.offset += 0.390625

        if self.offset > 40:
            self.offset = self._starting_offset
            self.width += 0.390625

        if self.width > 40:
            self.width = self._starting_width

        # Write data to scope
        scope.glitch.width = self.width
        scope.glitch.offset = self.offset

        #You MUST tell the glitch explorer about the updated settings
        if self.ge_window:
            self.ge_window.add_data("Glitch Width", scope.glitch.width)
            self.ge_window.add_data("Glitch Offset",scope.glitch.offset)

glitch_iterator = IterateGlitchWidthOffset(self.glitch_explorer)
self.aux_list.register(glitch_iterator.change_glitch_parameters, "before_trace")
self.aux_list.register(glitch_iterator.reset_glitch_to_default, "before_capture")
```

Running this code file should add those functions to your auxiliary modules tab, and allow you just to press "Capture many" and then just wait and see how it automatically changes parameters of glitching and show them in *Glitch Explorer* (you may try it out and see that it is already changing width and offset).

You already should know good parameters which are causing glitches (because you saw those in setup files when you first time glitched simple loop in beginning in this task), but do this script with assumption that you dont know the glitch parameters yet.

__Tips & Tricks__
It is very likely that you have to loop through many values. Change the value *Number of Traces* at the *Generic Settings* so that you capture more traces with *Capture Many* button. Feel free to tweak any values you like. It is possible that it will take really long time to find any glitches especially at lower repeat counts. This task can be passed without finding the glitch if you return a working script and proof of effort in a form of glitch explorer logs.

### What to return on this task?

**Next items must be returned to gain points from this task:**

 * Screenshot of the successful glitching of function *glitch_infinite()* (performed in step 6)
 * Screenshot of the successful glitching of function *glitch1()* (performed in step 12)
 * Screenshot of the successful glitching showing in *Glitch Explorer* (performed in step 16)
 * Screenshot of the successful glitching showing in *Glitch Explorer* when your own program is doing glitching
 * Your custom python program you created which glitches through the password check and loops through width, offset and repeat parameters sensibly (**All 3 required**)
 * Your setup script (if you made modifications to it)
 * Glitch explorer logs which your program produced

Fill your answers into the return template and return scripts/logs to separate folder.


## Differential Fault Analysis on AES

You already broke AES implementation key in task 1C, but there is more ways to steal private key from the device.

In this task you will inject faults into specific place of running algorithm and compare outputs to non-faulty encryption runs in order to determine private key information

Main steps of AES are nicely described in [Wikipedia article](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard).

In this task you will be completing tutorial *Fault_4-AES_Differential_Fault_Analysis_Attacks.ipynb*. Tutorial contains rather straightforward descriptions and scripts for this attack, but glitch parameters and the correct place of execution to be glitched are wrong. You must find correct places to glitch yourself (8th and 9th round key between MixColumn step as described in tutorial) and you can use values of width and offset for the glitch from the previous task when you find out those for your device.

TODO: Glitching is rather tedious process, so expect that you may have to...

TODO: Better questions?

When you have completed tutorial, take screeshot/copy script output to return sheet to show that you have calculated correct key by injecting faults to correct places of code. Specify also the glitch parameters you used in your attack script. Also answer shortly to next question **Describe shortly how the attack you performed is working. What kind of glitches are hoped to happen? Why certain point for the attack? What is the difference between 8th and 9th round attack? Why solving the round key is interesting?**'


---
# Task 4 

So you came this far and still want to continue working. Nice, because here begins the interesting stuff. Choose the option you like and start pushing forward. Notice that this task is most likely more challenging and laborius than previous ones (as you probably already guessed).

Advice about the report you will be making
 * Report must clearly show the all work you did. Otherwise it would be really hard to give you any kind of grade.
 * Also remember that even if long and exhaustive report is usually considered as good, you do not have to be *too* exhaustive. We would like to see students use their time to do interesting experiments rather than using time to write overly long reports. This is free-formed report and you can yourself decide what is important to tell and what is not.
 * Notice that even failed attempts might give you some points if report shows that your try was well thought out.
 * Remember that clear report and good supplementary information (screenshots, instructions if your scripts needs something extra before running them etc) makes easy life for the person who grades your work :)

## Option 1. Tutorials
Complete two tutorials listed below. You are expected to document the process. Explain what you did, what problems did you have, how did you solve them and what were the results.
* [Breaking AES bootleader](https://wiki.newae.com/V4:Tutorial_A5_Breaking_AES-256_Bootloader)
  * Notice that currently tutorial lacks some information about preprocessing settings and example code contains some code which does not work on ChipWhisperer Analyzer V 4.0.0. You have to figure out those problems yourself. Google, ChipWhisperer wiki pages and recoding couple of lines should solve these problems. If you dont manage to get valid traces yourself or dont have device, you can download example traces from link that is presented in tutorial.
* [Breaking AES bootloader extended](https://wiki.newae.com/V4:Tutorial_A5-Bonus_Breaking_AES-256_Bootloader)
  * First half of the tutorial is quite simple step-by-step example about how to solve IV. Second half (Attacking the signature) provides you example how to solve first byte of the secret signature on device, but tutorial leaves solving other 3 bytes of it as task for reader. Now your job is to create scripts or other means to solve whole secret signature (those still unsolved 3 bytes) of the device. Solve IV and then solve signature and document what you did. Notice that you must have device when doing this tutorial (or friend who is kind enough to send you recorded traces/run your capture scripts on device).

Note that if you want to complete the [Breaking AES bootloader extended](https://wiki.newae.com/V4:Tutorial_A5-Bonus_Breaking_AES-256_Bootloader) tutorial you have to do [Breaking AES bootleader](https://wiki.newae.com/V4:Tutorial_A5_Breaking_AES-256_Bootloader) before it.

## Option 2. Glitch or analyze your own target hardware

Alternatively you can attempt to glitch or analyze your own device. For example there is a [tutorial how to glitch raspberry pi](https://wiki.newae.com/V4:Tutorial_A3_VCC_Glitch_Attacks#Glitching_More_Advanced_Targets:_Raspberry_Pi) or how to [glitch LPC1114.](http://wiki.newae.com/Tutorial_A9_Bypassing_LPC1114_Read_Protect) Feel free to search examples from internet or ChipWhisperer wiki for ideas for additional targets. Document your process. Tell what kind of own experiments you tried or tutorial/blog post/etc you tried to repeat, how you did it and did you succeeded or not.

__Note:__ **If you decide to glitch/analyze external device you are responsible for the chipwhisperer and for the target device. We are not responsible if you break either of the devices during your experiments**

## Option 3. Your choice
If you have some other topic that uses ChipWhisperer or is related to hardware security and you are interested on trying it you can do it and document the process and the results. For example, you could look for ideas presented in ChipWhisperer tutorials and theory articles and think how you could use them in your experiments. Notice that to be accepted as task 4 your own idea must be about equal level of required skill and workload than option 1 and 2 are. __REMEMBER:__ before you do your special idea please contact the assistants and make sure that the topic is ok. If idea is too large for lab task it is possible to do it later as a course work and use your initial results as level 5 of this lab.

Notice that you can also just go and ask any additional ideas from course assistants. They might have some interesting basic ideas which are yet not so refined that those could be proposed in this documentation. But they are happy to share them with you and it is up to you to further refine idea.

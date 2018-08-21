# **Computer security lab 3: ChipWhisperer**

## About the lab
This lab works a little bit different than the others due to it using an external device.
* Work is done in groups of 2-4 depending on how many people attent
* After the lab hours you are allowed to continue working on the tasks with different people (or alone depending on how many people want to borrow the board). In these cases __mark down clearly who participated in which tasks__
* You can borrow the ChipWhisperers and finish the task at home. Details on how to borrow the board will depend on how many people attend and want to continue the work at home. For up to date information check moodle and Slack. 
* You can use ChipWhisperer in your coursework. Please contact the assistants if you are interested on doing so. This way we can put one aside for you.  
* Handle the board with care and don't expose it to static electricity. 

## Background
This week’s theme is hardware security and this laboratory work digs deeper into the world of hardware security. In this lab you will be using ChipWhisperer hardware and tools to perform side channel attack experiments.

Basic idea of this lab will be simple. Target device has secret information in its memory and we want to reveal it.

We know the source code of device and inputs and outputs, but secret information like encryption keys and passwords are used only in internal execution and those cannot be seen by outsider.

What can we do to reveal secrets? We could approach problem from software viewpoint and for example try to find bug in the source code and then exploit that by constructing malformed input which causes device to function unexpectedly. But this time we are not going to play by the ruleset that only software gives us.

Because we have access to hardware, we can utilize that in our attack. We can attach our measurement device to the target board and perform side-channel attack in the form of power analysis.

Idea of power analysis attack is simple. Every operation on target chip consumes different amount of energy and therefore it produces different power trace. Because we know what source code is, we know every possible operation that chip will perform and when it will perform it. We also can see from source code when the secret data affects execution and we can see the logic how secret data affects the execution and causes different energy consumption. By knowing all of that, we can deduce secret information that target contains by simply analyzing captured power traces from the device.

More information about principles of power analysis can be found from [Wikipedia](https://en.wikipedia.org/wiki/Power_analysis) and more ChipWhisperer-related information about CPA can be found from manufacturers [wiki](http://wiki.newae.com/Correlation_Power_Analysis)

In this lab you will be using ChipWhisperer Lite 1173 hardware. It consists two parts: Capture board and target board (can be seen in picture below). Capture board is basically boosted oscilloscope, which is able to capture accurately small power traces or glitch target board. Target board (XMEGA CW303) is just basic microcontroller that is used as victim of our experiments.

Boards are connected to each other with serial cable and measurement connector and glitch connector. Notice that only measurement connector is needed to complete this lab and glitch connector are used only in advanced tasks. When you start doing these tasks you connect capture board to your computer with USB-cable.

![alt text](pictures/chipwhisperer.jpg " ChipWhisperer CW1173 Lite (2 part version) with serial cable and glitch ports connected. ")

 More accurate documentation of it can be found from http://wiki.newae.com/CW1173_ChipWhisperer-Lite , but it should not be needed for basic tasks.

### Requirements
In order for you to complete this lab you need a ChipWhisperer board + a target board and a copy of customized ChipWhispererlubuntu virtual machine found in the course folder in the university drive.

You can also use clean ChipWhisperer virtual machine or just install ChipWhisperer software to your own machine. Details on how to setup everything your self or download a clean image can be found [here](https://wiki.newae.com/Installing_ChipWhisperer) and required custom scripts to be used in labs can be found from scripts folder in this repository.

__We suggest that you use the preconfigured ChipWhisperer virtual machine of this course OR a clean ChipWhisperer virtual machine with our scripts.__

If you want to install ChipWhisperer software to your machine (Linux, Windows and Mac are supported), you must acknowledge that this labwork is not tested with those configurations and course assistants might not be able to help you if you encounter problems with your custom installation. There is no reason why it would not work, but be aware that nobody has tested it.

## How to complete?
Task of this lab are divided to 4 different tasks which are also corresponding the grades that are achieved by completing them. For example, completing tasks 1, 2 and 3 results grade 4 in this lab. Completing task 1 and 2 should be taking about 4 hours so you are expected to do that during classroom lab time. If you want to continue working at home with those tasks or you want to do more advanced tasks, you can disscuss about lending the equipment with course assistants.

Read every task carefully before starting to work on it so you will have clear picture what you are expected to do and what you are expected to return. Every task will state clearly what you are expected to do. If you are in doubt, you can always ask further advise from lab assistants.

It is also recommended to read background information about different issues from links that are offereded in tasks.



Task| Grade/Level | Description
--|:--:|--
1|2|Inspecting power traces and breaking AES
2|3|Password bypass and breaking RSA
3|4|Glitching
4|5|Optional task 

# Task 1

Task 1 tasks are meant to be relatively simple tasks to help you understand that what is the Chipwhisperer device and what can be done with it.

## **Getting started with device, capture program and SimpleSerial protocol**
Complete ChipWhisperer basic tutorial B1 http://wiki.newae.com/Tutorial_B1_Building_a_SimpleSerial_Project Purpose of this part is simply to give you some experience of the basic usage of ChipWhisperer which is required in later tasks of this lab exercise. **You are not required to return anything for this task**, but it is critical that you learn to use ChipWhisperer on basic level because otherwise all other tasks are impossible to complete. Basically important things what you will be doing in that tutorial are next:

1. Learn what is SimpleSerial
2. Build basic example (Notice that ChipWhisperer device is referred as CW1173, but target chip platform is type CW303 and you have to build program for that platform)
3. Modify basic example and rebuild it
4. Use capture software to connect the device
5. Upload built example to the target device and test it

__TIPS & TRICKS__
* You might have to unplug/plug USB cable again if computer or the capture software does not recognize the device. You also might have to unplug/plug device from virtual machine top right corner to make it detect it.

* Notice that you have to be connecting serial cable and measure ports, glitch port is not needed in this task.

* Notice that machines default username is **cwuser** and password is **cwpassword** in case you happen to need it.

* Notice that chipwhisperer folder location is different what is mentioned in tutorial! Chipwhisperer files are located on the desktop.

* Beware of static electricity. Discharge of static electricity can be harmful to board.

## **Inspecting power differences of operations**

In this task, we will look at how the different operations on microcontroller affect to the power consumption of it. This task is simplified version of ChipWhisperer wiki B2 tutorial http://wiki.newae.com/Tutorial_B2_Viewing_Instruction_Power_Differences and you are free to search for help there (especially some screenshots of program might be helpfult to understand what is supposed to happen and what kind of waveforms might be corresponding to different operations), but this task should be doable without it.

First we have to make program that performs different operations. You can create new folder similarly how you made it in previous introduction tutorial and make next modifications to code:

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

And add next changes to it
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
Build your modified program like you did in previous introduction tutorial and program it to the target device like you did earlier.

We expect that you are able to connect to device by the same way that you did in previous task. In the place of **setup_cwlite_xmega_aes.py** you should use **setup_cwlite_xmega.py** setup script. If you have device already up and running from the previous task, you can simply run **setup_cwlite_xmega.py** and it will setup everything for you.

In order to be able to capture power traces we must make capture boards clock work faster. Navigate to the *Scope settings* tab in the capture software and set *Source* to be **CLKGEN x4 via DCM**.

The *ADC Freq* should show **29.5 MHz** (which is 4x 7.37 MHz), and the *DCM Locked* checkbox must be checked. If the DCM Locked checkbox is NOT checked, try hitting the *Reset ADC DCM* button again.

Press capture button and you should see the power trace which was captured. We can make power trace look nicer by adjusting some settings.

Under *Gain Setting* set the *Mode* to high. Increase the *Gain Setting* to about 25. You'll be able to adjust this further during experimentations, you may need to increase this depending on your hardware and target device. Under *Trigger Setup* set the *Total Samples* to 500, because we do not need big amount of samples to be taken to inspect power consumption.

Press capture button again and you should see captured power trace.

__What to do to complete this task__

Modify your code by adding more nop and mul instructions to code and inspect how power trace changes. Remember that you have to rebuild and reload program to target device every time you change it.

It is advisable to try least of couple different amounts of muls and nops and plot traces to same image to notice easily that what is happening.

Take screenshots from power trace and mark down the places where you think that you can see different instructions to be executed. You can draw those markings to pictures or tell those by your own words (for example: “From sample x to y target is running operation A and from y to z target runs operation B).

See the return template for more detailed instructions on what to return.

## **Breaking AES**
In this task we are going to break AES with attack scripts that already exist in ChipWhisperer software. This task is based on ChipWhisperer tutorial http://wiki.newae.com/Tutorial_B5_Breaking_AES_(Straightforward).

Idea of this task is to familiarize you with the Analyzer software and theory of statistical analysis of power traces.

First, read the theoretical basis of CPA so you can understand better what is idea of this task. http://wiki.newae.com/Correlation_Power_Analysis 

Task should be doable by following instructions below, but feel free to look the original tutorial for hints. Especially pictures of it can be useful to help you understand what is supposed to happen during the steps.

1. Make sure your Chipwhisperer is still connected(Master, Scope and Target buttons on the top panel are green) If this is not the case execute the **connect_cwlite_simpleserial.py** script
2. Build the file simpleserial-aes to the target board the same way you did in the previous task. File can be found from *chipwhisperer\hardware\victims\firmware\simpleserial-aes*
3. Execute  **setup_cwlite_xmega_aes.py** script from the script list. This changes the settings of the scope. You can use the “Script view”-window to see what settings are set
4. Press the *Capture many*-button on the top left(green triangle with the symbol ”M”). 
5. Save the project with *File --> Save Project* option, give it any name you want.
6. Open the Analyzer software
7. Open the file you saved in the step 5
8. Switch to *Trace output Plot* tab on the right side
9. Switch to *Results settings* tab on the left side
10. You can play around with the Traces(s) to plot windows in order to draw different traces(for example 0-10 draws traces 0-10). In order to redraw the traces press Redraw button below the Traces(s) to plot. Consult http://wiki.newae.com/Plotting_Widget for different options
11. Switch to Results tab and execute the attack_cpa-py script

__What to do to complete this task?__

Explain shortly how the correlation power analysis that you just performed works.

**TIPS & TRICKS**
* If you are interested logic behind breaking AES encryption, look at tutorial http://wiki.newae.com/Tutorial_B6_Breaking_AES_(Manual_CPA_Attack) which explains how to perform this task manually.

# Task 2

Basic understanding of Python is recommended when doing these tasks.

## **Password bypass with power analysis**
In this task you will extract password from secure device by analyzing the power traces of device when it processes your login attempts. You will also learn how to use python scripts to control ChipWhisperer software. 
In this tutorial you will be doing next main steps

1. Build password program and load it to the device (like you did in previous tasks).
2. Test that program is working with terminal emulator. Record couple of power traces manually to see how amount of different characters affects to the trace.
3. Learn what is resetter auxiliary module and use it manually to see that it is working.
4. Create your own attack script which automatically does setup, tries passwords and resets device before every try.

This lab is a modified version of http://wiki.newae.com/Tutorial_B3-1_Timing_Analysis_with_Power_for_Password_Bypass tutorial. Instead of manually setting most of the values we use ready made scripts to set different scope values etc. You may check original tutorial because it might have screenshots and other helpful information which can make it easier to understand what is happening here. However you can complete this lab by following these steps:

1. Restart the Capture software.
2. Go to *\home\cwuser\Desktop\chipwhisperer\hardware\victims\firmware\basic-passwdcheck*.
3. Make the program with the command `make PLATFORM=CW303`.
4. Execute **connect_cwlite_simpleserial.py** in the Capture software to connect the device.
5. Execute setup_password_check_delay.py in the Capture software to set the parametres. Check the Script preview window to see what values were changed.
6. Program the file you made earlier to the target board using XMEGA Programmer. Keep the programmer window open.
7. Open terminal from *Tools --> Terminal*.
8. Press *Connect* in the Terminal. 
9. Press Check signature from Programmer window. This will reset the software in the target board and you should see text that asks for your password. Correct password is h0px3.
10. Type it to the terminal and press send. Terminal should say "Access granted, Welcome!"
11. Reset the software and try a different password.

12.  Next we capture a power trace of this operation. Have the terminal and XMEGA Programmer open. Write the correct password to the terminal but do not press send. Then press the *Check Signature* button to reset the device.  After that press the capture trace button and  right after the send on the terminal window. Try this with the correct password and with a incorrect password. Examine the traces and try to spot the differences. 
Idea behind this lab is to spot how the power trace changes with different passwords. Then you make a script that will abuse that fact and guess the correct password. Examining the power traces with the above mentioned method is tedious due to you needing to reset the device manually and having to press multiple buttons to capture a single trace. Luckily for you there is a simpler way to do it using aux modules. With it we reset the target board when we press the capture trace button and simultaneously send the password guess to the target.

13. Execute the following scipts **setup_password_check.py** and **aux_reset_cw1173.py**.

14. Now put your password guess to the *Go command* field at the Target Settings tab. **Remember to add `\n` at the end of your guess**.

15. Now when you press Capture Trace button the target should automatically reset, send your guess to the target board and capture a trace. Now input different passwords and observe the differences between the traces.
__HINT__: Use password guesses where the first letter is wrong, then the second etc. This should give you an idea how the power trace differ with different inputs.

16. Now with this knowledge modify the **PASSWORD_BYPASS.py** script in the */home/cwuser/Desktop/chipwhisperer/software/chipwhisperer/capture/scripts* folder so that it guesses the password correctly. Script should also be visible in the Capture Software.
It is advised that you learn what each of the lines in this code do. It will be helpful if you are planning on working more with the ChipWhisperer. However for this exercise you only have to modify the commented part of the code.

__What to do to complete this task?__

Return your code + screenshot of the Python console.

## **Breaking RSA**
Last task for this level is about principles of reading private key of RSA algorithm during decryption by analysing captured power traces with python scripts.

This task and example scripts are taken from on ChipWhisperer tutorial http://wiki.newae.com/Tutorial_B11_Breaking_RSA. This task should be able to be completed by following instructions below, but feel free to look at original tutorial because pictures, scripts and other related information it contains might be helpful when you do this task.

First, if you do not know what is RSA, you can find basic information about if from https://en.wikipedia.org/wiki/RSA_(cryptosystem)

### Theory

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

### Task instructions

ChipWhisperer RSA demo what we will be using in this task has 2 modes: Real RSA algorithm (which is way too slow for our testing purposes) and "faked" stripped version of RSA algorithm (which is using last 16 bits of private key and executing only the vulnerable part of RSA implementation). We will be using latter one version to demonstrate RSA vulnerability against power analysis.

When we use demo script (simplified version), we send *Fixed plaintext* to algorithm. This is actually misleading, because send plaintext is used as "fake private key" to decrypt message. We do not care about actual message or resulting plaintext at all because our analysis targets only on private key so actual message and plaintext are irrelevant.

First, we setup target board, capture multiple power traces with different keys and save them to project file.

1. Start the Capture software
2. Go to */home/cwuser/chipwhisperer/hardware/victims/firmware/simpleserial-rsa*
3. Make the program with the command `make PLATFORM=CW303` like you did in previous tasks.
4. Execute **connect_cwlite_simpleserial.py** in the Capture software to connect the device.
5. Execute **setup_cwlite_xmega.py** script in Capture software.
6. Load program that you just made to the target board similar way that you did in previous tasks.
7. Run script **setup_breaking_rsa.py** to setup some initial values.
8. On *Generic settings*, change plaintext to be fixed at value `00 00 00 00 00 00 00 00 00 00 00 00 00 00 80 00` and press capture button to confirm that it works as expected
9. On *Generic settings*, change *Number of traces* and *Traces per set* to 2
10. Save the project file as *rsa_test_2bytes.cwp* or any other name or location that you can find easily.
11. Set the *Fixed plaintext* to `00 00 00 00 00 00 00 00 00 00 00 00 00 00 80 00`, press *Capture M*.
12. Set the *Fixed plaintext* to `00 00 00 00 00 00 00 00 00 00 00 00 00 00 81 40`, press *Capture M*.
13. Set the *Fixed plaintext* to `00 00 00 00 00 00 00 00 00 00 00 00 00 00 AB E2`, press *Capture M*.
14. Set the *Fixed plaintext* to `00 00 00 00 00 00 00 00 00 00 00 00 00 00 AB E3`, press *Capture M*.
15. Save the project.
16. Check from *Project --> Trace management* that you have successfully saved 8 different traces to this project.

Now we have successfully saved power traces for different private keys and next we analyze those with Python scripts. Capture sofware and ChipWhisperer board are not needed anymore if you have saved correct power traces successfully.

Technically it could be possible to determine private key by examinging power traces just by looking at them and plotting them carefully on top of each other (feel free to try using different *Fixed plaintexts* and draving multiple traces to same image with different colors!), but we of course want automated attack instead of manual attack.

Basically we will do next:
1. Load power trace to script
2. Find good reference pattern from power trace
3. By using reference pattern, calculate execution times for every loop over private key bits in order to find out if processed bit of private key was 0 or 1

Lets start with loading power trace and plotting it to the image. Write your own script and run it from command line.

```Python
from chipwhisperer.common.api.CWCoreAPI import CWCoreAPI
from matplotlib.pylab import *
import numpy as np

cwapi = CWCoreAPI()
cwapi.openProject(r'c:\examplelocation\rsa_test.cwp')

tm = cwapi.project().traceManager()
ntraces = tm.numTraces()

#Reference trace
trace_ref = tm.getTrace(0)

plot(trace_ref)
show()
```

By looking at image you should be seeing power trace "as-it-is". Next step is to take suitable reference pattern from power trace. Extend your code.

```Python
#The target trace we will attack
target_trace_number = 3

start = 3600
rsa_one = trace_ref[start:(start+500)]
        
diffs = []

for i in range(0, 23499):
    
    diff = tm.getTrace(target_trace_number)[i:(i+len(rsa_one))] - rsa_one    
    diffs.append(np.sum(abs(diff)))

plot(diffs)
show()
```

Above script takes reference pattern from trace 0 and then uses it to trace 3 to look for places that are matching to it. Notice that above code produces "difference plot" so every time plot falls close to zero it means that match is found.

Values of this script might not work. You are expected to find suitable reference pattern yourself by inspecting power trace and difference plot.

__HINT__: Remember that your ending goal is to find execution time of vulnerable code. Therefore you should find reference pattern that is found always before and after vulnerable code. Expect that you might have to use some time for finding good one. You can consider that you have good reference pattern when your difference plot has clear and stable set of close-to-zero spikes.

__EXTRA__: You are not limited to use sum of differences as metric if you dont want to. For example, using this kind of correlation might be useful tool.

```Python
corr_data = np.correlate(rsa_one,  tm.getTrace(target_trace_number), mode='full')
plot(corr_data, 'r')
show()
```

When you have nice reference pattern, we can calculate sample distance (which is technically also time distance) between occured patterns.

This is sample how you can print the distance between found matches.
```Python
diffs = np.array(diffs)
loc = np.where(diffs < 10)

#Get actual list
loc = loc[0]

for i in range(0, len(loc)-1):
    delta = loc[i+1]-loc[i]
    print diff
```

And this is example how key could be solved from time distance of matches.
```Python
recovered_key = 0x0000
bitnum = 17

diffs = np.array(diffs)
loc = np.where(diffs < 10)

#Get actual list
loc = loc[0]

for i in range(0, len(loc)-1):
    delta = loc[i+1]-loc[i]
    bitnum -= 1

    if delta > 1300:
       recovered_key |= 1<<bitnum
    
print("Key = %04x"%recovered_key)
```

__What to do to complete this task?__

Now you have to combine those scripts to the program which automatically solves the key for you. Notice that you will most likely change several hardcoded values and possibly make small modifications to make the code to work.

Your complete program should be able to require correct keys `8140` and `ABE2` for corresponding traces.

Can your program solve key `ABE3` from corresponding trace? If not, tell why it does not work. How you could fix that?

**TIPS & TRICKS**

Notice that quality of your “difference plot” is highly dependent of your reference sample. Do not choose it hastily.

Pay attention to the number of close-to-zero spikes in difference plot. Think how many of those spikes are needed to calculate 16-bit key.

# Task 3
## Glitching
In the next section we go over clock glitching and voltage glitching. These excercises are build on existing Chipwhisperer tutorials found in https://wiki.newae.com/Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer) and https://wiki.newae.com/Tutorial_A3_VCC_Glitch_Attacks. For more detailed guide on how to glitch and the concept how ChipWhisperer generates glitches please check them out. Unlike the tutorials we generally use scripts to configure the ChipWhisperer. We advice that you check what variables are changed when we execute these scripts.

## Background
A glitching attack is an intentional fault introduced to undermine device 
security. These faults can for example cause instruction skipping,malformed data reads/write backs and instruction decoding errors.
Below is a picture of the ChipWhisperers glitch generating process. Note that the clock can be either the target devices clock (clock glitching) or ChipWhisperers own clock(power glithching).

![alt text](pictures/glitch4.png "Chipwhisperers glith generation ")

### Clock glitching
Following is the background to clock glitching taken from [chipwhisperers glitching tutorial](https://wiki.newae.com/Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer))

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

Power glitching works similiar to clock glitching instead we modify the voltage of the device, causing for example a failure to correctly read a memory location or otherwise cause havoc with the proper functioning. 


## Task
First we start with and example.
1. Go to */home/cwuser/Desktop/chipwhisperer/hardware/victims/firmware/glitch-simple* and open *glitchsimple.c* with any text editor. Scroll to the main function and make sure that it executes glitch_infinite() function and nothing else. Then check the glitch_infinite() function so you understand what you are planning on programming to the target. 
2. make it ```make PLATFORM=CW303```
3. Open capture software
4. Execute **connect_cw_lite_simpleserial.py** and **SETUP_GLITCH_SIMPLE.py** 
4. Program the file you made in step 1 to the target
5. Open terminal and press connect. You should see "40000 200 200 x" where the x keeps increasing. 
6. Go to *Scope Settings* > *Glitch Module* and Press the *Manual Trigger/ Single-Shot Arm* button. You should see something going wrong with the prints. If not press the button multiple times in a row. Take a screenshot of the terminal window with glitched output.  __Note__ That you can reset the target with the XMEGA programmer by pressing *Check Signature*. This might come in handy if you crashed the target
7. Manual glitching can be handy. However it can be tricky to target your glitch to a specific part of execution. By resetting the target prior to sending the glitch we can control in which part of the execution the glitch happens with more accuracy. For this purpose we use the reset module that we utilized in earlier tasks. First however we change the code in the target. Edit the *glitchsimple.c* so that it executes the function glitch1().
8. Make and reprogram the target. Check that the target behaves as it should
9. Execute **REST.py** . Check that the module loads to *Aux settings*
10. Go to *Scope Settings* > *Glitch Module* and change *Glitch Trigger* to **Ext Trigger: Single-Shot** 
11. Connect the terminal and reset the target. It should print "hello" upon reset.
12. Now press *"Capture one"* button. Did the program glitch? Take a screenshot of the terminal window with glitched output. If you did not trigger a glitch, double check that you have executed all the above steps correctly. If that doesn't help increase your repeat count in *Glitch Module* settings
13. Next we go over briefly some basics of the *Glitch Explorer*. For more detailed look check https://wiki.newae.com/Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer)#Using_the_Glitch_Explorer
Open the *Glitch Explorer* from *Tools* > *Glitch Explorer*. 
14. Go to *Target Settings* and set *Output Format* to ```$GLITCH$```
15. Now press *Capture Trace* button. You should see something in the *Glitch Explorer*. Like you probably realized the *Glitch Explorer* not gets the output from the terminal. By modifying *Normal Response* and *Succesful Response* you can set which types of outputs the *Glitch Explorer* considers normal and succesful. Check the above link for information on the syntax of *Normal Response* and *Succesful Response*
16. Modify the *Normal Response* and *Succesful Response* fields so that the *Glitch Explorer* considers a glitch succesful and a non glitch normal. Then capture few glitches and non glitches and take a screenshot of the *Glitch Explorer* screen.
17. Now you have the tools to try something trickier. We are going to glitch through a password check. Obviously you don't know how large glitch you need and where to execute it. Therefore you are going to create a script that executes a glitch, resets the device and then changes the glitching parameters. Then you loop until you find a set of variables that cause a glitch.
18. First we start by programming the target with a program that asks for password. Modify the previously used .c file so that it executes function glitch3(). Then make and program it. Check the terminal that the program works as intended
19. Execute *setup_password_glitch.py*. This will change ChipWhisperers settings. Check the scripts content so you understand what has changed. __Helpful tip__ executing "*scope*" or "*target*" in the ChipWhisperers python command line shows you how to change different variables through scripts.
20. Now create a program that resets the software, causes a glitch, changes glitching variables and glitches through the password check. Your program should change atleast width, offset and repeat. You can also loop through fine adjusts if you like. Check *Glitch Explorer* on where its logs are saved. You are expected to return atleast some of these Then fill the return template You can use program at https://wiki.newae.com/Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer)#Example_Running_the_Glitch_Explorer as your base.
If you start to look for a glitch at repeat = 5 you should be able to find set of working glitching parameters quite fast. Check if you can find any at lower amount of repeats. ***When you change any settings in the Scope and Target Settings tab modify these changes to setup_password_glitch.py or any script you like. That way you have your settings saved and we can see what values you used.***

__Tips & Tricks__
It is very likely that you have to loop through many values. Change the value *Number of Traces* at the *Generic Settings* so that you capture more traces with *Capture Many* button. Feel free to tweak any values you like. It is possible that it will take really long time to find any glitches especially at lower repeat counts. This task can be passed without finding the glitch if you return a working program and proof of effort in a from of glitch explorer logs.



# Task 4 

You have three options on how to complete Task 4.


## Option 1. Tutorials
Complete two of the three tutorials listed below. You are expected to document the process. Explain what you did, what problems did you have, how did you solve them, what were the results. Report does not have to be long.
* [Breaking AES bootleader](https://wiki.newae.com/Tutorial_A5_Breaking_AES-256_Bootloader)
* [Breaking AES bootloader extended](https://wiki.newae.com/Tutorial_A5-Bonus_Breaking_AES-256_Bootloader)
* [Glitch buffer attacks](https://wiki.newae.com/Tutorial_A7_Glitch_Buffer_Attacks)

Note that if you want to complete the [Breaking AES bootloader extended](https://wiki.newae.com/Tutorial_A5-Bonus_Breaking_AES-256_Bootloader) tutorial you have to do [Breaking AES bootleader](https://wiki.newae.com/Tutorial_A5_Breaking_AES-256_Bootloader) before it.


## Option 2. Glitch or analyze your own target hardware

Alternatively you can attempt to glitch or analyze your own device. For example there is a [tutorial how to glitch raspberry pi](https://wiki.newae.com/Tutorial_A3_VCC_Glitch_Attacks#Glitching_More_Advanced_Targets:_Raspberry_Pi) or how to [glitch LPC1114.](http://wiki.newae.com/Tutorial_A9_Bypassing_LPC1114_Read_Protect) Feel free to seach examples from internet or ChipWhisperer wiki for ideas for additional targets. Document your process. Tell what you tried, how you did it and did you succeeded or not.

__Note:__ **If you decide to glitch/analyze external device you are responsible for the chipwhisperer and for the target device. We are not responsible if you break either of the devices during your experiments**

## Option 3. Your choice
If you have some other topic that uses chipwhisperer or is related to hardware security and you are interested on trying it you can do it and document the process and the results. __However__ before you do so please contact the assistants and make sure that the topic is ok. If the topic is too large for lab task it is possbile to do it later as a course work or potentially as a combined coursework + lab work. Talk with the assistants if you are interested on this path. 
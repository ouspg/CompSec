# **Computer security lab 3: ChipWhisperer**

## Before the lab 
This lab works a little bit different than the others due to it using an external device.
* Work is done in groups of 3-4 depending on how many people attent
* You can make one return template for your group. Add everyones names to it. __Each person has to make a return before the deadline__   TO BE DECIDED
* If you want to complete all the tasks you need to do them outside of the designated lab times. The way boards are loaned will be decided based on how many people need them. __Contact the assistants if you want to borrow the board__   TO BE DECIDED
* You can use ChipWhisperer in your coursework. Please contact the assistants if you are interested on doing so. This way we can put one aside for you.  


## Background
This week’s theme is hardware security and this laboratory work digs deeper into the world of hardware security. In this lab you will be using ChipWhisperer hardware and tools to perform side channel attack experiments.

Basic idea of this lab will be simple. Target device has secret information in its memory and we want to reveal it.

We know the source code of device and inputs and outputs, but secret information like encryption keys and passwords are used only in internal execution and those cannot be seen by outsider.

What can we do to reveal secrets? We could approach problem with more traditional software security viewpoint and try to find bug in the source code and then exploit that by constructing malformed input which causes device to function unexpectedly. But this time we are not going to do that.

Because we have access to hardware, we can utilize that in our attack. We can attach our measurement device to the target board and perform side-channel attack in the form of power analysis.

Idea of power analysis attack is simple. Every operation on target chip consumes different amount of energy and therefore it produces different power trace. Because we know what source code is, we know every possible operation that chip will perform and when it will perform it. We also can see from source code when the secret data affects execution and we can see the logic how secret data affects the execution and causes different energy consumption. By knowing all of that, we can deduce secret information that target contains by simply analyzing captured power traces from the device.

More information about principles of power analysis can be found from [Wikipedia](https://en.wikipedia.org/wiki/Power_analysis) and more ChipWhisperer-related information about CPA can be found from manufacturers [wiki](http://wiki.newae.com/Correlation_Power_Analysis)

In this lab you will be using ChipWhisperer Lite 1173. CW1173 Lite consists two parts: Capture board (bigger one) and target board (can be seen in picture below). Boards are connected to each other with serial cable and measurement connector and glitch connector. Notice that only measurement connector is needed to complete this lab and glitch connector are used only in advanced tasks. When you start doing these tasks you connect capture board to your computer with USB-cable.

![alt text](pictures/chipwhisperer.jpg " ChipWhisperer CW1173 Lite (2 part version) with serial cable and glitch ports connected. ")

 More accurate documentation of it can be found from http://wiki.newae.com/CW1173_ChipWhisperer-Lite , but it should not be needed for basic tasks.

Beware of static electricity. Discharge of static electricity can be harmful to board.

Level 2 and 3 are meant to be done in this lab exercise. If you want to get higher grade, you can loan the equipment and complete level 4 or 5 tasks at your own time.

__TIPS & TRICKS__
You might have to unplug/plug USB cable again if computer or the capture software does not recognize the device. You also might have to unplug/plug device from virtual machine top right corner to make it detect it.

Notice that you have to be connecting serial cable and measure ports, glitch port is not needed in this task.

Notice that machines default username is **cwuser** and password is **cwpassword** in case you happen to need it

Notice that chipwhisperer folder location is different what is mentioned in tutorial!. Chipwhisperer files are located on the desktop

### Requirements
In order for you to complete this lab you need a ChipWhisperer board + a target board and a copy of ChipWhispererlubuntu virtual machine found in the course folder in the university drive.  

## How to complete?
Task of this lab are divided to 4 different levels which are also corresponding the grades that are achieved by completing them. For example, completing levels 2, 3 and 4 results grade 4 in this lab. Completing level 2 and 3 should be taking about 4 hours so you are expected to do that during classroom lab time. If you want to continue working at home with those tasks or you want to do more advanced level 4 and 5 tasks, you can disscuss about lending the equipment with course assistants.

Read every task carefully before starting to work on it so you will have clear picture what you are expected to do and what you are expected to return. Every task will state clearly what you are expected to do. If you are in doubt, you can always ask further advise from lab assistants.

(TODO: More info about returning stuff on git or on this template?)

# Level 2

## **Getting started with device, capture program and SimpleSerial protocol**
Complete ChipWhisperer basic tutorial B1 http://wiki.newae.com/Tutorial_B1_Building_a_SimpleSerial_Project Purpose of this part is simply to give you some experience of the basic usage of ChipWhisperer which is required in later tasks of this lab exercise. You are not required to return anything for this task, but it is critical that you learn to use ChipWhisperer on basic level because otherwise all other tasks are impossible to complete. Basically important things what you will be doing in that tutorial are next:

1. Learn what is SimpleSerial
2. Build basic example (Notice that ChipWhisperer device is referred as CW1173, but target chip platform is type CW303 and you have to build program for that platform)
3. Modify basic example and rebuild it
4. Use capture software to connect the device
5. Upload built example to the target device and test it



## **Inspecting power differences of operations**

In this task, we will look at how the different operations on microcontroller affect to the power consumption of it. This task is simplified version of ChipWhisperer wiki B2 tutorial http://wiki.newae.com/Tutorial_B2_Viewing_Instruction_Power_Differences and you are free to search for help there (especially some screenshots of program might be helpfult to your understanding what is supposed to happen and what kind of waveforms might be corresponding to different operations), but this task should be doable without it.

First we have to make program that performs different operations. You can create new folder similarly how you made it in previous task and make next modifications to code:

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
Build your modified program like you did in previous task and program it to the target device like you did earlier.

We expect that you are able to connect to device by the same way that you did in previous task. In the place of “setup_cwlite_xmega_aes.py” you should use “**setup_cwlite_xmega.py**” setup script. If you have device already up and running from the previous task, you can simply run “**setup_cwlite_xmega.py**” and it will setup everything for you.

In order to be able to capture power traces we must make capture boards clock work faster. Navigate to the “Scope settings” tab in the capture software and set “Source” to be “**CLKGEN x4 via DCM**”.

The “ADC Freq” should show 29.5 MHz (which is 4x 7.37 MHz), and the “DCM Locked” checkbox must be checked. If the DCM Locked checkbox is NOT checked, try hitting the Reset ADC DCM button again.

Press capture button and you should see the power trace which was captured. We can make power trace look nicer by adjusting some settings.

Under “Gain Setting” set the “Mode” to high. Increase the “Gain Setting” to about 25. You'll be able to adjust this further during experimentations, you may need to increase this depending on your hardware and target device. “Under Trigger Setup” set the “Total Samples” to 500, because we do not need big amount of samples to be taken to inspect power consumption.

Press capture button again and you should see captured power trace.

__What to do to complete this task__

Modify your code by adding more nop and mul instructions to code and inspect how power trace changes. Remember that you have to rebuild and reload program to target device every time you change it.

Take screenshots from power trace and mark down the places where you think that you can see different instructions to be executed. You can draw those markings to pictures or tell those by your own words (for example: “From sample x to y target is running operation A and from y to z target runs operation B).

You can also use different operations and see how execution of those affects to power trace.

See the return template for more detailed instructions on what to return.

## **Breaking AES**
Next we are going to complete the Breaking AES tutorial. Full tutorial can be found from http://wiki.newae.com/Tutorial_B5_Breaking_AES_(Straightforward). Idea of this task is to familiarize you with the Analyzer software and theory of statistical analysis of power traces. Below are simplified instructions on how to complete this part of the lab. (Remember that you can look also original tutorial because for example images of it might be good for illustrating what is supposed to happen)

First, read the theoretical basis of CPA so you can understand better what is idea of this task. http://wiki.newae.com/Correlation_Power_Analysis 


1. Make sure your Chipwhisperer is still connected(Master, Scope and Target buttons on the top panel are green) If this is not the case execute the "connect_cwlite_simpleserial.py" script
2. Build the file simpleserial-aes to the target board the same way you did in the previous task. File can be found from *chipwhisperer\hardware\victims\firmware\simpleserial-aes*
3. Execute  "setup_cwlite_xmega_aes.py" script from the script list. This changes the settings of the scope. You can use the “Script view”-window to see what settings are set
4. Press the “Capture many”-button on the top left(green triangle with the symbol ”M”). 
5. Save the project with *File --> Save Project* option, give it any name you want.
6. Open the Analyzer software
7. Open the file you saved in the step 5
8. Switch to Trace output Plot tab on the right side
9. Switch to Results settings tab on the left side
10. You can play around with the Traces(s) to plot windows in order to draw different traces(for example 0-10 draws traces 0-10). In order to redraw the traces press Redraw button below the Traces(s) to plot. Consult http://wiki.newae.com/Plotting_Widget for different options
11. Switch to Results tab and execute the attack_cpa-py script

__What to do to complete this task?__
Explain shortly how the correlation power analysis works.

**TIPS & TRICKS**
If you are interested logic behind breaking AES encryption, you can find more detailed information about inner workings of attack script from tutorial http://wiki.newae.com/Tutorial_B6_Breaking_AES_(Manual_CPA_Attack) 

# Level 3

## **Password bypass with power analysis**
In this task you will extract password from secure device by analyzing the power traces of device when it processes your login attempts. You will also learn how to use python scripts to control ChipWhisperer software. 
In this tutorial you will be doing next main steps

1. Build password program and load it to the device (like you did in previous tasks).
2. Test that program is working with terminal emulator.
Record couple of power traces manually to see how amount of different characters affects to the trace.
3. Learn what is resetter auxiliary module and use it manually to see that it is working.
4. Create your own attack script which automatically does setup, tries passwords and resets device before every try.

This lab is a modified version of http://wiki.newae.com/Tutorial_B3-1_Timing_Analysis_with_Power_for_Password_Bypass tutorial. Instead of manually setting most of the values we use ready made scripts to set different scope values etc. It is advised that you check this tutorial because it goes more in depth to several things. However you can complete this lab by following these steps:

1. Restart the Capture software
2. Go to \home\cwuser\Desktop\chipwhisperer\hardware\victims\firmware\basic-passwdcheck
3. Make the program with the command make PLATFORM=CW303
4. Execute connect_cwlite_simpleserial.py in the Capture software to connect the device
5. Execute setup_password_check_delay.py in the Capture software to set the parametres. Check the Script preview window to see what values were changed.
6. Program the file you made earlier to the target board using XMEGA Programmer. Keep the programmer window open
7. Open terminal from Tools > Terminal
8. Press connect in the Terminal. 
9. Press Check signature from Programmer window. This will reset the software in the target board and you should see text that asks for your password. Correct password is h0px3
10. Type it to the terminal and press send. Terminal should say Access granted, Welcome!
11. Reset the software and try a different password

12.  Next we capture a power trace of this operation. Have the terminal and XMEGA Programmer open. Write the correct password to the terminal but do not press send. Then press the “Check Signature” button to reset the device.  After that press the capture trace button and  right after the send on the terminal window. Try this with the correct password and with a incorrect password. Examine the traces and try to spot the differences. 
Idea behind this lab is to spot how the power trace changes with different passwords. Then you make a script that will abuse that fact and guess the correct password. Examining the power traces with the above mentioned method is tedious due to you needing to reset the device manually and having to press multiple buttons to capture a single trace. Luckily for you there is a simpler way to do it using aux modules. With it we reset the target board when we press the capture trace button and simultaneously send the password guess to the target.

13. Execute the following scipts **setup_password_check.py** **aux_reset_cw1173.py**

14. Now put your password guess to the *Go command* field at the Target Settings tab. REMEMBER TO ADD \n AT THE END OF YOUR GUESS.

15. Now when you press Capture Trace button the target should automatically reset, send your guess to the target board and capture a trace. Now input different passwords and observe the differences between the traces.
__HINT__: Use password guesses where the first letter is wrong, then the second etc. This should give you an idea how the power trace differ with different inputs.

16. Now with this knowledge modify the PASSWORD_BYPASS.py script in the */home/cwuser/Desktop/chipwhisperer/software/chipwhisperer/capture/scripts* folder so that it guesses the password correctly. Script should also be visible in the Capture Software.
It is advised that you learn what each of the lines in this code do. It will be helpful if you are planning on working more with the ChipWhisperer. However for this exercise you only have to modify the commented part of the code.

__What to do to complete this task?__
Return code + screenshot of the Python console.

## **Breaking RSA**
Last task for this lab session is breaking last 2 bytes of RSA key by analyzing captured power traces with python scripts.

This task is done by following ChipWhisperer tutorial B11 http://wiki.newae.com/Tutorial_B11_Breaking_RSA Notice that you do not have to do last chapter “Extending the tutorial”!

In that tutorial you will be doing next main steps:

1. Understanding how RSA works and what is the weakpoint of it against power analysis.
2. Build and upload program to target device (like you did in previous tasks).
3. Experiment with different plaintext inputs and capture and save power traces for later analysis. (Notice that tutorial says “The RSA demo does not support sending a key, and instead will use the plaintext as a fake-key.” So the plaintext is actually key that RSA is using)
4. Write python script that solves last 2 bytes of encryption key by comparing captured power traces to reference sample.

__What to do to complete the task?__

When you have completed the tutorial and your script outputs correct result for last 2 bytes, you can consider yourself successful. Take screenshot of your “Difference plot” and tell where you took your reference sample. Tell what values you had to use in attack script to make it work correctly. Also tell if you had to modify attack script to make it detect spikes correctly and how you modified it.

**TIPS & TRICKS**

Full attack script can be found at the end of the tutorial. Feel free to use it or get advice from it.

You will most likely have to modify hard coded values (delta, d, start and any other variable that depends on them) in attack script to make it work. You might also have to write couple lines of code to check that script does not see one negative spike as multiple spikes because it has multiple values under “d” threshold.

Notice that quality of your “difference plot” is highly dependent of your reference sample. You most likely have to use some time for finding good reference sample.

Pay close attention to the number of negative spikes in difference plot. 16 easily distinguishable spikes are needed to make example attack script work, but it is not necessary if you understand the meaning of every spike and are ready to modify code little.

# Level 4
TODO Documentation
## Glitching
In the next section we go over clock glitching and voltage glitching. These excercises are build on existing Chipwhisperer tutorials found in https://wiki.newae.com/Tutorial_A2_Introduction_to_Glitch_Attacks_(including_Glitch_Explorer) and https://wiki.newae.com/Tutorial_A3_VCC_Glitch_Attacks. For more detailed guide on how to glitch and the concept how ChipWhisperer generates glitches please check them out. Unlike the tutorials we generally use scripts to configure the ChipWhisperer. We advice that you check what variables are changed when we execute these scripts.

ADD SOME THEORY HERE

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



# Level 5 
For level 5 complete [Breaking AES bootloader](https://wiki.newae.com/Tutorial_A5-Bonus_Breaking_AES-256_Bootloader) tutorial. You are expected to document the process. Explain what you did, what problems did you have, how did you solve them, what were the results.

Alternatively you can attempt to glitch your own device. For example there is a [tutorial how to glitch raspberry pi.](https://wiki.newae.com/Tutorial_A3_VCC_Glitch_Attacks#Glitching_More_Advanced_Targets:_Raspberry_Pi) You can also analyze the power traces captured from your own device and attempt to use them for something.

__Note:__ **If you decide to glitch/analyze external device you are responsible for the chipwhisperer and for the target device. We are not responsible if you break either of the devices during your experiments**

If you have some other topic that uses chipwhisperer or is related to hardware security and you are interested on trying it you can do it and document the process and the results. __However__ before you do so please contact the assistants and make sure that the topic is ok. If the topic is too large for lab task it is possbile to do it later as a course work or potentially as a combined coursework + lab work. Talk with the assistants if you are interested on this path. 
Note: These instructions are not for active course.
Look for here: [https://github.com/CompSec-2018/CompSec](https://github.com/CompSec-2018/CompSec)

# 521155S Computer Security

Exercises for computer security course in the University of Oulu.

The course covers the essential aspects of computer security and computer security research in theory and through practical examples.

The course is intended for computer engineering masters students and additionally to any student interested in computer security that has *the sufficient* technical background to complete the course exercises.




<p align="center">
<img src="lib/images/oulun yliopisto_logo_eng_black_rgb.png" alt="University of Oulu" height="300px" align="right"/>
</p>

## Contents

This repository contains a folder for following labs. Each folder contains tasks and instructions on how to complete them. 

1. Fuzzing lab

2. Network lab

3. Botnets and malwares lab

4. Shellcoding lab

5. ChipWhisperer lab

## The Course

The course has seven (7) lectures, seven (7) weekly lecture questionnaires, five (5) laboratory exercises and final coursework (no exam).

Lectures are handling topics from high perspective and they are not going technically deep. Lecture questionnaires are based on lectures (surprisingly!).

Laboratory exercises are thought as individual packages: containing theory and exercises, and going technologically very deep.

To pass the course, you have to get enough points *totally* from exercises/questionnaires and final coursework. From the beginning, you should be able to see, what you have to do for earning some specific grade. 

**This means: as long as you get enough points from somewhere, you can skip even final coursework. Grading table is presented [here.](#grading)**

*Generally, every week there is a choice: Make lecture questionnaires sufficiently and you will get grade 1 from that week **OR** participate for lab and complete tasks as described to get grade 2 or more from that week. You can't get points from both lecture questionnaires and labs in the same week.*

Grades from the labs are equal to amount of points they are offering.

Everyone can make weekly questionnaires from lectures in last two weeks, and earn total of two (2) points, even if all of the five labs has been completed.

In practise, exercises of the course have been divided to five (5) different levels. Level is indicating for grade/points you are able to achieve by reaching that level.

When level rises, so does workload/difficulty.

Labs have been split to different tasks. **The amount of tasks which are required for each level/grade is defined in the grading section of corresponding lab.**

* __Level 1:__ You don't have to participate in the lab. You earn grade 1 from that week by attending lectures and answering to lecture questionnaires of corresponding topic
* __Level 2:__ Complete the bare minimum of the lab. This will earn you grade **2** from that week. You are expected to do this during lab hours.
* __Level 3:__ Complete the whole lab without extra work. This will earn you grade **3** from this week. You are expexted to do this during the lab hours but you are allowed to finish it on your own time
* __Level 4:__ Complete the above (excluding lecture questionnaires) and some extra work. This will earn you a grade of **4** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return it before deadline.
* __Level 5:__ Complete all the above (excluding lecture questionnaires) and the most challenging extra work. You will earn a grade of **5** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return it before deadline.

## Grading

As described earlier, you can get up to 5 points in each week during the first five weeks. (Total 25 points)

For last two weeks, there is still possibility earn total of 2  points from weekly lecture questionnaires (one (1) each), even if you have completed five labs already.

From final coursework, points can be obtained as following. Grade from 1 to 5 is multiplied with three (3):

Topic|Grade/Points*
-|-
Academic survey (essay)|1 - 3 (3 - 9)
Small own project or project from given topics| 2 - 4 (6 - 12)
Challenging own project | 3 - 5 (9 - 15)

*This table might still change. TBA final coursework topics


*As result, we get following table for total grade:*

Total Points|Total Grade
:-:|:-:
<10 | failed
10+ | 1
15+ | 2
21+ | 3
28+ | 4
35+ | 5

42 points are maximun.

## Final coursework topics

Note, that all topics are not equal in maximum points they are offering.

* Academic survey (cybersecurity essay/literature review)
* Trivial own project or predefined task
* Advanced non-trivial own project

*Predefined topics to be announced later...*

In each lab, there is option to make grade 5 task to be more challenging and comprehensive, and make it as final coursework. This has to be approved by assistant.

*Deadline for final course work is in the end of week 42. (End of course week 7.)*

## Deadlines

For each week you are expected to return assignments of corresponding lab OR corresponding lecture assignment.

Week | Course week|Lecture Topics|Laboratory| Assigment Deadline|
:-:|:-:|:-:|:-:|:--:
36 | 1 | Introductory lecture, Computer Security in general, software and fuzz testing| Fuzzing | Wednesday, 12.09.2018, at 23:59|
37 | 2 | Network security, risk | Network and websecurity | Wednesday, 19.09.2018, at 23:59
38 | 3 | Cybercrime, botnets, malware  | Botnets and malwares | Wednesday, 26.09.2018, at 23:59
39 | 4 | Software vulnerabilities and exploits | Shellcoding | Wednesday, 03.10.2018, at 23:59
40 | 5 | Hardware security | HW and side channels / Possibility to improve or make missing labs | -
41 | 6 | IoT, product security | HW and side channels / Possibility to improve or make missing labs |Wednesday, 17.10.2018, at 23:59
42 | 7 | Privacy, GDPR, future challenges | Demo of course projects |  **Sunday, 21.10.2018, at 23:59 

***This is deadline of final coursework as well.*

***NOTE:***  Week 5 and 6 have been mixed, because there are limited amount of devices which are required for ChipWhisperer lab.

## Instructions

 * Enroll to the course

 * Find course's Moodle page from University's [Moodle](https://oystack.oulu.fi/course/index.php?categoryid=16)
 
 * Find a link whereof you can receive and create a private repository containing all the return folders.

 * Create GitHub account, if you don't have one already, and create this private repository from the link.

 * You can see deadlines above. They are same in Moodle. There might be exceptions for ChipWhisperer.

 * Complete as many tasks as you wish and update your repository accordingly. Check the grading table found in each labs instructions on what you have to complete in order to earn the grade of your choosing

 * Push your changes to your repository before deadline.

 * Return a document to Moodle's return box with following content:
   * Your name(s) (There is group work in ChipWhisperer lab)
   * Link to your private GitHub repository
   * *Remember to do this for each lab, if you want to get things reviewed!*
   * Additionally for Week 6/Lab6, if you are returning some improvements for previous labs, mention what have you improved or done.




Check [cheat sheet](https://services.github.com/on-demand/downloads/github-git-cheat-sheet.pdf) if you need a refresher on how to use Git. Some basic commands below  
```git
git add </path/filename>
git commit -m "<message>"
git push
```

## Virtual machines

Each lab utilizes one of the virtual machines below:

* Kali Linux - for shellcoding, fuzzing and web security lab
  * User: compsec
  * Password: course
* Ubuntu 16.04 - for botnets and malware analysis
  * User: compsec 
  * Password: course
* Lubuntu 17.04- side-channel attacks with ChipWhisperer
  * User: cwuser
  * Password. cwpassword

These virtual machines are located on network drive.

 Machines can be run directly from there, *but all changes on virtual machines are lost, after shutting them down.*

### **Method 1: copy machine, and run locally**

If you have enough space on your lab computer, and you are not too hesitated to start, recommended way is to copy virtual machine from network drive, and then start it locally. This way changes are not lost in shutdown.

You can mount network drive with following cmd command:

```
net use z: "\\kaappi\Virtuaalikoneet$"
```

There should be now new Z: drive, named as Virtuaalikoneet$

And virtual machines are located in:

Virtuaalikoneet$ -> VMware -> CompSec

Copy selected virtual machine to C:\Temp folder.

Run machine from .vmx file, which ***does not*** say 'copy and run'.

When the virtual machine asks if you have copied or moved the machine, press __"I copied it"__.

### **Method 2: run machine directly from network drive**

This is the fastest way to start working: you don't need to wait copy-process.

If you don't mind that changes are lost on shutdown, machines can be run directly from network drive.

 To run virtual machines from there, you have to use following commands. Open Windows cmd, and run them in there:

### For Kali Linux:
```shell
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$")) && (if exist "C:\Temp\Kali" (rd /s /q "C:\Temp\Kali" && mkdir "C:\Temp\Kali") else (mkdir "C:\Temp\Kali")) && copy "Z:\VMware\CompSec\Kalix64\Kali_copy_and_run_me.vmx" "C:\Temp\Kali\Kali_copy_and_run_me.vmx" && start "" "C:\Temp\Kali\Kali_copy_and_run_me.vmx"
```
### For Ubuntu 16.04: 

```shell
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$")) && (if exist "C:\Temp\Ubuntux64" (rd /s /q "C:\Temp\Ubuntux64" && mkdir "C:\Temp\Ubuntux64") else (mkdir "C:\Temp\Ubuntux64")) && copy "Z:\VMware\CompSec\Ubuntu 64-bit\Ubuntu64_copy_and_run.vmx" "C:\Temp\Ubuntux64\Ubuntu64_copy_and_run.vmx" && start "" "C:\Temp\Ubuntux64\Ubuntu64_copy_and_run.vmx"
```
### For Lubuntu 17.04:
```shell
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$")) && (if exist "C:\Temp\LUbuntu64" (rd /s /q "C:\Temp\LUbuntu64" && mkdir "C:\Temp\LUbuntu64") else (mkdir "C:\Temp\LUbuntu64")) && copy "Z:\VMware\CompSec\ChipWhisperer\LUbuntu64-bit_copy_and_run.vmx" "C:\Temp\LUbuntu64\LUbuntu64_copy_and_run.vmx" && start "" "C:\Temp\LUbuntu64\LUbuntu64_copy_and_run.vmx"
```

When the virtual machine asks if you have copied or moved the machine, press __"I copied it"__.

## Contribution

Do you have a lot of ideas or suggestions to improve course?
Fork repository, and make a pull request. Let's have a look!

This might have positive effect for your grade as well.

## License

Any information, guidelines, tutorials, examples or code pieces here are for teaching purposes, under MIT license, unless otherwise declared.

This repository contains tutorials and examples for how to use some spefic tools

* The licence of corresponding tool should be applied for the usage of tool

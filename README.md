# 521155S Computer Security

<p align="right">
<img src="lib/images/ouspglogo4.png" alt="University of Oulu" height="100px" align="right"/>
</p>

Exercises for computer security course in the University of Oulu.

The course covers the essential aspects of computer security and computer security research in theory and through practical examples.

The course is intended for computer engineering masters students and additionally to any student interested in computer security that has *the sufficient* technical background to complete the course exercises.

The lectures and place for returning assignments can be found from University Moodle: [https://moodle.oulu.fi](https://moodle.oulu.fi)

Course is under Faculty of Information Technology and Electrical Engineering.

The course is organized by Oulu University Secure Programming Group (OUSPG)

<p align="center">
<img src="lib/images/oulun yliopisto_logo_eng_black_rgb.png" alt="University of Oulu" height="300px" align="right"/>
</p>



## Contents

* [The Course](#The-Course)

* [Instructions](#Instructions)

* [Grading](#Grading)

* [Final coursework topics](#Final-coursework-topics)

* [Virtual machines (Lab environment)](#Virtual-machines)

* [Contribution](#Contribution)

* [License](#License)


## The Course

<details open><summary>Details</summary>

  

The course has seven (7) lectures, seven (7) weekly lecture questionnaires, six (6) laboratory exercises and final coursework (no exam).

Lectures are handling topics from high perspective and they are not going technically deep. Lecture questionnaires are based on the topic of the lectures (surprisingly!).

Laboratory exercises are thought as individual packages: containing theory and exercises, and going technologically very deep.

Lab materials are located in their corresponding folders: 

1. [Fuzzing lab](Lab1_Fuzzing)

2. [Network lab](Lab2_Network)

3. [Botnets and malwares lab](Lab3_Botnets_and_malwares)

4. [Shellcoding lab](Lab4_Introduction_to_Shellcoding)

5. [ChipWhisperer lab](Lab5_ChipWhisperer)

6. [Digital forensics lab](Lab6_Digital_Forensics)

See section about [virtual machines](#Virtual-machines) to setup laboratory environment in the University classes or at home.

Final coursework topics can be seen in [here.](#Final-coursework-topics)

To pass the course, you have to get enough points *totally* from exercises/questionnaires and final coursework. From the beginning, you should be able to see, what you have to do for earning some specific grade. 

**This means: as long as you get enough points from somewhere to pass the course, you can skip any lab/lecture task and even final coursework. All tasks on this course are optional, but the amount of points will determine your grade. Grading section is presented [here.](#grading)**

*Generally, every week there is a decision to be made how many steps you want to take: Make lecture questionnaires sufficiently and you will get grade 1 from that week or participate for lab and complete tasks as described to get grade 2 or higher from that week.* You *cannot* get points from lecture questionnaires and laboratory exercises both, but if there be case when your lab work is not enough for grade 1, and questionnaire might help with that.

Grades from the labs are equal to amount of points they are offering.

In practice, exercises of the course have been divided to five (5) different levels. Level is indicating for grade/points you are able to achieve by reaching that level.

When level rises, so does workload/difficulty.

Labs have been split to different tasks. **The amount of tasks which are required for each level/grade is defined in the grading section of corresponding lab.**

* __Level 1:__ You earn grade 1 from that week by attending lectures and answering to lecture questionnaires of corresponding topic
* __Level 2:__ Complete the bare minimum of the lab. This will earn you grade **2** from that week.
* __Level 3:__ Complete above (excluding lecture task) and the whole lab without extra work. This will earn you grade **3** from this week.
* __Level 4:__ Complete the above (excluding lecture task) and some extra work. This will earn you a grade of **4** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return it before deadline.
* __Level 5:__ Complete all the above (excluding lecture task) and the most challenging extra work. You will earn a grade of **5** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return it before deadline.

See [deadlines](#deadlines) section for more information about how much you have time to work with lab depending on level you want to reach.

</details>

## Instructions

<details open><summary>Details</summary>

  

 * Enroll to the course

 * Find course's Moodle page from University's [Moodle](https://moodle.oulu.fi/course/search.php?search=computer+security)
 
 * Find a link whereof you can receive and create a private repository containing all the return template folders. You are expected to answer for given templates and store your actual work in this repository. 

 * Create GitHub account, if you don't have one already, and create this private repository from the link.

 * You can see deadlines below. They are same in the Moodle. There might be exceptions for ChipWhisperer.

 * Complete as many tasks as you wish and update your repository accordingly. Check the grading table found in each labs instructions on what you have to complete in order to earn the grade of your choosing

 * Push your changes to your repository before deadline.

 * Return a document to Moodle's return box with following content:
   * Your name(s)
   * Link to your private GitHub repository
   * *Remember to do this for each lab, if you want to get things reviewed!*

Check [cheat sheet](https://github.github.com/training-kit/downloads/github-git-cheat-sheet.pdf) if you need a refresher on how to use Git. Some basic commands below  
```git
git add </path/filename>
git commit -m "<message>"
git push
```

</details>


## Grading

<details><summary>Details (Click to collapse!)</summary>

  

As described earlier, you can get up to 5 points in each week during the first six weeks. (Total 30 points)

For last week (week 7), there is still possibility earn 1 point from weekly lecture questionnaire (there is no lab on week 7).

From final coursework, points can be obtained as following.

There are four (4) different tiers for final coursework.

Tier|Topic|Grade/Points
-|-|-
1 | BE AWARE - Personal risk analysis (non-technical)|1 (2 - 4)
2 | FIND OUT - Survey paper (non-technical)|  2 - 3 (5 - 10)
3 | IMPLEMENT - Simple technical project report | 2 - 4 (5 - 13)
4 | CONTRIBUTE - Advanced project report | 3 - 5 (8 - 15)


Total Points|Total Grade
:-:|:-:
<9 | failed
9+ | 1
14+ | 2
20+ | 3
27+ | 4
35+ | 5

46 points are maximum.

### Imaginary grading examples

**Alice** is student with very basic technical skills and limited time due to many other courses demanding her attention. She manages to do easiest laboratory task at weeks 1,2 and 3. On fourth week she is too busy to do anything for this course, but on week 5 she manages to do easiest lab task again. On week 6 and 7 she decides to do only lecture tasks and then concentrates on writing survey paper as her coursework, because lack of available time. Hers coursework passes the minimum requirements, resulting 5 points and her other accomplishments give her (2+2+2+0+2+1+1) 10 points, so she receives final grade of 2 from this course.

**Bob** is student with some technical experience and some background knowledge of computer security issues. He manages to grab 3 points from first 3 weeks by doing basic level of laboratory tasks. On weeks 4 and 5 he steps up and does labs with some extra tasks, resulting 4 points from each lab. On week 6 he does easiest level of lab. On week 7 he does not do weekly assignments at all and concentrates on doing his technical coursework which he intends to do properly. Technical coursework turns to be nice one, resulting 10 points, and with other points (3+3+3+4+4+2+0=19) he receives grade 4 from this course.

</details>


## Final coursework topics

<details><summary>Details (Click to collapse!)</summary>

  

Note, that all topics are not equal in maximum points they are offering. More information can be found in Final Project lecture slides.

1.  BE AWARE - Personal risk analysis (non-technical)
    * Write a personal risk analysis according to template

2. FIND OUT - Survey paper (non-technical)
    * Write a scientific survey article on a security topic for points up to good level. No technical implementation needed.

3. IMPLEMENT - Simple technical project report
    * Using one of the provided topics, perform a short technical project and write an associated report for points from satisfactory to laudable.
    * The expected level is: repeat and demonstrate something known.
4. CONTRIBUTE - Advanced project report
    * Choosing your own topic, and perform a technical project and write  a report
    * The guideline for choosing topics is: the topic should have the potential of having a positive contribution to security. 

In some labs, there might be possibility to extend grade 5 task to be more challenging and comprehensive, and then return it as your coursework. Send message to course assistant about your idea and lets have a look at it before you start your work.

*Deadline for final course work is in the end of week 43. (End of course week 8.)*

</details>

## Deadlines

<details><summary>Details (Click to collapse!)</summary>

  

For each week you are expected to return assignments of corresponding week before specified deadline.

If you reach at least 3 points/level by that deadline, you may submit your work to return box and ask for extra time to do more difficult tasks if you think that given time is not enough for more challenging tasks. 

In that case your work is attempted to be graded ASAP on Tuesday and if it is sufficient you will be given short feedback and extended deadline (same week Thursday 12:00, before new laboratory exercise). Note, that this offers possibility for improvements as well!

Week | Course week|Lecture Topics|Laboratory|Deadline
:-:|:-:|:-:|:-:|:--:
36 | 1 | Introductory lecture, Computer Security in general, software and fuzz testing| Fuzzing |Monday, 09.09.2019, at 23:55
37 | 2 | Network security, risk | Network and websecurity |Monday, 16.09.2019, at 23:55
38 | 3 | Cybercrime, botnets, malware  | Botnets and malwares |Monday, 23.09.2019, at 23:55
39 | 4 | Software vulnerabilities and exploits | Shellcoding |Monday, 30.09.2019, at 23:55
40 | 5 | Hardware security | HW and side channels |Monday, 07.10.2019, at 23:55
41 | 6 | Production security, IoT security | Digital forensics|Monday, 14.10.2019, at 23:55
42 | 7 | Privacy, GDPR, future challenges | Demo of course projects |Monday, 21.10.2019, at 23:55
43 | 8 | No lecture | No lab |Coursework deadline Sunday, 27.10.2019, at 23:55



</details>


## Virtual machines

<details><summary>Details (Click to collapse!)</summary>

  

Note: If you are using following virtual machines in your own pc, they are preconfigured with 4GB of RAM for VMware player. So if you have less than 8 GB of RAM in your pc, you might want to reduce this preconfigured RAM. 

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

### **Copy machine and run locally**

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

### **Run machine directly from network drive**

This is the fastest way to start working: you don't need to wait copy-process.

If you don't mind that changes are lost on shutdown, machines can be run directly from network drive.

 To run virtual machines from there, you have to use following commands. Open Windows cmd, and run them in there:

### For Kali Linux:
```shell
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$"))^
 && (if exist "C:\Temp\Kali" (rd /s /q "C:\Temp\Kali"^
 && mkdir "C:\Temp\Kali") else (mkdir "C:\Temp\Kali"))^
 && copy "Z:\VMware\CompSec\Kalix64_2019\Kali_copy_and_run_me.vmx" "C:\Temp\Kali\Kali_copy_and_run_me.vmx"^
 && start "" "C:\Temp\Kali\Kali_copy_and_run_me.vmx"
```
### For Ubuntu 16.04: 

```shell
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$"))^
 && (if exist "C:\Temp\Ubuntux64" (rd /s /q "C:\Temp\Ubuntux64"^
 && mkdir "C:\Temp\Ubuntux64") else (mkdir "C:\Temp\Ubuntux64"))^
 && copy "Z:\VMware\CompSec\Ubuntu16.04_64-bit\Ubuntu64_copy_and_run.vmx" "C:\Temp\Ubuntux64\Ubuntu64_copy_and_run.vmx"^
 && start "" "C:\Temp\Ubuntux64\Ubuntu64_copy_and_run.vmx"
```

### For Lubuntu 17.04:
```shell
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$"))^
 && (if exist "C:\Temp\LUbuntu64" (rd /s /q "C:\Temp\LUbuntu64"^
 && mkdir "C:\Temp\LUbuntu64") else (mkdir "C:\Temp\LUbuntu64"))^
 && copy "Z:\VMware\CompSec\ChipWhisperer\LUbuntu64-bit_copy_and_run.vmx" "C:\Temp\LUbuntu64\LUbuntu64_copy_and_run.vmx"^
 && start "" "C:\Temp\LUbuntu64\LUbuntu64_copy_and_run.vmx"
```

When the virtual machine asks if you have copied or moved the machine, press __"I copied it"__.

## Getting virtual machines over Eduroam (University WLAN)

You can mount network drive into your own PC, if it has been connected to [Eduroam ](http://www.oulu.fi/ict/eduroam).

After you have successfully connected to network, you can mount network drive as following. If any credentials are asked, username is username@student.oulu.fi

### Windows
Open Windows cmd:

```shell
net use z: "\\kaappi\Virtuaalikoneet$"
```
Drive should be mounted after giving correct credentials.

### Linux (Debian - based)
If you have mnt folder in root directory, and package *cifs-utils* is installed, you can:

```shell
sudo mount -t cifs //kaappi/Virtuaalikoneet$ /mnt/ -o user=username@student.oulu.fi
```
Depending on your versions, you might need to play with 'sec' -variable, for example Ubuntu 16.04 might require:
```shell
sudo mount -t cifs //kaappi/Virtuaalikoneet$ /mnt/ -o user=username@student.oulu.fi,sec=ntlm
```
Passwords should be prompted.

Virtual machines are located in:

Virtuaalikoneet$ -> VMware -> CompSec

## Getting virtual machines remotely


If you are not able to get in to University to copy virtual machines from network drive by using Lab computer, you can do it remotely as well.
This requires setting up *VPN - connection* to University network.
This can be acquired by following guidelines presented [here.](http://www.oulu.fi/ict/vpn)

Looks like two factor authentication(Authentication via SMS) is not enabled by default. You have to enable it by following instructions here: [http://www.oulu.fi/ict/authentication#vpn](http://www.oulu.fi/ict/authentication#vpn)

**Shortly:**
 * Download suitable VPN client here: [https://www.oulu.fi/jakelu/vpn/](https://www.oulu.fi/jakelu/vpn/)
 * Login with student credentials is required
 * Once you have installed the correct client, start it
 * Use *sa.oulu.fi* as server URL.
 * Connect by using your student username and selecting Student (SMS) authentication method. You have to use strong authentication (Student (SMS)) to be able to mount the drive.

After you have successfully connected to network, instructions are same as [here.](#getting-virtual-machines-over-eduroam-university-wlan)

</details>

## Contribution

Do you have a lot of ideas or suggestions to improve course?
Fork repository, and make a pull request. Let's have a look!

This might have positive effect for your grade as well.

Current contributors for the course (order by last name):

  * Aku Haataja (as course assistant)
  * Lauri Haverinen (as course assistant)
  * Ville Kemppainen (as course assistant)
  * Jukka Pajukangas (as course assistant)
  * Niklas Saari (as course assistant)

## License

Any information, guidelines, tutorials, examples or code pieces here are for teaching purposes, under MIT license, unless otherwise declared.

This repository contains tutorials and examples for how to use some specific tools

* The licence of corresponding tool should be applied for the usage of tool

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

  

The course has seven (7) lectures, six (6) laboratory exercises and Moodle exam. Course does not contain final coursework this year because separate course considering it is planned.

Lectures are handling topics from high perspective and they are not going technically deep. Moodle exam is based on the lectures.

Laboratory exercises are thought as independent packages: containing theory and exercises, and going technologically very deep.

Lab materials are located in their corresponding folders: 

1. [Fuzzing lab](Lab1_Fuzzing)

2. [Network lab](Lab2_Network)

3. [Botnets and malwares lab](Lab3_Botnets_and_malwares)

4. [Shellcoding lab](Lab4_Introduction_to_Shellcoding)

5. [ChipWhisperer lab](Lab5_ChipWhisperer)

6. [Digital forensics lab](Lab6_Digital_Forensics)

See section about [virtual machines](#Virtual-machines) to setup laboratory environment in the University classes or at home.

To pass this course with grade 1, you have to pass the Moodle exam.

To get better grade, you have to do some laboratory exercises.
You can somewhat decide what grade you will earn on this course because you can (hopefully!) see from the beginning how much work is required to each grade.
All laboratory tasks are optional and total points from those will determine your grade. Grading section is presented [here.](#grading)

Labs are divided to levels (which is corresponding grade/points on that lab), level may contain one or several tasks.
**The amount of tasks which are required for each level/grade is defined in the grading section of corresponding lab.**
Tasks are designed to become somewhat harder and time-consuming on each level.
Getting 2-3 points from each lab doable for average student with reasonable amount of work, 4-5 points require lot more time and skill.

See [deadlines](#deadlines) section for information about deadlines of lab works.

</details>

## Instructions

<details open><summary>Details</summary>

 * Enroll to the course

 * Find course's Moodle page from University's [Moodle](https://moodle.oulu.fi/course/search.php?search=computer+security)
 
 * Find a link whereof you can receive and create a private repository containing all the return template folders. You are expected to answer for given templates and store your actual work in this repository. 

 * Create GitHub account, if you don't have one already, and create this private repository from the link.

 * You can see deadlines below. They are same in the Moodle. There might be exceptions for ChipWhisperer.

 * Complete as many tasks as you wish and update your repository accordingly. Check the grading table found in each labs instructions on what you have to complete in order to earn the grade of your choosing

 * Push your changes to your repository before deadline, and return link to your repository to corresponding return box of the lab in Moodle.


Check [cheat sheet](https://github.github.com/training-kit/downloads/github-git-cheat-sheet.pdf) if you need a refresher on how to use Git. Some basic commands below  
```git
git add </path/filename>
git commit -m "<message>"
git push
```

</details>


## Grading

<details><summary>Details (Click to collapse!)</summary>

  
As described earlier, you have to pass Moodle exams to pass the course. You can have higher grade by doing labworks.

You can get up to 5 points in each lab (Total 30 points). Grade is determined based on those points next.

Total Points|Total Grade
:-:|:-:
9+ | 2
15+ | 3
21+ | 4
27+ | 5

</details>

## Moodle exam (WIP)

## Deadlines

<details><summary>Details (Click to collapse!)</summary>

  

Each week has deadline for corresponding lab exercise.

Week | Course week|Lecture Topics|Laboratory|Deadline
:-:|:-:|:-:|:-:|:--:
36 | 1 | Introductory lecture, Computer Security in general, software and fuzz testing| Fuzzing | WIP .09.2020, at 23:55
37 | 2 | Network security, risk | Network and websecurity |WIP .09.2020, at 23:55
38 | 3 | Cybercrime, botnets, malware  | Botnets and malwares |WIP .09.2020, at 23:55
39 | 4 | Software vulnerabilities and exploits | Shellcoding |WIP .09.2020, at 23:55
40 | 5 | Hardware security | HW and side channels |WIP .09.2020, at 23:55
41 | 6 | Production security, IoT security | Digital forensics|WIP .09.2020, at 23:55
42 | 7 | Privacy, GDPR, future challenges | - |



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

#### Running the Virtual machines under QEMU
If you are using QEMU/KVM, you cannot directly load the .vmdk file to run the virtual machines as-is due to lack of support for split .vmdk files.

In order to combine the .vmdk disk parts into a format QEMU can load you need to convert them into a .qcow2 disk file using qemu-img: 
```shell
qemu-img convert Kali.vmdk Kali.qcow2
```

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

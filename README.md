# 521155S Computer Security

Exercises for computer security course in the University of Oulu

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




## Current state/ TODO

  
- [ ] Lab1 Level 5 task missing for now. Return template missing
- [x] Lab2 Tasks done. Return template done. Might need typo fixes and minor wording tweaks  
- [x] Lab3 Tasks finished. Finish the before the lab chapter.
- [x] Lab4 Should be finished
- [x] Lab5 Tasks done. Return box done. Might need typo fixes and minor wording tweaks

## The Course

The contents of the course have been divided to five (5) different levels. Level is indicating for grade/points you are able to achieve by reaching that level.

When level rises, so does workload/difficulty.

To pass the course, you have to get enough points from exercises and final course work. From the beginning, you should be able to see, what you have to do for earning some specific grade.

*Generally, every week there is a choice: Make lecture tasks/diary sufficiently and you will get grade 1 **OR** participate for lab and complete tasks as described to get grade 2 or more.*

Labs have been split to different tasks. **The amount of tasks which are required for each level/grade is defined in the grading section of corresponding lab.**

* __Level 1:__ You don't have to participate in the lab. You earn grade 1 from that week by attending lectures and filling a lecture diary/tasks of corresponding topic
* __Level 2:__ Complete the bare minimum of the lab. This will earn you grade **2** from that week. You are expected to do this during lab hours.
* __Level 3:__ Complete the whole lab without extra work. This will earn you grade **3** from this week. You are expexted to do this during the lab hours but you are allowed to finish it on your own time
* __Level 4:__ Complete the above and some extra work. This will earn you a grade of **4** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return it before deadline.
* __Level 5:__ Complete all the above and the most challenging extra work. You will earn a grade of **5** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return it before deadline.

## Deadlines

For each week you are expected to return assignments of corresponding lab OR corresponding lecture tasks.

Section|Deadline|Topic/Lab
:-:|:-:|:-:
Week 1 | Wednesday, 12.09.2018, at 23:59| Fuzzing
Week 2 | Wednesday, 19.09.2018, at 23:59 | Network and websecurity
Week 3 | Wednesday, 26.09.2018, at 23:59 | Botnets and malwares
Week 4 | Wednesday, 03.10.2018, at 23:59 | Shellcoding
Week 5 | Wednesday, 10.10.2018, at 23:59 | Side-channel attacks with ChipWhisperer
Week 6 | Wednesday, 17.10.2018, at 23:59 | Possibility to improve or make missing labs
Week 7 | - | Ask guidance for final coursework

***NOTE:***  Week 5 and 6 might be mixed, depending on the amount of participants in the lab. There are limited amount of devices which are required for ChipWhisperer lab.

## Instructions

 * Enroll to the course

 * Find course's Moodle page from University's [Moodle](https://oystack.oulu.fi/)
 
 * Find a link whereof you can receive and create a private repository containing all the return folders.

 * Create GitHub account, if you don't have one already, and create this private repository from the link.

 * You can see deadlines above. They are same in Moodle. There might be exception for ChipWhiperer, depending on if everyone is able to get device in Week 5.

 * Complete as many tasks as you wish and update your repository accordingly. Check the grading table found in each labs instructions on what you have to complete in order to earn the grade of your choosing

 * Push your changes to your repository before deadline.

 * Return a document to Moodle's return box with following content:
   * Your name
   * Link to your private GitHub repository
   * *Remember to do this for each lab, if you want to get things reviewed!*
   * Additionally for Week 6/Lab6, if you are returning something, mention what have you improved or done.




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

These virtual machines are located on network drive:

 Machines can be run directly from there, *but all changes on virtual machines are lost, after shutting them down.*

### **Method 1: copy machine, and run locally**

If you have enough space on your lab computer, and you are not too hesitated to start, recommended way is to copy virtual machine from network drive, and then start it locally.

You can mount network drive with following cmd command:

```
net use z: "\\kaappi\Virtuaalikoneet$"
```

There should be now new Z: drive, named as Virtuaalikoneet$

And virtual machines are located in:

Virtuaalikoneet$ -> VMware -> CompSec

Copy selected virtual machine to C:\Temp folder

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
(if exist "Z:" (echo "Drive already mounted") else (net use z: "\\kaappi\Virtuaalikoneet$")) && (if exist "C:\Temp\LUbuntu64" (rd /s /q "C:\Temp\LUbuntu64" && mkdir "C:\Temp\LUbuntu64") else (mkdir "C:\Temp\LUbuntu64")) && copy "Z:\VMware\CompSec\ChipWhisperer\LUbuntu64-bit_copy_and_run.vmx" "C:\Temp\Ubuntux64\LUbuntu64_copy_and_run.vmx" && start "" "C:\Temp\Ubuntux64\LUbuntu64_copy_and_run.vmx"
```



## Contribution

Do you have a lot of ideas or suggestions to improve course?
Fork repository, and make a pull request. Let's have a look!

This might have positive effect for your grade as well.

## License

Any information, guidelines, tutorials, examples or code pieces here are for teaching purposes, under MIT license, unless otherwise declared.

This repository contains tutorials and examples for how to use some spefic tools

* The licence of corresponding tool should be applied for the usage of tool

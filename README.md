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

- [x] Lab1 Tasks finished. Reread and fix typos. Add a chapter about how to do the returns?   
- [ ] Lab2 Level 5 task missing for now
- [x] Lab3 Tasks finished. Finish the before the lab chapter.   
- [x] Lab4 Should be finished
- [x] Lab5 Should be finished.

## Labs

Labs have been split to 4 tasks. Each task corresponds to the grade you will earn by completing that level

* __Task 0:__ You don't have to participate in the lab. You earn grade 1 from that week by attending lectures and filling a lecture diary/tasks of corresponding topic
* __Task 1:__ Complete the bare minimum of the lab. This will earn you grade **2** from that week. You are expected to do this during lab hours.
* __Task 2:__ Complete the whole lab without extra work. This will earn you grade **3** from this week. You are expexted to do this during the lab hours but you are allowed to finish it on your own time
* __Task 3:__ Complete the above and some extra work. Will earn you a grafe of **4** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return them to the assistants before the deadline
* __Task 4:__ Complete all the above and the most challenging extra work. Yuo will earn a grade of **5** from that week. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time and return them to the assistants before the deadline

## Deadlines

Each week you are expected to return assingments for corresponding lab OR for corresponding lecture tasks.

Section|Deadline|Topic/Lab
:-:|:-:|:-:
Week 1 | Wednesday, 12.09.2018, at 23:59| Fuzzing
Week 2 | Wednesday, 19.09.2018, at 23:59 | Network and websecurity
Week 3 | Wednesday, 26.09.2018, at 23:59 | Botnets and malwares
Week 4 | Wednesday, 03.10.2018, at 23:59 | Shellcoding
Week 5 | Wednesday, 10.10.2018, at 23:59 | Side-channel attacks with ChipWhisperer
Week 6 | Wednesday, 17.10.2018, at 23:59 | Possibility to improve or make missing labs
Week 7 | - | Ask guidance for final coursework

Check [Moodle](https://oystack.oulu.fi/) for a link from which you can receive a private repository containing your return folders. __Remember to leave a document to the Moodle return box containing you name and link to your repository__. We need that to track who owns which repository and to check that you are active in the course. 

Your work will not be graded if you don't submit this document __each week__.

Deadlines are in Moodle as well. If for some reason Moodle box is available longer than presented here, that is correct deadline.

## Instructions

* Enroll to the course
* Find course's Moodle page from University's [Moodle](https://oystack.oulu.fi/) 
* Find a link from which you can receive and create a private repository containing all the return folders.
* Check Moodle for lab deadlines
* Complete as many tasks as you wish and update your repository accordingly. Check the grading table found in each labs instructions on what you have to complete in order to earn the grade of your choosing
* Push your changes to your repository before deadline
* Return a document to Moodle's return box containing:
  * Your name 
  * Link to your private GitHub repository

Check [cheat sheet](https://services.github.com/on-demand/downloads/github-git-cheat-sheet.pdf) if you need a refresher on how to use Git. Some basic commands below  
```git
git add </path/filename>
git commit -m "<message>"
git push
```

## Virtual machines

Each lab utilizes one or more virtual machines. These machines can be found from the University drive.

Following virtual machines will be used:

* Kali Linux - for shellcoding, fuzzing and web security lab
  * User: compsec
  * Password: course
* Ubuntu 16.04 - for botnets and malware analysis
  * User: compsec 
  * Password: course
* Lubuntu 16.04- side-channel attacks with ChipWhisperer
  * User: cwuser
  * Password. cwpassword

Path to virtual machines:

Yleiset -> Mikroluokat -> CompSec


## Contribution

Do you have a lot of ideas or suggestions to improve course?
Fork repository, and make a pull request. Let's have a look!

This might have positive effect for your grade as well.

## License

Any information, guidelines, tutorials, examples or code pieces here are for teaching purposes, under MIT license, unless otherwise declared.

This repository contains tutorials and examples for how to use some spefic tools

* The licence of corresponding tool should be applied for the usage of tool
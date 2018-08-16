# 521155S Computer Security

Exercises for computer security course in the University of Oulu

The course covers the essential aspects of computer security and computer security research in theory and through practical examples.

The course is intended for computer engineering masters students and additionally to any student interested in computer security that has *the sufficient* technical background to complete the course exercises.

<p align="center">
<img src="lib/images/oulun yliopisto_logo_eng_black_rgb.png" alt="University of Oulu" height="300px" align="right"/>
</p>

## Contents

This repository is split to following contents:

1. Exercise/Lab folders
    * Each lab has its own folder which contains instructions on how to complete that specific lab.
2. Return templates
    * Contains material you need to return in order to pass the lab
    * In future, return templates could be in own repository wheres the instructions repository is submodule of it
    * Idea: use GitHub classroom to generate own repository for each student, and they can return their individual work this way

## Current state/ TODO

- [x] Lab1 Tasks finished. Reread and fix typos. Add a chapter about how to do the returns?   
- [ ] Lab2 Level 5 task missing for now
- [x] Lab3 Tasks finished. Finish the before the lab chapter.   
- [x] Lab4 Should be finished
- [x] Lab5 Should be finished.

## Labs

Labs have been split to 5 levels. Each level corresponds to the grade you will earn by completing that level

* Level 1: For level one you don't have to participate in the lab. You earn this by attending lectures and filling a lecture diary/tasks of corresponding topic
* Level 2: Complete the bare minimum of the lab. You are expected to do this during lab hours
* Level 3: Complete the whole lab without extra work. You are expexted to do this during the lab hours but you are allowed to finish it on your own time
* Level 4: Complete the above and some extra work. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time, and return them to the assistants before the deadline
* Level 5: Complete all the above and the most challenging extra work. It is likely that you don't have time to complete this during lab hours so you are expected to do this extra work on your own time and return them to the assistants before the deadline

## Returns

Return_Instructions folder contains a folder for each lab. In every folder is also a return template that you are expected to fill. __Only the contents of this folder will be graded. Put everything you want to return here__. Some labs are constructed so that the task descriptions also contain the anwer fields. If you want to you can put your answers to these fields and then copy the whole document to the return folder. In these cases remember to add your name to the document.

 You are allowed and in some cases expected to add new files and folders to the lab return folder. If you return programs have a clear explanation on how to run it preferably in the return template.

## Instructions

* You are given a link by the course assistant that will give you a private repository containing all this.
* Check this weeks task from LabX_YXZ folder.
* Return what you are expected to the Return_instructions/LabXTemplate folder
* Push your changes to your repo before deadline
* Return a document containing your github repos link to moodle.

Check [cheat sheet](https://services.github.com/on-demand/downloads/github-git-cheat-sheet.pdf) if you need a refresher on how to use git. Some basic commands below  
```git
git add <location>
git commit -m "<message>"
git push
```

## Virtual machines

Each lab utilizes one or more virtual machines. These machines can be found from the University drive.

At least following operating systems will be used:

* Kali Linux - for shellcoding, fuzzing and web security lab
  * User: compsec
  * Password: course
* Ubuntu 16.04 - for botnets and malware analysis
  * User: compsec 
  * Password: course
* Lubuntu 16.04- side-channel attacks with ChipWhisperer

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
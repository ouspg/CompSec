Computer Security Lab 6: Digital Forensics
====

## ToC
* [Preliminary tasks](#Preliminary-tasks)
* [Introduction](#Introduction)
  * [Practical arrangements of this lab](#Practical-arrangements-of-this-lab)
  * [Grading](#Grading)
  * [Important reminder](#Important-reminder)
* [Tasks](#Tasks)
  * [Task 1](#Task-1)
  * [Task 2](#Task-2)
  * [Task 3](#Task-3)

## Preliminary tasks

Get familiar with the documentation of following tools / useful background info articles
* [Digital forensics on Wikipedia](https://en.wikipedia.org/wiki/Digital_forensics)
* [Steganography on Wikipedia](https://en.wikipedia.org/wiki/Steganography)
* [Data recovery on Wikipedia](https://en.wikipedia.org/wiki/Data_recovery)
* [Volatility wiki](https://github.com/volatilityfoundation/volatility/wiki)
* Search information about different tools which could be used in computer forensics
  * Examples: foremost, scalpel, exiftool, binwalk, strings
  * Simply writing "Digital forensics tools" to Google should provide huge load of information
* Image metadata and criminals [The Register](https://www.theregister.co.uk/2016/09/19/dark_web_drug_sellers_shutter_locationtracking_exif_data_from_photos/)
* [What is CTF?](https://dev.to/atan/what-is-ctf-and-how-to-get-started-3f04)

## Introduction

Digital forensics (aka digital forensic science) is field committed to recovering and investigating evidence found in digital devices.

Field is too large to cover in single lab (there exist multiple different digital forensic subfields) so this lab this lab only intends to give you slight intro to the digital forensic investigation related issues.

You can find good overview of the fied from [Wikipedia](https://en.wikipedia.org/wiki/Digital_forensics)

Notice that this lab does not make you actually any kind of certified digital forensics expert.
There exist actual training for those jobs which may include also lot of evidence chain-of-custody and legal issues which are not paid attention in this lab at all.
This lab tries to concentrate on interesting problem-solving situations which could theoretically be part of forensic investigation in real life.

## Practical arrangements of this lab

This lab does not require any specific Linux distribution to be used.
You are required to install quite many tools yourself, so anything you can install them on is good enough.
Kali image used earlier in this course should work reasonably well with this lab (and it has large set of needed tools already installed).

All memory and image dumps are available at same place than virtual machines on university network drive (packages are stored under folder "Lab6_Digital_Forensics").
There is also download link available in Moodle for that package.

## Important reminder

As you (hopefully!) already know, this lab is somewhat different than the others.

This lab features tasks being little similar than tasks in CTF-challenges.
There is specified type of information hidden in somewhere and it is up to you to figure it out.

Basically this means that this lab may be harder than the others,
instructions and directions where you should go are more unclear than in the other labs and change of tool usage problems and other irritating errors is higher than in the other labs.
This lab is arranged second time on this course.
This means that some of the irritating points-of-failure from last year have been addressed, but this lab could still be described as more "experimental" than other labs.

Other labs might have had simple tutorials/instructions how to use certain tools during them.
This lab does not do such a thing. You are expected to determine yourself what tools you have to use and learn usage of them yourself.

There may or may not be multiple ways to solve each task.
You must use your own judgement to determine what ways could or should be pursued to gain success.
Independent thinking/researching of problem and creative problem solving is highly encouraged.

You are required to install all needed tools yourself and if there happens to be some problems with them - well, hopefully Google and your own troubleshooting skills can help you then.

Consider yourself to be properly informed after reading this.

If you still want to take this challenge, good luck. You might really need it too.

## Grading

Task of this lab are divided to 3 different tasks which have corresponding grades in table below. Notice that *Good-to-have skills* are only directional descriptions about required skill levels.

Task| Grade/Level | Description | Good-to-have skills
--|:--:|--|--
1A|2|Memory investigation|Basic understanding of working of RAM and Volatility usage
1B+C|3| Data recovery and steganography investigation | Basic understanding of disk storage systems and steganography
2|4|DDoS attack investigation|Fluent usage of basic linux commands and coding, understanding of DDoS attack principles
3|5|Advanced experiments|Different skills depending on your project

# Tasks

Start working on Task 1 and proceed to harder ones after you complete that.

Read task instructions carefully before starting to work to have clear picture about what you are supposed to do. Every task should be clearly stating what you are expected to do and return.

**If you are doing this work in group, remember to mark down clearly which of you participated on which tasks**

## Task 1

Welcome to the imaginary day of digital forensic investigator. This task has highly fictional backstory which tries to give meaningful context to tasks. Notice that also any task or skill you will be using might or might not be useful in real life, because this lab does not equal to any official digital forensic training. Also, because this story is purely fictional, any possible connections to the real life events or people are coincidental.

Story starts here.

Mallory is notorious member of criminal underworld. He is known for illegal items trade, and he is rumored to have multiple shady contacts supplying him with high-quality "stuff", which have made him easy to gain foothold of black market.

Mallory has also reputation of being faster talker than thinker.

Mallory have been successful in his criminal activities lately, giving large influx of money and letting him expand his network, which have made him one of the "big players" of criminal underworld.

Unfortunately for him, also law enforcement at national level agencies have noticed his success. Mallory has reputation of being faster talker than thinker and because rumors spread fast, becoming known by law enforcement was only matter of time.

Big wheels start to turn, and large surveillance operation against Mallory and his minions was started started. After 3 months of fruitless efforts intel from trusted source appears: Mallorys gang is going to do drug deal next day.

Intel turns out to be correct and leading investigator decides that this is correct moment to strike. This would not be major victory, because only couple of Mallorys men would be caught red-handed, but it still could result Mallorys conviction if enough evidence is found about his involvement. Situation is not optimal, but small success is better than fruitless waiting of 3 months.

Moment to strike has come: Special units of police crash into the place of meeting and find 2 of Mallorys crooks with huge stash of illegal weapons and drugs. Simultaneously multiple carefully coordinated house raids are performed to all known members of Mallorys gang, including Mallorys home himself.

Mallory is caught by surprise when police storms into his apartment and immediately arrests him.
Police officers start to search Mallorys apartment and technician begins to investigate Mallorys computer which is turned on and logged on. After discussing with leading investigator, technician decides to start with dumping volatile memory of computer to his external hard drive.
Next to Mallorys computer is ordinary USB-memory stick. That stick is securely bagged to the evidence box for later inspection.

But Mallory has some brutal surprise for digital forensic technician: Just as memory dump from volatile memory is secured to investigators external drive, Mallorys computer starts to smoke and soon catches on fire explosively. Technician grabs his drive containing memory dump and runs out of apartment because toxic smoke from melting components is starting to spread fastly.
Apartment is evacuated fastly and any human casualties are avoided, but Mallorys improvised dead-man-switch - timed incendiary bomb inside computer which he supposedly managed to trigger when he heard police breaking in - has rendered whole machine totally unsalvageable.

Investigators know that there was so much critical information gone with Mallorys computer, and any hope they have left lies in single memory dump of Mallorys machine and ordinary USB memory stick.

### A) Inspecting memory with Volatility

> *Interrogator: You just would not mind telling where have you hidden your delivery caches?*
> 
> *Mallory: Haha! Do you imagine I will tell GPS locations of my last 2 hidden drug caches because you just ask for it? Uh-, I mean- I don't know what you are talking about!*
> 
> *Interrogator: Ok, ok, you do not need to shout. Lets have little lighter chat instead for while - shall we? I like lot of hiking, do you have any favourite map services you could recommend for me?*
> 
> *Mallory: Well, I am ok with this little chit-chat. Killing time is just fine because eventually you realize that I am completely innocent law-abiding citizen and let me go. Hmm, I like to use Google Maps via regular browser, I am little old stylish.*
> 
> *Interrogator: Ok, sounds nice. For what purpose are you using it?*
> 
> *Mallory: I want to check different locations before I-, uh- I mean I like hiking too.*

While exact location remains unknown, intel gathered from other sources suggests that Mallorys organization has been using codenames for those 2 caches: *LAKE* and *COAST*. Leading investigator suspects that those codenames are most likely describing also the places themselves. Leading investigator also suspects, that hidden caches are mostly located not too far from city and those should not require too long distance to be travelled by foot. Also caches can not obviously be located on densely populated areas.

Your first task is to find 2 different GPS locations where police officers should start for looking hidden stashes.

> *Leading investigator: There is problem with gathering Mallorys emails*
> 
> *You: How so? In this case we have court order for service provider to give us access to Mallorys email-account.*
> 
> *Leading investigator: Yes we do, but seems like they all have gone on holiday or something. I did not succeed connecting to anybody who could give us access right now. Typical corporate bureaucratics...*
> 
> *You: Oh. That's bad. But eventually we will get it.*
> 
> *Leading investigator: Yes we will. But this is urgent because any useful intel we could get from his email might be irrelevant next week because word about Mallorys arrest is spreading and his contacts are going to flee any moment with hidden caches.*
> 
> *You: I see. So we have only this memory dump right now. I'll see what I can do.*

Intel from unconfirmed sources says that there is rumors about Mallory having also third hidden cache. Nothing about it is known but its codename: *FOREST*

Your second task is to retrieve any email exchange of Mallory and his criminal partner. Extract content of the messages and solve location of third hidden cache.

Fill your answers and reasoning to the return template.

#### Hints and links

Volatility is tool for volatile memory inspection.

Find out what browser Mallory is using and then search for URLs which you want to find from its process memory.

Similar approach can be used to e-mail task: Determine what program Mallory is using for mail and start digging the process memory of it.

* [Volatility wiki](https://github.com/volatilityfoundation/volatility/wiki)
  * Useful volatility commands, `pslist`, `yarascan`, `memdump`
  * Correct profile for Mallorys machine is `Win7SP1x64_23418`
  * There exist lots of different Volatility plugins: Some may make your life lots of easier with this task
* Exiftool is tool for inspecting image metadata
* Foremost can extract files of specified type from other files, for example memory dumps of processes


### B) Data hiding & password recovery

> *Interrogator: We have started investigating that USB memory stick found next to your computer. Would you be nice enough to bother telling what data is on that stick?*
> 
> *Mallory: Of course. I am totally innocent so I can tell that on that stick was couple of totally useless RTF and PDF documents. And I kept some lorem ipsum flle and bunch of random strings there too.*
> 
> *Interrogator: "Was" and "kept". What do you mean?*
> 
> *Mallory: Well, I deleted everything. And formatted that stick too. Sadly everything is gone, otherwise I would have given everything to you because I totally have nothing to hide.*
> 
> *Interrogator: Well, I see. When you cleared that stick then?*
> 
> *Mallory: Just 15 seconds before you burst in through my door. What a coincidence!*
> 
> *Interrogator: Sure.*

Technical investigator attaches Mallorys memory stick to his machine by using write-blocker device. Stick seems to be empty and freshly formatted as Mallory implied. Technical investigator utilizes his tools to create raw disk-dump of that USB-stick and then gives it to you.

Your task is next:
* Recover RTF and PDF documents (1 RTF, 2 PDFs)
  * You must independently utilize your skills, creativity and hints from memory dump to decrypt PDF document content

#### Hints and links

Carve out deleted documents from disk and proceed on your task as you see fit.

Useful tools and utilities
* `foremost`, common tool for recovering files
* `scalpel`, another tool based on foremost
  * Learn to use custom configuring of it to carve files that foremost can not
* Any hex editors/readers (for example Ghex and hexdump) for investigating raw memory
* `hashcat`
  * Utility for recovering passwords, high amount of features for different situations
* `rockyou.txt`
  * Enormous collection of commonly used passwords
* `pdf2john.py` is utility for extracting hash information from PDF files

Some hints:
* Scalpel might sometimes produce broken files, try with another configurations or foremost
* Some PDF-readers might not handle AES-256 encrypted PDF well. They claim that the password is incorrect even when it is not. Try with another PDF-capable program (for example with internet browser).
* Hashcat might require some other libraries to be installed before it runs correctly
* Feel free to utilize any other tool you can find to solve these tasks
* Files with strong encryption and long enough passwords are unfeasible to be bruteforced
* Mallory might have kept some unneccessary file clutter on his USB-stick just to annoy anybody else who happens to read it.
* [File slack space](https://www.google.com/search?q=file+slack+space)


### C) Detecting and analyzing steganography

> *Investigator: Hey, I found something interesting*
> 
> *You: Ok, bring it on.*
> 
> *Investigator: I digged out some of Mallorys public online profiles and found that he has profile on this service*
> 
> *You: Not surprising - Even you and I and 50% of population of this nation have profile there*
> 
> *Investigator: Correct. You can see that Mallorys public profile lists all interest groups he has membership of. One of the groups gathered my attention: United Space Photo Gatherers - USPG. Do you see what I mean?*
> 
> *You: Hmm, yesss. Mallory seems not to be that kind of person who has interest on sharing and discussing space images*
> 
> *Investigator: I thought the same. I joined that group myself and started digging around little. Seems like that Mallory joined that group 2 years ago but has not posted single image or comment to that group - ever*
> 
> *You: Odd, but could be explained by that he just joined group and then forgot its existence. Happens to everybody sometimes*
> 
> *Investigator: So I thought. Until I went to the statistics page of that group. Obviously Mallory is not on those highly wanted "TOP 10 Poster of month"-listings at all, but some miscellaneous statistics show that he has been amongst TOP 100 frequent visitors during last 2 years. That is more than 99% of whole group.*
> 
> *You: That is weird. So what is your conclusion?*
> 
> *Investigator: I suspect that Mallory is using that message group as covert channel to receive messages from his criminal partners. Could you take a look at those images and either confirm or deny my theory?*
> 
> *You: I'll see what I can do*

Your task is to find 4 different suspicious images, and then extract the clear-text of the messages hidden into them. 

#### Hints and links

Steganography is practice of concealing actual information inside innocuous-looking information.

First problem is to identify image which is holding secret information, second problem is to find how to extract it.

Useful info
* [Useful overview to steganography](https://en.wikipedia.org/wiki/Steganography)
* Useful command line commands: `strings`, `hexdump`, `foremost`, `binwalk`
* [StegExpose](https://github.com/b3dk7/StegExpose) - Tool for detecting LSB steganography
* [zsteg](https://github.com/zed-0xff/zsteg) - Tool for detecting and extracting steganography
* steghide and its counterpart [StegCracker](https://github.com/Paradoxis/StegCracker)

Hints:
* Simplest form of hiding text in image is simply writing it straight to the image data, as plain text or encoded text
  * Tools like `strings` and `hexdump` are useful in these cases
  * Somebody could encode their message before injecting it to the image file, so you must decode it too
* More advanced image steganography includes modification of least-significant-bits (LSB) of PNG images.
  * Statistical tools exists to detect if image is tampered somehow
  * Tools like StegExpose and zsteg can detect and extract LSB-hidden information from images
* It is possible to include file into another file
  * Obviously it makes file bigger than it should be
  * Tools like foremost and/or binwalk can detect this kind of file-in-file tampering
  * Image steganography tool `steghide` can encrypt and hide information to image very efficiently
    * That tool has counter named `StegCracker`, which bruteforces information hidden with `steghide` out of the image (but you have to provide wordlist for it)
* Final hint for this task 1C comes from interrogation log:
> *Interrogator: By the way, if you hid your secret data to image with some tool supporting encryption, would you use some leetspeak version of your own name as password? Like `m4lL0rY`*
> 
> *Mallory: H-h-haha, of couse not - I am not obviously that stupid!*
> 
> *Interrogators note: Mallory starts to sweat visibly*

## Task 2: Analyzing DDoS attack

Your next task is to make analysis and report of the real world DDoS attack.

Remember malware presented in lab 3? That malware was responsible of causing this DDoS attack. You will find server log file from same place than memory dumps of earlier tasks.

After unzipping log, you may find out that opening log file (which contains over 6 million lines of data) may crash regular text editor so you most likely have to utilize other tools to initial investigation of log file. Commands `grep`, `less`, `sort`, `cut`, `awk` and `uniq` might be helpful.

Calculate next things from attack: Start time(s) and end time(s) (different parts in attack can exist), attack intensity charts/tables (requests per second and per minute) and IP addresses (bots) participating attack and analysis of them (times new bots entered in, how many bots were total, request counts per bot).

Feel free to use any tool/scripting language/existing solution to calculate your analysis.

Analyze how server was burdened. Obviously by sending overload of requests to it, but why just that kind of request was used? You do not know inner workings of server, but make educated guess based on what you see and know.

Can you find person who hypothetically was behind the whole attack? That person made one mistake, and his/hers IP address could be reasoned out from the logs.

### What to return

Your carefully thought out analysis of attack containing **at least** next items:
* Careful analysis of attack start/end time, intensities and bots participating it (analysis targets described above). Your style of reporting is free-formed, but depth and quality of analysis is expected to be sufficient.
* Well-reasoned explanation why certain type of request were used in DDoS attack.
* IP address which points towards the real person controlling the botnet, and reasoning why you ended up to that conclusion.

Fill your answers to the return template.

## Task 3

Last stage of this lab is more free-formed experimenting. Pick your option and start to explore issue and write report what your found/tried and what were the results.

### Option 1: Internet Browser Private Mode Forensics

We already touched little bit of investigating browser volatile memory in earlier tasks. It was not extremely hard to extract URLs of visited sites that way.

But how about private browsing? How is it viewed from the standpoint of digital forensics?

Familiarize yourself with next articles (you can find them in Google Scholar):
* *Do Private and Portable Web Browsers Leave Incriminating Evidence? - D Ohana, N Shashidhar*
* *A Process-Level Analysis of Private Browsing Behavior: A Focus on Google Chromes Incognito Mode - G Horsman*
* *On the Privacy of Private Browsing - A Forensic Approach - K Satvat, M Forshaw, F Hao, E Toreini*
* *Forensic Analysis of Private Browsing Artifacts - H Said, N Al Mutawa, I Al Awadhi*
* *Forensic Analysis and Evidence Collection for Web Browser Activity - A Nalawade, S Bharne, V Mane*

You might have to use your university account/use machines on university network to gain access to certain articles.

Do not limit yourself to the information above. Simply googling the issues can provide more interesting information and possibilities for experimentation.

Now it is your time to invent your own experiments. You can for example run different browsers in virtual machine, then take memory dumps or disk dumps of those machines and start digging around to find sensitive information.

Consider trying next:
* Do you manage replicate results which were presented in those research papers?
* What if you try with newer versions of browsers which produced some recoverable artifacts? Are problems fixed in newer versions or are they still present?

Write free-formed report of what kind of experiments you tried and what kind of results you achieved.

### Option 2: Your own small project

Invent your own experiments connected somehow to digital forensics and tell your idea to course assistant before starting to work.

Notice that your own idea should be about same difficulty/workload level than option 1. 

You may consider next vague ideas as examples of what kind of stuff could be tried:
* Filesystem/volume slack space experimenting - What kind of data can be hidden there for example with different filesystems
* OSINT tools - Multiple interesting tools exists (even already installed in default Kali linux), choose multiple of those and start making experiments with them.
* Android forensics - Acquire image of your own phone and start digging with common or smartphone-specific forensic tools

Write free-formed report of what kind of experiments you tried and what kind of results you achieved.
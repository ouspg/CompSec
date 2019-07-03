Computer Security Lab 6: Digital forensics
====

## ToC

* [Introduction](#Introduction)
  * [Practical arrangements of this lab](#Practical-arrangements-of-this-lab)
  * [Grading](#Grading)
* [Tasks](#Tasks)
  * [Task 1](#Task-1)
  * [Task 2](#Task-2)
  * [Task 3](#Task-3)

# Introduction

Digital forensics (aka digital forensic science) is field committed to recovering and investigating evidence found in digital devices.

TBA: Utilization on public and private sectors

Field is too large to cover in single lab (many different forensic fields) and this lab this lab only intends to give you slight into the world of forensic investigation.

You will learn to use tools like TBA:

TBA: List of useful links to tools and communities

## Practical arrangements of this lab

This lab utilizes the same Kali virtual machine you used in earlier labs. 2 raw dumps are available at TBA: Folder

TBA: Common info of lab practices

## Grading

Task of this lab are divided to 3 different tasks which have corresponding grades in table below. Notice that *Good-to-have skills* are only directional descriptions about required skill levels.

Task| Grade/Level | Description | Good-to-have skills
--|:--:|--|--
1|3|Memory, disk image and steganography investigation|Basic understanding of working of RAM, disk storage system and steganography
2|4|DDoS attack investigation|Fluent usage of command line tools, visualization tools and understanding of DDoS attack principles
3|5|Advanced experiments|Different skills depending on your project

# Tasks

Start working on task 1 and proceed to harder ones after you complete that. Task 1 is designed to take about 4 hours to complete so try to do it at lab session. Task 2 and 3 are more harder and laborous so you most likely do not have time to make all tasks in lab session.

Read task instructions carefully before starting to work to have clear picture about what you are supposed to do. Every task should be clearly stating what you are expected to do and return.

**If you are doing this work in group, remember to mark down clearly which of you participated on which tasks**

## Task 1

TBA: Better opening statement
Welcome to the imaginary day of digital forensic investigator. Task 1 has highly fictional backstory which tries to give meaningful context to tasks. Notice that also any task or skill you will be using might or might not be useful in real life, because this lab was not created by real digital forensic police/military official.

Story starts here.

Mallory is notorious member of criminal underworld. He is known for illeagal drug and weapon trade, and he is rumored to have very cheap and reliable suppliers on both which have made him easy to gain foothold of black market.

Mallory have been successfull in his criminal activities lately, giving large influx of money and letting him expand his network, which have made him one of the "big players" of criminal underworld.

Unfortunately for him, also law enforcement at national level agencies have noticed his success. Mallory has reputation of being faster talker than thinker and because rumors spread fast, becoming known by law enforcement was only matter of time.

Big wheels start to turn, and large surveillance operation against Mallory and his minions is started. After 3 monts of fruitless efforts intel from trusted source apprears: Mallorys gang is going to do drug deal next day.

Intel turns out to be correct and leading investigator decides that this is correct moment to strike. This would not be major victory, because only couple of Mallorys men would be caught red-handed, but it still could result Mallorys conviction if enough evidence is found about his involvement. Situation is not optimal, but small success is better than fruitless waiting of 3 months.

Moment to stirke has come: Special units of police crash into the place of meeting and find 2 of Mallorys crooks with huge stash of illeagal weapons and drugs. Simultaneously multiple carefully coordinated house raids are performed to all known members of Mallorys gang, including Mallorys home himself.

Mallory is caught by surprise when police storms into his apartment and immediately arrests him.
Police officers start to search Mallorys apartment and technican begins to investigate Mallorys computer which is turned on and logged on. After discussing with leading investigator, techican decides to start with dumping volatile memory of computer to his external hard drive.
Next to Mallorys computer is ordinary USB-memory stick. That stick is securely bagged to the evidence box for later inspection.

But Mallory has some brutal surprise to digital forensic technican: Just as memory dump from volatile memory is secured to investigators external drive, Mallorys computer starts to smoke and soon catches on fire explosively. Technican grabs his drive containing memory dump and runs out of apartment because toxic smoke from melting components is starting to spread fastly.
Apartment is evacuated fastly and any human casualities are avoided, but Mallorys improvised dead-man-switch - timed icendiary bomb inside computer which he supposedly managed to trigger when he heard police breaking in - has rendered whole machine totally unsalvageable.

Investigators know that there was so much critical information gone with Mallorys computer, and any hope they have left lies in single memory dump of Mallorys machine and ordinary USB memory stick.

### A) Inspecting Windows event logs

While other Investigations starts with interrogation of Mallory goes on.

Intel gathered from multiple sources during surveillance phase of operation suggests that there has been underworld meeting of criminal bosses at neighbouring city at day xxx.
Leading investigator does not know if Mallory attended that "conference" or not and he is unsure if he should continue that line of investigation or rule that out.

Mallory claims that he has been home all time on that day:

> *Interrogator: What you were doing on xxx*
> 
> *Mallory: Oh, xxx , I was at home watching cat videos with my computer. I definately was not committing anything shady business at another city because I sat front of my computer all day!*

Your task is to find out if any other evidence supports or conflicts with Mallorys alibi. You must tell to the leading investigator whether he should keep that line of investigation open (evidence does not support Mallorys alibi) or cut it out and redirect resources to other matters (evidence does support Mallorys alibi).

Fill your answer and reasoning to the return template.

#### Hints and links

Windows stores all kind of activity of machine to the event log which can greatly help investigating what has been happening with machine.

* TBA: Link to event log info
* There exists tool named [EVTXtract](https://github.com/williballenthin/EVTXtract) This tool can search for event logs from memory and recover them if possible


### B) Inspecting memory with Volatility

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
> *Mallory: I want to chek different locations before I-, uh- I mean I like hiking too.*

While exact location remains unknown, intel gathered from other sources suggests that Mallorys organization has been using codenames for those 2 caches: *Lake* and *Coast*.

Your first task is to find 2 different GPS locations where police officers should start for looking hidden stashes.

> *Leading investigator: There is problem with gathering Mallorys emails*
> 
> *You: How so? In this case we have court order for service provider to give us access to Mallorys email-account.*
> 
> *Leading investigator: Yes we do, but seems like they all have gone on holiday or something. I did not succeed connecting to anybody who could give us accees right now. Typical corporate bureaucratics...*
> 
> *You: Oh. Thats bad. But eventually we will get it.*
> 
> *Leading investigator: Yes we will. But this is urgent because any useful intel we could get from his email might be irrelevant next week because word about Mallorys arrest is spreading and his contacts are going to flee any moment.*
> 
> *You: I see. So we have only this memory dump right now. I'll see what I can do.*

Your second task is to retrieve any email Mallory sent to his criminal partners. You must extract address and content of that mail so investigators could have more leads about Mallorys criminal contacts.

Fill your answers and reasoning to the return template.

#### Hints and links

Volatility is tool for volatile memory inspection.

Find out what browser Mallory is using and then search for URLs which you want to find from its process memory.

* [Volatility wiki](https://github.com/volatilityfoundation/volatility/wiki)
* Possibly useful commands, `pslist`, `psscan`, `yarascan` 
* TBA: Mallorys OS version or correct volatility profile


### C) Data hiding & password recovery

TBA: Background story, task descriptions, tools

> *Interrogator: We have started investigating that USB memory stick. Would you be nice enough to bother telling what data is on that stick?*
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
> *Interrogator: Sure*


Technical investigator attachs Mallorys memory stick to his machine by using write-blocker device. Stick seems to be empty and freshly formatted as Mallory implied. Techincal investigator utilizes his tools to create raw disk-dump of that USB-stick and then gives it to you.

Your task is next:
* Recover RTF and PDF documents (4 of them total) and all of the content of them.
  * You must independently utilize your skills and creativity to unencrypt PDF document content
* Raw disk image can be found from TBA

#### Hints and links

Carve out deleted documents from disk and proceed your task as you find small hints in them. Good luck.

Useful tools
* `foremost`, common tool for finding information inside files
* `scalpel`, another tool based on foremost
  * Learn to use custom configuring of it to carve files that foremost can not
* Any hex editors/readers (for example Ghex and hexdump)
* `hashcat`
  * Brute-force utility for solving passwords from hashes, high amount of features targeting different types of passwords and encyptions
* `rockyou.txt`
  * Enormous collection of commonly used passwords
* `pdf2john.py` is utility for extracting hash information from PDF files.

Some hints:
* Scalpel might sometimes produce broken files, try with another configurations or foremost
* Some PDF-readers might not handle AES-256 encrypted PDF well. They claim that the password is incorrect even when it is not. Try with another reader (for example internet browser plugin reader).
* Hashcat might require some other libraries to be installed before it runs correctly
* Feel free to utilize any other tool you can find to solve these tasks

### F) Detecting and analyzing steganography

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
> *Investigator: So I thought. Until I went to the statistics page of that group. Obviously Mallory is not on those highly wanted "TOP 10 Poster of month"-listings at all, but some miscellaneous staticstics show that he has been amongst TOP 100 frequent visitors during last 2 years. That is more than 99% of whole group.*
> 
> *You: That is weird. So what is your conclusion?*
> 
> *Investigator: I suspect that Mallory is using that message group as covert channel to receive messages from his criminal partners. Could you take a look at those images and either confirm or deny my theory?*
> 
> *You: I'll see what I can do*

Your task is to find 4 different suspicious images, and then extract the messages hidden into them.

Files can be found in the folder x

#### Hints and links

Steganography is practice of concealing actual information inside innocous-looking information. TBA: short description of usage

First problem is to identify image which is holding secret information, second problem is to find how to extract it.

Useful info
* [Userful overwiev to steganography](https://en.wikipedia.org/wiki/Steganography)
* Useful command line commands: `strings`, `hexdump`, `foremost`, `binwalk`
* [StegExpose](https://github.com/b3dk7/StegExpose) - Tool for detecting LSB steganography
* [zsteg](https://github.com/zed-0xff/zsteg) - Tool for detecting and extracting steganography
* steghide and its counterpart [StegCracker](https://github.com/Paradoxis/StegCracker)
* TBA: Link to bash tutorial

TODO: Rewrite needed for this part
Hints:
* As you probably already quessed, images are the likely carriers of hidden information in this task
* Simplest form of hiding text in image is simply writing it straight to the image with for example hex editor
  * Consider investigating image with tools like hexdump and strings to find out if image has pure textual context embedded
  * There is quite many images there, so running commands one-by-one to them is kinda laborous. Consider writing bash script to yourself like
  * Somebody could encode their message before injecting it to the image file, so you must decode it too
* More advanced image steganography includes modification of least-significant-bits (LSB) of image. This type of hiding can easily hide data from human eye because changing LSB of each pixel does not make noticeable difference to humans.
  * Statistical tools exists to detect if image is tampered somehow
  * You may use tools StegExpose and zsteg to detect and extract LSB-hidden information from images
* It is possible to include file into another file
  * Obviously file with hidden information is bigger than it should be
  * Consider tools like foremost and/or binwalk to inspect suspicious files
  * Image steganography tool steghide has countertool named StegCracker

> *Interrogator: "By the way, if you encryped your information, would you use some leetspeak version of your own name as password? Like `m4lL0rY`*
> 
> *Mallory: "H-h-haha, of couse not - I am not obviously that stupid!*
> 
> *Irrogators note: Mallory starts to sweat visibly*

## Task 2

TBA: DDoS investigation task

## Task 3

TBA: Description

Multiple varying options available

### Option 1: TBA (browser private mode investigation)

TBA: Initial info and links to research

### Option 2: OSINT

TBA: Task description, requirements and links to tools

### Option 3: Your own invention

TBA: Generic description